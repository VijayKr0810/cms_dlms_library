/* Includes */
#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
#include "/home/iot-gateway/redis-5.0.8-bin/include/hiredis.h"

/*  Local Micro*/
#define LOG_FILE_NAME 		"cms_ftp_push_proc.log"
#define FTP_NORMAL_SERVER 	1
#define FTP_LOG_SERVER 		2

dlms_dcu_config_t 		dlms_dcu_config;
redisContext 			*p_redis_handler;
redisReply 				*p_redis_reply;

/* Globals */
char 							g_dbg_buff[256],g_msg_str[256];
FILE 							*g_dlms_file_ptr;
uint32_t						g_position;
char 							debug_file_name[64];
uint8_t 						g_curl_init_flag;
uint8_t 						g_log_curl_init_flag;


/* Fun Proto Type */
int32_t read_cfg_from_redis(void);
int32_t redis_init(char *hostname, uint16_t port);
int32_t dbg_log(uint8_t mode, const char *p_format, ...);
int32_t curl_init(uint8_t);
void send_dcu_log_data(void);
void send_meter_data(void);

/* ============================================================================ */
int main(int argc, char **argv)
{
	static char fun_name[]="main()";
	int32_t fun_ret=-1;
	
	memset(debug_file_name,0,sizeof(debug_file_name));
	sprintf(debug_file_name,"%s/%s",LOG_DIR,LOG_FILE_NAME);
	
	if(redis_init("127.0.0.1",6379)!=0)
	{
		dbg_log(REPORT,"%-20s : Redis Client initialize failed\n",fun_name);
		return -1;
	}
	
	if(read_cfg_from_redis()!=0)
	{
		dbg_log(REPORT,"%-20s : Redis reading config failed\n",fun_name);
		return -1;
	}
	
	if(dlms_dcu_config.ftp_ser_cfg.enable==1)
	{
		dbg_log(INFORM,"%-20s : Enabled  FTP server\n",fun_name);
	}
	
	FILE *p_file_ptr = fopen("/usr/cms/log/cms_temp.log","w");
	if(p_file_ptr==NULL)
	{
		dbg_log(REPORT,"%-20s : Failed to create a dummy log file\n",fun_name);
	}
	else
	{
		fprintf(p_file_ptr,"%s","Test Ftp Data!!\n");
	}
	fclose(p_file_ptr);
	
	if(curl_init(FTP_NORMAL_SERVER)!=0)
	{
		dbg_log(REPORT,"%-20s : Curl Init Failed First Time\n",fun_name);
		g_curl_init_flag=0;
	}
	else
	{
		dbg_log(REPORT,"%-20s : Curl Init Success\n",fun_name);
		g_curl_init_flag=1;
	}
	
	if(dlms_dcu_config.ftp_ser_cfg.diff_log_ser==1)
	{
		dbg_log(INFORM,"%-20s : Enabled Diff server for log purpose\n",fun_name);
		if(curl_init(FTP_LOG_SERVER)!=0)
		{
			dbg_log(REPORT,"%-20s : Log Curl Init Failed failed First Time\n",fun_name);
			g_log_curl_init_flag=0;
		}
		else
		{
			dbg_log(REPORT,"%-20s : Log Curl Init success First Time\n",fun_name);
			g_log_curl_init_flag=1;
		}
	}
	
	if(g_curl_init_flag!=0)
	{
		dbg_log(INFORM,"%-20s : First Time to send Meter data\n",fun_name);
		send_meter_data();
	}
	
	if(g_log_curl_init_flag!=0)
	{
		if(dlms_dcu_config.ftp_ser_cfg.diff_log_ser==1)
		{
			dbg_log(INFORM,"%-20s : First Time to send  DCU Log data\n",fun_name);
			send_dcu_log_data();
		}
	}

	time_t curr_time_sec = time(NULL);
	time_t log_curr_time_sec = time(NULL);
	
	while(1)
	{
		if(g_curl_init_flag==0)
		{
			if(curl_init(FTP_NORMAL_SERVER)!=0)
			{
				dbg_log(REPORT,"%-20s : Curl Init Failed failed Inside Idle Loop\n",fun_name);
				g_curl_init_flag=0;
			}
			else
			{
				g_curl_init_flag=1;
			}
		}
		else
		{
			if((time(NULL)-curr_time_sec)>dlms_dcu_config.ftp_ser_cfg.upload_period*60)
			{
				curr_time_sec=time(NULL);
				dbg_log(INFORM,"%-20s : Inside Idle Loop Time to send Meter data\n",fun_name);
				send_meter_data();
			}
		}
		
		if(g_log_curl_init_flag==0)
		{
			if(dlms_dcu_config.ftp_ser_cfg.diff_log_ser==1)
			{
				if(curl_init(FTP_LOG_SERVER)!=0)
				{
					dbg_log(REPORT,"%-20s : Log Curl Init Failed failed Inside Idle loop\n",fun_name);
					g_log_curl_init_flag=0;
				}
				else
				{
					g_log_curl_init_flag=1;
				}
			}
		}
		else
		{
			if(dlms_dcu_config.ftp_ser_cfg.diff_log_ser==1)
			{
				if((time(NULL)-log_curr_time_sec)>dlms_dcu_config.ftp_ser_cfg.log_upload_period)
				{
					curr_time_sec=time(NULL);
					dbg_log(INFORM,"%-20s : Inside Idle Loop Time to DCU Log data\n",fun_name);
					send_dcu_log_data();
				}
			}
		}
	}
	
	sleep(3);
	
	return 0;
}

int32_t read_cfg_from_redis(void)
{
	uint8_t idx=0,port_idx=0;
	
	memset(&dlms_dcu_config,0,sizeof(dlms_dcu_config));
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget FTP_SER_INFO Enable DiffLogSer SerPort UploadPeriod LocDir Password UserName SerIp LogSerPort LogUploadPeriod LogLocDir LogPassword LogUserName LogSerIp");
	
	printf("Total Elements : %d\n",p_redis_reply->elements);
	
	if(p_redis_reply!=NULL)
	{
		if(p_redis_reply->element[0]->str!=NULL)
		{
			dlms_dcu_config.ftp_ser_cfg.enable=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[1]->str!=NULL)
		{
			dlms_dcu_config.ftp_ser_cfg.diff_log_ser=atoi(p_redis_reply->element[1]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[2]->str!=NULL)
		{
			dlms_dcu_config.ftp_ser_cfg.ser_port=atoi(p_redis_reply->element[2]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[3]->str!=NULL)
		{
			dlms_dcu_config.ftp_ser_cfg.upload_period=atoi(p_redis_reply->element[3]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[4]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ftp_ser_cfg.loc_dir,p_redis_reply->element[4]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[5]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ftp_ser_cfg.password,p_redis_reply->element[5]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[6]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ftp_ser_cfg.username,p_redis_reply->element[6]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[7]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ftp_ser_cfg.ser_ip,p_redis_reply->element[7]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[8]->str!=NULL)
		{
			dlms_dcu_config.ftp_ser_cfg.log_ser_port=atoi(p_redis_reply->element[8]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[9]->str!=NULL)
		{
			dlms_dcu_config.ftp_ser_cfg.log_upload_period=atoi(p_redis_reply->element[9]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[0]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ftp_ser_cfg.log_loc_dir,p_redis_reply->element[7]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[0]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ftp_ser_cfg.log_password,p_redis_reply->element[7]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[0]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ftp_ser_cfg.log_username,p_redis_reply->element[7]->str);
		}
		else 
			goto EXIT;
		
		if(p_redis_reply->element[0]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ftp_ser_cfg.log_ser_ip,p_redis_reply->element[7]->str);
		}
		else 
			goto EXIT;
	}
	
	return 0;
	
	EXIT:
	return -1;
}

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
   
    freeReplyObject(p_redis_reply);
	
	return 0;
}

/**************************************************************************************************
*Function 					: dbg_log()
*Input Parameters 			: mode, debug message
*Output Parameters 			: None
*Return	Value				: Total num bytes of debug message.
*Description 				: mentain debug information.
********************************************************************************************************/
int32_t dbg_log(uint8_t mode, const char *p_format, ...)
{
	uint32_t done = 0;
	va_list arg;

	memset(g_dbg_buff,0,sizeof(g_dbg_buff));
	va_start (arg, p_format);
	done = vsprintf ((char *)g_dbg_buff, (const char *)p_format, arg);
	
	time_t		curr_time_sec=0;
	struct tm	*p_curr_time_tm;
	char		time_str[64];
	char		file_name[64];

	curr_time_sec = time(NULL);
	p_curr_time_tm = localtime(&curr_time_sec);
	strftime(time_str, 64,"%d_%b_%Y_%H_%M_%S", p_curr_time_tm);
	
	memset(g_msg_str,0,sizeof(g_msg_str));
	strcpy(g_msg_str, time_str);
	strcat(g_msg_str, " : ");
	
	switch(mode)
	{
		case INFORM:
			strcat(g_msg_str, "[Inform]");
		break;
		
		case WARNING:
			strcat(g_msg_str, "[Warning]");
		break;
		
		case SEVERE:
			strcat(g_msg_str, "[Severe]");
		break;
		
		case FATAL:
			strcat(g_msg_str, "[Fatal]");
		break;
		
		case REPORT:
			strcat(g_msg_str, "[Report]");
		break;
		
		default : break;
	}
	
	//strcat(g_msg_str, p_dbg_msgs[ mode ]);
	
	strcat(g_msg_str, " : ");
	
	strcat(g_msg_str, g_dbg_buff);
	g_msg_str[strlen(g_msg_str)] = 0;
	
	printf("%s",g_msg_str);
	fflush(stdout);
	
	memset(file_name,0,sizeof(file_name));
	sprintf(file_name,"%s",debug_file_name);
			
	#if DEBUG_LOG
		g_dlms_file_ptr = write_dbglog(g_dlms_file_ptr, file_name, g_msg_str);
	#endif
			
	va_end(arg);
	
	//printf("Return of dbglog : %d\n",done);
	return done;
}

/**************************************************************************************************
*Function 					: write_dbglog()
*Input Parameters 			: file pointer, debug log file path, debug message
*Output Parameters 			: None
*Return	Value				: file pointer,.
*Description 				: write debug message in file.
********************************************************************************************************/

FILE* write_dbglog(FILE*dbg_fptr_arr, char*log_file_path, char *p_data)
{
	FILE				*p_dbg_fptr_arr=NULL;
	long int			position=0;
	struct stat 		st_log;
	
	if(stat(log_file_path,&st_log)==-1)
	{
		p_dbg_fptr_arr = fopen(log_file_path, "w");
		if(p_dbg_fptr_arr == NULL)
		{
			printf("Write Mode open call failed for file : %s , Error : %s\n",log_file_path,strerror(errno));
			return NULL;
		}
	}
	else
	{
		p_dbg_fptr_arr = fopen(log_file_path, "a");
		if(p_dbg_fptr_arr == NULL)
		{
			printf("Append Mode open call failed for file : %s , Error : %s\n",log_file_path,strerror(errno));
			return NULL;
		}
	}
	
	p_data[255] = '\0';
	fprintf(p_dbg_fptr_arr,"%s",p_data);
	fflush(p_dbg_fptr_arr);

	if(p_dbg_fptr_arr!=NULL)
		position = ftell(p_dbg_fptr_arr);
	
	if(position>=FILE_SIZE_EXCEED)
	{
		printf("Dbg File size reached max.\n");
		if(p_dbg_fptr_arr!=NULL)
		{
			fclose(p_dbg_fptr_arr);
		}
		
		char bkp_log_file[64],cmd_str[128];
		
		memset(bkp_log_file,0,sizeof(bkp_log_file));
		memset(cmd_str,0,sizeof(cmd_str));
		
		sprintf(bkp_log_file,"%s_bkp",log_file_path);
		
		rename(log_file_path,bkp_log_file);
		
		//sprintf(cmd_str,"cp %s %s",log_file_path,bkp_log_file);
		//system(cmd_str);
		
		p_dbg_fptr_arr = fopen(log_file_path, "w");
		
		if(p_dbg_fptr_arr == NULL)
		{
			printf("open call failed for file : %s , Error : %s\n",log_file_path,strerror(errno));
			return NULL;
		}
	}
	
	fclose(p_dbg_fptr_arr);
	//printf("dbgmsg written in path : %s\n",log_file_path);
	return dbg_fptr_arr;
}

/* End Of file */