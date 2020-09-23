/**
 * log.c -- log and error handling.
 *    _______       _______            __        __
 *   / ____/ |     / / ___/____  _____/ /_____  / /_
 *  / / __ | | /| / /\__ \/ __ \/ ___/ //_/ _ \/ __/
 * / /_/ / | |/ |/ /___/ / /_/ / /__/ ,< /  __/ /_
 * \____/  |__/|__//____/\____/\___/_/|_|\___/\__/
 *
 * The MIT License (MIT)
 * Copyright (c) 2009-2016 Gerardo Orellana <hello @ goaccess.io>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Includes */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "log.h"
#include "xmalloc.h"
#include "gen_inc.h"
#include "log.h"

static FILE *log_file;


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

/* Open a access file whose name is specified in the given path. */
int
access_log_open (const char *path)
{
  if (path == NULL)
    return 0;

  if (access (path, F_OK) != -1)
    log_file = fopen (path, "a");
  else
    log_file = fopen (path, "w");
  if (log_file == NULL)
    return 1;

  return 0;
}

/* Close the access log file. */
void
access_log_close (void)
{
  if (log_file != NULL)
    fclose (log_file);
}

#pragma GCC diagnostic ignored "-Wformat-nonliteral"
/* Debug otuput */
void
dbg_printf (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  vfprintf (stderr, fmt, args);
  //vfprintf (stdout, fmt, args);
  //fflush (stdout);
  //printf("\n");
  va_end (args);
}

/* Write formatted access log data to the logfile. */
void
access_fprintf (const char *fmt, ...)
{
  va_list args;

  /* if (!log_file)
    return; */

  va_start (args, fmt);
  vfprintf (log_file, fmt, args);
  //vfprintf (stdout, fmt, args);
  fflush (log_file);
  //fflush (stdout);
  va_end (args);
}

#pragma GCC diagnostic warning "-Wformat-nonliteral"
