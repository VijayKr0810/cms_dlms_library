/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	main.c
* Summary:  Meter Poll Process of DLMS Module.
*
**********************************************************************/

/* Includes */
#include "gen_inc.h"
#include "dlms_api_config.h"
#include "dlms_api.h"
#include "log.h"
#include "dlms_fun.h"
#include "/home/iot-gateway/hiredis/hiredis.h"
#include "dlms_met_poll_proc.h"
//#include "dbg_logger_proc.h"

int32_t create_ipc_socket(char *log_ip_addr, uint16_t loc_port);
/* Globals */
int32_t 				g_win_dbg_soc_fd;
time_t 					g_last_hc_msg_time;
char					p_comm_port_det[16];
char					g_data_dir_path[64];
uint8_t 				g_need_to_read_obis[MAX_NO_OF_METER_PER_PORT];
uint8_t 				g_port_idx,g_midx;
char 					poll_debug_file_name[64];
int32_t 				g_num_blocks_blk_data[MAX_NO_OF_METER_PER_PORT];
time_t 					g_inst_resp_time[MAX_NO_OF_METER_PER_PORT][MAX_RESP_TIME_ENTRY];
time_t 					g_ls_resp_time[MAX_NO_OF_METER_PER_PORT][MAX_RESP_TIME_ENTRY];
time_t 					g_dp_resp_time[MAX_NO_OF_METER_PER_PORT][MAX_RESP_TIME_ENTRY];
time_t 					g_event_resp_time[MAX_NO_OF_METER_PER_PORT][MAX_RESP_TIME_ENTRY];
time_t 					g_bill_resp_time[MAX_NO_OF_METER_PER_PORT][MAX_RESP_TIME_ENTRY];

time_t 					g_avg_inst_resp_time;
time_t 					g_avg_dp_resp_time;
time_t 					g_avg_bill_resp_time;
time_t 					g_avg_event_resp_time;
time_t 					g_avg_ls_resp_time;

time_t 					g_avg_inst_resp_time;
uint8_t 				g_inst_resp_time_cnt;
uint8_t 				g_ls_resp_time_cnt;
uint8_t 				g_dp_resp_time_cnt;
uint8_t 				g_event_resp_time_cnt;
uint8_t 				g_bill_resp_time_cnt;
char					g_curr_meter_ser_info[MAX_NO_OF_METER_PER_PORT][32];
char					g_prev_meter_ser_info[MAX_NO_OF_METER_PER_PORT][32];

/* Structures */
gen_data_val_info_t			gen_data_val_info[128];

all_param_obis_val_info_t 	g_all_inst_param_obis_val,
							g_all_ls_param_obis_val,
							g_all_event_param_obis_val,
							g_all_bill_param_obis_val,
							g_all_dp_param_obis_val;
							
dlms_dcu_config_t 			dlms_dcu_config;

meter_comm_params_t 			meter_comm_params;
gen_params_det_t 				gen_inst_param_det[MAX_NO_OF_METER_PER_PORT],
								gen_ls_param_det[MAX_NO_OF_METER_PER_PORT],
								gen_event_param_det[MAX_NO_OF_METER_PER_PORT],
								gen_bill_param_det[MAX_NO_OF_METER_PER_PORT],
								gen_daily_prof_param_det[MAX_NO_OF_METER_PER_PORT];
								
obis_name_plate_info_t 			name_plate_info[MAX_NO_OF_METER_PER_PORT];
inst_val_info_t					g_inst_data_val;

	
redisContext 			*p_redis_handler=NULL;
redisReply 				*p_redis_reply=NULL;


/* ------------------------------------------------------------------------------------------- */

/**************************************************************************************************
*Function 					: main()
*Input Parameters 			: Command line argument. port details
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: Initail point of Module.
********************************************************************************************************/
int main(int argc, char **argv)
{
	static char 	fun_name[]="main()";
	int32_t 		fun_ret=-1,idx=0;
	uint8_t 		midx=0;
	struct 			stat dir_st = {0};
	time_t tot_time_now,time_now;
	

	g_last_hc_msg_time=time(NULL);
	clear_temp_lib_data(0);
	
	g_midx=midx;
	memset(poll_debug_file_name,0,sizeof(poll_debug_file_name));
	
	if(argc < 2)
	{
		printf("Please provide port details!!, recv numof argument : %d\n",argc);
		return -1;
	}
	
	g_port_idx= atoi(argv[1]);
	if(g_port_idx>MAX_NO_OF_SERIAL_PORT)
	{
		printf("Please provide Valid port details, it should be in between %d to %d\n",0,MAX_NO_OF_SERIAL_PORT);
		return -1;
	}

	sprintf(poll_debug_file_name,"%s/%s_%d.log",LOG_DIR,MET_POLL_LOG_FILE_NAME,g_port_idx);
	
	met_poll_dbg_log(REPORT,"%-20s : !!!!! Meter Poll Proc Started Now!!!!!!!!!!!!\n",fun_name);
	
	if(redis_init("127.0.0.1",6379)!=RET_SUCCESS)
	{
		g_midx=midx;
		met_poll_dbg_log(REPORT,"%-20s : Redis Client initialize failed\n",fun_name);
		return -1;
	}
	
	send_hc_msg();
	
	if(read_cfg_from_redis()!=RET_SUCCESS)
	{
		g_midx=midx;
		met_poll_dbg_log(REPORT,"%-20s : Get Basic config from redis failed\n",fun_name);
		return -1;
	}
	
	g_win_dbg_soc_fd = create_ipc_socket(dlms_dcu_config.dlms_dcu_info.dbglog_ip,DLMS_MODULE_IPC_PORT+g_port_idx);
	if(g_win_dbg_soc_fd<0)
	{
		met_poll_dbg_log(INFORM,"%-20s : Failed to create Windows Dbg log socket\n",fun_name);
		return -1;
	}
	else
	{
		met_poll_dbg_log(INFORM,"%-20s : Success Windows Dbg log socket on Ip : %s, With FD : %d\n",
		fun_name,dlms_dcu_config.dlms_dcu_info.dbglog_ip,g_win_dbg_soc_fd);
	}
	
	g_midx=midx;
	met_poll_dbg_log(INFORM,"%-20s : Uart Port det for this Port : %s\n",
	fun_name,dlms_dcu_config.ser_prot_cfg.ser_prot_param[g_port_idx].ser_port);
	
	g_last_hc_msg_time=time(NULL);
	
	memset(&meter_comm_params,0,sizeof(meter_comm_params_t));
	fill_meter_comm_params_det(&meter_comm_params,0);
	
	send_hc_msg();
	
	fun_ret = init_comm(&meter_comm_params);
	if(fun_ret<0)
	{
		g_midx=midx;
		met_poll_dbg_log(REPORT,"%-20s : Failed to initilized communication Error Code : %d\n",fun_name,fun_ret);
		return -1;
	}
	
	met_poll_dbg_log(INFORM,"%-20s : Communication establised\n",fun_name);
	
	memset(g_data_dir_path,0,sizeof(g_data_dir_path));
	sprintf(g_data_dir_path,"%s",ROOT_DATA_DIR);
	
	if (stat(g_data_dir_path, &dir_st) == -1) 
	{
		if( (mkdir(g_data_dir_path,0777) ) < 0 )					
		{
			met_poll_dbg_log(INFORM,"%-20s : Created Root data dir : %s\n",fun_name,g_data_dir_path);
		}
	}
	
	memset(g_data_dir_path,0,sizeof(g_data_dir_path));
	sprintf(g_data_dir_path,"%s",ROOT_LIB_DATA_DIR);
	
	if (stat(g_data_dir_path, &dir_st) == -1) 
	{
		if( (mkdir(g_data_dir_path,0777) ) < 0 )					
		{
			met_poll_dbg_log(INFORM,"%-20s : Created Root Lib data dir : %s\n",fun_name,g_data_dir_path);
		}
	}
	
	for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
	{
		g_midx=midx;
		
		send_hc_msg();
		
		if(!dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable)
		{
			continue;
		}
		
		memset(g_data_dir_path,0,sizeof(g_data_dir_path));
		sprintf(g_data_dir_path,"%s/meter_id_%d",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
		
		if (stat(g_data_dir_path, &dir_st) == -1) 
		{
			if( (mkdir(g_data_dir_path,0777) ) < 0 )					
			{
				met_poll_dbg_log(INFORM,"%-20s : Created Root Lib data dir : %s\n",fun_name,g_data_dir_path);
			}
		}
		
		memset(g_data_dir_path,0,sizeof(g_data_dir_path));
		sprintf(g_data_dir_path,"%s/meter_id_%d",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
		
		if (stat(g_data_dir_path, &dir_st) == -1) 
		{
			if( (mkdir(g_data_dir_path,0777) ) < 0 )					
			{
				met_poll_dbg_log(INFORM,"%-20s : Created Root ls data dir : %s\n",fun_name,g_data_dir_path);
			}
		}
		
		memset(g_data_dir_path,0,sizeof(g_data_dir_path));
		sprintf(g_data_dir_path,"%s/meter_id_%d/od",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
		
		if (stat(g_data_dir_path, &dir_st) == -1) 
		{
			if( (mkdir(g_data_dir_path,0777) ) < 0 )					
			{
				met_poll_dbg_log(INFORM,"%-20s : Created Root ls OD data dir : %s\n",fun_name,g_data_dir_path);
			}
		}
	}
	
	get_prev_met_ser_num();

	/* dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[0].meter_addr=22;
	fill_meter_comm_params_det(&meter_comm_params,0);
	connect_to_meter(&meter_comm_params);
	
	meter_comm_params.from.day =29;
	meter_comm_params.from.month = 8;
	meter_comm_params.from.year = 2020;
	meter_comm_params.from.hour = 0;
	meter_comm_params.from.minute = 4;
	meter_comm_params.from.second = 0;
	
	meter_comm_params.to.day = 1;
	meter_comm_params.to.month = 9;
	meter_comm_params.to.year = 2020;
	meter_comm_params.to.hour = 0;
	meter_comm_params.to.minute = 4;
	meter_comm_params.to.second =0;
	

	fun_ret = get_ls_values_day_range(&meter_comm_params,1);
	if(fun_ret<0)
	{
		met_poll_dbg_log(REPORT,"%-20s : Failed to get Current day ls data from Meter Error Code : %d\n",fun_name,fun_ret);
	}
			
	return 0; */
	
	char file_path[64];
	char file_name[64];
	char dir_path[64];
	
	/* Read Basic Obis and Inst data */
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
		
			if(read_meter_obis_code(midx)<0)
			{
				met_poll_dbg_log(INFORM,"%-20s : Initially Need to read Obis Code flag enable\n",fun_name);
				g_need_to_read_obis[midx]=1;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Initially  Recvd read Obis Code\n",fun_name);
				g_need_to_read_obis[midx]=0;
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
	
	/* Read Event */
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
				met_poll_dbg_log(INFORM,"%-20s : Event Need to read Obis Code flag enable\n",fun_name);
				if(read_meter_obis_code(midx)<0)
				{
					g_need_to_read_obis[midx]=1;
				}
				else
				{
					met_poll_dbg_log(INFORM,"%-20s : Event Recvd read Obis Code\n",fun_name);
					g_need_to_read_obis[midx]=0;
				}
			}
			
			send_hc_msg();
			time_now=time(NULL);
			
			time_t tot_eve_time=time(NULL);
			
			uint8_t event_class_type=0;
			
			for(event_class_type=0; event_class_type<7; event_class_type++)
			{
				send_hc_msg();
				
				clear_temp_lib_data(midx);
	
				memset(file_path,0,sizeof(file_path));
				memset(file_name,0,sizeof(file_name));
					
				sprintf(file_path,"%s/meter_id_%d/event_%d",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,event_class_type);
				sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
					
				time_now = time(NULL);
				fun_ret = get_event_data_all(&meter_comm_params,event_class_type);
				if(fun_ret<0)
				{
					met_poll_dbg_log(REPORT,"%-20s : Failed to get event data for type : %d from Meter Error Code : %d\n",
					fun_name,event_class_type,fun_ret);
					continue;
				}

				else
				{
					met_poll_dbg_log(INFORM,"%-20s : Recv Event for type : %d Data from meter. Time elasped : %ld sec\n",
					fun_name,event_class_type,time(NULL)-time_now);
				}
				
				convert_to_decoded_data(file_path, file_name, &gen_event_param_det[midx]);
			}
			
			met_poll_dbg_log(INFORM,"%-20s : To get all events type Total Time elasped : %ld sec\n",
			fun_name,event_class_type,time(NULL)-tot_eve_time);
		}
		else
		{
			p_redis_reply = redisCommand(p_redis_handler, "HMSET SerPort%dMet%dStatus VALUE %d",g_port_idx,midx,2);
			freeReplyObject(p_redis_reply);
		}
	}
	
	send_hc_msg();
	check_met_ser_num();
	
	/* Read Midnight */
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
				met_poll_dbg_log(INFORM,"%-20s : Midnight Need to read Obis Code flag enable\n",fun_name);
				if(read_meter_obis_code(midx)<0)
				{
					g_need_to_read_obis[midx]=1;
				}
				else
				{
					met_poll_dbg_log(INFORM,"%-20s : Midnight Recvd read Obis Code\n",fun_name);
					g_need_to_read_obis[midx]=0;
				}
			}
			
			send_hc_msg();
			time_now=time(NULL);
			memset(file_path,0,sizeof(file_path));
			memset(dir_path,0,sizeof(dir_path));
			memset(file_name,0,sizeof(file_name));
			
			clear_temp_lib_data(midx);
				
			send_hc_msg();
			time_now = time(NULL);
			fun_ret = get_midnight_data_all(&meter_comm_params);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to midnight data from Meter Error Code : %d\n",fun_name,fun_ret);
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Recv midnight Data from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
				
				sprintf(dir_path,"%s/meter_id_%d",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
				
				DIR 			*p_data_dir=NULL;
				struct dirent 	*p_dir_str=NULL;
	
				p_data_dir = opendir(dir_path);
				if ( p_data_dir == NULL )
				{
					met_poll_dbg_log(INFORM,"%-20s : Failed to opendir Error : %s\n",fun_name,strerror(errno));
					continue;
				}
				while ( (p_dir_str = readdir(p_data_dir)) != NULL )
				{
					if (( strcmp(p_dir_str->d_name,".") == 0 ) || ( strcmp(p_dir_str->d_name,"..") == 0 ))
					{
						continue;
					}
					if ( strstr(p_dir_str->d_name,"dp") != NULL)
					{
						sprintf(file_path,"%s/meter_id_%d/%s",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,p_dir_str->d_name);
						sprintf(file_name,"%s/meter_id_%d/%s",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,p_dir_str->d_name);
						convert_to_decoded_data(file_path, file_name, &gen_daily_prof_param_det[midx]);	
					}
				}
				
				closedir(p_data_dir);
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
	
	/* Billing */
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
				met_poll_dbg_log(INFORM,"%-20s : Billing Need to read Obis Code flag enable\n",fun_name);
				if(read_meter_obis_code(midx)<0)
				{
					g_need_to_read_obis[midx]=1;
				}
				else
				{
					met_poll_dbg_log(INFORM,"%-20s : Billing Recvd read Obis Code\n",fun_name);
					g_need_to_read_obis[midx]=0;
				}
			}
			
			send_hc_msg();
			time_now=time(NULL);
			clear_temp_lib_data(midx);
			send_hc_msg();
			time_now = time(NULL);
			fun_ret = get_billing_info(&meter_comm_params);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to get billing data from Meter Error Code : %d\n",fun_name,fun_ret);
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Recv billing Data from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
				
				memset(file_path,0,sizeof(file_path));
				memset(file_name,0,sizeof(file_name));
					
				sprintf(file_path,"%s/meter_id_%d/billing",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
				sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
				
				convert_to_decoded_data(file_path, file_name, &gen_bill_param_det[midx]);	
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
	
	/* Today's load survey data  */
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
				met_poll_dbg_log(INFORM,"%-20s : Today's LS data Need to read Obis Code flag enable\n",fun_name);
				if(read_meter_obis_code(midx)<0)
				{
					g_need_to_read_obis[midx]=1;
				}
				else
				{
					met_poll_dbg_log(INFORM,"%-20s : Today's LS data Recvd read Obis Code\n",fun_name);
					g_need_to_read_obis[midx]=0;
				}
			}
			
			send_hc_msg();
			time_now=time(NULL);
			send_hc_msg();
			time_t ls_curr_time=0;
			time(&ls_curr_time);
			
			struct tm *p_curr_time = localtime(&ls_curr_time);
			
			struct tm st_time,time_stamp,next_date_tm;
			time_t time_of_day=0,next_time_day=0;
			
			meter_comm_params.from.day = p_curr_time->tm_mday;
			meter_comm_params.from.month = p_curr_time->tm_mon+1;
			meter_comm_params.from.year = p_curr_time->tm_year+1900;
			meter_comm_params.from.hour = 0;
			meter_comm_params.from.minute = 4;
			meter_comm_params.from.second = 0;
			
			meter_comm_params.to.day = p_curr_time->tm_mday;
			meter_comm_params.to.month = p_curr_time->tm_mon+1;
			meter_comm_params.to.year = p_curr_time->tm_year+1900;
			meter_comm_params.to.hour = p_curr_time->tm_hour;
			meter_comm_params.to.minute = p_curr_time->tm_min;
			meter_comm_params.to.second = p_curr_time->tm_sec;
			
			clear_temp_lib_data(midx);
			time_now = time(NULL);
			fun_ret = get_ls_values_day_range(&meter_comm_params,1);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to get Current day ls data from Meter Error Code : %d\n",fun_name,fun_ret);
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Recv Current day ls Data from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
				
				sprintf(file_path,"%s/meter_id_%d/%02d_%02d_%04d",ROOT_DATA_DIR,
				g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,
				meter_comm_params.from.day,meter_comm_params.from.month,meter_comm_params.from.year);
				
				//sprintf(file_name,"%02d_%02d_%04d",meter_comm_params.from.day,meter_comm_params.from.month,meter_comm_params.from.year);
				sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
				append_in_exist_file(file_path, file_name, &gen_ls_param_det[midx]);
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
	
	/* Getting Prev load survey data */
	for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
	{
		send_hc_msg();
		g_midx=midx;
		
		if(dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable)
		{
			get_prev_ls_data(midx);
		}
	}
	
	/* Today's load survey data  */
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
				met_poll_dbg_log(INFORM,"%-20s : Last Today's LS data Need to read Obis Code flag enable\n",fun_name);
				if(read_meter_obis_code(midx)<0)
				{
					g_need_to_read_obis[midx]=1;
				}
				else
				{
					met_poll_dbg_log(INFORM,"%-20s : Last Today's LS data Recvd read Obis Code\n",fun_name);
					g_need_to_read_obis[midx]=0;
				}
			}
			
			send_hc_msg();
			time_now=time(NULL);
			send_hc_msg();
			time_t ls_curr_time=0;
			time(&ls_curr_time);
			
			struct tm *p_curr_time = localtime(&ls_curr_time);
			
			struct tm st_time,time_stamp,next_date_tm;
			time_t time_of_day=0,next_time_day=0;
			
			meter_comm_params.from.day = p_curr_time->tm_mday;
			meter_comm_params.from.month = p_curr_time->tm_mon+1;
			meter_comm_params.from.year = p_curr_time->tm_year+1900;
			meter_comm_params.from.hour = 0;
			meter_comm_params.from.minute = 4;
			meter_comm_params.from.second = 0;
			
			meter_comm_params.to.day = p_curr_time->tm_mday;
			meter_comm_params.to.month = p_curr_time->tm_mon+1;
			meter_comm_params.to.year = p_curr_time->tm_year+1900;
			meter_comm_params.to.hour = p_curr_time->tm_hour;
			meter_comm_params.to.minute = p_curr_time->tm_min;
			meter_comm_params.to.second = p_curr_time->tm_sec;
			
			clear_temp_lib_data(midx);
			time_now = time(NULL);
			fun_ret = get_ls_values_day_range(&meter_comm_params,1);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to get Current day ls data from Meter Error Code : %d\n",fun_name,fun_ret);
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Recv Current day ls Data from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
				
				sprintf(file_path,"%s/meter_id_%d/%02d_%02d_%04d",ROOT_DATA_DIR,
				g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,
				meter_comm_params.from.day,meter_comm_params.from.month,meter_comm_params.from.year);
				
				sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
				append_in_exist_file(file_path, file_name, &gen_ls_param_det[midx]);
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
	
	time_t curr_time ,ls_curr_time,time_of_day;
	struct tm st_time,time_stamp;
	
	time_t g_last_inst_read_time[MAX_NO_OF_METER_PER_PORT];
	time_t g_last_ls_read_time[MAX_NO_OF_METER_PER_PORT];
	time_t g_last_dp_read_time[MAX_NO_OF_METER_PER_PORT];
	time_t g_last_event_read_time[MAX_NO_OF_METER_PER_PORT];
	time_t g_last_bill_read_time[MAX_NO_OF_METER_PER_PORT];
		
	for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
	{
		 g_last_inst_read_time[midx] = time(NULL);
		 g_last_ls_read_time[midx] = time(NULL);
		 g_last_dp_read_time[midx] = time(NULL);
		 g_last_event_read_time[midx] = time(NULL);
		 g_last_bill_read_time[midx] = time(NULL);
	}
	
	struct tm *p_curr_time=NULL;
	
	g_midx=0;
	met_poll_dbg_log(REPORT,"%-20s : >>>>>Entering into Idle polling loop!!!!\n",fun_name);
	
	int32_t cnt=0, cnt1;
	while(0)
	{
		sleep(2);
		fun_ret = connect_to_meter(&meter_comm_params);
		if(fun_ret<0)
		{
			cnt++;
			met_poll_dbg_log(REPORT,"%-20s : Inside Idle Loop Failed to connect Meter Error Code : %d, Count : %d\n",fun_name,fun_ret,cnt);
		}
		else
		{
			cnt=0;
			met_poll_dbg_log(REPORT,"%-20s : >>>>>>>Connect Success\n",fun_name);
		}
		
		fun_ret = get_nameplate_details(&meter_comm_params, &name_plate_info[midx]);
		if(fun_ret<0)
		{
			cnt1++;
			met_poll_dbg_log(REPORT,"%-20s : Failed to get nameplate info from Meter Error Code : %d, cnt1 : %d\n",fun_name,fun_ret,cnt1);
		}
		else
		{
			cnt1=0;
			met_poll_dbg_log(REPORT,"%-20s : Recv Nameplate from meter !!!\n",fun_name);
		}		
	}
	
	/* Ideal Loop */
	while(1)
	{
		sleep(1);
		check_met_ser_num();
		
		fun_ret=0;
		for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
		{
			send_hc_msg();
			check_od_msg_request();
			
			g_midx=midx;
			met_poll_dbg_log(REPORT,"%-20s : g_midx : %d, midx : %d, Meter Enable Status : %d\n",
			fun_name,g_midx,midx,dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable);
			
			if(dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable)
			{
				delete_old_files(midx);
				
				curr_time = time(NULL);
				
				fill_meter_comm_params_det(&meter_comm_params,midx);
			
				fun_ret = connect_to_meter(&meter_comm_params);
				if(fun_ret<0)
				{
					met_poll_dbg_log(REPORT,"%-20s : Inside Idle Loop Failed to connect Meter Error Code : %d\n",fun_name,fun_ret);
					p_redis_reply = redisCommand(p_redis_handler, "HMSET SerPort%dMet%dStatus VALUE %d",g_port_idx,midx,0);
					freeReplyObject(p_redis_reply);
					continue;
				}
				else
				{
					p_redis_reply = redisCommand(p_redis_handler, "HMSET SerPort%dMet%dStatus VALUE %d",g_port_idx,midx,1);
					freeReplyObject(p_redis_reply);
				}

				met_poll_dbg_log(INFORM,"%-20s : Inside Idle Loop Getting NamePlate info from Meter\n",fun_name);
				memset(&name_plate_info[midx],0,sizeof(obis_name_plate_info_t));
				fun_ret = get_nameplate_details(&meter_comm_params, &name_plate_info[midx]);
				if(fun_ret<0)
				{
					met_poll_dbg_log(REPORT,"%-20s : Failed to get nameplate info from Meter Error Code : %d\n",fun_name,fun_ret);
					continue;
				}
				else
				{
					met_poll_dbg_log(REPORT,"%-20s : Recv Nameplate from meter !!!\n",fun_name);
					update_np_det_to_redis(&name_plate_info[midx],midx);
				}
			
				if(g_need_to_read_obis[midx]==1)
				{
					met_poll_dbg_log(REPORT,"%-20s : Inside Idle Loop Need to read obis flag Enable\n",fun_name);
					memset(&gen_inst_param_det[midx],0,sizeof(gen_params_det_t));
					memset(&gen_ls_param_det[midx],0,sizeof(gen_params_det_t));
					memset(&gen_bill_param_det[midx],0,sizeof(gen_params_det_t));
					memset(&gen_daily_prof_param_det[midx],0,sizeof(gen_params_det_t));
					memset(&gen_event_param_det[midx],0,sizeof(gen_params_det_t));
					
					fun_ret = get_obis_codes(&meter_comm_params,&gen_inst_param_det[midx],&gen_ls_param_det[midx],
					&gen_event_param_det[midx],&gen_bill_param_det[midx],&gen_daily_prof_param_det[midx]);
					if(fun_ret<0)
					{
						met_poll_dbg_log(REPORT,"%-20s : Inside Idle Loop Failed to get obis info from Meter Error Code : %d\n",fun_name,fun_ret);
						g_need_to_read_obis[midx]=1;
						continue;
					}
					else
					{
						met_poll_dbg_log(REPORT,"%-20s : Inside Idle Loop Recv obis info from Meter\n",fun_name);
						g_need_to_read_obis[midx]=0;
						
						get_prev_ls_data(midx);
					}
				}
				
				//if(dlms_dcu_config.dcu_poll_info.inst_poll_info.enable)
				if(1)
				{
					if((curr_time-g_last_inst_read_time[midx])>=REFF_INST_POLL_TIME)
					{
						time_t curr_inst_time;
						curr_inst_time=time(NULL);
						g_last_inst_read_time[midx]=curr_time;
						memset(&g_inst_data_val,0,sizeof(g_inst_data_val));
		
						//fun_ret = get_inst_values(&meter_comm_params, &g_inst_data_val);
						
						met_poll_dbg_log(INFORM,"%-20s : Inside Ideal Loop Getting Inst data\n",fun_name);
						fun_ret = get_inst_values(&meter_comm_params, gen_data_val_info);
						if(fun_ret<0)
						{
							met_poll_dbg_log(INFORM,"%-20s : Failed to get inst value. Error Code : %d\n",fun_name,fun_ret);
							
							continue;
						}
						else
						{
							met_poll_dbg_log(INFORM,"%-20s : Recv Inst Data, Time Resp taken in sec : %ld\n",
							fun_name,(time(NULL)-curr_inst_time));
							
							p_redis_reply = redisCommand(p_redis_handler, "HMSET SerPort%dMet%dStatus VALUE %d",g_port_idx,midx,1);
							freeReplyObject(p_redis_reply);
							
							p_redis_reply = redisCommand(p_redis_handler,"hmset INST SINGLE_INST_RESP_TIME %d",(time(NULL)-curr_inst_time));
							freeReplyObject(p_redis_reply);	
								
							g_inst_resp_time[midx][g_inst_resp_time_cnt]=(time(NULL)-curr_inst_time);
							g_inst_resp_time_cnt++;
							if(g_inst_resp_time_cnt>MAX_RESP_TIME_ENTRY)
							{
								g_inst_resp_time_cnt=0;
								g_avg_inst_resp_time=0;
								
								for(idx=0; idx<MAX_RESP_TIME_ENTRY; idx++)
								{
									g_avg_inst_resp_time = g_avg_inst_resp_time+g_inst_resp_time[midx][idx];
								}

								met_poll_dbg_log(INFORM,"%-20s : Avg Time for Last 50 Inst data type qry-response : %ld\n",
								fun_name,g_avg_inst_resp_time);
								
								p_redis_reply = redisCommand(p_redis_handler,"hmset INST AVG_INST_RESP_TIME %d",g_avg_inst_resp_time);
								
								freeReplyObject(p_redis_reply);				
							}
							
							//memcpy(&g_all_inst_param_obis_val,&meter_comm_params.meter_response,sizeof(g_all_inst_param_obis_val));
							//send_inst_det_to_redis(&g_inst_data_val,sizeof(inst_val_info_t),INST_INFO_KEY,midx);
							send_inst_det_to_redis(INST_INFO_KEY,midx);
						}
					}
				}
				
				if(dlms_dcu_config.dcu_poll_info.bill_poll_info.enable)
				{
					if((curr_time-g_last_bill_read_time[midx])>dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_hr*60*60)
					{
						met_poll_dbg_log(INFORM,"%-20s : Inside Ideal Loop Getting Billing data\n",fun_name);
						clear_temp_lib_data(midx);
							
						time_t curr_bill_time=time(NULL);
						send_hc_msg();
						g_last_bill_read_time[midx]=curr_time;
						
						fun_ret = get_billing_info(&meter_comm_params);
						if(fun_ret<0)
						{
							met_poll_dbg_log(INFORM,"%-20s : Failed to get Billing Profile value. Error Code : %d\n",fun_name,fun_ret);
							continue;
						}
						else
						{
							met_poll_dbg_log(INFORM,"%-20s : Inside Ideal Loop Recvd Billing data, Time elasped : %ld\n",
							fun_name,time(NULL)-curr_bill_time);
							memset(file_path,0,sizeof(file_path));
							memset(file_name,0,sizeof(file_name));
							
							sprintf(file_path,"%s/meter_id_%d/billing",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
							//sprintf(file_name,"%s","billing");
							sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
							convert_to_decoded_data(file_path, file_name, &gen_bill_param_det[midx]);
				
							g_bill_resp_time[midx][g_bill_resp_time_cnt]=(time(NULL)-curr_bill_time);
							p_redis_reply = redisCommand(p_redis_handler,"hmset BILL SINGLE_BILL_RESP_TIME %d",
							(time(NULL)-curr_bill_time));
							freeReplyObject(p_redis_reply);
							
							g_bill_resp_time_cnt++;
							if(g_bill_resp_time_cnt>MAX_RESP_TIME_ENTRY)
							{
								g_bill_resp_time_cnt=0;
								g_avg_bill_resp_time=0;
								
								for(idx=0; idx<MAX_RESP_TIME_ENTRY; idx++)
								{
									g_avg_bill_resp_time = g_avg_bill_resp_time+g_bill_resp_time[midx][idx];
								}
								
								met_poll_dbg_log(INFORM,"%-20s : Avg Time for Last 50 Billing data type qry-response : %ld\n",
								fun_name,g_avg_bill_resp_time);
								//printf("Avg Time for Last 50 Billing data type qry-response : %ld\n",g_avg_bill_resp_time);
								
								p_redis_reply = redisCommand(p_redis_handler,"hmset BILL AVG_BILL_RESP_TIME %d",g_avg_bill_resp_time);
								
								freeReplyObject(p_redis_reply);				
							}
						}
					}
				}
					
				//if(dlms_dcu_config.dcu_poll_info.event_poll_info.enable)
				if(1)
				{
					if((curr_time-g_last_event_read_time[midx])>REFF_EVENT_POLL_TIME)
					{
						g_last_event_read_time[midx]=curr_time;
						uint8_t event_class_type=0;
						
						for(event_class_type=0; event_class_type<7; event_class_type++)
						{
							time_t curr_event_time=time(NULL);
							met_poll_dbg_log(INFORM,"%-20s : Inside Ideal Loop Getting Event data for type : %d\n",
							fun_name,event_class_type);
							
							clear_temp_lib_data(midx);
							
							fun_ret = get_event_data(&meter_comm_params,event_class_type);
							if(fun_ret<0)
							{
								met_poll_dbg_log(INFORM,"%-20s : Failed to get Event data for event class : %d, Error Code : %d\n",fun_name,event_class_type,fun_ret);
								//printf("Failed to get Event data for event class : %d, Error Code : %d\n",event_class_type,fun_ret);
								continue;
							}
							else
							{
								met_poll_dbg_log(INFORM,"%-20s : Inside Ideal Loop Recvd Event data for type : %d, Time elasped : %ld\n",
								fun_name,event_class_type,time(NULL)-curr_event_time);
							
								sprintf(file_path,"%s/meter_id_%d/event_%d",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,event_class_type);
								
								//sprintf(file_name,"event_%d",event_class_type);
								
								sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
								convert_to_decoded_data(file_path, file_name, &gen_event_param_det[midx]);
								
								g_event_resp_time[midx][g_event_resp_time_cnt]=(time(NULL)-curr_event_time);
								p_redis_reply = redisCommand(p_redis_handler,"hmset EVENT EID_%d_SINGLE_EVENT_RESP_TIME %d",
								(time(NULL)-curr_event_time));
								freeReplyObject(p_redis_reply);
							
								g_event_resp_time_cnt++;
								if(g_event_resp_time_cnt>MAX_RESP_TIME_ENTRY)
								{
									g_event_resp_time_cnt=0;
									g_avg_event_resp_time=0;
									
									for(idx=0; idx<MAX_RESP_TIME_ENTRY; idx++)
									{
										g_avg_event_resp_time = g_avg_event_resp_time+g_event_resp_time[midx][idx];
									}
									
									met_poll_dbg_log(INFORM,"%-20s : Avg Time for Last 50 Event data type qry-response : %ld\n",fun_name,g_avg_event_resp_time);
									
									//printf("Avg Time for Last 50 Event data type qry-response : %ld\n",g_avg_event_resp_time);
									
									p_redis_reply = redisCommand(p_redis_handler,"hmset EVENT EID_%d_AVG_EVENT_RESP_TIME %d",event_class_type,g_avg_event_resp_time);
									
									freeReplyObject(p_redis_reply);				
								}
								
								char event_key_buff[32];
								memset(event_key_buff,0,sizeof(event_key_buff));
								sprintf(event_key_buff,"%s_%d",EVENT_INFO_KEY,event_class_type);
							}
						}
					}
				}
					
				if(dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.enable)
				{
					if((curr_time-g_last_dp_read_time[midx])>dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_hr*60*60)
					{
						time_t curr_dp_time=time(NULL);
						met_poll_dbg_log(INFORM,"%-20s : Inside Ideal Loop Getting Midnight data\n",fun_name);
							
						clear_temp_lib_data(midx);
							
						send_hc_msg();
						g_last_dp_read_time[midx]=curr_time;
						
						fun_ret = get_midnight_data(&meter_comm_params);
						if(fun_ret<0)
						{
							met_poll_dbg_log(INFORM,"%-20s : Failed to get Daily Profile value. Error Code : %d\n",fun_name,fun_ret);
							//printf("Failed to get Daily Profile value. Error Code : %d\n",fun_ret);
							continue;
						}
						else
						{
							met_poll_dbg_log(INFORM,"%-20s : Inside Ideal Loop Recvd Midnight data, time elasped : %ld\n",
							fun_name,time(NULL)-curr_dp_time);
							
							g_dp_resp_time[midx][g_dp_resp_time_cnt]=(time(NULL)-curr_dp_time);
							p_redis_reply = redisCommand(p_redis_handler,"hmset DP SINGLE_DP_RESP_TIME %d",
							(time(NULL)-curr_dp_time));
							
							memset(file_path,0,sizeof(file_path));
							memset(file_name,0,sizeof(file_name));
								
							sprintf(file_path,"%s/meter_id_%d",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
							
							DIR 			*p_data_dir=NULL;
							struct dirent 	*p_dir_str=NULL;
				
							//sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
							sprintf(dir_path,"%s/meter_id_%d",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
							p_data_dir = opendir(dir_path);
							if ( p_data_dir == NULL )
							{
								met_poll_dbg_log(INFORM,"%-20s : Failed to opendir Error : %s\n",fun_name,strerror(errno));
								continue;
							}
							while ( (p_dir_str = readdir(p_data_dir)) != NULL )
							{
								if (( strcmp(p_dir_str->d_name,".") == 0 ) || ( strcmp(p_dir_str->d_name,"..") == 0 ))
								{
									continue;
								}
								if ( strstr(p_dir_str->d_name,"dp") != NULL)
								{
									sprintf(file_path,"%s/meter_id_%d/%s",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,p_dir_str->d_name);

									sprintf(file_name,"%s/meter_id_%d/%s",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,p_dir_str->d_name);
									
									convert_to_decoded_data(file_path, file_name, &gen_daily_prof_param_det[midx]);	
								}
							}
							
							closedir(p_data_dir);
				
							g_dp_resp_time_cnt++;
							if(g_dp_resp_time_cnt>MAX_RESP_TIME_ENTRY)
							{
								g_dp_resp_time_cnt=0;
								g_avg_dp_resp_time=0;
								
								for(idx=0; idx<MAX_RESP_TIME_ENTRY; idx++)
								{
									g_avg_dp_resp_time = g_avg_dp_resp_time+g_ls_resp_time[midx][idx];
								}
								
								met_poll_dbg_log(INFORM,"%-20s : Avg Time for Last 50 Daily Profile data type qry-response : %ld\n",fun_name,g_avg_dp_resp_time);
								//printf("Avg Time for Last 50 Daily Profile data type qry-response : %ld\n",g_avg_dp_resp_time);
								
								p_redis_reply = redisCommand(p_redis_handler,"hmset DP AVG_DP_RESP_TIME %d",g_avg_dp_resp_time);
								
								freeReplyObject(p_redis_reply);				
							}
						}
					}
				}
				
				//if(dlms_dcu_config.dcu_poll_info.ls_poll_info.enable)
				if(1)
				{

					if((curr_time-g_last_ls_read_time[midx])>REFF_LS_POLL_TIME)
					{
						time_t curr_ls_time=time(NULL);
						met_poll_dbg_log(INFORM,"%-20s : Inside Ideal Loop Getting Load survey last 1 Hour data\n",fun_name);
							
						clear_temp_lib_data(midx);
							
						send_hc_msg();
						g_last_ls_read_time[midx]=curr_time;
						
						time(&ls_curr_time);
	
						p_curr_time = localtime(&ls_curr_time);
	
						st_time.tm_mday = p_curr_time->tm_mday;
						st_time.tm_mon =  p_curr_time->tm_mon;
						st_time.tm_year = p_curr_time->tm_year;
						st_time.tm_hour = p_curr_time->tm_hour;
						st_time.tm_min = p_curr_time->tm_min;
						st_time.tm_sec = p_curr_time->tm_sec;
	
						time_of_day = mktime(&st_time);
	
						time_of_day -= (1*60*60);
	
						localtime_r(&time_of_day,&time_stamp);

						meter_comm_params.to.day = st_time.tm_mday;
						meter_comm_params.to.month = st_time.tm_mon+1;
						meter_comm_params.to.year = st_time.tm_year+1900;
						meter_comm_params.to.hour = st_time.tm_hour;
						meter_comm_params.to.minute = st_time.tm_min;
						meter_comm_params.to.second = st_time.tm_sec;
							
						meter_comm_params.from.day = time_stamp.tm_mday;
						meter_comm_params.from.month = time_stamp.tm_mon+1;
						meter_comm_params.from.year = time_stamp.tm_year+1900;
						meter_comm_params.from.hour = time_stamp.tm_hour;
						meter_comm_params.from.minute = time_stamp.tm_min;
						meter_comm_params.from.second = time_stamp.tm_sec;
		
						fun_ret = get_ls_values_block_range(&meter_comm_params, 4);
						if(fun_ret<0)
						{
							met_poll_dbg_log(INFORM,"%-20s : Failed to get prev load survey data. Error Code : %d\n",fun_name,fun_ret);
							//printf("Failed to get prev load survey data. Error Code : %d\n",fun_ret);
							continue;
						}
						else
						{
							met_poll_dbg_log(INFORM,"%-20s : Inside Ideal Loop  Recv Ls Time Resp taken in sec : %ld\n",
							fun_name,(time(NULL)-curr_ls_time));
							
							p_redis_reply = redisCommand(p_redis_handler,"hmset LS SINGLE_LS_RESP_TIME %d",
							(time(NULL)-curr_ls_time));
							
							//printf(">>>Ls Time Resp taken in sec : %ld\n",(time(NULL)-curr_ls_time));
							g_ls_resp_time[midx][g_ls_resp_time_cnt]=(time(NULL)-curr_ls_time);
							g_ls_resp_time_cnt++;
							if(g_ls_resp_time_cnt>MAX_RESP_TIME_ENTRY)
							{
								g_ls_resp_time_cnt=0;
								g_avg_ls_resp_time=0;
								
								for(idx=0; idx<MAX_RESP_TIME_ENTRY; idx++)
								{
									g_avg_ls_resp_time = g_avg_ls_resp_time+g_ls_resp_time[midx][idx];
								}
								
								met_poll_dbg_log(INFORM,"%-20s : Avg Time for Last 50 LS data type qry-response : %ld\n",fun_name,g_avg_ls_resp_time);
								
								//printf("Avg Time for Last 50 LS data type qry-response : %ld\n",g_avg_ls_resp_time);
								
								p_redis_reply = redisCommand(p_redis_handler,"hmset LS AVG_LS_RESP_TIME %d",g_avg_ls_resp_time);
								
								freeReplyObject(p_redis_reply);				
							}
							
							sprintf(file_path,"%s/meter_id_%d/%02d_%02d_%04d",ROOT_DATA_DIR,
							g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,
							meter_comm_params.from.day,meter_comm_params.from.month,meter_comm_params.from.year);
							
							//sprintf(file_name,"%02d_%02d_%04d",meter_comm_params.from.day,meter_comm_params.from.month,meter_comm_params.from.year);
							sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
							//sprintf(file_name,"%s/cms_lib_data",ROOT_LIB_DATA_DIR);
							append_in_exist_file(file_path, file_name, &gen_ls_param_det[midx]);
						}
					}
				}
			}
			else
			{
				p_redis_reply = redisCommand(p_redis_handler, "HMSET SerPort%dMet%dStatus VALUE %d",g_port_idx,midx,2);
				freeReplyObject(p_redis_reply);
			}
		}
	}
	
	redisFree(p_redis_handler);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: send_hc_msg()
*Input Parameters 			: Void
*Output Parameters 			: None.
*Return	Value				: Void.
*Description 				: To send HC Message to Redis server on a periodic time.
********************************************************************************************************/
void send_hc_msg(void)
{
	time_t curr_time=time(NULL);
	
	if((curr_time-g_last_hc_msg_time)>=15)
	{
		g_last_hc_msg_time=curr_time;
		p_redis_reply = redisCommand(p_redis_handler,"hmset P%d_dlms_poll_proc_hc_msg updatetime %d",g_port_idx,curr_time);
		
		static char fun_name[]="send_hc_msg()";
		if(p_redis_reply!=NULL)
		{
			met_poll_dbg_log(REPORT,"%-20s : !!!!HC Send msg Status : %s\n",fun_name,p_redis_reply->str);
		}
		
		freeReplyObject(p_redis_reply);
		
		met_poll_dbg_log(REPORT,"%-20s : >>>>Sending HC Msg to Redis server time in sec : %ld\n",fun_name,curr_time);
	}
}

/**************************************************************************************************
*Function 					: delete_old_files()
*Input Parameters 			: Meter Index
*Output Parameters 			: None.
*Return	Value				: Success/Failure.
*Description 				: To delete old file , which is more than 46 days old.
********************************************************************************************************/
int32_t delete_old_files(uint8_t midx)
{
	static char 	fun_name[]="delete_old_files()";
	
	DIR 			*p_data_dir=NULL;
	struct dirent 	*p_dir_str=NULL;
	char 			file_name[64],dir_data_path[64];
	time_t 			curr_time,time_of_day;
	struct tm 		str_time,time_stamp;
	int32_t 		day,mon,year;
	
	g_midx=midx;
	time(&curr_time);
	localtime_r(&curr_time,&time_stamp);

	time_of_day = time(NULL);

	memset(dir_data_path,0,sizeof(dir_data_path));
	
	sprintf(dir_data_path,"%s/meter_id_%d",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
	p_data_dir = opendir(dir_data_path);
	if ( p_data_dir == NULL )
	{
		printf("Failed to opendir %s\n",strerror(errno));
		return RET_NO_RESP;

	}
	while ( (p_dir_str = readdir(p_data_dir)) != NULL )
	{
		//printf("File name %s\n",p_dir_str->d_name);
		if (( strcmp(p_dir_str->d_name,".") == 0 ) || ( strcmp(p_dir_str->d_name,"..") == 0 ))
		{
			continue;
		}
		if (( strstr(p_dir_str->d_name,"event") != NULL)  || 
			( strstr(p_dir_str->d_name,"dp") != NULL) ||
			( strstr(p_dir_str->d_name,"bill") != NULL) ||
			( strstr(p_dir_str->d_name,".tgz") != NULL)||
			( strstr(p_dir_str->d_name,"od")!= NULL) 
			)
		{
			continue;
		}
		
		memset(file_name,0,sizeof(file_name));
		sprintf(file_name,"%s/%s",dir_data_path,p_dir_str->d_name);
		
		day = mon = year = 0;
		
		get_date(p_dir_str->d_name,&day,&mon,&year);

		str_time.tm_mday = day;
		str_time.tm_mon =  mon - 1;
		str_time.tm_year = year - 1900;
		str_time.tm_hour = 0;
		str_time.tm_min = 0;
		str_time.tm_sec = 0;

		time_of_day = mktime(&str_time);
		localtime_r(&time_of_day, &time_stamp);
		
		if ( ( curr_time - time_of_day ) >= OLD_DATA_FILES_TIME*24*60*60 )
		{
			met_poll_dbg_log(INFORM,"%-20s : Diff Time in day : %d, Time to delete the file : %s\n",
			fun_name,((curr_time - time_of_day)/(24*60*60)),file_name);
			
			remove(file_name);
		}
	}
	
	closedir(p_data_dir);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: check_ls_file_avl()
*Input Parameters 			: Meter Idx, Ls File Name.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To check complete load survey data file.
********************************************************************************************************/
int32_t check_ls_file_avl(char* file_name, uint8_t midx)
{
	/* char 	time_entry[32]; */
	FILE	*p_file_ptr = NULL;
	static char fun_name[]="check_ls_file_avl()";
	uint16_t	line_cnt = 0;
	
	p_file_ptr = fopen(file_name,"r");
	if(p_file_ptr == NULL)
	{
		met_poll_dbg_log(REPORT,"%-20s : File : %s is not opened Read mode, Error : %s\n",fun_name,file_name,strerror(errno));
		return -1;
	}
	else
	{
		
		char 		read_line[256];
		while(fgets(read_line,256,p_file_ptr)!=NULL)
		{
			line_cnt++;
			if(line_cnt>=(g_num_blocks_blk_data[midx]+1))
			{
				met_poll_dbg_log(INFORM,"%-20s : ::: file_name : %s All entry  found \n",fun_name,file_name);
				
				fclose(p_file_ptr);
				
				return 1;
			}
			/* else
			{
				fclose(p_file_ptr);
				
				remove(file_name);
				
				return 0;
			} */
			memset(read_line,0,sizeof(read_line));
		}
	}

	fclose(p_file_ptr);
	
	met_poll_dbg_log(INFORM,"%-20s : Total Entry Found : %d, MeterGives : %d\n",fun_name,line_cnt,g_num_blocks_blk_data[midx]);
	met_poll_dbg_log(INFORM,"%-20s : ::: file_name : %s Not All entry  found, Removing file\n",fun_name,file_name);
	
	remove(file_name);
	
	return 0;
}

/**************************************************************************************************
*Function 					: get_date()
*Input Parameters 			: Ls File Name, day,month,year.
*Output Parameters 			: day,month,year.
*Return	Value				: void.
*Description 				: To get date info from load survey data file.
********************************************************************************************************/
void get_date(char *p_file_name,int *day,int *mon,int *year)
{
	char *token;
	char *delim = "_";
	char str[4][8];
	int idx = 0;
	
	memset(str,0,sizeof(str));
	token = strtok(p_file_name, delim);
	while( token != NULL )
	{
		memset(str[idx],0,8);
		strcpy(str[idx],token);
		token = strtok(NULL,delim);
		//printf("Token %d - %s\n",i,str[i]);
		idx++;
	}
	
	*day = atoi(str[0]);
	*mon = atoi(str[1]);
	*year = atoi(str[2]);

	//printf("day : %d mon : %d year : %d\n",*day,*mon,*year);

	return;
}

/**************************************************************************************************
*Function 					: print_val_scal_onis_val_info()
*Input Parameters 			: pointer of valobis scalarobis and scalar value.
*Output Parameters 			: Void.
*Return	Value				: void.
*Description 				: To print the obis info.
********************************************************************************************************/
void print_val_scal_onis_val_info(uint8_t* val_obis, uint8_t* scalar_obis, int8_t scalar_val)
{
	static char fun_name[]="val_obis_det()";
	
	met_poll_dbg_log(INFORM,"%-20s : ValObis : %d.%d.%d.%d.%d.%d, ScalObis : %d.%d.%d.%d.%d.%d, ScalVal : %d\n",fun_name,
	val_obis[0],val_obis[1],val_obis[2],val_obis[3],val_obis[4],val_obis[5],
	scalar_obis[0],scalar_obis[1],scalar_obis[2],scalar_obis[3],scalar_obis[4],scalar_obis[5],scalar_val);
}

/**************************************************************************************************
*Function 					: get_prev_met_ser_num()
*Input Parameters 			: Void.
*Output Parameters 			: Void.
*Return	Value				: void.
*Description 				: To get previous meter sreial number.
********************************************************************************************************/
void get_prev_met_ser_num(void)
{
	static char fun_name[]="get_prev_met_ser_num()";
	uint8_t 	midx=0;
	memset(g_prev_meter_ser_info,0,sizeof(g_prev_meter_ser_info));
	
	for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
	{
		if(!dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable)
			continue;
		
		p_redis_reply = redisCommand(p_redis_handler, "HMGET Port%dMet%dSerNum SER_NUM",g_port_idx,midx);
		if(p_redis_reply!=NULL)
		{
			if(p_redis_reply->element[0]->str!=NULL)
			{
				strcpy(g_prev_meter_ser_info[midx],p_redis_reply->element[0]->str);
			}
		}
		
		met_poll_dbg_log(INFORM,"%-20s : %d > From Redis Meter Serial : %s\n",fun_name,midx+1,g_prev_meter_ser_info[midx]);
	}
}

/**************************************************************************************************
*Function 					: check_met_ser_num()
*Input Parameters 			: Void.
*Output Parameters 			: Void.
*Return	Value				: void.
*Description 				: To check meter sreial number mismatch.
********************************************************************************************************/
void check_met_ser_num(void)
{
	static char fun_name[]="check_met_ser_num()";
	uint8_t 	midx=0;
	struct stat dir_st = {0};
	
	memset(g_curr_meter_ser_info,0,sizeof(g_curr_meter_ser_info));
	
	for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
	{
		if(!dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable)
			continue;
		
		p_redis_reply = redisCommand(p_redis_handler, "HMGET Port%dMet%dSerNum SER_NUM",g_port_idx,midx);
		if(p_redis_reply!=NULL)
		{
			if(p_redis_reply->element[0]->str!=NULL)
			{
				strcpy(g_curr_meter_ser_info[midx],p_redis_reply->element[0]->str);
			}
		}
	}
		
	for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
	{
		g_midx=midx;
		if(!dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable)
			continue;
		
		if(strlen(g_curr_meter_ser_info[midx])==0)
		{
			g_midx=midx;
			met_poll_dbg_log(INFORM,"%-20s : Current Meter SerNum is empty, Move to check next.\n",fun_name);
			continue;
		}
		
		if(strcmp(g_curr_meter_ser_info[midx], g_prev_meter_ser_info[midx])==0)
		{
			g_midx=midx;
			met_poll_dbg_log(INFORM,"%-20s : Both meter serial num are same.\n",fun_name);
		}
		else
		{
			if(strlen(g_prev_meter_ser_info[midx])==0)
			{
				g_midx=midx;
				met_poll_dbg_log(INFORM,"%-20s : Prev Meter SerNum is empty, Move to check next.\n",fun_name);
				continue;
			}
		
			char del_dir_cnt[32];
			
			g_midx=midx;
			met_poll_dbg_log(INFORM,"%-20s : Meter Serial num changed. Curr Meter ser : %s ,Prev Meter ser num was : %s\n",
			fun_name,g_curr_meter_ser_info[midx],g_prev_meter_ser_info[midx]);
			
			memset(del_dir_cnt,0,sizeof(del_dir_cnt));
			
			met_poll_dbg_log(INFORM,"%-20s : Deleting dir_path : %s/meter_id_%d\n",
			fun_name,ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
			
			sprintf(del_dir_cnt,"rm -rf %s/meter_id_%d/*",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
			system(del_dir_cnt);

			char curr_ls_file_path[64];
			memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));

			memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
			sprintf(curr_ls_file_path,"%s/meter_id_%d/od",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
			
			if (stat(curr_ls_file_path, &dir_st) == -1) 
			{
				if( (mkdir(g_data_dir_path,0777) ) < 0 )					
				{
					met_poll_dbg_log(INFORM,"%-20s : Created Root ls OD data dir : %s\n",fun_name,g_data_dir_path);
				}
			}

			g_need_to_read_obis[midx]=1;
		}
	}
	
	int8_t need_to_store_flag=0;
	
	for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
	{
		g_midx=midx;
		if(!dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable)
			continue;
		
		if(strlen(g_curr_meter_ser_info[midx]))
		{
			need_to_store_flag = 1;
		}
	}
	
	if(need_to_store_flag)
	{
		memcpy(g_prev_meter_ser_info,g_curr_meter_ser_info,sizeof(g_prev_meter_ser_info));
	}
}

/**************************************************************************************************
*Function 					: clear_temp_lib_data()
*Input Parameters 			: Meter Index.
*Output Parameters 			: Void.
*Return	Value				: void.
*Description 				: To clear temp lib data in a directory.
********************************************************************************************************/
void clear_temp_lib_data(uint8_t midx)
{
	static char fun_name[]="del_temp_lib_data()";
	char cms_lib_data[128];
	char dir_data_path[128];
	FILE *p_file_ptr;
	DIR 			*p_data_dir=NULL;
	struct dirent 	*p_dir_str=NULL;
	
	memset(cms_lib_data,0,sizeof(cms_lib_data));
	memset(dir_data_path,0,sizeof(dir_data_path));
	
	sprintf(dir_data_path,"%s/meter_id_%d",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
	p_data_dir = opendir(dir_data_path);
	if ( p_data_dir == NULL )
	{
		met_poll_dbg_log(REPORT,"%-20s : Failed to opendir : %s, Error : %s\n",fun_name,dir_data_path,strerror(errno));
		return ;
	}
	
	while ( (p_dir_str = readdir(p_data_dir)) != NULL )
	{
		if (( strcmp(p_dir_str->d_name,".") == 0 ) || ( strcmp(p_dir_str->d_name,"..") == 0 ))
		{
			continue;
		}
		else
		{
			sprintf(cms_lib_data,"%s/%s",dir_data_path,p_dir_str->d_name);
			remove(cms_lib_data);
			/* p_file_ptr = fopen(cms_lib_data,"w");
			if(p_file_ptr!=NULL)
				fclose(p_file_ptr); */
		}					
	}
	closedir(p_data_dir);
		
	//sprintf(cms_lib_data,"rm -rf %s/meter_id_%d/*",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
	//sprintf(cms_lib_data,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
	
	met_poll_dbg_log(REPORT,"%-20s : Deleting Lib Data Dir Content : %s/meter_id_%d\n",
	fun_name,ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
	
	//system(cms_lib_data);
}

/**************************************************************************************************
*Function 					: get_prev_ls_data()
*Input Parameters 			: Meter Index.
*Output Parameters 			: Void.
*Return	Value				: Success/Failure.
*Description 				: To get previous load survey data from meter.
********************************************************************************************************/
int get_prev_ls_data(uint8_t midx)
{
	static char fun_name[]="get_prev_ls_data()";
	int32_t 		fun_ret=-1,idx=0;
	time_t 			ls_curr_time=0;
	char 			file_path[64];
	char 			file_name[64];
	time(&ls_curr_time);

	struct tm *p_curr_time = localtime(&ls_curr_time);
	
	struct tm st_time,time_stamp,next_date_tm;
	time_t time_of_day=0,next_time_day=0;
	
	if(dlms_dcu_config.dlms_dcu_info.read_prev_ls_data==1)
	{
		st_time.tm_mday = p_curr_time->tm_mday;
		st_time.tm_mon =  p_curr_time->tm_mon;
		st_time.tm_year = p_curr_time->tm_year;
		st_time.tm_hour = 0;
		st_time.tm_min = 0;
		st_time.tm_sec = 0;

		time_of_day = mktime(&st_time);
		time_of_day -= (24*60*60);
		localtime_r(&time_of_day,&time_stamp);
		
		time_t tot_time_now=time(NULL);
		
		for(idx=0; idx<LAST_NUM_DAYS_LS_READ; idx++)
		{
			memset(file_path,0,sizeof(file_path));
			memset(file_name,0,sizeof(file_name));
			
			clear_temp_lib_data(midx);
			
			send_hc_msg();
			
			localtime_r(&time_of_day,&time_stamp);
				
			next_time_day =  time_of_day + 60*60*24;
			localtime_r(&next_time_day,&next_date_tm);
			
			meter_comm_params.from.day = time_stamp.tm_mday;
			meter_comm_params.from.month = time_stamp.tm_mon+1;
			meter_comm_params.from.year = time_stamp.tm_year+1900;
			meter_comm_params.from.hour = 0;
			meter_comm_params.from.minute = 4;
			meter_comm_params.from.second = 0;
				
			meter_comm_params.to.day = next_date_tm.tm_mday;
			meter_comm_params.to.month = next_date_tm.tm_mon+1;
			meter_comm_params.to.year = next_date_tm.tm_year+1900;
			meter_comm_params.to.hour = 0;
			meter_comm_params.to.minute = 3;
			meter_comm_params.to.second = 0;
			
			sprintf(file_path,"%s/meter_id_%d/%02d_%02d_%04d",ROOT_DATA_DIR,
				g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1,
				meter_comm_params.from.day,meter_comm_params.from.month,meter_comm_params.from.year);
				
			if(check_ls_file_avl(file_path,midx)==1)
			{
				met_poll_dbg_log(REPORT,"%-20s : Data File Present : %s\n",fun_name,file_path);
				time_of_day = time_of_day-(60*60*24);
				continue;
			}
			
			fill_meter_comm_params_det(&meter_comm_params,midx);

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
			
			if(g_need_to_read_obis[midx]==1)
			{
				if(read_meter_obis_code(midx)<0)
				{
					g_need_to_read_obis[midx]=1;
				}
				else
				{
					g_need_to_read_obis[midx]=0;
				}
			}

			time_t time_now = time(NULL);
			time_t read_inst_time_now = time(NULL);
			fun_ret = get_ls_values_day_range(&meter_comm_params,1);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to prev day ls data from Meter Error Code : %d\n",
				fun_name,midx,fun_ret);
				
				time_of_day = time_of_day-(60*60*24);
				continue;
			}
			else
			{
				g_midx = midx;
				met_poll_dbg_log(REPORT,"%-20s : DayIdx : %d, Recv Prev day ls data for day : %02d_%02d_%04d\n",
				fun_name,idx+1,meter_comm_params.from.day,meter_comm_params.from.month,meter_comm_params.from.year);
				
				met_poll_dbg_log(INFORM,"%-20s : Total Time taken to get 1 day ls data : %ld\n",fun_name,time(NULL)-time_now);
				
				//sprintf(file_name,"%02d_%02d_%04d",meter_comm_params.from.day,meter_comm_params.from.month,meter_comm_params.from.year);
				sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
				
				struct stat file_st;
				
				if(stat(file_name,&file_st)==-1)
				{
					met_poll_dbg_log(INFORM,"%-20s : Missing Input Library Data File : %s\n",fun_name,file_name);
				}
				else
				{
					met_poll_dbg_log(INFORM,"%-20s : Writing Load Survey Data File : %s\n",fun_name,file_path);
					append_in_exist_file(file_path, file_name, &gen_ls_param_det[midx]);
				}
			}
			
			time_of_day = time_of_day-(60*60*24);
			
			time_now = time(NULL);
			
			g_midx = midx;
			get_inst_data_for_all_met();
			
			g_midx = midx;
			met_poll_dbg_log(INFORM,"%-20s : Total Time taken to get Inst data for all Meters : %ld\n",fun_name,time(NULL)-time_now);
			
			met_poll_dbg_log(INFORM,"%-20s : Total Time taken to get Inst data for all Meters+1 day ls : %ld\n",
			fun_name,time(NULL)-read_inst_time_now);
		}
		
		met_poll_dbg_log(REPORT,"%-20s : Total Time taken to get all prev day ls data : %ld\n",fun_name,time(NULL)-tot_time_now);
	}
	else
	{
		met_poll_dbg_log(REPORT,"%-20s : To read prev LS data flag is disable!!!\n",fun_name);
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: fill_meter_comm_params_det()
*Input Parameters 			: Meter Comm Param structure & Meter Index.
*Output Parameters 			: Void.
*Return	Value				: Success/Failure.
*Description 				: To get previous load survey data from meter.
********************************************************************************************************/
void fill_meter_comm_params_det(meter_comm_params_t *meter_comm_params, uint8_t midx)
{
	static char fun_name[]="fill_params_det()";

	//clear_temp_lib_data(midx);

	meter_comm_params->inf_type=INF_SERIAL;
	meter_comm_params->meter_type=dlms_dcu_config.dlms_dcu_info.meter_type;
	meter_comm_params->meter_addr_format=dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].meter_addr_size;
	
	meter_comm_params->meter_id=dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].meter_addr;

	memcpy(meter_comm_params->interface_params,(char*)&dlms_dcu_config.ser_prot_cfg.ser_prot_param[g_port_idx],sizeof(dlms_dcu_config.ser_prot_cfg.ser_prot_param[g_port_idx]));
	
	//sprintf(file_name,"%s/meter_id_%d/cms_lib_data",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
	sprintf(meter_comm_params->filename,"%s/meter_id_%d",ROOT_LIB_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
	strcpy(meter_comm_params->meter_pass,dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].meter_pass);
	
	met_poll_dbg_log(REPORT,"%-20s : MeterIdx : %d, MetAddr : %d,  Addr Size : %d\n",
	fun_name,midx,meter_comm_params->meter_id,meter_comm_params->meter_addr_format);
}

/**************************************************************************************************
*Function 					: read_cfg_from_redis()
*Input Parameters 			: Void.
*Output Parameters 			: Void.
*Return	Value				: Success/Failure.
*Description 				: To get config details from Redis server.
********************************************************************************************************/
int32_t read_cfg_from_redis(void)
{
	uint8_t idx=0;
	char 	*p_gen_ptr=NULL;
	
	memset(&dlms_dcu_config,0,sizeof(dlms_dcu_config));
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO DcuDevId NumEthPort MeterType DataFormatType DataTrfType MasterProtoType DbgLogEnable DcuDevLoc DcuGpsLoc DbgLogIp ReadPrevLsData FaultTolSupp");
	
	printf("Total Elements : %d\n",p_redis_reply->elements);
	
	if(p_redis_reply!=NULL)
	{
		//printf("elements : %d\n",p_redis_reply->elements);

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
		
		p_gen_ptr=p_redis_reply->element[10]->str;
		if(p_gen_ptr!=NULL)
			dlms_dcu_config.dlms_dcu_info.read_prev_ls_data = atoi(p_redis_reply->element[10]->str);
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[11]->str;
		if(p_gen_ptr!=NULL)
			dlms_dcu_config.dlms_dcu_info.fault_to_1_supp = atoi(p_redis_reply->element[11]->str);
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	else
	{
		printf("Failed to get DCU_GEN_INFO\n");
		return -1;
	}

	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_SERIAL_INFO NumDcuSer");
	
	printf("DCU_SERIAL_INFO NumDcuSer Total Elements : %d\n",p_redis_reply->elements);
	
	if(p_redis_reply!=NULL)
	{
		//printf("elements : %d\n",p_redis_reply->elements);

		p_gen_ptr=p_redis_reply->element[0]->str;
		//p_gen_ptr=p_redis_reply->str;
		
		//printf(">>> p_gen_ptr : %s\n",p_gen_ptr);
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.ser_prot_cfg.num_ser_port=atoi(p_redis_reply->element[0]->str);
			//printf("NumDcuSer : %d\n",dlms_dcu_config.ser_prot_cfg.num_ser_port);
			freeReplyObject(p_redis_reply);
		}
		else 
			goto EXIT;
	}
	else
	{
		printf("Failed to get DCU_SERIAL_INFO\n");
		goto EXIT;
	}
	
	printf("Getting Other ser info\n");
	
	for(idx=0; idx<MAX_NO_OF_SERIAL_PORT; idx++)
	{
		printf("Getting Serial info for Idx : %d\n",idx);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_SERIAL_INFO DcuSer%dPort DcuSer%dBaudrate DcuSer%dDataBits DcuSer%dStopBits DcuSer%dParity DcuSer%dInfMode",idx+1,idx+1,idx+1,idx+1,idx+1,idx+1);
	
		printf("PortIdx : %d Total Elements : %d\n",idx+1,p_redis_reply->elements);
		
		if(p_redis_reply!=NULL)
		{
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				//strcpy(dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].ser_port,"/dev/ttyS4");
				strcpy(dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].ser_port,p_redis_reply->element[0]->str);
				//printf("Uart : %s\n",dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].ser_port);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[1]->str;
			if(p_gen_ptr!=NULL)
				dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].baudrate=atoi(p_redis_reply->element[1]->str);
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[2]->str;
			if(p_gen_ptr!=NULL)
				dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].databits=atoi(p_redis_reply->element[2]->str);
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[3]->str;
			if(p_gen_ptr!=NULL)
				dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].stopbits=atoi(p_redis_reply->element[3]->str);
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[4]->str;
			if(p_gen_ptr!=NULL)
				dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].parity=atoi(p_redis_reply->element[4]->str);
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[5]->str;
			if(p_gen_ptr!=NULL)
				dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].infmode=atoi(p_redis_reply->element[5]->str);
			else 
				goto EXIT;
			
			freeReplyObject(p_redis_reply);
		}
		else
		{
			printf("Failed to get DCU_SERIAL_INFO for port : %d\n",idx+1);
			goto EXIT;
		}
	}
	
	/*p_redis_reply = redisCommand(p_redis_handler,"hmget INST_POLL_INFO Enable PollType Periodicity PollSec PollMint PollHr");

	//printf("Inst Total Elements : %d\n",p_redis_reply->elements);

	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.inst_poll_info.enable=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	
		p_gen_ptr=p_redis_reply->element[1]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_type=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.inst_poll_info.periodicity=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_sec=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_mint=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_hr=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget LS_POLL_INFO Enable PollType Periodicity PollSec PollMint PollHr");

	//printf("Inst Total Elements : %d\n",p_redis_reply->elements);

	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.ls_poll_info.enable=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	
		p_gen_ptr=p_redis_reply->element[1]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_type=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.ls_poll_info.periodicity=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_sec=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_mint=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_hr=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget EVENT_POLL_INFO Enable PollType Periodicity PollSec PollMint PollHr");

	//printf("Event Total Elements : %d\n",p_redis_reply->elements);

	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.event_poll_info.enable=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	
		p_gen_ptr=p_redis_reply->element[1]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.event_poll_info.poll_type=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.event_poll_info.periodicity=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.event_poll_info.poll_sec=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.event_poll_info.poll_mint=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.event_poll_info.poll_hr=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	}
*/
		 
	p_redis_reply = redisCommand(p_redis_handler,"hmget BILL_POLL_INFO Enable PollType Periodicity PollSec PollMint PollHr");

	printf("Bill Total Elements : %d\n",p_redis_reply->elements);

	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.bill_poll_info.enable=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	
		p_gen_ptr=p_redis_reply->element[1]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_type=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.bill_poll_info.periodicity=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_sec=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_mint=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_hr=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	}
	else
	{
		printf("Failed to get BILL_POLL_INFO\n");
		goto EXIT;
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DP_POLL_INFO Enable PollType Periodicity PollSec PollMint PollHr");

	printf("DP Total Elements : %d\n",p_redis_reply->elements);

	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.enable=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	
		p_gen_ptr=p_redis_reply->element[1]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_type=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.periodicity=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_sec=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_mint=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_hr=atoi(p_redis_reply->element[0]->str);
		}
		else 
			goto EXIT;
	}
	else
	{
		printf("Failed to get DP_POLL_INFO\n");
		goto EXIT;
	}
	 	
	printf("!!!!getting SerMetInfo\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSER_MET_INFO NumMeters",g_port_idx);
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			dlms_dcu_config.dlms_channel_cfg[g_port_idx].num_meter=atoi(p_redis_reply->element[0]->str);
			freeReplyObject(p_redis_reply);
		}
		else 
			goto EXIT;
	}
	else
	{
		printf("Failed to get Port%dSER_MET_INFO\n",g_port_idx);
		goto EXIT;
	}
	
	printf("!!!!getting SerMetInfo Config details\n");
	for(idx=0; idx<MAX_NO_OF_METER_PER_PORT; idx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSerMeter_%dConfig Enable MeterId MeterAddrSize MeterAddr MeterPass MeterLoc",g_port_idx,idx+1);
	
		printf("MeterIdx : %d Total Elements : %d\n",idx+1,p_redis_reply->elements);
		
		if(p_redis_reply!=NULL)
		{
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[idx].enable=atoi(p_redis_reply->element[0]->str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[1]->str;
			if(p_gen_ptr!=NULL)
				dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[idx].meter_id=atoi(p_redis_reply->element[1]->str);
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[2]->str;
			if(p_gen_ptr!=NULL)
				dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[idx].meter_addr_size=atoi(p_redis_reply->element[2]->str);
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[3]->str;
			if(p_gen_ptr!=NULL)
				dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[idx].meter_addr=atoi(p_redis_reply->element[3]->str);
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[4]->str;
			if(p_gen_ptr!=NULL)
				strcpy(dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[idx].meter_pass,p_redis_reply->element[4]->str);
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[5]->str;
			if(p_gen_ptr!=NULL)
				strcpy(dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[idx].meter_loc,p_redis_reply->element[5]->str);
			else 
				goto EXIT;
			
			freeReplyObject(p_redis_reply);
		}
		else
		{
			printf("Failed to get P_%dSerMeter_%dConfig\n",g_port_idx,idx+1);
			goto EXIT;
		}
	}

	return 0;
	
	EXIT:
		printf("This is exit, i.e something wrong in above config\n");
		return -1;
}

/* End Of File */