/**********************************************************************************
* Copyright (c) 2019 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	iot_modbus_poll_proc.c
* Summary:  Modbus g_query response process

***********************************************************************************/

/*** Include ***/
#include "iot_general.h"
#include "iot_modbus_rel.h"
#include "iot_dev_config.h"
#include "iot_ipc_msg.h"
#include <hiredis.h>
int32_t send_comm_mon_qry(void);
int32_t send_comm_mon_resp(void);
int send_diag_info(uint8_t g_midx, const char *format, ...);

/* Local Micro */
#define 								ERROR_RESP_LEN 			5

#define 								MAX_REGS_READ  			20
#define 								DEF_GAP_REG  			10

/* Structure */
function_grp_t 							fun_grp[MAX_NO_OF_METER_PER_PORT][6];
modbus_grp_str_t 						mod_grp_str[MAX_REG_PER_METER],temp_mod_grp_str;
mod_time_info_t							g_mod_time_info[MAX_NO_OF_METER_PER_PORT];

/* Extern */
extern iot_dev_cfg_t					iot_dev_cfg;
extern ipc_msg_t                        ipc_msg;
extern iot_data_list_t                  iot_data_list;
extern iot_stats_t						iot_stats[];
extern iot_event_data_t  				iot_event_data;
extern uint8_t 							g_pidx,g_midx;
extern uint8_t							g_recv_ser_buff[];
extern uint16_t							g_met_reg_offset;
extern uint8_t 							g_ser_mon_flag;
extern 	redisContext *c;
extern 	redisReply *reply; 
/* Globals */
uint8_t 								g_fun_idx;
char 									g_query[SIZE_256];

uint8_t									g_falty_cnt[MAX_NO_OF_METER_PER_PORT];
/* ------------------------------------------------------------------------------------------------ */






/*********************************************************************
*Function 		: send_diag_info()
*In Params 		: Meter Idx and format.
*Output 		: None
*Return			: void.
*Description 	: to send diag info to redis
**********************************************************************/
int send_diag_info(uint8_t g_midx, const char *format, ...)
{
	char msg[256];
	memset(msg,0,256);
	struct tm	*curr_time_str=NULL;
	char		time_str[SIZE_64];
	time_t 		curr_time = 0;
	
	curr_time = time(NULL);
	curr_time_str = localtime(&curr_time);
	strftime(time_str, SIZE_64,"%d/%b/%Y_%H:%M:%S", curr_time_str);
	sprintf(msg,"updatetime %s diag_msg: %s",time_str,format);
	reply = redisCommand(c,"lpush serport%d_meter%d_diag_msg %s",g_pidx,g_midx,msg);
	freeReplyObject(reply);
	return RET_OK;
}
/*********************************************************************
*Function 		: store_query()
*In Params 		: Meter Idx and reg_idx.
*Output 		: None
*Return			: void.
*Description 	: group and store all configured queries based on func codes
**********************************************************************/
void store_query(uint8_t dev_idx,uint8_t idx)
{
	uint8_t fun_idx=0,fun_type_found = 0,qry_num=0;

	for ( fun_idx = 0;fun_idx < MAX_FN_TYPES; fun_idx++ )
	{
		if ( fun_grp[dev_idx][fun_idx].fun_code == iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[idx].func_code )
		{
			qry_num=fun_grp[dev_idx][fun_idx].num_query;
			fun_grp[dev_idx][fun_idx].mod_grp_str[qry_num].start_add=iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[idx].start_addr;
			fun_grp[dev_idx][fun_idx].mod_grp_str[qry_num].num_of_regs=iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[idx].num_of_regs;
			fun_grp[dev_idx][fun_idx].num_query++;
			fun_type_found = 1;
			break;
		}
	}
	
	if ( !fun_type_found )
	{
		fun_grp[dev_idx][g_fun_idx].fun_code = iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[idx].func_code;
		fun_grp[dev_idx][g_fun_idx].mod_grp_str[fun_grp[dev_idx][g_fun_idx].num_query].start_add=iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[idx].start_addr;
		fun_grp[dev_idx][g_fun_idx].mod_grp_str[fun_grp[dev_idx][g_fun_idx].num_query].num_of_regs=iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[idx].num_of_regs;
		fun_grp[dev_idx][g_fun_idx].num_query++;
		g_fun_idx++;
	}
}

/*********************************************************************
*Function 		: sort_query()
*In Params 		: Meter Idx and reg_idx.
*Output 		: None.
*Return			: void.
*Description 	: sort queries in ascending order within the func code
**********************************************************************/
void sort_query(int dev_idx,int idx)
{
	uint8_t qry_idx,sub_qry_idx;
	
	for ( qry_idx = 0; qry_idx < fun_grp[dev_idx][idx].num_query; qry_idx++ )
	{
		for ( sub_qry_idx = 0; sub_qry_idx < fun_grp[dev_idx][idx].num_query-1; sub_qry_idx++ )
		{
			if ( fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx].start_add > fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx+1].start_add )
			{
				memset(&temp_mod_grp_str,0,sizeof(temp_mod_grp_str));
				temp_mod_grp_str.start_add = fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx].start_add;
				temp_mod_grp_str.num_of_regs = fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx].num_of_regs;
				fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx].start_add = fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx+1].start_add;
				fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx].num_of_regs = fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx+1].num_of_regs;
				fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx+1].start_add = temp_mod_grp_str.start_add;
				fun_grp[dev_idx][idx].mod_grp_str[sub_qry_idx+1].num_of_regs = temp_mod_grp_str.num_of_regs;
			}
		}
	}
}

/*********************************************************************
*Function 		: init_and_sort_query()
*In Params 		: void.
*Output 		: None.
*Return			: Status.
*Description 	: Initiliazation and sorting of queries
**********************************************************************/
int32_t init_and_sort_query(void)
{
	static char 		fun_name[]="init_and_sort_query()";
	uint8_t 			dev_idx=0,fun_idx=0,num_entry=0;
	
	//printf("num_of_devices : %d\n",iot_dev_cfg.chan_cfg[g_pidx].num_of_devices);
	
	for ( dev_idx = 0; dev_idx < iot_dev_cfg.chan_cfg[g_pidx].num_of_devices; dev_idx++ ) // Form Sorted Array Acc to FunCode
	{
		g_fun_idx = 0;
		g_midx=dev_idx;
		
		memset(&fun_grp[dev_idx],0,sizeof(fun_grp[0]));
		if(iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].enable_device==0) // Check Device is Up or Not
			continue;

		for ( num_entry = 0; num_entry < iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.num_of_points; num_entry++ )
		{
			store_query(dev_idx,num_entry);
		}
		
		//printf("DevIdx : %d , Qry stored.\n",dev_idx);
		
		for (fun_idx = 0; fun_idx < g_fun_idx; fun_idx++ )
		{
			sort_query(dev_idx,fun_idx);
		}
	}
	
	return RET_OK;
}

int32_t poll_mod_dev1(void)
{
	send_query(1,3,99,2);
	
	return RET_OK;
}

/*********************************************************************
*Function 		: poll_mod_dev()
*In Params 		: void.
*Output 		: None.
*Return			: Status.
*Description 	: poll all sorted queries.
**********************************************************************/
int32_t poll_mod_dev(void)
{
	static char 					fun_name[]="poll_mod_dev()";
	int32_t 						ret=0;
	uint8_t 						dev_idx=0,fun_code=0,num_entry=0,fun_idx,qry_Idx=0;
	int32_t 						num_of_regs = 0,start_addr2 = -1,num_reg_gap=0;
	/* time_t 							dev_curr_time, qry_curr_time; */
	
	memset(g_mod_time_info,0,sizeof(g_mod_time_info));
	
	for ( dev_idx = 0; dev_idx <MAX_NO_OF_METER_PER_PORT; dev_idx++ )
	{
		write_hc_msg_on_redis();
		g_midx = dev_idx;
		
		dbg_log(INFORM,"%-25s : Polling ModMetIdx : %d Status : %s TotalReg : %d\n",
			fun_name,dev_idx,(iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].enable_device)?"Enable":"Disable",
							iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.num_of_points);

		if((iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].enable_device))
		{
			send_diag_info(dev_idx,"SlaveId : %d Polling Started",
			iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr);
			
			/* dev_curr_time = time(NULL); */
			
			if(iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].dev_status == DEVICE_BAD)
			{
				write_hc_msg_on_redis();
				g_falty_cnt[dev_idx]++;
				
				send_diag_info(dev_idx,"SlaveId : %d Device Status is Bad, Faulty count is : %d",
				iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,g_falty_cnt[dev_idx]);
			
				if(g_falty_cnt[dev_idx]<=MAX_FLTY_CNT)
				{
					write_hc_msg_on_redis();
					continue;				
				}
				else
				{
					write_hc_msg_on_redis();
					send_diag_info(dev_idx,"SlaveId : %d Device Status is Bad, Reached Max Faulty count need to poll again",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr);
				
					dbg_log(INFORM,"%-25s : ModMetIdx : %d reached MAX_FLTY_CNT need to poll again.\n",fun_name,dev_idx);
					g_falty_cnt[dev_idx]=0;
					iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].dev_status = DEVICE_GOOD;
				}
			}
			
			g_mod_time_info[dev_idx].dev_id=dev_idx;

			gettimeofday(&g_mod_time_info[dev_idx].send_qry_time,NULL);
	
			for ( fun_idx = 0; fun_idx < MAX_FN_TYPES; fun_idx++ )
			{
				write_hc_msg_on_redis();
				if(iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].dev_status == DEVICE_BAD)
					break;

				if (( fun_grp[dev_idx][fun_idx].fun_code == WRITE_SINGLE_COIL ) || ( fun_grp[dev_idx][fun_idx].fun_code == 0 ))
					continue;

				start_addr2 = -1;num_of_regs = 0;num_reg_gap = 0;
				
				dbg_log(INFORM,"%-25s : FunCode : %d :: TotalNumQry : %d\n",
				fun_name,fun_grp[dev_idx][fun_idx].fun_code,fun_grp[dev_idx][fun_idx].num_query);
				
				send_diag_info(dev_idx,"SlaveId : %d Sending qry for FunCode : %d :: TotalNumQry : %d",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,
					fun_grp[dev_idx][fun_idx].fun_code,fun_grp[dev_idx][fun_idx].num_query);
					
				for ( qry_Idx = 0; qry_Idx < fun_grp[dev_idx][fun_idx].num_query; qry_Idx++ )
				{
			
					write_hc_msg_on_redis();
					if (qry_Idx < (fun_grp[dev_idx][fun_idx].num_query - 1 ))
					{
						/* dbg_log(INFORM,"%-25s : start_addr : %d num_of_regs : %d +1 start_addr : %d num_of_regs : %d totNumRegs : %d num_reg_gap : %d\n",fun_name,
								fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add,fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs,
								fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx+1].start_add,fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx+1].num_of_regs,num_of_regs,num_reg_gap); */
				
						if ( ( fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs ) == fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx+1].start_add )
						{
							write_hc_msg_on_redis();
							if ( start_addr2 == -1 )
								start_addr2 = fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add;

							num_of_regs = num_of_regs + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs;
							
							if ( num_of_regs < MAX_REGS_READ )
								continue;
							else
							{
								dbg_log(INFORM,"%-25s : Cont start_addr : %d num_of_regs : %d start_addr2 : %d numGap : %d totNumRegs : %d\n",fun_name,
									fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add,
									fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs,
									start_addr2,num_reg_gap,num_of_regs);

								if ( start_addr2 != -1 )
								{
									dbg_log(INFORM,"%-25s : Query to be sent, StartAddr : %d num_of_regs : %d\n",fun_name,start_addr2,num_of_regs);
									send_query(dev_idx,fun_grp[dev_idx][fun_idx].fun_code,start_addr2,num_of_regs);
									//start_addr2 = -1;num_of_regs = 0;num_reg_gap = 0;
								}
								else
								{
									//should never come here
									start_addr2 = fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add;
									num_of_regs = fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs;
									dbg_log(INFORM,"%-25s : Last entry After for loop, Query to be sent, StartAddr : %d num_of_regs : %d\n",fun_name,start_addr2,num_of_regs);
									send_query(dev_idx,fun_grp[dev_idx][fun_idx].fun_code,start_addr2,num_of_regs);
									//start_addr2 = -1;num_of_regs = 0;num_reg_gap = 0;
								}
								start_addr2 = -1;num_of_regs = 0;num_reg_gap = 0;
							}
						}
						else
						{
							write_hc_msg_on_redis();
							//dbg_log(INFORM,"%-25s : GAP in start Addr\n",fun_name);
							if (( start_addr2 == -1 ) || ( num_of_regs == 0 ))
							{
								dbg_log(INFORM,"%-25s : GAP in start Addr : May be single entry Or next qry to be sent\n",fun_name);
								
								start_addr2 = fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add;
					
								num_of_regs = fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs;
						
								num_reg_gap += fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx+1].start_add - ( fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs ) ;
						
								dbg_log(INFORM,"%-25s : start_addr2 : %d num_of_regs : %d numGap : %d\n",fun_name,start_addr2,num_of_regs,num_reg_gap);
								
								if ( num_reg_gap < DEF_GAP_REG )
								{
									dbg_log(INFORM,"%-25s : GAP in start Addr : num_reg_gap < 20\n",fun_name);
									continue;
								}
								else
								{
									write_hc_msg_on_redis();
									//dbg_log(INFORM,"%-25s : Gap > 20 Query to be sent, StartAddr : %d num_of_regs : %d\n",fun_name,start_addr2,num_of_regs);
									send_query(dev_idx,fun_grp[dev_idx][fun_idx].fun_code,start_addr2,num_of_regs);
									start_addr2 = -1;num_of_regs = 0;num_reg_gap = 0;	
								}
							}
							else
							{
								write_hc_msg_on_redis();
								if (( fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx+1].start_add - ( fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs ) < DEF_GAP_REG ) &&
										( ( num_of_regs + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs + num_reg_gap + ( fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx+1].start_add - ( fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs )) < MAX_REGS_READ )))
								{
									num_reg_gap += (fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx+1].start_add) - ( fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs ) ;
									num_of_regs = num_of_regs + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs;
									dbg_log(INFORM,"%-25s : Gap < 20 start_addr2 : %d num_of_regs : %d numGap : %d\n",fun_name,start_addr2,num_of_regs,num_reg_gap);
									continue;
								}
								else
								{
									write_hc_msg_on_redis();
									num_of_regs = num_of_regs + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs + num_reg_gap;
									dbg_log(INFORM,"%-25s : Gap > 20 or num_of_regs > 100 Query to be sent, StartAddr %d num_of_regs %d\n",fun_name,start_addr2,num_of_regs);
									send_query(dev_idx,fun_grp[dev_idx][fun_idx].fun_code,start_addr2,num_of_regs);
									start_addr2 = -1;num_of_regs = 0;num_reg_gap = 0;
								}
							}
						}
					}
					else //last entry for that fc
					{
						write_hc_msg_on_redis();
						dbg_log(INFORM,"%-25s : j < num_query-1 start_addr : %d num_of_regs : %d start_addr2 : %d numGap : %d\n",fun_name,
								fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add,fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs,start_addr2,num_reg_gap);

						if ( start_addr2 != -1 )
						{
							num_of_regs = num_of_regs + fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs + num_reg_gap;
							
							dbg_log(INFORM,"%-25s : After for loop, Query to be sent, StartAddr : %d num_of_regs : %d\n",
							fun_name,start_addr2,num_of_regs);
							
							send_query(dev_idx,fun_grp[dev_idx][fun_idx].fun_code,start_addr2,num_of_regs);
							//start_addr2 = -1;num_of_regs = 0;num_reg_gap = 0;
						}
						else
						{
							start_addr2 = fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].start_add;
							num_of_regs = fun_grp[dev_idx][fun_idx].mod_grp_str[qry_Idx].num_of_regs;
							
							dbg_log(INFORM,"%-25s : &&&& Last entry After for loop, Query to be sent, StartAddr : %d num_of_regs : %d\n",
							fun_name,start_addr2,num_of_regs);
							
							send_query(dev_idx,fun_grp[dev_idx][fun_idx].fun_code,start_addr2,num_of_regs);
							//start_addr2 = -1;num_of_regs = 0;num_reg_gap = 0;
						}
						start_addr2 = -1; num_of_regs = 0; num_reg_gap = 0;
					}
					
					gettimeofday(&g_mod_time_info[dev_idx].recv_resp_time,NULL);
					write_hc_msg_on_redis();
					g_mod_time_info[dev_idx].time_taken=(
					(double) (g_mod_time_info[dev_idx].recv_resp_time.tv_usec - g_mod_time_info[dev_idx].send_qry_time.tv_usec)/ 1000000
					+ (double) (g_mod_time_info[dev_idx].recv_resp_time.tv_sec - g_mod_time_info[dev_idx].send_qry_time.tv_sec));
			
					dbg_log(INFORM,"%-25s : MeterIdx : %d Total time taken for this qry_resp : %0.4f sec\n",
					fun_name,g_midx,g_mod_time_info[dev_idx].time_taken);
					
					send_diag_info(dev_idx,"SlaveId : %d FucnCode : %d ,Total time taken for this qry_resp : %0.4f sec",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,
					fun_grp[dev_idx][fun_idx].fun_code,
					g_mod_time_info[dev_idx].time_taken);
					
				}//for each query in a device
			}//for each fun_code in a device
			write_hc_msg_on_redis();
			fill_polled_data(dev_idx);
			
			//send_polled_data(dev_idx);
		}
		else
			continue;
		write_hc_msg_on_redis();
		sleep(1);
	}//for each device
	
	dev_idx = 0;
	double avg_poll_time=0;
	for ( dev_idx = 0; dev_idx <MAX_NO_OF_METER_PER_PORT; dev_idx++ )
	{
		write_hc_msg_on_redis();
		avg_poll_time=avg_poll_time+g_mod_time_info[dev_idx].time_taken;
	}
	
	dbg_log(INFORM,"%-25s : Total  time take for 1 poll : %0.4f sec\n",fun_name,avg_poll_time);
	
	dev_idx = 0;
	send_diag_info(dev_idx,"SlaveId : %d Total  time take for 1 Complete poll : %0.4f sec",
			iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,avg_poll_time);
		write_hc_msg_on_redis();	
	return RET_OK;
}

/*********************************************************************
*Function 		: send_query()
*In Params 		: Meter Idx, fun_code,start_addr,num_of_points
*Output 		: None.
*Return			: Void.
*Description 	: send qry to device, validate resp and proc response.
**********************************************************************/
void send_query(uint8_t dev_idx,uint8_t fun_code,uint16_t start_addr,uint16_t num_of_points)
{
	write_hc_msg_on_redis();
	static char fun_name[] = "send_query()";
	uint8_t slave_addr=0,retry_idx;

	slave_addr = iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr;
	
	dbg_log(INFORM,"%-25s : Sending query slave_addr : %d fun_code : %d start_addr : %d num_of_regs : %d\n",
	fun_name,slave_addr,fun_code,start_addr,num_of_points);

	send_diag_info(dev_idx,"SlaveId : %d Sending query FunCode : %d start_addr : %d num_of_regs : %d",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,
					fun_code,start_addr,num_of_points);
					
	memset(g_query,0,sizeof(g_query));

	for ( retry_idx = 0; retry_idx < iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].retries; retry_idx++ )
	{ 
		write_hc_msg_on_redis();
		int32_t ret_ser_read = -1;
		
		build_send_query(slave_addr,fun_code,start_addr,num_of_points);
		
		if(g_ser_mon_flag)
			send_comm_mon_qry();
		
		ret_ser_read = read_serial_port(dev_idx);
		write_hc_msg_on_redis();
		if(g_ser_mon_flag)
			send_comm_mon_resp();
		write_hc_msg_on_redis();
		if ( ret_ser_read <= 0 )
		{
			write_hc_msg_on_redis();
			send_diag_info(dev_idx,"SlaveId : %d Failed to read serial, Retry val : %d",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,(retry_idx+1));
					
			dbg_log(INFORM,"%-25s : read serial failed for MeterIdx : %d Retry val : %d\n",fun_name,dev_idx,(retry_idx+1));
			
			if ( retry_idx!= ( iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].retries - 1))
				continue;
			
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].dev_status = DEVICE_BAD;
		}
		else
		{
			write_hc_msg_on_redis();
			send_diag_info(dev_idx,"SlaveId : %d Got response",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr);
					
			dbg_log(INFORM,"%-25s : Got response for MeterIdx : %d fun_code : %d\n",fun_name,dev_idx,fun_code);
			
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].dev_status = DEVICE_GOOD;

			if ( validate_response(dev_idx, ret_ser_read) == -1 )
			{
				iot_stats[g_midx].invalid_resp_cnt++;
				
				send_diag_info(dev_idx,"SlaveId : %d Invalid Response received, Retry val : %d",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,(retry_idx+1));
					
				dbg_log(REPORT,"%-25s : Failed to validate device response for MeterIdx : %d\n",fun_name,dev_idx);
				
				if ( retry_idx != ( iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].retries - 1))
					continue;
				
				goto EXIT ;
			}
			
			iot_stats[g_midx].valid_resp_cnt++;
			
			send_diag_info(dev_idx,"SlaveId : %d Valid Response received",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr);
					
			proc_modbus_resp(ret_ser_read,start_addr,fun_code,dev_idx,num_of_points);
			write_hc_msg_on_redis();
			
			break;
		}
	}
	
	EXIT :
	return;
}

/*********************************************************************
*Function 		: build_send_query()
*In Params 		: Meter Idx, fun_code,start_addr,num_of_points
*Output 		: None.
*Return			: Status.
*Description 	: Build and send qry to device
**********************************************************************/
int32_t build_send_query(uint8_t slave,uint8_t function,uint16_t start_addr,uint16_t num_of_points)
{
	static char fun_name[]=	"build_send_query()";
	
	uint8_t            		num_bytes=0;
	uint16_t 				recv_crc=0;
	char  					*p_cptr=NULL;

	write_hc_msg_on_redis();

	memset(g_query,0,sizeof(g_query));
	dbg_log(INFORM,"%-25s : Recvd query slave_addr : %d fun_code : %d start_addr : %d num_of_regs : %d\n",
						fun_name,slave,function,start_addr,num_of_points);

	// Build the query first
	g_query[num_bytes++] = slave;
	g_query[num_bytes++] = function;
	g_query[num_bytes++] = (start_addr) >> 8;       // Slave address - high byte
	g_query[num_bytes++] = (start_addr) & 0x00ff;   // Slave address - low byte
	g_query[num_bytes++] = num_of_points >> 8;         // Number of registers - high byte
	g_query[num_bytes++] = num_of_points & 0x00ff;     // Number of registers - low byte
	
    recv_crc=modbus_crc16(g_query,num_bytes);
	
	p_cptr=(char*)&recv_crc;
	g_query[num_bytes++] =p_cptr[1];
	g_query[num_bytes++] =p_cptr[0];

	write_serial_port(g_query,num_bytes);
	write_hc_msg_on_redis();
	return RET_OK;	
}

/*********************************************************************
*Function 		: validate_response()
*In Params 		: resp length
*Output 		: None.
*Return			: Status.
*Description 	: validate the recv response
**********************************************************************/
int32_t validate_response(uint8_t dev_idx, int32_t ret)
{
	char  			*p_cptr=NULL;
	uint16_t 		recv_crc=0;
	write_hc_msg_on_redis();
	recv_crc=modbus_crc16((char*)g_recv_ser_buff,ret-2);
	p_cptr=(char*)&recv_crc;
	
	if(((g_recv_ser_buff[ret-1]&0XFF) == p_cptr[0]) && ((g_recv_ser_buff[ret-2]&0XFF) == p_cptr[1]))
		return RET_OK;
	else
	{
		static char fun_name[]="validate_response()";
		
		send_diag_info(dev_idx,"SlaveId : %d InValid Response received, CRC not matched",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr);
					
		dbg_log(REPORT,"%-25s : Error in CRC : Calculated : %X %X Recvd  : %X %X\n",
					fun_name,p_cptr[0],p_cptr[1],(g_recv_ser_buff[ret-2]&0XFF),(g_recv_ser_buff[ret-1]&0XFF));
		
		return RET_FAILURE;
	}
	write_hc_msg_on_redis();
}

/*********************************************************************
*Function 		: proc_modbus_resp()
*In Params 		: resp length,start_addr,fun_code,MeterIdx,num_of_points
*Output 		: None.
*Return			: Status.
*Description 	: process the recv response
**********************************************************************/
int32_t proc_modbus_resp(int32_t len,uint16_t start_addr,uint8_t fun_code,uint8_t dev_idx,uint16_t num_of_points)
{
	
	
	static char fun_name[]="proc_modbus_resp()";
	uint8_t idx=0,val_pos=0,num_reg=0;
	int8_t data_pt_idx = -1;
	
	write_hc_msg_on_redis();
	
	if((g_recv_ser_buff[1]&0x80) == 0X80)
	{
		uint8_t error_code=0;
		error_code = (g_recv_ser_buff[2]&0xFF);
		
		switch(error_code)
		{
			case  ILLEGAL_FUNCTION :
					send_diag_info(dev_idx,"SlaveId : %d Exception :: ILLEGAL_FUNCTION, Send for the qry. FunCode : %d",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,fun_code);
					
				dbg_log(REPORT,"%-25s : MeterIdx : %d ILLEGAL_FUNCTION Send for the qry. FunCode : %d\n",
						fun_name,dev_idx,fun_code);
			break;
			
			case  ILLEGAL_DATA_ADDRESS :
					send_diag_info(dev_idx,"SlaveId : %d Exception :: ILLEGAL_DATA_ADDRESS, Send for the qry. start_addr : %d",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,start_addr);
					
				dbg_log(REPORT,"%-25s : MeterIdx : %d ILLEGAL_DATA_ADDRESS Send for the qry. start_addr : %d\n",
						fun_name,dev_idx,start_addr);
			break;
			
			case  ILLEGAL_DATA_VALUE :
					send_diag_info(dev_idx,"SlaveId : %d Exception :: ILLEGAL_DATA_VALUE, Send for the qry. num_of_points : %d",
					iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].node_addr,num_of_points);
					
				dbg_log(REPORT,"%-25s : MeterIdx : %d ILLEGAL_DATA_VALUE Send for the qry. num_of_points : %d\n",
						fun_name,dev_idx,num_of_points);
			break;
			
			case  SLAVE_DEVICE_FAILURE :
				dbg_log(REPORT,"%-25s : MeterIdx : %d SLAVE_DEVICE_FAILURE Send for the qry\n",
						fun_name,dev_idx);
			break;
			
			case  ACKNOWLEDGEMENT :
				dbg_log(REPORT,"%-25s : MeterIdx : %d ACKNOWLEDGEMENT Send for the qry.\n",
						fun_name,dev_idx);			
			break;
			
			case  SLAVE_DEVICE_BUSY :
				dbg_log(REPORT,"%-25s : MeterIdx : %d ILLEGAL_FUNCTION Send for the qry. FunCode : %d\n",
						fun_name,dev_idx,fun_code);
			break;
			
			case  MEMORY_PARITY_ERROR :
				dbg_log(REPORT,"%-25s : MeterIdx : %d SLAVE_DEVICE_BUSY Send for the qry\n",
						fun_name,dev_idx);
			break;
			
			case  GATEWAY_PATH_UNAVAILABLE :
				dbg_log(REPORT,"%-25s : MeterIdx : %d GATEWAY_PATH_UNAVAILABLE Send for the qry.\n",
						fun_name);
			break;
			
			default : break;
		}
		
		return RET_FAILURE;
	}
	write_hc_msg_on_redis();
	switch(fun_code)
	{
		case WRITE_SINGLE_COIL:
		case WRITE_MULT_COIL:
		case WRITE_SINGLE_REG:
		case WRITE_MULT_REG:
		break;
		
		case READ_COIL:
		case READ_DISCRETE:

			data_pt_idx=get_mod_data_pt_idx(dev_idx,start_addr,fun_code,&num_reg);
			
			val_pos = 3;
			proc_read_coil(len,dev_idx,data_pt_idx,val_pos,num_of_points,fun_code);
			write_hc_msg_on_redis();
			
		break;
		
		case READ_HOLDING:
		case READ_INPUT:
		
			//data_pt_idx=get_mod_data_pt_idx(dev_idx,start_addr,fun_code,&num_reg);
			write_hc_msg_on_redis();
			val_pos = 3;
			
			dbg_log(INFORM,"%-25s : DevIdx : %d StartAddr : %d NumOfRegs : %d\n",fun_name,dev_idx,start_addr,num_of_points);
			for ( idx = 0; idx < num_of_points; idx++ )
			{
				data_pt_idx = get_mod_data_pt_idx(dev_idx,start_addr,fun_code,&num_reg);
				write_hc_msg_on_redis();
				if(data_pt_idx == -1)
				{
					start_addr = start_addr + 1;
					val_pos = val_pos + 2;
					continue;
				}
				
				dbg_log(INFORM,"%-25s : Proc message , val_pos : %d reg_idx : %d ValIdx : %d\n",fun_name,val_pos,data_pt_idx,idx);
				
				val_pos = proc_read_register(val_pos,dev_idx,data_pt_idx,idx,fun_code);
				
				start_addr = start_addr + num_reg;
			}
		break;
		
		default : break;
	}
	write_hc_msg_on_redis();
	return RET_OK;
}

/*********************************************************************
*Function 		: proc_read_coil()
*In Params 		: 
*Output 		: None.
*Return			: Status.
*Description 	: process the read coil fun_code
**********************************************************************/
int32_t proc_read_coil(uint8_t len, uint8_t dev_idx, uint8_t reg_idx, uint8_t pos, uint8_t num_of_points,uint8_t fun_code)
{
	static char fun_name[]="proc_read_coil()";
	uint8_t idx=0,pos_idx=0,num_resp_byte=0;
	uint16_t data_val=0;
	uint32_t data_idx=0;
	
	if((num_of_points%8)==0)
		num_resp_byte=num_of_points/8;
	else
		num_resp_byte=(num_of_points/8)+1;
	
	for(pos_idx = pos; pos_idx < len-2; pos_idx++)
	{
		data_val=g_recv_ser_buff[pos_idx]&0xFF;
		
		iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[reg_idx + pos_idx - pos].curr_reg_val[0] = data_val;
		
		dbg_log(INFORM,"%-25s : dev_idx : %d pos_idx : %d, reg_idx : %d num_of_points : %d num_resp_byte : %d data_val : %X\n",
					fun_name,dev_idx,pos_idx,reg_idx,num_of_points,num_resp_byte,data_val);
					
	}
	
/* 	if(num_resp_byte==1)
	{
		data_val=g_recv_ser_buff[pos]&0xFF;
	}
	else
	{
		uint16_t data_val1 = g_recv_ser_buff[pos]&0xFF;
		
		data_val= g_recv_ser_buff[pos+1]&0xFF;
		data_val = data_val | (data_val1<<8);
	} */
	
/* 	for(idx=reg_idx;idx<num_of_points;idx++)
	{
		iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[idx].reg_val[0]=((data_val>>idx)&0x01);
		//printf("%d ",iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[idx].reg_val[0]);
	} */
	
	//printf("\n");
	
	return RET_OK;
}

/*********************************************************************
*Function 		: get_mod_data_pt_idx()
*In Params 		: MeterIdx,start_addr,fun_code
*Output 		: None.
*Return			: reg_idx.
*Description 	: search for valid reg_idx
**********************************************************************/
int32_t get_mod_data_pt_idx(uint8_t dev_idx,uint16_t start_addr,uint8_t fun_code,uint8_t *num_reg)
{
	uint8_t reg_idx=0;
	write_hc_msg_on_redis();
	for ( reg_idx = 0; reg_idx < MAX_REG_PER_METER; reg_idx++ )
	{
		write_hc_msg_on_redis();
		if(( iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[reg_idx].start_addr == start_addr) &&
			( iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[reg_idx].func_code == fun_code))
		{
			*num_reg = iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[reg_idx].num_of_regs;
			
			dbg_log(INFORM,"%-25s : Found reg config idx : %d num of reg %d\n","get_mod_data()",reg_idx,*num_reg);
			
			return reg_idx;
		}
	}
	
	return RET_FAILURE;
}

/*********************************************************************
*Function 		: proc_read_register()
*In Params 		: Position ,MeterIdx,RegIdx,val_idx
*Output 		: None.
*Return			: Status.
*Description 	: process the read register fun_code
**********************************************************************/
int32_t proc_read_register(uint8_t pos,uint8_t dev_idx,uint8_t asdu_idx,uint8_t val_idx,uint8_t fun_code)
{
	static char fun_name[]="proc_read_register()";
	uint8_t		src_idx=0,idx=0;
	float 		*p_flt_ptr=NULL,flt_reg_val;
	char 		meter_ser_num[32];
	uint16_t 	num_of_regs=0;
	
	dbg_log(INFORM,"%-25s : DevIdx : %d RegIdx : %d Pos : %d val_idx : %d\n",fun_name,dev_idx,asdu_idx,pos,val_idx);
	write_hc_msg_on_redis();
/* 	switch(iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].param_type)
	{
		case VOLT1_TYPE :
		break;
		
		case SER_NUM_TYPE : 
			num_of_regs = iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].num_of_regs;
			dbg_log(INFORM,"%-25s : Meter Idx : %d , reg_idx : %d , pos : %d , num_of_regs : %d Type is SER_NUM_TYPE\n",
						fun_name,dev_idx,asdu_idx,pos,num_of_regs);
						
			src_idx = pos+num_of_regs*2;
			memset(meter_ser_num,0,32);
			for(idx=0;idx<num_of_regs*2;idx++)
			{
				meter_ser_num[idx]=g_recv_ser_buff[src_idx--];
			}

			dbg_log(INFORM,"%-25s : Meter serial number : %s\n",fun_name,(char*)meter_ser_num);
			return (pos + num_of_regs*2);
		break;
		
		default : break;
	} */

	switch(iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].format)
	{
		case SIGNED_16BIT_INTEGER_TYPE:
		case UNSIGNED_16BIT_INTEGER_TYPE:
		{
			write_hc_msg_on_redis();
			src_idx = pos + 1; 
			for ( idx = 0; idx < 2; idx++ )
			{
				iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[idx] = g_recv_ser_buff[src_idx--];
				//buf[idx]=iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].reg_val[idx];
			}
			
			check_event(dev_idx,asdu_idx,fun_code);
			return ( pos + 2 );
		}
		break;
	
		case SIGNED_32BIT_LW_HW_INTEGER_TYPE:
		case UNSIGNED_32BIT_LW_HW_INTEGER_TYPE:
		{
			write_hc_msg_on_redis();
			src_idx = pos + 3; 
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[2] = g_recv_ser_buff[src_idx--];
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[3] = g_recv_ser_buff[src_idx--];
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[0] = g_recv_ser_buff[src_idx--];
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[1] = g_recv_ser_buff[src_idx--];
			
			check_event(dev_idx,asdu_idx,fun_code);
			return ( pos + 4 );
		}
		
		break;
		
		case SIGNED_32BIT_HW_LW_INTEGER_TYPE:
		case UNSIGNED_32BIT_HW_LW_INTEGER_TYPE:
		{
			write_hc_msg_on_redis();
			src_idx = pos + 3; 
			for ( idx = 0; idx < 4; idx++ )
			{
				iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[idx] = g_recv_ser_buff[src_idx--];
				//buf[idx]=iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].reg_val[idx];
			}
			check_event(dev_idx,asdu_idx,fun_code);
			return ( pos + 4 );
		}
		break;
		
		case FLOAT_LW_HW_TYPE: 
		{
			write_hc_msg_on_redis();
			src_idx = pos + 3;

			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[2] = g_recv_ser_buff[src_idx--];
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[3] = g_recv_ser_buff[src_idx--];
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[0] = g_recv_ser_buff[src_idx--];
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[1] = g_recv_ser_buff[src_idx--];
			
/* 			printf("Byte Val : %X %X %X %X\n",
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].reg_val[2],
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].reg_val[3],
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].reg_val[0],
			iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].reg_val[1]); */
			
			p_flt_ptr = (float *)iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val;
			
			/* printf("After Byte Val : %X %X %X %X\n",p_flt_ptr[0],p_flt_ptr[1],p_flt_ptr[2],p_flt_ptr[3]); */
	
			flt_reg_val = *p_flt_ptr;

			dbg_log(INFORM,"%-25s : FLOAT_LW_HW_TYPE : DevIdx : %d RegIdx : %d Pos : %d val_idx : %d RegName : %s reg_val : %0.4f\n",
			fun_name,dev_idx,asdu_idx,pos,val_idx,iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].name_id,flt_reg_val);
			
			//strcpy(iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val,(char *)flt_reg_val);
			
			
			check_event(dev_idx,asdu_idx,fun_code);
			return ( pos + 4 );
		}
		break;
		
		case FLOAT_HW_LW_TYPE: 
		{
			write_hc_msg_on_redis();
			char buf[4];
			memset(buf,0,4);
			src_idx = pos + 3; 
			for ( idx = 0; idx < 4; idx++ )
			{
				iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[idx] = g_recv_ser_buff[src_idx--];
				//dbg_log(INFORM,"%-25s : %02X\n",fun_name,iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[idx]);
				buf[idx]=iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[idx];
			}

			p_flt_ptr = (float *)iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val;
			flt_reg_val = (float)*p_flt_ptr; 		

			dbg_log(INFORM,"%-25s : FLOAT_HW_LW_TYPE : DevIdx : %d RegIdx : %d Pos : %d val_idx : %d RegName : %s reg_val : %0.4f\n",
			fun_name,dev_idx,asdu_idx,pos,val_idx,iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].name_id,flt_reg_val);
			
			/* p_flt_ptr = (float *)buf;
			flt_reg_val = (float)*p_flt_ptr; 
			dbg_log(INFORM,"%-25s : -->>>FLOAT_HW_LW_TYPE : DevIdx : %d RegIdx : %d Pos : %d val_idx : %d reg_val : %0.4f\n",
			fun_name,dev_idx,asdu_idx,pos,val_idx,flt_reg_val); */
			//strcpy(iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val,(char *)flt_reg_val);	
			check_event(dev_idx,asdu_idx,fun_code);
			return ( pos + 4 );
		}
		break;
		
		default : 
			dbg_log(INFORM,"%-25s : Invalid data format for DevIdx : %d RegIdx : %d Pos : %d val_idx : %d\n",fun_name,dev_idx,asdu_idx,pos,val_idx);
		break;
	}
	
	return RET_OK;
}


/****************************************
*Function 		: write_devices_status()
*Params 		: None
*Return			: Success or error message
*Description 	: To write devices status on redis server
*****************************************/
int32_t write_devices_status(void)
{
	static char fun_name[]="write_devices_status()";
	struct tm	*curr_time_str=NULL;
	char		time_str[SIZE_64];
	time_t 		curr_time = 0;
	int idx=0;
	reply = redisCommand(c,"hmset serport%d_Device_status Num_dev %d",g_pidx,MAX_NO_OF_METER_PER_PORT);
	freeReplyObject(reply);
	for(idx=0;idx<MAX_NO_OF_METER_PER_PORT;idx++)
	{	
		write_hc_msg_on_redis();
		reply = redisCommand(c,"hmset serport%d_Device_status Dev%d_id %d",g_pidx,idx+1,iot_data_list.iot_data_port[g_pidx].iot_data_meter[idx].iot_device_id);
		freeReplyObject(reply);
		reply = redisCommand(c,"hmset serport%d_Device_status Dev%d_status %d",g_pidx,idx+1,iot_data_list.iot_data_port[g_pidx].iot_data_meter[idx].dev_status);
		freeReplyObject(reply);
				
	}
	curr_time = time(NULL);
	//curr_time_str = localtime(&curr_time);
	//strftime(time_str, SIZE_64,"%d/%b/%Y_%H:%M:%S", curr_time_str);
	reply = redisCommand(c,"hmset serport%d_Device_status updatetime %d",g_pidx,curr_time);
	freeReplyObject(reply);
	write_hc_msg_on_redis();
	return RET_OK;
}


/*********************************************************************
*Function 		: write_into_redis()
*In Params 		: port index ,Meter Idx,register index
*Output 		: None.
*Return			: Void.
*Description 	: write polled data into redis server
**********************************************************************/
int32_t write_into_redis(uint8_t pidx,uint8_t midx,uint8_t reg_idx)
{

	static char fun_name[]="write_into_redis()";
	float *p_flt_ptr=NULL,flt_reg_val;
	int *p_int_ptr=NULL,int_reg_val=0;
	char 		meter_ser_num[32];
	uint16_t 	num_of_regs=0;
	
	write_hc_msg_on_redis();
	reply = redisCommand(c,"hmset serport%d_dev%d Val%d_nameid %s",pidx,midx,reg_idx+1,iot_data_list.iot_data_port[pidx].iot_data_meter[midx].iot_data_reg[reg_idx].name_id);
	freeReplyObject(reply);
	switch(iot_dev_cfg.chan_cfg[pidx].mod_met_cfg[midx].met_prf.reg_cfg[reg_idx].format)
	{

		case FLOAT_LW_HW_TYPE :
		case FLOAT_HW_LW_TYPE :
			write_hc_msg_on_redis();
			p_flt_ptr = (float *)iot_data_list.iot_data_port[pidx].iot_data_meter[midx].iot_data_reg[reg_idx].curr_reg_val;
			flt_reg_val = *p_flt_ptr;
			reply = redisCommand(c,"hmset serport%d_dev%d Val%d %f",pidx,midx,reg_idx+1,flt_reg_val);
			freeReplyObject(reply);
		
		break;
		
		case SIGNED_16BIT_INTEGER_TYPE :
		case UNSIGNED_16BIT_INTEGER_TYPE :
		case SIGNED_32BIT_HW_LW_INTEGER_TYPE :
		case SIGNED_32BIT_LW_HW_INTEGER_TYPE :
		case UNSIGNED_32BIT_HW_LW_INTEGER_TYPE :
		case UNSIGNED_32BIT_LW_HW_INTEGER_TYPE :
		
			write_hc_msg_on_redis();
			p_int_ptr = (int *)iot_data_list.iot_data_port[pidx].iot_data_meter[midx].iot_data_reg[reg_idx].curr_reg_val;
			int_reg_val = *p_int_ptr;
			reply = redisCommand(c,"hmset serport%d_dev%d Val%d %d",pidx,midx,reg_idx+1,int_reg_val);
			freeReplyObject(reply);
			
		default : 
			write_hc_msg_on_redis();
			reply = redisCommand(c,"hmset serport%d_dev%d Val%d %d",pidx,midx,reg_idx+1,0);
			freeReplyObject(reply);
		break;
	}
	dbg_log(INFORM,"%-25s : serport%d_dev%d reg%d is updated Sucessfully\n",fun_name,g_pidx,midx,reg_idx);
	
	return RET_OK;
}



/*********************************************************************
*Function 		: fill_polled_data()
*In Params 		: Meter Idx.
*Output 		: None.
*Return			: Void.
*Description 	: fill the polled into data structure.
**********************************************************************/
void fill_polled_data(uint8_t midx)
{
	static char fun_name[]="fill_polled_data()";
	struct tm	*curr_time_str=NULL;
	char		time_str[SIZE_64];
	time_t 		curr_time = 0;
	uint8_t 	reg_idx=0;
	
	write_hc_msg_on_redis();
	
	iot_data_list.iot_data_port[g_pidx].iot_data_meter[midx].iot_device_id=iot_dev_cfg.iot_device_id;
	iot_data_list.iot_data_port[g_pidx].iot_data_meter[midx].port_idx=g_pidx;
	iot_data_list.iot_data_port[g_pidx].iot_data_meter[midx].midx=midx;
	
	write_hc_msg_on_redis(); 
	
	reply = redisCommand(c,"hmset serport%d_dev%d Device_id %d",g_pidx,midx,iot_data_list.iot_data_port[g_pidx].iot_data_meter[midx].iot_device_id);
	freeReplyObject(reply);
	reply = redisCommand(c,"hmset serport%d_dev%d Num_values %d",g_pidx,midx,iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[midx].met_prf.num_of_points);
	freeReplyObject(reply);
	
	for(reg_idx=0;reg_idx<MAX_REG_PER_METER;reg_idx++)
	{
		write_hc_msg_on_redis();
		strcpy(iot_data_list.iot_data_port[g_pidx].iot_data_meter[midx].iot_data_reg[reg_idx].name_id,
		iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[midx].met_prf.reg_cfg[reg_idx].name_id);
		
		iot_data_list.iot_data_port[g_pidx].iot_data_meter[midx].iot_data_reg[reg_idx].data_type = 
		iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[midx].met_prf.reg_cfg[reg_idx].format;
		write_into_redis(g_pidx,midx,reg_idx);
		
	}
	write_hc_msg_on_redis();
	curr_time = time(NULL);
	curr_time_str = localtime(&curr_time);
	strftime(time_str, SIZE_64,"%d/%b/%Y_%H:%M:%S", curr_time_str);
	reply = redisCommand(c,"hmset serport%d_dev%d updatetime %s",g_pidx,midx,time_str);
	freeReplyObject(reply);
	write_hc_msg_on_redis();
	dbg_log(INFORM,"%-25s : serport%d_dev%d hash is updated Sucessfully\n",fun_name,g_pidx,midx);
}

/*********************************************************************
*Function 		: check_event()
*In Params 		: Meter Idx,reg idx,fun_code,prev val, curr, val.
*Output 		: None.
*Return			: Status.
*Description 	: to check events occur and send it to mqtt pub proc.
**********************************************************************/
uint32_t check_event(uint8_t dev_idx,uint8_t asdu_idx,uint8_t fun_code)
{
	static char fun_name[] = "check_event()";
	float dead_band_val=0.0,dead_band = 0.0;
	float prev_val=0.0,curr_val=0.0,*p_flt_ptr=NULL;
	write_hc_msg_on_redis();
	switch(fun_code)
	{
		case READ_HOLDING:
		case READ_INPUT:
			write_hc_msg_on_redis();
			p_flt_ptr=(float *)iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val;
			curr_val = (float)*p_flt_ptr;
			curr_val = curr_val * iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].scalefact;
			
			memcpy(iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val,&curr_val,4);
			
			p_flt_ptr=(float *)iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].prev_reg_val;
			prev_val = (float)*p_flt_ptr;
			prev_val = prev_val * iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].scalefact;

			memcpy(iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].prev_reg_val,&curr_val,4);
					
			switch(iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].acq_mode)
			{
				case PERIODIC :
					write_hc_msg_on_redis();
					dbg_log(INFORM,"%-25s : MeterIdx : %d, RegIdx : %d is periodic no need to generate events\n",fun_name,dev_idx,asdu_idx);
					return RET_OK;
				break;
				
				case ABSOLUTE :
					write_hc_msg_on_redis();
					if((curr_val < iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].minval) ||
						(curr_val > iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].maxval))
					{
						dbg_log(INFORM,"%-25s : MeterIdx : %d, RegIdx : %d Analog event generated due to minval/Maxval\n",fun_name,dev_idx,asdu_idx);
					}
					else
					{
						return RET_OK;
					}
				break;
				
				case DEADBAND :
					write_hc_msg_on_redis();
					dead_band = iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[dev_idx].met_prf.reg_cfg[asdu_idx].dead_band;
					dead_band_val = prev_val*(dead_band)/(float)100;
					
					if ( dead_band_val < 0.0 )
						dead_band_val = dead_band_val * -1;
					
					if((curr_val < (prev_val - dead_band_val)) || (curr_val > (prev_val + dead_band_val)))
					{
						dbg_log(INFORM,"%-25s : MeterIdx : %d, RegIdx : %d Analog event generated due to dead_band_val\n",fun_name,dev_idx,asdu_idx);
					}
					else
					{
						return RET_OK;
					}
				break;
				
				default : break;
			}
		break;
		
		case READ_COIL:
		case READ_DISCRETE:
			write_hc_msg_on_redis();
			if(iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[0]!=
				iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].prev_reg_val[0])
			{
					iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].prev_reg_val[0]=
					iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val[0];
					
					dbg_log(INFORM,"%-25s : MeterIdx : %d, RegIdx : %d IO event generated\n",fun_name,dev_idx,asdu_idx);
			}
			else
			{
				return RET_OK;
			}
		break;
		
		default : break;
	}
	
	ipc_msg.proc_id = MODRTU_MASTER_PROC;
	ipc_msg.msg_type = EVENT_MSG;
	ipc_msg.msg_len = sizeof(iot_event_data);
	write_hc_msg_on_redis();
	iot_event_data.midx = dev_idx;
	strcpy(iot_event_data.name_id,iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[g_midx].met_prf.reg_cfg[asdu_idx].name_id);
	memcpy(iot_event_data.reg_val,iot_data_list.iot_data_port[g_pidx].iot_data_meter[dev_idx].iot_data_reg[asdu_idx].curr_reg_val,4);
	iot_event_data.data_type = iot_dev_cfg.chan_cfg[g_pidx].mod_met_cfg[g_midx].met_prf.reg_cfg[asdu_idx].format;
	
	write_hc_msg_on_redis();
	
	memcpy((void*)ipc_msg.msg,(void*)&iot_event_data,sizeof(iot_event_data));
	
	//send_to_udp((char *)&ipc_msg,sizeof(ipc_msg),STATUS_MODULE_IPC_PORT);
	//send_to_udp((char *)&ipc_msg,sizeof(ipc_msg),MQTT_MODULE_IPC_PORT);

	return RET_OK;
}

/* End of file */
