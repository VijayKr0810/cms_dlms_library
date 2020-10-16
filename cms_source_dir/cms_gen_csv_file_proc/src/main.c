#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "gen_inc.h"
#include "nxjson.h"
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


#define INST_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_inst_obis_det.json"
#define LS_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_ls_obis_det.json"
#define DP_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_dp_obis_det.json"
#define BILL_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_bill_obis_det.json"
#define EVENT_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_event_obis_det.json"

#define INST_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_inst_obis_det.json"
#define LS_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_ls_obis_det.json"
#define DP_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_dp_obis_det.json"
#define BILL_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_bill_obis_det.json"
#define EVENT_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_event_obis_det.json"


#define REFF_FORM_CSV_TIME 	16*60
//#define REFF_FORM_CSV_TIME 	1

#define DCU_CSV_FILE_TYPE 	1

#define MAX_PARAM_NUM 		128 // Billing has max param number . so max is 128
#define MAX_FILE_OD_LINE 	290
typedef struct
{
	uint32_t 		tot_num_obis;
	char 			obis_val[MAX_PARAM_NUM][32];
}obis_val_det_t;

typedef struct
{
	uint32_t 		tot_num_line_obis;
	obis_val_det_t 	obis_val_det[MAX_FILE_OD_LINE];
	
}all_obis_val_info_t;
	
typedef struct
{
	char 	obis_code[32];
	char 	param_name[32];
	char 	param_val[32];
	
}obis_param_val_info_t;


/* Global */
char 					g_line[512],g_line_bkp[512];
char 					debug_file_name[64];
dlms_dcu_config_t 		dlms_dcu_config;

redisContext 			*p_redis_handler;
redisReply 				*p_redis_reply;

int32_t read_cfg_from_redis(void);
int32_t redis_init(char *hostname, uint16_t port);

int32_t convt_file_content_det(char *user_file_json, char *root_param_name, char *in_data_file_name,char *out_csv_file_path)
{
	static char fun_name[]="convt_file_content_det()";
	uint8_t 	g_obis_idx=0,g_tot_obis_det;
	int32_t 	g_tot_file_line_cnt;
	int16_t 	pidx_midx = 0;
	uint8_t 	file_num_param=0,idx=0,jdx=0,pos_idx=0;
	
	char 	*p_loc_data=NULL;
	char 	*p_loc_data1=NULL;
	char 	*p_loc_data2=NULL;
	int32_t file_fd=0;
	struct 	stat obis_st;
	

	if(stat(user_file_json,&obis_st)==-1)
	{
		printf("can't Find original file - %s\n", user_file_json);
		return -1;
	}
	
	//printf(">>File Size : %ld\n",obis_st.st_size);
	
	p_loc_data=malloc(obis_st.st_size+1);
	p_loc_data1=malloc(obis_st.st_size+4);
	p_loc_data2=malloc(obis_st.st_size+5);
	
	memset(p_loc_data,0,(obis_st.st_size+1));
	memset(p_loc_data1,0,(obis_st.st_size+4));
	memset(p_loc_data2,0,(obis_st.st_size+5));
	
	printf("opening user file json det : %s\n",user_file_json);
	
	file_fd=open(user_file_json, O_RDONLY);
	if (file_fd == -1) 
	{
		printf("can't open to read original file - %s\n", user_file_json);
		free(p_loc_data);
		free(p_loc_data1);
		free(p_loc_data2);
		return -1;
	}
	
	if (obis_st.st_size != read(file_fd, p_loc_data, obis_st.st_size)) 
	{
		printf("can't read original file - %s\n", user_file_json);
		close(file_fd);
		free(p_loc_data);
		free(p_loc_data1);
		free(p_loc_data2);
		return -1;
	}
	else
	{
		printf("tot bytes read from user json file : %ld\n",obis_st.st_size);
	}
	
	//printf("Strlen : %d\n",strlen(p_loc_data));
	
	//printf("\n%s\n",p_loc_data);
	
	sprintf(p_loc_data1,"%s",p_loc_data);
	
	close(file_fd);
	
	//printf("\n%s\n",p_loc_data1);
	
	const   nx_json *p_root_value = NULL;
	const   nx_json *p_gen_trav = NULL;
	const   nx_json *p_item_trav = NULL;
	const char *p_gen_ptr=NULL;
	
	strcpy(p_loc_data2, p_loc_data1);
	
	//printf("\n%s\n",p_loc_data2);
	
	p_root_value = nx_json_parse(p_loc_data1,0);

	if (p_root_value != NULL) 
	{
		p_gen_trav = nx_json_get(p_root_value,root_param_name);
		if(p_gen_trav != NULL)
		{
			p_gen_ptr = nx_json_get(p_gen_trav,"NumParams")->text_value;
			if(p_gen_ptr!=NULL)
			{
				file_num_param = atoi(p_gen_ptr);
			}
			else
			{
				printf("%s(): failed to get NumParams\n",root_param_name);
			}
		}
		else
		{
			printf("failed to get %s\n",root_param_name);
		}
	}
	
	nx_json_free(p_root_value);
	
	printf("total NUM_PARAM from User json File : %d\n",file_num_param);
	
	obis_param_val_info_t org_obis_det[file_num_param];
	
	obis_param_val_info_t user_obis_param_val[file_num_param];
	
	p_root_value = nx_json_parse(p_loc_data2,0);

	if (p_root_value != NULL) 
	{
		p_gen_trav = nx_json_get(p_root_value,root_param_name);
		if(p_gen_trav != NULL)
		{
			const nx_json *obis_list_trav=NULL;
			
			obis_list_trav = nx_json_get(p_gen_trav,"ObisCodeList");
			if(obis_list_trav != NULL)
			{
				for(idx=0; idx<file_num_param; idx++)
				{
					p_item_trav = nx_json_item(obis_list_trav, idx);
					if(p_item_trav!=NULL)
					{
						p_gen_ptr = nx_json_get(p_item_trav,"obis")->text_value;
						if(p_gen_ptr!=NULL)
						{
							strcpy(org_obis_det[idx].obis_code,p_gen_ptr);
						}
						else
						{
							printf("ObisCodeList(): failed to get Item obis for idx : %d\n",idx);
						}
						
						p_gen_ptr = nx_json_get(p_item_trav,"assign")->text_value;
						//printf("p_gen_ptr : %s\n",p_gen_ptr);
						if(p_gen_ptr!=NULL)
						{
							strcpy(org_obis_det[idx].param_name,p_gen_ptr);
						}
						else
						{
							printf("ObisCodeList(): failed to get Item assign for idx : %d\n",idx);
						}
					}
					else
					{
						printf("ObisCodeList(): failed to get Item for idx : %d\n",idx);
					}
				}
			}
			else
			{
				printf("failed to get ObisCodeList\n");
			}
		}
		else
		{
			printf("failed to get Params\n");
		}
	}
	else
	{
		printf("Improper Json format\n");
	}

	free(p_loc_data);
	free(p_loc_data1);
	free(p_loc_data2);
	
	char *token=NULL;
	FILE *p_file_ptr=NULL;
	
	printf("Opening Data file : %s\n",in_data_file_name);
	
	p_file_ptr = fopen(in_data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		printf("2 IN_DATA_FILE_NAME : %s, failed to open Error : %s\n",in_data_file_name,strerror(errno));
		return -1;
	}

	memset(g_line,0,sizeof(g_line));
	memset(g_line_bkp,0,sizeof(g_line_bkp));
	
	fgets(g_line,sizeof(g_line),p_file_ptr);
	strcpy(g_line_bkp,g_line);
	
	token = strtok(g_line_bkp,"\t");
	while(token!=NULL)
	{
		g_obis_idx++;
		token = strtok(NULL,"\t");
	}
	
	char 	g_obis_det[g_obis_idx][32];

	fclose(p_file_ptr);
	
	g_obis_idx=0;
	
	token = strtok(g_line,"\t");
	while(token!=NULL)
	{
		//printf(">>>Org data File OBIS : %s\n",token);
		if(strstr(token,"\n"))
		{
			char loc_token[32];
			memset(loc_token,0,sizeof(loc_token));
			strncpy(loc_token,token,strlen(token)-1);
			strcpy(g_obis_det[g_obis_idx++],loc_token);
		}
		else
		{
			strcpy(g_obis_det[g_obis_idx++],token);
		}
		token = strtok(NULL,"\t");
	}
	
	printf("total avl obis is in org file : %d\n",g_obis_idx);
	g_tot_obis_det=g_obis_idx;
	
	/* for(g_obis_idx=g_obis_idx; g_obis_idx; g_obis_idx--)
		printf("%s\n",g_obis_det[g_obis_idx]); */
	
	uint8_t pos_info_buff[g_tot_obis_det];
	
	for(idx=0; idx<g_tot_obis_det; idx++)
	{
		//printf(">>>>%s\n",g_obis_det[idx]);
		
		for(jdx=0; jdx<file_num_param; jdx++)
		{
			//printf(">>>FILE OBISLEN : %d, OrgLen : %d\n",strlen(g_obis_det[idx]),strlen(org_obis_det[jdx].obis_code));
			//printf("%s\t%s\t%s\n",g_obis_det[idx],org_obis_det[jdx].obis_code,org_obis_det[jdx].param_name);
			
			if(strstr(g_obis_det[idx],org_obis_det[jdx].obis_code)!=NULL)
			//if(strcmp(org_obis_det[jdx].obis_code,g_obis_det[idx])==0)
			{
				//printf("Idx : %d, Obis found in org obis list at pos : %d\n",idx,jdx);
				pos_info_buff[pos_idx++] = idx;
				break;
			}
		}
	}
	
	p_file_ptr = fopen(in_data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		printf("1 IN_DATA_FILE_NAME : %s, failed to open Error : %s\n",in_data_file_name,strerror(errno));
		return -1;
	}
	
	g_tot_file_line_cnt=0;
	fgets(g_line,sizeof(g_line),p_file_ptr);
	while(fgets(g_line,sizeof(g_line),p_file_ptr)!=NULL)
	{
		g_tot_file_line_cnt++;
	}
	
	//printf("%s\n",g_line);
	
	fclose(p_file_ptr);
	
	printf("total number of line in  org file : %d\n",g_tot_file_line_cnt);
	
	p_file_ptr = fopen(in_data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		printf("IN_DATA_FILE_NAME : %s, failed to open Error : %s\n",in_data_file_name,strerror(errno));
		return -1;
	}
	
	all_obis_val_info_t all_obis_val_info;

	all_obis_val_info.tot_num_line_obis=g_tot_file_line_cnt;
	uint32_t loc_idx=0;
	
	for(loc_idx=0;loc_idx<g_tot_file_line_cnt;loc_idx++)
	{
		all_obis_val_info.obis_val_det[loc_idx].tot_num_obis=pos_idx;
	}
	
	loc_idx=0,jdx=0,idx=0;
	int32_t line_cnt=0;
	
	printf("Getting line by line details from file\n");
	
	fgets(g_line,sizeof(g_line),p_file_ptr);
	
	while(fgets(g_line,sizeof(g_line),p_file_ptr)!=NULL)
	{
		//printf("%s\n",g_line);
		loc_idx=0;
		token = strtok(g_line,"\t");
		idx=0;
		
		printf("Storing data for LineCnt : %d\n",line_cnt);
		while(token!=NULL)
		{
			for(jdx=0; jdx<pos_idx;jdx++)
			{
				if(loc_idx==pos_info_buff[jdx])
				{
					if(strstr(token,"\n"))
					{
						char loc_token[32];
						memset(loc_token,0,sizeof(loc_token));
						strncpy(loc_token,token,strlen(token)-1);
						strcpy(all_obis_val_info.obis_val_det[line_cnt].obis_val[loc_idx],loc_token);
					}
					else
					{
						strcpy(all_obis_val_info.obis_val_det[line_cnt].obis_val[loc_idx],token);
					}
					
					//printf("Got Need info in list, LinCnt : %d, loc_idx : %d, Idx : %d token : %s\n",
					//line_cnt,loc_idx,idx,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
					//idx++;
					//break;
				}
			}
			loc_idx++;
			
			token = strtok(NULL,"\t");
		}
		line_cnt++;
	}
	
	printf("recv Total line by line details from file : %d\n",line_cnt);
	
	fclose(p_file_ptr);
	
	loc_idx=0;
	
	p_file_ptr = fopen(out_csv_file_path,"w");
	if(p_file_ptr==NULL)
	{
		printf("OutCsv,File : %s, failed to open Error : %s\n",out_csv_file_path,strerror(errno));
		return -1;
	}
	
	for(idx=0; idx<g_tot_obis_det; idx++)
	{
		for(jdx=0; jdx<file_num_param; jdx++)
		{
			if(strcmp(org_obis_det[jdx].obis_code, g_obis_det[idx])==0)
			{
				if(loc_idx==(pos_idx-1))
				{
					//sprintf(g_temp_str,"%c%s%c\n",DBL_QUOTES,org_obis_det[jdx].param_name,DBL_QUOTES);
					fprintf(p_file_ptr,"%s\n",org_obis_det[jdx].obis_code);
				}
				else
				{
					//printf("%s,",org_obis_det[jdx].param_name);
					//sprintf(g_temp_str,"%c%s%c,",DBL_QUOTES,org_obis_det[jdx].param_name,DBL_QUOTES);
					fprintf(p_file_ptr,"%s,",org_obis_det[jdx].obis_code);
				}
				loc_idx++;
				break;
			}
		}
	} 
	
	printf(" OBIS Code added into csv file\n");
	
	for(line_cnt=0; line_cnt<g_tot_file_line_cnt; line_cnt++)
	{
		printf("Total actual obis per line : %d For line : %d\n",all_obis_val_info.obis_val_det[line_cnt].tot_num_obis,line_cnt);
		for(idx=0; idx<all_obis_val_info.obis_val_det[line_cnt].tot_num_obis;idx++)
		{
			if(idx==all_obis_val_info.obis_val_det[line_cnt].tot_num_obis-1)
			{
				fprintf(p_file_ptr,"%s\n",all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
				fflush(p_file_ptr);
			}
			else
			{
				fprintf(p_file_ptr,"%s,",all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
				fflush(p_file_ptr);
			}
		}
	}
	
	fclose(p_file_ptr);

	return 0;
}

int32_t form_csv_file_format(void)
{
	static char 	fun_name[]="form_csv_file_format()";
	uint8_t 		idx,pidx;
	DIR 			*p_data_dir=NULL;
	struct dirent 	*p_dir_str=NULL;
	char 			curr_file_name[128],dir_data_path[128],csv_file_path[128];
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
			{
				//dbg_log(REPORT,"%-20s : PortIds : %d, MeterIdx : %d Not enable\n",fun_name,pidx,idx);
				continue;
			}
			
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
	}
	
	memset(dir_data_path,0,sizeof(dir_data_path));
	for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
	{
		for(idx=0; idx<dlms_dcu_config.dlms_channel_cfg[pidx].num_meter; idx++)
		{
			memset(dir_data_path,0,sizeof(dir_data_path));
			if(!dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].enable)
			{
				dbg_log(REPORT,"%-20s : Port-%d Met-%d Not enable\n",fun_name,pidx,idx);
				continue;
			}
			
			sprintf(dir_data_path,"%s/meter_id_%d",ROOT_DATA_DIR,pidx*MAX_NO_OF_METER_PER_PORT+idx+1);
			
			//dbg_log(REPORT,"%-20s : Port-%d Met-%d Opening Data dir : %s\n",fun_name,pidx,idx,dir_data_path);
			
			p_data_dir = NULL;
			p_data_dir = opendir(dir_data_path);
			if ( p_data_dir == NULL )
			{
				dbg_log(REPORT,"%-20s : Port-%d Met-%d Failed to opendir %s, Error : %s\n",
				fun_name,pidx,idx,dir_data_path,strerror(errno));
				
				//printf("Failed to opendir %s, Error : %s\n",dir_data_path,strerror(errno));
				continue;
			}
			
			while ( (p_dir_str = readdir(p_data_dir)) != NULL )
			{
				memset(curr_file_name,0,sizeof(curr_file_name));
				printf(">>> DirPath  : %s, Directory read  FileName : %s\n",dir_data_path,p_dir_str->d_name);
				
				if (( strcmp(p_dir_str->d_name,".") == 0 ) || ( strcmp(p_dir_str->d_name,"..") == 0 ) || ( strcmp(p_dir_str->d_name,"od") == 0 ))
				{
					continue;
				}
				
				sprintf(curr_file_name,"%s/%s",dir_data_path,p_dir_str->d_name);
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d FileName : %s\n",fun_name,pidx,idx,curr_file_name);
				
				memset(csv_file_path,0,sizeof(csv_file_path));
				sprintf(csv_file_path,"%s/%s/meter_id_%d/%s.csv",ROOT_DATA_DIR,
				"upstream/csv_proc",(pidx*MAX_NO_OF_METER_PER_PORT+idx+1),p_dir_str->d_name);
				
				if(strstr(p_dir_str->d_name,"dp")!=NULL)
				{
					convt_file_content_det(DP_OBIS_PARAMS_JSON,"MNParams",curr_file_name,csv_file_path);
				}
				else if(strstr(p_dir_str->d_name,"event")!=NULL)
				{
					convt_file_content_det(EVENT_OBIS_PARAMS_JSON,"EventParams",curr_file_name,csv_file_path);
				}
				else if(strstr(p_dir_str->d_name,"bill")!=NULL)
				{
					convt_file_content_det(BILL_OBIS_PARAMS_JSON,"BillParams",curr_file_name,csv_file_path);
				}
				else
				{
					convt_file_content_det(LS_OBIS_PARAMS_JSON,"LSParams",curr_file_name,csv_file_path);
				}
				
/* 				dbg_log(INFORM,"%-20s : Port-%d Met-%d 2DIR_DATA_PATH : %s\n",fun_name,pidx,idx,dir_data_path);
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d Opening CSV file : %s\n",
				fun_name,pidx,idx,csv_file_path);
				
				p_file_ptr=NULL;
				p_file_ptr=fopen(csv_file_path,"w");
				if(p_file_ptr==NULL)
				{
					dbg_log(INFORM,"%-20s : Port-%d Met-%d can't Open the CSV file : %s, Error : %s\n",fun_name,pidx,idx,csv_file_path,strerror(errno));
					
					free(p_text_data);
					//printf("can't Open the CSV file - %s\n", csv_file_path);
					continue;
				}
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d 3DIR_DATA_PATH : %s\n",fun_name,pidx,idx,dir_data_path);
				
				//fprintf(p_file_ptr,"%s",p_text_data);
				fwrite(p_text_data,strlen(p_text_data),1,p_file_ptr);
				fflush(p_file_ptr);
				
				fclose(p_file_ptr);
				
				free(p_text_data); */
			}
			
			closedir(p_data_dir);
		}
	}
	
	return 0;
}

int32_t form_csv_file_format11(void)
{	
	static char 	fun_name[]="form_csv_file_format()";
	uint8_t 		idx,pidx;
	DIR 			*p_data_dir=NULL;
	struct dirent 	*p_dir_str=NULL;
	char 			curr_file_name[128],dir_data_path[128],csv_file_path[128];
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
			{
				//dbg_log(REPORT,"%-20s : PortIds : %d, MeterIdx : %d Not enable\n",fun_name,pidx,idx);
				continue;
			}
			
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
	}
	
	memset(dir_data_path,0,sizeof(dir_data_path));
	for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
	{
		for(idx=0; idx<dlms_dcu_config.dlms_channel_cfg[pidx].num_meter; idx++)
		{
			memset(dir_data_path,0,sizeof(dir_data_path));
			if(!dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].enable)
			{
				dbg_log(REPORT,"%-20s : Port-%d Met-%d Not enable\n",fun_name,pidx,idx);
				continue;
			}
			
			sprintf(dir_data_path,"%s/meter_id_%d",ROOT_DATA_DIR,pidx*MAX_NO_OF_METER_PER_PORT+idx+1);
			
			dbg_log(REPORT,"%-20s : Port-%d Met-%d Opening Data dir : %s\n",fun_name,pidx,idx,dir_data_path);
			
			p_data_dir = NULL;
			p_data_dir = opendir(dir_data_path);
			if ( p_data_dir == NULL )
			{
				dbg_log(REPORT,"%-20s : Port-%d Met-%d Failed to opendir %s, Error : %s\n",
				fun_name,pidx,idx,dir_data_path,strerror(errno));
				
				//printf("Failed to opendir %s, Error : %s\n",dir_data_path,strerror(errno));
				continue;
			}
			
			while ( (p_dir_str = readdir(p_data_dir)) != NULL )
			{
				memset(curr_file_name,0,sizeof(curr_file_name));
				printf(">>> DirPath  : %s, Directory read  FileName : %s\n",dir_data_path,p_dir_str->d_name);
				
				if (( strcmp(p_dir_str->d_name,".") == 0 ) || ( strcmp(p_dir_str->d_name,"..") == 0 ) || ( strcmp(p_dir_str->d_name,"od") == 0 ))
				{
					continue;
				}
				
				sprintf(curr_file_name,"%s/%s",dir_data_path,p_dir_str->d_name);
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d FileName : %s\n",fun_name,pidx,idx,curr_file_name);
				
				//continue;
				//printf("Finding File : %s\n",file_name);
				
				if (stat(curr_file_name, &st)==-1) 
				{
					dbg_log(INFORM,"%-20s : Port-%d Met-%d can't find  FileName  : %s, Error : %s\n",
					fun_name,pidx,idx,curr_file_name,strerror(errno));
					//printf("can't find file : %s\n", file_name);
					continue;
				}
		
				file_fd = open(curr_file_name, O_RDONLY);
				if (file_fd == -1) 
				{
					dbg_log(INFORM,"%-20s : Port-%d Met-%d can't open to read original file : %s, Error : %s\n",fun_name,pidx,idx,curr_file_name,strerror(errno));
					
					//printf("can't open to read original file - %s\n", file_name);
					continue;
				}
		  
				// Read file
				p_text_data = NULL;
				p_text_data = malloc(st.st_size+1); // this is not going to be freed
				memset(p_text_data,0,st.st_size+1);
				
				printf("file size : %ld\n",st.st_size);
				
				if (st.st_size!=read(file_fd, p_text_data, st.st_size)) 
				{
					dbg_log(INFORM,"%-20s : Port-%d Met-%d can't read original file : %s, Error : %s\n",fun_name,pidx,idx,curr_file_name,strerror(errno));
					
					//printf("can't read original file - %s\n", file_name);
					close(file_fd);
					free(p_text_data);
					continue;
				}
				
				close(file_fd);
				
				// Add null char
				p_text_data[st.st_size]='\0';
				
				//printf("len p_text_data : %d\n",strlen(p_text_data));
				
				for(cnt_idx=0; cnt_idx<st.st_size+1; cnt_idx++)
				{
					if(p_text_data[cnt_idx]=='\t')
						p_text_data[cnt_idx]=',';
				}
				
				//printf("111 len p_text_data : %ld\n",strlen(p_text_data));
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d Updation success for file : %s\n",
				fun_name,pidx,idx,curr_file_name);
				
				//printf("Updation success for file : %s\n",p_dir_str->d_name);
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d 1DIR_DATA_PATH : %s\n",fun_name,pidx,idx,dir_data_path);
				
				// /usr/cms/data/DlmsData/upstream/csv_proc/meter_id_1/dp_09_2020.csv
				memset(csv_file_path,0,sizeof(csv_file_path));
				sprintf(csv_file_path,"%s/%s/meter_id_%d/%s.csv",ROOT_DATA_DIR,
				"upstream/csv_proc",(pidx*MAX_NO_OF_METER_PER_PORT+idx+1),p_dir_str->d_name);
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d 2DIR_DATA_PATH : %s\n",fun_name,pidx,idx,dir_data_path);
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d Opening CSV file : %s\n",
				fun_name,pidx,idx,csv_file_path);
				
				p_file_ptr=NULL;
				p_file_ptr=fopen(csv_file_path,"w");
				if(p_file_ptr==NULL)
				{
					dbg_log(INFORM,"%-20s : Port-%d Met-%d can't Open the CSV file : %s, Error : %s\n",fun_name,pidx,idx,csv_file_path,strerror(errno));
					
					free(p_text_data);
					//printf("can't Open the CSV file - %s\n", csv_file_path);
					continue;
				}
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d 3DIR_DATA_PATH : %s\n",fun_name,pidx,idx,dir_data_path);
				
				//fprintf(p_file_ptr,"%s",p_text_data);
				fwrite(p_text_data,strlen(p_text_data),1,p_file_ptr);
				fflush(p_file_ptr);
				
				fclose(p_file_ptr);
				
				free(p_text_data);
				
				dbg_log(INFORM,"%-20s : Port-%d Met-%d DIR_DATA_PATH : %s\n",fun_name,pidx,idx,dir_data_path);
				dbg_log(INFORM,"%-20s : Port-%d Met-%d InFileName : %s\n",fun_name,pidx,idx,curr_file_name);
				dbg_log(INFORM,"%-20s : Port-%d Met-%d Out CSV file : %s\n",fun_name,pidx,idx,csv_file_path);
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
	
	form_csv_file_format();
	
	printf("Total Time taken : %ld\n",time(NULL)-g_last_ls_read_time);
	
	while(1)
	{
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
			dbg_log(INFORM,"%-20s : Time left to start csv file format : %ld sec\n",
			fun_name,REFF_FORM_CSV_TIME-(curr_time-g_last_ls_read_time));
		}
		
		sleep(5);
	}

	return 0;
}

/* End Of File */