/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	dlms_api.c
* Summary:  API of DLMS Module.
*
**********************************************************************/

/* Includes */
#include "gen_inc.h"
#include "gen_fun.h"
#include "log.h"
#include "dlms_fun.h"
#include "dlms_api.h"

int8_t get_inst_values(meter_comm_params_t *meter_comm_params, gen_data_val_info_t *p_gen_data_val_info);

/* Extern */
extern date_time_t 				meter_date_time;
extern uint32_t 				g_int_period_blk;
extern uint8_t 					OFFSET;


/* Globals */
char 							lib_dbg_file_name[SIZE_64]="/usr/cms/log/cms_dlms_api.log";
char 							g_ls_data_dir_path[SIZE_64];
uint8_t							g_append_event_file_flag;			

/**************************************************************************************************
*Function 					: init_comm()
*Input Parameters 			: Structure containing type of communication and the required parameters. 
							  Type identifying serial or ethernet.
*Output Parameters 			: Serial fd or socket fd.
*Return	Value				: Success or appropriate error code.
*Description 				: This API initializes the communication channel of DLMS devices. If the type is serial, 
							  initializes the serial port with the supplied parameters , 
							  if ethernet, initializes the tcp connection with the meter.
********************************************************************************************************/
int8_t init_comm(meter_comm_params_t *meter_comm_params)
{
	static char 	fun_name[]="init_comm()";

	//memset(lib_dbg_file_name,0,sizeof(lib_dbg_file_name));
	//sprintf(lib_dbg_file_name,"%s/cms_dlms_api.log",LOG_DIR);
	
	memset(g_ls_data_dir_path,0,sizeof(g_ls_data_dir_path));
	sprintf(g_ls_data_dir_path,"%s",meter_comm_params->filename);
	
	//printf("meter_comm_params Library side size : %d\n",sizeof(meter_comm_params_t));
	
	/* lib_dbg_log(INFORM,"%-20s : Created Root ls data dir : %s\n",fun_name,g_ls_data_dir_path);
	lib_dbg_log(INFORM,"%-20s : CMS DLMS API Version :: %s\n",fun_name,DLMS_API_VERSION);
	lib_dbg_log(INFORM,"%-20s : Communicatin started for DLMS API.\n",fun_name); */
	
	if(meter_comm_params->inf_type==INF_SERIAL)
	{
		return init_serial(meter_comm_params);
	}
	else if(meter_comm_params->inf_type==INF_TCP)
	{
		return init_tcp_conn(meter_comm_params);
	}
	else
	{
		return RET_INVALID_INF_TYPE;
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: connect_to_meter()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Sends DISC, SNRM and AARQ packets to the meter and get the response.
********************************************************************************************************/
int8_t connect_to_meter(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="connect_to_meter()";
	int8_t ret_val=0;
	
	memset(g_ls_data_dir_path,0,sizeof(g_ls_data_dir_path));
	sprintf(g_ls_data_dir_path,"%s",meter_comm_params->filename);
	
	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			OFFSET=0;
		break;
		
		case 2:
			OFFSET=1;
		break;
		
		case 4:
			OFFSET=3;
		break;
		
		default:
			OFFSET=0;
		break;
	}
	
	//ret_val = send_disc(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format);
	ret_val = send_disc(meter_comm_params);
	if(ret_val<0)
	{
		lib_dbg_log(REPORT,"%-20s : DISC Frame Qry  failed\n",fun_name);
		return ret_val;
	}
	
	//ret_val = send_snrm(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format);
	ret_val = send_snrm(meter_comm_params);
	if(ret_val<0)
	{
		lib_dbg_log(REPORT,"%-20s : SNRM Qry  failed\n",fun_name);
		return ret_val;
	}
	
	//ret_val = send_aarq(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format,meter_comm_params->meter_pass);
	ret_val = send_aarq(meter_comm_params);
	if(ret_val<0)
	{
		lib_dbg_log(REPORT,"%-20s : AARQ Qry  failed\n",fun_name);
		return ret_val;
	}
	
	lib_dbg_log(REPORT,"%-20s : Meter connected succfully\n",fun_name);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_nameplate_details()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response structure with all the nameplate details.
*Return	Value				: Success or appropriate error code.
*Description 				: Get the nameplate information of the meter and return the decoded nameplate values in appropriate structure.
********************************************************************************************************/
int8_t get_nameplate_details(meter_comm_params_t *meter_comm_params, obis_name_plate_info_t *np_params_obis_val_info)
{
	//get_nameplate_info(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format,np_params_obis_val_info);
	get_nameplate_info(meter_comm_params,np_params_obis_val_info);

	return 0;
}

/**************************************************************************************************
*Function 					: get_obis_codes()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: This function does the following tasks
								•	gets values obis code of all the types of data . 
								•	get the scalar obis codes of all the types of data. 
								•	get the scalar value of all the types of data. 
********************************************************************************************************/
int8_t get_obis_codes( meter_comm_params_t *meter_comm_params,
						gen_params_det_t *recv_gen_inst_param_det,
						gen_params_det_t *recv_gen_ls_param_det,
						gen_params_det_t *recv_gen_event_param_det,
						gen_params_det_t *recv_gen_bill_param_det,
						gen_params_det_t *recv_gen_daily_prof_param_det)
{
	int8_t ret_val = 0;
	
	//ret_val = get_dp_obis_code_det(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format,recv_gen_daily_prof_param_det);
	ret_val = get_dp_obis_code_det(meter_comm_params,recv_gen_daily_prof_param_det);
	if(ret_val<0)
	{
		return ret_val;
	}
	else
	{
		printf("Recv Daily profile obis code info\n");
	}
	
	//ret_val = get_inst_obis_code_det(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format,recv_gen_inst_param_det);
	ret_val = get_inst_obis_code_det(meter_comm_params,recv_gen_inst_param_det);
	if(ret_val<0)
	{
		return ret_val;
	}
	else
	{
		printf("Recv Inst obis code info\n");
	}
	
	//ret_val = get_ls_obis_code_det(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format,recv_gen_ls_param_det);
	ret_val = get_ls_obis_code_det(meter_comm_params,recv_gen_ls_param_det);
	if(ret_val<0)
	{
		return ret_val;
	}
	else
	{
		printf("Recv Ls obis code info\n");
	}
	
	//ret_val = get_billing_obis_code_det(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format,recv_gen_bill_param_det);
	ret_val = get_billing_obis_code_det(meter_comm_params,recv_gen_bill_param_det);
	if(ret_val<0)
	{
		return ret_val;
	}
	else
	{
		printf("Recv Billing obis code info\n");
	}
	
	//ret_val = get_event_obis_code_det(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format,recv_gen_event_param_det);
	ret_val = get_event_obis_code_det(meter_comm_params,recv_gen_event_param_det);
	if(ret_val<0)
	{
		return ret_val;
	}
	else
	{
		printf("Recv Event obis code info\n");
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_inst_values()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get the instantaneous data  of the meter and return the decoded values of instantaneous data in appropriate structure
********************************************************************************************************/
int8_t get_inst_values(meter_comm_params_t *meter_comm_params, gen_data_val_info_t *p_gen_data_val_info)
{
	if(get_inst_val(meter_comm_params,p_gen_data_val_info)<0)
	{
		return RET_INST_VAL_FAILED_TYPE;
	}
	else
	{
		printf("+++++++++++++++++++Recv Inst data\n");
	}
	
	return 0;
}

/**************************************************************************************************
*Function 					: get_ls_values_block_range()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get the load survey data of the meter for the given block range. The range should be such that 							it contains data of fewer blocks say maximum of 4 blocks. 
								The decoded values of the blocks are returned in appropriate structure.
********************************************************************************************************/
int8_t get_ls_values_block_range(meter_comm_params_t *meter_comm_params, uint8_t last_num_blk_read)
{
	static char fun_name[]="get_ls_values_block_range()";
	if(last_num_blk_read>4)
	{
		printf("Received More number of block to be read. Max is 4\n");
		return -1;
	}
	else
	{
		date_time_t st_date_time, end_date_time;
/* 		
		struct tm st_time,time_stamp;
		time_t time_of_day=0;
		
		uint8_t comm_fd = meter_comm_params->fd;
		uint32_t dlms_met_addr = meter_comm_params->meter_id;
		uint8_t met_addr_size = meter_comm_params->meter_addr_format;
		
		if(get_curr_date_time(comm_fd, dlms_met_addr, met_addr_size)<0)
		{
			lib_dbg_log(REPORT,"%-20s : failed to get Meter curr date time\n",fun_name); 
			return -1;
		} */
		
		memset(&st_date_time,0,sizeof(st_date_time));
		memset(&end_date_time,0,sizeof(end_date_time));
		
		/* st_time.tm_mday = meter_date_time.day;
		st_time.tm_mon =  meter_date_time.month - 1;
		st_time.tm_year = meter_date_time.year - 1900;
		st_time.tm_hour = meter_date_time.hour;
		st_time.tm_min = meter_date_time.minute;
		st_time.tm_sec = meter_date_time.second;
		
		time_of_day = mktime(&st_time);
		time_of_day -= (last_num_blk_read*g_int_period_blk*60);
		localtime_r(&time_of_day,&time_stamp);
		
		st_date_time.day = time_stamp.tm_mday;
		st_date_time.month = time_stamp.tm_mon+1;
		st_date_time.year = time_stamp.tm_year+1900;
		st_date_time.hour = time_stamp.tm_hour;
		st_date_time.minute = time_stamp.tm_min;
		st_date_time.second = time_stamp.tm_sec;
		
		end_date_time.day = meter_date_time.day;
		end_date_time.month = meter_date_time.month;
		end_date_time.year = meter_date_time.year;
		end_date_time.hour = meter_date_time.hour;
		end_date_time.minute = meter_date_time.minute;
		end_date_time.second = meter_date_time.second; */
		
		st_date_time.day = meter_comm_params->from.day;
		st_date_time.month = meter_comm_params->from.month;
		st_date_time.year = meter_comm_params->from.year;
		st_date_time.hour = meter_comm_params->from.hour;
		st_date_time.minute = meter_comm_params->from.minute;
		st_date_time.second = meter_comm_params->from.second;
		
		end_date_time.day = meter_comm_params->to.day;
		end_date_time.month = meter_comm_params->to.month;
		end_date_time.year = meter_comm_params->to.year;
		end_date_time.hour = meter_comm_params->to.hour;
		end_date_time.minute = meter_comm_params->to.minute;
		end_date_time.second = meter_comm_params->to.second;
		
		return recv_ls_blk_range_data(meter_comm_params,st_date_time,end_date_time);
	}
}

/**************************************************************************************************
*Function 					: get_ls_values_hour_range()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get the load survey data of the meter for the given range in hours. 
								The range can be upto 24 hours. 
								The decoded values are stored in the files for that day. 
								Only the last block data is returned to the calling function.
********************************************************************************************************/
int8_t get_ls_values_hour_range(meter_comm_params_t *meter_comm_params,uint8_t last_num_hr_read)
{
	static char fun_name[]="get_ls_values_hour_range()";
	
	if(last_num_hr_read>24)
	{
		printf("Received More number of block to be read. Max is 24\n");
		return -1;
	}
	else
	{
		date_time_t st_date_time, end_date_time;
		st_date_time.day = meter_comm_params->from.day;
		st_date_time.month = meter_comm_params->from.month;
		st_date_time.year = meter_comm_params->from.year;
		st_date_time.hour = meter_comm_params->from.hour;
		st_date_time.minute = meter_comm_params->from.minute;
		st_date_time.second = meter_comm_params->from.second;
		
		end_date_time.day = meter_comm_params->to.day;
		end_date_time.month = meter_comm_params->to.month;
		end_date_time.year = meter_comm_params->to.year;
		end_date_time.hour = meter_comm_params->to.hour;
		end_date_time.minute = meter_comm_params->to.minute;
		end_date_time.second = meter_comm_params->to.second;
		
		/* date_time_t st_date_time, end_date_time;
		struct tm st_time,time_stamp;
		time_t time_of_day=0;
		
		uint8_t comm_fd = meter_comm_params->fd;
		uint32_t dlms_met_addr = meter_comm_params->meter_id;
		uint8_t met_addr_size = meter_comm_params->meter_addr_format;
		
		if(get_curr_date_time(comm_fd, dlms_met_addr, met_addr_size)<0)
		{
			lib_dbg_log(REPORT,"%-20s : failed to get Meter curr date time\n",fun_name); 
			return -1;
		}
		
		memset(&st_time,0,sizeof(st_time));
		memset(&end_date_time,0,sizeof(end_date_time));
		
		st_time.tm_mday = meter_date_time.day;
		st_time.tm_mon =  meter_date_time.month - 1;
		st_time.tm_year = meter_date_time.year - 1900;
		st_time.tm_hour = meter_date_time.hour;
		st_time.tm_min = meter_date_time.minute;
		st_time.tm_sec = meter_date_time.second;
		
		time_of_day = mktime(&st_time);
		time_of_day -= (last_num_hr_read*60*60);
		localtime_r(&time_of_day,&time_stamp);
		
		st_date_time.day = time_stamp.tm_mday;
		st_date_time.month = time_stamp.tm_mon+1;
		st_date_time.year = time_stamp.tm_year+1900;
		st_date_time.hour = time_stamp.tm_hour;
		st_date_time.minute = time_stamp.tm_min;
		st_date_time.second = time_stamp.tm_sec;
		
		end_date_time.day = meter_date_time.day;
		end_date_time.month = meter_date_time.month;
		end_date_time.year = meter_date_time.year;
		end_date_time.hour = meter_date_time.hour;
		end_date_time.minute = meter_date_time.minute;
		end_date_time.second = meter_date_time.second; */
		
		return recv_ls_hour_range_data(meter_comm_params,st_date_time,end_date_time);
	}
}

/**************************************************************************************************
*Function 					: get_ls_values_day_range()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get the load survey data of the meter for the given range in days. 
								The range can be upto 1 month. 
								The decoded values are stored in the files for that day. 
								Only the last block data is returned to the calling function.
********************************************************************************************************/
int8_t get_ls_values_day_range(meter_comm_params_t *meter_comm_params, uint8_t last_num_days_read)
{
	if(last_num_days_read>LAST_NUM_DAYS_LS_READ)
	{
		printf("Received More number of block to be read. Max is : %d\n",LAST_NUM_DAYS_LS_READ);
		return -1;
	}
	else
	{
		return recv_ls_day_range_data(meter_comm_params,last_num_days_read);
	}
}

/**************************************************************************************************
*Function 					: get_event_data()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter, event class.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get the latest maximum 10 events stored in the meter for the event class. 
								The events read are stored in appropriate file in the standard format. 
								Only the last event of the class is returned to the calling function.
********************************************************************************************************/
int8_t get_event_data(meter_comm_params_t *meter_comm_params,uint8_t event_class)
{
	if(event_class>7)
	{
		printf("Received invalid event class type. it should be in between 0-6\n");
		return -1;
	}
	else
	{
		g_append_event_file_flag=0;
		return get_event_class_data(meter_comm_params,event_class,0);
	}
}

/**************************************************************************************************
*Function 					: get_event_data_all()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter, event class.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get all the events stored in the meter for the event class. 
							  The events read are stored in appropriate file in the standard format. 
							  Only the last event of the class is returned to the calling function.
********************************************************************************************************/
int8_t get_event_data_all(meter_comm_params_t *meter_comm_params,uint8_t event_class)
{
	if(event_class>7)
	{
		printf("Received invalid event class type. it should be in between 0-6\n");
		return -1;
	}
	else
	{
		g_append_event_file_flag=0;
		return get_event_class_data(meter_comm_params,event_class,1);
	}
}

/**************************************************************************************************
*Function 					: get_midnight_data_all()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter, event class.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get  all the midnight data available in the meter. 
							The decoded values are stored in files with the month as the name. 
							Only the last midnight data is returned to the calling function.
********************************************************************************************************/
int8_t get_midnight_data_all(meter_comm_params_t *meter_comm_params)
{
	return get_daily_profile_value(meter_comm_params,1);
}

/**************************************************************************************************
*Function 					: get_midnight_data()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter, event class.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get  the midnight data for the current month from the meter. 
								The decoded values are stored in files with the month as the name. 
								Only the last midnight data is returned to the calling function.
********************************************************************************************************/
int8_t get_midnight_data(meter_comm_params_t *meter_comm_params)
{
	return get_daily_profile_value(meter_comm_params,0);
}

/**************************************************************************************************
*Function 					: get_billing_info()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter, event class.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get the billing information of the last month. 
								Only the last information is returned to the calling function.
********************************************************************************************************/
int8_t get_billing_info(meter_comm_params_t *meter_comm_params)
{
	return get_bill_data_info(meter_comm_params);
}

/**************************************************************************************************
*Function 					: disconnect_meter()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter, event class.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: Disconnects the meter and closes the communication.
********************************************************************************************************/
int8_t disconnect_meter(meter_comm_params_t *meter_comm_params)
{
	int8_t ret_val=0;
	
	//ret_val = send_disc(meter_comm_params->fd,meter_comm_params->meter_id,meter_comm_params->meter_addr_format);
	ret_val = send_disc(meter_comm_params);
	if(ret_val<0)
	{
		static char fun_name[]="disconnect_meter()";
		lib_dbg_log(REPORT,"%-20s : DISC Frame Qry  failed\n",fun_name);
		return ret_val;
	}
	
	return ret_val;
}

/* End of file */