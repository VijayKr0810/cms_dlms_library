#include "gen_inc.h"
#include "dlms_api_config.h"
#include "dlms_api.h"
#include "log.h"
#include "dlms_fun.h"
#include "dlms_met_poll_proc.h"
#include "/home/iot-gateway/hiredis/hiredis.h"


/* Extern */
extern uint8_t 					g_port_idx,g_midx;
extern gen_data_val_info_t			gen_data_val_info[];
extern all_param_obis_val_info_t 	g_all_inst_param_obis_val;

extern gen_params_det_t 		gen_inst_param_det[],
								gen_ls_param_det[],
								gen_event_param_det[],
								gen_bill_param_det[],
								gen_daily_prof_param_det[];
								
extern dlms_dcu_config_t 			dlms_dcu_config;
extern meter_comm_params_t 			meter_comm_params;				
extern obis_name_plate_info_t 		name_plate_info[];
extern redisContext 			*p_redis_handler;
extern redisReply 				*p_redis_reply;
extern uint8_t 					g_need_to_read_obis[];	
extern int32_t 					g_num_blocks_blk_data[];		
char 	g_line_buff[512];
/* ========================================================================================== */

int32_t get_inst_data_for_all_met(void)
{
	static char fun_name[]="inst_data_all_met()";
	uint8_t midx;
	time_t time_now;
	int32_t fun_ret;
	
	for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
	{
		send_hc_msg();
		g_midx=midx;
		
		if(dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable)
		{
			fill_meter_comm_params_det(&meter_comm_params,midx);
			time_now=time(NULL);
			fun_ret = connect_to_meter(&meter_comm_params);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to connect Meter Error Code : %d\n",fun_name,fun_ret);
				p_redis_reply = redisCommand(p_redis_handler, "HMSET SerPort%dMet%dStatus VALUE %d",g_port_idx,midx,0);
				freeReplyObject(p_redis_reply);
				g_need_to_read_obis[midx]=1;
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Conneted to meter.\n",fun_name);
				p_redis_reply = redisCommand(p_redis_handler, "HMSET SerPort%dMet%dStatus VALUE %d",g_port_idx,midx,1);
				freeReplyObject(p_redis_reply);
			}
			
			send_hc_msg();
			
			memset(&name_plate_info[midx],0,sizeof(obis_name_plate_info_t));
			
			fun_ret = get_nameplate_details(&meter_comm_params, &name_plate_info[midx]);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to get nameplate info from Meter Error Code : %d\n",
				fun_name,fun_ret);
				g_need_to_read_obis[midx]=1;
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Recv Nameplate from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
				
				update_np_det_to_redis(&name_plate_info[midx],midx);
			}

			send_hc_msg();
			
			time_now=time(NULL);
			
			if(g_need_to_read_obis[midx]==1)
			{
				met_poll_dbg_log(INFORM,"%-20s : Inside Read Inst Data, Need to read Obis Code flag enable\n",fun_name);
				if(read_meter_obis_code(midx)<0)
				{
					g_need_to_read_obis[midx]=1;
				}
				else
				{
					met_poll_dbg_log(INFORM,"%-20s : Inside Read Inst Data, Recvd read Obis Code\n",fun_name);
					g_need_to_read_obis[midx]=0;
				}
			}

			send_hc_msg();

			fun_ret = get_inst_values(&meter_comm_params, gen_data_val_info);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to inst info from Meter Error Code : %d\n",fun_name,fun_ret);
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Recv Inst Data from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
				
				if(fill_recv_inst_val(midx)<0)
				{
					met_poll_dbg_log(INFORM,"%-20s : Failed to filled inst val recv from Library\n",fun_name);
					continue;
				}

				send_inst_det_to_redis(INST_INFO_KEY,midx);
			}
		}
		else
		{
			p_redis_reply = redisCommand(p_redis_handler, "HMSET SerPort%dMet%dStatus VALUE %d",g_port_idx,midx,2);
			freeReplyObject(p_redis_reply);
		}
	}
	
	send_hc_msg();
	
	check_met_ser_num();
	
	return 0;
}

int32_t read_meter_obis_code(uint8_t midx)
{
	static char fun_name[]="read_meter_obis_code";
	int32_t fun_ret,idx;
	time_t time_now;
	
	memset(&gen_inst_param_det[midx],0,sizeof(gen_params_det_t));
	memset(&gen_ls_param_det[midx],0,sizeof(gen_params_det_t));
	memset(&gen_bill_param_det[midx],0,sizeof(gen_params_det_t));
	memset(&gen_daily_prof_param_det[midx],0,sizeof(gen_params_det_t));
	memset(&gen_event_param_det[midx],0,sizeof(gen_params_det_t));
	
	time_now=time(NULL);
	fun_ret = get_obis_codes(&meter_comm_params,&gen_inst_param_det[midx],&gen_ls_param_det[midx],
	&gen_event_param_det[midx],&gen_bill_param_det[midx],&gen_daily_prof_param_det[midx]);
	if(fun_ret<0)
	{
		g_need_to_read_obis[midx]=1;
		met_poll_dbg_log(REPORT,"%-20s : Failed to obis info from Meter Error Code : %d\n",fun_name,fun_ret);
		return -1;
	}
	else
	{
		met_poll_dbg_log(INFORM,"%-20s : Recv all obis code from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
		g_need_to_read_obis[midx]=0;
		
		send_hc_msg();
		
		met_poll_dbg_log(REPORT,"%-20s : Inst obis info details!!!\n",fun_name);
		for(idx=0; idx<gen_inst_param_det[midx].tot_num_val_obis; idx++)
			print_val_scal_onis_val_info(gen_inst_param_det[midx].val_obis[idx],gen_inst_param_det[midx].scalar_val[idx].obis_code,gen_inst_param_det[midx].scalar_val[idx].value);
		
		met_poll_dbg_log(REPORT,"%-20s : Load survey obis info details!!!\n",fun_name);
		for(idx=0; idx<gen_ls_param_det[midx].tot_num_val_obis; idx++)
			print_val_scal_onis_val_info(gen_ls_param_det[midx].val_obis[idx],gen_ls_param_det[midx].scalar_val[idx].obis_code,gen_ls_param_det[midx].scalar_val[idx].value);
		
		met_poll_dbg_log(REPORT,"%-20s : Event obis info details!!!\n",fun_name);
		for(idx=0; idx<gen_event_param_det[midx].tot_num_val_obis; idx++)
			print_val_scal_onis_val_info(gen_event_param_det[midx].val_obis[idx],gen_event_param_det[midx].scalar_val[idx].obis_code,gen_event_param_det[midx].scalar_val[idx].value);
		
		met_poll_dbg_log(REPORT,"%-20s : Billing obis info details!!!\n",fun_name);
		for(idx=0; idx<gen_bill_param_det[midx].tot_num_val_obis; idx++)
			print_val_scal_onis_val_info(gen_bill_param_det[midx].val_obis[idx],gen_bill_param_det[midx].scalar_val[idx].obis_code,gen_bill_param_det[midx].scalar_val[idx].value);
		
		met_poll_dbg_log(REPORT,"%-20s : Midnight obis info details!!!\n",fun_name);
		for(idx=0; idx<gen_daily_prof_param_det[midx].tot_num_val_obis; idx++)
			print_val_scal_onis_val_info(gen_daily_prof_param_det[midx].val_obis[idx],gen_daily_prof_param_det[midx].scalar_val[idx].obis_code,gen_daily_prof_param_det[midx].scalar_val[idx].value);
	}
	
	g_num_blocks_blk_data[midx] = get_int_blk_period(&meter_comm_params);
	if(g_num_blocks_blk_data[midx]<0)
	{
		met_poll_dbg_log(REPORT,"%-20s : Failed to Block details for LS, Error Code : %d\n",fun_name,g_num_blocks_blk_data[midx]);
		return -1;
	}

	send_hc_msg();
	
	g_need_to_read_obis[midx]=0;
	return 0;
}
/**************************************************************************************************
*Function 					: store_recv_inst_date_time()
*Input Parameters 			: inst index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store inst date time in appropriate structure.
********************************************************************************************************/
int32_t store_recv_inst_date_time(uint8_t midx, uint8_t index)
{
	uint16_t 	year;
	date_time_t date_time;
	
	year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
	date_time.day= gen_data_val_info[index].value[3];
	date_time.month= gen_data_val_info[index].value[2];
	date_time.year =  year;
	date_time.hour= gen_data_val_info[index].value[5];
	date_time.minute= gen_data_val_info[index].value[6];
	date_time.second= gen_data_val_info[index].value[7];
	
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].obis_code,gen_inst_param_det[midx].val_obis[index],6);
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].value,&date_time,sizeof(date_time_t));
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: store_recv_inst_val()
*Input Parameters 			: comm_fd, meter address, meter addr size, inst val structure.
*Output Parameters 			: Inst val structure.
*Return	Value				: Success or appropriate error code.
*Description 				: To get inst value and copy into respective structure.
********************************************************************************************************/
int32_t store_recv_inst_val(uint8_t midx, uint8_t index, float recv_flt_val)
{
	static char fun_name[] = "store_recv_inst_val()";
	
	//dbg_log(INFORM,"%-20s : Index : %d, RecvFltVal : %0.5f\n",fun_name,index,recv_flt_val);
	
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].obis_code,gen_inst_param_det[midx].val_obis[index],6);
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].value,&recv_flt_val,4);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: fill_recv_inst_val()
*Input Parameters 			: None.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To fill inst data value in appropriate structure.
********************************************************************************************************/
int32_t fill_recv_inst_val(uint8_t midx)
{
	static char fun_name[]="fill_recv_inst_val()";
	uint8_t 	idx=0;
	int8_t 		*p_tmp_str=NULL;
	float 		flt_val = 0.0,scal_flt_val=0.0;
	uint8_t		uint8_temp_val=0;
	int16_t		int16_temp_val=0;
	uint16_t	uint16_temp_val=0;
	int32_t		int32_temp_val=0;
	uint32_t	uint32_temp_val=0;
	float 		float_temp_val=0.0;
	

	g_all_inst_param_obis_val.tot_num_params=gen_inst_param_det[midx].tot_num_value;
	
	for(idx=0; idx<gen_inst_param_det[midx].tot_num_value; idx++)
	{
		//printf("fill_inst_val : Idx : %d , scalar val : %d\n",idx,gen_inst_param_det.scalar_val[idx].value);
		switch(gen_data_val_info[idx].data_type)
		{
			case	FLOAT_32BIT_TYPE:
				p_tmp_str=(int8_t*)&float_temp_val;
				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_act_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				
				flt_val = (float)((float)float_temp_val * scal_flt_val);
				if(store_recv_inst_val(midx, idx, flt_val) < 0)
					continue;
			break;
			
			case UNSIGNED_32BIT_TYPE:
				p_tmp_str=(int8_t*)&uint32_temp_val;

				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_act_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				
				flt_val = (float)((float)uint32_temp_val * scal_flt_val);
				
				if(store_recv_inst_val(midx, idx, flt_val) < 0)
					continue;
				
			break;
			case SIGNED_32BIT_TYPE:
				p_tmp_str=(int8_t*)&int32_temp_val;

				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_act_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				
				flt_val = (float)((float)int32_temp_val * scal_flt_val);
				
				if(store_recv_inst_val(midx, idx, flt_val) < 0)
					continue;
	
			break;
			
			case UNSIGNED_16BIT_TYPE:
					p_tmp_str=(int8_t*)&uint16_temp_val;


					p_tmp_str[1] = gen_data_val_info[idx].value[0];
					p_tmp_str[0] = gen_data_val_info[idx].value[1];
					
					get_act_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);
					
				
					flt_val = (float)((float)uint16_temp_val * scal_flt_val);

					
					if(store_recv_inst_val(midx, idx, flt_val) < 0)
						continue;
			break;
			
			case SIGNED_16BIT_TYPE:

				p_tmp_str=(int8_t*)&int16_temp_val;

				p_tmp_str[1] = gen_data_val_info[idx].value[0];
				p_tmp_str[0] = gen_data_val_info[idx].value[1];
				
				get_act_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);

				flt_val = (float)((float)int16_temp_val * scal_flt_val);
				
				if(store_recv_inst_val(midx, idx, flt_val) < 0)
					continue;
			break;
			
			case UNSIGNED_8BIT_TYPE:
				p_tmp_str=(int8_t*)&uint8_temp_val;
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				get_act_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				flt_val = (float)((float)uint8_temp_val * scal_flt_val);
				
				if(store_recv_inst_val(midx, idx, flt_val) < 0)
					continue;
			break;
			
			case OCTET_STRING_TYPE:
				if(store_recv_inst_date_time(midx, idx)<0)
					continue;

			break;
			
			default : break;
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_act_scaler_mf()
*Input Parameters 			: multiplication factor and value.
*Output Parameters 			: multiplication factor value.
*Return	Value				: Success or appropriate error code.
*Description 				: To get multiplication factor.
********************************************************************************************************/
int32_t get_act_scaler_mf(int8_t mf,float *mf_val)
{
	switch( mf )
	{
		case -7:*mf_val = 0.0000001;break;		
		case -6:*mf_val = 0.000001;break;		
		case -5:*mf_val = 0.00001;break;
		case -4:*mf_val = 0.0001;;break;
		case -3:*mf_val = 0.001;break;
		case -2:*mf_val = 0.01;break;
		case -1:*mf_val = 0.1;break;
		case 1:*mf_val = 10.0;break;
		case 2:*mf_val = 100.0;break;
		case 3:*mf_val = 1000.0;break;
		case 4:*mf_val = 10000.0;break;
		case 5:*mf_val = 100000.0;break;
		case 6:*mf_val = 1000000.0;break;
		case 7:*mf_val = 10000000.0;break;
		case 8:*mf_val = 100000000.0;break;
		case 9:*mf_val = 1000000000.0;break;
		default:*mf_val = 1.0;break;
	}

	return RET_SUCCESS;
}

/* Convert lib org file to decode file into respective directory Only in case of load survey*/
void append_in_exist_file(char *out_file_path, char *in_file_name, gen_params_det_t *recv_gen_param_det)
{
	static char fun_name[]="apndn_exist_file()";
	float scal_flt_val;
	struct stat file_st;
	
	if(stat(out_file_path,&file_st)==-1)
	{
		met_poll_dbg_log(REPORT,"%-20s : Not Present Output File : %s\n",fun_name,out_file_path);
		
		if(convert_to_decoded_data(out_file_path,in_file_name,recv_gen_param_det)<0)
		{
			return;
		}
	}
	else
	{
		int32_t		file_fd=0;
		file_fd = open(out_file_path, O_RDONLY);
		if (file_fd == -1) 
		{
			met_poll_dbg_log(REPORT,"%-20s : can't open file Error - %s\n",fun_name,strerror(errno));
		}
		
		char *p_file_read=malloc(file_st.st_size+1);
		memset(p_file_read,0,file_st.st_size+1);
		
		if (file_st.st_size!=read(file_fd, p_file_read, file_st.st_size)) 
		{
			met_poll_dbg_log(REPORT,"%-20s : can't read file Error - %s\n",fun_name,strerror(errno));
	
			close(file_fd);
			free(p_file_read);
			return ;
		}
		
		p_file_read[file_st.st_size]='\0';
		
		//met_poll_dbg_log(INFORM,"%-20s :  OutPut File : %s, ContentLen : %d\n",fun_name,out_file_path,strlen(p_file_read));
		close(file_fd);
		
		FILE *p_file_ptr;
		p_file_ptr = fopen(in_file_name,"r");
		if(p_file_ptr==NULL)
		{
			met_poll_dbg_log(REPORT,"%-20s :  Open Input file : %s in read mode Error :  %s\n",fun_name,in_file_name,strerror(errno));
			free(p_file_read);
			return ;
		}
		
		int32_t line_cnt=0;
		memset(g_line_buff,0,sizeof(g_line_buff));
		while(fgets(g_line_buff,512,p_file_ptr)!=NULL)
		{
			line_cnt++;
		}
		fclose(p_file_ptr);
		
		met_poll_dbg_log(INFORM,"%-20s :  Input File : %s, TotLine Count : %d\n",fun_name,in_file_name,line_cnt);
		
		char in_data_buff[line_cnt][512];
		
		memset(in_data_buff,0,sizeof(in_data_buff));
		
		p_file_ptr = fopen(in_file_name,"r");
		if(p_file_ptr==NULL)
		{
			met_poll_dbg_log(REPORT,"%-20s :  Open Input file : %s in read mode Error :  %s\n",fun_name,in_file_name,strerror(errno));
			free(p_file_read);
			return ;
		}
		
		line_cnt=0;
		memset(g_line_buff,0,sizeof(g_line_buff));
		while(fgets(g_line_buff,512,p_file_ptr)!=NULL)
		{
			strcpy(in_data_buff[line_cnt],g_line_buff);
			line_cnt++;
		}
		fclose(p_file_ptr);
		
		//met_poll_dbg_log(INFORM,"%-20s :  IN_DATA_BUFF : TotLen : %d\n",fun_name,line_cnt);
		
		p_file_ptr = fopen(out_file_path,"a");
		if(p_file_ptr==NULL)
		{
			met_poll_dbg_log(REPORT,"%-20s :  Open Input file : %s in Append mode Error :  %s\n",fun_name,out_file_path,strerror(errno));
			free(p_file_read);
			return ;
		}
		
		int32_t idx;
		char time_buff[32];
		for(idx=1; idx<line_cnt; idx++)
		{
			//met_poll_dbg_log(INFORM,"%-20s : Entry Idx : %d\n%s\n",fun_name,idx,in_data_buff[idx]);
			
			memset(time_buff,0,sizeof(time_buff));
			sprintf(time_buff,"%c%c:%c%c",in_data_buff[idx][0],in_data_buff[idx][1],in_data_buff[idx][3],in_data_buff[idx][4]);
			
			if(strstr(p_file_read,time_buff)!=NULL)
			{
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Entry Idx : %d New Time : %s need to in file\n",fun_name,idx,time_buff);
				char *token;
				int32_t val_cnt=0;
				token = strtok(in_data_buff[idx],"\t");
				while(token!=NULL)
				{
					//printf("%s ",token);
					val_cnt++;
					if(val_cnt==1)
					{
						fprintf(p_file_ptr,"%s\t",token);
						fflush(p_file_ptr);
					}
					else
					{
						get_act_scaler_mf(recv_gen_param_det->scalar_val[val_cnt].value,&scal_flt_val);
						fprintf(p_file_ptr,"%0.5f\t",atof(token)*scal_flt_val);
						fflush(p_file_ptr);
					}
					token = strtok(NULL,"\t");
				}
				//printf("%s","\n");
				fprintf(p_file_ptr,"%s","\n");
				fflush(p_file_ptr);
			}
		}
		free(p_file_read);
		fclose(p_file_ptr);
	}
	
	met_poll_dbg_log(REPORT,"%-20s :  Success Write Output file :  %s\n",fun_name,out_file_path);
}

/* Convert lib org file to decode file into respective directory */
int32_t convert_to_decoded_data(char *out_file_path, char *in_file_name, gen_params_det_t *recv_gen_param_det)
{
	static char fun_name[]="conv_to_decd_data()";
	struct stat file_st;
	
	/* char *dp_ptr=NULL,*bill_ptr=NULL,*event_ptr=NULL; */
	
	//>>>>Output File : /usr/cms/data/DlmsData/meter_id_2/01_10_2020
	
	met_poll_dbg_log(INFORM,"%-20s : >>>>Output File : %s\n",fun_name,out_file_path);
	
/* 	dp_ptr = strstr(out_file_path,"dp");
	bill_ptr = strstr(out_file_path,"bill");
	event_ptr = strstr(out_file_path,"event"); */
	
	/* met_poll_dbg_log(INFORM,"%-20s : File status : %s, %s, %s\n",fun_name,dp_ptr,bill_ptr,event_ptr); */
	//if((strstr(out_file_path,"dp")==NULL) || (strstr(out_file_path,"bill")==NULL) || (strstr(out_file_path,"event")==NULL))
	//if((strstr(out_file_path,"dp")==NULL) || (strstr(out_file_path,"bill")==NULL) || (strstr(out_file_path,"event")==NULL))
	
/* 	if(((dp_ptr)==NULL) || ((bill_ptr)==NULL) || ((event_ptr)==NULL))
	{
		if(stat(out_file_path,&file_st)!=-1)
		{
			met_poll_dbg_log(INFORM,"%-20s : Output File : %s available\n",fun_name,out_file_path);
		
			append_in_exist_file(out_file_path,in_file_name,recv_gen_param_det);
			
			return RET_SUCCESS;
		}
	} */

	float scal_flt_val;
	FILE *p_file_ptr,*p_file_ptr1;
	
	p_file_ptr = fopen(in_file_name,"r");
	if(p_file_ptr==NULL)
	{
		met_poll_dbg_log(REPORT,"%-20s : Open Input file : %s in read mode Error :  %s\n",fun_name,in_file_name,strerror(errno));
		return -1;
	}
	
	p_file_ptr1 = fopen(out_file_path,"w");
	if(p_file_ptr1==NULL)
	{
		met_poll_dbg_log(REPORT,"%-20s : Open Output file : %s in Write mode Error :  %s\n",fun_name,out_file_path,strerror(errno));
		fclose(p_file_ptr);
		return -1;
	}

	//printf(">>>Files opened for read/write...\n");
	
	int32_t line_cnt=0;
	memset(g_line_buff,0,sizeof(g_line_buff));
	
	while(fgets(g_line_buff,512,p_file_ptr)!=NULL)
	{
		//printf("%s\n",g_line_buff);
		line_cnt++;
		if(line_cnt==1)
		{
			//printf("This is obis content line, need to strore in output file as it is\n");
			fputs(g_line_buff,p_file_ptr1);
			fflush(p_file_ptr1);
		}
		else
		{
			char *token;
			int32_t val_cnt=0;
			token = strtok(g_line_buff,"\t");
			
			while(token!=NULL)
			{
				//printf("%s ",token);
				val_cnt++;
				if(val_cnt==1)
				{
					fprintf(p_file_ptr1,"%s\t",token);
					fflush(p_file_ptr1);
				}
				else
				{
					//float loc_flt_val;
					scal_flt_val=0.0;
					get_act_scaler_mf(recv_gen_param_det->scalar_val[val_cnt].value,&scal_flt_val);
					if(val_cnt==recv_gen_param_det->tot_num_val_obis)
					{
						if(strstr(token,"\n"))
						{
							char loc_token[32];
							memset(loc_token,0,sizeof(loc_token));
							strncpy(loc_token,token,strlen(token)-1);
							fprintf(p_file_ptr1,"%0.5f",atof(loc_token)*scal_flt_val);
						}
						else
						{
							fprintf(p_file_ptr1,"%0.5f\t",atof(token)*scal_flt_val);
						}
					}
					else
						fprintf(p_file_ptr1,"%0.5f\t",atof(token)*scal_flt_val);
					
					fflush(p_file_ptr1);
				}
				token = strtok(NULL,"\t");
			}
			//printf("%s","\n");
			fprintf(p_file_ptr1,"%s","\n");
			//fflush(p_file_ptr1);
			
			//printf("Total Value in Input file : %d\n",val_cnt);
		}
	}
	
	met_poll_dbg_log(REPORT,"%-20s :  Success Write Output file :  %s\n",fun_name,out_file_path);
	
	fclose(p_file_ptr);
	fclose(p_file_ptr1);

	//printf("Total lines in Input file : %d\n",line_cnt);
	
	/* rename(out_file_path,in_file_path);
	remove(out_file_path); */
	
	return RET_SUCCESS;
}

/* End Of File */