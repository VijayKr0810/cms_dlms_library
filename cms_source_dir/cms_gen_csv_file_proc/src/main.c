#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
//#include "/home/iot-gateway/hiredis/hiredis.h"
#include "/home/iot-gateway/redis-5.0.8-bin/include/hiredis.h"


/*  Local Micro*/
#define LOG_FILE_NAME 		"cms_gen_csv_proc.log"
#define INST_INFO_KEY 		"inst_info"
#define NP_INFO_KEY 		"np_info"
#define BILLING_INFO_KEY 	"billing_key_info"
#define EVENT_INFO_KEY 		"event_type_key_info"
#define LS_BLK_INFO_KEY 	"ls_blk_info"
#define REFF_FORM_CSV_TIME 	16*60

#define DCU_CSV_FILE_TYPE 	1
/* Global */
char 					debug_file_name[64];
dlms_dcu_config_t 		dlms_dcu_config;

redisContext 			*p_redis_handler;
redisReply 				*p_redis_reply;

int32_t read_cfg_from_redis(void);
int32_t redis_init(char *hostname, uint16_t port);

int32_t form_csv_file_format(void)
{	
	static char 	fun_name[]="form_csv_file_format()";
	uint8_t 		idx,pidx;
	DIR 			*p_data_dir=NULL;
	struct dirent 	*p_dir_str=NULL;
	char 			file_name[64],dir_data_path[64],csv_file_path[64];
	char 			*p_text_data=NULL;
	struct 			stat st,dir_st;
	int32_t 		file_fd=0,cnt_idx;
	FILE			*p_file_ptr=NULL;
	
	memset(dir_data_path,0,sizeof(dir_data_path));
	sprintf(dir_data_path,"%s/%s",ROOT_DATA_DIR,"upstream");	
	if (stat(dir_data_path, &dir_st) == -1) 
	{
		if( (mkdir(dir_data_path,0777) ) < 0 )					
		{
			dbg_log(INFORM,"%-20s : Created Root upstream data dir : %s\n",fun_name,dir_data_path);
		}
	}
	
	memset(dir_data_path,0,sizeof(dir_data_path));
	sprintf(dir_data_path,"%s/%s",ROOT_DATA_DIR,"upstream/csv_proc");
	if (stat(dir_data_path, &dir_st) == -1) 
	{
		if( (mkdir(dir_data_path,0777) ) < 0 )					
		{
			dbg_log(INFORM,"%-20s : Created Root upstream csv proc data dir : %s\n",fun_name,dir_data_path);
		}
	}
	
	for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
	{
		for(idx=0; idx<dlms_dcu_config.dlms_channel_cfg[pidx].num_meter;idx++)
		{
			if(!dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].enable)
				continue;
			
			memset(dir_data_path,0,sizeof(dir_data_path));
			sprintf(dir_data_path,"%s/%s/meter_id_%d",ROOT_DATA_DIR,"upstream/csv_proc",
			pidx*MAX_NO_OF_METER_PER_PORT+idx+1);
			if (stat(dir_data_path, &dir_st) == -1) 
			{
				if( (mkdir(dir_data_path,0777) ) < 0 )					
				{
					dbg_log(INFORM,"%-20s : Created Root upstream csv data dir : %s\n",fun_name,dir_data_path);
				}
			}
		}
	
		for(idx=0; idx<dlms_dcu_config.dlms_channel_cfg[pidx].num_meter; idx++)
		{
			if(!dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].enable)
				continue;
			
			memset(dir_data_path,0,sizeof(dir_data_path));
			sprintf(dir_data_path,"%s/meter_id_%d",ROOT_DATA_DIR,pidx*MAX_NO_OF_METER_PER_PORT+idx+1);
			
			p_data_dir = opendir(dir_data_path);
			if ( p_data_dir == NULL )
			{
				printf("Failed to opendir %s, Error : %s\n",dir_data_path,strerror(errno));
				continue;
			}
			
			while ( (p_dir_str = readdir(p_data_dir)) != NULL )
			{
				if (( strcmp(p_dir_str->d_name,".") == 0 ) || ( strcmp(p_dir_str->d_name,"..") == 0 ))
				{
					continue;
				}
				
				memset(file_name,0,sizeof(file_name));
				sprintf(file_name,"%s/%s",dir_data_path,p_dir_str->d_name);
				
				printf("Finding File : %s\n",file_name);
				
				if (stat(file_name, &st)==-1) 
				{
					printf("can't find file : %s\n", file_name);
					continue;
				}
		
				file_fd = open(file_name, O_RDONLY);
				if (file_fd == -1) 
				{
					printf("can't open to read original file - %s\n", file_name);
					continue;
				}
		  
				// Read file
				p_text_data = malloc(st.st_size+1); // this is not going to be freed
				if (st.st_size!=read(file_fd, p_text_data, st.st_size)) 
				{
					printf("can't read original file - %s\n", file_name);
					close(file_fd);
					continue;
				}
				
				close(file_fd);
				
				// Add null char
				p_text_data[st.st_size]='\0';
				
				for(cnt_idx=0;cnt_idx<st.st_size+1;cnt_idx++)
				{
					if(p_text_data[cnt_idx]=='\t')
						p_text_data[cnt_idx]=',';
				}
				
				printf("Updation success for file : %s\n",p_dir_str->d_name);
				
				memset(csv_file_path,0,sizeof(csv_file_path));
				sprintf(csv_file_path,"%s/%s/meter_id_%d/%s.csv",ROOT_DATA_DIR,
				"upstream/csv_proc",pidx*MAX_NO_OF_METER_PER_PORT+idx+1,p_dir_str->d_name);
				
				p_file_ptr=fopen(csv_file_path,"w");
				if(p_file_ptr==NULL)
				{
					printf("can't Open the CSV file - %s\n", csv_file_path);
					continue;
				}
				
				fprintf(p_file_ptr,"%s",p_text_data);
				fflush(p_file_ptr);
				
				fclose(p_file_ptr);
				
				free(p_text_data);
			}
			
			closedir(p_data_dir);
		}
	}

	return 0;
}

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
	
	if(dlms_dcu_config.dlms_dcu_info.data_format_type!=DCU_CSV_FILE_TYPE)
	{
		dbg_log(REPORT,"%-20s : DCU Data format typeis not CSV Type,No need toproceed.\n",fun_name);
		return -1;
	}
	
	time_t g_last_ls_read_time=time(NULL);
	
	while(1)
	{
		sleep(5);
		
		time_t curr_time=time(NULL);
		
		if((curr_time-g_last_ls_read_time)>REFF_FORM_CSV_TIME)
		{
			g_last_ls_read_time=curr_time;
			if(form_csv_file_format()!=0)
			{
				dbg_log(REPORT,"%-20s : Failed to generate csv file format\n",fun_name);
				continue;
			}
			else	
				dbg_log(INFORM,"%-20s : Successfully generate csv file format\n",fun_name);
		}
		else
		{
			dbg_log(INFORM,"%-20s : Time left to start csv file format : %ld sec\n",fun_name,REFF_FORM_CSV_TIME-(curr_time-g_last_ls_read_time));
		}
	}

	return 0;
}

/* End Of File */