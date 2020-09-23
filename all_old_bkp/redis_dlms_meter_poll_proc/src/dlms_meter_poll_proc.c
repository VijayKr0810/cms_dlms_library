/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	main.c
* Summary:  Redis and DLMS Module.
*
**********************************************************************/

/* Includes */
#include "gen_inc.h"
#include "gen_fun.h"
#include "log.h"
#include "dlms_fun.h"
#include "dlms_api.h"
//#include "/home/iot-gateway/hiredis/hiredis.h"
#include "hiredis.h"

#define LAST_NUM_DAYS_LS_READ 5
int32_t fill_def_config(meter_comm_params_t *meter_comm_params);
int32_t redis_init(char *host, uint16_t port);
int32_t send_np_det_to_redis(obis_name_plate_info_t name_plate_info);
int32_t send_det_to_redis(char *msg, uint32_t len, char *key_name);
int32_t check_ls_data_file_avl(meter_comm_params_t meter_comm_params);

meter_comm_params_t meter_comm_params;

/* ---------------------------------------------------------- */
int32_t main(int argc,char** argv)
{
	static char fun_name[]="main()";
	int8_t 		fun_ret=-1;
	
	//fill_def_config(&meter_comm_params);
	
	redis_init("192.168.101.108",6379);
	
	serport_params_t serport_params;

	// Filling some default value to structure to start communication
	strcpy(serport_params.ser_port,"/dev/ttyS4");
	serport_params.baudrate=10;
	serport_params.databits=8;
	serport_params.stopbits=1;
	serport_params.parity=0;
	serport_params.handshake=NO_HANDSHAKE;
	serport_params.infmode=RS232_MODE;

	meter_comm_params.inf_type=INF_SERIAL;
	meter_comm_params.meter_type=LNT;
	meter_comm_params.meter_addr_format=1;
	
	if(meter_comm_params.meter_addr_format==1)
	{
		meter_comm_params.meter_id=3;
	}
	else
	{
		meter_comm_params.meter_id=19;
	}
	meter_comm_params.interface_params=&serport_params;
	sprintf(meter_comm_params.filename,"%s/meter_id_%02d",ROOT_DATA_DIR,meter_comm_params.meter_id);
	strcpy(meter_comm_params.meter_pass,"lnt1");
	
	fun_ret = init_comm(&meter_comm_params);
	if(fun_ret<0)
	{
		printf("Failed to initilized communication Error Code : %d\n",fun_ret);
		return -1;
	}
	
	printf("Initilized communication success\n");
	
	fun_ret = connect_to_meter(&meter_comm_params);
	if(fun_ret<0)
	{
		printf("Failed to connect to meter Error Code : %d\n",fun_ret);
		return -1;
	}
	
	gen_params_det_t 				gen_inst_param_det,gen_ls_param_det,gen_event_param_det,gen_bill_param_det,gen_daily_prof_param_det;
	
	fun_ret = get_obis_codes(&meter_comm_params,&gen_inst_param_det,&gen_ls_param_det,
	&gen_event_param_det,&gen_bill_param_det,&gen_daily_prof_param_det);
	if(fun_ret<0)
	{
		printf("Failed to get obis codes.Error Code : %d\n",fun_ret);
		return -1;
	}
	
	obis_name_plate_info_t name_plate_info;
	
	fun_ret = get_nameplate_details(&meter_comm_params, &name_plate_info);
	if(fun_ret<0)
	{
		printf("Failed to get nameplate details. Error Code : %d\n",fun_ret);
		return -1;
	}
	
	send_np_det_to_redis(name_plate_info);
	
	inst_val_info_t				g_inst_data_val;
	memset(&g_inst_data_val,0,sizeof(g_inst_data_val));
	
	fun_ret = get_inst_values(&meter_comm_params, &g_inst_data_val);
	if(fun_ret<0)
	{
		printf("Failed to get inst value. Error Code : %d\n",fun_ret);
		return -1;
	}
	else
	{
		#define INST_INFO_KEY 		"inst_info"
		send_det_to_redis((char*)&g_inst_data_val,sizeof(g_inst_data_val),INST_INFO_KEY);
		//send_inst_det_to_redis(g_inst_data_val);
	}
	
	fun_ret = get_ls_values_day_range(&meter_comm_params, LAST_NUM_DAYS_LS_READ);
	if(fun_ret<0)
	{
		printf("Failed to get prev load survey data. Error Code : %d\n",fun_ret);
		return -1;
	}
	else
	{
		check_ls_data_file_avl(meter_comm_params);
		block_val_info_t g_block_val_info;
		
		#define LS_BLK_INFO_KEY 		"ls_blk_info"
		
		memcpy(&g_block_val_info,&meter_comm_params.meter_response,sizeof(block_val_info_t));
		
		send_det_to_redis((char*)&g_block_val_info,sizeof(block_val_info_t),LS_BLK_INFO_KEY);
	}
	
	fun_ret = get_midnight_data_all(&meter_comm_params);
	if(fun_ret<0)
	{
		printf("Failed to get midnight data. Error Code : %d\n",fun_ret);
		return -1;
	}
	else
	{
		// send_det_to_redis((char*)&g_block_val_info,sizeof(block_val_info_t),LS_BLK_INFO_KEY);
	}
	
	uint8_t event_class_type=0;
	event_val_info_t event_val_info;
	
	for(event_class_type=0; event_class_type<7; event_class_type++)
	{
		events_type_info_t events_type_info;
		fun_ret = get_event_data_all(&meter_comm_params,event_class_type);
		if(fun_ret<0)
		{
			printf("Failed to get midnight data. Error Code : %d\n",fun_ret);
			return -1;
		}
		else
		{
			#define EVENT_INFO_KEY "event_type_key_info"
			char event_key_buff[32];
			memset(event_key_buff,0,sizeof(event_key_buff));
			sprintf(event_key_buff,"%s_%d",EVENT_INFO_KEY,event_class_type);
			
			memcpy(&event_val_info,&meter_comm_params.meter_response,sizeof(event_val_info_t));
			send_det_to_redis((char*)&event_val_info,sizeof(event_val_info_t),event_key_buff);
		}
	}
	
	fun_ret = get_billing_info(&meter_comm_params);
	if(fun_ret<0)
	{
		printf("Failed to get midnight data. Error Code : %d\n",fun_ret);
		return -1;
	}
	else
	{
		#define BILLING_INFO_KEY "billing_key_info"
		//send_det_to_redis((char*)&g_block_val_info,sizeof(block_val_info_t),BILLING_INFO_KEY);
	}
	
	//get_billing_info
	//get_event_data_all
	disconnect_meter(&meter_comm_params);
	
	return RET_SUCCESS;
}

void get_curr_date_time1(struct tm *curr_date_tm)
{
	time_t curr_time=0;
	time(&curr_time);
	
	struct tm *p_curr_time = localtime(&curr_time);
	printf("Current date file name : %02d_%02d_%04d\n",
	p_curr_time->tm_mday,p_curr_time->tm_mon+1,p_curr_time->tm_year+1900);
	
	memcpy(curr_date_tm,p_curr_time,sizeof(struct tm));
}

int32_t check_ls_data_file_avl(meter_comm_params_t meter_comm_params)
{
	struct stat file_st={0};
	uint8_t day_idx=0;
	char 	file_name[64]={0};
	char 	tot_ls_file_det[LAST_NUM_DAYS_LS_READ][64];
	
	struct tm st_time,time_stamp,curr_date_tm;
	time_t time_of_day=0,next_time_day=0,curr_time=0;
	uint8_t no_file_cnt=0;
	
	get_curr_date_time1(&curr_date_tm);

	st_time.tm_mday = curr_date_tm.tm_mday;
	st_time.tm_mon =  curr_date_tm.tm_mon ;
	st_time.tm_year = curr_date_tm.tm_year;
	st_time.tm_hour = curr_date_tm.tm_hour;
	st_time.tm_min = curr_date_tm.tm_min;
	st_time.tm_sec = curr_date_tm.tm_sec;
	printf("33 Current date file name : %02d_%02d_%04d\n",st_time.tm_mday,st_time.tm_mon+1,st_time.tm_year+1900);
	
	time_of_day = mktime(&st_time);
	//time_of_day -= (last_num_days_read*60*60);
	time_of_day -= (24*60*60);
	localtime_r(&time_of_day,&time_stamp);
	
	printf("22 Current date file name : %02d_%02d_%04d\n",time_stamp.tm_mday,time_stamp.tm_mon+1,time_stamp.tm_year+1900);
	
	for(day_idx=0; day_idx<LAST_NUM_DAYS_LS_READ; day_idx++)
	{
		printf("Current date file name : %02d_%02d_%04d\n",time_stamp.tm_mday,time_stamp.tm_mon+1,time_stamp.tm_year+1900);
		memset(file_name,0,sizeof(file_name));
		sprintf(file_name,"%s/%02d_%02d_%04d",meter_comm_params.filename,
		time_stamp.tm_mday,time_stamp.tm_mon+1,time_stamp.tm_year+1900);
		
		localtime_r(&time_of_day,&time_stamp);
		
		if(stat(file_name,&file_st)==-1)
		{
			printf("This LS data file is not available : %s\n",file_name);
			memset(tot_ls_file_det[day_idx],0,sizeof(tot_ls_file_det[day_idx]));
			strcpy(tot_ls_file_det[day_idx],file_name);
			time_of_day = time_of_day-(60*60*24);
			no_file_cnt++;
			continue;
		}
		time_of_day = time_of_day-(60*60*24);
	}
	
	if(no_file_cnt)
	{
		printf("Total Num of absent ls file : %d\n",no_file_cnt);
		for(day_idx=0; day_idx<no_file_cnt; day_idx++)
			printf("Absent File Name : %s\n",tot_ls_file_det[day_idx]);
	}
	
	return RET_SUCCESS;
}

#if 0

int32_t main1(int argc , char** argv)
{
	static char fun_name[]="main()";
	float p_flt_ptr=0.0;
	uint8_t obis[6]={0};
	
	printf("In Dlms Redis Programm\n");
	
	char p_msg[128];
	const char *hostname = "192.168.101.108";
    int port = 6379;
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    
	redisContext *c;
	redisReply *reply;

	printf("Try to connect to Redis Server : %s\n",hostname);
	c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) 
	{
        if (c) 
		{
            printf("Connection error: %s\n", c->errstr);
			printf("Disconnecting to Redis Server : %s\n",hostname);
            redisFree(c);
        } 
		else 
		{
            printf("Connection error: can't allocate redis context\n");
        }
		
        exit(1);
    }
	
	printf("Connected to Redis Server\n");
	
	/* PING server */
    reply = redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
	
    freeReplyObject(reply);

	meter_comm_params_t meter_comm_params;

	if(connect_to_meter(&meter_comm_params)<0)
	{
		printf("Failed to connect to meter\n");
		return -1;
	}
	
	obis_name_plate_info_t name_plate_info;
	if(get_nameplate_details(&meter_comm_params, &name_plate_info)<0)
	{
		printf("Failed to get nameplate details.\n");
		return -1;
	}
	else
	{
		printf("OBIS_CODE\t\tPARAMS_NAME\t\tPARAM_VALUE\n");
		
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%s\n",
				name_plate_info.meter_ser_num.param_obis_code[0],
				name_plate_info.meter_ser_num.param_obis_code[1],
				name_plate_info.meter_ser_num.param_obis_code[2],
				name_plate_info.meter_ser_num.param_obis_code[3],
				name_plate_info.meter_ser_num.param_obis_code[4],
				name_plate_info.meter_ser_num.param_obis_code[5],
				name_plate_info.meter_ser_num.param_name,
				name_plate_info.meter_ser_num.param_value
				);
		
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%s\n",
				name_plate_info.manf_name.param_obis_code[0],
				name_plate_info.manf_name.param_obis_code[1],
				name_plate_info.manf_name.param_obis_code[2],
				name_plate_info.manf_name.param_obis_code[3],
				name_plate_info.manf_name.param_obis_code[4],
				name_plate_info.manf_name.param_obis_code[5],
				name_plate_info.manf_name.param_name,
				name_plate_info.manf_name.param_value
				);
				
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%s\n",
				name_plate_info.fw_vwesion.param_obis_code[0],
				name_plate_info.fw_vwesion.param_obis_code[1],
				name_plate_info.fw_vwesion.param_obis_code[2],
				name_plate_info.fw_vwesion.param_obis_code[3],
				name_plate_info.fw_vwesion.param_obis_code[4],
				name_plate_info.fw_vwesion.param_obis_code[5],
				name_plate_info.fw_vwesion.param_name,
				name_plate_info.fw_vwesion.param_value
				);
				
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%d\n",
				name_plate_info.meter_type.param_obis_code[0],
				name_plate_info.meter_type.param_obis_code[1],
				name_plate_info.meter_type.param_obis_code[2],
				name_plate_info.meter_type.param_obis_code[3],
				name_plate_info.meter_type.param_obis_code[4],
				name_plate_info.meter_type.param_obis_code[5],
				name_plate_info.meter_type.param_name,
				name_plate_info.meter_type.param_value[0]
				);
		
		memcpy(&p_flt_ptr,&name_plate_info.int_ct_ratio.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				name_plate_info.int_ct_ratio.param_obis_code[0],
				name_plate_info.int_ct_ratio.param_obis_code[1],
				name_plate_info.int_ct_ratio.param_obis_code[2],
				name_plate_info.int_ct_ratio.param_obis_code[3],
				name_plate_info.int_ct_ratio.param_obis_code[4],
				name_plate_info.int_ct_ratio.param_obis_code[5],
				name_plate_info.int_ct_ratio.param_name,
				p_flt_ptr
				/* name_plate_info.int_ct_ratio.param_value */
				);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&name_plate_info.int_pt_ratio.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				name_plate_info.int_pt_ratio.param_obis_code[0],
				name_plate_info.int_pt_ratio.param_obis_code[1],
				name_plate_info.int_pt_ratio.param_obis_code[2],
				name_plate_info.int_pt_ratio.param_obis_code[3],
				name_plate_info.int_pt_ratio.param_obis_code[4],
				name_plate_info.int_pt_ratio.param_obis_code[5],
				name_plate_info.int_pt_ratio.param_name,
				p_flt_ptr
				/* name_plate_info.int_pt_ratio.param_value */
				);
	
		printf("+++++++ Recv Nameplate info success\n");
	}
	
	//name_plate_info
	char key_name[32]="name_plate_det_key";
	
	reply = redisCommand(c, "HMSET %s stat %b", key_name, &name_plate_info, sizeof(name_plate_info));
	printf("Saveṣ status : %s\n", reply->str);//that shows +OK
		
	freeReplyObject(reply);

	printf("Disconnecting from Metere & closing connection\n",hostname);
	disconnect_meter(&meter_comm_params);
	
	/* Disconnects and frees the context */
	printf("Disconnecting to Redis Server : %s\n",hostname);
    
	redisFree(c);
	
	return RET_SUCCESS;
}

#endif

/* End Of File */