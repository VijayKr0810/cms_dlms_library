#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
#include "cms_mon_proc.h"
#include "/home/iot-gateway/redis-5.0.8-bin/include/hiredis.h"


proc_info_t 					proc_info[MAX_PROCESSES];
dlms_dcu_config_t 				dlms_dcu_config;
redisContext 					*p_redis_handler;
redisReply 						*p_redis_reply;

int32_t 						g_win_dbg_soc_fd;
char 							g_rbt_buffer[512];
char 							debug_file_name[64];
uint8_t 						g_num_procs;
time_t                          g_rawtime,g_last_diag_time,g_last_hc_send_time,g_check_proc_time;
time_t 							g_proc_timeout[MAX_PROCESSES];
uint8_t 						g_kill_all,g_restart,g_reboot_pidx;
uint8_t 						g_dlms_proc_fail_cnt[MAX_NO_OF_SERIAL_PORT];
pid_t 							g_parent_pid;

void exec_procs(int32_t idx);
int32_t start_child(char *p_proc_name,char *p_arg1,char *p_arg2);
int32_t write_rbt_msg_into_redis(int proc_id,uint8_t port_id);
int32_t restart_proc_id(int proc_id,int32_t arg_idx);
int32_t get_proc_idx(char* p_procName,int32_t arg_idx);

/* ----------------------------------------------------------------------------------------------- */
int32_t redis_init(char *hostname, uint16_t port)
{
	static char fun_name[]="redis_init()";
	
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	
	dbg_log(INFORM,"%-20s : Trying to connect on Redis Server : %s with port : %d\n",fun_name,hostname,port);
	
    p_redis_handler = redisConnectWithTimeout(hostname, port, timeout);
    if (p_redis_handler == NULL || p_redis_handler->err) 
	{
        if (p_redis_handler) 
		{
			dbg_log(INFORM,"%-20s : Connection error: %s\n",fun_name,p_redis_handler->errstr);
            
            redisFree(p_redis_handler);
        } 
		else 
		{
			dbg_log(INFORM,"%-20s : Connection error: can't allocate redis context\n",fun_name);
        }
    }
	
	dbg_log(INFORM,"%-20s : Connected on Redis Server : %s with port : %d\n",fun_name,hostname,port);
 
	return 0;
}

/*********************************************************************
	*Function 		: write_hc_on_redis()
	*In Params 		: void .
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to write hc message on redis  .
**********************************************************************/

int32_t write_hc_on_redis()
{
	time_t curr_time;
	curr_time=time(NULL);
	
	if ((curr_time-g_last_hc_send_time)>45)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmset monproc_hc_msg updatetime %d",curr_time);
		freeReplyObject(p_redis_reply);
		g_last_hc_send_time=time(NULL);
	}
	
	return 0;
}

/*********************************************************************
	*Function 		: write_reboot_info()
	*In Params 		: reason and process name.
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to write reboot info on file.
**********************************************************************/

int32_t write_reboot_info(char reason,char* p_procName)
{
	static char fun_name[]="write_reboot_info()";
	int file_fd=0,len=0,flags=0;
	
	char date_str[SIZE_64];
	struct stat file_pt;
	struct tm	*p_curr_time=NULL;
	time_t local_time;
	
	time(&local_time);
	p_curr_time = localtime(&local_time);
	
	memset(date_str,0,sizeof(date_str));
	sprintf(date_str,"%02d-%02d-%d %02d:%02d:%02d",
	p_curr_time->tm_mday,p_curr_time->tm_mon+1,p_curr_time->tm_year+1900,p_curr_time->tm_hour,p_curr_time->tm_min,p_curr_time->tm_sec);
	
	if ( (file_fd=stat(RBT_INFO_PATH,&file_pt)) == 0)
	{
		len = file_pt.st_size;
		dbg_log(INFORM,"%-20s : Rbtt info file size : %d\n",fun_name,len);
	}
	else
	{
		dbg_log(INFORM,"%-20s : Error while getting stat of Rbt fact info file.Err : %d\n",fun_name,errno);
		len = -1;
	}
	
	if(len < MAX_RBT_INFO_SIZE)	
	flags = (O_APPEND|O_CREAT|O_RDWR);
	else
	{
		memset(g_rbt_buffer,0,sizeof(g_rbt_buffer));
		sprintf(g_rbt_buffer,"tail -10 %s > %s_bkup",RBT_INFO_PATH,RBT_INFO_PATH);
		system(g_rbt_buffer);
		
		memset(g_rbt_buffer,0,sizeof(g_rbt_buffer));
		sprintf(g_rbt_buffer,"rm  %s",RBT_INFO_PATH);
		system(g_rbt_buffer); 
		
		memset(g_rbt_buffer,0,sizeof(g_rbt_buffer));
		sprintf(g_rbt_buffer,"mv %s_bkp %s",RBT_INFO_PATH,RBT_INFO_PATH);
		system(g_rbt_buffer); 
		
		flags = (O_APPEND|O_CREAT|O_RDWR);
	}
	
	if ( (file_fd=open(RBT_INFO_PATH, flags)) < 0)
	{
		dbg_log(REPORT,"%-20s : Rbt info info file open  Error. Errno : %d Err : %s\n",fun_name,errno,strerror(errno));
		return -1;
	}
	else
	{
		memset(g_rbt_buffer,0,sizeof(g_rbt_buffer));
		if(reason == RBT_PING_FAIL)
		sprintf(g_rbt_buffer,"%s : All Ping Failed.TGLE WDT PIN STOPPED. RBT THRGH WDT,due to Proc : %s \n",date_str,p_procName);
		
		else if( reason==RBT_DEF_RST_TO)
		sprintf(g_rbt_buffer,"%s : TGLE WDT PIN STOPPED for Configured Hrs. RBT THRGH WDT\n",date_str);
		
		else if(reason ==RBT_FROM_WDT)
		sprintf(g_rbt_buffer,"%s : TGLE WDT PIN STOPPED by WDT. due to Proc : %s\n",date_str,p_procName);
		
		else if(reason ==SIGNAL_INTR)
		sprintf(g_rbt_buffer,"%s : SIgnal Interrupt Received \n",date_str);
		
		else if(reason ==RBT_OTH_PROC)
		sprintf(g_rbt_buffer,"%s : Reason for rebooting  : %s\n",date_str,p_procName);
		
		else if (reason == PROC_UP )
		sprintf(g_rbt_buffer,"%s :  %s\n",date_str,p_procName);
		else
		sprintf(g_rbt_buffer,"%s : DEF : TGLE WDT PIN STOPPED RBT THRGH WDT\n",date_str);
		
		len = strlen(g_rbt_buffer);
		
		int ret=-1;
		
		ret=write(file_fd, g_rbt_buffer, len);
		if( ret != len)
		{
			dbg_log(REPORT,"%-20s : boot fact Info Write Failed. Size Mismatch.wrote : %d. Expected : %d Err : %s\n",
			fun_name,ret,len,strerror(errno));
			
			close(file_fd);
			
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : Boot fact info write Success.Wrote : %d. Expected : %d.\n",fun_name,ret,len);
		
		close(file_fd);
	}
	
	return 0;
}

/*********************************************************************
	*Function 		: check_hc_msg()
	*In Params 		: void .
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to check hc message on redis  .
**********************************************************************/

int32_t check_hc_msg(void)
{
	static char fun_name[]="check_hc_msg()";
	uint8_t 	idx=0,pidx=0;
	
	if(proc_info[pidx].status)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmget web_back_end_hc_msg updatetime");
		if(p_redis_reply->element[0]->str)
		{
			dbg_log(INFORM,"%-20s : HC Msg Time from Web BackEnd Proc, Updated time : %d\n",
				fun_name,atoi(p_redis_reply->element[0]->str));
			
			g_proc_timeout[pidx]=atoi(p_redis_reply->element[0]->str);
		}
		
		freeReplyObject(p_redis_reply);
	}	
	pidx++;
	
	for (idx=0; idx<MAX_NO_OF_SERIAL_PORT; idx++)
	{
		if(proc_info[pidx].status)
		{
			p_redis_reply = redisCommand(p_redis_handler,"hmget P%d_dlms_poll_proc_hc_msg updatetime",idx);
			if(p_redis_reply->element[0]->str)
			{
				dbg_log(INFORM,"%-20s : HC Msg Time from DLMS ProcId : %d, Updated time : %d\n",
				fun_name,idx,atoi(p_redis_reply->element[0]->str));
				g_proc_timeout[pidx]=atoi(p_redis_reply->element[0]->str);
			}
			
			freeReplyObject(p_redis_reply);
		}
		pidx++;
	}
	
	if(proc_info[pidx].status)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmget ntp_hc_msg updatetime");
		if(p_redis_reply->element[0]->str)
		{
			dbg_log(INFORM,"%-20s : >>Rcv HC Msg from Ntp Client Proc, Updated time : %d\n",fun_name,atoi(p_redis_reply->element[0]->str));
			g_proc_timeout[pidx]=atoi(p_redis_reply->element[0]->str);
		}
		
		freeReplyObject(p_redis_reply);
	}	
	pidx++;

	return 0;
}

/*********************************************************************
	*Function 		: send_pmon_diag_msg_to_redis()
	*In Params 		: void.
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to write  diag message on redis server.
**********************************************************************/
int32_t send_pmon_diag_msg_to_redis(void)
{
	static char fun_name[]="send_pmon_diag_msg_to_redis()";
	time_t 		update_time=0;
	struct tm	*p_curr_time_tm;
	char		time_str[SIZE_64];
	
/*
	char 		buff[32];
	FILE 		*p_flt_ptr=0;
 	memset(iot_dev_diag_msg.model_num,0,32);
	memset(iot_dev_diag_msg.fw_ver,0,32);
	memset(iot_dev_diag_msg.serial_num,0,32);
	
	p_flt_ptr = fopen("/srv/www/htdocs/info/version.txt","r");
	if(p_flt_ptr != NULL)
	{
		fscanf(p_flt_ptr,"%31s",buff);
		strcpy(iot_dev_diag_msg.model_num,buff);
		
		fscanf(p_flt_ptr,"%31s",buff);
		strcat(iot_dev_diag_msg.fw_ver,buff);
		
		strcat(iot_dev_diag_msg.fw_ver,"_");
		
		fscanf(p_flt_ptr,"%31s",buff);
		strcat(iot_dev_diag_msg.fw_ver,buff);
		
		fclose(p_flt_ptr);
	}
	
	strcpy(iot_dev_diag_msg.serial_num,IOT_SERIAL_NUM); */
	
	dbg_log(INFORM,"%-20s : Sending diag msg on redis server\n",fun_name);
	
	update_time=time(NULL);
	p_curr_time_tm = localtime(&update_time);
	memset(time_str,0,sizeof(time_str));
	strftime(time_str, SIZE_64,"%d/%b/%Y_%H:%M:%S", p_curr_time_tm);
	
	/* p_redis_reply = redisCommand(p_redis_handler,"hmset pmon_diag updatetime %s  model_num %s fw_ver %s serial_num %s iot_gw_up_time %s",time_str,iot_dev_diag_msg.model_num,iot_dev_diag_msg.fw_ver,iot_dev_diag_msg.serial_num,iot_dev_diag_msg.iot_gw_up_time); */
	
	//curr_time = time(NULL);
	g_last_diag_time = time(NULL);

	return 0;
}

/*********************************************************************
	*Function 		: kill_all_proc()
	*In Params 		: void.
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to kill all processes.
**********************************************************************/

void kill_all_proc(void)
{
	uint8_t proc_idx=0;
	
	static char fun_name[] = "kill_all_proc()";
	g_kill_all = 1;
	
	for ( proc_idx = 0; proc_idx < g_num_procs; proc_idx++ )
	{
		if ( proc_info[proc_idx].status )
		{
			dbg_log(INFORM,"%-20s : Killing process : %s pid %d\n",fun_name,proc_info[proc_idx].proc_name,proc_info[proc_idx].pid);
			
			kill(proc_info[proc_idx].pid,SIGKILL);
			
			usleep(250000);
		}
	}
}

/*********************************************************************
	*Function 		: waitfor_child()
	*In Params 		: signal number.
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to handle sigchild signal.
**********************************************************************/

void waitfor_child(int32_t sig)
{
	static char fun_name[] = "waitfor_child()";
	int			status=0;
	pid_t		child_pid=0;
	uint8_t			proc_idx=0;
	time_t		time_now;
	time_t		curr_time_sec;
	struct tm	*p_curr_time_tm=NULL;
	char		time_str[64];
	char 		msg_data[128];
	
	child_pid = waitpid(-1, &status,0);
	
	dbg_log(INFORM,"%-20s : Received SIGCHLD : pid : %d, status : %d\n",fun_name,child_pid,status);
	
	if ( g_kill_all == 1 )
	{
		dbg_log(INFORM,"%-20s : Killing the child process..\n",fun_name);
		return;
	}
	
	for ( proc_idx = 0; proc_idx < g_num_procs; proc_idx++ )
	{
		if ( proc_info[proc_idx].status == 1 )
		{
			if ( proc_info[proc_idx].pid == child_pid )
			{
				dbg_log(INFORM,"%-20s : Child : %d : ProcName : %s \n",fun_name,proc_idx,proc_info[proc_idx].proc_name);
				
				proc_info[proc_idx].status = 0;
				
				time_now = time(NULL);
				
				dbg_log(INFORM,"%-20s : Num of restarts : %d TimeDiff : %d\n",
				fun_name,proc_info[proc_idx].num_restart,(time_now-proc_info[proc_idx].restart_time));
				
				if ((time_now-proc_info[proc_idx].restart_time ) < PROC_RESTART_TIME_DIFF )
				{
					dbg_log(INFORM,"%-20s : Time diff less than defined value\n",fun_name);
					
					if ( proc_info[proc_idx].num_restart >= MAX_PROC_RESTARTS )
					{
						dbg_log(REPORT,"%-20s : Problem with the process, cannot restart\n",fun_name);
						
						curr_time_sec = time(NULL);
						p_curr_time_tm = localtime(&curr_time_sec);
						strftime(time_str, SIZE_64,"%d/%b/%Y_%H:%M:%S", p_curr_time_tm);
						
						dbg_log(INFORM,"%-20s : Problem with the process : %s failing continuously.\n",fun_name,
						proc_info[proc_idx].proc_name);
						
						memset(msg_data,0,sizeof(msg_data));
						sprintf(msg_data,"Problem with the process : %s failing continuously",proc_info[proc_idx].proc_name);
						
						write_reboot_info(RBT_FROM_WDT, msg_data);
						
						p_redis_reply = redisCommand(p_redis_handler,"hmset reboot_msg updatetime %s reboot_status %d process_name %s reason %s",time_str,1,proc_info[proc_idx].proc_name,"Problem with the process failing continuously");
						
						return;
					}
					
					memset(msg_data,0,sizeof(msg_data));
					sprintf(msg_data," Restarting the process : %s failing continuously",proc_info[proc_idx].proc_name);						
					write_reboot_info(RBT_FROM_WDT, msg_data);		
					
					//sleep(3);
					
					exec_procs(proc_idx);
					proc_info[proc_idx].restart_time = time_now;
					proc_info[proc_idx].num_restart++;
				}
				else
				{
					exec_procs(proc_idx);
					proc_info[proc_idx].restart_time = time_now;
					proc_info[proc_idx].num_restart = 0; 
					return;
				}
			}	
		}
	}
}

/*********************************************************************
	*Function 		: fill_proc_cfg_file()
	*In Params 		: Void.
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to fill the process details on structure.
**********************************************************************/
int32_t fill_proc_cfg_file(void)
{
	static char fun_name[]="fill_proc_cfg_file()";
	uint8_t pidx=0,proc_idx=0;
	
	memset(	&proc_info[proc_idx],0,sizeof(proc_info_t));
	memcpy(&proc_info[proc_idx].proc_name,CMS_WEB_BACK_END_PROC,sizeof(CMS_WEB_BACK_END_PROC));
	sprintf(proc_info[proc_idx].cmd_line_arg1,"0");
	sprintf(proc_info[proc_idx].cmd_line_arg2,"0");
	proc_idx++;
	
	for (pidx = 0; pidx < MAX_NO_OF_SERIAL_PORT; pidx++ )
	{
		if ( dlms_dcu_config.dlms_channel_cfg[pidx].num_meter > 0 )
		{
			memset(	&proc_info[proc_idx],0,sizeof(proc_info_t));
			memcpy(&proc_info[proc_idx].proc_name,CMS_DLMS_MET_POLL_PROC,sizeof(CMS_DLMS_MET_POLL_PROC));
			sprintf(proc_info[proc_idx].cmd_line_arg1,"%d",pidx);
			sprintf(proc_info[proc_idx].cmd_line_arg2,"0");
			proc_idx++;  
		}
	}
	
	memset(	&proc_info[proc_idx],0,sizeof(proc_info_t));
	memcpy(&proc_info[proc_idx].proc_name,CMS_NTP_CLIENT_PROC,sizeof(CMS_NTP_CLIENT_PROC));
	sprintf(proc_info[proc_idx].cmd_line_arg1,"0");
	sprintf(proc_info[proc_idx].cmd_line_arg2,"0");
	proc_idx++;

	switch(dlms_dcu_config.dlms_dcu_info.data_format_type)
	{
		case DCU_CSV_FILE_TYPE :
			memset(	&proc_info[proc_idx],0,sizeof(proc_info_t));
			memcpy(&proc_info[proc_idx].proc_name,CMS_GEN_CSV_FILE_PROC,sizeof(CMS_GEN_CSV_FILE_PROC));
			sprintf(proc_info[proc_idx].cmd_line_arg1,"0");
			sprintf(proc_info[proc_idx].cmd_line_arg2,"0");
			proc_idx++;
		
		break;
		
		default : break;
	}
	
	memset(	&proc_info[proc_idx],0,sizeof(proc_info_t));
	memcpy(&proc_info[proc_idx].proc_name,CMS_RESET_SWITCH_PROC,sizeof(CMS_RESET_SWITCH_PROC));
	sprintf(proc_info[proc_idx].cmd_line_arg1,"0");
	sprintf(proc_info[proc_idx].cmd_line_arg2,"0");
	proc_idx++;
	
	printf("Checking FTP Push proc status : %d\n",dlms_dcu_config.ftp_ser_cfg.enable);
	if(dlms_dcu_config.ftp_ser_cfg.enable == 1)
	{
		memset(	&proc_info[proc_idx],0,sizeof(proc_info_t));
		memcpy(&proc_info[proc_idx].proc_name,CMS_FTP_PUSH_PROC,sizeof(CMS_FTP_PUSH_PROC));
		sprintf(proc_info[proc_idx].cmd_line_arg1,"0");
		sprintf(proc_info[proc_idx].cmd_line_arg2,"0");
		proc_idx++;
	}
	
	g_num_procs = proc_idx;
	
	dbg_log(INFORM,"%-20s : procCfg() : Num of procs : %d\n",fun_name,g_num_procs);
	
	return 0;
}

/*********************************************************************
	*Function 		: exec_procs()
	*In Params 		: Void.
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to launch child process.
**********************************************************************/
void exec_procs(int32_t idx)
{
	int ret=0;
	static char fun_name[] = "exec_procs()";
	time_t	time_now;
	char msg_data[128];
	memset(msg_data,0,sizeof(msg_data));
	
	time_now = time(NULL);
	
	dbg_log(INFORM,"%-20s : Starting child %d proc : %s %s %s\n",
	fun_name,idx,proc_info[idx].proc_name,proc_info[idx].cmd_line_arg1,proc_info[idx].cmd_line_arg2);
	
	/* sprintf(msg_data,"starting child  %d proc %s",idx,proc_info[idx].proc_name);
	write_reboot_info(PROC_UP,msg_data); */
	
	ret = start_child(proc_info[idx].proc_name,proc_info[idx].cmd_line_arg1,proc_info[idx].cmd_line_arg2);
	if ( ret <= 0 )
	{
		dbg_log(FATAL,"%-20s : Failed to start child : %d \n",fun_name,idx);
		proc_info[idx].status = 0;
	}
	else
	{
		proc_info[idx].status = 1;
		proc_info[idx].pid = ret;
		proc_info[idx].restart_time = time_now;
		
		g_proc_timeout[idx]=time_now;
		
		dbg_log(INFORM, "%-20s : Started child : %d successfully , pid : %d\n",fun_name,idx,ret);
	}
	
	dbg_log(INFORM,"%-20s : ***** End of exec_procs****\n",fun_name);
	
	return;
}

/*********************************************************************
	*Function 		: start_child()
	*In Params 		: process name ,cmd line argument 1, cmd line argument 2.
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to start the child process.
**********************************************************************/
int32_t start_child(char *p_proc_name, char *p_arg1, char *p_arg2)
{
	pid_t		child_pid=0;
	static char fun_name[]="start_child()";
	
	switch( (child_pid=fork()) )
	{
		case -1: // fork failed - log and exit or return;
		{
			dbg_log(FATAL, "%-20s : Fork failed : %s\n",fun_name,strerror(errno));
			exit(-1);
		}
		break;
		
		case 0: // 'child process'
		{
			dbg_log(INFORM,"%-20s : line argumet 1 : %s & 2 : %s\n",fun_name,p_arg1,p_arg2);
			if( execlp(p_proc_name, p_proc_name,p_arg1,p_arg2,NULL) == -1 )
			{
				dbg_log(FATAL, "%-20s : execlp failed %s\n",fun_name,strerror(errno));
				exit(-1);
			}
		}
		break;
		
		default: // 'parent process'
		{
			dbg_log(INFORM,"%-20s : Fork succeeded pid : %d\n",fun_name,child_pid);
			return child_pid;
		}
		break;
	}
	
	dbg_log(INFORM,"%-20s : ***** End of start_child****\n",fun_name);
	
	return 0;
}

/*********************************************************************
	*Function 		: invoke_procs()
	*In Params 		: None
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to launch the child process.
**********************************************************************/
int32_t invoke_procs(void)
{
	static char fun_name[] = "invoke_procs()";
	int8_t proc_idx=0;
	
	dbg_log(INFORM,"%-20s : Number of procs : %d\n",fun_name,g_num_procs);
	
	for ( proc_idx = 0; proc_idx < g_num_procs; proc_idx++ )
	{
		exec_procs(proc_idx);
		
		sleep(1);
	}
	
	dbg_log(INFORM,"%-20s : *** End of invokeProc ***\n",fun_name);
	
	return 0;
}

/*********************************************************************
	*Function 		: check_proc_timeout()
	*In Params 		: None
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to check process timeout (any process is hanged )
**********************************************************************/
int32_t check_proc_timeout(void)
{
	static char 	fun_name[]="check_proc_timeout()";
	uint8_t 		proc_idx=0, port_idx=0;
	time_t 			curr_time;
	char 			msg_data[128];
	
	curr_time = time(NULL);
	
	for(proc_idx=0; proc_idx<g_num_procs; proc_idx++)
	{
		dbg_log(INFORM,"%-20s : ProcId : %d CurrTime : %d , PrevTime : %d\n",fun_name,proc_idx,curr_time,g_proc_timeout[proc_idx]);
		if((curr_time-g_proc_timeout[proc_idx])>REFF_TIME_OUT)
		{
			dbg_log(INFORM,"%-20s : ProcId : %d DiffTimeout : %d sec\n",fun_name,proc_idx,(curr_time-g_proc_timeout[proc_idx]));
			
			g_proc_timeout[proc_idx]=curr_time;
			
			if(strcmp(CMS_DLMS_MET_POLL_PROC,proc_info[proc_idx].proc_name)==0)
			{
				dbg_log(REPORT,"%-20s : From DLMS MET POLL PROC : %d HC Message not recv within in time : %d sec\n",
				fun_name,port_idx,REFF_TIME_OUT);
				
				g_dlms_proc_fail_cnt[port_idx]=g_dlms_proc_fail_cnt[port_idx]+1;
				
				dbg_log(REPORT,"%-20s : DLMS MET POLL PROC : %d  Number of Fail Count : %d\n",
				fun_name,port_idx,g_dlms_proc_fail_cnt[port_idx]);
					
				if(g_dlms_proc_fail_cnt[port_idx]>1)
				{
					p_redis_reply = redisCommand(p_redis_handler,"hmset P%d_dlms_poll_proc_hc_msg updatetime %d",port_idx,time(NULL));
					freeReplyObject(p_redis_reply);
					
					restart_proc_id(DLMS_POLL_PROC_ID,port_idx);
					
					g_proc_timeout[proc_idx]=time(NULL);
					
					proc_info[proc_idx].restart_time=time(NULL);
				}
				
				if(g_dlms_proc_fail_cnt[port_idx]>MAX_PROC_HANG_CNT)
				{
					dbg_log(REPORT,"%-20s : DLMS MET POLL PROC : %d  Number of Fail Count : %d, MAX : %d\n",
					fun_name,port_idx,g_dlms_proc_fail_cnt[port_idx],MAX_PROC_HANG_CNT);
					
					g_proc_timeout[proc_idx]=time(NULL);
					
					memset(msg_data,0,sizeof(msg_data));
					
					sprintf(msg_data,"Dlms poll proc : %d, failed numof times : %d",port_idx,g_dlms_proc_fail_cnt[port_idx]);
					
					write_rbt_msg_into_redis(DLMS_POLL_PROC_ID,port_idx);
					
					write_reboot_info(RBT_FROM_WDT, msg_data);
					
					g_dlms_proc_fail_cnt[port_idx]=0;
					
					g_check_proc_time = time(NULL);
					return 0;
				}
				
				port_idx++;
			}
		}
	}
	
	g_check_proc_time = time(NULL);
	return 0;
}

/*********************************************************************
	*Function 		: write_rbt_msg_into_redis()
	*In Params 		: process id .
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to write reboot message on redis  .
**********************************************************************/
int32_t write_rbt_msg_into_redis(int proc_id, uint8_t port_id)
{
	time_t		curr_time_sec=0;
	struct tm	*p_curr_time_tm;
	char		time_str[SIZE_64];
	char		reason_msg[SIZE_64];
	
	curr_time_sec = time(NULL);
	
	memset(time_str,0,sizeof(time_str));
	memset(reason_msg,0,sizeof(reason_msg));
	
	p_curr_time_tm = localtime(&curr_time_sec);
	strftime(time_str, SIZE_64,"%d/%b/%Y_%H:%M:%S", p_curr_time_tm);
	
	switch(proc_id)
	{
		case DLMS_POLL_PROC_ID :
		{
			sprintf(reason_msg,"DLMS Proc : %d, process is hanged long time",port_id);
			p_redis_reply = redisCommand(p_redis_handler,"hmset reboot_msg updatetime %s reboot_status %d process_name %s reason %s",
			time_str,1,CMS_DLMS_MET_POLL_PROC,reason_msg);
			
			freeReplyObject(p_redis_reply);
			
			static char fun_name[]="write_rbt_msg_into_redis";
			dbg_log(INFORM,"%-20s : %s process is hanged long time so unit reboot is initiated \n",fun_name,CMS_DLMS_MET_POLL_PROC);
		}
		
		break;
		
		default : break;
	}
	
/* 	kill_all_proc();
	
	sleep(5);
	
	exit(1); */
	
	return 0;
}

/*********************************************************************
	*Function 		: restart_proc_id()
	*In Params 		: process id , argument index.
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to restart the process  .
**********************************************************************/

int32_t restart_proc_id(int proc_id,int32_t arg_idx)
{
	static char fun_name[]="restart_proc_id()";
	uint8_t proc_idx=0;
	
	switch(proc_id)
	{
		case DLMS_POLL_PROC_ID :
			proc_idx=get_proc_idx(CMS_DLMS_MET_POLL_PROC,arg_idx);
			if(proc_idx!=-1)
			{
				g_kill_all = 1;
				
				dbg_log(INFORM,"%-20s : Restarting the process : %s %s\n",fun_name,proc_info[proc_idx].proc_name,proc_info[proc_idx].cmd_line_arg1);
				
				kill(proc_info[proc_idx].pid,SIGKILL);
				
				exec_procs(proc_idx);
				
				g_kill_all = 0;
			}
		break;

		default : break;
	}
	
	sleep(1);
	
	return 0;
}

/*********************************************************************
	*Function 		: get_proc_idx()
	*In Params 		: process name and argument index .
	*Output 		: None
	*Return			: process id or appropriate error code.
	*Description 	: This function is used to get process id  .
**********************************************************************/
int32_t get_proc_idx(char* p_procName,int32_t arg_idx)
{
	uint8_t proc_idx=0;
	
	for(proc_idx=0; proc_idx<MAX_PROCESSES; proc_idx++)
	{
		if(strcmp(p_procName,proc_info[proc_idx].proc_name)==0)
			if(atoi(proc_info[proc_idx].cmd_line_arg1)==arg_idx)
				return proc_idx;
	}
	
	return -1;	
}

void sig_handler(int32_t sig)
{
	static char fun_name[] = "sig_handler()";
	
	//dbg_log(INFORM ,"%-20s : Recv Signal : %d\n",fun_name,sig);
	
	//if ( sig == SIGALRM || sig == SIGTERM )
	
	/* if ( sig == SIGALRM )
	{
		dbg_log(INFORM,"%-20s : IN SIGALARM\n",fun_name);
		
		//alarm(20);
		return;
	} */
	
	dbg_log(INFORM,"%-20s : Received signal %d. Kill all the processes\n",fun_name,sig);
	
	kill_all_proc();
	
	write_reboot_info(SIGNAL_INTR,"Recv Killall signal to kill all the process.");
	
	exit(0);
}

int32_t read_cfg_from_redis(void)
{
	static char fun_name[]="read_cfg_from_redis()";
	
	uint8_t pidx=0;
	const char *p_gen_ptr=NULL;
	
	memset(&dlms_dcu_config,0,sizeof(dlms_dcu_config_t));
	
	printf("reading config from redis\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget FTP_SER_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		printf("Ftp Enable Status : %d\n",atoi(p_redis_reply->element[0]->str));
		dlms_dcu_config.ftp_ser_cfg.enable=atoi(p_redis_reply->element[0]->str);
		freeReplyObject(p_redis_reply);
	}
	else
	{
		dbg_log(INFORM,"%-20s : FTP Push Proc Disables\n",fun_name);
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO DcuDevId");
	if(p_redis_reply!=NULL)
	{
		printf("1 total num read element : %d\n",p_redis_reply->elements);
		freeReplyObject(p_redis_reply);
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO DcuDevId NumEthPort MeterType DataFormatType DataTrfType MasterProtoType DbgLogEnable DcuDevLoc DcuGpsLoc DbgLogIp");
	
	//printf("total num read element : %d\n",p_redis_reply->elements);
	
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dlms_dcu_info.dcu_dev_id=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
			dlms_dcu_config.dlms_dcu_info.num_eth_port=atoi(p_redis_reply->element[1]->str);
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
			dlms_dcu_config.dlms_dcu_info.meter_type=atoi(p_redis_reply->element[2]->str);
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
			dlms_dcu_config.dlms_dcu_info.data_format_type=atoi(p_redis_reply->element[3]->str);
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
			dlms_dcu_config.dlms_dcu_info.data_trf_type=atoi(p_redis_reply->element[4]->str);
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
			dlms_dcu_config.dlms_dcu_info.master_proto_type=atoi(p_redis_reply->element[5]->str);
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[6]->str;
		if(p_gen_ptr!=NULL)
			dlms_dcu_config.dlms_dcu_info.dbglog_enable=atoi(p_redis_reply->element[6]->str);
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[7]->str;
		if(p_gen_ptr!=NULL)
			strcpy(dlms_dcu_config.dlms_dcu_info.dcu_location,p_redis_reply->element[7]->str);
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[8]->str;
		if(p_gen_ptr!=NULL)
			strcpy(dlms_dcu_config.dlms_dcu_info.dcu_gps_loc,p_redis_reply->element[8]->str);
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[9]->str;
		if(p_gen_ptr!=NULL)
			strcpy(dlms_dcu_config.dlms_dcu_info.dbglog_ip,p_redis_reply->element[9]->str);
		else 
			goto EXIT;

		freeReplyObject(p_redis_reply);
	}
	else
	{
		printf("Error in reading config from redis\n");
		goto EXIT;
	}
	
	for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSER_MET_INFO NumMeters",pidx);
		if(p_redis_reply!=NULL)
		{
			printf("port : %d, total num meters : %d\n",pidx,p_redis_reply->elements);
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				dlms_dcu_config.dlms_channel_cfg[pidx].num_meter=atoi(p_redis_reply->element[0]->str);
				freeReplyObject(p_redis_reply);
			}
			else 
				goto EXIT;
		}
		else
			goto EXIT;
	}
	
	return 0;
	
	EXIT:
		return -1;
}

int main(int argc, char **argv)
{
	static char fun_name[]="main()";
	uint8_t idx,proc_idx;
	
	memset(debug_file_name,0,sizeof(debug_file_name));
	sprintf(debug_file_name,"%s/%s",LOG_DIR,CMS_MON_PROC_LOG_FILE_NAME);
	
	dbg_log(INFORM,"%-20s : This is Process Monitor Module!!!!\n",fun_name);
	dbg_log(INFORM,"%-20s : Creating Updated Config into redis from binary file\n",fun_name);
	
	system(CMS_BIN_TO_REDIS_PROC);
	
	if(redis_init("127.0.0.1",6379)!=0)
	{
		dbg_log(INFORM,"%-20s : Failed to initilised Redis Server\n",fun_name);
		return -1;
	}

	if(read_cfg_from_redis()<0)
	{
		dbg_log(INFORM,"%-20s : Failed to read basic cfg from redis\n",fun_name);
		return -1;
	}

	g_win_dbg_soc_fd = create_ipc_socket(dlms_dcu_config.dlms_dcu_info.dbglog_ip,PMON_MODULE_IPC_PORT);
	if(g_win_dbg_soc_fd<0)
	{
		dbg_log(INFORM,"%-20s : Failed to create Windows Dbg log socket\n",fun_name);
		return -1;
	}
	else
	{
		dbg_log(INFORM,"%-20s : Success Windows Dbg log socket on Ip : %s, With FD : %d\n",
		fun_name,dlms_dcu_config.dlms_dcu_info.dbglog_ip,g_win_dbg_soc_fd);
	}
	
	g_parent_pid = getpid();
	
	//set signal handler for parent
	signal(SIGTERM,sig_handler);
	signal(SIGINT,sig_handler);
	signal(SIGHUP,sig_handler);
	signal(SIGSEGV,sig_handler);
	signal(SIGCHLD,waitfor_child);
	
	fill_proc_cfg_file();
	
	for(proc_idx=0; proc_idx<g_num_procs; proc_idx++)
		dbg_log(INFORM,"%-20s : proc no : %d : %s %s %s\n",fun_name,proc_idx+1,
				proc_info[proc_idx].proc_name,
				proc_info[proc_idx].cmd_line_arg1,
				proc_info[proc_idx].cmd_line_arg2);
	
	dbg_log(INFORM,"%-20s : Writing reboot status as Zero\n",fun_name);
	p_redis_reply = redisCommand(p_redis_handler,"hmset reboot_msg reboot_status %d",0);
			
	invoke_procs();
	
	uint8_t g_port_idx;
	for(g_port_idx=0; g_port_idx<MAX_NO_OF_SERIAL_PORT; g_port_idx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmset P%d_dlms_poll_proc_hc_msg updatetime %d",g_port_idx,time(NULL));
		if(p_redis_reply!=NULL)
		{
			dbg_log(INFORM,"%-20s : PortIdx : %d, HC Set msg Status : %s\n",fun_name,g_port_idx,p_redis_reply->str);
		}
		
		freeReplyObject(p_redis_reply);
	}
	
	sleep(5);
	
	g_last_diag_time = time(NULL);
	g_check_proc_time = time(NULL);
	g_last_hc_send_time=time(NULL);

	dbg_log(INFORM,"%-20s : After Invoke, filling current time for all procs\n",fun_name);
	for (idx=0; idx<g_num_procs; idx++)
	{
		g_proc_timeout[idx]=time(NULL);
		dbg_log(INFORM,"%-20s : ProcId : %d, Filled Current TIme in sec : %d\n",fun_name,idx,g_proc_timeout[idx]);
	}
	
	dbg_log(INFORM,"%-20s : >>>>>>>>>Entring into idle while loop!!!!\n",fun_name);
	
	while ( 1 ) 
	{
		time_t current_time=time(NULL);
		
		check_hc_msg();	
		
/* 		if ((current_time - g_check_proc_time ) > CHECK_PROC_TIME)
		{
			check_proc_timeout();		
		} */
		
		if ((current_time - g_last_diag_time ) > SEND_DIAG_MSG_TIME)
		{
			send_pmon_diag_msg_to_redis();
			check_proc_timeout();
		}
		
		write_hc_on_redis();
		
		sleep(3);
		
		dbg_log(INFORM,"%-20s : In Idle while loop to test killall command\n",fun_name);
	}
	
	dbg_log(INFORM,"%-20s : ********** Returning from PMON Proc. Here we should not be available!!!!\n",fun_name);
	
	return 0;
}

/* End Of File */