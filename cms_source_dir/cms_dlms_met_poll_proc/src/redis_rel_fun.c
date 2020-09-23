#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
#include "dlms_api.h"
#include "dlms_fun.h"
#include "/home/iot-gateway/hiredis/hiredis.h"

int32_t met_poll_dbg_log(uint8_t mode, const char *p_format, ...);

/* Extern  */
extern uint8_t 					g_port_idx,g_midx;
extern redisContext 			*p_redis_handler;
extern redisReply 				*p_redis_reply;
extern all_param_obis_val_info_t 	g_all_inst_param_obis_val;
extern  char					g_curr_meter_ser_info[MAX_NO_OF_METER_PER_PORT][32];
/* ================================================================== */
int32_t redis_init(char *hostname, uint16_t port)
{
	static char fun_name[]="redis_init()";
	
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	
	met_poll_dbg_log(INFORM,"%-20s : Trying to connect on Redis Server : %s with port : %d\n",fun_name,hostname,port);
	
    p_redis_handler = redisConnectWithTimeout(hostname, port, timeout);
    if (p_redis_handler == NULL || p_redis_handler->err) 
	{
        if (p_redis_handler) 
		{
			met_poll_dbg_log(INFORM,"%-20s : Connection error: %s\n",fun_name,p_redis_handler->errstr);
            
            redisFree(p_redis_handler);
        } 
		else 
		{
			met_poll_dbg_log(INFORM,"%-20s : Connection error: can't allocate redis context\n",fun_name);
        }
    }
	
	met_poll_dbg_log(INFORM,"%-20s : Connected on Redis Server : %s with port : %d\n",fun_name,hostname,port);
   
    freeReplyObject(p_redis_reply);
	
	return RET_SUCCESS;
}

int32_t update_np_det_to_redis(obis_name_plate_info_t *name_plate_info, uint32_t midx)
{
	g_midx=midx;
	char obis_buff[32];
	
	memset(obis_buff,0,sizeof(obis_buff));
	sprintf(obis_buff,"%d.%d.%d.%d.%d.%d",
	name_plate_info->meter_ser_num.param_obis_code[0],
	name_plate_info->meter_ser_num.param_obis_code[1],
	name_plate_info->meter_ser_num.param_obis_code[2],
	name_plate_info->meter_ser_num.param_obis_code[3],
	name_plate_info->meter_ser_num.param_obis_code[4],
	name_plate_info->meter_ser_num.param_obis_code[5]
	);
	
	printf("obis_buff : %s, strlen : %d\n",obis_buff,strlen(obis_buff));
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dnp_info MeterSerNum %s MeterSerNumObis %s",g_port_idx,midx,
	name_plate_info->meter_ser_num.param_value,obis_buff);
	freeReplyObject(p_redis_reply);
	
/* 	printf("MeterSerNumObis %d %d %d %d %d %d\n",
	name_plate_info->meter_ser_num.param_obis_code[0],
	name_plate_info->meter_ser_num.param_obis_code[1],
	name_plate_info->meter_ser_num.param_obis_code[2],
	name_plate_info->meter_ser_num.param_obis_code[3],
	name_plate_info->meter_ser_num.param_obis_code[4],
	name_plate_info->meter_ser_num.param_obis_code[5]
	); */
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dnp_info MfgName %s MfgNameObis %s",g_port_idx,midx,
	name_plate_info->manf_name.param_value,name_plate_info->manf_name.param_obis_code);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dnp_info FwVer %s FwVerObis %s",g_port_idx,midx,
	name_plate_info->fw_vwesion.param_value,name_plate_info->fw_vwesion.param_obis_code);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dnp_info MeterType %d MeterTypeObis %s",g_port_idx,midx,
	name_plate_info->meter_type.param_value,name_plate_info->meter_type.param_obis_code);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dnp_info CTRatio %d CTRatioObis %s",g_port_idx,midx,
	name_plate_info->int_ct_ratio.param_value,name_plate_info->int_ct_ratio.param_obis_code);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dnp_info PTRatio %s PTRatioObis %s",g_port_idx,midx,
	name_plate_info->int_pt_ratio.param_value,name_plate_info->int_pt_ratio.param_obis_code);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Port%dMet%dnp_info MetStorType %d MetStorTypeObis %s",g_port_idx,midx,
	name_plate_info->met_store_type.param_value,name_plate_info->met_store_type.param_obis_code);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET Port%dMet%dSerNum SER_NUM %s",
	g_port_idx,midx,name_plate_info->meter_ser_num.param_value);
	
	freeReplyObject(p_redis_reply);
	
	//strcpy(g_curr_meter_ser_info[midx],name_plate_info->meter_ser_num.param_value);
	
	
	return RET_SUCCESS;
}

int32_t send_det_to_redis(char *msg, uint32_t len, char *key_name)
{
	printf("Updating info into redis server for key_name : %s\n",key_name);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s stat %b",key_name, msg, len);
	
	printf("Info Saved status : %s\n", p_redis_reply->str); //that shows +OK
		
	freeReplyObject(p_redis_reply);
		
	return RET_SUCCESS;
}

int32_t send_inst_det_to_redis(inst_val_info_t *inst_data_val,int len, char *p_key_name,uint8_t midx)
{
	char time_buff[32];
	char key_name[32];
	date_time_t date_time;
	uint8_t idx=0;
	float 	flt_val=0.0,*p_flt_ptr=NULL;
	uint8_t date_time_obis[6]={0,0,1,0,0,255};
	
	g_midx=midx;
	memset(&date_time,0,sizeof(date_time_t));
	memset(time_buff,0,sizeof(time_buff));
	memset(key_name,0,sizeof(key_name));
	
	sprintf(key_name,"Port%dMet%d%s",g_port_idx,midx,p_key_name);
	
	printf("Total Number of Inst Params : %d\n",g_all_inst_param_obis_val.tot_num_params);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s NUM_PARAM %d",
	key_name,g_all_inst_param_obis_val.tot_num_params);
		
	freeReplyObject(p_redis_reply);
		
	for(idx=0; idx<g_all_inst_param_obis_val.tot_num_params; idx++)
	{
		printf("OBIS DET : %d.%d.%d.%d.%d.%d\t",
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[0],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[1],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[2],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[3],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[4],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[5]
		);
		
		switch(g_all_inst_param_obis_val.param_obis_val_info[idx].data_type)
		{
			case OCTET_STRING_TYPE:
			{
				memcpy(&date_time,&g_all_inst_param_obis_val.param_obis_val_info[idx].value,sizeof(date_time_t));
				printf("Inst Date : %02d_%02d_%04d %02d:%02d:%02d\n",
				date_time.day,
				date_time.month,
				date_time.year,
				date_time.hour,
				date_time.minute,
				date_time.second
				);
			}
			break;
			
			default:
			{
				memcpy(&flt_val,&g_all_inst_param_obis_val.param_obis_val_info[idx].value,4);
				printf("INST Val : %0.5f\n",flt_val);
			}
			break;
		}
	}
	
	char 	obis_buff[32];
	char 	value_buff[32];
	
	for(idx=0; idx<g_all_inst_param_obis_val.tot_num_params; idx++)
	{
		memset(obis_buff,0,sizeof(obis_buff));
		memset(value_buff,0,sizeof(value_buff));
		
		sprintf(obis_buff,"%d.%d.%d.%d.%d.%d",
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[0],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[1],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[2],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[3],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[4],
		g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code[5]
		);
		
		switch(g_all_inst_param_obis_val.param_obis_val_info[idx].data_type)
		{
			case OCTET_STRING_TYPE:
			{
				memcpy(&date_time,&g_all_inst_param_obis_val.param_obis_val_info[idx].value,sizeof(date_time_t));
				sprintf(value_buff,"%02d_%02d_%04d %02d:%02d:%02d",
				date_time.day,
				date_time.month,
				date_time.year,
				date_time.hour,
				date_time.minute,
				date_time.second
				);
				
				if(memcmp(g_all_inst_param_obis_val.param_obis_val_info[idx].obis_code,date_time_obis,6)==0)
					memcpy(time_buff,value_buff,32);
			}
			break;
			
			default:
			{
				memcpy(&flt_val,&g_all_inst_param_obis_val.param_obis_val_info[idx].value,4);
				sprintf(value_buff,"%0.5f",flt_val);
			}
			break;
		}
		
		p_redis_reply = redisCommand(p_redis_handler, "HMSET %s Obis_%d %s Value_%d %s",key_name,idx+1,obis_buff,idx+1,value_buff);
		
		//printf("Inst Info Saved status : %s\n", p_redis_reply->str); //that shows +OK
		
		freeReplyObject(p_redis_reply);
	}
	
/* 	memset(time_buff,0,sizeof(time_buff));
	
	sprintf(time_buff,"%02d_%02d_%04d %02d:%02d:%02d",
	date_time.day,
	date_time.month,
	date_time.year,
	date_time.hour,
	date_time.minute,
	date_time.second
	); */
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s UPDATE_TIME %s",key_name,time_buff);
	freeReplyObject(p_redis_reply);
	
	printf("Updated Inst info into redis server last update time : %s\n",time_buff);
	
	return 0;
	
	#if 0
	memset(time_buff,0,sizeof(time_buff));
	sprintf(time_buff,"%02d_%02d_%04d %02d:%02d:%02d",
	inst_data_val->date_time.day,
	inst_data_val->date_time.month,
	inst_data_val->date_time.year,
	inst_data_val->date_time.hour,
	inst_data_val->date_time.minute,
	inst_data_val->date_time.second
	);
	
	printf("Updating Inst info into redis server for key_name : %s\n",key_name);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s Time %s",key_name,time_buff);freeReplyObject(p_redis_reply);
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s CurrIr %s",key_name,inst_data_val->cur_ir.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s CurrIb %s",key_name,inst_data_val->cur_ib.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s CurrIy %s",key_name,inst_data_val->cur_iy.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s VoltR %s",key_name,inst_data_val->volt_r.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s VoltY %s",key_name,inst_data_val->volt_y.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s VoltB %s",key_name,inst_data_val->volt_b.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s PfR %s",key_name,inst_data_val->pf_r.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s PfY %s",key_name,inst_data_val->pf_y.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s PfB %s",key_name,inst_data_val->pf_b.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s PfAvg %s",key_name,inst_data_val->pf_avg.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s PfAvg %s",key_name,inst_data_val->pf_avg.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s PfAvg %s",key_name,inst_data_val->pf_avg.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s Freq %s",key_name,inst_data_val->freq.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s Kva %s",key_name,inst_data_val->kva.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s Kw %s",key_name,inst_data_val->kw.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s Kwh %s",key_name,inst_data_val->kwh.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s KvarhLag %s",key_name,inst_data_val->kvarh_lag.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s KvarhLead %s",key_name,inst_data_val->kvarh_lead.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s Kvah %s",key_name,inst_data_val->kvah.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s Kwmd %s",key_name,inst_data_val->kwmd.param_value);freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s Kvamd %s",key_name,inst_data_val->kvamd.param_value);freeReplyObject(p_redis_reply);
	
	memset(time_buff,0,sizeof(time_buff));
	sprintf(time_buff,"%02d_%02d_%04d %02d:%02d:%02d",
	inst_data_val->bill_date.day,
	inst_data_val->bill_date.month,
	inst_data_val->bill_date.year,
	inst_data_val->bill_date.hour,
	inst_data_val->bill_date.minute,
	inst_data_val->bill_date.second
	);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s BillDate %s",key_name,time_buff);freeReplyObject(p_redis_reply);
	
	printf("Inst Info Saved status : %s\n", p_redis_reply->str); //that shows +OK
	#endif
	
	return RET_SUCCESS;
}

void check_od_msg_request(void)
{
	
}

/* End of file */