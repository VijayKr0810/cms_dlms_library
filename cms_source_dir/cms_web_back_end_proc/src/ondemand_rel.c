#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/home/iot-gateway/hiredis/hiredis.h"
#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
#include "dlms_api.h"
#include "dlms_fun.h"
#include "nxjson.h"
#include "web_back_end.h"

char 							g_line[512],g_line_bkp[512];
/* Extern */
extern redisContext 			*p_redis_handler;
extern redisReply 				*p_redis_reply;
extern dlms_dcu_config_t 		dlms_dcu_config;

char 							g_comm_status_buff[4][16]={"No","Yes","Not Configured"};
char 	g_meter_ser_num_info[MAX_NO_OF_SERIAL_PORT][MAX_NO_OF_METER_PER_PORT][32];

int16_t get_port_met_det(const char *dir_name)
{
	uint8_t pidx = 0, midx = 0;
	int16_t  pidx_midx = 0;
	int8_t *p_data = NULL;
					
	p_data = (int8_t *)&pidx_midx;
	
	//meter_id_00
	pidx=atoi(&dir_name[9]);
	pidx=(pidx-1)/MAX_NO_OF_METER_PER_PORT;
	
	midx=atoi(&dir_name[9]);
	midx=(midx-1)%MAX_NO_OF_METER_PER_PORT;
	
	p_data[1] = pidx;
	p_data[0] = midx;
	
	return pidx_midx;
}

int16_t find_ser_num(const char *met_ser_num)
{
	static char fun_name[]="find_ser_num()";
	char file_name[32];
	int mer_ser_file_ret = 0;
	uint8_t pidx = 0, midx = 0;
	FILE *met_ser_fp=NULL;
	
	for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
	{
		for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
		{
			p_redis_reply = redisCommand(p_redis_handler, "HMGET Port%dMet%dSerNum SER_NUM",pidx,midx);
			if(p_redis_reply!=NULL)
			{
				if(p_redis_reply->element[0]->str!=NULL)
				{
					strcpy(g_meter_ser_num_info[pidx][midx],p_redis_reply->element[0]->str);
				}
				else
				{
					//printf("HMGET Failed to get SER_NUM for PortId : %d, MeterId : %d\n",pidx,midx);
				}
			}
		}
	}
	
	for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
	{
		for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
		{
			if(strlen(g_meter_ser_num_info[pidx][midx])>0)
			{
				if ( strstr(g_meter_ser_num_info[pidx][midx],met_ser_num) != NULL )
				{
					int16_t pidx_midx = 0;
					int8_t *p_data = NULL;
					
					p_data = (int8_t *)&pidx_midx;
					p_data[1] = pidx;
					p_data[0] = midx;
					
					dbg_log(INFORM,"%-20s : Both meter ser num are same, Val : %X\n",fun_name,pidx_midx);
					return pidx_midx;
				}
			}
		}	
	}
	
	dbg_log(REPORT,"%-25s : Recv MeterSerNum : %s Not Found\n",fun_name,met_ser_num);
	
	return RET_NO_RESP;
}

int32_t send_od_det(uint32_t seq_num, const char *met_ser_num, char *user_file_json, char *root_param_name, char *data_file_name, char *type, char *data_type)
{
	uint8_t g_obis_idx,g_tot_obis_det;
	uint32_t g_tot_file_line_cnt;
	char cmd_status[32];
	static char fun_name[]="send_od_det()";
	int16_t 	pidx_midx = 0;
	uint8_t 	file_num_param=0,idx=0,jdx=0,pos_idx=0;
	
	char 	*p_loc_data=NULL;
	char 	*p_loc_data1=NULL;
	char 	*p_loc_data2=NULL;
	int32_t file_fd=0;
	struct 	stat obis_st;
	
	memset(cmd_status,0,sizeof(cmd_status));
	strcpy(cmd_status,"SUCCESS");
	
	if(stat(user_file_json,&obis_st)==-1)
	{
		printf("can't Find original file - %s\n", user_file_json);
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
	}
	
	//printf(">>File Size : %ld\n",obis_st.st_size);
	
	p_loc_data=malloc(obis_st.st_size+1);
	p_loc_data1=malloc(obis_st.st_size+4);
	p_loc_data2=malloc(obis_st.st_size+5);
	
	memset(p_loc_data,0,(obis_st.st_size+1));
	memset(p_loc_data1,0,(obis_st.st_size+4));
	memset(p_loc_data2,0,(obis_st.st_size+5));
	
	file_fd=open(user_file_json, O_RDONLY);
	if (file_fd == -1) 
	{
		printf("can't open to read original file - %s\n", user_file_json);
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
	}
	
	if (obis_st.st_size != read(file_fd, p_loc_data, obis_st.st_size)) 
	{
		printf("can't read original file - %s\n", user_file_json);
		close(file_fd);
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
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
			printf("p_gen_ptr : %s\n",p_gen_ptr);
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
	
	//printf("total NUM_PARAM from User json File : %d\n",file_num_param);
	
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
			printf("failed to get EventParams\n");
		}
	}
	else
	{
		printf("Improper Json format\n");
	}

	free(p_loc_data);
	free(p_loc_data1);
	free(p_loc_data2);
	nx_json_free(p_root_value);
	
	char *token=NULL;
	FILE *p_file_ptr=NULL;
	
	p_file_ptr = fopen(data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
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
		strcpy(g_obis_det[g_obis_idx++],token);
		token = strtok(NULL,"\t");
	}
	
	//printf("total avl obis is in org file : %d\n",g_obis_idx);
	g_tot_obis_det=g_obis_idx;
	
	/* for(g_obis_idx=g_obis_idx;g_obis_idx;g_obis_idx--)
		printf("%s\n",g_obis_det[g_obis_idx]); */
	
	uint8_t pos_info_buff[g_tot_obis_det];
	
	for(idx=0; idx<g_tot_obis_det; idx++)
	{
		for(jdx=0; jdx<file_num_param; jdx++)
		{
			//if(strstr(org_obis_det[jdx].obis_code,g_obis_det[idx])!=NULL)
			if(strcmp(org_obis_det[jdx].obis_code,g_obis_det[idx])==0)
			{
				//printf("Idx : %d, Obis found in org obis list at pos : %d\n",idx,jdx);
				//printf("%s\t%s\t%s\n",g_obis_det[idx],org_obis_det[jdx].obis_code,org_obis_det[jdx].param_name);
				pos_info_buff[pos_idx++] = idx;
				break;
			}
		}
	}
	
	//printf("total number of  obis match from org file : %d\n",pos_idx);
	//for(idx=0; idx<pos_idx; idx++)
		//printf("%d\t",pos_info_buff[idx]);
	//printf("\n");
	
	
	p_file_ptr = fopen(data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
	}
	
	g_tot_file_line_cnt=0;
	fgets(g_line,sizeof(g_line),p_file_ptr);
	while(fgets(g_line,sizeof(g_line),p_file_ptr)!=NULL)
	{
		g_tot_file_line_cnt++;
	}
	
	//printf("%s\n",g_line);
	
	fclose(p_file_ptr);
	
	//printf("total number of  obis line in  org event file : %d\n",g_tot_file_line_cnt);
	
	p_file_ptr = fopen(data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
	}
	
	typedef struct
	{
		uint32_t 		tot_num_obis;
		char 			obis_val[pos_idx][32];
	}obis_val_det_t;
	
	typedef struct
	{
		uint32_t 		tot_num_line_obis;
		obis_val_det_t 	obis_val_det[g_tot_file_line_cnt];
		
	}all_obis_val_info_t;
	
	all_obis_val_info_t all_obis_val_info;

	all_obis_val_info.tot_num_line_obis=g_tot_file_line_cnt;
	uint32_t loc_idx=0;
	
	for(loc_idx=0;loc_idx<g_tot_file_line_cnt;loc_idx++)
	{
		all_obis_val_info.obis_val_det[loc_idx].tot_num_obis=pos_idx;
	}
	
	loc_idx=0,jdx=0,idx=0;
	int32_t line_cnt=0;
	
	//printf("Getting line by line details from file\n");
	
	fgets(g_line,sizeof(g_line),p_file_ptr);
	
	while(fgets(g_line,sizeof(g_line),p_file_ptr)!=NULL)
	{
		//printf("%s\n",g_line);
		loc_idx=0;
		line_cnt++;
		token = strtok(g_line,"\t");
		idx=0;
		while(token!=NULL)
		{
			for(jdx=0; jdx<pos_idx;jdx++)
			{
				if(loc_idx==pos_info_buff[jdx])
				{
					char loc_token[32];
					if(strstr(token,"\n"))
					{
						memset(loc_token,0,sizeof(loc_token));
						strncpy(loc_token,token,strlen(token)-1);
						strcpy(all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],loc_token);
					}
					else
					{
						strcpy(all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],token);
					}
					
					//printf("Got Need info in list, LinCnt : %d, loc_idx : %d, Idx : %d token : %s\n",
					//line_cnt,loc_idx,idx,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
					idx++;
					break;
				}
			}
			loc_idx++;
			
			token = strtok(NULL,"\t");
		}
	}
	
	fclose(p_file_ptr);
	
	//EXIT:
	loc_idx=0;
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,type,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cOD_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,cmd_status,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n"); 
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cMET_SERNUM%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,met_ser_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_PARAM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,pos_idx,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_ENTRIES%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_tot_file_line_cnt,DBL_QUOTES);
	strcat(json_text,g_temp_str);
		
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cPARAM_LIST%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	
	for(idx=0; idx<g_tot_obis_det; idx++)
	{
		for(jdx=0; jdx<file_num_param; jdx++)
		{
			if(strcmp(org_obis_det[jdx].obis_code, g_obis_det[idx])==0)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				if(loc_idx==(pos_idx-1))
				{
					//printf("%s\n",org_obis_det[jdx].param_name);
					sprintf(g_temp_str,"%c%s%c\n",DBL_QUOTES,org_obis_det[jdx].param_name,DBL_QUOTES);
				}
				else
				{
					printf("%s,",org_obis_det[jdx].param_name);
					sprintf(g_temp_str,"%c%s%c,",DBL_QUOTES,org_obis_det[jdx].param_name,DBL_QUOTES);
				}
				strcat(json_text,g_temp_str);
				loc_idx++;
				break;
			}
		}
	} 
	
	strcat(json_text,"],\n"); // End of PARAM_LIST
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%c%s%c:\n",DBL_QUOTES,data_type,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	for(line_cnt=0; line_cnt<g_tot_file_line_cnt; line_cnt++)
	{
		if(!line_cnt)
			continue;
		
		strcat(json_text,"{");
		//printf("Total actual obis per line : %d For line : %d\n",all_obis_val_info.obis_val_det[line_cnt].tot_num_obis,line_cnt);
		for(idx=0; idx<all_obis_val_info.obis_val_det[line_cnt].tot_num_obis;idx++)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			if(idx==all_obis_val_info.obis_val_det[line_cnt].tot_num_obis-1)
			{
				//printf("%s\n",all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
				sprintf(g_temp_str,"%cV%d%c:%c%s%c",DBL_QUOTES,idx,DBL_QUOTES,DBL_QUOTES,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],DBL_QUOTES);
			}
			else
			{
				//printf("%s,",all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
				sprintf(g_temp_str,"%cV%d%c:%c%s%c,",DBL_QUOTES,idx,DBL_QUOTES,DBL_QUOTES,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],DBL_QUOTES);
			}
			strcat(json_text,g_temp_str);
		}
		
		if(line_cnt==g_tot_file_line_cnt-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}
	
	strcat(json_text,"]\n"); // end of EVENT_DATA
	
	strcat(json_text,"}\n"); // DATA
	
	strcat(json_text,"}\n"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_od_billing_det(uint32_t seq_num, const char *met_ser_num)
{
	char 		file_name[64];
	static char fun_name[]="send_od_midnight_det()";
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0,file_num_param=0,idx=0,jdx=0,pos_idx=0;
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	memset(file_name,0,sizeof(file_name));
	sprintf(file_name,"%s/meter_id_%d/billing",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	
	send_od_det(seq_num,met_ser_num,EVENT_OBIS_PARAMS_JSON,"BillParams",file_name,"OD_BILLING","BILL_DATA");
	
	return RET_SUCCESS;
}

int32_t send_od_midnight_det(uint32_t seq_num, const char *met_ser_num, uint8_t month, uint16_t year)
{
	char 		file_name[64];
	static char fun_name[]="send_od_midnight_det()";
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0,file_num_param=0,idx=0,jdx=0,pos_idx=0;
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	memset(file_name,0,sizeof(file_name));
	sprintf(file_name,"%s/meter_id_%d/dp_%02d_%04d",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx),month,year);
	
	send_od_det(seq_num,met_ser_num,EVENT_OBIS_PARAMS_JSON,"MNParams",file_name,"OD_MID_NIGHT","MN_DATA");
	
	return RET_SUCCESS;
}

int32_t send_od_event_det(uint32_t seq_num, const char *met_ser_num, uint8_t event_type)
{
	char file_name[64];
	static char fun_name[]="send_od_event_det()";
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0,file_num_param=0,idx=0,jdx=0,pos_idx=0;
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	memset(file_name,0,sizeof(file_name));
	sprintf(file_name,"%s/meter_id_%d/event_%d",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx),event_type);
	
	send_od_det(seq_num,met_ser_num,EVENT_OBIS_PARAMS_JSON,"EventParams",file_name,"OD_EVENT","EVENT_DATA");
	
	return RET_SUCCESS;
}

int32_t send_od_event_det11(uint32_t seq_num, const char *met_ser_num, uint8_t event_type)
{
	uint8_t g_obis_idx,g_tot_obis_det;
	uint32_t g_tot_file_line_cnt;

	static char fun_name[]="send_od_event_det()";
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0,file_num_param=0,idx=0,jdx=0,pos_idx=0;
	
	printf("Recv od event command for ser_num : %s, event_type : %d\n",met_ser_num,event_type);
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	char 	*p_loc_data=NULL;
	char 	*p_loc_data1=NULL;
	char 	*p_loc_data2=NULL;
	int32_t file_fd=0;
	struct 	stat obis_st;
	
	if(stat(EVENT_OBIS_PARAMS_JSON,&obis_st)==-1)
	{
		printf("can't Find original file - %s\n", EVENT_OBIS_PARAMS_JSON);
	}
	
	printf(">>File Size : %ld\n",obis_st.st_size);
	
	p_loc_data=malloc(obis_st.st_size+1);
	p_loc_data1=malloc(obis_st.st_size+4);
	p_loc_data2=malloc(obis_st.st_size+5);
	
	memset(p_loc_data,0,(obis_st.st_size+1));
	memset(p_loc_data1,0,(obis_st.st_size+4));
	memset(p_loc_data2,0,(obis_st.st_size+5));
	
	file_fd=open(EVENT_OBIS_PARAMS_JSON, O_RDONLY);
	if (file_fd == -1) 
	{
		printf("can't open to read original file - %s\n", EVENT_OBIS_PARAMS_JSON);
	}
	
	if (obis_st.st_size != read(file_fd, p_loc_data, obis_st.st_size)) 
	{
		printf("can't read original file - %s\n", EVENT_OBIS_PARAMS_JSON);
		close(file_fd);
	}
	else
	{
		printf("tot bytes read from user json file : %ld\n",obis_st.st_size);
	}
	
	printf("Strlen : %d\n",strlen(p_loc_data));
	
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
		p_gen_trav = nx_json_get(p_root_value,"EventParams");
		if(p_gen_trav != NULL)
		{
			p_gen_ptr = nx_json_get(p_gen_trav,"NumParams")->text_value;
			printf("p_gen_ptr : %s\n",p_gen_ptr);
			if(p_gen_ptr!=NULL)
			{
				file_num_param = atoi(p_gen_ptr);
			}
			else
			{
				printf("EventParams(): failed to get NumParams\n");
			}
		}
		else
		{
			printf("failed to get EventParams\n");
		}
	}
	
	nx_json_free(p_root_value);
	
	printf("total NUM_PARAM from User json File : %d\n",file_num_param);
	
	obis_param_val_info_t org_obis_det[file_num_param];
	
	obis_param_val_info_t user_obis_param_val[file_num_param];
	
	p_root_value = nx_json_parse(p_loc_data2,0);

	if (p_root_value != NULL) 
	{
		p_gen_trav = nx_json_get(p_root_value,"EventParams");
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
			printf("failed to get EventParams\n");
		}
	}
	else
	{
		printf("Improper Json format\n");
	}

	free(p_loc_data);
	free(p_loc_data1);
	free(p_loc_data2);
	nx_json_free(p_root_value);
	
	char file_name[64], *token=NULL;
	FILE *p_file_ptr=NULL;
	
	memset(file_name,0,sizeof(file_name));
	sprintf(file_name,"%s/meter_id_%d/event_%d",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx),event_type);
	
	p_file_ptr = fopen(file_name,"r");
	if(p_file_ptr==NULL)
		return 0;
	
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
		strcpy(g_obis_det[g_obis_idx++],token);
		token = strtok(NULL,"\t");
	}
	
	printf("total avl obis is in org file : %d\n",g_obis_idx);
	g_tot_obis_det=g_obis_idx;
	
	/* for(g_obis_idx=g_obis_idx;g_obis_idx;g_obis_idx--)
		printf("%s\n",g_obis_det[g_obis_idx]); */
	
	uint8_t pos_info_buff[g_tot_obis_det];
	
	for(idx=0; idx<g_tot_obis_det; idx++)
	{
		for(jdx=0; jdx<file_num_param; jdx++)
		{
			//if(strstr(org_obis_det[jdx].obis_code,g_obis_det[idx])!=NULL)
			if(strcmp(org_obis_det[jdx].obis_code,g_obis_det[idx])==0)
			{
				printf("Idx : %d, Obis found in org obis list at pos : %d\n",idx,jdx);
				printf("%s\t%s\t%s\n",g_obis_det[idx],org_obis_det[jdx].obis_code,org_obis_det[jdx].param_name);
				pos_info_buff[pos_idx++] = idx;
				break;
			}
		}
	}
	
	printf("total number of  obis match from org file : %d\n",pos_idx);
	for(idx=0; idx<pos_idx; idx++)
		printf("%d\t",pos_info_buff[idx]);
	printf("\n");
	
	
	p_file_ptr = fopen(file_name,"r");
	if(p_file_ptr==NULL)
		return 0;
	
	g_tot_file_line_cnt=0;
	while(fgets(g_line,sizeof(g_line),p_file_ptr)!=NULL)
	{
		g_tot_file_line_cnt++;
	}
	
	//printf("%s\n",g_line);
	
	fclose(p_file_ptr);
	
	printf("total number of  obis line in  org event file : %d\n",g_tot_file_line_cnt);
	
	p_file_ptr = fopen(file_name,"r");
	if(p_file_ptr==NULL)
		return 0;
	
	typedef struct
	{
		uint32_t 		tot_num_obis;
		char 			obis_val[pos_idx][32];
	}obis_val_det_t;
	
	typedef struct
	{
		uint32_t 		tot_num_line_obis;
		obis_val_det_t 	obis_val_det[g_tot_file_line_cnt];
		
	}all_obis_val_info_t;
	
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
		line_cnt++;
		token = strtok(g_line,"\t");
		idx=0;
		while(token!=NULL)
		{
			for(jdx=0; jdx<pos_idx;jdx++)
			{
				if(loc_idx==pos_info_buff[jdx])
				{
					char loc_token[32];
					if(strstr(token,"\n"))
					{
						memset(loc_token,0,sizeof(loc_token));
						strncpy(loc_token,token,strlen(token)-1);
						strcpy(all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],loc_token);
					}
					else
					{
						strcpy(all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],token);
					}
					
					//printf("Got Need info in list, LinCnt : %d, loc_idx : %d, Idx : %d token : %s\n",
					//line_cnt,loc_idx,idx,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
					idx++;
					break;
				}
			}
			loc_idx++;
			
			token = strtok(NULL,"\t");
		}
	}
	
	fclose(p_file_ptr);
	
	loc_idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cOD_EVENT%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cOD_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n"); 
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cMET_SERNUM%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,met_ser_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_PARAM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,pos_idx,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_ENTRIES%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_tot_file_line_cnt-1,DBL_QUOTES);
	strcat(json_text,g_temp_str);
		
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cPARAM_LIST%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	
	for(idx=0; idx<g_tot_obis_det; idx++)
	{
		for(jdx=0; jdx<file_num_param; jdx++)
		{
			if(strcmp(org_obis_det[jdx].obis_code, g_obis_det[idx])==0)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				if(loc_idx==(pos_idx-1))
				{
					//printf("%s\n",org_obis_det[jdx].param_name);
					sprintf(g_temp_str,"%c%s%c\n",DBL_QUOTES,org_obis_det[jdx].param_name,DBL_QUOTES);
				}
				else
				{
					printf("%s,",org_obis_det[jdx].param_name);
					sprintf(g_temp_str,"%c%s%c,",DBL_QUOTES,org_obis_det[jdx].param_name,DBL_QUOTES);
				}
				strcat(json_text,g_temp_str);
				loc_idx++;
				break;
			}
		}
	} 
	
	strcat(json_text,"],\n"); // End of PARAM_LIST
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cEVENT_DATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	for(line_cnt=0; line_cnt<g_tot_file_line_cnt; line_cnt++)
	{
		if(!line_cnt)
			continue;
		
		strcat(json_text,"{");
		//printf("Total actual obis per line : %d For line : %d\n",all_obis_val_info.obis_val_det[line_cnt].tot_num_obis,line_cnt);
		for(idx=0; idx<all_obis_val_info.obis_val_det[line_cnt].tot_num_obis;idx++)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			if(idx==all_obis_val_info.obis_val_det[line_cnt].tot_num_obis-1)
			{
				//printf("%s\n",all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
				sprintf(g_temp_str,"%cV%d%c:%c%s%c",DBL_QUOTES,idx,DBL_QUOTES,DBL_QUOTES,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],DBL_QUOTES);
			}
			else
			{
				//printf("%s,",all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
				sprintf(g_temp_str,"%cV%d%c:%c%s%c,",DBL_QUOTES,idx,DBL_QUOTES,DBL_QUOTES,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],DBL_QUOTES);
			}
			strcat(json_text,g_temp_str);
		}
		
		if(line_cnt==g_tot_file_line_cnt-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}
	
	strcat(json_text,"]\n"); // end of EVENT_DATA
	
	strcat(json_text,"}\n"); // DATA
	
	strcat(json_text,"}\n"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

void send_od_event_det1(uint32_t seq_num, const char *met_ser_num, uint8_t event_type)
{
	static char fun_name[]="send_od_event_det()";
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0,file_num_param=0,idx=0,jdx=0,pos_idx=0;
	
	printf("Recv od event command for ser_num : %s, event_type : %d\n",met_ser_num,event_type);
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	char 	*p_loc_data=NULL;
	char 	*p_loc_data1=NULL;
	char 	*p_loc_data2=NULL;
	int32_t file_fd=0;
	struct 	stat obis_st;
	
	if(stat(EVENT_OBIS_PARAMS_JSON,&obis_st)==-1)
	{
		printf("can't Find original file - %s\n", EVENT_OBIS_PARAMS_JSON);
	}
	
	printf(">>File Size : %ld\n",obis_st.st_size);
	
	p_loc_data=malloc(obis_st.st_size+1);
	p_loc_data1=malloc(obis_st.st_size+4);
	p_loc_data2=malloc(obis_st.st_size+5);
	
	memset(p_loc_data,0,(obis_st.st_size+1));
	memset(p_loc_data1,0,(obis_st.st_size+4));
	memset(p_loc_data2,0,(obis_st.st_size+5));
	
	file_fd=open(EVENT_OBIS_PARAMS_JSON, O_RDONLY);
	if (file_fd == -1) 
	{
		printf("can't open to read original file - %s\n", EVENT_OBIS_PARAMS_JSON);
	}
	
	if (obis_st.st_size != read(file_fd, p_loc_data, obis_st.st_size)) 
	{
		printf("can't read original file - %s\n", EVENT_OBIS_PARAMS_JSON);
		close(file_fd);
	}
	else
	{
		printf("tot bytes read from user json file : %ld\n",obis_st.st_size);
	}
	
	printf("Strlen : %d\n",strlen(p_loc_data));
	
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
		p_gen_trav = nx_json_get(p_root_value,"EventParams");
		if(p_gen_trav != NULL)
		{
			p_gen_ptr = nx_json_get(p_gen_trav,"NumParams")->text_value;
			printf("p_gen_ptr : %s\n",p_gen_ptr);
			if(p_gen_ptr!=NULL)
			{
				file_num_param = atoi(p_gen_ptr);
			}
			else
			{
				printf("EventParams(): failed to get NumParams\n");
			}
		}
		else
		{
			printf("failed to get EventParams\n");
		}
	}
	
	nx_json_free(p_root_value);
	
	printf("total NUM_PARAM from User json File : %d\n",file_num_param);
	
	obis_param_val_info_t user_obis_param_val[file_num_param];
	
	p_root_value = nx_json_parse(p_loc_data2,0);

	if (p_root_value != NULL) 
	{
		p_gen_trav = nx_json_get(p_root_value,"EventParams");
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
							strcpy(user_obis_param_val[idx].obis_code,p_gen_ptr);
						}
						else
						{
							printf("ObisCodeList(): failed to get Item obis for idx : %d\n",idx);
						}
						
						p_gen_ptr = nx_json_get(p_item_trav,"assign")->text_value;
						if(p_gen_ptr!=NULL)
						{
							strcpy(user_obis_param_val[idx].param_name,p_gen_ptr);
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
			printf("failed to get EventParams\n");
		}
	}
	else
	{
		printf("Improper Json format\n");
	}

	free(p_loc_data);
	free(p_loc_data1);
	free(p_loc_data2);
	nx_json_free(p_root_value);

	uint8_t status = 1;
	
	FILE *p_file_ptr = NULL;
	char 	data_file_name[64];
	uint32_t tot_line_cnt=0;
	
	memset(data_file_name,0,sizeof(data_file_name));
	
	sprintf(data_file_name,"%s/meter_id_%d/event_%d",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx),event_type);
	
	p_file_ptr = fopen(data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		printf("Can't open event data file : %s, error : %s\n",data_file_name,strerror(errno));
	}
	else
	{
		memset(g_line,0,sizeof(g_line));
		fgets(g_line,sizeof(g_line),p_file_ptr);
		
	}
	
	uint8_t g_obis_idx=0;
	
	char *token=NULL;
	
	memset(g_line_bkp,0,sizeof(g_line_bkp));
	strcpy(g_line_bkp,g_line);
	
	token = strtok(g_line,"\t");
	while(token!=NULL)
	{
		g_obis_idx++;
		token = strtok(NULL,"\t");
	}
	
	printf("Total params avaible : %d, in event type %d file\n",g_obis_idx,event_type);
	
	obis_param_val_info_t event_obis_param_val[g_obis_idx];
	
	fseek(p_file_ptr,0,SEEK_SET);
	
	while(fgets(g_line,sizeof(g_line),p_file_ptr)!=NULL)
	{
		tot_line_cnt++;
	}
	
	fclose(p_file_ptr);
	
	printf("Total Line avaible : %d, in event type %d file\n",tot_line_cnt,event_type);
	
	g_obis_idx=0;
	token = strtok(g_line,"\t");
	while(token!=NULL)
	{
		strcpy(event_obis_param_val[g_obis_idx++].obis_code,token);
		token = strtok(NULL,"\t");
	}
	
	uint8_t max_obis_num=0;
	
	if(file_num_param>g_obis_idx)
		max_obis_num = file_num_param;
	else
		max_obis_num = g_obis_idx;
	
	uint8_t pos_info_buff[max_obis_num];
	
	for(idx=0; idx<file_num_param; idx++)
	{
		//printf("%s\t%s\n",user_obis_param_val[idx].obis_code, event_obis_param_val[0].obis_code);
		
		for(jdx=0; jdx<g_obis_idx; jdx++)
		{
			if(strcmp(user_obis_param_val[idx].obis_code, event_obis_param_val[jdx].obis_code)==0)
			{
				printf("%s\t%s\n",user_obis_param_val[idx].obis_code, event_obis_param_val[jdx].obis_code);
				pos_info_buff[pos_idx++] = idx;
				break;
			}
		}
	}
	
	uint32_t loc_idx=0;
	
	loc_idx=0,jdx=0,idx=0;
	int32_t line_cnt=0;
	
	p_file_ptr = fopen(data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		printf("Can't open event data file : %s, error : %s\n",data_file_name,strerror(errno));
	}
	
	while(fgets(g_line,sizeof(g_line),p_file_ptr)!=NULL)
	{
		//printf("%s\n",g_line);
		loc_idx=0;
		line_cnt++;
		
		token = strtok(g_line,"\t");
		idx=0;
		while(token!=NULL)
		{
			for(jdx=0; jdx<pos_idx;jdx++)
			{
				if(loc_idx==pos_info_buff[jdx])
				{
					if(line_cnt==1)
					{
						if(jdx==pos_idx-1)
							printf("%s",user_obis_param_val[jdx].param_name);
						else
							printf("%s,",user_obis_param_val[jdx].param_name);
					}
					else
					{
						char loc_token[32];
						if(strstr(token,"\n"))
						{
							memset(loc_token,0,sizeof(loc_token));
							strncpy(loc_token,token,strlen(token)-1);
							
							if(jdx==pos_idx-1)
								printf("%s",loc_token);
							else
								printf("%s,",loc_token);
						}
						else
						{
							if(jdx==pos_idx-1)
								printf("%s",token);
							else
								printf("%s,",token);
						}
						
					}
					//printf("Got Need info in list, LinCnt : %d, loc_idx : %d, Idx : %d token : %s\n",line_cnt,loc_idx,idx,token);
					idx++;
					
					break;
				}
			}
			loc_idx++;
			
			token = strtok(NULL,"\t");
		}
	}
	
	fclose(p_file_ptr);

	return ;
}

void send_od_ls_range_det(uint32_t seq_num, const char *met_ser_num, date_time_t st_date_time, date_time_t end_date_time)
{
	static char fun_name[]="send_od_ls_range_det()";
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0;
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dOdLsCmd NeedToRead %d",pidx,midx,1);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dOdLsCmd Day %d Mon %d Year %d Hour %d Min %d",
	pidx,midx,st_date_time.day,st_date_time.month,st_date_time.year,st_date_time.hour,st_date_time.minute);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dOdLsCmd Day2 %d Mon2 %d Year2 %d Hour2 %d Min2 %d",
	pidx,midx,end_date_time.day,end_date_time.month,end_date_time.year,end_date_time.hour,end_date_time.minute);
	freeReplyObject(p_redis_reply);
}

void send_od_inst_det(uint32_t seq_num, const char *met_ser_num)
{
	uint8_t num_params=0,file_num_param=0,num_param;
	uint8_t idx=0,jdx=0;
	char 	*gen_ptr=NULL;
	char 	key_name[32];
	
	uint8_t 	pidx=0,midx=0;
	uint16_t 	pidx_midx=0;
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;	
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cOD_INST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cOD_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	memset(key_name,0,sizeof(key_name));
	sprintf(key_name,"Port%dMet%d%s",pidx,midx,INST_INFO_KEY);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMGET %s NUM_PARAM",key_name);
	if(p_redis_reply!=NULL)
	{
		if(p_redis_reply->element[0]->str!=NULL)
		{
			num_params=atoi(p_redis_reply->element[0]->str);
		}
		else
		{
			printf("HMGET Failed to get NUM_PARAM\n");
		}
	}
	
	freeReplyObject(p_redis_reply);
	
	printf("total NUM_PARAM from meter : %d\n",num_params);
	
	obis_param_val_info_t met_obis_param_val[num_params];
	for(idx=0; idx<num_params; idx++)
	{
		memset(key_name,0,sizeof(key_name));
		sprintf(key_name,"Port%dMet%d%s",pidx,midx,INST_INFO_KEY);
	
		p_redis_reply = redisCommand(p_redis_handler, "HMGET %s Obis_%d Value_%d",key_name,idx+1,idx+1);
		if(p_redis_reply!=NULL)
		{
			gen_ptr = p_redis_reply->element[0]->str;
			if(gen_ptr!=NULL)
			{
				strcpy(met_obis_param_val[idx].obis_code,gen_ptr);
			}
			else
			{
				printf("HMGET Failed to get param obis for idx : %d\n",idx);
			}
			
			gen_ptr = p_redis_reply->element[1]->str;
			if(gen_ptr!=NULL)
			{
				strcpy(met_obis_param_val[idx].param_val,gen_ptr);
			}
			else
			{
				printf("HMGET Failed to get param value for idx : %d\n",idx);
			}
			
			freeReplyObject(p_redis_reply);
		}
	}
	
	char 	*p_loc_data=NULL;
	char 	*p_loc_data1=NULL;
	char 	*p_loc_data2=NULL;
	int32_t file_fd=0;
	struct stat obis_st;
	
	if(stat(INST_OBIS_PARAMS_JSON,&obis_st)==-1)
	{
		printf("can't Find original file - %s\n", INST_OBIS_PARAMS_JSON);
	}
	
	printf(">>File Size : %ld\n",obis_st.st_size);
	
	p_loc_data=malloc(obis_st.st_size+1);
	p_loc_data1=malloc(obis_st.st_size+4);
	p_loc_data2=malloc(obis_st.st_size+5);
	
	memset(p_loc_data,0,(obis_st.st_size+1));
	memset(p_loc_data1,0,(obis_st.st_size+4));
	memset(p_loc_data2,0,(obis_st.st_size+5));
	
	file_fd=open(INST_OBIS_PARAMS_JSON, O_RDONLY);
	if (file_fd == -1) 
	{
		printf("can't open to read original file - %s\n", INST_OBIS_PARAMS_JSON);
	}
	
	if (obis_st.st_size != read(file_fd, p_loc_data, obis_st.st_size)) 
	{
		printf("can't read original file - %s\n", INST_OBIS_PARAMS_JSON);
		close(file_fd);
	}
	else
	{
		printf("tot bytes read from user json file : %ld\n",obis_st.st_size);
	}
	
	printf("Strlen : %d\n",strlen(p_loc_data));
	
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
		p_gen_trav = nx_json_get(p_root_value,"InstParams");
		if(p_gen_trav != NULL)
		{
			p_gen_ptr = nx_json_get(p_gen_trav,"NumParams")->text_value;
			printf("p_gen_ptr : %s\n",p_gen_ptr);
			if(p_gen_ptr!=NULL)
			{
				file_num_param = atoi(p_gen_ptr);
			}
			else
			{
				printf("InstParams(): failed to get NumParams\n");
			}
		}
		else
		{
			printf("failed to get InstParams\n");
		}
	}
	
	nx_json_free(p_root_value);
	
	printf("total NUM_PARAM from File : %d\n",file_num_param);
	
	obis_param_val_info_t user_obis_param_val[file_num_param];
	
	p_root_value = nx_json_parse(p_loc_data2,0);

	if (p_root_value != NULL) 
	{
		p_gen_trav = nx_json_get(p_root_value,"InstParams");
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
							strcpy(user_obis_param_val[idx].obis_code,p_gen_ptr);
						}
						else
						{
							printf("ObisCodeList(): failed to get Item obis for idx : %d\n",idx);
						}
						
						p_gen_ptr = nx_json_get(p_item_trav,"assign")->text_value;
						if(p_gen_ptr!=NULL)
						{
							strcpy(user_obis_param_val[idx].param_name,p_gen_ptr);
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
			printf("failed to get InstParams\n");
		}
	}
	else
	{
		printf("Improper Json format\n");
	}

	free(p_loc_data);
	free(p_loc_data1);
	free(p_loc_data2);
	nx_json_free(p_root_value);

	uint8_t status = 0;
	
	p_redis_reply = redisCommand(p_redis_handler, "HMGET SerPort%dMet%dStatus VALUE",pidx,midx);
	if(p_redis_reply!=NULL)
	{
		if(p_redis_reply->element[0]->str!=NULL)
		{
			status=atoi(p_redis_reply->element[0]->str);
		}
	}
				
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cMET_SERNUM%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,met_ser_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCOMM_STATUS%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_comm_status_buff[status],DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_PARAM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,file_num_param,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cINST_PARAM%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	
	for(idx=0; idx<file_num_param; idx++)
	{
		strcat(json_text,"{\n");
		for(jdx=0; jdx<num_params; jdx++)
		{
			if(strcmp(user_obis_param_val[idx].obis_code, met_obis_param_val[jdx].obis_code)==0)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cparam%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,user_obis_param_val[idx].param_name,DBL_QUOTES);
				strcat(json_text,g_temp_str);
			
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cval%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,met_obis_param_val[jdx].param_val,DBL_QUOTES);
				strcat(json_text,g_temp_str);
				
				break;
			}
		}
		
		if(jdx==num_params)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cparam%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,user_obis_param_val[idx].param_name,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cval%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"NA",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}

		if(idx==file_num_param-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}

	strcat(json_text,"]\n");
	
	strcat(json_text,"}\n"); // DATA
	
	strcat(json_text,"}\n"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return ;
}

void fill_user_obis_det(char *file_name, char *param_type)
{
	char *p_loc_data=NULL;
	struct stat obis_st;
	int32_t file_fd=0;
	
	if(stat(file_name,&obis_st)==-1)
	{
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%c%s%c:\n",DBL_QUOTES,param_type,DBL_QUOTES);
		strcat(json_text,g_temp_str);
		strcat(json_text,"{\n");
		
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cNumParams%c:%c0%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
		strcat(json_text,g_temp_str);
		
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cObisCodeList%c:\n",DBL_QUOTES,DBL_QUOTES);
		strcat(json_text,g_temp_str);
		strcat(json_text,"[\n");
		
		strcat(json_text,"]\n");
		
		strcat(json_text,"}\n");
	}
	else
	{
		p_loc_data=malloc(obis_st.st_size+1);
		memset(p_loc_data,0,obis_st.st_size+1);
		file_fd=open(file_name,O_RDONLY);
		
		if (file_fd == -1) 
		{
			printf("can't open to read original file - %s\n", file_name);
		}
		
		if (obis_st.st_size!=read(file_fd, p_loc_data, obis_st.st_size)) 
		{
			printf("can't read original file - %s\n", file_name);
			close(file_fd);
		}
		
		strcat(json_text,p_loc_data);
		close(file_fd);
		free(p_loc_data);
	}
}

int32_t send_met_ser_num_det(int32_t seq_num)
{
	static char fun_name[]="find_ser_num()";
	char file_name[32];
	int mer_ser_file_ret = 0;
	uint8_t pidx = 0, midx = 0;
	uint8_t tot_num_ser_num = 0, idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"GET_METER_SER_LIST",DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cOD_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
	{
		for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
		{
			p_redis_reply = redisCommand(p_redis_handler, "HMGET Port%dMet%dSerNum SER_NUM",pidx,midx);
			if(p_redis_reply!=NULL)
			{
				if(p_redis_reply->element[0]->str!=NULL)
				{
					tot_num_ser_num++;
				}
				else
				{
					//printf("HMGET Failed to get SER_NUM for PortId : %d, MeterId : %d\n",pidx,midx);
				}
			}
		}
	}
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_MET%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,tot_num_ser_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cMET_LIST%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	
	for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
	{
		for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
		{
			p_redis_reply = redisCommand(p_redis_handler, "HMGET Port%dMet%dSerNum SER_NUM",pidx,midx);
			if(p_redis_reply!=NULL)
			{
				if(p_redis_reply->element[0]->str!=NULL)
				{
					memset(g_temp_str,0,sizeof(g_temp_str));
			
					if(idx<tot_num_ser_num-1)
						sprintf(g_temp_str,"%c%s%c,",DBL_QUOTES,p_redis_reply->element[0]->str,DBL_QUOTES);
					else
						sprintf(g_temp_str,"%c%s%c",DBL_QUOTES,p_redis_reply->element[0]->str,DBL_QUOTES);
					
					strcat(json_text,g_temp_str);
					
					idx++;
				}
				else
				{
					//printf("HMGET Failed to get SER_NUM for PortId : %d, MeterId : %d\n",pidx,midx);
				}
			}
		}
	}
	
	strcat(json_text,"]\n");
	
	strcat(json_text,"}\n"); // End of Data
	
	strcat(json_text,"}\n"); // End of Json

	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_file_content_det(uint32_t seq_num, const char *met_ser_num, char *user_file_json, char *root_param_name, char *data_file_name,const char *dir_name, const char *file_name, const char *view_type, char *type)
{
	static char fun_name[]="send_file_content_det()";
	uint8_t 	g_obis_idx,g_tot_obis_det;
	uint32_t 	g_tot_file_line_cnt;
	char 		cmd_status[32];
	int16_t 	pidx_midx = 0;
	uint8_t 	file_num_param=0,idx=0,jdx=0,pos_idx=0;
	
	char 	*p_loc_data=NULL;
	char 	*p_loc_data1=NULL;
	char 	*p_loc_data2=NULL;
	int32_t file_fd=0;
	struct 	stat obis_st;
	
	memset(cmd_status,0,sizeof(cmd_status));
	strcpy(cmd_status,"SUCCESS");
	
	if(stat(user_file_json,&obis_st)==-1)
	{
		printf("can't Find original file - %s\n", user_file_json);
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
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
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
	}
	
	if (obis_st.st_size != read(file_fd, p_loc_data, obis_st.st_size)) 
	{
		printf("can't read original file - %s\n", user_file_json);
		close(file_fd);
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
	
	//printf("total NUM_PARAM from User json File : %d\n",file_num_param);
	
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
			printf("failed to get EventParams\n");
		}
	}
	else
	{
		printf("Improper Json format\n");
	}

	free(p_loc_data);
	free(p_loc_data1);
	free(p_loc_data2);
	nx_json_free(p_root_value);
	
	char *token=NULL;
	FILE *p_file_ptr=NULL;
	
	printf("Opening Data file : %s\n",data_file_name);
	
	p_file_ptr = fopen(data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
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
		strcpy(g_obis_det[g_obis_idx++],token);
		token = strtok(NULL,"\t");
	}
	
	//printf("total avl obis is in org file : %d\n",g_obis_idx);
	g_tot_obis_det=g_obis_idx;
	
	/* for(g_obis_idx=g_obis_idx;g_obis_idx;g_obis_idx--)
		printf("%s\n",g_obis_det[g_obis_idx]); */
	
	uint8_t pos_info_buff[g_tot_obis_det];
	
	for(idx=0; idx<g_tot_obis_det; idx++)
	{
		for(jdx=0; jdx<file_num_param; jdx++)
		{
			//if(strstr(org_obis_det[jdx].obis_code,g_obis_det[idx])!=NULL)
			if(strcmp(org_obis_det[jdx].obis_code,g_obis_det[idx])==0)
			{
				//printf("Idx : %d, Obis found in org obis list at pos : %d\n",idx,jdx);
				//printf("%s\t%s\t%s\n",g_obis_det[idx],org_obis_det[jdx].obis_code,org_obis_det[jdx].param_name);
				pos_info_buff[pos_idx++] = idx;
				break;
			}
		}
	}
	
	p_file_ptr = fopen(data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		strcpy(cmd_status,"FAILURE");
		//goto EXIT;
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
	
	p_file_ptr = fopen(data_file_name,"r");
	if(p_file_ptr==NULL)
	{
		strcpy(cmd_status,"FAILURE");
	}
	
	typedef struct
	{
		uint32_t 		tot_num_obis;
		char 			obis_val[pos_idx][32];
	}obis_val_det_t;
	
	typedef struct
	{
		uint32_t 		tot_num_line_obis;
		obis_val_det_t 	obis_val_det[g_tot_file_line_cnt];
		
	}all_obis_val_info_t;
	
	all_obis_val_info_t all_obis_val_info;

	all_obis_val_info.tot_num_line_obis=g_tot_file_line_cnt;
	uint32_t loc_idx=0;
	
	for(loc_idx=0;loc_idx<g_tot_file_line_cnt;loc_idx++)
	{
		all_obis_val_info.obis_val_det[loc_idx].tot_num_obis=pos_idx;
	}
	
	loc_idx=0,jdx=0,idx=0;
	int32_t line_cnt=0;
	
	//printf("Getting line by line details from file\n");
	
	fgets(g_line,sizeof(g_line),p_file_ptr);
	
	while(fgets(g_line,sizeof(g_line),p_file_ptr)!=NULL)
	{
		//printf("%s\n",g_line);
		loc_idx=0;
		line_cnt++;
		token = strtok(g_line,"\t");
		idx=0;
		while(token!=NULL)
		{
			for(jdx=0; jdx<pos_idx;jdx++)
			{
				if(loc_idx==pos_info_buff[jdx])
				{
					char loc_token[32];
					if(strstr(token,"\n"))
					{
						memset(loc_token,0,sizeof(loc_token));
						strncpy(loc_token,token,strlen(token)-1);
						strcpy(all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],loc_token);
					}
					else
					{
						strcpy(all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],token);
					}
					
					//printf("Got Need info in list, LinCnt : %d, loc_idx : %d, Idx : %d token : %s\n",
					//line_cnt,loc_idx,idx,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
					idx++;
					break;
				}
			}
			loc_idx++;
			
			token = strtok(NULL,"\t");
		}
	}
	
	fclose(p_file_ptr);
	
	loc_idx=0;
	
	//EXIT : 
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,type,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cOD_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,cmd_status,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n"); 
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cMET_SERNUM%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,met_ser_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_PARAM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,pos_idx,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDIR_NAME%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,dir_name,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cFILE_NAME%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,file_name,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cVIEW_TYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,view_type,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_ENTRIES%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_tot_file_line_cnt,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cPARAM_LIST%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	
	for(idx=0; idx<g_tot_obis_det; idx++)
	{
		for(jdx=0; jdx<file_num_param; jdx++)
		{
			if(strcmp(org_obis_det[jdx].obis_code, g_obis_det[idx])==0)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				if(loc_idx==(pos_idx-1))
				{
					//printf("%s\n",org_obis_det[jdx].param_name);
					sprintf(g_temp_str,"%c%s%c\n",DBL_QUOTES,org_obis_det[jdx].param_name,DBL_QUOTES);
				}
				else
				{
					printf("%s,",org_obis_det[jdx].param_name);
					sprintf(g_temp_str,"%c%s%c,",DBL_QUOTES,org_obis_det[jdx].param_name,DBL_QUOTES);
				}
				strcat(json_text,g_temp_str);
				loc_idx++;
				break;
			}
		}
	} 
	
	strcat(json_text,"],\n"); // End of PARAM_LIST
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%c%s%c:\n",DBL_QUOTES,"FILE_DATA",DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	for(line_cnt=0; line_cnt<g_tot_file_line_cnt; line_cnt++)
	{
		if(!line_cnt)
			continue;
		
		strcat(json_text,"{");
		//printf("Total actual obis per line : %d For line : %d\n",all_obis_val_info.obis_val_det[line_cnt].tot_num_obis,line_cnt);
		for(idx=0; idx<all_obis_val_info.obis_val_det[line_cnt].tot_num_obis;idx++)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			if(idx==all_obis_val_info.obis_val_det[line_cnt].tot_num_obis-1)
			{
				//printf("%s\n",all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
				sprintf(g_temp_str,"%cV%d%c:%c%s%c",DBL_QUOTES,idx,DBL_QUOTES,DBL_QUOTES,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],DBL_QUOTES);
			}
			else
			{
				//printf("%s,",all_obis_val_info.obis_val_det[line_cnt].obis_val[idx]);
				sprintf(g_temp_str,"%cV%d%c:%c%s%c,",DBL_QUOTES,idx,DBL_QUOTES,DBL_QUOTES,all_obis_val_info.obis_val_det[line_cnt].obis_val[idx],DBL_QUOTES);
			}
			strcat(json_text,g_temp_str);
		}
		
		if(line_cnt==g_tot_file_line_cnt-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}
	
	strcat(json_text,"]\n"); // end of EVENT_DATA
	
	strcat(json_text,"}\n"); // DATA
	
	strcat(json_text,"}\n"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_event_file_content(uint32_t seq_num, const char *met_ser_num,const char *dir_name,const char *file_name,const char *view_type)
{
	char 		file_path[64];
	static char fun_name[]="send_event_file_content()";
	
	memset(file_path,0,sizeof(file_path));
	sprintf(file_path,"%s/%s/%s",ROOT_DATA_DIR,dir_name,file_name);
	
	send_file_content_det(seq_num,met_ser_num,EVENT_OBIS_PARAMS_JSON,"EventParams",file_path,dir_name,file_name,view_type,"GET_EVENT_FILE_CONTENT");
	
	return RET_SUCCESS;
}

int32_t send_bill_file_content(uint32_t seq_num, const char *met_ser_num,const char *dir_name,const char *file_name,const char *view_type)
{
	char 		file_path[64];
	static char fun_name[]="send_bill_file_content()";
	
	memset(file_path,0,sizeof(file_path));
	sprintf(file_path,"%s/%s/%s",ROOT_DATA_DIR,dir_name,file_name);
	
	send_file_content_det(seq_num,met_ser_num,BILL_OBIS_PARAMS_JSON,"BillParams",file_path,dir_name,file_name,view_type,"GET_BILL_FILE_CONTENT");
	
	return RET_SUCCESS;
}

int32_t send_dp_file_content(uint32_t seq_num, const char *met_ser_num,const char *dir_name,const char *file_name,const char *view_type)
{
	char 		file_path[64];
	static char fun_name[]="send_dp_file_content()";
	
	memset(file_path,0,sizeof(file_path));
	sprintf(file_path,"%s/%s/%s",ROOT_DATA_DIR,dir_name,file_name);
	
	send_file_content_det(seq_num,met_ser_num,DP_OBIS_PARAMS_JSON,"MNParams",file_path,dir_name,file_name,view_type,"GET_BILL_FILE_CONTENT");
	
	return RET_SUCCESS;
}

int32_t send_ls_file_content(uint32_t seq_num, const char *met_ser_num,const char *dir_name,const char *file_name,const char *view_type)
{
	char 		file_path[64];
	static char fun_name[]="send_ls_file_content()";
	
	memset(file_path,0,sizeof(file_path));
	sprintf(file_path,"%s/%s/%s",ROOT_DATA_DIR,dir_name,file_name);
	
	send_file_content_det(seq_num,met_ser_num,LS_OBIS_PARAMS_JSON,"LSParams",file_path,dir_name,file_name,view_type,"GET_LS_FILE_CONTENT");
	
	return RET_SUCCESS;
}

int32_t send_file_list_det(int32_t seq_num, const char *met_ser_num, char *type, char *dir_path, char *key_word, uint8_t read_ls, char* dir_name)
{
	if(read_ls==1)
	{
		printf("This time need to send ls files only\n");
	}
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,type,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cOD_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	uint8_t tot_num_dir = 0, idx=0;
	
	DIR 		*dir_det = NULL;
	struct dirent *dir_str=NULL;
	
	dir_det = opendir(dir_path);
	if ( dir_det == NULL )
	{
		printf("Failed to opendir %s\n",strerror(errno));
		return RET_NO_RESP;
	}
	
	while((dir_str=readdir(dir_det)) != NULL )
	{
		if (( strcmp(dir_str->d_name,".") == 0 ) || ( strcmp(dir_str->d_name,"..") == 0 ) || !strstr(dir_str->d_name,key_word))
		{
			continue;
		}
		else if(read_ls==1)
		{
			if(strstr(dir_str->d_name,"bill") || strstr(dir_str->d_name,"dp") ||strstr(dir_str->d_name,"event"))
			{
				//printf("Other than ls file : %s\n",dir_str->d_name);
				continue;
			}
			else
			{
				//printf("ls file : %s\n",dir_str->d_name);
				tot_num_dir++;
			}
		}
		else
			tot_num_dir++;
	}
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDIR_NAME%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,dir_name,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_FILES%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,tot_num_dir,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cFILE_LIST%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");

	closedir(dir_det);
	
	dir_det = opendir(dir_path);
	if ( dir_det == NULL )
	{
		printf("Failed to opendir %s\n",strerror(errno));
		return RET_NO_RESP;
	}
	
	while((dir_str=readdir(dir_det)) != NULL )
	{
		if (( strcmp(dir_str->d_name,".") == 0 ) || ( strcmp(dir_str->d_name,"..") == 0 ) || !strstr(dir_str->d_name,key_word))
		{
			continue;
		}
		else if(key_word==NULL)
		{
			if(strstr(dir_str->d_name,"bill") || strstr(dir_str->d_name,"dp") ||strstr(dir_str->d_name,"event"))
				continue;
		}
		else if(read_ls==1)
		{
			if(strstr(dir_str->d_name,"bill") || strstr(dir_str->d_name,"dp") ||strstr(dir_str->d_name,"event"))
			{
				//printf("Other than ls file : %s\n",dir_str->d_name);
				continue;
			}
			else
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				
				if(idx<tot_num_dir-1)
					sprintf(g_temp_str,"%c%s%c,",DBL_QUOTES,dir_str->d_name,DBL_QUOTES);
				else
					sprintf(g_temp_str,"%c%s%c",DBL_QUOTES,dir_str->d_name,DBL_QUOTES);
				
				strcat(json_text,g_temp_str);
				
				idx++;
			}
		}
		else
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			
			if(idx<tot_num_dir-1)
				sprintf(g_temp_str,"%c%s%c,",DBL_QUOTES,dir_str->d_name,DBL_QUOTES);
			else
				sprintf(g_temp_str,"%c%s%c",DBL_QUOTES,dir_str->d_name,DBL_QUOTES);
			
			strcat(json_text,g_temp_str);
			
			idx++;
		}
	}
	
	strcat(json_text,"]\n");
	
	strcat(json_text,"}\n"); // End of Data
	
	strcat(json_text,"}\n"); // End of Json

	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_od_ls_file_list_det(int32_t seq_num, const char *met_ser_num)
{
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0, idx=0;
	char 		file_name[64];
	char 		dir_name[64];
	char 		od_ls_file_name[6][32];
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	p_redis_reply = redisCommand(p_redis_handler,"hgetall Port%dMet%dOdLsFile",pidx,midx);
	printf("Total num of od files : %d\n",p_redis_reply->elements);
	
	for(idx=0; idx<p_redis_reply->elements; idx=idx+2)
	{
		printf("%s\n",p_redis_reply->element[idx+1]->str);
		strcpy(od_ls_file_name[idx/2],p_redis_reply->element[idx+1]->str);
	}
	
	memset(file_name,0,sizeof(file_name));
	memset(dir_name,0,sizeof(dir_name));
	sprintf(file_name,"%s/meter_id_%d/od",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	sprintf(dir_name,"meter_id_%d",(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	
	//send_file_list_det(seq_num, met_ser_num, "GET_OD_LS_FILE_LIST", file_name, "",1,dir_name);
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"GET_OD_LS_FILE_LIST",DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cOD_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDIR_NAME%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,dir_name,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_FILES%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(p_redis_reply->elements/2),DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cFILE_LIST%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[");

	for(idx=0; idx<p_redis_reply->elements/2; idx++)
	{
		memset(g_temp_str,0,sizeof(g_temp_str));
		if(idx<(p_redis_reply->elements/2)-1)
			sprintf(g_temp_str,"%c%s%c,",DBL_QUOTES,od_ls_file_name[idx],DBL_QUOTES);
		else
			sprintf(g_temp_str,"%c%s%c",DBL_QUOTES,od_ls_file_name[idx],DBL_QUOTES);
				
		strcat(json_text,g_temp_str);
	}
	
	strcat(json_text,"]\n");
	
	strcat(json_text,"}\n"); // End of Data
	
	strcat(json_text,"}\n"); // End of Json

	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_ls_file_list_det(int32_t seq_num, const char *met_ser_num)
{
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0;
	char 		file_name[64];
	char 		dir_name[64];
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	memset(file_name,0,sizeof(file_name));
	memset(dir_name,0,sizeof(dir_name));
	sprintf(file_name,"%s/meter_id_%d",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	sprintf(dir_name,"meter_id_%d",(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	
	send_file_list_det(seq_num, met_ser_num, "GET_LS_FILE_LIST", file_name, "",1,dir_name);
	
	return RET_SUCCESS;
}

int32_t send_event_file_list_det(int32_t seq_num, const char *met_ser_num)
{
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0;
	char 		file_name[64];
	char 		dir_name[64];
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	memset(file_name,0,sizeof(file_name));
	memset(dir_name,0,sizeof(dir_name));
	sprintf(file_name,"%s/meter_id_%d",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	sprintf(dir_name,"meter_id_%d",(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	
	send_file_list_det(seq_num, met_ser_num, "GET_EVENT_FILE_LIST", file_name, "event",0,dir_name);
	
	return RET_SUCCESS;
}

int32_t send_dp_file_list_det(int32_t seq_num, const char *met_ser_num)
{
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0;
	char 		file_name[64];
	char 		dir_name[64];
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	memset(file_name,0,sizeof(file_name));
	memset(dir_name,0,sizeof(dir_name));
	sprintf(file_name,"%s/meter_id_%d",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	sprintf(dir_name,"meter_id_%d",(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	
	send_file_list_det(seq_num, met_ser_num, "GET_DP_FILE_LIST", file_name, "dp",0,dir_name);
	
	return RET_SUCCESS;
}

int32_t send_bill_file_list_det(int32_t seq_num, const char *met_ser_num)
{
	int16_t 	pidx_midx = 0;
	uint8_t 	pidx=0,midx=0;
	char 		file_name[64];
	char 		dir_name[64];
	
	pidx_midx = find_ser_num(met_ser_num);
	pidx = (pidx_midx>>8)&0XFF;
	midx = pidx_midx&0XFF;
	
	memset(file_name,0,sizeof(file_name));
	memset(dir_name,0,sizeof(dir_name));
	sprintf(file_name,"%s/meter_id_%d",ROOT_DATA_DIR,(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	sprintf(dir_name,"meter_id_%d",(pidx*MAX_NO_OF_METER_PER_PORT+midx));
	
	send_file_list_det(seq_num, met_ser_num, "GET_BILL_FILE_LIST", file_name, "bill",0,dir_name);
	
	return RET_SUCCESS;
}

int32_t send_dir_list_det(int32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"GET_DIR_LIST",DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cOD_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	uint8_t tot_num_dir = 0, idx=0;
	
	DIR 		*dir_det = NULL;
	struct dirent *dir_str=NULL;
	
	dir_det = opendir(ROOT_DATA_DIR);
	if ( dir_det == NULL )
	{
		printf("Failed to opendir %s\n",strerror(errno));
		return RET_NO_RESP;
	}
	
	while((dir_str=readdir(dir_det)) != NULL )
	{
		if (( strcmp(dir_str->d_name,".") == 0 ) || ( strcmp(dir_str->d_name,"..") == 0 ) || !strstr(dir_str->d_name,"meter_id"))
		{
			continue;
		}
		else
			tot_num_dir++;
	}
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_DIRS%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,tot_num_dir,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDIR_LIST%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");

	closedir(dir_det);
	
	dir_det = opendir(ROOT_DATA_DIR);
	if ( dir_det == NULL )
	{
		printf("Failed to opendir %s\n",strerror(errno));
		return RET_NO_RESP;
	}
	
	while((dir_str=readdir(dir_det)) != NULL )
	{
		if (( strcmp(dir_str->d_name,".") == 0 ) || ( strcmp(dir_str->d_name,"..") == 0 ) || !strstr(dir_str->d_name,"meter_id"))
		{
			continue;
		}
		else
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			
			if(idx<tot_num_dir-1)
				sprintf(g_temp_str,"%c%s%c,",DBL_QUOTES,dir_str->d_name,DBL_QUOTES);
			else
				sprintf(g_temp_str,"%c%s%c",DBL_QUOTES,dir_str->d_name,DBL_QUOTES);
			
			strcat(json_text,g_temp_str);
			
			idx++;
		}
	}
	
	strcat(json_text,"]\n");
	
	strcat(json_text,"}\n"); // End of Data
	
	strcat(json_text,"}\n"); // End of Json

	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

/* End Of File */