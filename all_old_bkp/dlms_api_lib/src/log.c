/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	log.c
* Summary:  log related to DLMS Module.
*
**********************************************************************/

/* Includes */
#include "gen_inc.h"
#include "log.h"

/* Globals */
char 							g_dbg_buff[256],g_msg_str[256];
FILE 							*g_dlms_file_ptr;
uint32_t						g_position;

/* Extern  */
extern char 					debug_file_name[];

/* -------------------------------------------------------------------------- */
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
	
	return done;
}

/**************************************************************************************************
*Function 					: write_dbglog()
*Input Parameters 			: file pointer, debug log file path, debug message
*Output Parameters 			: None
*Return	Value				: file pointer,.
*Description 				: write debug message in file.
********************************************************************************************************/

FILE* write_dbglog(FILE*p_dbg_fptr_arr, char*g_file_path, char *p_data)
{
	uint64_t			position;
	
	if(p_dbg_fptr_arr==NULL)
	{
		p_dbg_fptr_arr = fopen(g_file_path, "w");
		if(p_dbg_fptr_arr == NULL)
		{
			printf("Write Mode open call failed for file : %s , Error : %s\n",g_file_path,strerror(errno));
			return NULL;
		}
	}
	else
	{
		p_dbg_fptr_arr = fopen(g_file_path, "a");
		if(p_dbg_fptr_arr == NULL)
		{
			printf("Append Mode open call failed for file : %s , Error : %s\n",g_file_path,strerror(errno));
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
		
		sprintf(bkp_log_file,"%s_bkp",g_file_path);
		
		sprintf(cmd_str,"cp %s %s",g_file_path,bkp_log_file);
		system(cmd_str);
		
		p_dbg_fptr_arr = fopen(g_file_path, "w");
		
		if(p_dbg_fptr_arr == NULL)
		{
			printf("open call failed for file : %s , Error : %s\n",g_file_path,strerror(errno));
			return NULL;
		}
	}
	
	fclose(p_dbg_fptr_arr);
	return p_dbg_fptr_arr;
}

/* End of file */