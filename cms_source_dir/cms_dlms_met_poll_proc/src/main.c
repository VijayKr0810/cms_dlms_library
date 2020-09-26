#include "gen_inc.h"
#include "dlms_api_config.h"
#include "dlms_api.h"
#include "log.h"
#include "dlms_fun.h"
#include "/home/iot-gateway/hiredis/hiredis.h"

#define REFF_INST_POLL_TIME 	2
#define REFF_EVENT_POLL_TIME 	5*60
#define REFF_LS_POLL_TIME 		15*60


int32_t met_poll_dbg_log(uint8_t mode, const char *p_format, ...);
int32_t redis_init(char *hostname, uint16_t port);
int32_t update_np_det_to_redis(obis_name_plate_info_t *name_plate_info, uint32_t len);
int32_t send_det_to_redis(char *msg, uint32_t len, char *key_name);
int32_t send_inst_det_to_redis(inst_val_info_t *inst_data_val,int len, char *key_name, uint8_t midx);
void 	check_od_msg_request(void);

/* Global */

#define   MAX_RESP_TIME_ENTRY 50
time_t 					g_last_hc_msg_time;
char					p_comm_port_det[16];
char					g_data_dir_path[64];
uint8_t 				g_need_to_read_obis[MAX_NO_OF_METER_PER_PORT];
uint8_t 				g_port_idx,g_midx;
char 					poll_debug_file_name[64];

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
char					g_curr_meter_ser_info[MAX_NO_OF_METER_PER_PORT][32];
char					g_prev_meter_ser_info[MAX_NO_OF_METER_PER_PORT][32];

/*  Local Micro*/
#define MET_POLL_LOG_FILE_NAME "cms_met_poll_proc"
#define INST_INFO_KEY 		"inst_info"
#define NP_INFO_KEY 		"np_info"
#define BILLING_INFO_KEY 	"billing_key_info"
#define EVENT_INFO_KEY 		"event_type_key_info"
#define LS_BLK_INFO_KEY 	"ls_blk_info"

void get_prev_met_ser_num(void)
{
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
	}
}

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
			char del_dir_cnt[32];
			
			g_midx=midx;
			met_poll_dbg_log(INFORM,"%-20s : Meter Serial num changed. Curr Meter ser : %s ,Prev Meter ser num was : %s\n",
			fun_name,g_curr_meter_ser_info[midx],g_prev_meter_ser_info[midx]);
			
			memset(del_dir_cnt,0,sizeof(del_dir_cnt));

			sprintf(del_dir_cnt,"rm -rf %s/meter_id_%d/*",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
			system(del_dir_cnt);

			char curr_ls_file_path[64];
			memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
			if(dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].meter_addr_size==1)
				sprintf(curr_ls_file_path,"%s/meter_id_%d/od",ROOT_DATA_DIR,3);
			else
				sprintf(curr_ls_file_path,"%s/meter_id_%d/od",ROOT_DATA_DIR,dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].meter_addr);
			
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
	
	memcpy(g_prev_meter_ser_info,g_curr_meter_ser_info,sizeof(g_prev_meter_ser_info));
}

int32_t read_cfg_from_redis(void)
{
	memset(&dlms_dcu_config,0,sizeof(dlms_dcu_config));
	p_redis_reply=NULL;
	uint8_t idx=0;
	char 	*p_gen_ptr=NULL;
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO DcuDevId NumEthPort MeterType DataFormatType DataTrfType MasterProtoType DbgLogEnable DcuDevLoc DcuGpsLoc DbgLogIp ReadPrevLsData FaultTolSupp");
	
	//printf("Total Elements : %d\n",p_redis_reply->elements);
	
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
		return -1;
	

	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_SERIAL_INFO NumDcuSer");
	
	//printf("NumDcuSer Total Elements : %d\n",p_redis_reply->elements);
	
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
		goto EXIT;
	
	//printf("Getting Other ser info\n");
	
	for(idx=0; idx<MAX_NO_OF_SERIAL_PORT; idx++)
	{
		//printf("Getting Serial info for Idx : %d\n",idx);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_SERIAL_INFO DcuSer%dPort DcuSer%dBaudrate DcuSer%dDataBits DcuSer%dStopBits DcuSer%dParity DcuSer%dInfMode",idx+1,idx+1,idx+1,idx+1,idx+1,idx+1);
	
		//printf("Idx : %d Total Elements : %d\n",idx+1,p_redis_reply->elements);
		
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
			goto EXIT;
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget INST_POLL_INFO Enable PollType Periodicity PollSec PollMint PollHr");

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
		
	p_redis_reply = redisCommand(p_redis_handler,"hmget BILL_POLL_INFO Enable PollType Periodicity PollSec PollMint PollHr");

	//printf("Bill Total Elements : %d\n",p_redis_reply->elements);

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
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DP_POLL_INFO Enable PollType Periodicity PollSec PollMint PollHr");

	//printf("DP Total Elements : %d\n",p_redis_reply->elements);

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
		goto EXIT;
	
	
	for(idx=0; idx<MAX_NO_OF_METER_PER_PORT; idx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSerMeter_%dConfig Enable MeterId MeterAddrSize MeterAddr MeterPass MeterLoc",idx+1);
	
		//printf("Idx : %d Total Elements : %d\n",idx+1,p_redis_reply->elements);
		
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
			goto EXIT;
	}

	return 0;
	
	EXIT:
	return -1;
}

void fill_meter_comm_params_det(meter_comm_params_t *meter_comm_params ,uint8_t midx)
{
	static char fun_name[]="fill_meter_comm_params_det()";
	
	meter_comm_params->inf_type=INF_SERIAL;
	meter_comm_params->meter_type=dlms_dcu_config.dlms_dcu_info.meter_type;
	meter_comm_params->meter_addr_format=dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].meter_addr_size;
	
	meter_comm_params->meter_id=dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].meter_addr;

	memcpy(meter_comm_params->interface_params,(char*)&dlms_dcu_config.ser_prot_cfg.ser_prot_param[g_port_idx],sizeof(dlms_dcu_config.ser_prot_cfg.ser_prot_param[g_port_idx]));
	
	sprintf(meter_comm_params->filename,"%s/meter_id_%d",ROOT_DATA_DIR,g_port_idx*MAX_NO_OF_METER_PER_PORT+midx+1);
	strcpy(meter_comm_params->meter_pass,dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].meter_pass);
	
	met_poll_dbg_log(REPORT,"%-20s : Filled Meter Comm Param details!!!, MetAddr : %d,  Addr Size : %d, PassWord : %s\n",
	fun_name,meter_comm_params->meter_id,meter_comm_params->meter_addr_format,meter_comm_params->meter_pass);
}

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

	printf("day : %d mon : %d year : %d\n",*day,*mon,*year);

	return;
}

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

void print_val_scal_onis_val_info(uint8_t* val_obis, uint8_t* scalar_obis, int8_t scalar_val)
{
	static char fun_name[]="val_obis_det()";
	
	dbg_log(INFORM,"%-20s : ValObis : %d.%d.%d.%d.%d.%d, ScalObis : %d.%d.%d.%d.%d.%d, ScalVal : %d\n",fun_name,
	val_obis[0],val_obis[1],val_obis[2],val_obis[3],val_obis[4],val_obis[5],
	scalar_obis[0],scalar_obis[1],scalar_obis[2],scalar_obis[3],scalar_obis[4],scalar_obis[5],scalar_val);
}


int main(int argc, char **argv)
{
	static char fun_name[]="main()";
	int32_t 	fun_ret=-1,idx=0;
	uint8_t 	midx=0;
	struct 			stat dir_st = {0};
	
	time_t tot_time_now,time_now;
	
	g_midx=midx;
	memset(poll_debug_file_name,0,sizeof(poll_debug_file_name));
	
	if(argc < 2)
	{
		printf("Please provide port details!!, recv numof argument : %d\n",argc);
		return -1;
	}
	
	g_last_hc_msg_time=time(NULL);
	
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
	read_cfg_from_redis();
	
	g_midx=midx;
	met_poll_dbg_log(INFORM,"%-20s : Uart Port det for this Port : %s\n",
	fun_name,dlms_dcu_config.ser_prot_cfg.ser_prot_param[g_port_idx].ser_port);
	
	g_last_hc_msg_time=time(NULL);
	
	memset(&meter_comm_params,0,sizeof(meter_comm_params_t));
	fill_meter_comm_params_det(&meter_comm_params,0);
	
	//printf(">>> Filled ls data dir path : %s\n",meter_comm_params.filename);
	
	send_hc_msg();
	
	fun_ret = init_comm(&meter_comm_params);
	if(fun_ret<0)
	{
		g_midx=midx;
		met_poll_dbg_log(REPORT,"%-20s : Failed to initilized communication Error Code : %d\n",fun_name,fun_ret);
		return -1;
	}
	
	met_poll_dbg_log(INFORM,"%-20s : Communication establised\n",fun_name);
	
	for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
	{
		g_midx=midx;
		
		send_hc_msg();
		
		if(!dlms_dcu_config.dlms_channel_cfg[g_port_idx].met_cfg[midx].enable)
		{
			continue;
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

#if 1
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
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Conneted to meter.\n",fun_name);
				p_redis_reply = redisCommand(p_redis_handler, "HMSET SerPort%dMet%dStatus VALUE %d",g_port_idx,midx,1);
				freeReplyObject(p_redis_reply);
			}
			
			send_hc_msg();
			
			memset(&gen_inst_param_det[midx],0,sizeof(gen_params_det_t));
			memset(&gen_ls_param_det[midx],0,sizeof(gen_params_det_t));
			memset(&gen_bill_param_det[midx],0,sizeof(gen_params_det_t));
			memset(&gen_daily_prof_param_det[midx],0,sizeof(gen_params_det_t));
			memset(&gen_event_param_det[midx],0,sizeof(gen_params_det_t));
			memset(&name_plate_info[midx],0,sizeof(obis_name_plate_info_t));
			
			fun_ret = get_nameplate_details(&meter_comm_params, &name_plate_info[midx]);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to get nameplate info from Meter Error Code : %d\n",
				fun_name,fun_ret);
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Recv Nameplate from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
				
				update_np_det_to_redis(&name_plate_info[midx],midx);
			}
			
			send_hc_msg();
			
			time_now=time(NULL);
			
			fun_ret = get_obis_codes(&meter_comm_params,&gen_inst_param_det[midx],&gen_ls_param_det[midx],
			&gen_event_param_det[midx],&gen_bill_param_det[midx],&gen_daily_prof_param_det[midx]);
			if(fun_ret<0)
			{
				g_need_to_read_obis[midx]=1;
				met_poll_dbg_log(REPORT,"%-20s : Failed to obis info from Meter Error Code : %d\n",fun_name,fun_ret);
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Recv all obis code from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
				g_need_to_read_obis[midx]=0;
				
				for(idx=0; idx<gen_inst_param_det[midx].tot_num_val_obis; idx++)
					print_val_scal_onis_val_info(gen_inst_param_det[midx].val_obis[idx],gen_inst_param_det[midx].scalar_val[idx].obis_code,gen_inst_param_det[midx].scalar_val[idx].value);
				
				for(idx=0; idx<gen_ls_param_det[midx].tot_num_val_obis; idx++)
					print_val_scal_onis_val_info(gen_ls_param_det[midx].val_obis[idx],gen_ls_param_det[midx].scalar_val[idx].obis_code,gen_ls_param_det[midx].scalar_val[idx].value);
				
				for(idx=0; idx<gen_event_param_det[midx].tot_num_val_obis; idx++)
					print_val_scal_onis_val_info(gen_event_param_det[midx].val_obis[idx],gen_event_param_det[midx].scalar_val[idx].obis_code,gen_event_param_det[midx].scalar_val[idx].value);
				
				for(idx=0; idx<gen_bill_param_det[midx].tot_num_val_obis; idx++)
					print_val_scal_onis_val_info(gen_bill_param_det[midx].val_obis[idx],gen_bill_param_det[midx].scalar_val[idx].obis_code,gen_bill_param_det[midx].scalar_val[idx].value);
				
				for(idx=0; idx<gen_daily_prof_param_det[midx].tot_num_val_obis; idx++)
					print_val_scal_onis_val_info(gen_daily_prof_param_det[midx].val_obis[idx],gen_daily_prof_param_det[midx].scalar_val[idx].obis_code,gen_daily_prof_param_det[midx].scalar_val[idx].value);
			}
			
			return 0;
			
			send_hc_msg();
			time_now=time(NULL);
			memset(&g_all_inst_param_obis_val,0,sizeof(g_all_inst_param_obis_val));
			memset(&g_inst_data_val,0,sizeof(inst_val_info_t));
			
			fun_ret = get_inst_values(&meter_comm_params, &g_inst_data_val);
			if(fun_ret<0)
			{
				met_poll_dbg_log(REPORT,"%-20s : Failed to inst info from Meter Error Code : %d\n",fun_name,fun_ret);
				continue;
			}
			else
			{
				met_poll_dbg_log(INFORM,"%-20s : Recv Inst Data from meter. Time elasped : %ld sec\n",fun_name,time(NULL)-time_now);
				
				memcpy(&g_all_inst_param_obis_val,&meter_comm_params.meter_response,sizeof(g_all_inst_param_obis_val));
				send_inst_det_to_redis(&g_inst_data_val,sizeof(inst_val_info_t),INST_INFO_KEY,midx);
			}
			
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
			}
			
			send_hc_msg();
			uint8_t event_class_type=0;
			
			for(event_class_type=0; event_class_type<7; event_class_type++)
			{
				send_hc_msg();
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
			}
			
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
			}
			
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
			}
			
			send_hc_msg();
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
				
				tot_time_now=time(NULL);
				
				for(idx=0; idx<LAST_NUM_DAYS_LS_READ; idx++)
				{
					send_hc_msg();
					
					time_now = time(NULL);
					
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
					
					fun_ret = get_ls_values_day_range(&meter_comm_params,1);
					if(fun_ret<0)
					{
						met_poll_dbg_log(REPORT,"%-20s : Failed to prev day ls data from Meter Error Code : %d\n",
						fun_name,midx,fun_ret);
					}
					else
					{
						met_poll_dbg_log(REPORT,"%-20s : Recv Prev day ls data for day : %02d_%02d_%04d\n",
						fun_name,meter_comm_params.from.day,meter_comm_params.from.month,meter_comm_params.from.year);
						
						met_poll_dbg_log(REPORT,"%-20s : Total Time taken to get 1 day ls data : %ld\n",fun_name,time(NULL)-time_now);
					}
					
					time_of_day = time_of_day-(60*60*24);
				}
				
				met_poll_dbg_log(REPORT,"%-20s : Total Time taken to get all prev day ls data : %ld\n",fun_name,time(NULL)-tot_time_now);
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
	
#endif
	
	time_t curr_time ,ls_curr_time,time_of_day;
	struct tm st_time,time_stamp;
	
	time_t g_last_inst_read_time = time(NULL);
	time_t g_last_ls_read_time = time(NULL);
	time_t g_last_dp_read_time = time(NULL);
	time_t g_last_event_read_time = time(NULL);
	time_t g_last_bill_read_time = time(NULL);
	
	struct tm *p_curr_time=NULL;
	
	g_midx=0;
	met_poll_dbg_log(REPORT,"%-20s : Entering into Idle polling loop!!!!\n",fun_name);
	
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
		
		fun_ret = get_nameplate_details(&meter_comm_params, &name_plate_info);
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
				memset(&name_plate_info,0,sizeof(obis_name_plate_info_t));
				fun_ret = get_nameplate_details(&meter_comm_params, &name_plate_info);
				if(fun_ret<0)
				{
					met_poll_dbg_log(REPORT,"%-20s : Failed to get nameplate info from Meter Error Code : %d\n",fun_name,fun_ret);
					continue;
				}
				else
				{
					met_poll_dbg_log(REPORT,"%-20s : Recv Nameplate from meter !!! : %d\n",fun_name);
					update_np_det_to_redis(&name_plate_info,midx);
				}
			
				if(g_need_to_read_obis[midx]==1)
				{
					memset(&gen_inst_param_det[midx],0,sizeof(gen_params_det_t));
					memset(&gen_ls_param_det[midx],0,sizeof(gen_params_det_t));
					memset(&gen_bill_param_det[midx],0,sizeof(gen_params_det_t));
					memset(&gen_daily_prof_param_de[midx]t,0,sizeof(gen_params_det_t));
					memset(&gen_event_param_det[midx],0,sizeof(gen_params_det_t));
					
					fun_ret = get_obis_codes(&meter_comm_params,&gen_inst_param_det[midx],&gen_ls_param_det[midx],
					&gen_event_param_det[midx],&gen_bill_param_det[midx],&gen_daily_prof_param_det[midx]);
					if(fun_ret<0)
					{
						met_poll_dbg_log(REPORT,"%-20s : Failed to obis info from Meter Error Code : %d\n",fun_name,fun_ret);
						continue;
					}
					else
					{
						g_need_to_read_obis[midx]=0;
					}
				}
				
				if(dlms_dcu_config.dcu_poll_info.inst_poll_info.enable)
				{
					if((curr_time-g_last_inst_read_time)>=REFF_INST_POLL_TIME)
					{
						time_t curr_inst_time;
						curr_inst_time=time(NULL);
						g_last_inst_read_time=curr_time;
						memset(&g_inst_data_val,0,sizeof(g_inst_data_val));
		
						fun_ret = get_inst_values(&meter_comm_params, &g_inst_data_val);
						if(fun_ret<0)
						{
							met_poll_dbg_log(INFORM,"%-20s : Failed to get inst value. Error Code : %d\n",fun_name,fun_ret);
							
							continue;
						}
						else
						{
							met_poll_dbg_log(INFORM,"%-20s : Recv Inst Data, Time Resp taken in sec : %ld\n",fun_name,(time(NULL)-curr_inst_time));
							
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
							
							memcpy(&g_all_inst_param_obis_val,&meter_comm_params.meter_response,sizeof(g_all_inst_param_obis_val));
							send_inst_det_to_redis(&g_inst_data_val,sizeof(inst_val_info_t),INST_INFO_KEY,midx);
						}
					}
				}
				
				if(dlms_dcu_config.dcu_poll_info.bill_poll_info.enable)
				{
					if((curr_time-g_last_bill_read_time)>dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_hr*60*60)
					{
						time_t curr_bill_time=time(NULL);
						send_hc_msg();
						g_last_bill_read_time=curr_time;
						
						fun_ret = get_billing_info(&meter_comm_params);
						if(fun_ret<0)
						{
							met_poll_dbg_log(INFORM,"%-20s : Failed to get Billing Profile value. Error Code : %d\n",fun_name,fun_ret);
							continue;
						}
						else
						{
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
								
								met_poll_dbg_log(INFORM,"%-20s : Avg Time for Last 50 Billing data type qry-response : %ld\n",fun_name,g_avg_bill_resp_time);
								//printf("Avg Time for Last 50 Billing data type qry-response : %ld\n",g_avg_bill_resp_time);
								
								p_redis_reply = redisCommand(p_redis_handler,"hmset BILL AVG_BILL_RESP_TIME %d",g_avg_bill_resp_time);
								
								freeReplyObject(p_redis_reply);				
							}
							//send_det_to_redis((char*)&g_inst_data_val,sizeof(g_inst_data_val),INST_INFO_KEY);
						}
					}
				}
					
				if(dlms_dcu_config.dcu_poll_info.event_poll_info.enable)
				{
					time_t curr_event_time=time(NULL);
					
					if((curr_time-g_last_event_read_time)>REFF_EVENT_POLL_TIME)
					{
						g_last_event_read_time=curr_time;
						uint8_t event_class_type=0;
						event_val_info_t event_val_info;
						
						for(event_class_type=0; event_class_type<7; event_class_type++)
						{
							fun_ret = get_event_data(&meter_comm_params,event_class_type);
							if(fun_ret<0)
							{
								met_poll_dbg_log(INFORM,"%-20s : Failed to get Event data for event class : %d, Error Code : %d\n",fun_name,event_class_type,fun_ret);
								//printf("Failed to get Event data for event class : %d, Error Code : %d\n",event_class_type,fun_ret);
								continue;
							}
							else
							{
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
								
								memcpy(&event_val_info,&meter_comm_params.meter_response,sizeof(event_val_info_t));
								//send_det_to_redis((char*)&event_val_info,sizeof(event_val_info_t),event_key_buff);
							}
						}
					}
				}
					
				if(dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.enable)
				{
					time_t curr_dp_time=time(NULL);
					
					if((curr_time-g_last_dp_read_time)>dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_hr*60*60)
					{
						send_hc_msg();
						g_last_dp_read_time=curr_time;
						
						fun_ret = get_midnight_data(&meter_comm_params);
						if(fun_ret<0)
						{
							met_poll_dbg_log(INFORM,"%-20s : Failed to get Daily Profile value. Error Code : %d\n",fun_name,fun_ret);
							//printf("Failed to get Daily Profile value. Error Code : %d\n",fun_ret);
							continue;
						}
						else
						{
							g_dp_resp_time[midx][g_dp_resp_time_cnt]=(time(NULL)-curr_dp_time);
							p_redis_reply = redisCommand(p_redis_handler,"hmset DP SINGLE_DP_RESP_TIME %d",
							(time(NULL)-curr_dp_time));
							
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
				
				if(dlms_dcu_config.dcu_poll_info.ls_poll_info.enable)
				{
					time_t curr_ls_time=time(NULL);

					if((curr_time-g_last_ls_read_time)>REFF_LS_POLL_TIME)
					{
						send_hc_msg();
						g_last_ls_read_time=curr_time;
						
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
							met_poll_dbg_log(INFORM,"%-20s : Ls Time Resp taken in sec : %ld\n",fun_name,(time(NULL)-curr_ls_time));
							
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
							
							block_val_info_t g_block_val_info;
							
							memcpy(&g_block_val_info,&meter_comm_params.meter_response,sizeof(block_val_info_t));
							
							//send_det_to_redis((char*)&g_block_val_info,sizeof(block_val_info_t),LS_BLK_INFO_KEY);
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

/* End Of File */