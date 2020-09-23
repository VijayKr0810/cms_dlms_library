#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/home/iot-gateway/hiredis/hiredis.h"
#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"


/* Extern  */
extern redisContext 			*p_redis_handler;
extern redisReply 				*p_redis_reply;
extern dlms_dcu_config_t 		dlms_dcu_config;
/* Globals */
char 							g_dbg_buff[256],g_msg_str[256];
FILE 							*g_dlms_file_ptr;
uint32_t						g_position;

/* Extern  */
extern char 					debug_file_name[];

/* ================================================================== */
int32_t read_cfg_from_redis(void)
{
	uint8_t idx=0,port_idx=0;
	char 	*p_gen_ptr=NULL;
	
	memset(&dlms_dcu_config,0,sizeof(dlms_dcu_config));
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO DcuDevId NumEthPort MeterType DataFormatType DataTrfType MasterProtoType DbgLogEnable DcuDevLoc DcuGpsLoc DbgLogIp");
	
	//printf("Total Elements : %d\n",p_redis_reply->elements);
	
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
		goto EXIT;
	
	for (port_idx=0; port_idx<MAX_NO_OF_SERIAL_PORT; port_idx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSER_MET_INFO NumMeters",port_idx);
		if(p_redis_reply!=NULL)
		{
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				dlms_dcu_config.dlms_channel_cfg[port_idx].num_meter=atoi(p_redis_reply->element[0]->str);
				freeReplyObject(p_redis_reply);
			}
			else 
				goto EXIT;
		}
		else
			goto EXIT;
		
		printf("tot num dlms meter config : %d\n",dlms_dcu_config.dlms_channel_cfg[port_idx].num_meter);
		
		uint8_t jdx=0;
		
		for(idx=0; idx<MAX_NO_OF_METER_PER_PORT; idx++)
		{
			
			p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSerMeter_%dConfig Enable MeterId MeterAddrSize MeterAddr MeterPass MeterLoc",port_idx,idx+1);
		
			//printf("Idx : %d SER_MET_INFO Total Elements : %d\n",idx+1,p_redis_reply->elements);
			
			//for(jdx=0; jdx<p_redis_reply->elements;jdx++)
				//printf("Jdx : %d STR : %s\n",jdx+1,p_redis_reply->element[jdx]->str);
			
			if(p_redis_reply!=NULL)
			{
				//printf("0\n");
				
				p_gen_ptr=p_redis_reply->element[0]->str;
				if(p_gen_ptr!=NULL)
				{
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].enable=atoi(p_redis_reply->element[0]->str);
				}
				else 
					goto EXIT;
				
				//printf("1\n");
				p_gen_ptr=p_redis_reply->element[1]->str;
				if(p_gen_ptr!=NULL)
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_id=atoi(p_redis_reply->element[1]->str);
				else 
					goto EXIT;
				//printf("2\n");
				p_gen_ptr=p_redis_reply->element[2]->str;
				if(p_gen_ptr!=NULL)
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_addr_size=atoi(p_redis_reply->element[2]->str);
				else 
					goto EXIT;
				//printf("3\n");
				p_gen_ptr=p_redis_reply->element[3]->str;
				if(p_gen_ptr!=NULL)
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_addr=atoi(p_redis_reply->element[3]->str);
				else 
					goto EXIT;
				//printf("4\n");
				p_gen_ptr=p_redis_reply->element[4]->str;
				if(p_gen_ptr!=NULL)
					strcpy(dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_pass,p_redis_reply->element[4]->str);
				else 
					goto EXIT;
				//printf("5\n");
				p_gen_ptr=p_redis_reply->element[5]->str;
				if(p_gen_ptr!=NULL)
					strcpy(dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_loc,p_redis_reply->element[5]->str);
				else 
					goto EXIT;
				//printf("6\n");
				freeReplyObject(p_redis_reply);
			}
			else
				goto EXIT;
		}
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
	char		temp_str[8];
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

FILE* write_dbglog(FILE*p_dbg_fptr_arr, char*log_file_path, char *p_data)
{
	uint64_t			position;
	
	if(p_dbg_fptr_arr==NULL)
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

	position = ftell(p_dbg_fptr_arr);
	g_position = position;
	
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
	return p_dbg_fptr_arr;
}


/* End of File */