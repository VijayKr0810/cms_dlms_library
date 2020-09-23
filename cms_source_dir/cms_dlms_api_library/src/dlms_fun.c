/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	dlms_fun.c
* Summary:  DLMS related functions.
*
**********************************************************************/

/* Includes */
#include "gen_inc.h"
#include "gen_fun.h"
#include "log.h"
#include "dlms_fun.h"
#include "dlms_api.h"

/* Externs */
extern char 				g_ls_data_dir_path[];
extern uint8_t 				g_append_event_file_flag;

/* Structures */
gen_data_val_info_t			gen_data_val_info[128];
date_time_t					meter_date_time,bill_date_time,g_st_date_time,g_end_date_time;
name_plate_info_t			g_name_plate_info;
inst_val_info_t				g_inst_data_val;
bill_val_info_t 			g_bill_val_info;
block_val_info_t 			g_block_val_info;
all_events_data_value_t		all_events_data_value;
all_daily_profile_data_value_t all_daily_profile_data_value;
event_val_info_t 			g_event_val_info;

gen_params_det_t 			gen_inst_param_det,gen_ls_param_det,
							gen_event_param_det,gen_dp_param_det,
							gen_bill_param_det;

all_param_obis_val_info_t 	g_all_inst_param_obis_val,
							g_all_ls_param_obis_val,
							g_all_event_param_obis_val,
							g_all_bill_param_obis_val,
							g_all_dp_param_obis_val;

obis_name_plate_info_t		g_obis_name_plate_info;

#define 					MASTER_INST_OBIS_FILE			"master_inst_obis_list.txt"
#define 					MASTER_LS_OBIS_FILE				"master_ls_obis_list.txt"
#define 					MASTER_BILL_OBIS_FILE			"master_billing_obis_list.txt"
#define 					MASTER_DP_OBIS_FILE				"master_dp_obis_list.txt"
#define 					MASTER_EVENT_OBIS_FILE			"master_event_obis_list.txt"

#define						MAX_NUM_INST_PARAMS		75
#define						MAX_NUM_LS_PARAMS		32
#define						MAX_NUM_EVENT_PARAMS	28
#define						MAX_NUM_DP_PARAMS		24
#define						MAX_NUM_BILL_PARAMS		128

param_det_t					g_inst_param_det[MAX_NUM_INST_PARAMS];
param_det_t					g_ls_param_det[MAX_NUM_LS_PARAMS];
param_det_t					g_event_param_det[MAX_NUM_EVENT_PARAMS];
param_det_t					g_daily_profile_param_det[MAX_NUM_DP_PARAMS];
param_det_t					g_billing_param_det[MAX_NUM_BILL_PARAMS];

param_det_t					inst_param_det1[80]={
										{ {0,0,1,0,0,255}, "date_time" 	},
										{ {1,0,31,7,0,255},"cur_ir" 	},{ {1,0,51,7,0,255},"cur_iy" 	},
										{ {1,0,71,7,0,255},"cur_ib" 	},{ {1,0,32,7,0,255},"volt_r" 	},
										{ {1,0,52,7,0,255},"volt_y"    	},{ {1,0,72,7,0,255},"volt_b"	},
										{ {1,0,33,7,0,255},"pf_r"   	},{ {1,0,53,7,0,255},"pf_y"   	},
										{ {1,0,73,7,0,255},"pf_b"   	},{ {1,0,13,7,0,255},"pf_avg" 	},
										{ {1,0,14,7,0,255},"freq"  		},{ {1,0,9,7,0,255},"kva"    	},
										{ {1,0,1,7,0,255},"kw"     		},{ {1,0,3,7,0,255},"kvar"   	},
										{ {0,0,96,7,0,255},"num_pow_fail"},{ {0,0,94,91,8,255},"cu_pf_dur"},
										{ {0,0,94,91,0,255},"cu_ta_cnt"	},{ {0,0,0,1,0,255},"cu_bi_cnt" },
										{ {0,0,96,2,0,255},"cu_pr_cnt"	},{ {0,0,0,1,2,255},"bill_date" },
										{ {1,0,1,8,0,255},"kwh"   		},{ {1,0,5,8,0,255},"kvarh_lag"	},
										{ {1,0,8,8,0,255},"kvarh_lead"	},{ {1,0,9,8,0,255},"kvah"   	},
										{ {1,0,1,6,0,255},"kwmd"   		},{ {1,0,9,6,0,255},"kvamd"  	}
										};
								
param_det_t					ls_param_det1[32]={
										{ {0,0,1,0,0,255}, "date_time" 	},	{ {1,0,31,27,0,255},"cur_ir"},
										{ {1,0,51,27,0,255},"cur_iy" 	},{ {1,0,71,27,0,255},"cur_ib" 	},
										{ {1,0,32,27,0,255},"volt_r"   	},{ {1,0,52,27,0,255},"volt_y"  },
										{ {1,0,72,27,0,255},"volt_b"   	},{ {1,0,14,27,0,255},"freq"   	},
										{ {1,0,2,29,0,255},"kwh_exp"   	},{ {1,0,1,29,0,255},"kwh_imp"   	},
										{ {1,0,5,29,0,255},"kvarh_lag"   },{ {1,0,8,29,0,255},"kvarh_lead" },
										{ {1,0,10,29,0,255},"kvah_exp"   	},{ {1,0,9,29,0,255},"kvah_imp"   }
										};	

param_det_t					event_param_det1[28]={
									{ {0,0,1,0,0,255}, "date_time" },	
									{ {1,0,31,7,0,255},"cur_ir" },
									{ {1,0,51,7,0,255},"cur_iy" },
									{ {1,0,71,7,0,255},"cur_ib" },
									{ {1,0,32,7,0,255},"volt_r"	},
									{ {1,0,52,7,0,255},"volt_y"	},
									{ {1,0,72,7,0,255},"volt_b"	},
									{ {1,0,33,7,0,255},"pf_r"	},
									{ {1,0,53,7,0,255},"pf_y"	},
									{ {1,0,73,7,0,255},"pf_b"	},
									{ {1,0,1,8,0,255},"kwh"		},
									{ {0,0,96,11,0,255},"event_code"}};	

param_det_t					daily_profile_param_det1[24]={
										{ {0,0,1,0,0,255}, "date_time" },
										{ {1,0,1,8,0,255},"kwh_imp" },
										{ {1,0,2,8,0,255},"kwh_exp" },
										{ {1,0,9,8,0,255},"kvah_imp" },
										{ {1,0,10,8,0,255},"kvah_exp"},
										{ {1,0,94,91,1,255},"react_enhi"},
										{ {1,0,94,91,2,255},"react_enlo"},
										{ {1,0,5,8,0,255},"kvarh_q1"},
										{ {1,0,6,8,0,255},"kvarh_q2"},
										{ {1,0,7,8,0,255},"kvarh_q3"},
										{ {1,0,8,8,0,255},"kvarh_q4"}
									};									

param_det_t	     			billing_param_det1[128] = {
										{ {0,0,0,1,2,255}, "date_time" },	
										{ {1,0,13,0,0,255},"sys_pf" },
										{ {1,0,1,8,0,255},"kwh" },
										{ {1,0,1,8,1,255},"kwh_tz1" },
										{ {1,0,1,8,2,255},"kwh_tz2" },
										{ {1,0,1,8,3,255},"kwh_tz3" },
										{ {1,0,1,8,4,255},"kwh_tz4" },
										{ {1,0,1,8,5,255},"kwh_tz5" },
										{ {1,0,1,8,6,255},"kwh_tz6" },
										{ {1,0,1,8,7,255},"kwh_tz7" },
										{ {1,0,1,8,8,255},"kwh_tz8" },
										{ {1,0,5,8,0,255},"kvarh_lag"},
										{ {1,0,8,8,0,255},"kvarh_lead"},
										{ {1,0,9,8,0,255},"kvah"   },
										{ {1,0,9,8,1,255},"kvah_tz1" },
										{ {1,0,9,8,2,255},"kvah_tz2" },
										{ {1,0,9,8,3,255},"kvah_tz3" },
										{ {1,0,9,8,4,255},"kvah_tz4" },
										{ {1,0,9,8,5,255},"kvah_tz5" },
										{ {1,0,9,8,6,255},"kvah_tz6" },
										{ {1,0,9,8,7,255},"kvah_tz7" },
										{ {1,0,9,8,8,255},"kvah_tz8" },
										{ {1,0,1,6,0,255},"kwmd"   },
										{ {1,0,1,6,1,255},"kwmd_tz1" },
										{ {1,0,1,6,2,255},"kwmd_tz2" },
										{ {1,0,1,6,3,255},"kwmd_tz3" },
										{ {1,0,1,6,4,255},"kwmd_tz4" },
										{ {1,0,1,6,5,255},"kwmd_tz5" },
										{ {1,0,1,6,6,255},"kwmd_tz6" },
										{ {1,0,1,6,7,255},"kwmd_tz7" },
										{ {1,0,1,6,8,255},"kwmd_tz8" },
										{ {1,0,9,6,0,255},"kvamd"   },
										{ {1,0,9,6,1,255},"kvamd_tz1" },
										{ {1,0,9,6,2,255},"kvamd_tz2" },
										{ {1,0,9,6,3,255},"kvamd_tz3" },
										{ {1,0,9,6,4,255},"kvamd_tz4" },
										{ {1,0,9,6,5,255},"kvamd_tz5" },
										{ {1,0,9,6,6,255},"kvamd_tz6" },
										{ {1,0,9,6,7,255},"kvamd_tz7" },
										{ {1,0,9,6,8,255},"kvamd_tz8" }
			};
			
/* Globals */
char 						g_last_entry_buff[256];
char 						g_prev_ls_file_name[64];
uint8_t 					g_no_ls_data_avl_flag,g_num_ls_param,g_secure_met_flag;
char 						g_float_str[16];
uint8_t 					g_event_type_idx,g_num_event_param,g_max_num_event[8],g_tot_event_entry;
uint8_t						g_raw_data_buff[8*1024];
uint32_t 					g_raw_data_idx,g_name_plate_idx,g_int_period_blk,g_num_blocks_blk_data;
uint8_t 					OFFSET,g_query_type,g_meter_store_order;
uint8_t						g_send_buff[256],g_temp_buff[256],g_recv_buff[1024];
uint8_t 					g_src_addr=0x41,g_meter_mfg_type;
uint8_t 					g_recv_seq_num,g_send_seq_num;
uint8_t						g_block_num_det[4];
uint8_t						g_ls_decode_flag,g_rr_frame;
uint8_t						g_met_status,g_rr_frame,g_get_nxt_blk,g_first_time_resp,
							g_comp_blk_resp;
uint32_t					g_get_nxt_blk_val;
uint8_t 					g_dp_entry_idx,g_tot_bill_entry;
uint8_t						g_date_time_obis[8]={0,0,1,0,0,255};
uint8_t						g_date_time_bill_obis[8]={0,0,0,1,2,255};

uint8_t 					name_plate_obis[6][6]=
							{
							 {0,0,96,1,0,255} ,	//"Meter Serial No.",     "0.0.96.1.0.255",
							 {0,0,96,1,1,255} ,	//"Manufacturer Name",    "0.0.96.1.1.255",
							 {1,0,0,2,0,255} ,	//"Firmware Version",     "1.0.0.2.0.255",
							 {0,0,94,91,9,255} ,	//"Meter Type",           "0.0.94.91.9.255",
							 {1,0,0,4,2,255} ,	//"Int. CT Ratio",        "1.0.0.4.2.255",
							 {1,0,0,4,3,255} 	
							};

uint16_t fcstab[256] = {
							0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
							0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
							0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
							0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
							0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
							0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
							0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
							0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
							0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
							0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
							0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
							0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
							0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
							0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
							0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
							0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
							0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
							0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
							0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
							0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
							0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
							0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
							0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
							0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
							0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
							0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
							0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
							0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
							0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
							0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
							0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
							0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78

};

/* ---------------------------------------------------------------------- */
void print_val_scal_onis_val_info(uint8_t* val_obis, uint8_t* scalar_obis, int8_t scalar_val)
{
	static char fun_name[]="print_val_scal_onis_val_info()";
	
	dbg_log(INFORM,"%-20s : ValObis : %d.%d.%d.%d.%d.%d, ScalObis : %d.%d.%d.%d.%d.%d, ScalVal : %d\n",fun_name,
	val_obis[0],val_obis[1],val_obis[2],val_obis[3],val_obis[4],val_obis[5],
	scalar_obis[0],scalar_obis[1],scalar_obis[2],scalar_obis[3],scalar_obis[4],scalar_obis[5],scalar_val);
}

/**************************************************************************************************
*Function 					: fill_val_obis_det()
*Input Parameters 			: Qyuery type.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To fill obis code information for various query type.
********************************************************************************************************/
int32_t fill_val_obis_det(uint8_t type)
{
	static char fun_name[]="fill_val_obis_det()";
	uint8_t idx=0, jdx=0, data_type=0;
	
	switch(type)
	{
		case INST_VAL_OBIS_TYPE:
		{
			idx = 0;
			dbg_log(REPORT,"%-20s : Total NumOf Inst Val Obis : %d\n",fun_name,gen_inst_param_det.tot_num_val_obis);
			
			for(idx=0;idx<gen_inst_param_det.tot_num_val_obis;idx++)
			{
				memcpy(gen_inst_param_det.val_obis[idx], &g_raw_data_buff[(18*idx)+7], 6);
			}
		}	
		break;
		
		case INST_SCALE_OBIS_TYPE:
		{
			idx = 0;
			dbg_log(REPORT,"%-20s : Total NumOf Inst Scalar Obis : %d\n",fun_name,gen_inst_param_det.tot_num_scalar);
			
			for(idx=0;idx<gen_inst_param_det.tot_num_scalar;idx++)
			{
				memcpy(gen_inst_param_det.scalar_val[idx].obis_code,&g_raw_data_buff[(18*idx)+7],6);
			}
		}
		break;
		
		case INST_SCALE_VAL_TYPE:
		{
			uint8_t index =3;
			idx = 0;
			for(idx=0;idx<gen_inst_param_det.tot_num_val_obis;idx++)
			{
				for(jdx=0;jdx<gen_inst_param_det.tot_num_scalar;jdx++)
				{
					if(memcmp(gen_inst_param_det.val_obis[idx],gen_inst_param_det.scalar_val[jdx].obis_code,6)==0)
					{
						gen_inst_param_det.scalar_val[idx].value=g_raw_data_buff[index]&0XFF;
						index += 6;
						print_val_scal_onis_val_info(gen_inst_param_det.val_obis[idx],gen_inst_param_det.scalar_val[jdx].obis_code,gen_inst_param_det.scalar_val[idx].value);
						break;
					}
				}
			}
		}
		break;
		
		case INST_VALUES_TYPE:
		{
			uint32_t index =0;
			index = index+2;
			
			idx = 0;
			dbg_log(INFORM,"%-20s : Tot_num of Inst value : %d\n",fun_name,gen_inst_param_det.tot_num_value);
			
			for(idx=0; idx<gen_inst_param_det.tot_num_value; idx++)
			{
				//printf("Index : %d, Index Val : %d\n",index,g_raw_data_buff[index]);
				data_type = g_raw_data_buff[index++];
				gen_data_val_info[idx].data_type = data_type;
				
				switch(data_type)
				{
					case	FLOAT_32BIT_TYPE:
					case UNSIGNED_32BIT_TYPE:
					case SIGNED_32BIT_TYPE:
						gen_data_val_info[idx].num_bytes = 4;
						memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],4);
						index+=4;
					break;
					
					case UNSIGNED_16BIT_TYPE:
					case SIGNED_16BIT_TYPE:
						gen_data_val_info[idx].num_bytes = 2;
						memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],2);
						index+=2;
					break;
					
					case UNSIGNED_8BIT_TYPE:
						gen_data_val_info[idx].num_bytes = 1;
						memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],1);
						index+=1;
					break;
					
					case OCTET_STRING_TYPE:
						gen_data_val_info[idx].num_bytes = g_raw_data_buff[index];
						memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index+1],gen_data_val_info[idx].num_bytes);
						index+=(gen_data_val_info[idx].num_bytes+1);
					break;
					
					default : break;
				}
			}
		}
		break;
	
		case BLOCK_VAL_OBIS_TYPE:
		{
			for(idx=0;idx<gen_ls_param_det.tot_num_val_obis;idx++)
			{
				memcpy(gen_ls_param_det.val_obis[idx],&g_raw_data_buff[(18*idx)+7],6);
			}
		}
		break;
		
		case BLOCK_SCALER_OBIS_TYPE:
		{
			for(idx=0;idx<gen_ls_param_det.tot_num_scalar;idx++)
			{
				memcpy(gen_ls_param_det.scalar_val[idx].obis_code,&g_raw_data_buff[(18*idx)+7],6);
				//print_data(gen_ls_param_det.scalar_val[idx].obis_code,6);
			}
		}
		break;
		
		case BLOCK_SCALER_VALUE_TYPE:
		{
			uint8_t index =3;
			idx = 0;
			for(idx=0; idx<gen_ls_param_det.tot_num_val_obis; idx++)
			{
				for(jdx=0; jdx<gen_ls_param_det.tot_num_scalar; jdx++)
				{
					if(memcmp(gen_ls_param_det.val_obis[idx], gen_ls_param_det.scalar_val[jdx].obis_code, 6)==0)
					{
						gen_ls_param_det.scalar_val[idx].value = g_raw_data_buff[index];
						index += 6;
						print_val_scal_onis_val_info(gen_ls_param_det.val_obis[idx],gen_ls_param_det.scalar_val[jdx].obis_code,gen_ls_param_det.scalar_val[idx].value);
						break;
					}
				}
			}
			
		}
		break;
		
		case EVENT_VALUE_OBIS_TYPE:
		{
			for(idx=0; idx<gen_event_param_det.tot_num_val_obis; idx++)
			{
				memcpy(gen_event_param_det.val_obis[idx],&g_raw_data_buff[(18*idx)+7],6);
			}
		}
		break;
		
		case EVENT_SCALER_OBIS_TYPE:
		{
			for(idx=0; idx<gen_event_param_det.tot_num_scalar; idx++)
			{
				memcpy(gen_event_param_det.scalar_val[idx].obis_code,&g_raw_data_buff[(18*idx)+7],6);
			}
		}
		break;
		
		case EVENT_SCALER_VALUE_TYPE:
		{
			uint8_t index =3;
			
			for(idx=0;idx<gen_event_param_det.tot_num_val_obis;idx++)
			{
				for(jdx=0;jdx<gen_event_param_det.tot_num_scalar;jdx++)
				{
					if(memcmp(gen_event_param_det.val_obis[idx],gen_event_param_det.scalar_val[jdx].obis_code,6)==0)
					{
						gen_event_param_det.scalar_val[idx].value=g_raw_data_buff[index];
						index += 6;
						print_val_scal_onis_val_info(gen_event_param_det.val_obis[idx],gen_event_param_det.scalar_val[jdx].obis_code,gen_event_param_det.scalar_val[idx].value);
						break;
					}
				}
			}
		}
		break;
		
		case EVENT_VALUE_TYPE:
		{
			uint32_t index =0;
			uint8_t event_idx =0;

			event_idx = g_event_type_idx;
			
			all_events_data_value.events_type_info[event_idx].num_event = gen_event_param_det.tot_num_value;
			printf("EVENT_VALUE_TYPE : event_idx : %d tot_num_value : %d g_num_event_param : %d\n",
					event_idx,gen_event_param_det.tot_num_value,g_num_event_param);
			
			event_idx = 0;
			
			for(event_idx=0; event_idx<gen_event_param_det.tot_num_value; event_idx++)
			{
				index = index+2;

				for(idx=0; idx<g_num_event_param; idx++)
				{
					data_type = g_raw_data_buff[index++];
					gen_data_val_info[idx].data_type = data_type;
					
					switch(data_type)
					{
						case	FLOAT_32BIT_TYPE:
						case UNSIGNED_32BIT_TYPE:
						case SIGNED_32BIT_TYPE:
							gen_data_val_info[idx].num_bytes = 4;
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],4);
							index+=4;
						break;
						
						case UNSIGNED_16BIT_TYPE:
						case SIGNED_16BIT_TYPE:
							gen_data_val_info[idx].num_bytes = 2;
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],2);
							index+=2;
						break;
						
						case UNSIGNED_8BIT_TYPE:
							gen_data_val_info[idx].num_bytes = 1;
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],1);
							index+=1;
						break;
						
						case OCTET_STRING_TYPE:
							gen_data_val_info[idx].num_bytes = g_raw_data_buff[index];
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index+1],gen_data_val_info[idx].num_bytes);
							index+=(gen_data_val_info[idx].num_bytes+1);
							//printf("!!!!!!!!!!event_idx : %d\n",event_idx);
						break;
						
						default : break;
					}
				}
				
				if(fill_event_val(event_idx)<0)
				{
					dbg_log(REPORT,"%-20s : Failed to filled for event index : %d\n",fun_name,event_idx);
						continue;
				}
				
				store_event_det_file(g_event_type_idx);
			}
		}
		break;
		
		case DAILY_VAL_OBIS_TYPE:
		{
			for(idx=0;idx<gen_dp_param_det.tot_num_val_obis;idx++)
			{
				memcpy(gen_dp_param_det.val_obis[idx],&g_raw_data_buff[(18*idx)+7],6);
			}
		}
		break;
		
		case DAILY_SCALAR_OBIS_TYPE:
		{
			for(idx=0;idx<gen_dp_param_det.tot_num_scalar;idx++)
			{
				memcpy(gen_dp_param_det.scalar_val[idx].obis_code,&g_raw_data_buff[(18*idx)+7],6);
			}
		}
		break;
		
		case DAILY_SCALAR_VALUE_TYPE:
		{
			uint8_t index =3;
			for(idx=0;idx<gen_dp_param_det.tot_num_val_obis;idx++)
			{
				for(jdx=0;jdx<gen_dp_param_det.tot_num_scalar;jdx++)
				{
					if(memcmp(gen_dp_param_det.val_obis[idx],gen_dp_param_det.scalar_val[jdx].obis_code,6)==0)
					{
						gen_dp_param_det.scalar_val[idx].value=g_raw_data_buff[index];
						index += 6;
						print_val_scal_onis_val_info(gen_dp_param_det.val_obis[idx],gen_dp_param_det.scalar_val[jdx].obis_code,gen_dp_param_det.scalar_val[idx].value);
						break;
					}
				}
			}
		}
		break;
		
		case DAILY_VALUES_TYPE:
		{
			uint8_t dp_index=0;
			uint32_t index = 0;
			idx = 0;
			
			dbg_log(INFORM,"%-20s : total num of dp entry : %d\n",fun_name,gen_dp_param_det.tot_num_value);
			
			for(dp_index=0; dp_index<gen_dp_param_det.tot_num_value; dp_index++)
			{
				if(index>=g_raw_data_idx)
				{
					printf(">>>>Reached MAX decode index from raw data\n");
					break;
				}
				index = index+2;
				
				printf("DpIdx : %d, Index : %d\n",dp_index,index);
				
				for(idx=0; idx<g_num_ls_param; idx++)
				{
					data_type = g_raw_data_buff[index++];
					gen_data_val_info[idx].data_type = data_type;
					
					switch(data_type)
					{
						case	FLOAT_32BIT_TYPE:
						case UNSIGNED_32BIT_TYPE:
						case SIGNED_32BIT_TYPE:
							gen_data_val_info[idx].num_bytes = 4;
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],4);
							index+=4;
						break;
						
						case UNSIGNED_16BIT_TYPE:
						case SIGNED_16BIT_TYPE:
							gen_data_val_info[idx].num_bytes = 2;
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],2);
							index+=2;
						break;
						
						case UNSIGNED_8BIT_TYPE:
							gen_data_val_info[idx].num_bytes = 1;
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],1);
							index+=1;
						break;
						
						case OCTET_STRING_TYPE:
							gen_data_val_info[idx].num_bytes = g_raw_data_buff[index];
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index+1],gen_data_val_info[idx].num_bytes);
							index+=(gen_data_val_info[idx].num_bytes+1);
						break;
						
						default : break;
					}
				}
				
				if(fill_daily_profile_val(dp_index)<0)
				{
					dbg_log(REPORT,"%-20s : Failed to filled for Dp index : %d\n",fun_name,dp_index);
						continue;
				}
				
				save_dp_data_file();
			}
		}
		break;
		
		case BILL_VAL_OBIS_TYPE:
		{
			dbg_log(REPORT,"%-20s : Total NumOf Billing Val Obis : %d\n",fun_name,gen_bill_param_det.tot_num_val_obis);
			for(idx=0;idx<gen_bill_param_det.tot_num_val_obis;idx++)
			{
				memcpy(gen_bill_param_det.val_obis[idx], &g_raw_data_buff[(18*idx)+7], 6);
			}
		}
		break;
		
		case BILL_SCALER_OBIS_TYPE:
		{
			dbg_log(REPORT,"%-20s : Total NumOf Billing Scalar Obis : %d\n",fun_name,gen_bill_param_det.tot_num_scalar);
			for(idx=0;idx<gen_bill_param_det.tot_num_scalar;idx++)
			{
				memcpy(gen_bill_param_det.scalar_val[idx].obis_code,&g_raw_data_buff[(18*idx)+7],6);
			}
		}
		break;
		
		case BILL_SCALER_VALUE_TYPE:
		{
			uint8_t index =3;
			idx = 0;
			for(idx=0;idx<gen_bill_param_det.tot_num_val_obis;idx++)
			{
				for(jdx=0;jdx<gen_bill_param_det.tot_num_scalar;jdx++)
				{
					if(memcmp(gen_bill_param_det.val_obis[idx],gen_bill_param_det.scalar_val[jdx].obis_code,6)==0)
					{
						gen_bill_param_det.scalar_val[idx].value=g_raw_data_buff[index]&0XFF;
						index += 6;
						print_val_scal_onis_val_info(gen_bill_param_det.val_obis[idx],gen_bill_param_det.scalar_val[jdx].obis_code,gen_bill_param_det.scalar_val[idx].value);
						break;
					}
				}
			}
		}
		break;
		
		case BILL_VALUE_TYPE:
		{
			uint8_t bill_index=0;
			uint32_t index = 0;
			idx = 0;
			
			dbg_log(INFORM,"%-20s : total num of bill entry : %d Tot num of bill params : %d\n",
			fun_name,gen_bill_param_det.tot_num_value,g_num_ls_param);
			
			for(bill_index=0; bill_index<gen_bill_param_det.tot_num_value; bill_index++)
			{
				if(index>=g_raw_data_idx)
				{
					printf(">>>>Reached MAX decode index from raw data\n");
					break;
				}
				index = index+2;
				for(idx=0; idx<g_num_ls_param; idx++)
				{
					data_type = g_raw_data_buff[index++];
					gen_data_val_info[idx].data_type = data_type;
					
					switch(data_type)
					{
						case	FLOAT_32BIT_TYPE:
						case UNSIGNED_32BIT_TYPE:
						case SIGNED_32BIT_TYPE:
							gen_data_val_info[idx].num_bytes = 4;
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],4);
							index+=4;
						break;
						
						case UNSIGNED_16BIT_TYPE:
						case SIGNED_16BIT_TYPE:
							gen_data_val_info[idx].num_bytes = 2;
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],2);
							index+=2;
						break;
						
						case UNSIGNED_8BIT_TYPE:
							gen_data_val_info[idx].num_bytes = 1;
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],1);
							index+=1;
						break;
						
						case OCTET_STRING_TYPE:
							//printf("ls_index : %d Before Date time decode index : %d\n",ls_index,index);
							gen_data_val_info[idx].num_bytes = g_raw_data_buff[index];
							memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index+1],gen_data_val_info[idx].num_bytes);
							index+=(gen_data_val_info[idx].num_bytes+1);
						break;
						
						default : break;
					}
				}
				
				if(fill_billing_val(bill_index)<0)
				{
					dbg_log(REPORT,"%-20s : Failed to filled for Bill index : %d\n",fun_name,bill_index);
						continue;
				}
				
				print_bill_data_info();
			}
		}
		break;
		
		default : break;
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_gen_scalar_val()
*Input Parameters 			: comm_fd,meter_address,meter_addr_size,qry_type,inf_class,obis_code,obis_code_len,attr_num.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get scalar value for various query type.
********************************************************************************************************/
int32_t get_gen_scalar_val(meter_comm_params_t *meter_comm_params, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
{
	static char fun_name[]="get_gen_scalar_val()";

	uint8_t temp_nxt_blk_flag = 0;
	
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	g_get_nxt_blk_val=1;
	g_first_time_resp=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = recv_qry_type;

	if(send_get_request(meter_comm_params, int_class, obis_code, obis_len, attr_no)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get inst scaler obis info\n",fun_name);
		return -1;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst scaler value rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst scaler value next block frame\n",fun_name);
				return -1;
			}
		}
	}
	
	if(fill_val_obis_det(recv_qry_type)<0)
		return -1;
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_gen_scalar_obis()
*Input Parameters 			: comm_fd,meter_address,meter_addr_size,qry_type,inf_class,obis_code,obis_code_len,attr_num.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get scalar obis for various query type.
********************************************************************************************************/
int32_t get_gen_scalar_obis(meter_comm_params_t *meter_comm_params,uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
{
	static char fun_name[]="get_gen_scalar_obis()";

	uint8_t temp_nxt_blk_flag = 0;
	
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	g_get_nxt_blk_val=1;
	g_first_time_resp=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;

	g_query_type = recv_qry_type;
	
	
	if(send_get_request(meter_comm_params, int_class, obis_code, obis_len, attr_no)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get inst scaler obis info\n",fun_name);
		return -1;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst scaler obis rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst scaler obis next block frame\n",fun_name);
				return -1;
			}
		}
	}

	if(fill_val_obis_det(recv_qry_type)<0)
		return -1;
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_gen_val_obis()
*Input Parameters 			: comm_fd,meter_address,meter_addr_size,qry_type,inf_class,obis_code,obis_code_len,attr_num.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get val obis for various query type.
********************************************************************************************************/
int32_t get_gen_val_obis(meter_comm_params_t *meter_comm_params, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
{
	static char fun_name[]="get_inst_val_obis()";
	
	uint8_t temp_nxt_blk_flag = 0;
	
	g_get_nxt_blk_val=1;
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	
	g_first_time_resp=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = recv_qry_type;
	
	if(send_get_request(meter_comm_params, int_class, obis_code, obis_len, attr_no)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get val obis info\n",fun_name);
		return -1;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst val obis rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst val obis get next blk frame\n",fun_name);
				return -1;
			}
			temp_nxt_blk_flag=0;
			g_get_nxt_blk_val = g_get_nxt_blk_val+1;
		}
	}
	
	if(fill_val_obis_det(recv_qry_type)<0)
		return -1;
	
	return RET_SUCCESS;
}

/* Billing Related */
/**************************************************************************************************
*Function 					: get_num_bill_entries()
*Input Parameters 			: comm_fd, meter address, meter addr size.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get total num of Billing available.
********************************************************************************************************/
int32_t get_num_bill_entries(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="get_num_bill_entries()";
	
	uint8_t 	idx=0;
	
	uint8_t 	temp_nxt_blk_flag = 0;
	uint8_t 	obis[6]={0};
	
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	g_get_nxt_blk_val=1;
	g_first_time_resp=1;
	
	GET_OBIS_OCTETS(BILL_ENTRY_OBIS_STR,obis);
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = BILL_ENTRIES_TYPE;
	dbg_log(INFORM,"%-20s : Sending QryType : BILL_ENTRIES_TYPE\n",fun_name);

	if(send_get_request(meter_comm_params, BILL_ENTRY_INT_CLASS, obis, 6, BILL_ENTRY_ARR_NO)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get event entry data info\n",fun_name);
		return -1;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get bill entry rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get bill entry get next frame frame\n",fun_name);
				return -1;
			}
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: print_date_info()
*Input Parameters 			: date_time struct.
*Output Parameters 			: None.
*Return	Value				: Void.
*Description 				: To print date_time info of recv structure.
********************************************************************************************************/
void print_date_info(date_time_t date_time)
{
	printf("%02d_%02d_%04d %02d:%02d:%02d\n",date_time.day,date_time.month,date_time.year,
	date_time.hour,date_time.minute,date_time.second);
}

/**************************************************************************************************
*Function 					: print_bill_data_info()
*Input Parameters 			: Void.
*Output Parameters 			: None.
*Return	Value				: Void.
*Description 				: To print billing data information.
********************************************************************************************************/
void print_bill_data_info(void)
{
	static char fun_name[]="print_bill_data_info()";
	uint8_t 	idx=0,file_avl=0;
	FILE		*p_file_ptr=NULL;
	char 		curr_ls_file_path[64];
	float 		flt_val=0.0;
	int32_t 	int_val = 0;
	struct stat 		st;
	char 		value_buff[32],obis_buff[32];
	date_time_t date_time;
	
	memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
	sprintf(curr_ls_file_path,"%s/billing",g_ls_data_dir_path);
	
	p_file_ptr = fopen(curr_ls_file_path,"w");
	if(p_file_ptr == NULL)
	{
		dbg_log(REPORT,"%-20s : Event File is not opened write mode, Error : %s\n",fun_name,strerror(errno));
		return ;
	}

	dbg_log(INFORM,"%-20s : Adding OBIS Header for Billing file : %s\n",fun_name,curr_ls_file_path);
	for(idx=0; idx<g_all_bill_param_obis_val.tot_num_params; idx++)
	{
		memset(obis_buff,0,sizeof(obis_buff));
		sprintf(obis_buff,"%d.%d.%d.%d.%d.%d",
		g_all_bill_param_obis_val.param_obis_val_info[idx].obis_code[0],
		g_all_bill_param_obis_val.param_obis_val_info[idx].obis_code[1],
		g_all_bill_param_obis_val.param_obis_val_info[idx].obis_code[2],
		g_all_bill_param_obis_val.param_obis_val_info[idx].obis_code[3],
		g_all_bill_param_obis_val.param_obis_val_info[idx].obis_code[4],
		g_all_bill_param_obis_val.param_obis_val_info[idx].obis_code[5]
		);

		fprintf(p_file_ptr,"%s\t",obis_buff);
		printf("%s\t",obis_buff);
		
		fflush(p_file_ptr);

		memset(value_buff,0,sizeof(obis_buff));
		switch(g_all_bill_param_obis_val.param_obis_val_info[idx].data_type)
		{
			case OCTET_STRING_TYPE:
			{
				memset(&date_time,0,sizeof(date_time));
				memcpy(&date_time,&g_all_bill_param_obis_val.param_obis_val_info[idx].value,sizeof(date_time_t));
				sprintf(value_buff,"%02d_%02d_%02d %02d:%02d",date_time.day,date_time.month,date_time.year,date_time.hour,date_time.minute);
			}
			break;
			
			default:
			{
				memcpy(&flt_val,&g_all_bill_param_obis_val.param_obis_val_info[idx].value,4);
				sprintf(value_buff,"%0.5f",flt_val);
			}
			break;
		}
		
		fprintf(p_file_ptr,"%s\n",value_buff);
		printf("%s\n",value_buff);

		fflush(p_file_ptr);
	}
	
	fclose(p_file_ptr);
	
	return;
}

void print_bill_data_info1(void)
{
	float float_val=0.0;
	
	print_date_info(g_bill_val_info.date_time);
	memcpy(&float_val,&g_bill_val_info.sys_pf.param_value,4);
	printf("SYS_PF : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kwh.param_value,4);
	printf("KWH : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kwh_tz1.param_value,4);
	printf("KWH_TZ1 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kwh_tz2.param_value,4);
	printf("KWH_TZ2 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kwh_tz3.param_value,4);
	printf("KWH_TZ3 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kwh_tz4.param_value,4);
	printf("KWH_TZ4 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kwh_tz5.param_value,4);
	printf("KWH_TZ5 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kwh_tz6.param_value,4);
	printf("KWH_TZ6 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kwh_tz7.param_value,4);
	printf("KWH_TZ7 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kwh_tz8.param_value,4);
	printf("KWH_TZ8 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvarh_lag.param_value,4);
	printf("KVARH_LAG : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvarh_lead.param_value,4);
	printf("KVARH_LEAD : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvah.param_value,4);
	printf("KVAH : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvah_tz1.param_value,4);
	printf("KVAH_TZ1 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvah_tz2.param_value,4);
	printf("KVAH_TZ2 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvah_tz3.param_value,4);
	printf("KVAH_TZ3 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvah_tz4.param_value,4);
	printf("KVAH_TZ4 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvah_tz5.param_value,4);
	printf("KVAH_TZ5 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvah_tz6.param_value,4);
	printf("KVAH_TZ6 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvah_tz7.param_value,4);
	printf("KVAH_TZ7 : %0.5f\n",float_val);
	
	float_val=0.0;
	memcpy(&float_val,&g_bill_val_info.kvah_tz8.param_value,4);
	printf("KVAH_TZ8 : %0.5f\n",float_val);
}

/**************************************************************************************************
*Function 					: get_bill_data_info()
*Input Parameters 			: structure containing meter id, meter address etc.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get billing data information.
********************************************************************************************************/
int32_t get_bill_data_info(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="get_bill_data_info()";
	uint8_t obis[6] = {0};
	uint8_t temp_nxt_blk_flag = 0;
	
	/* uint8_t comm_fd = meter_comm_params->fd;
	uint32_t dlms_met_addr = meter_comm_params->meter_id;
	uint8_t met_addr_size = meter_comm_params->meter_addr_format; */
	
	GET_OBIS_OCTETS(BILL_DATA_VAL_OBIS_STR,obis);
	
	if(get_num_bill_entries(meter_comm_params)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get number of billing info\n",fun_name);
		return -1;
	}
	
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	
	g_first_time_resp=1;
	g_get_nxt_blk_val=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = BILL_VALUE_TYPE;
	dbg_log(INFORM,"%-20s : Sending QryType : BILL_VALUE_TYPE\n",fun_name);
	
	if(send_get_bill_request(meter_comm_params,BILL_DATA_INT_CLASS, obis, 6, BILL_DATA_ATTR_NO)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get daily profile  value info\n",fun_name);
		return -1;
	}

	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get daily profile  value rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			//if(send_get_next_blk(midx, g_get_nxt_blk_val)<0)
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get daily profile  value get next frame frame\n",fun_name);
				return -1;
			}
			temp_nxt_blk_flag=0;
			g_get_nxt_blk_val = g_get_nxt_blk_val+1;
		}
	}
	
	if(fill_val_obis_det(BILL_VALUE_TYPE)<0)
		return -1;
	
	//print_bill_data_info();
	
	meter_comm_params->resp_len = sizeof(g_bill_val_info);
	
	memcpy(&meter_comm_params->meter_response, &g_bill_val_info, sizeof(g_bill_val_info));
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: store_bill_date_time()
*Input Parameters 			: Bill Index and value index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store billing time info in appropriate structure.
********************************************************************************************************/
int32_t store_bill_date_time(uint8_t bill_index, uint8_t index)
{
	uint16_t 	year=0;
	uint8_t 	bill_dt_idx=0;
	date_time_t loc_date_time={0};
	
	date_time_t date_time;
	
	year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
	date_time.day= gen_data_val_info[index].value[3];
	date_time.month= gen_data_val_info[index].value[2];
	date_time.year =  year;
	date_time.hour= gen_data_val_info[index].value[5];
	date_time.minute= gen_data_val_info[index].value[6];
	date_time.second= gen_data_val_info[index].value[7];
	
	memcpy(&g_all_bill_param_obis_val.param_obis_val_info[index].obis_code,gen_bill_param_det.val_obis[index],6);
	memcpy(&g_all_bill_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_bill_param_obis_val.param_obis_val_info[index].value,&date_time,sizeof(date_time_t));
	
	return RET_SUCCESS;
	
	printf("Bill Idx : %d, BillParamIdx : %d\n",bill_index,index);
	
	for(bill_dt_idx=0; bill_dt_idx<gen_bill_param_det.tot_num_val_obis; bill_dt_idx++)
	{
		if((index==0)&&(bill_dt_idx==0))
		{
			print_data(gen_bill_param_det.val_obis[index],6);
			//print_data(g_billing_param_det[bill_dt_idx].obis_code,6);
		}
		
		if( (memcmp(gen_bill_param_det.val_obis[index], g_billing_param_det[bill_dt_idx].obis_code,6)) == 0)
		{
			year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
				loc_date_time.day= gen_data_val_info[index].value[3];
				loc_date_time.month= gen_data_val_info[index].value[2];
				loc_date_time.year =  year;
				loc_date_time.hour= gen_data_val_info[index].value[5];
				loc_date_time.minute= gen_data_val_info[index].value[6];
				loc_date_time.second= 0;
			
			print_date_info(loc_date_time);
			
			if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"date_time",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.date_time,&loc_date_time,sizeof(date_time_t));
			} 
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kwmd",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kwmd_date_time,&loc_date_time,sizeof(date_time_t));
			}
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kwmd_tz1",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kwmd_tz1_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kwmd_tz2",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kwmd_tz2_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kwmd_tz3",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kwmd_tz3_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kwmd_tz4",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kwmd_tz4_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kwmd_tz5",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kwmd_tz5_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kwmd_tz6",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kwmd_tz6_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kwmd_tz7",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kwmd_tz7_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kwmd_tz8",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kwmd_tz8_date_time,&loc_date_time,sizeof(date_time_t));
			}
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kvamd",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kvamd_date_time,&loc_date_time,sizeof(date_time_t));
			}
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kvamd_tz1",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kvamd_tz1_date_time,&loc_date_time,sizeof(date_time_t));
			}
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kvamd_tz2",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kvamd_tz2_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kvamd_tz3",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kvamd_tz3_date_time,&loc_date_time,sizeof(date_time_t));
			}
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kvamd_tz4",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kvamd_tz4_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kvamd_tz5",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kvamd_tz5_date_time,&loc_date_time,sizeof(date_time_t));
			}
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kvamd_tz6",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kvamd_tz6_date_time,&loc_date_time,sizeof(date_time_t));
			}
			
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kvamd_tz7",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kvamd_tz7_date_time,&loc_date_time,sizeof(date_time_t));
			}
			else if( (memcmp(g_billing_param_det[bill_dt_idx].param_name,"kvamd_tz8",strlen(g_billing_param_det[bill_dt_idx].param_name))) == 0)
			{
				memcpy(&g_bill_val_info.kvamd_tz8_date_time,&loc_date_time,sizeof(date_time_t));
			}
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: store_bill_val()
*Input Parameters 			: Bill Index, value index and Billing value.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store Billing data info in appropriate structure.
********************************************************************************************************/
int32_t store_bill_val(uint8_t dp_index, uint8_t index, float recv_flt_val)
{
	uint8_t idx = 0;
	
	memcpy(&g_all_bill_param_obis_val.param_obis_val_info[index].obis_code,gen_bill_param_det.val_obis[index],6);
	memcpy(&g_all_bill_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_bill_param_obis_val.param_obis_val_info[index].value,&recv_flt_val,4);
	
	return RET_SUCCESS;
	
	//for(idx=0; idx<gen_bill_param_det.tot_num_val_obis; idx++)
	for(idx=0; idx<MAX_NUM_BILL_PARAMS; idx++)
	{
		if( (memcmp(gen_bill_param_det.val_obis[index],g_billing_param_det[idx].obis_code,6)) == 0)
		{
/* 			printf("--->>>>Param Obis and Val Obis matched:: Index : %d Idx : %d g_ls_entry_idx : %d recv_flt_val : %0.5f\n",
			index,idx,g_ls_entry_idx,recv_flt_val); */
			
			if( (memcmp(g_billing_param_det[idx].param_name,"sys_pf",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.sys_pf.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.sys_pf.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.sys_pf.param_name,"%s","BILL_SYS_PF");
			}
			
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwh",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwh.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwh.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwh.param_name,"%s","BILL_KWH");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwh_tz1",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwh_tz1.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwh_tz1.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwh_tz1.param_name,"%s","BILL_KWH_TZ1");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwh_tz2",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwh_tz2.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwh_tz2.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwh_tz2.param_name,"%s","BILL_KWH_TZ2");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwh_tz3",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwh_tz3.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwh_tz3.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwh_tz3.param_name,"%s","BILL_KWH_TZ3");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwh_tz4",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwh_tz4.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwh_tz4.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwh_tz4.param_name,"%s","BILL_KWH_TZ4");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwh_tz5",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwh_tz5.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwh_tz5.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwh_tz5.param_name,"%s","BILL_KWH_TZ5");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwh_tz6",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwh_tz6.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwh_tz6.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwh_tz6.param_name,"%s","BILL_KWH_TZ6");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwh_tz7",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwh_tz7.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwh_tz7.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwh_tz7.param_name,"%s","BILL_KWH_TZ7");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwh_tz8",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwh_tz8.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwh_tz8.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwh_tz8.param_name,"%s","BILL_KWH_TZ8");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvarh_lag",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvarh_lag.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvarh_lag.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvarh_lag.param_name,"%s","BILL_KVARH_LAG");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvarh_lead",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvarh_lead.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvarh_lead.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvarh_lead.param_name,"%s","BILL_KVARH_LEAD");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvah",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvah.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvah.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvah.param_name,"%s","BILL_KVAH");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvah_tz1",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvah_tz1.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvah_tz1.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvah_tz1.param_name,"%s","BILL_KVAH_TZ1");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvah_tz2",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvah_tz2.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvah_tz2.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvah_tz2.param_name,"%s","BILL_KVAH_TZ2");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvah_tz3",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvah_tz3.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvah_tz3.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvah_tz3.param_name,"%s","BILL_KVAH_TZ3");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvah_tz4",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvah_tz4.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvah_tz4.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvah_tz4.param_name,"%s","BILL_KVAH_TZ4");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvah_tz5",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvah_tz5.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvah_tz5.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvah_tz5.param_name,"%s","BILL_KVAH_TZ5");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvah_tz6",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvah_tz6.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvah_tz6.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvah_tz6.param_name,"%s","BILL_KVAH_TZ6");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvah_tz7",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvah_tz7.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvah_tz7.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvah_tz7.param_name,"%s","BILL_KVAH_TZ7");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvah_tz8",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvah_tz8.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvah_tz8.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvah_tz8.param_name,"%s","BILL_KVAH_TZ8");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwmd",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwmd.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwmd.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwmd.param_name,"%s","BILL_KWMD");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwmd_tz1",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwmd_tz1.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwmd_tz1.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwmd_tz1.param_name,"%s","BILL_KWMD_TZ1");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwmd_tz2",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwmd_tz2.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwmd_tz2.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwmd_tz2.param_name,"%s","BILL_KWMD_TZ2");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwmd_tz3",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwmd_tz3.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwmd_tz3.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwmd_tz3.param_name,"%s","BILL_KWMD_TZ3");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwmd_tz4",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwmd_tz4.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwmd_tz4.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwmd_tz4.param_name,"%s","BILL_KWMD_TZ4");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwmd_tz5",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwmd_tz5.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwmd_tz5.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwmd_tz5.param_name,"%s","BILL_KWMD_TZ5");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwmd_tz6",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwmd_tz6.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwmd_tz6.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwmd_tz6.param_name,"%s","BILL_KWMD_TZ6");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwmd_tz7",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwmd_tz7.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwmd_tz7.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwmd_tz7.param_name,"%s","BILL_KWMD_TZ7");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kwmd_tz8",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kwmd_tz8.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kwmd_tz8.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kwmd_tz8.param_name,"%s","BILL_KWMD_TZ8");
			}else if( (memcmp(g_billing_param_det[idx].param_name,"kvamd",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvamd.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvamd.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvamd.param_name,"%s","BILL_KVAMD");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvamd_tz1",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvamd_tz1.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvamd_tz1.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvamd_tz1.param_name,"%s","BILL_KVAMD_TZ1");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvamd_tz2",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvamd_tz2.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvamd_tz2.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvamd_tz2.param_name,"%s","BILL_KVAMD_TZ2");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvamd_tz3",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvamd_tz3.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvamd_tz3.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvamd_tz3.param_name,"%s","BILL_KVAMD_TZ3");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvamd_tz4",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvamd_tz4.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvamd_tz4.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvamd_tz4.param_name,"%s","BILL_KVAMD_TZ4");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvamd_tz5",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvamd_tz5.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvamd_tz5.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvamd_tz5.param_name,"%s","BILL_KVAMD_TZ5");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvamd_tz6",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvamd_tz6.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvamd_tz6.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvamd_tz6.param_name,"%s","BILL_KVAMD_TZ6");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvamd_tz7",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvamd_tz7.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvamd_tz7.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvamd_tz7.param_name,"%s","BILL_KVAMD_TZ7");
			}
			else if( (memcmp(g_billing_param_det[idx].param_name,"kvamd_tz8",strlen(g_billing_param_det[idx].param_name))) == 0)
			{
				memcpy(g_bill_val_info.kvamd_tz8.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(g_bill_val_info.kvamd_tz7.param_value,&recv_flt_val,4);
				sprintf(g_bill_val_info.kvamd_tz8.param_name,"%s","BILL_KVAMD_TZ8");
			}
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_billing_obis_code_det()
*Input Parameters 			: comm_fd, dlma address, meter addr size, general param structure.
*Output Parameters 			: general param structure.
*Return	Value				: Success or appropriate error code.
*Description 				: To get billing obis code details and fill in appropriate structure.
********************************************************************************************************/
int32_t get_billing_obis_code_det(meter_comm_params_t *meter_comm_params,gen_params_det_t *recv_gen_billing_param_det)
{
	static char fun_name[]="get_billing_obis_code_det()";
	uint8_t obis[8] = {0};
	
	GET_OBIS_OCTETS(BILL_VAL_OBIS_STR,obis);
	
	dbg_log(INFORM,"%-20s : Sending QryType : BILL_VAL_OBIS_TYPE\n",fun_name);
	if(get_gen_val_obis(meter_comm_params, BILL_VAL_OBIS_TYPE,BILL_VAL_INT_CLASS,obis,6,BILL_VAL_ARR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get daily profile val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	printf("1. Getting Billing Obis code info\n");
	GET_OBIS_OCTETS(BILL_SCALAR_OBIS_STR,obis);
	/* //1,0,94,91,6,255
	 val_obis[0] = 1;
	 val_obis[1] = 0;
	 val_obis[2] = 94;
	 val_obis[3] = 91;
	 val_obis[4] = 6;
	 val_obis[5] = 255;
	 
	 int_class=0x0007, attr_no=0x0003; */
	
	dbg_log(INFORM,"%-20s : Sending QryType : BILL_SCALER_OBIS_TYPE\n",fun_name);
	if(get_gen_scalar_obis(meter_comm_params, BILL_SCALER_OBIS_TYPE,BILL_SCALAR_INT_CLASS,obis,6,BILL_SCARAR_ARR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	/* val_obis[0] = 1;
	val_obis[1] = 0;
	val_obis[2] = 94;
	val_obis[3] = 91;
	val_obis[4] = 6;
	val_obis[5] = 255;
	 
	int_class=0x0007, attr_no=0x0002; */
	
	GET_OBIS_OCTETS(BILL_SCALAR_VAL_STR,obis);
	dbg_log(INFORM,"%-20s : Sending QryType : BILL_SCALER_VALUE_TYPE\n",fun_name);
	if(get_gen_scalar_val(meter_comm_params, BILL_SCALER_VALUE_TYPE,BILL_SCALAR_VAL_INT_CLASS,obis,6,BILL_SCALAR_VAL_ARR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_billing_val_obis()
*Input Parameters 			: Buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process billing val obis.
********************************************************************************************************/
int32_t proc_billing_val_obis( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_billing_val_obis()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_bill_param_det.tot_num_val_obis = msg[loc_idx-1];
		
		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen in Getnext block\n",fun_name);
				
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_billing_scalar_obis()
*Input Parameters 			: Buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process billing scalar obis.
********************************************************************************************************/
int32_t proc_billing_scalar_obis( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_billing_scalar_obis()";

	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_bill_param_det.tot_num_scalar = msg[loc_idx-1];

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_billing_scalar_val()
*Input Parameters 			: Buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process billing scalar val obis.
********************************************************************************************************/
int32_t proc_billing_scalar_val( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_billing_scalar_val()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0F))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));
		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0F))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_billing_value()
*Input Parameters 			: Buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process Billing value.
********************************************************************************************************/
int32_t proc_billing_value( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_billing_value()";
	
	uint8_t loc_idx=0;
	uint32_t index=0;
	
	if(g_first_time_resp == 1)
	{
		for(index=0; index<len; index++)
		{
			if((msg[index] == 0X02) && ((msg[index+2] == 0X09)))
			{
				loc_idx = index;
				g_num_ls_param = msg[index+1];
				break;
			}
		}
		
		if(index == len)
		{
			dbg_log(REPORT,"%-20s : No start stamp seen.\n",fun_name);
			return -1;
		}
		
		gen_bill_param_det.tot_num_value = msg[index-1];
		
		dbg_log(INFORM,"%-20s : Billing NumOfEntry : %d, Num of Params : %d\n",
		fun_name,gen_bill_param_det.tot_num_value,g_num_ls_param);
		
		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		else if(g_get_nxt_blk || g_comp_blk_resp)
		{
			for(index=0; index<len; index++)
			{
				if((msg[index] == 0X02) && ((msg[index+2] == 0X09)))
				{
					loc_idx = index;
					g_num_ls_param = msg[index+1];
					break;
				}
			}
			
			if(index == len)
			{
				dbg_log(REPORT,"%-20s : No start stamp seen.\n",
				fun_name);
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);

	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: fill_billing_val()
*Input Parameters 			: bill index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To fill billing data value into appropriate structure.
********************************************************************************************************/
int32_t fill_billing_val(uint8_t bill_index)
{
	static char fun_name[]="fill_billing_val()";

	uint8_t 	idx=0;
	int8_t 		*p_tmp_str=NULL;
	float 		flt_val = 0.0,scal_flt_val=0.0;
	uint8_t		uint8_temp_val=0;
	int16_t		int16_temp_val=0;
	uint16_t	uint16_temp_val=0;
	int32_t		int32_temp_val=0;
	uint32_t	uint32_temp_val=0;
	float 		float_temp_val = 0.0;
	
	//printf("Filling Midnight day idx : %d, g_num_ls_param : %d\n",dp_index,g_num_ls_param);
	
	memset(&g_all_bill_param_obis_val,0,sizeof(g_all_bill_param_obis_val));
	g_all_bill_param_obis_val.tot_num_params=g_num_ls_param;
	
	for(idx=0; idx<g_num_ls_param; idx++)
	{
		switch(gen_data_val_info[idx].data_type)
		{
			case	FLOAT_32BIT_TYPE:
				p_tmp_str=(int8_t*)&float_temp_val;
				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_dp_param_det.scalar_val[idx].value,&scal_flt_val);
				
				//dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
				//fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,float_temp_val);
	
				flt_val = (float)((float)float_temp_val * scal_flt_val);
				
				//dbg_log(INFORM,"%-20s : After Multiply value : %f\n",fun_name,flt_val);
				
				if(store_bill_val(bill_index, idx, flt_val) < 0)
					continue;
			break;
			
			case UNSIGNED_32BIT_TYPE:
			case SIGNED_32BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					p_tmp_str=(int8_t*)&uint32_temp_val;
				else
					p_tmp_str=(int8_t*)&int32_temp_val;

				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_dp_param_det.scalar_val[idx].value,&scal_flt_val);
/* 				printf(":::::::::recv_ls_idx : %d Idx : %d ScalarVal : %d scal_flt_val : %f\n",
				recv_ls_idx,idx,gen_dp_param_det.scalar_val[idx].value,scal_flt_val); */
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
				{
					flt_val = (float)((float)uint32_temp_val * scal_flt_val);
					/* dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
					fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,(float)uint32_temp_val); */
				}
				else
				{
					flt_val = (float)((float)int32_temp_val * scal_flt_val);
					/* dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
					fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,(float)int32_temp_val); */
				}
				
				/* dbg_log(INFORM,"%-20s : After Multiply value : %f\n",fun_name,flt_val); */
				if(store_bill_val(bill_index, idx, flt_val) < 0)
					continue;
	
			break;
			
			case UNSIGNED_16BIT_TYPE:
			case SIGNED_16BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					p_tmp_str=(int8_t*)&uint16_temp_val;
				else
					p_tmp_str=(int8_t*)&int16_temp_val;

				p_tmp_str[1] = gen_data_val_info[idx].value[0];
				p_tmp_str[0] = gen_data_val_info[idx].value[1];
				
				get_scaler_mf(gen_dp_param_det.scalar_val[idx].value,&scal_flt_val);
				
				/* printf("16BIT_TYPE :::::recv_ls_idx : %d Idx : %d ScalarVal : %d scal_flt_val : %f\n",
				recv_ls_idx,idx,gen_dp_param_det.scalar_val[idx].value,scal_flt_val); */
				
				/* printf("p_tmp_str[0] : %X, p_tmp_str[1] : %X p_tmp_str[2] : %X, p_tmp_str[3] : %X\n",
									gen_data_val_info[idx].value[0],
									gen_data_val_info[idx].value[1],
									gen_data_val_info[idx].value[2],
									gen_data_val_info[idx].value[3]); */
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
				{
					flt_val = (float)((float)uint16_temp_val * scal_flt_val);	
					/* dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
					fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,uint16_temp_val); */
				}
				else
				{
					flt_val = (float)((float)int16_temp_val * scal_flt_val);
					/* dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
					fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,int16_temp_val); */
				}
				
				/* dbg_log(INFORM,"%-20s : After Multiply value : %f\n",fun_name,flt_val); */
				if(store_bill_val(bill_index, idx, flt_val) < 0)
					continue;

			break;
			
			case UNSIGNED_8BIT_TYPE:
				p_tmp_str=(int8_t*)&uint8_temp_val;
				p_tmp_str[0] = gen_data_val_info[idx].value[0];
				get_scaler_mf(gen_dp_param_det.scalar_val[idx].value,&scal_flt_val);
				flt_val = (float)((float)uint8_temp_val * scal_flt_val);
				
				if(store_bill_val(bill_index, idx, flt_val) < 0)
					continue;
			break;
			
			case OCTET_STRING_TYPE:
				if(store_bill_date_time(bill_index, idx)<0)
					continue;

			break;
			
			default : break;
		}
	}
	
	return RET_SUCCESS;
}

/* MidNight Related */

/**************************************************************************************************
*Function 					: get_dp_obis_code_det()
*Input Parameters 			: comm_fd, dlma address, meter addr size, general param structure.
*Output Parameters 			: general param structure.
*Return	Value				: Success or appropriate error code.
*Description 				: To get daily profile obis code details and fill in appropriate structure.
********************************************************************************************************/
int32_t get_dp_obis_code_det(meter_comm_params_t *meter_comm_params,gen_params_det_t *recv_gen_daily_prof_param_det)
{
	static char fun_name[]="get_dp_obis_code_det()";
	uint8_t val_obis[6] = {0};
	
	GET_OBIS_OCTETS(DP_VAL_OBIS_STR,val_obis);
	dbg_log(INFORM,"%-20s : Sending QryType : DAILY_VAL_OBIS_TYPE\n",fun_name);
	if(get_gen_val_obis(meter_comm_params, DAILY_VAL_OBIS_TYPE,DP_VAL_INT_CLASS,val_obis,6,DP_VAL_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get daily profile val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	 /* val_obis[0] = 1;
	 val_obis[1] = 0;
	 val_obis[2] = 94;
	 val_obis[3] = 91;
	 val_obis[4] = 5;
	 val_obis[5] = 255;
	 
	 int_class=0x0007, attr_no=0x0003; */
	
	GET_OBIS_OCTETS(DP_VAL_OBIS_STR,val_obis);
	dbg_log(INFORM,"%-20s : Sending QryType : DAILY_SCALAR_OBIS_TYPE\n",fun_name);
	if(get_gen_scalar_obis(meter_comm_params, DAILY_SCALAR_OBIS_TYPE,DP_SCALAR_INT_CLASS,val_obis,6,DP_SCALAR_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	/* val_obis[0] = 1;
	val_obis[1] = 0;
	val_obis[2] = 94;
	val_obis[3] = 91;
	val_obis[4] = 5;
	val_obis[5] = 255;
	 
	int_class=0x0007, attr_no=0x0002; */
	
	GET_OBIS_OCTETS(DP_SCALAR_VAL_STR,val_obis);
	dbg_log(INFORM,"%-20s : Sending QryType : DAILY_SCALAR_VALUE_TYPE\n",fun_name);
	if(get_gen_scalar_val(meter_comm_params, DAILY_SCALAR_VALUE_TYPE,DP_SCALAR_VAL_INT_CLASS,val_obis,6,DP_SCALAR_VAL_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: store_dp_date_time()
*Input Parameters 			: Dp Index and value index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store dp time info in appropriate structure.
********************************************************************************************************/
int32_t store_dp_date_time(uint8_t dp_index, uint8_t index)
{
	uint16_t 	year=0;

	date_time_t date_time;
	
	year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
	date_time.day= gen_data_val_info[index].value[3];
	date_time.month= gen_data_val_info[index].value[2];
	date_time.year =  year;
	date_time.hour= gen_data_val_info[index].value[5];
	date_time.minute= gen_data_val_info[index].value[6];
	date_time.second= gen_data_val_info[index].value[7];
	
	memcpy(&g_all_dp_param_obis_val.param_obis_val_info[index].obis_code,gen_dp_param_det.val_obis[index],6);
	memcpy(&g_all_dp_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_dp_param_obis_val.param_obis_val_info[index].value,&date_time,sizeof(date_time_t));
	
	return RET_SUCCESS;
	
	//if(memcmp(gen_dp_param_det.val_obis[index],g_date_time_obis,6)==0)
	if(1)
	{
		g_dp_entry_idx++;
		
		printf("dp_index : %d, Storing date for g_dp_entry_idx : %d -->>> %d_%d %02d:%02d \n",
														dp_index,g_dp_entry_idx,
														gen_data_val_info[index].value[3],
														gen_data_val_info[index].value[2],
														gen_data_val_info[index].value[5],
														gen_data_val_info[index].value[6]);

		year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
		all_daily_profile_data_value.daily_profile_val_info[dp_index].date_time.day= gen_data_val_info[index].value[3];
		all_daily_profile_data_value.daily_profile_val_info[dp_index].date_time.month= gen_data_val_info[index].value[2];
		all_daily_profile_data_value.daily_profile_val_info[dp_index].date_time.year =  year;
		all_daily_profile_data_value.daily_profile_val_info[dp_index].date_time.hour= gen_data_val_info[index].value[5];
		all_daily_profile_data_value.daily_profile_val_info[dp_index].date_time.minute= gen_data_val_info[index].value[6];
		all_daily_profile_data_value.daily_profile_val_info[dp_index].date_time.second= 0;
		
/* 		printf("g_ls_entry_idx ::: %d Stored date %02d-%02d  %02d:%02d \n",g_ls_entry_idx,
				all_ls_data_info.block_val_info[g_ls_entry_idx].date_time.day,
				all_ls_data_info.block_val_info[g_ls_entry_idx].date_time.month,
				all_ls_data_info.block_val_info[g_ls_entry_idx].date_time.hour,
				all_ls_data_info.block_val_info[g_ls_entry_idx].date_time.minute
		); */
		
		return RET_SUCCESS;
	}
	else
	{
		//printf("Ls date time not matched for ls_idx : %d index : %d\n",ls_idx,index);
		return -1;
	}
}

/**************************************************************************************************
*Function 					: store_dp_val()
*Input Parameters 			: Dp Index, value index and DP value.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store dp time info in appropriate structure.
********************************************************************************************************/
int32_t store_dp_val(uint8_t dp_index, uint8_t index, float recv_flt_val)
{
	uint8_t idx = 0;
	
	memcpy(&g_all_dp_param_obis_val.param_obis_val_info[index].obis_code,gen_dp_param_det.val_obis[index],6);
	memcpy(&g_all_dp_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_dp_param_obis_val.param_obis_val_info[index].value,&recv_flt_val,4);
	
	return RET_SUCCESS;
	
	
	recv_flt_val = recv_flt_val/(float)1000;
	
	//for(idx=0; idx<gen_dp_param_det.tot_num_val_obis; idx++)
	for(idx=0; idx<MAX_NUM_DP_PARAMS; idx++)
	{
		if( (memcmp(gen_dp_param_det.val_obis[index],g_daily_profile_param_det[idx].obis_code,6)) == 0)
		{
/* 			printf("--->>>>Param Obis and Val Obis matched:: Index : %d Idx : %d g_ls_entry_idx : %d recv_flt_val : %0.5f\n",
			index,idx,g_ls_entry_idx,recv_flt_val); */
			
			if( (memcmp(g_daily_profile_param_det[idx].param_name,"kvah_imp",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvah_imp.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvah_imp.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvah_imp.param_name,"%s","DP_KVAH_IMP");
			}
			
			else if( (memcmp(g_daily_profile_param_det[idx].param_name,"kvah_exp",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvah_exp.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvah_exp.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvah_exp.param_name,"%s","DP_KVAH_EXP");
			}
			
			else if( (memcmp(g_daily_profile_param_det[idx].param_name,"react_enhi",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].react_enhi.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].react_enhi.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].react_enhi.param_name,"%s","DP_EN_HI");
			}
			
			else if( (memcmp(g_daily_profile_param_det[idx].param_name,"react_enlo",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].react_enlo.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].react_enlo.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].react_enlo.param_name,"%s","DP_EN_LO");
			}
			
			else if((memcmp(g_daily_profile_param_det[idx].param_name,"kvarh_q1",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q1.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q1.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q1.param_name,"%s","DP_KVARH_Q1");
			}
			
			else if( (memcmp(g_daily_profile_param_det[idx].param_name,"kvarh_q2",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q2.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q2.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q2.param_name,"%s","DP_KVARH_Q2");
			}
			
			else if( (memcmp(g_daily_profile_param_det[idx].param_name,"kwh_imp",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kwh_imp.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kwh_imp.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].kwh_imp.param_name,"%s","DP_KWH_IMP");
			}
			
			else if( (memcmp(g_daily_profile_param_det[idx].param_name,"kwh_exp",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kwh_exp.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kwh_exp.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].kwh_exp.param_name,"%s","DP_KWH_EXP");
			}
			
			else if((memcmp(g_daily_profile_param_det[idx].param_name,"kvarh_q3",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q3.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q3.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q3.param_name,"%s","DP_KVARH_Q3");
			}
			
			else if((memcmp(g_daily_profile_param_det[idx].param_name,"kvarh_q4",strlen(g_daily_profile_param_det[idx].param_name))) == 0)
			{
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q4.param_obis_code,gen_dp_param_det.val_obis[index],6);
				memcpy(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q4.param_value,&recv_flt_val,4);
				sprintf(all_daily_profile_data_value.daily_profile_val_info[dp_index].kvarh_q4.param_name,"%s","DP_KVARH_Q4");
			}
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: save_dp_data_file()
*Input Parameters 			: None.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store dp info value in respective file.
********************************************************************************************************/
int32_t save_dp_data_file(void)
{
	static char fun_name[]="save_dp_data_file()";
	char 		curr_ls_file_path[64];
	uint8_t		idx = 0,file_avl=0;
	FILE		*p_file_ptr = NULL;
	float 		flt_val=0.0;
	struct 		stat st;
	date_time_t date_time;
	char 		obis_buff[32],value_buff[32];
	
	memset(&date_time,0,sizeof(date_time_t));
	memcpy(&date_time,&g_all_dp_param_obis_val.param_obis_val_info[0].value,sizeof(date_time_t));
	
	memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
	sprintf(curr_ls_file_path,"%s/dp_%02d_%04d",g_ls_data_dir_path,date_time.month,date_time.year);
	
	if(stat(curr_ls_file_path,&st)==-1)
	{
		file_avl=0;		
	}
	else
	{
		file_avl=1;
	}
	
	if(file_avl==0)
	{
		p_file_ptr = fopen(curr_ls_file_path,"w");
	
		if(p_file_ptr == NULL)
		{
			dbg_log(REPORT,"%-20s : File is not opened write mode, Error : %s\n",fun_name,strerror(errno));
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : Adding OBIS Header for new file : %s\n",fun_name,curr_ls_file_path);
		for(idx=0; idx<g_all_dp_param_obis_val.tot_num_params; idx++)
		{
			memset(obis_buff,0,sizeof(obis_buff));
			sprintf(obis_buff,"%d.%d.%d.%d.%d.%d",
			g_all_dp_param_obis_val.param_obis_val_info[idx].obis_code[0],
			g_all_dp_param_obis_val.param_obis_val_info[idx].obis_code[1],
			g_all_dp_param_obis_val.param_obis_val_info[idx].obis_code[2],
			g_all_dp_param_obis_val.param_obis_val_info[idx].obis_code[3],
			g_all_dp_param_obis_val.param_obis_val_info[idx].obis_code[4],
			g_all_dp_param_obis_val.param_obis_val_info[idx].obis_code[5]
			);
			
			if(idx==g_all_dp_param_obis_val.tot_num_params-1)
				fprintf(p_file_ptr,"%s\n",obis_buff);
			else
				fprintf(p_file_ptr,"%s\t",obis_buff);
			
			fflush(p_file_ptr);
		}
	}
	else
	{
		p_file_ptr = fopen(curr_ls_file_path,"a");
	
		if(p_file_ptr == NULL)
		{
			dbg_log(REPORT,"%-20s : File is not opened append mode, Error : %s\n",fun_name,strerror(errno));
			return -1;
		}
	}
	
	for(idx=0; idx<g_all_dp_param_obis_val.tot_num_params; idx++)
	{
		memset(value_buff,0,sizeof(obis_buff));
		switch(g_all_dp_param_obis_val.param_obis_val_info[idx].data_type)
		{
			case OCTET_STRING_TYPE:
			{
				memset(&date_time,0,sizeof(date_time));
				memcpy(&date_time,&g_all_dp_param_obis_val.param_obis_val_info[idx].value,sizeof(date_time_t));
				sprintf(value_buff,"%02d_%02d_%04d",date_time.day,date_time.month,date_time.year);
			}
			break;
			
			default:
			{
				memcpy(&flt_val,&g_all_dp_param_obis_val.param_obis_val_info[idx].value,4);
				sprintf(value_buff,"%0.5f",flt_val);
			}
			break;
		}
		
		if(idx==g_all_dp_param_obis_val.tot_num_params-1)
		{
			fprintf(p_file_ptr,"%s\n",value_buff);
			printf("%s\n",value_buff);
		}
		else
		{
			fprintf(p_file_ptr,"%s\t",value_buff);
			printf("%s\t",value_buff);
		}
		
		fflush(p_file_ptr);
	}
	
	fclose(p_file_ptr);
	
	return RET_SUCCESS;
}

int32_t save_dp_data_file1(void)
{
	static char fun_name[]="save_dp_data_file()";
	char 		curr_ls_file_path[64];
	uint8_t		idx = 0;
	FILE		*p_file_ptr = NULL;
	float 		p_flt_ptr=0.0;
	struct 		stat st;
	
	memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
	sprintf(curr_ls_file_path,"%s/dp_%02d_%04d",
	g_ls_data_dir_path,
	all_daily_profile_data_value.daily_profile_val_info[0].date_time.month,
	all_daily_profile_data_value.daily_profile_val_info[0].date_time.year
	);
	
	p_file_ptr = fopen(curr_ls_file_path,"w");
	
	if(p_file_ptr == NULL)
	{
		dbg_log(REPORT,"%-20s : File is not opened write mode, Error : %s\n",fun_name,strerror(errno));
		return -1;
	}
	
	fprintf(p_file_ptr,"%s\n","DATE\tKWH_IMP\tKWH_EXP\tKVAH_IMP\tKVAH_EXP\tRE_High\tRE_Low\tKVARH_Q1\tKVARH_Q2\tKVARH_Q3\tKVARH_Q4");
	fflush(p_file_ptr);
	
	fprintf(p_file_ptr,"%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t\%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\n",

			g_date_time_obis[0],g_date_time_obis[1],g_date_time_obis[2],g_date_time_obis[3],
			g_date_time_obis[4],g_date_time_obis[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[5],

			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[5]);
			
	dbg_log(INFORM,"%-20s : Total num of mid_night data available : %d \n",fun_name,g_dp_entry_idx);
	
	dbg_log(INFORM,"%-20s : Listing all midnight data val info : %d \n",fun_name,gen_dp_param_det.tot_num_value);
	
	//for(idx=0; idx<g_dp_entry_idx; idx++)
	for(idx=0; idx<gen_dp_param_det.tot_num_value; idx++)
	{
		printf(">>>idx : %d, fileName : %s/dp_%02d_%04d\n",
		idx,g_ls_data_dir_path,
		all_daily_profile_data_value.daily_profile_val_info[idx].date_time.month,
		all_daily_profile_data_value.daily_profile_val_info[idx].date_time.year);
		
		if(all_daily_profile_data_value.daily_profile_val_info[idx].date_time.day == 0)
		{
			dbg_log(REPORT,"%-20s : Idx : %d Date Time can't be 00_00_0000 \n",fun_name,idx);
			continue;
		}
		
		memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
		
		sprintf(curr_ls_file_path,"%s/dp_%02d_%04d",
		g_ls_data_dir_path,
		all_daily_profile_data_value.daily_profile_val_info[idx].date_time.month,
		all_daily_profile_data_value.daily_profile_val_info[idx].date_time.year
		);
		
		printf(">>>idx : %d, fileName : %s\n",idx,curr_ls_file_path);
		if(stat(curr_ls_file_path,&st)==-1)
		{
			fclose(p_file_ptr);
			
			p_file_ptr = fopen(curr_ls_file_path,"w");
			
			if(p_file_ptr == NULL)
			{
				dbg_log(REPORT,"%-20s : File is not opened write mode, Error : %s\n",fun_name,strerror(errno));
				return -1;
			}
			
			fprintf(p_file_ptr,"%s\n","DATE\tKWH_IMP\tKWH_EXP\tKVAH_IMP\tKVAH_EXP\tRE_High\tRE_Low\tKVARH_Q1\tKVARH_Q2\tKVARH_Q3\tKVARH_Q4");
			fflush(p_file_ptr);
			
			fprintf(p_file_ptr,"%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t\%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\n",

			g_date_time_obis[0],g_date_time_obis[1],g_date_time_obis[2],g_date_time_obis[3],
			g_date_time_obis[4],g_date_time_obis[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_imp.param_obis_code[5],

			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kwh_exp.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_imp.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvah_exp.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enhi.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].react_enlo.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q1.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q2.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q3.param_obis_code[5],
			
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[0],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[1],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[2],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[3],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[4],
			all_daily_profile_data_value.daily_profile_val_info[0].kvarh_q4.param_obis_code[5]);
		}
		
		fprintf(p_file_ptr,"%02d_%02d_%04d\t",
		all_daily_profile_data_value.daily_profile_val_info[idx].date_time.day,
		all_daily_profile_data_value.daily_profile_val_info[idx].date_time.month,
		all_daily_profile_data_value.daily_profile_val_info[idx].date_time.year);
	
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].kwh_imp.param_value,4);
		fprintf(p_file_ptr,"%0.5f\t",p_flt_ptr);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].kwh_exp.param_value,4);
		fprintf(p_file_ptr,"%0.5f\t",p_flt_ptr);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].kvah_imp.param_value,4);
		fprintf(p_file_ptr,"%0.5f\t",p_flt_ptr);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].kvah_exp.param_value,4);
		fprintf(p_file_ptr,"%0.5f\t",p_flt_ptr);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].react_enhi.param_value,4);
		fprintf(p_file_ptr,"%0.5f\t",p_flt_ptr);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].react_enlo.param_value,4);
		fprintf(p_file_ptr,"%0.5f\t",p_flt_ptr);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].kvarh_q1.param_value,4);
		fprintf(p_file_ptr,"%0.5f\t",p_flt_ptr);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].kvarh_q2.param_value,4);
		fprintf(p_file_ptr,"%0.5f\t",p_flt_ptr);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].kvarh_q3.param_value,4);
		fprintf(p_file_ptr,"%0.5f\t",p_flt_ptr);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&all_daily_profile_data_value.daily_profile_val_info[idx].kvarh_q4.param_value,4);
		fprintf(p_file_ptr,"%0.5f\n\n",p_flt_ptr);

		fflush(p_file_ptr);
	}
	
	fclose(p_file_ptr);
	
	if(g_secure_met_flag==1)
	{
		dbg_log(INFORM,"%-20s : Meter storing order is FIFO need to sort the DP file : %s\n",fun_name,curr_ls_file_path);
		
		//sort_dp_data_file(curr_ls_file_path);
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_daily_profile_value()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter and read all dp flag.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get midnight data from meter.
********************************************************************************************************/
int32_t get_daily_profile_value(meter_comm_params_t*meter_comm_params, uint8_t dp_all)
{
	static char fun_name[]="get_daily_profile_scalar_val()";
	
	uint8_t obis[6] = {0};
	
	uint8_t temp_nxt_blk_flag = 0;
	
	uint8_t comm_fd = meter_comm_params->fd;
	uint32_t dlms_met_addr = meter_comm_params->meter_id;
	uint8_t met_addr_size = meter_comm_params->meter_addr_format;
	
	GET_OBIS_OCTETS(DP_DATA_VAL_OBIS_STR,obis);
	g_dp_entry_idx = 0;
	
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	
	g_first_time_resp=1;
	g_get_nxt_blk_val=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = DAILY_VALUES_TYPE;
	dbg_log(INFORM,"%-20s : Sending QryType : DAILY_VALUES_TYPE\n",fun_name);
	
	if(dp_all==1)
	{
		if(send_get_request(meter_comm_params,DP_DATA_VAL_INT_CLASS, obis, 6, DP_DATA_VAL_ATTR_NO)<0)
		{
			dbg_log(REPORT,"%-20s : failed to get daily profile  value info\n",fun_name);
			return -1;
		}
	}
	else
	{
		if(get_curr_date_time(meter_comm_params)<0)
		{
			dbg_log(REPORT,"%-20s : failed to get current meter date time\n",fun_name);
			return -1;
		}
		
		g_query_type = DAILY_VALUES_TYPE;
		
		memcpy(&g_end_date_time.day,&meter_date_time,sizeof(date_time_t));
		memcpy(&g_st_date_time.day,&meter_date_time,sizeof(date_time_t));
		g_st_date_time.day = 0;
		
		if(send_blk_profile_request(meter_comm_params, DP_DATA_VAL_INT_CLASS, obis, 6, DP_DATA_VAL_ATTR_NO)<0)
		{
			dbg_log(REPORT,"%-20s : failed to get daily profile data\n",fun_name);
			return -1;
		}
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get daily profile  value rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			//if(send_get_next_blk(midx, g_get_nxt_blk_val)<0)
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get daily profile  value get next frame frame\n",fun_name);
				return -1;
			}
			temp_nxt_blk_flag=0;
			g_get_nxt_blk_val = g_get_nxt_blk_val+1;
		}
	}
	
	if(fill_val_obis_det(DAILY_VALUES_TYPE)<0)
		return -1;
	
	//save_dp_data_file();
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_daily_profile_val_obis()
*Input Parameters 			: Buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process daily profile val obis.
********************************************************************************************************/
int32_t proc_daily_profile_val_obis( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_daily_profile_val_obis()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
		
		/* loc_idx=17+OFFSET; */
		
		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_dp_param_det.tot_num_val_obis = msg[loc_idx-1];
		
		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen in Getnext block\n",fun_name);
				
				return -1;
			}
			
			/* loc_idx=21+OFFSET; */
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	//
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_daily_profile_scalar_obis()
*Input Parameters 			: Buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process daily profile scalar obis.
********************************************************************************************************/
int32_t proc_daily_profile_scalar_obis( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_daily_profile_scalar_obis()";

	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		/* loc_idx=17+OFFSET; */
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_dp_param_det.tot_num_scalar = msg[loc_idx-1];

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
			/* loc_idx=21+OFFSET; */
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_daily_profile_scalar_val()
*Input Parameters 			: Buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process daily profile scalar val obis.
********************************************************************************************************/
int32_t proc_daily_profile_scalar_val( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_daily_profile_scalar_val()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		/* loc_idx=19+OFFSET; */
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0F))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
		
		
		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));
		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0F))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
			/* loc_idx=21+OFFSET; */
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_daily_profile_value()
*Input Parameters 			: Buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process daily profile value.
********************************************************************************************************/
int32_t proc_daily_profile_value( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_daily_profile_value()";
	
	uint8_t loc_idx=0;
	uint32_t index=0;
	
	if(g_first_time_resp == 1)
	{
		for(index=0; index<len; index++)
		{
			if((msg[index] == 0X02) && ((msg[index+2] == 0X09)))
			{
				loc_idx = index;
				g_num_ls_param = msg[index+1];
				break;
			}
		}
		
		if(index == len)
		{
			dbg_log(REPORT,"%-20s : No start stamp seen.\n",fun_name);
			return -1;
		}
		
		gen_dp_param_det.tot_num_value = msg[loc_idx-1];
		
		dbg_log(INFORM,"%-20s : DP num_of_element : %d\n",fun_name,gen_dp_param_det.tot_num_value);
		
		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		else if(g_get_nxt_blk || g_comp_blk_resp)
		{
			for(index=0; index<len; index++)
			{
				if((msg[index] == 0X02) && ((msg[index+2] == 0X09)))
				{
					loc_idx = index;
					g_num_ls_param = msg[index+1];
					break;
				}
			}
			
			if(index == len)
			{
				dbg_log(REPORT,"%-20s : No start stamp seen.\n",
				fun_name);
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	//EXIT :
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: fill_daily_profile_val()
*Input Parameters 			: dp index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To fill midnight data value into appropriate structure.
********************************************************************************************************/
int32_t fill_daily_profile_val(uint8_t dp_index)
{
	static char fun_name[]="fill_daily_profile_val()";

	uint8_t 	idx=0;
	int8_t 		*p_tmp_str=NULL;
	float 		flt_val = 0.0,scal_flt_val=0.0;
	uint8_t		uint8_temp_val=0;
	int16_t		int16_temp_val=0;
	uint16_t	uint16_temp_val=0;
	int32_t		int32_temp_val=0;
	uint32_t	uint32_temp_val=0;
	float 		float_temp_val = 0.0;
	
	//printf("Filling Midnight day idx : %d, g_num_ls_param : %d\n",dp_index,g_num_ls_param);
	
	g_all_dp_param_obis_val.tot_num_params=g_num_ls_param;
	
	for(idx=0; idx<g_num_ls_param; idx++)
	{
		switch(gen_data_val_info[idx].data_type)
		{
			case	FLOAT_32BIT_TYPE:
				p_tmp_str=(int8_t*)&float_temp_val;
				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_dp_param_det.scalar_val[idx].value,&scal_flt_val);
				
				/* dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
				fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,float_temp_val); */
	
				flt_val = (float)((float)float_temp_val * scal_flt_val);
				
				//dbg_log(INFORM,"%-20s : After Multiply value : %f\n",fun_name,flt_val);
				
				if(store_dp_val(dp_index, idx, flt_val) < 0)
					continue;
			break;
			
			case UNSIGNED_32BIT_TYPE:
			case SIGNED_32BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					p_tmp_str=(int8_t*)&uint32_temp_val;
				else
					p_tmp_str=(int8_t*)&int32_temp_val;

				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_dp_param_det.scalar_val[idx].value,&scal_flt_val);
/* 				printf(":::::::::recv_ls_idx : %d Idx : %d ScalarVal : %d scal_flt_val : %f\n",
				recv_ls_idx,idx,gen_dp_param_det.scalar_val[idx].value,scal_flt_val); */
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
				{
					flt_val = (float)((float)uint32_temp_val * scal_flt_val);
					/* dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
					fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,(float)uint32_temp_val); */
				}
				else
				{
					flt_val = (float)((float)int32_temp_val * scal_flt_val);
					/* dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
					fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,(float)int32_temp_val); */
				}
				
				/* dbg_log(INFORM,"%-20s : After Multiply value : %f\n",fun_name,flt_val); */
				if(store_dp_val(dp_index, idx, flt_val) < 0)
					continue;
	
			break;
			
			case UNSIGNED_16BIT_TYPE:
			case SIGNED_16BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					p_tmp_str=(int8_t*)&uint16_temp_val;
				else
					p_tmp_str=(int8_t*)&int16_temp_val;

				p_tmp_str[1] = gen_data_val_info[idx].value[0];
				p_tmp_str[0] = gen_data_val_info[idx].value[1];
				
				get_scaler_mf(gen_dp_param_det.scalar_val[idx].value,&scal_flt_val);
				
				/* printf("16BIT_TYPE :::::recv_ls_idx : %d Idx : %d ScalarVal : %d scal_flt_val : %f\n",
				recv_ls_idx,idx,gen_dp_param_det.scalar_val[idx].value,scal_flt_val); */
				
				/* printf("p_tmp_str[0] : %X, p_tmp_str[1] : %X p_tmp_str[2] : %X, p_tmp_str[3] : %X\n",
									gen_data_val_info[idx].value[0],
									gen_data_val_info[idx].value[1],
									gen_data_val_info[idx].value[2],
									gen_data_val_info[idx].value[3]); */
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
				{
					flt_val = (float)((float)uint16_temp_val * scal_flt_val);	
					/* dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
					fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,uint16_temp_val); */
				}
				else
				{
					flt_val = (float)((float)int16_temp_val * scal_flt_val);
					/* dbg_log(INFORM,"%-20s : Scalar val : %d, ScalFltVal : %f, Before Multiply val : %f\n",
					fun_name,gen_dp_param_det.scalar_val[idx].value,scal_flt_val,int16_temp_val); */
				}
				
				/* dbg_log(INFORM,"%-20s : After Multiply value : %f\n",fun_name,flt_val); */
				if(store_dp_val(dp_index, idx, flt_val) < 0)
					continue;

			break;
			
			case UNSIGNED_8BIT_TYPE:
				p_tmp_str=(int8_t*)&uint8_temp_val;
				p_tmp_str[0] = gen_data_val_info[idx].value[0];
				get_scaler_mf(gen_dp_param_det.scalar_val[idx].value,&scal_flt_val);
				flt_val = (float)((float)uint8_temp_val * scal_flt_val);
				
				if(store_dp_val(dp_index, idx, flt_val) < 0)
					continue;
			break;
			
			case OCTET_STRING_TYPE:
				if(store_dp_date_time(dp_index, idx)<0)
					continue;

			break;
			
			default : break;
		}
	}
	
	return RET_SUCCESS;
}

/* Event Related */
/**************************************************************************************************
*Function 					: store_event_det_file()
*Input Parameters 			: event class type.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store events details into file for a event class type.
********************************************************************************************************/
int32_t store_event_det_file(uint8_t event_class)
{
	static char fun_name[]="store_event_det_file()";
	uint8_t 	e_idx=event_class,idx=0,file_avl=0;
	FILE		*p_file_ptr=NULL;
	char 		curr_ls_file_path[64];
	float 		flt_val=0.0;
	int32_t 	int_val = 0;
	struct stat 		st;
	char 		value_buff[32],obis_buff[32];
	date_time_t date_time;
	
	memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
	sprintf(curr_ls_file_path,"%s/event_%d",g_ls_data_dir_path,event_class);
	
	if(stat(curr_ls_file_path,&st)==-1)
	{
		file_avl=0;
	}
	else
	{
		file_avl=1;
	}
	
	//if(g_append_event_file_flag==0)
	if(file_avl==0)
	{
		p_file_ptr = fopen(curr_ls_file_path,"w");
		if(p_file_ptr == NULL)
		{
			dbg_log(REPORT,"%-20s : Event File is not opened write mode, Error : %s\n",fun_name,strerror(errno));
			g_append_event_file_flag=1;
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : Adding OBIS Header for Event file : %s\n",fun_name,curr_ls_file_path);
		for(idx=0; idx<g_all_event_param_obis_val.tot_num_params; idx++)
		{
			memset(obis_buff,0,sizeof(obis_buff));
			sprintf(obis_buff,"%d.%d.%d.%d.%d.%d",
			g_all_event_param_obis_val.param_obis_val_info[idx].obis_code[0],
			g_all_event_param_obis_val.param_obis_val_info[idx].obis_code[1],
			g_all_event_param_obis_val.param_obis_val_info[idx].obis_code[2],
			g_all_event_param_obis_val.param_obis_val_info[idx].obis_code[3],
			g_all_event_param_obis_val.param_obis_val_info[idx].obis_code[4],
			g_all_event_param_obis_val.param_obis_val_info[idx].obis_code[5]
			);
			
			if(idx==g_all_event_param_obis_val.tot_num_params-1)
				fprintf(p_file_ptr,"%s\n",obis_buff);
			else
				fprintf(p_file_ptr,"%s\t",obis_buff);
			
			fflush(p_file_ptr);
		}
	}
	else
	{
		p_file_ptr = fopen(curr_ls_file_path,"a");
		if(p_file_ptr == NULL)
		{
			dbg_log(REPORT,"%-20s : Event File is not opened Append mode, Error : %s\n",fun_name,strerror(errno));
			g_append_event_file_flag=1;
			return -1;
		}
	}
	
	for(idx=0; idx<g_all_event_param_obis_val.tot_num_params; idx++)
	{
		memset(value_buff,0,sizeof(obis_buff));
		switch(g_all_event_param_obis_val.param_obis_val_info[idx].data_type)
		{
			case OCTET_STRING_TYPE:
			{
				memset(&date_time,0,sizeof(date_time));
				memcpy(&date_time,&g_all_event_param_obis_val.param_obis_val_info[idx].value,sizeof(date_time_t));
				sprintf(value_buff,"%02d_%02d_%02d %02d:%02d",date_time.day,date_time.month,date_time.year,date_time.hour,date_time.minute);
			}
			break;
			
			/* case FLOAT_32BIT_TYPE:
			{
				memcpy(&flt_val,&g_all_event_param_obis_val.param_obis_val_info[idx].value,4);
				sprintf(value_buff,"%0.5f",flt_val);
				printf("Event type : ,Eid : %d is float type\n",event_class,idx);
			}
			break; */
			
			default:
			{
				memcpy(&flt_val,&g_all_event_param_obis_val.param_obis_val_info[idx].value,4);
				sprintf(value_buff,"%0.5f",flt_val);
				
				/* int_val=0;
				memcpy(&int_val,&g_all_event_param_obis_val.param_obis_val_info[idx].value,4);
				sprintf(value_buff,"%d",int_val);
				printf("Event type : ,Eid : %d is integer type\n",event_class,idx); */
			}
			break;
		}
		
		if(idx==g_all_event_param_obis_val.tot_num_params-1)
		{
			fprintf(p_file_ptr,"%s\n",value_buff);
			printf("%s\n",value_buff);
		}
		else
		{
			fprintf(p_file_ptr,"%s\t",value_buff);
			printf("%s\t",value_buff);
		}
		
		fflush(p_file_ptr);
	}
	
	fclose(p_file_ptr);
	
	g_append_event_file_flag=1;
	
	return RET_SUCCESS;
}

int32_t store_event_det_file1(uint8_t event_class)
{
	static char fun_name[]="store_event_det_file()";
	uint8_t 	e_idx=event_class,idx=0;
	FILE		*p_file_ptr=NULL;
	char 		curr_ls_file_path[64];
	float 		flt_val=0.0;
	int32_t 	intval = 0.0;
	struct stat 		st;
	
	memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
	sprintf(curr_ls_file_path,"%s/event",g_ls_data_dir_path);
	
	if(stat(curr_ls_file_path,&st)==-1)
	{
		p_file_ptr = fopen(curr_ls_file_path,"w");
		if(p_file_ptr == NULL)
		{
			dbg_log(REPORT,"%-20s : Event File is not opened write mode, Error : %s\n",fun_name,strerror(errno));
			return -1;
		}
		fprintf(p_file_ptr,"EVENT_CODE\tEVENT_TIME\tCURR_R\tCURR_Y\tCURR_B\tVOLT_R\tVOLT_Y\tVOLT_B\tKWH\tPF_R\tPR_Y\tPF_B\n");
		fprintf(p_file_ptr,"%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t\%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\t%d.%d.%d.%d.%d.%d\n",
			all_events_data_value.events_type_info[0].event_val_info[0].event_code.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].event_code.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].event_code.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].event_code.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].event_code.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].event_code.param_obis_code[5],
		
			g_date_time_obis[0],g_date_time_obis[1],g_date_time_obis[2],g_date_time_obis[3],
			g_date_time_obis[4],g_date_time_obis[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ir.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ir.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ir.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ir.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ir.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ir.param_obis_code[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].cur_iy.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_iy.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_iy.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_iy.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_iy.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_iy.param_obis_code[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ib.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ib.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ib.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ib.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ib.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].cur_ib.param_obis_code[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].volt_r.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_r.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_r.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_r.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_r.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_r.param_obis_code[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].volt_y.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_y.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_y.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_y.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_y.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_y.param_obis_code[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].volt_b.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_b.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_b.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_b.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_b.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].volt_b.param_obis_code[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].kwh.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].kwh.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].kwh.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].kwh.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].kwh.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].kwh.param_obis_code[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].pf_r.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_r.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_r.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_r.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_r.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_r.param_obis_code[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].pf_y.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_y.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_y.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_y.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_y.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_y.param_obis_code[5],
			
			all_events_data_value.events_type_info[0].event_val_info[0].pf_b.param_obis_code[0],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_b.param_obis_code[1],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_b.param_obis_code[2],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_b.param_obis_code[3],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_b.param_obis_code[4],
			all_events_data_value.events_type_info[0].event_val_info[0].pf_b.param_obis_code[5]
			);
		fflush(p_file_ptr);
	}
	else
	{
		p_file_ptr = fopen(curr_ls_file_path,"a");
		if(p_file_ptr == NULL)
		{
			dbg_log(REPORT,"%-20s : Event File is not opened Apend mode, Error : %s\n",fun_name,strerror(errno));
			return -1;
		}
	}

	//for(e_idx=0; e_idx<MAX_EVENT_TYPE; e_idx++) 
	{
		dbg_log(INFORM,"%-20s : Etpye : %d, TotNumEvents : %d\n",
		fun_name,e_idx,all_events_data_value.events_type_info[e_idx].num_event);
		
		for(idx=0; idx<all_events_data_value.events_type_info[e_idx].num_event; idx++)
		{
			if(idx==all_events_data_value.events_type_info[e_idx].num_event-1)
			{
				memcpy(&g_event_val_info,&all_events_data_value.events_type_info[e_idx].event_val_info[idx],sizeof(event_val_info_t));
			}
			
			intval=0;
			memcpy(&intval,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].event_code.param_value,4);
			
			if(intval==0)
			{
				dbg_log(INFORM,"%-20s : Etpye : %d, EventNumIdx : %d, Event code can't be ZERO.\n",fun_name,e_idx,idx);
				continue;
			}
			
			fprintf(p_file_ptr,"%d\t%02d/%02d/%04d %02d:%02d:%02d\t",intval,
			
			all_events_data_value.events_type_info[e_idx].event_val_info[idx].date_time.day,
			all_events_data_value.events_type_info[e_idx].event_val_info[idx].date_time.month,
			all_events_data_value.events_type_info[e_idx].event_val_info[idx].date_time.year,
			all_events_data_value.events_type_info[e_idx].event_val_info[idx].date_time.hour,
			all_events_data_value.events_type_info[e_idx].event_val_info[idx].date_time.minute,
			0);
			
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].cur_ir.param_value,4);
			fprintf(p_file_ptr,"%0.5f\t",flt_val);
	
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].cur_iy.param_value,4);
			fprintf(p_file_ptr,"%0.5f\t",flt_val);
			
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].cur_ib.param_value,4);
			fprintf(p_file_ptr,"%0.5f\t",flt_val);
			
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].volt_r.param_value,4);
			fprintf(p_file_ptr,"%0.5f\t",flt_val);
			
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].volt_y.param_value,4);
			fprintf(p_file_ptr,"%0.5f\t",flt_val);flt_val=0.0;
			
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].volt_b.param_value,4);
			fprintf(p_file_ptr,"%0.5f\t",flt_val);
			
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].kwh.param_value,4);
			fprintf(p_file_ptr,"%0.5f\t",flt_val);
			
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].pf_r.param_value,4);
			fprintf(p_file_ptr,"%0.5f\t",flt_val);
			
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].pf_y.param_value,4);
			fprintf(p_file_ptr,"%0.5f\t",flt_val);
			
			flt_val=0.0;
			memcpy(&flt_val,&all_events_data_value.events_type_info[e_idx].event_val_info[idx].pf_b.param_value,4);
			fprintf(p_file_ptr,"%0.5f\n\n",flt_val);

			fflush(p_file_ptr);
		}
	}
	
	fclose(p_file_ptr);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_num_event_entries()
*Input Parameters 			: obis code info.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get total num of event available for a particular obis code.
********************************************************************************************************/
int32_t get_num_event_entries(meter_comm_params_t *meter_comm_params, uint8_t* obis)
{
	static char fun_name[]="get_num_event_entries()";
	
	uint8_t idx=0;
	uint8_t temp_nxt_blk_flag = 0;
	
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	g_get_nxt_blk_val=1;
	g_first_time_resp=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = EVENT_ENTRIES_TYPE;
	dbg_log(INFORM,"%-20s : Sending QryType : EVENT_ENTRIES_TYPE, for event class : %d\n",fun_name,obis[4]);

	if(send_get_request(meter_comm_params, EVENT_ENTRY_INT_CLASS, obis, 6, EVENT_ENTRY_ATTR_NO)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get event entry data info\n",fun_name);
		return -1;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get event entry rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get event entry get next frame frame\n",fun_name);
				return -1;
			}
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: store_event_date_time()
*Input Parameters 			: Event idx, Val Index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store event time  details in appropriate structure.
********************************************************************************************************/
int32_t store_event_date_time( uint8_t e_idx, uint8_t index)
{
	uint16_t 	year=0;
	
	uint8_t idx = g_event_type_idx;

	date_time_t date_time;
	
	year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
	date_time.day= gen_data_val_info[index].value[3];
	date_time.month= gen_data_val_info[index].value[2];
	date_time.year =  year;
	date_time.hour= gen_data_val_info[index].value[5];
	date_time.minute= gen_data_val_info[index].value[6];
	date_time.second= gen_data_val_info[index].value[7];
	
	memcpy(&g_all_event_param_obis_val.param_obis_val_info[index].obis_code,gen_event_param_det.val_obis[index],6);
	memcpy(&g_all_event_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_event_param_obis_val.param_obis_val_info[index].value,&date_time,sizeof(date_time_t));
	
	return RET_SUCCESS;
	
	if(memcmp(gen_event_param_det.val_obis[index],g_date_time_obis,6)==0)
	{
		year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
		all_events_data_value.events_type_info[idx].event_val_info[e_idx].date_time.day= gen_data_val_info[index].value[3];
		all_events_data_value.events_type_info[idx].event_val_info[e_idx].date_time.month= gen_data_val_info[index].value[2];
		all_events_data_value.events_type_info[idx].event_val_info[e_idx].date_time.year =  year;
		all_events_data_value.events_type_info[idx].event_val_info[e_idx].date_time.hour= gen_data_val_info[index].value[5];
		all_events_data_value.events_type_info[idx].event_val_info[e_idx].date_time.minute= gen_data_val_info[index].value[6];
		all_events_data_value.events_type_info[idx].event_val_info[e_idx].date_time.second= gen_data_val_info[index].value[7];

		return RET_SUCCESS;
	}
	else
	{
		return -1;
	}
}

/**************************************************************************************************
*Function 					: store_event_val()
*Input Parameters 			: event class type, event val idx, event value.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store event value details in appropriate structure.
********************************************************************************************************/
int32_t store_event_val( uint8_t event_class, uint8_t index, float recv_flt_val)
{
	uint8_t idx=0;
	
	uint8_t e_idx = g_event_type_idx;
	
	memcpy(&g_all_event_param_obis_val.param_obis_val_info[index].obis_code,gen_event_param_det.val_obis[index],6);
	memcpy(&g_all_event_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_event_param_obis_val.param_obis_val_info[index].value,&recv_flt_val,4);
	
	return RET_SUCCESS;
	
	//printf("store_event_val ::---->>> Index : %d recv  fltval : %0.5f\n",index,recv_flt_val);
	
	//for(idx=0; idx<gen_event_param_det.tot_num_val_obis; idx++)
	for(idx=0; idx<MAX_NUM_EVENT_PARAMS; idx++)
	{
		if( (memcmp(gen_event_param_det.val_obis[index], g_event_param_det[idx].obis_code, 6)) == 0)
		{
			if( (memcmp(g_event_param_det[idx].param_name,"cur_ir",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].cur_ir.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].cur_ir.param_value,&recv_flt_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].cur_ir.param_name,"%s","EVENT_CUR_IR");
			}
			
			else if( (memcmp(g_event_param_det[idx].param_name,"cur_iy",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].cur_iy.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].cur_iy.param_value,&recv_flt_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].cur_iy.param_name,"%s","EVENT_CUR_IY");
			}
			
			else if( (memcmp(g_event_param_det[idx].param_name,"cur_ib",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].cur_ib.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].cur_ib.param_value,&recv_flt_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].cur_ib.param_name,"%s","EVENT_CUR_IB");
			}
			else if( (memcmp(g_event_param_det[idx].param_name,"volt_r",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].volt_r.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].volt_r.param_value,&recv_flt_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].volt_r.param_name,"%s","EVENT_VOLT_R");
			}
			else if( (memcmp(g_event_param_det[idx].param_name,"volt_y",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].volt_y.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].volt_y.param_value,&recv_flt_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].volt_y.param_name,"%s","EVENT_VOLT_Y");
			}
			else if( (memcmp(g_event_param_det[idx].param_name,"volt_b",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].volt_b.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].volt_b.param_value,&recv_flt_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].volt_b.param_name,"%s","EVENT_VOLT_B");
			}
			
			else if( (memcmp(g_event_param_det[idx].param_name,"pf_r",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].pf_r.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].pf_r.param_value,&recv_flt_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].pf_r.param_name,"%s","EVENT_PF_R");
			}
			
			else if( (memcmp(g_event_param_det[idx].param_name,"pf_y",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].pf_y.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].pf_y.param_value,&recv_flt_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].pf_y.param_name,"%s","EVENT_PF_Y");
			}
			
			else if( (memcmp(g_event_param_det[idx].param_name,"pf_b",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].pf_b.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].pf_b.param_value,&recv_flt_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].pf_b.param_name,"%s","EVENT_PF_B");
			}
			
			else if( (memcmp(g_event_param_det[idx].param_name,"kwh",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				float stor_val=recv_flt_val/(float)1000;
				
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].kwh.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].kwh.param_value,&stor_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].kwh.param_name,"%s","EVENT_KWH");
			}
	
			else if( (memcmp(g_event_param_det[idx].param_name,"event_code",strlen(g_event_param_det[idx].param_name))) == 0)
			{
				uint32_t stor_int_val=(uint32_t)recv_flt_val;
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].event_code.param_obis_code,gen_event_param_det.val_obis[index],6);
				memcpy(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].event_code.param_value,&stor_int_val,4);
				sprintf(all_events_data_value.events_type_info[e_idx].event_val_info[event_class].event_code.param_name,"%s","EVENT_CODE");
			}
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_event_val_obis()
*Input Parameters 			: buffer and buffer length.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process event val obis details.
********************************************************************************************************/
int32_t proc_event_val_obis( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_event_val_obis()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}

		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_event_param_det.tot_num_val_obis = msg[loc_idx-1];

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen in Getnext block\n",fun_name);
				
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_event_scalar_obis()
*Input Parameters 			: buffer and buffer length.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process event scalar obis details.
********************************************************************************************************/
int32_t proc_event_scalar_obis( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_event_scalar_obis()";

	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		/* loc_idx=17+OFFSET; */
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}

		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));
		
		gen_event_param_det.tot_num_scalar = msg[loc_idx-1];

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_event_scalar_val()
*Input Parameters 			: buffer and buffer length.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process event scalar value details.
********************************************************************************************************/
int32_t proc_event_scalar_val( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_event_scalar_val()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0F))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}

		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0F))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_event_value()
*Input Parameters 			: buffer and buffer length.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process event value details.
********************************************************************************************************/
int32_t proc_event_value(uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_event_value()";
	uint32_t loc_idx=0,idx=0;
	uint32_t index = 0;
	uint8_t event_idx =0;

	event_idx = g_event_type_idx;
	
	if((msg[12+OFFSET]==0X01) && (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X01))
	{
		gen_event_param_det.tot_num_value = 0;
		
		dbg_log(INFORM,"%-20s : Event Data not available for this Event Type : %d\n",fun_name,event_idx);
		
		all_events_data_value.events_type_info[event_idx].num_event = 0;
		
		return 1;
	}

	if(g_first_time_resp == 1)
	{
		for(index=0; index<len; index++)
		{
			//if((msg[index] == 0X02) && ((msg[index+2] == 0X09)) && ((msg[index+3] == 0X0C)))
			if((msg[index] == 0X01) && ((msg[index+2] == 0X02)))
			{
				loc_idx = index+2;
				g_num_event_param = msg[index+3];
				break;
			}
		}
		
		if(index == len)
		{
			dbg_log(REPORT,"%-20s : No start stamp seen.\n",fun_name);
			return -1;
		}

		dbg_log(INFORM,"%-20s : event_idx : %d num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,event_idx,msg[loc_idx-1],len-(loc_idx+3));

		gen_event_param_det.tot_num_value = msg[loc_idx-1];
		g_num_event_param=0;
		
		if(gen_event_param_det.tot_num_value==0)
		{
			g_num_event_param=0;
		}
		else
		{
			g_num_event_param = msg[loc_idx+1];
			all_events_data_value.events_type_info[event_idx].num_event = msg[loc_idx+1];
		}
		
		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(index=0; index<len; index++)
			{
				if((msg[index] == 0X02) && ((msg[index+2] == 0X09)) && ((msg[index+3] == 0X0C)))
				//if((msg[index] == 0X01) && ((msg[index+2] == 0X02)))
				{
					loc_idx = index+2;
					g_num_ls_param = msg[index+1];
					break;
				}
			}
			
			if(index == len)
			{
				dbg_log(REPORT,"%-20s : No start stanp seen.\n",fun_name);
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: fill_event_val()
*Input Parameters 			: event class.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To fill event value details.
********************************************************************************************************/
int32_t fill_event_val( uint8_t event_idx)
{
	static char fun_name[]="fill_event_val()";

	uint8_t 	idx=0;
	int8_t 		*p_tmp_str=NULL;
	float 		flt_val = 0.0,scal_flt_val=0.0;
	uint8_t		uint8_temp_val=0;
	int16_t		int16_temp_val=0;
	uint16_t	uint16_temp_val=0;
	int32_t		int32_temp_val=0;
	uint32_t	uint32_temp_val=0;
	float 		float_temp_val=0.0;
	
	//printf("fill_event_val :::: Recv_event_idx : %d, g_num_event_param : %d\n",event_idx,g_num_event_param);
	
	g_all_event_param_obis_val.tot_num_params=g_num_event_param;
	
	for(idx=0; idx<g_num_event_param; idx++)
	{
		switch(gen_data_val_info[idx].data_type)
		{
			case	FLOAT_32BIT_TYPE:
				p_tmp_str=(int8_t*)&float_temp_val;
				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_event_param_det.scalar_val[idx].value,&scal_flt_val);
				
				flt_val = (float)((float)float_temp_val * scal_flt_val);
				if(store_event_val(event_idx, idx, flt_val) < 0)
					continue;
			break;
			
			case UNSIGNED_32BIT_TYPE:
			case SIGNED_32BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					p_tmp_str=(int8_t*)&uint32_temp_val;
				else
					p_tmp_str=(int8_t*)&int32_temp_val;

				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_event_param_det.scalar_val[idx].value,&scal_flt_val);
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					flt_val = (float)((float)uint32_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int32_temp_val * scal_flt_val);
				
				if(store_event_val(event_idx, idx, flt_val) < 0)
					continue;
	
			break;
			
			case UNSIGNED_16BIT_TYPE:
			case SIGNED_16BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					p_tmp_str=(int8_t*)&uint16_temp_val;
				else
					p_tmp_str=(int8_t*)&int16_temp_val;

				p_tmp_str[1] = gen_data_val_info[idx].value[0];
				p_tmp_str[0] = gen_data_val_info[idx].value[1];
				
				get_scaler_mf(gen_event_param_det.scalar_val[idx].value,&scal_flt_val);
				
			/* 	printf("16BIT_TYPE :::::event_idx : %d Idx : %d ScalarVal : %d scal_flt_val : %f\n",
				event_idx,idx,gen_event_param_det.scalar_val[idx].value,scal_flt_val); */
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					flt_val = (float)((float)uint16_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int16_temp_val * scal_flt_val);
				
				if(store_event_val(event_idx, idx, flt_val) < 0)
					continue;

			break;
			
			case UNSIGNED_8BIT_TYPE:
			
				//printf("UNSIGNED_8BIT_TYPE : Type\n");
				p_tmp_str=(int8_t*)&uint8_temp_val;
				p_tmp_str[0] = gen_data_val_info[idx].value[0];
				get_scaler_mf(gen_event_param_det.scalar_val[idx].value, &scal_flt_val);
				flt_val = (float)((float)uint8_temp_val * scal_flt_val);
				
				if(store_event_val(event_idx, idx, flt_val) < 0)
					continue;
				
			break;
			
			case OCTET_STRING_TYPE:
				//printf("g_num_event_param : %d ::: Filling Event data for event index : %d\n",g_num_event_param, event_idx);
				if(store_event_date_time(event_idx, idx)<0)
					continue;

			break;
			
			default : break;
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_event_class_data()
*Input Parameters 			: Structure containing type of communication and the required parameters, event_class.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get event data details for recv event class type.
********************************************************************************************************/
int32_t get_event_class_data(meter_comm_params_t *meter_comm_params, uint8_t event_class, uint8_t read_all_event_flag)
{
	static char fun_name[]="get_event_class_data()";
	
	uint8_t idx=0;
	uint8_t obis[6] = {0};
	uint8_t temp_nxt_blk_flag = 0;
	
	/* uint8_t comm_fd = meter_comm_params->fd;
	uint32_t dlms_met_addr = meter_comm_params->meter_id;
	uint8_t met_addr_size = meter_comm_params->meter_addr_format; */
	
	g_event_type_idx = event_class;

	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	g_get_nxt_blk_val=1;
	g_first_time_resp=1;
	
	GET_OBIS_OCTETS(EVENT_DATA_VAL_OBIS_STR,obis);
	obis[4] = event_class;
	
	if(get_num_event_entries(meter_comm_params,obis)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get event entry order for type : %d\n",fun_name,event_class);
		return -1;
	}
	
	if(g_max_num_event[g_event_type_idx]==0)
	{
		dbg_log(INFORM,"%-20s : No events available for this event type : %d\n",fun_name,event_class);
		all_events_data_value.events_type_info[idx].num_event = 0;
	
		return RET_SUCCESS;
	}
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = EVENT_VALUE_TYPE;
	dbg_log(INFORM,"%-20s : Sending QryType : EVENT_VALUE_TYPE for event type : %d\n",
	fun_name,event_class);

	if(send_get_event_request(meter_comm_params,EVENT_DATA_VAL_INT_CLASS, obis, 6, EVENT_DATA_VAL_ATTR_NO,read_all_event_flag)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get event value data info\n",fun_name);
		return -1;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get event value rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get event value get next frame frame\n",fun_name);
				return -1;
			}
		}
	}

	if(fill_val_obis_det(EVENT_VALUE_TYPE)<0)
		return -1;
	
	//store_event_det_file(event_class);
	
	memcpy(meter_comm_params->meter_response,&g_event_val_info,sizeof(event_val_info_t));
	
	return all_events_data_value.events_type_info[event_class].num_event;
}

/**************************************************************************************************
*Function 					: get_event_obis_code_det()
*Input Parameters 			: comm_fd,meter_address,meter_addr_size,event_param_details.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get obis code details for event.
********************************************************************************************************/
int8_t get_event_obis_code_det(meter_comm_params_t *meter_comm_params,gen_params_det_t*recv_gen_ls_param_det)
{
	static char fun_name[]="get_event_obis_code_det()";
	uint8_t val_obis[6] = {0};

	GET_OBIS_OCTETS(EVENT_VAL_OBIS_STR,val_obis);
	dbg_log(INFORM,"%-20s : Sending QryType : EVENT_VALUE_OBIS_TYPE\n",fun_name);
	if(get_gen_val_obis(meter_comm_params, EVENT_VALUE_OBIS_TYPE,EVENT_VAL_INT_CLASS,val_obis,6,EVENT_VAL_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get event val obis code\n",fun_name);
		return RET_VAL_OBIS_EVENT_FAIL;
	}
	
	 /* val_obis[0] = 1;
	 val_obis[1] = 0;
	 val_obis[2] = 94;
	 val_obis[3] = 91;
	 val_obis[4] = 7;
	 val_obis[5] = 255;
	 
	 int_class=0x0007, attr_no=0x0003; */
	
	GET_OBIS_OCTETS(EVENT_SCALAR_OBIS_STR,val_obis);
	
	dbg_log(INFORM,"%-20s : Sending QryType : EVENT_SCALER_OBIS_TYPE\n",fun_name);
	if(get_gen_scalar_obis(meter_comm_params, EVENT_SCALER_OBIS_TYPE,EVENT_SCALAR_INT_CLASS,val_obis,6,EVENT_SCALAR_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get event scalar obis code\n",fun_name);
		return RET_VAL_OBIS_LS_FAIL;
	}
	
	/* val_obis[0] = 1;
	val_obis[1] = 0;
	val_obis[2] = 94;
	val_obis[3] = 91;
	val_obis[4] = 7;
	val_obis[5] = 255;
	 
	int_class=0x0007, attr_no=0x0002; */
	
	GET_OBIS_OCTETS(EVENT_SCALAR_VAL_OBIS_STR,val_obis);
	
	dbg_log(INFORM,"%-20s : Sending QryType : EVENT_SCALER_VALUE_TYPE\n",fun_name);
	if(get_gen_scalar_val(meter_comm_params, EVENT_SCALER_VALUE_TYPE,EVENT_SCALAR_VAL_INT_CLASS,val_obis,6,EVENT_SCALAR_VAL_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get event scalar value\n",fun_name);
		return RET_VAL_OBIS_LS_FAIL;
	}
	
	return RET_SUCCESS;
}

/* Ls Related */
/**************************************************************************************************
*Function 					: get_ls_obis_code_det()
*Input Parameters 			: comm_fd,meter_address,meter_addr_size,load_survey_param_details.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get obis code details for load survey.
********************************************************************************************************/
int8_t get_ls_obis_code_det(meter_comm_params_t *meter_comm_params,gen_params_det_t*recv_gen_ls_param_det)
{
	if(get_int_blk_period(meter_comm_params)<0)
		return RET_VAL_OBIS_LS_FAIL;
	
	static char fun_name[]="get_ls_obis_code_det()";
	uint8_t val_obis[6] = {0};
	
	GET_OBIS_OCTETS(LS_VAL_OBIS_STR,val_obis);
	
	dbg_log(INFORM,"%-20s : Sending QryType : BLOCK_VAL_OBIS_TYPE\n",fun_name);
	if(get_gen_val_obis(meter_comm_params, BLOCK_VAL_OBIS_TYPE,LS_VAL_INT_CLASS,val_obis,6,LS_VAL_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_LS_FAIL;
	}
	
	 /* val_obis[0] = 1;
	 val_obis[1] = 0;
	 val_obis[2] = 94;
	 val_obis[3] = 91;
	 val_obis[4] = 4;
	 val_obis[5] = 255;
	 
	 int_class=0x0007, attr_no=0x0003; */
	
	GET_OBIS_OCTETS(LS_SCALAR_OBIS_STR,val_obis);
	
	dbg_log(INFORM,"%-20s : Sending QryType : BLOCK_SCALER_OBIS_TYPE\n",fun_name);
	if(get_gen_scalar_obis(meter_comm_params, BLOCK_SCALER_OBIS_TYPE,LS_SCALAR_INT_CLASS,val_obis,6,LS_SCALAR_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_LS_FAIL;
	}
	
	/* val_obis[0] = 1;
	val_obis[1] = 0;
	val_obis[2] = 94;
	val_obis[3] = 91;
	val_obis[4] = 4;
	val_obis[5] = 255;
	 
	int_class=0x0007, attr_no=0x0002; */
	
	GET_OBIS_OCTETS(LS_SCALAR_VAL_STR,val_obis);
	
	dbg_log(INFORM,"%-20s : Sending QryType : BLOCK_SCALER_VALUE_TYPE\n",fun_name);
	if(get_gen_scalar_val(meter_comm_params, BLOCK_SCALER_VALUE_TYPE,LS_SCALAR_VAL_INT_CLASS,val_obis,6,LS_SCALAR_VAL_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_LS_FAIL;
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: read_ls_data()
*Input Parameters 			: comm_fd,meter_address,meter_addr_size.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To read load survey data.
********************************************************************************************************/
int32_t read_ls_data(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="read_ls_data()";
	
	uint8_t obis[6] = {0};
	uint8_t temp_nxt_blk_flag = 0;
	
	g_get_nxt_blk_val=1;
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	
	memset(gen_data_val_info,0,sizeof(gen_data_val_info));
	
	g_first_time_resp=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	
	GET_OBIS_OCTETS(LS_DATA_VAL_OBIS_STR,obis);
	g_query_type = BLOCK_VALUES_TYPE;
	dbg_log(INFORM,"%-20s : Sending QryType : BLOCK_VALUES_TYPE\n",fun_name);
	
	if(send_blk_profile_request(meter_comm_params, LS_DATA_VAL_INT_CLASS, obis, 6, LS_DATA_VAL_ATTR_NO)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get load survey data\n",fun_name);
		return -1;
	}
	else if(g_no_ls_data_avl_flag==1)
	{
		dbg_log(REPORT,"%-20s : No block data available for this date time stamp\n",fun_name);
		return -1;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst scaler value rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			//if(send_get_next_blk(midx, g_get_nxt_blk_val)<0)
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_val)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst scaler value next block frame\n",fun_name);
				return -1;
			}
			temp_nxt_blk_flag=0;
			g_get_nxt_blk_val=g_get_nxt_blk_val+1;
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: recv_ls_blk_range_data()
*Input Parameters 			: Structure containing type of communication and the required parameters, last_num_blk_read.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get load survey data for last recv number of blocks.
********************************************************************************************************/
int32_t recv_ls_blk_range_data(meter_comm_params_t *meter_comm_params, date_time_t st_date_time, date_time_t end_date_time)
{
	static char fun_name[]="recv_ls_blk_range_data()";
	
	/* uint8_t comm_fd = meter_comm_params->fd;
	uint32_t dlms_met_addr = meter_comm_params->meter_id;
	uint8_t met_addr_size = meter_comm_params->meter_addr_format; */
		
	memset(&g_st_date_time,0,sizeof(date_time_t));
	memset(&g_end_date_time,0,sizeof(date_time_t));
	
	memcpy(&g_st_date_time,&st_date_time,sizeof(date_time_t));
	memcpy(&g_end_date_time,&end_date_time,sizeof(date_time_t));
	
	dbg_log(INFORM,"%-20s : Getting  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
	g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
	g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
	
	dbg_log(INFORM,"%-20s : Getting  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
	g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
	g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
	
	if(read_ls_data(meter_comm_params)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get ls data for date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
		g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
		
		return -1;
	}
	else
	{
		dbg_log(INFORM,"%-20s : Received  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
		g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
		
		dbg_log(INFORM,"%-20s : Received  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
		g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
	}
	
	meter_comm_params->resp_len=sizeof(block_val_info_t);
	memcpy(&meter_comm_params->meter_response, &g_block_val_info, sizeof(block_val_info_t));
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: recv_ls_hour_range_data()
*Input Parameters 			: Structure containing type of communication and the required parameters, last_num_hour_read.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get load survey data for last recv number of hour.
********************************************************************************************************/
int32_t recv_ls_hour_range_data(meter_comm_params_t *meter_comm_params,date_time_t st_date_time, date_time_t end_date_time)
{
	static char fun_name[]="recv_ls_hour_range_data()";
	
	/* uint8_t comm_fd = meter_comm_params->fd;
	uint32_t dlms_met_addr = meter_comm_params->meter_id;
	uint8_t met_addr_size = meter_comm_params->meter_addr_format; */
		
	memset(&g_st_date_time,0,sizeof(date_time_t));
	memset(&g_end_date_time,0,sizeof(date_time_t));
	
	memcpy(&g_st_date_time,&st_date_time,sizeof(date_time_t));
	memcpy(&g_end_date_time,&end_date_time,sizeof(date_time_t));
	
	dbg_log(INFORM,"%-20s : Getting  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
	g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
	g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
	
	dbg_log(INFORM,"%-20s : Getting  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
	g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
	g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
	
	if(read_ls_data(meter_comm_params)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get ls data for date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
		g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
		
		return -1;
	}
	else
	{
		dbg_log(INFORM,"%-20s : Received  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
		g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
		
		dbg_log(INFORM,"%-20s : Received  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
		g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
	}

	printf("Sending Resp Len : %d\n",meter_comm_params->resp_len);
	
	meter_comm_params->resp_len=sizeof(g_block_val_info);
	
	memcpy(&meter_comm_params->meter_response, &g_block_val_info, sizeof(block_val_info_t));
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: check_ls_file_avl()
*Input Parameters 			: Meter Idx, Ls File Name.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To check complete load survey data file.
********************************************************************************************************/
int32_t check_ls_file_avl(char* file_name)
{
	static char fun_name[]="check_ls_file_avl()";
	char 	read_line[256];
	uint8_t	line_cnt = 0;
	char 	time_entry[32];
	FILE	*p_file_ptr = NULL;
	
	memset(time_entry,0,32);
	
	if(g_meter_mfg_type==LNT_METER_MFG_TYPE)
	{
		sprintf(time_entry,"%02d:%02d",24,00);		
	}
	else
	{
		sprintf(time_entry,"%02d:%02d",23,(60-g_int_period_blk));
	}
	
	p_file_ptr = fopen(file_name,"r");
	if(p_file_ptr == NULL)
	{
		dbg_log(REPORT,"%-20s : File : %s is not opened Read mode, Error : %s\n",fun_name,file_name,strerror(errno));
		return -1;
	}
	else
	{
		while(fgets(read_line,256,p_file_ptr)!=NULL)
		{
			line_cnt++;
			
			if ( strstr(read_line, time_entry) != NULL )
			{
				if(line_cnt>=(g_num_blocks_blk_data+1))
				{
					dbg_log(INFORM,"%-20s : ::: file_name : %s Time entry : %s found \n",fun_name,file_name,time_entry);
					
					fclose(p_file_ptr);
					
					return 1;
				}
				else
				{
					fclose(p_file_ptr);
					
					remove(file_name);
					
					return 0;
				}
			}
			memset(read_line,0,256);
		}
	}
	
	fclose(p_file_ptr);
	
	dbg_log(INFORM,"%-20s : ::: file_name : %s Time entry : %s Not found Deleting file\n",
	fun_name,file_name,time_entry);
	
	remove(file_name);
	
	return 0;
}

/**************************************************************************************************
*Function 					: recv_ls_day_range_data()
*Input Parameters 			: Structure containing type of communication and the required parameters, last_num_days_read.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get load survey data for last recv number of days.
********************************************************************************************************/
int32_t recv_ls_day_range_data(meter_comm_params_t *meter_comm_params,uint8_t last_num_days_read)
{
	static char fun_name[]="recv_ls_day_range_data()";
	struct tm st_time,time_stamp,next_date_tm;
	time_t time_of_day=0,next_time_day=0;
	uint8_t idx=0;
	
	/* uint8_t comm_fd = meter_comm_params->fd;
	uint32_t dlms_met_addr = meter_comm_params->meter_id;
	uint8_t met_addr_size = meter_comm_params->meter_addr_format; */
	
	#if 0
	if(get_curr_date_time(meter_comm_params)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get Meter curr date time\n",fun_name); 
		return -1;
	}
	
	memset(&g_st_date_time,0,sizeof(g_st_date_time));
	memset(&g_end_date_time,0,sizeof(g_end_date_time));
	
	st_time.tm_mday = meter_date_time.day;
	st_time.tm_mon =  meter_date_time.month - 1;
	st_time.tm_year = meter_date_time.year - 1900;
	st_time.tm_hour = 0;
	st_time.tm_min = 0;
	st_time.tm_sec = 0;
	
	time_of_day = mktime(&st_time);
	//time_of_day -= (last_num_days_read*60*60);
	time_of_day -= (24*60*60);
	localtime_r(&time_of_day,&time_stamp);
	
	for(idx=0; idx<last_num_days_read; idx++)
	{
		memset(&g_st_date_time,0,sizeof(date_time_t));
		memset(&g_end_date_time,0,sizeof(date_time_t));
		
		localtime_r(&time_of_day,&time_stamp);
			
		next_time_day =  time_of_day + 60*60*24;
		localtime_r(&next_time_day,&next_date_tm);
		
		if(g_meter_mfg_type==LNT_METER_MFG_TYPE)
		{
			g_st_date_time.day = time_stamp.tm_mday;
			g_st_date_time.month = time_stamp.tm_mon+1;
			g_st_date_time.year = time_stamp.tm_year+1900;
			g_st_date_time.hour = 0;
			g_st_date_time.minute = 4;
			g_st_date_time.second = 0;
			
			g_end_date_time.day = next_date_tm.tm_mday;
			g_end_date_time.month = next_date_tm.tm_mon+1;
			g_end_date_time.year = next_date_tm.tm_year+1900;
			g_end_date_time.hour = 0;
			g_end_date_time.minute = 3;
			g_end_date_time.second = 0;
		}
		else
		{
			g_st_date_time.day = time_stamp.tm_mday;
			g_st_date_time.month = time_stamp.tm_mon+1;
			g_st_date_time.year = time_stamp.tm_year+1900;
			g_st_date_time.hour = 0;
			g_st_date_time.minute = 0;
			g_st_date_time.second = 0;
			
			g_end_date_time.day = time_stamp.tm_mday;
			g_end_date_time.month = time_stamp.tm_mon+1;
			g_end_date_time.year = time_stamp.tm_year+1900;
			g_end_date_time.hour = 23;
			g_end_date_time.minute = 59;
			g_end_date_time.second = 0;
		}
		
		char time_str[64];
		memset(time_str,0,sizeof(time_str));
		sprintf(time_str,"%s/%02d_%02d_%04d",meter_comm_params->filename,g_st_date_time.day,g_st_date_time.month,g_st_date_time.year);
		
		if(check_ls_file_avl(time_str)==1)
		{
			dbg_log(INFORM,"%-20s : Already available ls data for date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
			g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
			g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
			
			/* time_of_day = time_of_day+(60*60*24); */
			time_of_day = time_of_day-(60*60*24);
			
			continue;
		}
		
		dbg_log(INFORM,"%-20s : Getting  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
		g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
		
		dbg_log(INFORM,"%-20s : Getting  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
		g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
		
		if(read_ls_data(meter_comm_params)<0)
		{
			if(g_no_ls_data_avl_flag==1)
			{
				dbg_log(REPORT,"%-20s : No Load survey data available for this date: %02d_%02d_%04d",
				fun_name,g_st_date_time.day,g_st_date_time.month,g_st_date_time.year);
			}
			else
			{
				dbg_log(REPORT,"%-20s : failed to get ls data for date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
				g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
				g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
				
				time_of_day = time_of_day-(60*60*24);
				continue;
			}
		}
		else
		{
			dbg_log(INFORM,"%-20s : Received  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
			g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
			g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
			
			dbg_log(INFORM,"%-20s : Received  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
			g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
			g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
			
			int32_t fun_ret=0;
			char curr_ls_file_name[64];
			struct stat dir_st;
			
			memset(curr_ls_file_name,0,sizeof(curr_ls_file_name));
			sprintf(curr_ls_file_name,"%s/%02d_%02d_%04d",meter_comm_params->filename,g_st_date_time.day,g_st_date_time.month,g_st_date_time.year);
			
			if (stat(curr_ls_file_name, &dir_st) == -1) 
			{
				;
			}
			else
			{
				fun_ret = search_time_entry(curr_ls_file_name,"24:00");
				if(fun_ret==1)
				{
					dbg_log(INFORM,"%-20s : LoadSurvey data Entry 24:00 Found In file : %s\n",fun_name,curr_ls_file_name);
					time_of_day = time_of_day-(60*60*24);
					
					continue;
				}
				
				FILE *p_ls_file_ptr=NULL;
				
				p_ls_file_ptr = fopen(curr_ls_file_name,"a");
				if(p_ls_file_ptr == NULL)
				{
					dbg_log(REPORT,"%-20s : File is not opened Append mode, Error : %s\n",fun_name,strerror(errno));
					time_of_day = time_of_day-(60*60*24);
					
					continue;
				}
				
				dbg_log(INFORM,"%-20s Adding 24:00 Entry in file : %s\n",fun_name,curr_ls_file_name);
				
				fprintf(p_ls_file_ptr,"%s",g_last_entry_buff);
				
				fflush(p_ls_file_ptr);
				
				fclose(p_ls_file_ptr);
			}	
		}
		
		time_of_day = time_of_day-(60*60*24);
	}
	
	#endif
	
	g_st_date_time.day = meter_comm_params->from.day;
	g_st_date_time.month = meter_comm_params->from.month;
	g_st_date_time.year = meter_comm_params->from.year;
	g_st_date_time.hour = meter_comm_params->from.hour;
	g_st_date_time.minute = meter_comm_params->from.minute;
	g_st_date_time.second = meter_comm_params->from.second;
		
	g_end_date_time.day = meter_comm_params->to.day;
	g_end_date_time.month = meter_comm_params->to.month;
	g_end_date_time.year = meter_comm_params->to.year;
	g_end_date_time.hour = meter_comm_params->to.hour;
	g_end_date_time.minute = meter_comm_params->to.minute;
	g_end_date_time.second = meter_comm_params->to.second;
	
	dbg_log(INFORM,"%-20s : Getting  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
	g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
	g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
	
	dbg_log(INFORM,"%-20s : Getting  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
	g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
	g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
	
	if(read_ls_data(meter_comm_params)<0)
	{
		if(g_no_ls_data_avl_flag==1)
		{
			dbg_log(REPORT,"%-20s : No Load survey data available for this date: %02d_%02d_%04d",
			fun_name,g_st_date_time.day,g_st_date_time.month,g_st_date_time.year);
		}
		else
		{
			dbg_log(REPORT,"%-20s : failed to get ls data for date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
			g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
			g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
			
			return RET_NO_RESP;
		}
	}
	else
	{
		dbg_log(INFORM,"%-20s : Received  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
		g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
		
		dbg_log(INFORM,"%-20s : Received  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
		g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
	}
		
	meter_comm_params->resp_len=sizeof(g_block_val_info);
	
	memcpy(&meter_comm_params->meter_response, &g_block_val_info, sizeof(block_val_info_t));
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_int_blk_period()
*Input Parameters 			: comm_fd,meter_address,meter_addr_size.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get block interval period for load survey data.
********************************************************************************************************/
int32_t get_int_blk_period(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="get_int_blk_period()";
	uint8_t obis[6] = {0};
	uint8_t temp_nxt_blk_flag = 0;
	
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	g_get_nxt_blk_val=1;
	g_raw_data_idx = 0;
	g_first_time_resp=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_query_type = BLOCK_INT_PERIOD_TYPE;
	dbg_log(INFORM,"%-20s : Sending QryType : BLOCK_INT_PERIOD_TYPE\n",fun_name);
	
	GET_OBIS_OCTETS(LS_BLK_INT_PER_OBIS_STR,obis);
	
	if(send_get_request(meter_comm_params, LS_BLK_INT_PER_INT_CLASS, obis, 6, LS_BLK_INT_PER_ATTR_NO)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get block interval period info\n",fun_name);
		return -1;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get load survey val obis rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			//if(send_get_next_blk(midx, g_get_nxt_blk_val)<0)
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get block interval period get next frame frame\n",fun_name);
				return -1;
			}
			temp_nxt_blk_flag = 0;
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_ls_val_obis()
*Input Parameters 			: buffer and buffer length.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process val obis for load survey data.
********************************************************************************************************/
int32_t proc_ls_val_obis(uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_ls_val_obis()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_ls_param_det.tot_num_val_obis = msg[loc_idx-1];

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen in Getnext block\n",fun_name);
				
				return -1;
			}
			
			/* loc_idx=21+OFFSET; */
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_ls_scalar_obis()
*Input Parameters 			: buffer and buffer length.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process scalar obis for load survey data.
********************************************************************************************************/
int32_t proc_ls_scalar_obis( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_ls_scalar_obis()";
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
		
		/* loc_idx=17+OFFSET; */

		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_ls_param_det.tot_num_scalar = msg[loc_idx-1];

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
			/* loc_idx=21+OFFSET; */
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_ls_scalar_val()
*Input Parameters 			: buffer and buffer length.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process scalar value for load survey data.
********************************************************************************************************/
int32_t proc_ls_scalar_val( uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_ls_scalar_val()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0f))
			{
				loc_idx = idx;
				break;
			}
		}
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
		
		/* loc_idx=19+OFFSET; */

		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0f))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
			
				/* loc_idx=21+OFFSET; */
			}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s :  Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_ls_value()
*Input Parameters 			: buffer and buffer length.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process value for load survey data.
********************************************************************************************************/
int32_t proc_ls_value(uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_ls_value()";
	uint32_t loc_idx=0,idx=0;
	uint32_t index =0;
	uint8_t ls_index =0, data_type = 0;
		
	if((msg[12+OFFSET]==0X01) && (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X01))
	{
		dbg_log(INFORM,"%-20s : no LS data available for this date qry.\n",fun_name);
		return 1;
	}
	
	if(g_first_time_resp == 1)
	{
		for(index=0; index<len; index++)
		{
			//if(((msg[idx]==0X02)&&(msg[idx+2]==0X09)&&(msg[idx+3]==0X0C)) || (((msg[idx]==0X02)&&((msg[idx+2]==0X06)||(msg[idx+2]==0X05)))))
			if((msg[index] == 0X02) && ((msg[index+2] == 0X09)) && ((msg[index+3] == 0X0C)))
			{
				loc_idx = index;
				g_num_ls_param = msg[index+1];
				gen_ls_param_det.tot_num_value =g_num_ls_param;
				break;
			}
		}
		
		if(index == len)
		{
			dbg_log(REPORT,"%-20s : No start stamp seen.\n",fun_name);
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : Numof ls block : %d, First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		g_first_time_resp=0;
		
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk || g_comp_blk_resp)
		{
			for(index=0; index<len; index++)
			{
				//if(((msg[idx]==0X02)&&(msg[idx+2]==0X09)&&(msg[idx+3]==0X0C)) || (((msg[idx]==0X02)&&((msg[idx+2]==0X06)||(msg[idx+2]==0X05)))))
				if((msg[index] == 0X02) && ((msg[index+2] == 0X09)) && ((msg[index+3] == 0X0C)))
				{
					loc_idx = index;
					g_num_ls_param = msg[index+1];
					gen_ls_param_det.tot_num_value =g_num_ls_param;
					break;
				}
			}
			
			if(index == len)
			{
				dbg_log(REPORT,"%-20s : No start stamp seen.\n",fun_name);
				return -1;
			}
				/* loc_idx=23+OFFSET; */
			}
		else
			goto EXIT;
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	if(g_ls_decode_flag == 1)
	{
		dbg_log(INFORM,"%-20s : g_num_ls_param : %d g_raw_data_idx : %d\n",fun_name,g_num_ls_param,g_raw_data_idx);
	
		index = 0;
		
		while(1)
		{
			if(index>=g_raw_data_idx)
			{
				break;
			}
			
			index =index+2;
			//printf("Before decode index : %d Value : %X\n",index,g_raw_data_buff[index]);
			
			for(idx=0; idx<g_num_ls_param; idx++)
			{
				data_type = g_raw_data_buff[index++];
				gen_data_val_info[idx].data_type = data_type;
				
				switch(data_type)
				{
					case FLOAT_32BIT_TYPE:
					case UNSIGNED_32BIT_TYPE:
					case SIGNED_32BIT_TYPE:
						gen_data_val_info[idx].num_bytes = 4;
						memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],4);
						index+=4;
					break;
					
					case UNSIGNED_16BIT_TYPE:
					case SIGNED_16BIT_TYPE:
						gen_data_val_info[idx].num_bytes = 2;
						memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],2);
						index+=2;
					break;
					
					case UNSIGNED_8BIT_TYPE:
						gen_data_val_info[idx].num_bytes = 1;
						memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index],1);
						index+=1;
					break;
					
					case OCTET_STRING_TYPE:
						//printf("ls_index : %d Before Date time decode index : %d\n",ls_index,index);
						gen_data_val_info[idx].num_bytes = g_raw_data_buff[index];
						memcpy(gen_data_val_info[idx].value,&g_raw_data_buff[index+1],gen_data_val_info[idx].num_bytes);
						index+=(gen_data_val_info[idx].num_bytes+1);
					break;
					
					default : break;
				}
			}
			
			if(fill_ls_val(ls_index)<0)
			{
				dbg_log(REPORT,"%-20s : Failed to filled for ls index : %d\n",fun_name,ls_index);
					continue;
			}
		}
		g_raw_data_idx = 0;
	}
	
	EXIT :
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: send_blk_profile_request()
*Input Parameters 			: comm_fd,meter_address,meter_addr_size,qry_type,inf_class,obis_code,obis_code_len,attr_num.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get block profile details.
********************************************************************************************************/
int32_t send_blk_profile_request( meter_comm_params_t *meter_comm_params,uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
{
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0,ctrl_field=0;
	uint16_t		fcs=0, frm_format = 0;
	int32_t			send_fun_ret = -1;
	
	uint8_t 		loc_temp_byte[32]={0x02,0x01,0x01,0x02,0x04,
										0x02,0x04,0x12,0x00,0x08,
										0x09,0x06,0x00,0x00,0x01,
										0x00,0x00,0xFF,0x0F,0x02,
										0x12,0x00,0x00,0x09,0x0c};
										
	memset(g_send_buff,0,sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;

	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;

		case 2:
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		case 4:
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((((meter_comm_params->meter_id)>>7)<<1)&0XFF);
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		default:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;
	}

	g_send_buff[idx++] = g_src_addr;
	
	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num << 1 );
	g_send_seq_num = ( g_send_seq_num + 1 ) % 8;

	ctrl_field |= ( g_recv_seq_num << 5 );
	
	g_send_buff[idx++] = ctrl_field;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;
	
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0x00;

	g_send_buff[idx++] = (GET_REQUEST_NORMAL >> 8) & 0x00FF;;
	g_send_buff[idx++] = GET_REQUEST_NORMAL & 0x00FF;;

	g_send_buff[idx++] = 0x81;

	p_gen_ptr = (uint8_t*)&int_class;
	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];

	memcpy(&g_send_buff[idx],obis_code,obis_len);
	idx = idx +obis_len;
	
	uint8_t loc_idx =0;
	
	for(loc_idx =0; loc_idx<25;loc_idx++)
		g_send_buff[idx++] =loc_temp_byte[loc_idx];

	//st_date
	g_send_buff[idx++] = g_st_date_time.year>>8;
	g_send_buff[idx++] = g_st_date_time.year&0X00FF;
	g_send_buff[idx++] = g_st_date_time.month;
	g_send_buff[idx++] = g_st_date_time.day;
	g_send_buff[idx++] = 0xFF;
	g_send_buff[idx++] = g_st_date_time.hour;
	g_send_buff[idx++] = g_st_date_time.minute;
	g_send_buff[idx++] = g_st_date_time.second;
	
	g_send_buff[idx++] = 0xFF;
	g_send_buff[idx++] = 0x80;
	g_send_buff[idx++] = 0x00;
	g_send_buff[idx++] = 0xFF;
	
	//end_date
	g_send_buff[idx++] = 0x09;
	g_send_buff[idx++] = 0x0C;
	g_send_buff[idx++] = g_end_date_time.year>>8;
	g_send_buff[idx++] = g_end_date_time.year&0X00FF;
	g_send_buff[idx++] = g_end_date_time.month;
	g_send_buff[idx++] = g_end_date_time.day;
	g_send_buff[idx++] = 0xFF;
	g_send_buff[idx++] = g_end_date_time.hour;
	g_send_buff[idx++] = g_end_date_time.minute;
	g_send_buff[idx++] = g_end_date_time.second;
	
	g_send_buff[idx++] = 0xFF;
	g_send_buff[idx++] = 0x80;
	g_send_buff[idx++] = 0x00;
	g_send_buff[idx++] = 0xFF;
	
	p_gen_ptr = (uint8_t*)&attr_no;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	frm_format = FRAME_FORMAT_TYPE | (idx+1);
	p_gen_ptr = (uint8_t*)&frm_format;
	
	g_send_buff[1] = p_gen_ptr[1];
	g_send_buff[2] = p_gen_ptr[0];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], 5+OFFSET);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[6+OFFSET] = p_gen_ptr[0];
	g_send_buff[7+OFFSET] = p_gen_ptr[1];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	send_fun_ret = send_msg_meter(meter_comm_params, g_send_buff, idx);
	
	return send_fun_ret;
}

/**************************************************************************************************
*Function 					: fill_ls_val()
*Input Parameters 			: ls_index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To fill load survey value in appropriate structure.
********************************************************************************************************/
int32_t fill_ls_val( uint8_t recv_ls_idx)
{
	static char fun_name[]="fill_ls_val()";

	uint8_t 	idx=0;
	int8_t 		*p_tmp_str=NULL;
	float 		flt_val = 0.0,scal_flt_val=0.0;
	uint8_t		uint8_temp_val=0;
	int16_t		int16_temp_val=0;
	uint16_t	uint16_temp_val=0;
	int32_t		int32_temp_val=0;
	uint32_t	uint32_temp_val=0;
	float 		float_temp_val = 0.0;
	
	//printf("num_ls_param : %d ::: Filling LS data for ls index : %d\n",g_num_ls_param,recv_ls_idx);
	
	g_all_ls_param_obis_val.tot_num_params=gen_ls_param_det.tot_num_value;
	
	for(idx=0;idx<g_num_ls_param;idx++)
	{
		switch(gen_data_val_info[idx].data_type)
		{
			case	FLOAT_32BIT_TYPE:
				p_tmp_str=(int8_t*)&float_temp_val;
				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_ls_param_det.scalar_val[idx].value,&scal_flt_val);
				
				flt_val = (float)((float)float_temp_val * scal_flt_val);
				if(store_ls_val( recv_ls_idx, idx, flt_val) < 0)
					continue;
			break;
			
			case UNSIGNED_32BIT_TYPE:
			case SIGNED_32BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					p_tmp_str=(int8_t*)&uint32_temp_val;
				else
					p_tmp_str=(int8_t*)&int32_temp_val;

				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_ls_param_det.scalar_val[idx].value,&scal_flt_val);
/* 				printf(":::::::::recv_ls_idx : %d Idx : %d ScalarVal : %d scal_flt_val : %f\n",
				recv_ls_idx,idx,gen_ls_param_det.scalar_val[idx].value,scal_flt_val); */
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					flt_val = (float)((float)uint32_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int32_temp_val * scal_flt_val);
				
				if(store_ls_val( recv_ls_idx, idx, flt_val) < 0)
					continue;
	
			break;
			
			case UNSIGNED_16BIT_TYPE:
			case SIGNED_16BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					p_tmp_str=(int8_t*)&uint16_temp_val;
				else
					p_tmp_str=(int8_t*)&int16_temp_val;

				p_tmp_str[1] = gen_data_val_info[idx].value[0];
				p_tmp_str[0] = gen_data_val_info[idx].value[1];
				
				get_scaler_mf(gen_ls_param_det.scalar_val[idx].value,&scal_flt_val);
				
				/* printf("16BIT_TYPE :::::recv_ls_idx : %d Idx : %d ScalarVal : %d scal_flt_val : %f\n",
				recv_ls_idx,idx,gen_ls_param_det.scalar_val[idx].value,scal_flt_val); */
				
				/* printf("p_tmp_str[0] : %X, p_tmp_str[1] : %X p_tmp_str[2] : %X, p_tmp_str[3] : %X\n",
									gen_data_val_info[idx].value[0],
									gen_data_val_info[idx].value[1],
									gen_data_val_info[idx].value[2],
									gen_data_val_info[idx].value[3]); */
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					flt_val = (float)((float)uint16_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int16_temp_val * scal_flt_val);
				
				if(store_ls_val( recv_ls_idx, idx, flt_val) < 0)
					continue;

			break;
			
			case UNSIGNED_8BIT_TYPE:
				p_tmp_str=(int8_t*)&uint8_temp_val;
				p_tmp_str[0] = gen_data_val_info[idx].value[0];
				get_scaler_mf(gen_ls_param_det.scalar_val[idx].value,&scal_flt_val);
				flt_val = (float)((float)uint8_temp_val * scal_flt_val);
				
				if(store_ls_val( recv_ls_idx, idx, flt_val) < 0)
					continue;
				
			break;
			
			case OCTET_STRING_TYPE:
				if(store_ls_date_time( recv_ls_idx, idx)<0)
					continue;

			break;
			
			default : break;
		}
	}
	
	save_ls_data_file();
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: search_time_entry()
*Input Parameters 			: file path and time string.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To search time entry available in a given file.
********************************************************************************************************/
int32_t search_time_entry( char* filepath, char* time_entry)
{
	char *p_file_read = NULL;
	struct stat st;
	int32_t		file_fd=0;
	
	if(stat(filepath,&st)==-1)
	{
		return -1;
	}
	else
	{
		file_fd = open(filepath, O_RDONLY);
		if (file_fd == -1) 
		{
			printf("can't open file - %s", filepath);
			return -1;
		}

		p_file_read = (char*)malloc(st.st_size+1);
		if (st.st_size!=read(file_fd, p_file_read, st.st_size)) 
		{
			printf("can't read file - %s", filepath);
			close(file_fd);
			free(p_file_read);
			return -1;
		}
		
		close(file_fd);
		
		p_file_read[st.st_size]='\0';
		
		if ( strstr(p_file_read,time_entry) != NULL )
		{
			dbg_log(INFORM,"search_time_entry  ::: file_name : %s Time entry : %s found \n",filepath,time_entry);
			free(p_file_read);
			return 1;
		}
	}
	
	free(p_file_read);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: save_ls_data_file()
*Input Parameters 			: None.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To save load survey data into configured file location.
********************************************************************************************************/
int32_t save_ls_data_file(void)
{
	static char fun_name[]="save_ls_data_file()";
	uint8_t		idx = 0;
	FILE *p_ls_file_ptr=NULL;
	date_time_t date_time;
	char obis_buff[32],value_buff[32];
	struct stat st;
	char 		curr_ls_file_name[64],time_str[32];
	uint8_t		fun_ret = 0, avl_file=0;
	float 		flt_val=0.0;
	
	memset(&date_time,0,sizeof(date_time));
	memcpy(&date_time,&g_all_ls_param_obis_val.param_obis_val_info[0].value,sizeof(date_time_t));
	
	//sprintf(curr_ls_file_name,"%02d:%02d",date_time.hour,date_time.minute);

	memset(curr_ls_file_name,0,sizeof(curr_ls_file_name));
	sprintf(curr_ls_file_name,"%s/%02d_%02d_%04d",g_ls_data_dir_path,date_time.day,date_time.month,date_time.year);
	if(date_time.day==0)
	{
		dbg_log(REPORT,"%-20s : Day value can't be Zero.\n",fun_name);
		return -1;
	}
	
	if(stat(curr_ls_file_name,&st)==-1)
	{
		avl_file = 0;
	}
	else
	{
		avl_file = 1;
	}
	
	memset(time_str,0,sizeof(time_str));
	sprintf(time_str,"%02d:%02d",date_time.hour,date_time.minute);
	
	fun_ret = search_time_entry(curr_ls_file_name,time_str);
	if(fun_ret == 1)
	{
		return RET_SUCCESS;
	}
	
	if(avl_file == 0)
	{
		p_ls_file_ptr = fopen(curr_ls_file_name,"w");
		if(p_ls_file_ptr == NULL)
		{
			dbg_log(REPORT,"%-20s : File is not opened write mode, Error : %s\n",fun_name,strerror(errno));
			return -1;
		}
		
		dbg_log(INFORM,"%-20s : Adding Header for new file : %s\n",fun_name,curr_ls_file_name);
		for(idx=0; idx<g_all_ls_param_obis_val.tot_num_params; idx++)
		{
			memset(obis_buff,0,sizeof(obis_buff));
			sprintf(obis_buff,"%d.%d.%d.%d.%d.%d",
			g_all_ls_param_obis_val.param_obis_val_info[idx].obis_code[0],
			g_all_ls_param_obis_val.param_obis_val_info[idx].obis_code[1],
			g_all_ls_param_obis_val.param_obis_val_info[idx].obis_code[2],
			g_all_ls_param_obis_val.param_obis_val_info[idx].obis_code[3],
			g_all_ls_param_obis_val.param_obis_val_info[idx].obis_code[4],
			g_all_ls_param_obis_val.param_obis_val_info[idx].obis_code[5]
			);
			
			if(idx==g_all_ls_param_obis_val.tot_num_params-1)
				fprintf(p_ls_file_ptr,"%s\n",obis_buff);
			else
				fprintf(p_ls_file_ptr,"%s\t",obis_buff);
			
			fflush(p_ls_file_ptr);
		}
	}
	else
	{
		p_ls_file_ptr = fopen(curr_ls_file_name,"a");
		if(p_ls_file_ptr == NULL)
		{
			dbg_log(REPORT,"%-20s : File is not opened Append mode, Error : %s\n",fun_name,strerror(errno));
			return -1;
		}
	}
	
	dbg_log(REPORT,"%-20s : New time entry found need to store , %02d:%02d \n",fun_name,date_time.hour,date_time.minute);
	for(idx=0; idx<g_all_ls_param_obis_val.tot_num_params; idx++)
	{
		memset(value_buff,0,sizeof(obis_buff));
		switch(g_all_ls_param_obis_val.param_obis_val_info[idx].data_type)
		{
			case OCTET_STRING_TYPE:
			{
				memset(&date_time,0,sizeof(date_time));
				memcpy(&date_time,&g_all_ls_param_obis_val.param_obis_val_info[idx].value,sizeof(date_time_t));
				sprintf(value_buff,"%02d:%02d",date_time.hour,date_time.minute);
			}
			break;
			
			default:
			{
				memcpy(&flt_val,&g_all_ls_param_obis_val.param_obis_val_info[idx].value,4);
				sprintf(value_buff,"%0.5f",flt_val);
			}
			break;
		}
		
		if(idx==g_all_ls_param_obis_val.tot_num_params-1)
		{
			fprintf(p_ls_file_ptr,"%s\n",value_buff);
			printf("%s\n",value_buff);
		}
		else
		{
			fprintf(p_ls_file_ptr,"%s\t",value_buff);
			printf("%s\t",value_buff);
		}
		
		fflush(p_ls_file_ptr);
	}
	
	fclose(p_ls_file_ptr);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: store_ls_val()
*Input Parameters 			: ls_index, obis_index, value.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store load survey data in appropriate structure.
********************************************************************************************************/
int32_t store_ls_val( uint8_t ls_idx, uint8_t index, float recv_flt_val)
{
	uint8_t idx=0;

	memcpy(&g_all_ls_param_obis_val.param_obis_val_info[index].obis_code,gen_ls_param_det.val_obis[index],6);
	memcpy(&g_all_ls_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_ls_param_obis_val.param_obis_val_info[index].value,&recv_flt_val,4);
	
	return RET_SUCCESS;
		
	for(idx=0;idx<MAX_NUM_LS_PARAMS;idx++)
	{
		if( (memcmp(gen_ls_param_det.val_obis[index],g_ls_param_det[idx].obis_code,6)) == 0)
		{
			if( (memcmp(g_ls_param_det[idx].param_name,"cur_ir",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.cur_ir.param_obis_code,gen_ls_param_det.val_obis[index],6);
				memcpy(g_block_val_info.cur_ir.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.cur_ir.param_name,"%s","LS_CUR_IR");
				
				printf("Recv Curr_R det : val : %0.5f\n",recv_flt_val);
				print_data(g_block_val_info.cur_ir.param_obis_code,6);
			}
			
			else if( (memcmp(g_ls_param_det[idx].param_name,"cur_iy",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.cur_iy.param_obis_code,gen_ls_param_det.val_obis[index],6);
				memcpy(g_block_val_info.cur_iy.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.cur_iy.param_name,"%s","LS_CUR_IY");
			}
			else if( (memcmp(g_ls_param_det[idx].param_name,"cur_ib",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.cur_ib.param_obis_code,gen_ls_param_det.val_obis[index],6);
				memcpy(g_block_val_info.cur_ib.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.cur_ib.param_name,"%s","LS_CUR_IB");
			}
			else if( (memcmp(g_ls_param_det[idx].param_name,"volt_r",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.volt_r.param_obis_code,gen_ls_param_det.val_obis[index],6);
				memcpy(g_block_val_info.volt_r.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.volt_r.param_name,"%s","LS_VOLT_R");
			}
			else if( (memcmp(g_ls_param_det[idx].param_name,"volt_y",strlen(g_ls_param_det[idx].param_name))) == 0)
				{
				memcpy(g_block_val_info.volt_y.param_obis_code,gen_ls_param_det.val_obis[index],6);
				memcpy(g_block_val_info.volt_y.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.volt_y.param_name,"%s","LS_VOLT_Y");
			}
			else if( (memcmp(g_ls_param_det[idx].param_name,"volt_b",strlen(g_ls_param_det[idx].param_name))) == 0)
				{
				memcpy(g_block_val_info.volt_b.param_obis_code,gen_ls_param_det.val_obis[index],6);
				memcpy(g_block_val_info.volt_b.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.volt_b.param_name,"%s","LS_VOLT_B");
			}
			else if( (memcmp(g_ls_param_det[idx].param_name,"kwh_imp",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.kwh_imp.param_obis_code,gen_ls_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_block_val_info.kwh_imp.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.kwh_imp.param_name,"%s","LS_KWH_IMP");
			}
			else if( (memcmp(g_ls_param_det[idx].param_name,"kwh_exp",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.kwh_exp.param_obis_code,gen_ls_param_det.val_obis[index],6);
				memcpy(g_block_val_info.kwh_exp.param_value,&recv_flt_val,4);
				recv_flt_val = recv_flt_val/(float)1000;
				sprintf(g_block_val_info.kwh_exp.param_name,"%s","LS_KWH_EXP");
			}
			else if( (memcmp(g_ls_param_det[idx].param_name,"kvarh_lag",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.kvarh_lag.param_obis_code,gen_ls_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_block_val_info.kvarh_lag.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.kvarh_lag.param_name,"%s","LS_KVARH_LAG");
			}
			
			else if( (memcmp(g_ls_param_det[idx].param_name,"kvarh_lead",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.kvarh_lead.param_obis_code,gen_ls_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_block_val_info.kvarh_lead.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.kvarh_lead.param_name,"%s","LS_KVARH_LEAD");
			}
			
			else if( (memcmp(g_ls_param_det[idx].param_name,"kvah_imp",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.kvah_imp.param_obis_code,gen_ls_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_block_val_info.kvah_imp.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.kvah_imp.param_name,"%s","LS_KVAH_IMP");
			}
			
			else if( (memcmp(g_ls_param_det[idx].param_name,"kvah_exp",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.kvah_exp.param_obis_code,gen_ls_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_block_val_info.kvah_exp.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.kvah_exp.param_name,"%s","LS_KVAH_EXP");
			}
			
			else if( (memcmp(g_ls_param_det[idx].param_name,"freq",strlen(g_ls_param_det[idx].param_name))) == 0)
			{
				memcpy(g_block_val_info.freq.param_obis_code,gen_ls_param_det.val_obis[index],6);
				memcpy(g_block_val_info.freq.param_value,&recv_flt_val,4);
				sprintf(g_block_val_info.freq.param_name,"%s","LS_FREQ");
			}
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: store_ls_date_time()
*Input Parameters 			: ls_index, obis_index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store load survey time info in appropriate structure.
********************************************************************************************************/
int32_t store_ls_date_time( uint8_t ls_idx, uint8_t index)
{
	uint16_t 	year=0;
				
	date_time_t date_time;
	
	year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
	date_time.day= gen_data_val_info[index].value[3];
	date_time.month= gen_data_val_info[index].value[2];
	date_time.year =  year;
	date_time.hour= gen_data_val_info[index].value[5];
	date_time.minute= gen_data_val_info[index].value[6];
	date_time.second= gen_data_val_info[index].value[7];
	
	memcpy(&g_all_ls_param_obis_val.param_obis_val_info[index].obis_code,gen_ls_param_det.val_obis[index],6);
	memcpy(&g_all_ls_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_ls_param_obis_val.param_obis_val_info[index].value,&date_time,sizeof(date_time_t));
	
	return RET_SUCCESS;
	
	//if(memcmp(gen_ls_param_det.val_obis[index],g_date_time_obis,6)==0)
	if(1)
	{
		/* g_ls_entry_idx = (gen_data_val_info[index].value[5])*(60/g_int_period_blk) + (gen_data_val_info[index].value[6]/g_int_period_blk); */
		
/* 		printf(" Storing date for g_ls_entry_idx : %d -->>> %d_%d %02d:%02d \n",g_ls_entry_idx,
														gen_data_val_info[index].value[3],
														gen_data_val_info[index].value[2],
														gen_data_val_info[index].value[5],
														gen_data_val_info[index].value[6]); */

		year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
		g_block_val_info.date_time.day= gen_data_val_info[index].value[3];
		g_block_val_info.date_time.month= gen_data_val_info[index].value[2];
		g_block_val_info.date_time.year =  year;
		g_block_val_info.date_time.hour= gen_data_val_info[index].value[5];
		g_block_val_info.date_time.minute= gen_data_val_info[index].value[6];
		g_block_val_info.date_time.second= 0;
		
/* 		printf("ls_idx ::: %d Stored date %02d-%02d  %02d:%02d \n",ls_idx,
				block_val_info[ls_idx].date_time.day,
				block_val_info[ls_idx].date_time.month,
				block_val_info[ls_idx].date_time.hour,
				block_val_info[ls_idx].date_time.minute
		); */
		
		return RET_SUCCESS;
	}
	else
	{
		//printf("Ls date time not matched for ls_idx : %d index : %d\n",ls_idx,index);
		return -1;
	}
}

/* Inst Related */

/**************************************************************************************************
*Function 					: proc_inst_val_obis()
*Input Parameters 			: buffer, buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process inst val obis info.
********************************************************************************************************/
int32_t proc_inst_val_obis(uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_inst_val_obis()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}

		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_inst_param_det.tot_num_val_obis = msg[loc_idx-1];

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen in Getnext block\n",fun_name);
				
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_inst_scalar_obis()
*Input Parameters 			: buffer, buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process inst scalar obis info.
********************************************************************************************************/
int32_t proc_inst_scalar_obis(uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_inst_scalar_obis()";

	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
			{
				loc_idx = idx;
				break;
			}
		}
		
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
	
		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_inst_param_det.tot_num_scalar = msg[loc_idx-1];

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X04)&&(msg[idx+2]==0X12))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_inst_scalar_val()
*Input Parameters 			: buffer, buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process inst scalar value info.
********************************************************************************************************/
int32_t proc_inst_scalar_val(uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_inst_scalar_val()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{

		for(idx=0; idx<len; idx++)
		{
			if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0f))
			{
				loc_idx = idx;
				break;
			}
		}
		
		if(idx == len)
		{
			dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return -1;
		}
			
		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			for(idx=0; idx<len; idx++)
			{
				if((msg[idx]==0X02)&&(msg[idx+1]==0X02)&&(msg[idx+2]==0X0f))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_inst_value()
*Input Parameters 			: buffer, buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To process inst value info.
********************************************************************************************************/
int32_t proc_inst_value(uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_inst_value()";
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp == 1)
	{
		if(((msg[1]&0X08)==0x00) && (msg[12+OFFSET]==0X02)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X00))
		{
			loc_idx = 23+OFFSET;
		}
		else
		{
			for(idx=0; idx<len; idx++)
			{
				if(((msg[idx]==0X02)&&(msg[idx+2]==0X09)&&(msg[idx+3]==0X0C)) || (((msg[idx]==0X02)&&((msg[idx+2]==0X06)||(msg[idx+2]==0X05)))))
				{
					loc_idx = idx;
					break;
				}
			}
			if(idx == len)
			{
				dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return -1;
			}
		}

		dbg_log(INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx+1],len-(loc_idx+3));

		gen_inst_param_det.tot_num_value = msg[loc_idx+1];

		g_first_time_resp=0;
	}
	else
	{
		if(g_rr_frame)
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk)
		{
			if(((msg[1]&0X08)==0x00) && (msg[12+OFFSET]==0X02)&& (msg[13+OFFSET]==0X81))
			{
				loc_idx = 21+OFFSET;
			}
			else
			{
				for(idx=0; idx<len; idx++)
				{
					if(((msg[idx]==0X02)&&(msg[idx+2]==0X09)&&(msg[idx+3]==0X0C)) || (((msg[idx]==0X02)&&((msg[idx+2]==0X06)||(msg[idx+2]==0X05)))))
					{
						loc_idx = idx;
						break;
					}
				}
				if(idx == len)
				{

					dbg_log(INFORM,"%-20s : No start resp stamp seen\n",fun_name);

					return -1;
				}
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_inst_val()
*Input Parameters 			: comm_fd, meter address, meter addr size, inst val structure.
*Output Parameters 			: Inst val structure.
*Return	Value				: Success or appropriate error code.
*Description 				: To get inst value and copy into respective structure.
********************************************************************************************************/
int32_t get_inst_val(meter_comm_params_t *meter_comm_params, inst_val_info_t *recv_inst_data_val)
{
	static char fun_name[]="get_inst_val()";
	
	uint8_t obis[6] = {0};
	uint8_t temp_nxt_blk_flag = 0;
	
	memset(gen_data_val_info,0,sizeof(gen_data_val_info));
	memset(&g_all_inst_param_obis_val,0,sizeof(g_all_inst_param_obis_val));
	
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	g_get_nxt_blk_val=1;
	g_query_type = INST_VALUES_TYPE;
	dbg_log(INFORM,"%-20s : Sending QryType : INST_VALUES_TYPE\n",fun_name);
	
	g_first_time_resp=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	
	GET_OBIS_OCTETS(INST_DATA_VAL_OBIS_STR,obis);
	if(send_get_request(meter_comm_params, INST_DATA_VAL_INT_CLASS, obis, 6, INST_DATA_VAL_ATTR_NO)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get inst scaler obis info\n",fun_name);
		return -1;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst scaler value rr frame\n",fun_name);
				return -1;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get inst scaler value next block frame\n",fun_name);
				g_get_nxt_blk_val=g_get_nxt_blk_val+1;
				return -1;
			}
		}
	}
	
	if(fill_val_obis_det(INST_VALUES_TYPE)<0)
		return -1;
	
	if(fill_inst_val()<0)
		return -1;

	memcpy(recv_inst_data_val,&g_inst_data_val,sizeof(g_inst_data_val));
	
	memcpy(meter_comm_params->meter_response,&g_all_inst_param_obis_val,sizeof(g_all_inst_param_obis_val));
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: store_inst_val()
*Input Parameters 			: comm_fd, meter address, meter addr size, inst val structure.
*Output Parameters 			: Inst val structure.
*Return	Value				: Success or appropriate error code.
*Description 				: To get inst value and copy into respective structure.
********************************************************************************************************/
int32_t store_inst_val(uint8_t index, float recv_flt_val)
{
	uint8_t idx=0;
	static char fun_name[] = "store_inst_val()";
	
	dbg_log(INFORM,"%-20s : Index : %d, RecvFltVal : %0.5f\n",fun_name,index,recv_flt_val);
	
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].obis_code,gen_inst_param_det.val_obis[index],6);
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].value,&recv_flt_val,4);
	
	return RET_SUCCESS;
	
	//for(idx=0; idx<gen_inst_param_det.tot_num_value; idx++)
	for(idx=0; idx<MAX_NUM_INST_PARAMS; idx++)
	{
		if( (memcmp(gen_inst_param_det.val_obis[index], g_inst_param_det[idx].obis_code, 6)) == 0)
		{
			if( (memcmp(g_inst_param_det[idx].param_name,"cur_ir",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.cur_ir.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.cur_ir.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.cur_ir.param_name,"%s","INST_CUR_IR");
			}

			else if( (memcmp(g_inst_param_det[idx].param_name,"cur_iy",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.cur_iy.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.cur_iy.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.cur_iy.param_name,"%s","INST_CUR_IY");
			}
		
			else if( (memcmp(g_inst_param_det[idx].param_name,"cur_ib",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.cur_ib.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.cur_ib.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.cur_ib.param_name,"%s","INST_CUR_IB");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"volt_r",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.volt_r.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.volt_r.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.volt_r.param_name,"%s","INST_VOLT_R");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"volt_y",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.volt_y.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.volt_y.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.volt_y.param_name,"%s","INST_VOLT_Y");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"volt_b",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				//printf("In volt B, value : %0.5f\n",recv_flt_val);
				
				memcpy(g_inst_data_val.volt_b.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.volt_b.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.volt_b.param_name,"%s","INST_VOLT_B");
				//print_data(g_inst_data_val.volt_b.param_obis_code,6);
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"pf_r",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.pf_r.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.pf_r.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.pf_r.param_name,"%s","INST_PF_R");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"pf_y",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.pf_y.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.pf_y.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.pf_y.param_name,"%s","INST_PF_Y");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"pf_b",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.pf_b.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.pf_b.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.pf_b.param_name,"%s","INST_PF_B");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"pf_avg",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.pf_avg.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.pf_avg.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.pf_avg.param_name,"%s","INST_PF_AVG");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"freq",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.freq.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.freq.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.freq.param_name,"%s","INST_FREQ");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"kva",strlen(g_inst_param_det[idx].param_name))) == 0)
				{
				memcpy(g_inst_data_val.kva.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.kva.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.kva.param_name,"%s","INST_KVA");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"kw",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.kw.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.kw.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.kw.param_name,"%s","INST_KW");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"kvar",strlen(g_inst_param_det[idx].param_name))) == 0)
				{
				memcpy(g_inst_data_val.kvar.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.kvar.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.kvar.param_name,"%s","INST_KVAR");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"num_pow_fail",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.num_pow_fail.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.num_pow_fail.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.num_pow_fail.param_name,"%s","INST_NUM_POW_FAIL");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"cu_pf_dur",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.cu_pf_dur.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.cu_pf_dur.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.cu_pf_dur.param_name,"%s","INST_PF_DUR");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"cu_ta_cnt",strlen(g_inst_param_det[idx].param_name))) == 0)
				{
				memcpy(g_inst_data_val.cu_ta_cnt.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.cu_ta_cnt.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.cu_ta_cnt.param_name,"%s","INST_TA_CNT");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"cu_bi_cnt",strlen(g_inst_param_det[idx].param_name))) == 0)
				{
				memcpy(g_inst_data_val.cu_bi_cnt.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.cu_bi_cnt.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.cu_bi_cnt.param_name,"%s","INST_BI_CNT");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"cu_pr_cnt",strlen(g_inst_param_det[idx].param_name))) == 0)
				{
				memcpy(g_inst_data_val.cu_pr_cnt.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.cu_pr_cnt.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.cu_pr_cnt.param_name,"%s","INST_PR_CNT");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"kwh",strlen(g_inst_param_det[idx].param_name))) == 0)
				{
				memcpy(g_inst_data_val.kwh.param_obis_code,gen_inst_param_det.val_obis[index],6);
				memcpy(g_inst_data_val.kwh.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.kwh.param_name,"%s","INST_KWH");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"kvarh_lag",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.kvarh_lag.param_obis_code,gen_inst_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_inst_data_val.kvarh_lag.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.kvarh_lag.param_name,"%s","INST_KVARH_LEAD");
			}
		
			else if( (memcmp(g_inst_param_det[idx].param_name,"kvarh_lead",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.kvarh_lead.param_obis_code,gen_inst_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_inst_data_val.kvarh_lead.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.kvarh_lead.param_name,"%s","INST_KVARH_LEAD");
			}
			
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"kvah",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.kvah.param_obis_code,gen_inst_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_inst_data_val.kvah.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.kvah.param_name,"%s","INST_KVAH");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"kwmd",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.kwmd.param_obis_code,gen_inst_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_inst_data_val.kwmd.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.kwmd.param_name,"%s","INST_KWMD");
			}
			
			else if( (memcmp(g_inst_param_det[idx].param_name,"kvamd",strlen(g_inst_param_det[idx].param_name))) == 0)
			{
				memcpy(g_inst_data_val.kvamd.param_obis_code,gen_inst_param_det.val_obis[index],6);
				recv_flt_val = recv_flt_val/(float)1000;
				memcpy(g_inst_data_val.kvamd.param_value,&recv_flt_val,4);
				sprintf(g_inst_data_val.kvamd.param_name,"%s","INST_KVAMD");
			}
			
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: store_inst_date_time()
*Input Parameters 			: inst index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To store inst date time in appropriate structure.
********************************************************************************************************/
int32_t store_inst_date_time(uint8_t index)
{
	uint16_t 	year=0;
	date_time_t date_time;
	
	year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
	date_time.day= gen_data_val_info[index].value[3];
	date_time.month= gen_data_val_info[index].value[2];
	date_time.year =  year;
	date_time.hour= gen_data_val_info[index].value[5];
	date_time.minute= gen_data_val_info[index].value[6];
	date_time.second= gen_data_val_info[index].value[7];
	
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].obis_code,gen_inst_param_det.val_obis[index],6);
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].data_type,&gen_data_val_info[index].data_type,1);
	memcpy(&g_all_inst_param_obis_val.param_obis_val_info[index].value,&date_time,sizeof(date_time_t));
	
	return RET_SUCCESS;
	
	if(memcmp(gen_inst_param_det.val_obis[index],g_date_time_obis,6)==0)
	{
		year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
		meter_date_time.day = g_inst_data_val.date_time.day= gen_data_val_info[index].value[3];
		meter_date_time.month = g_inst_data_val.date_time.month= gen_data_val_info[index].value[2];
		meter_date_time.year = g_inst_data_val.date_time.year =  year;
		meter_date_time.hour = g_inst_data_val.date_time.hour= gen_data_val_info[index].value[5];
		meter_date_time.minute = g_inst_data_val.date_time.minute= gen_data_val_info[index].value[6];
		meter_date_time.second = g_inst_data_val.date_time.second= gen_data_val_info[index].value[7];
		
		return RET_SUCCESS;
	}
	else if(memcmp(gen_inst_param_det.val_obis[index],g_date_time_bill_obis,6)==0)
	{
		year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
		bill_date_time.day = g_inst_data_val.bill_date.day= gen_data_val_info[index].value[3];
		bill_date_time.month = g_inst_data_val.bill_date.month= gen_data_val_info[index].value[2];
		bill_date_time.year = g_inst_data_val.bill_date.year =  year;
		bill_date_time.hour = g_inst_data_val.bill_date.hour= gen_data_val_info[index].value[5];
		bill_date_time.minute = g_inst_data_val.bill_date.minute= gen_data_val_info[index].value[6];
		bill_date_time.second = g_inst_data_val.bill_date.second= gen_data_val_info[index].value[7];
								
		return RET_SUCCESS;
	}
	else
	{
		return -1;
	}
}

/**************************************************************************************************
*Function 					: fill_inst_val()
*Input Parameters 			: None.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To fill inst data value in appropriate structure.
********************************************************************************************************/
int32_t fill_inst_val(void)
{
	static char fun_name[]="fill_inst_val()";
	uint8_t 	idx=0;
	int8_t 		*p_tmp_str=NULL;
	float 		flt_val = 0.0,scal_flt_val=0.0;
	uint8_t		uint8_temp_val=0;
	int16_t		int16_temp_val=0;
	uint16_t	uint16_temp_val=0;
	int32_t		int32_temp_val=0;
	uint32_t	uint32_temp_val=0;
	float 		float_temp_val=0.0;
	
	g_all_inst_param_obis_val.tot_num_params=gen_inst_param_det.tot_num_value;
	
	for(idx=0; idx<gen_inst_param_det.tot_num_value; idx++)
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
				
				get_scaler_mf(gen_inst_param_det.scalar_val[idx].value,&scal_flt_val);
				
				flt_val = (float)((float)float_temp_val * scal_flt_val);
				if(store_inst_val(idx, flt_val) < 0)
					continue;
			break;
			
			case UNSIGNED_32BIT_TYPE:
			case SIGNED_32BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					p_tmp_str=(int8_t*)&uint32_temp_val;
				else
					p_tmp_str=(int8_t*)&int32_temp_val;

				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_inst_param_det.scalar_val[idx].value,&scal_flt_val);
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					flt_val = (float)((float)uint32_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int32_temp_val * scal_flt_val);
				
				if(store_inst_val(idx, flt_val) < 0)
					continue;
	
			break;
			
			case UNSIGNED_16BIT_TYPE:
			case SIGNED_16BIT_TYPE:
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					p_tmp_str=(int8_t*)&uint16_temp_val;
				else
					p_tmp_str=(int8_t*)&int16_temp_val;

				p_tmp_str[1] = gen_data_val_info[idx].value[0];
				p_tmp_str[0] = gen_data_val_info[idx].value[1];
				
				get_scaler_mf(gen_inst_param_det.scalar_val[idx].value,&scal_flt_val);
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					flt_val = (float)((float)uint16_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int16_temp_val * scal_flt_val);
				
				if(store_inst_val(idx, flt_val) < 0)
					continue;

			break;
			
			case UNSIGNED_8BIT_TYPE:
				p_tmp_str=(int8_t*)&uint8_temp_val;
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				get_scaler_mf(gen_inst_param_det.scalar_val[idx].value,&scal_flt_val);
				flt_val = (float)((float)uint8_temp_val * scal_flt_val);
				
				if(store_inst_val( idx, flt_val) < 0)
					continue;
			break;
			
			case OCTET_STRING_TYPE:
				if(store_inst_date_time(idx)<0)
					continue;

			break;
			
			default : break;
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_inst_obis_code_det()
*Input Parameters 			: comm_fd, dlma address, meter addr size, general param structure.
*Output Parameters 			: general param structure.
*Return	Value				: Success or appropriate error code.
*Description 				: To get inst obis code details and fill in appropriate structure.
********************************************************************************************************/
int32_t get_inst_obis_code_det(meter_comm_params_t *meter_comm_params,gen_params_det_t *recv_gen_inst_param_det)
{
	static char fun_name[]="get_inst_obis_code_det()";
	uint8_t val_obis[6] = {0};
	
	GET_OBIS_OCTETS(INST_VAL_OBIS_STR,val_obis);
	dbg_log(INFORM,"%-20s : Sending QryType : INST_VAL_OBIS_TYPE\n",fun_name);
	if(get_gen_val_obis(meter_comm_params, INST_VAL_OBIS_TYPE,INST_VAL_INT_CLASS,val_obis,6,INST_VAL_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	 /* val_obis[0] = 1;
	 val_obis[1] = 0;
	 val_obis[2] = 94;
	 val_obis[3] = 91;
	 val_obis[4] = 3;
	 val_obis[5] = 255;
	 
	 int_class=0x0007, attr_no=0x0003; */
	
	GET_OBIS_OCTETS(INST_SCALAR_OBIS_STR,val_obis);
	dbg_log(INFORM,"%-20s : Sending QryType : INST_SCALE_OBIS_TYPE\n",fun_name);
	if(get_gen_scalar_obis(meter_comm_params, INST_SCALE_OBIS_TYPE,INST_SCALAR_INT_CLASS,val_obis,6,INST_SCALAR_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	/* val_obis[0] = 1;
	val_obis[1] = 0;
	val_obis[2] = 94;
	val_obis[3] = 91;
	val_obis[4] = 3;
	val_obis[5] = 255;
	 
	int_class=0x0007, attr_no=0x0002; */
	
	GET_OBIS_OCTETS(INST_SCALAR_VAL_STR,val_obis);
	
	dbg_log(INFORM,"%-20s : Sending QryType : INST_SCALE_VAL_TYPE\n",fun_name);
	if(get_gen_scalar_val(meter_comm_params, INST_SCALE_VAL_TYPE,INST_SCALAR_VAL_INT_CLASS,val_obis,6,INST_SCALAR_VAL_ATTR_NO)<0)
	{
		dbg_log(INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: send_disc()
*Input Parameters 			: comm_fd, dlma address, meter addr size.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To send disc frame to meter.
********************************************************************************************************/
int32_t send_disc(meter_comm_params_t *meter_comm_params )
{
	static char 	fun_name[] = "send_disc()";
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0;
	uint16_t		fcs=0, frm_format=0, frame_len=(0x07)+OFFSET;
	int32_t			send_fun_ret = -1;


	g_query_type = DISC_TYPE;

	memset((void *)g_send_buff, 0, sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	frm_format = FRAME_FORMAT_TYPE | frame_len;
	p_gen_ptr = (uint8_t *)&frm_format;

	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];

	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;

		case 2:
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		case 4:
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((((meter_comm_params->meter_id)>>7)<<1)&0XFF);
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		default:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;
	}

	g_send_buff[idx++] = g_src_addr;

	g_send_buff[idx++] = CTRL_DISC_FRAME | POLL_FINAL_BIT;

	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF;
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	dbg_log(INFORM,"%-20s : sending disconnect frame\n",fun_name);
	
	send_fun_ret = send_msg_meter(meter_comm_params, g_send_buff, idx);
	
	if(send_fun_ret<0)
	{
		return send_fun_ret;
	}
	else
	{
		sleep(1);
	}
	
	return send_fun_ret;
}

/**************************************************************************************************
*Function 					: send_snrm()
*Input Parameters 			: comm_fd, dlma address, meter addr size.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To send snrm frame to meter.
********************************************************************************************************/
int32_t send_snrm(meter_comm_params_t *meter_comm_params)
{
	static char 	fun_name[] = "send_snrm()";
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0;
	uint16_t		fcs=0, frm_format=0, frame_len=(0x07)+OFFSET;
	int32_t			send_fun_ret = -1;

	g_query_type = SNRM_TYPE;

	g_send_seq_num = 0;
	g_recv_seq_num = 0;
	
	g_rr_frame = 0;
	g_get_nxt_blk = 0;
	
	memset((void *)g_send_buff, 0, sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	frm_format = FRAME_FORMAT_TYPE | frame_len;
	p_gen_ptr = (uint8_t *)&frm_format;

	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];

	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;

		case 2:
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		case 4:
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((((meter_comm_params->meter_id)>>7)<<1)&0XFF);
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		default:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;
	}

	g_send_buff[idx++] = g_src_addr;

	g_send_buff[idx++] = CTRL_SNRM_FRAME | POLL_FINAL_BIT;

	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF;
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	dbg_log(INFORM,"%-20s : sending SNRM frame\n",fun_name);
	
	send_fun_ret = send_msg_meter(meter_comm_params, g_send_buff, idx);
	
	return send_fun_ret;
}

/**************************************************************************************************
*Function 					: get_curr_date_time()
*Input Parameters 			: comm_fd, dlma address, meter addr size.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get current time info from meter.
********************************************************************************************************/
int32_t get_curr_date_time(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="get_curr_date_time()";
	uint8_t obis[6]={0};
	
	g_query_type = DATE_TIME_TYPE;
	dbg_log(INFORM,"%-20s : Sending QryType : DATE_TIME_TYPE\n",fun_name);
	
	GET_OBIS_OCTETS(DATE_TIME_OBIS_STR,obis);
	print_data(obis,6);
	
	if(send_get_request(meter_comm_params,DATE_TIME_INT_CLASS,obis,6,DATE_TIME_ATTR_NO)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get Meter date time info info\n",fun_name);
		return RET_VAL_OBIS_NP_FAIL;
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_event_entry_order()
*Input Parameters 			: comm_fd, dlma address, meter addr size.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get entry order of meter.
********************************************************************************************************/
int32_t get_event_entry_order(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="get_event_entry_order()";
	
	uint8_t idx=0;
	uint8_t temp_nxt_blk_flag = 0;
	uint8_t obis[6] = {0};
	
	g_rr_frame = 0;
	g_get_nxt_blk= 0;
	g_first_time_resp=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = CHECK_LIFO_OR_FIFO;
	
	dbg_log(INFORM,"%-20s : Sending QryType : CHECK_LIFO_OR_FIFO\n",fun_name);

	GET_OBIS_OCTETS(EVENT_ENTRY_OBIS_STR,obis);
	if(send_get_request(meter_comm_params,EVENT_ENTRY_ORDER_INT_CLASS, obis, 6, EVENT_ENTRY_ORDER_ATTR_NO)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get event entry data info\n",fun_name);
		return RET_VAL_OBIS_NP_FAIL;
	}
	
	while(g_rr_frame || g_get_nxt_blk)
	{
		if(g_get_nxt_blk)
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame)
		{
			if(send_rr_frame(meter_comm_params)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get event entry rr frame\n",fun_name);
				return RET_VAL_OBIS_NP_FAIL;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			//if(send_get_next_blk(midx, g_get_nxt_blk_val)<0)
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(meter_comm_params, *g_block_num_det)<0)
			{
				dbg_log(REPORT,"%-20s : failed to get event entry get next frame frame\n",fun_name);
				return RET_VAL_OBIS_NP_FAIL;
			}
		}
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: send_get_bill_request()
*Input Parameters 			: comm_fd, dlms address, meter addr size and block value.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get next block info data.
********************************************************************************************************/
int32_t send_get_bill_request (meter_comm_params_t *meter_comm_params,uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
{
	static char 	fun_name[]="send_get_bill_request()";
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0,ctrl_field=0;
	uint16_t		fcs=0, frm_format = 0;
	int32_t			send_fun_ret = -1;
	
	uint32_t		st_bill_num,end_bill_num;
				
	memset(g_send_buff,0,sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;

	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;

		case 2:
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		case 4:
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((((meter_comm_params->meter_id)>>7)<<1)&0XFF);
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		default:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;
	}

	g_send_buff[idx++] = g_src_addr;
	
	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num << 1 );
	g_send_seq_num = ( g_send_seq_num + 1 ) % 8;

	ctrl_field |= ( g_recv_seq_num << 5 );
	
	g_send_buff[idx++] = ctrl_field;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;
	
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0x00;

	g_send_buff[idx++] = (GET_REQUEST_NORMAL >> 8) & 0x00FF;;
	g_send_buff[idx++] = GET_REQUEST_NORMAL & 0x00FF;;

	g_send_buff[idx++] = 0x81;

	p_gen_ptr = (uint8_t*)&int_class;
	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];

	memcpy(&g_send_buff[idx],obis_code,obis_len);
	idx = idx +obis_len;
	
	g_send_buff[idx++] = 0x02;
	g_send_buff[idx++] = 0x01;
	g_send_buff[idx++] = 0x02;
	g_send_buff[idx++] = 0x02;
	g_send_buff[idx++] = 0x04;
	g_send_buff[idx++] = 0x06;
	
	if(g_meter_store_order == LI_FO)
	{
		if(g_tot_bill_entry>MAX_BILL_NUM)
		{
			//st_bill_num=g_tot_bill_entry-MAX_BILL_NUM;
			st_bill_num=g_tot_bill_entry;
			memset(&end_bill_num,0,4);
			end_bill_num = g_tot_bill_entry;
		}
		else if(g_tot_bill_entry<1)
		{
			st_bill_num =0;
			end_bill_num=0;
		}
		else
		{
			st_bill_num=1;
			end_bill_num=g_tot_bill_entry;
		}
		
		dbg_log(INFORM,"%-20s : LI_FO, StNumEvent : %d, EndNumEvent : %d\n",fun_name,st_bill_num,end_bill_num);

	}
	else if(g_meter_store_order == FI_FO)
	{
		if(g_tot_bill_entry==0)
			st_bill_num=0;
		else
			st_bill_num=1;
		
		if(g_tot_bill_entry>MAX_BILL_NUM)
		{
			memset(&end_bill_num,0,4);
			end_bill_num=MAX_BILL_NUM;
		}
		else
			end_bill_num=g_tot_bill_entry;
		
		dbg_log(INFORM,"%-20s : FI_FO, StNumEvent : %d, EndNumEvent : %d\n",fun_name,st_bill_num,end_bill_num);
	}
	
	p_gen_ptr = (uint8_t*)&st_bill_num;
	g_send_buff[idx++] = p_gen_ptr[3];
	g_send_buff[idx++] = p_gen_ptr[2];
	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];
	
	g_send_buff[idx++] = 0x06;
	p_gen_ptr = (uint8_t*)&end_bill_num;
	g_send_buff[idx++] = p_gen_ptr[3];
	g_send_buff[idx++] = p_gen_ptr[2];
	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];
	
	g_send_buff[idx++] = 0x12;
	g_send_buff[idx++] = 0x00;
	g_send_buff[idx++] = 0x01;
	g_send_buff[idx++] = 0x12;

	p_gen_ptr = (uint8_t*)&attr_no;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	frm_format = FRAME_FORMAT_TYPE | (idx+1);
	p_gen_ptr = (uint8_t*)&frm_format;
	
	g_send_buff[1] = p_gen_ptr[1];
	g_send_buff[2] = p_gen_ptr[0];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], 5+OFFSET);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[6+OFFSET] = p_gen_ptr[0];
	g_send_buff[7+OFFSET] = p_gen_ptr[1];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	dbg_log(INFORM,"%-20s : sending get_billing_request frame\n",fun_name);
	send_fun_ret = send_msg_meter(meter_comm_params, g_send_buff, idx);
	
	return send_fun_ret;
}

/**************************************************************************************************
*Function 					: send_get_event_request()
*Input Parameters 			: comm_fd, dlms address, meter addr size and block value.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get next block info data.
********************************************************************************************************/
int32_t send_get_event_request (meter_comm_params_t *meter_comm_params,uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no, uint8_t event_read_flag)
{
	static char 	fun_name[]="send_get_event_request()";
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0,ctrl_field=0;
	uint16_t		fcs=0, frm_format = 0;
	int32_t			send_fun_ret = -1;
	
	uint32_t		st_event_num=0,end_event_num=0;
				
	memset(g_send_buff,0,sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;

	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;

		case 2:
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		case 4:
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((((meter_comm_params->meter_id)>>7)<<1)&0XFF);
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		default:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;
	}

	g_send_buff[idx++] = g_src_addr;
	
	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num << 1 );
	g_send_seq_num = ( g_send_seq_num + 1 ) % 8;

	ctrl_field |= ( g_recv_seq_num << 5 );
	
	g_send_buff[idx++] = ctrl_field;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;
	
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0x00;

	g_send_buff[idx++] = (GET_REQUEST_NORMAL >> 8) & 0x00FF;;
	g_send_buff[idx++] = GET_REQUEST_NORMAL & 0x00FF;;

	g_send_buff[idx++] = 0x81;

	p_gen_ptr = (uint8_t*)&int_class;
	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];

	memcpy(&g_send_buff[idx],obis_code,obis_len);
	idx = idx +obis_len;
	
	g_send_buff[idx++] = 0x02;
	g_send_buff[idx++] = 0x01;
	g_send_buff[idx++] = 0x02;
	g_send_buff[idx++] = 0x02;
	g_send_buff[idx++] = 0x04;
	g_send_buff[idx++] = 0x06;
	
	if(g_meter_store_order == LI_FO)
	{
		if(g_tot_event_entry>MAX_EVENT_NUM)
		{
			if(event_read_flag==0)
			{
				st_event_num=g_tot_event_entry-MAX_EVENT_NUM;
			}
			else
				st_event_num=1;
			
			memset(&end_event_num,0,4);
			end_event_num = g_tot_event_entry;
		}
		else if(g_tot_event_entry<1)
		{
			st_event_num =0;
			end_event_num=0;
		}
		else
		{
			st_event_num=1;
			end_event_num=g_tot_event_entry;
		}
		
		dbg_log(INFORM,"%-20s : LI_FO, StNumEvent : %d, EndNumEvent : %d\n",fun_name,st_event_num,end_event_num);

	}
	else if(g_meter_store_order == FI_FO)
	{
		if(g_tot_event_entry==0)
			st_event_num=0;
		else
			st_event_num=1;
		
		if(g_tot_event_entry>MAX_EVENT_NUM)
		{
			if(event_read_flag==0)
			{
				memset(&end_event_num,0,4);
				end_event_num=MAX_EVENT_NUM;
			}
			else
				end_event_num=g_tot_event_entry;
			
		}
		else
			end_event_num=g_tot_event_entry;
		
		dbg_log(INFORM,"%-20s : FI_FO, StNumEvent : %d, EndNumEvent : %d\n",fun_name,st_event_num,end_event_num);
	}
	
	p_gen_ptr = (uint8_t*)&st_event_num;
	g_send_buff[idx++] = p_gen_ptr[3];
	g_send_buff[idx++] = p_gen_ptr[2];
	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];
	
	g_send_buff[idx++] = 0x06;
	p_gen_ptr = (uint8_t*)&end_event_num;
	g_send_buff[idx++] = p_gen_ptr[3];
	g_send_buff[idx++] = p_gen_ptr[2];
	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];
	
	g_send_buff[idx++] = 0x12;
	g_send_buff[idx++] = 0x00;
	g_send_buff[idx++] = 0x01;
	g_send_buff[idx++] = 0x12;

	p_gen_ptr = (uint8_t*)&attr_no;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	frm_format = FRAME_FORMAT_TYPE | (idx+1);
	p_gen_ptr = (uint8_t*)&frm_format;
	
	g_send_buff[1] = p_gen_ptr[1];
	g_send_buff[2] = p_gen_ptr[0];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], 5+OFFSET);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[6+OFFSET] = p_gen_ptr[0];
	g_send_buff[7+OFFSET] = p_gen_ptr[1];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	dbg_log(INFORM,"%-20s : sending get_event_request frame\n",fun_name);
	send_fun_ret = send_msg_meter(meter_comm_params, g_send_buff, idx);
	
	return send_fun_ret;
}

/**************************************************************************************************
*Function 					: send_get_next_blk()
*Input Parameters 			: comm_fd, dlma address, meter addr size and block value.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get next block info data.
********************************************************************************************************/
int32_t send_get_next_blk(meter_comm_params_t *meter_comm_params, uint32_t blk_val)
{
	static char 	fun_name[] = "send_get_next_blk()";
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0,ctrl_field=0;
	uint16_t		fcs=0, frm_format = 0;
	int32_t			send_fun_ret = -1, blk_val_data=0;
	
	memset((void *)g_send_buff, 0, sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;

	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;

		case 2:
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		case 4:
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((((meter_comm_params->meter_id)>>7)<<1)&0XFF);
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		default:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;
	}

	g_send_buff[idx++] = g_src_addr;
	
	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num << 1 );
	g_send_seq_num = ( g_send_seq_num + 1 ) % 8;

	ctrl_field |= ( g_recv_seq_num << 5 );
	
	g_send_buff[idx++] = ctrl_field;
	
	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;
	
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0x00;
	
	g_send_buff[idx++] = (GET_REQUEST_NEXT_DATA_BLOCK >> 8) & 0x00FF;;
	g_send_buff[idx++] = GET_REQUEST_NEXT_DATA_BLOCK & 0x00FF;;

	g_send_buff[idx++] = 0x81;

	p_gen_ptr = (uint8_t *)&blk_val;
	g_send_buff[idx++] = p_gen_ptr[3];
	g_send_buff[idx++] = p_gen_ptr[2];
	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];
	
/* 	memcpy(&g_send_buff[idx],&blk_val,4);
	idx += 4; */
	
	frm_format = FRAME_FORMAT_TYPE | (idx+1);
	p_gen_ptr = (uint8_t *)&frm_format;
	
	g_send_buff[1] = p_gen_ptr[1];
	g_send_buff[2] = p_gen_ptr[0];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], 5+OFFSET);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[6+OFFSET] = p_gen_ptr[0];
	g_send_buff[7+OFFSET] = p_gen_ptr[1];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	memcpy(&blk_val_data,&blk_val,4);
	//dbg_log(INFORM,"%-20s : sending Next block val : %d\n",fun_name,blk_val_data);
	dbg_log(INFORM,"%-20s : sending Next block val : %d\n",fun_name,blk_val);
	
	send_fun_ret = send_msg_meter(meter_comm_params, g_send_buff, idx);
	
	return send_fun_ret;
}

/**************************************************************************************************
*Function 					: send_get_request()
*Input Parameters 			: comm_fd,meter_address,meter_addr_size,qry_type,inf_class,obis_code,obis_code_len,attr_num.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get next available data details.
********************************************************************************************************/
int32_t send_get_request(meter_comm_params_t *meter_comm_params, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
{
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0,ctrl_field=0;
	uint16_t		fcs=0, frm_format = 0;
	int32_t			send_fun_ret = -1;
	
	memset(g_send_buff,0,sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;
	
	//printf("------>>>>met_addr_size : %d  dlms_met_addr : %d\n",g_met_addr_size,g_dlms_met_addr);
	
	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;

		case 2:
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		case 4:
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((((meter_comm_params->meter_id)>>7)<<1)&0XFF);
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		default:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;
	}
	
	g_send_buff[idx++] = g_src_addr;
	
	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num << 1 );
	
	g_send_seq_num = ( g_send_seq_num + 1 ) % 8;
	ctrl_field |= ( g_recv_seq_num << 5 );

	g_send_buff[idx++] = ctrl_field;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;
	
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0x00;

	g_send_buff[idx++] = (GET_REQUEST_NORMAL >> 8) & 0x00FF;;
	g_send_buff[idx++] = GET_REQUEST_NORMAL & 0x00FF;;

	g_send_buff[idx++] = 0x81;

	p_gen_ptr = (uint8_t*)&int_class;
	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];

	memcpy(&g_send_buff[idx],obis_code,obis_len);
	idx = idx +obis_len;
	
	p_gen_ptr = (uint8_t*)&attr_no;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	frm_format = FRAME_FORMAT_TYPE | (idx+1);
	p_gen_ptr = (uint8_t*)&frm_format;
	
	g_send_buff[1] = p_gen_ptr[1];
	g_send_buff[2] = p_gen_ptr[0];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], 5+OFFSET);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[6+OFFSET] = p_gen_ptr[0];
	g_send_buff[7+OFFSET] = p_gen_ptr[1];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	dbg_log(INFORM,"%-20s : sending get_request frame\n","send_get_request()");
	
	send_fun_ret = send_msg_meter(meter_comm_params, g_send_buff, idx);
	
	return send_fun_ret;
}

/**************************************************************************************************
*Function 					: send_aarq()
*Input Parameters 			: comm_fd, dlma address, meter addr size and meter password.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get next block info data.
********************************************************************************************************/
//int32_t send_aarq(meter_comm_params_t *meter_comm_params, char*meter_pass)
int32_t send_aarq(meter_comm_params_t *meter_comm_params)
{
	static char 	fun_name[] = "send_aarq()";
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0,ctrl_field=0;
	uint16_t		fcs=0, frm_format = 0;
	int32_t			send_fun_ret = -1;
	
	g_query_type = AARQ_TYPE;

	memset((void *)g_send_buff, 0, sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;

	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;

		case 2:
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		case 4:
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((((meter_comm_params->meter_id)>>7)<<1)&0XFF);
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		default:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;
	}

/*
	from DCU COPIED
	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num[midx] << 1 );
	g_send_seq_num[midx] = ( g_send_seq_num[midx] + 1 ) % 8;

	ctrl_field |= ( g_recv_seq_num[midx] << 5 );
	
	g_send_buff[idx++] = ctrl_field; */
	
	
	g_send_buff[idx++] = g_src_addr;

	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num << 1 );
	g_send_seq_num = ( g_send_seq_num + 1 ) % 8;

	ctrl_field |= ( g_recv_seq_num << 5 );
	
	g_send_buff[idx++] = ctrl_field;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;
	
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0x00;

	g_send_buff[idx++] = AARQ_FRAME;

	g_send_buff[idx++] = 46 + strlen(meter_comm_params->meter_pass);

	// Application context name tag, length and encoded value
	g_send_buff[idx++] = 0xA1;    // tag
	g_send_buff[idx++] = 0x09;    // length

	g_send_buff[idx++] = 0x06;
	g_send_buff[idx++] = 0x07;
	g_send_buff[idx++] = 0x60;
	g_send_buff[idx++] = 0x85;
	g_send_buff[idx++] = 0x74;
	g_send_buff[idx++] = 0x05;
	g_send_buff[idx++] = 0x08;
	g_send_buff[idx++] = 0x01;
	g_send_buff[idx++] = 0x01;

	g_send_buff[idx++] = 0x8A;
	g_send_buff[idx++] = 0x02;
	g_send_buff[idx++] = 0x07;
	g_send_buff[idx++] = 0x80;

	// Authentication Functional Unit
	g_send_buff[idx++] = 0x8B;

	g_send_buff[idx++] = 0x07;
	g_send_buff[idx++] = 0x60;
	g_send_buff[idx++] = 0x85;
	g_send_buff[idx++] = 0x74;
	g_send_buff[idx++] = 0x05;
	g_send_buff[idx++] = 0x08;
	g_send_buff[idx++] = 0x02;
	g_send_buff[idx++] = 0x01;

	// Authentication Value
	g_send_buff[idx++] = 0xAC;
	g_send_buff[idx++] = 2 + strlen(meter_comm_params->meter_pass);
	g_send_buff[idx++] = 0x80;
	g_send_buff[idx++] = strlen(meter_comm_params->meter_pass);

	memcpy((void *)&g_send_buff[idx],(const void*)meter_comm_params->meter_pass,strlen(meter_comm_params->meter_pass));
	idx += strlen(meter_comm_params->meter_pass);

	// Tag and length for AARQ User field
	g_send_buff[idx++] = 0xBE;    // tag
	g_send_buff[idx++] = 0x10;    // length

	// Encoding the choice for User Information (OCTET STRING) and length
	g_send_buff[idx++] = 0x04;    // tag
	g_send_buff[idx++] = 0x0E;    // length

	// Value
	g_send_buff[idx++] = 0x01;    // tag for DLMS Initiate Request
	g_send_buff[idx++] = 0x00;    // NOT USED
	g_send_buff[idx++] = 0x00;    // NOT USED
	g_send_buff[idx++] = 0x00;    // NOT USED
	g_send_buff[idx++] = 0x06;    // Proposed DLMS Version No.

	// Tag for Conformance Block
	g_send_buff[idx++] = 0x5F;    // tag - 1st part
	g_send_buff[idx++] = 0x1F;    // tag - 2nd part

	// Len of Conformance Block
	g_send_buff[idx++] = 0x04;

	// Conformance block
	g_send_buff[idx++] = 0x00;
	g_send_buff[idx++] = 0x00;
	g_send_buff[idx++] = 0x18;
	g_send_buff[idx++] = 0x1D;

	// Client Max receive PDU size (0xFFFF)
	g_send_buff[idx++] = 0xFF;
	g_send_buff[idx++] = 0xFF;
	
	frm_format = FRAME_FORMAT_TYPE | (idx+1);
	p_gen_ptr = (uint8_t *)&frm_format;
	
	g_send_buff[1] = p_gen_ptr[1];
	g_send_buff[2] = p_gen_ptr[0];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], 5+OFFSET);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[6+OFFSET] = p_gen_ptr[0];
	g_send_buff[7+OFFSET] = p_gen_ptr[1];
	
	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF; 
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	dbg_log(INFORM,"%-20s : sending AARQ frame\n",fun_name);
	
	send_fun_ret = send_msg_meter(meter_comm_params,g_send_buff, idx);
	
	return send_fun_ret;
}

/**************************************************************************************************
*Function 					: get_nameplate_info()
*Input Parameters 			: comm_fd, dlma address, meter addr size and name plate obis structure.
*Output Parameters 			: name plate obis structure.
*Return	Value				: Success or appropriate error code.
*Description 				: To get name plate info.
********************************************************************************************************/
int8_t get_nameplate_info(meter_comm_params_t *meter_comm_params, obis_name_plate_info_t *np_params_obis_val_info)
{
	static char fun_name[]="get_name_plate()";
	uint8_t 	idx = 0;
	time_t 		curr_time = time(NULL);
	
	if(get_curr_date_time(meter_comm_params)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get Meter curr date time\n",fun_name); 
		return RET_VAL_OBIS_NP_FAIL;
	}
	
	for(idx=0; idx<6; idx++)
	{
		g_query_type = NAME_PLATE_PARAMS_TYPE;
		dbg_log(INFORM,"%-20s : Sending QryType : NAME_PLATE_PARAMS_TYPE : %d\n",fun_name,idx);
		g_name_plate_idx = idx;
		
		if(send_get_request(meter_comm_params,NP_INT_CLASS, name_plate_obis[idx], 6, NP_ATTR_NO)<0)
		{
			dbg_log(REPORT,"%-20s : failed to get Name plae info for obis : %d,%d,%d,%d,%d,%d\n",
			fun_name,name_plate_obis[idx][0],
			name_plate_obis[idx][1],name_plate_obis[idx][2],
			name_plate_obis[idx][3],name_plate_obis[idx][4],
			name_plate_obis[idx][5]);
			
			continue;
		}
	}
	
	if( get_event_entry_order(meter_comm_params)<0)
	{
		dbg_log(REPORT,"%-20s : failed to get meter storing entry order\n",fun_name);
		
		return RET_VAL_OBIS_NP_FAIL;
	}
	
	g_name_plate_info.met_store_type = g_meter_store_order;
	uint8_t obis[6] = {0,0,99,98,0,255}; // obis code to check lifo fifo
	
	
	memcpy(g_obis_name_plate_info.met_store_type.param_obis_code,obis,6);
	memcpy(g_obis_name_plate_info.met_store_type.param_value,&g_name_plate_info.met_store_type,1);
	sprintf(g_obis_name_plate_info.met_store_type.param_name,"%s","Meter StoreType");
		
	memcpy(np_params_obis_val_info, &g_obis_name_plate_info,sizeof(g_obis_name_plate_info));		
	#if 0
					
					
	/* memcpy(g_np_params_obis_val_info[6].param_obis_code,obis,6);
	memcpy((int*)&g_np_params_obis_val_info[6].param_value,&g_name_plate_info.met_store_type,1);
	sprintf(g_np_params_obis_val_info[6].param_name,"%s","Meter StoreType"); */
	
	//memcpy(name_plate_info, &g_name_plate_info,sizeof(name_plate_info_t));
	
	//params_obis_val_info_t *np_params_obis_val_info 
	memcpy(np_params_obis_val_info, g_np_params_obis_val_info,sizeof(g_np_params_obis_val_info));
	
	#endif
	
	dbg_log(REPORT,"%-20s : Total time taken to proc Name plate details : %ld\n",fun_name,(time(NULL)-curr_time));
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: send_msg_meter()
*Input Parameters 			: comm_fd, buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To send buffer to meter.
********************************************************************************************************/
int32_t send_msg_meter(meter_comm_params_t *meter_comm_params, uint8_t* msg, int32_t len)
{
	static char fun_name[]="send_msg_meter()";
	uint8_t retry=0;
	int32_t ser_read_ret=-1;
	int8_t fun_ret = -1;
	
	//printf("---->>>>Sending Meter Addr : %d, AddrSize : %d\n",g_dlms_met_addr,g_met_addr_size);
	
	memset(g_recv_buff,0,sizeof(g_recv_buff));
	
	for(retry=0; retry<3; retry++)
	{
		memset(g_recv_buff,0,sizeof(g_recv_buff));
		
		if(meter_comm_params->inf_type==INF_SERIAL)
		{
			fun_ret = write_ser_port(meter_comm_params->fd, msg, len);
			if(fun_ret<0)
			{
				dbg_log(REPORT,"%-20s : Write serial failed, Retry Val : %d\n",fun_name,retry+1);
				//send_diag_info(midx,"%-16s : Write serial failed, Retry Val : %d",g_curr_meter_ser_info,retry+1);
				usleep(500000);
				continue;
			}
			else
			{
				dbg_log(INFORM,"%-20s : Num Bytes Write %d\n",fun_name,len);
				print_data(msg, len);
				
				memset(g_recv_buff,0,sizeof(g_recv_buff));
				ser_read_ret = -1;

				fun_ret = ser_read_ret = read_ser_port(meter_comm_params->fd, g_recv_buff, 2);
				if(ser_read_ret<0)
				{
					dbg_log(REPORT,"%-20s : Read serial failed, Retry Val : %d\n",fun_name,retry+1);
					usleep(500000);
					continue;
				}
				else
				{
					dbg_log(INFORM,"%-20s : Num Bytes Read %d\n",fun_name,ser_read_ret);
					print_data(g_recv_buff, ser_read_ret);
					
					fun_ret = proc_read_resp(g_recv_buff, ser_read_ret);
					if(fun_ret<0)
					{
						dbg_log(REPORT,"%-20s : Processing response failed, Retry Val : %d\n",fun_name,retry+1);
						usleep(500000);
						continue;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	
	if(retry<3)
		return RET_SUCCESS;
	else
		return fun_ret;
}

/**************************************************************************************************
*Function 					: send_rr_frame()
*Input Parameters 			: comm_fd, meter address and meter addr size.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To rr frame to meter.
********************************************************************************************************/
int32_t send_rr_frame(meter_comm_params_t *meter_comm_params)
{
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0,ctrl_field=0;
	uint16_t		fcs=0, frm_format=0, frame_len=(0x07)+OFFSET;
	int32_t			send_fun_ret = -1;
	
	memset((void *)g_send_buff, 0, sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	frm_format = FRAME_FORMAT_TYPE | frame_len;
	p_gen_ptr = (uint8_t *)&frm_format;

	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];

	switch(meter_comm_params->meter_addr_format)
	{
		case 1:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;

		case 2:
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		case 4:
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((((meter_comm_params->meter_id)>>7)<<1)&0XFF);
			g_send_buff[idx++] = (((meter_comm_params->meter_id)<<1)|0X01);
		break;

		default:
			g_send_buff[idx++] = meter_comm_params->meter_id=3;
		break;
	}

	g_send_buff[idx++] = g_src_addr;

	ctrl_field = (CTRL_RR_FRAME | POLL_FINAL_BIT);
	ctrl_field |= ( g_recv_seq_num << 5 );
	g_send_buff[idx++] = ctrl_field;

	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF;
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	send_fun_ret = send_msg_meter(meter_comm_params, g_send_buff, idx);
	
	return send_fun_ret;
}

/**************************************************************************************************
*Function 					: get_meter_date_time()
*Input Parameters 			: buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get date time info from buffer and store it into appropriate structure.
********************************************************************************************************/
int32_t get_meter_date_time(uint8_t* msg, int32_t len)
{
	static char fun_name[]="get_meter_date_time()";

	meter_date_time.day = msg[20+OFFSET];
	meter_date_time.month = msg[19+OFFSET];
	meter_date_time.year = (msg[17+OFFSET]<<8)|(msg[18+OFFSET]);
	meter_date_time.hour = msg[22+OFFSET];
	meter_date_time.minute = msg[23+OFFSET];
	meter_date_time.second = msg[24+OFFSET];

	
	dbg_log(INFORM,"%-20s : Current Meter Date Time : %02d_%02d_%04d %02d:%02d:%02d\n",
												fun_name,
												meter_date_time.day,
												meter_date_time.month,
												meter_date_time.year,
												meter_date_time.hour,
												meter_date_time.minute,
												meter_date_time.second
												);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_name_plate_det()
*Input Parameters 			: name plate index.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To get name plate details and store it into appropriate structure.
********************************************************************************************************/
int32_t get_name_plate_det(uint8_t np_idx)
{
	static char fun_name[]="get_name_plate_det()";
	uint8_t num_bytes = 0;
	uint8_t* p_loc_prt = NULL;

	switch(np_idx)
	{
		case 0:
			memset(g_name_plate_info.meter_ser_num,0,32);
			num_bytes = g_recv_buff[16+OFFSET];
			memcpy(g_name_plate_info.meter_ser_num,(char*)&g_recv_buff[17+OFFSET],num_bytes);
			
			printf("111 np_idx : %d\n",np_idx);
			
			memcpy(g_obis_name_plate_info.meter_ser_num.param_obis_code,name_plate_obis[np_idx],6);
			memcpy(g_obis_name_plate_info.meter_ser_num.param_value,&g_name_plate_info.meter_ser_num,num_bytes);
			sprintf(g_obis_name_plate_info.meter_ser_num.param_name,"%s","Meter Serial No");
			
			
			/* memcpy((char*)&g_np_params_obis_val_info[np_idx].param_value,&g_name_plate_info.meter_ser_num,num_bytes);
			printf(">>np_idx : %d\n",np_idx);
			sprintf(g_np_params_obis_val_info[np_idx].param_name,"%s","Meter Serial No");
			printf("np_idx : %d\n",np_idx); */

		break;
		
		case 1:
			memset(g_name_plate_info.manf_name,0,32);
			num_bytes = g_recv_buff[16+OFFSET];
			memcpy(g_name_plate_info.manf_name,(char*)&g_recv_buff[17+OFFSET],num_bytes);
			
			memcpy(g_obis_name_plate_info.manf_name.param_obis_code,name_plate_obis[np_idx],6);
			memcpy(g_obis_name_plate_info.manf_name.param_value,&g_name_plate_info.manf_name,num_bytes);
			sprintf(g_obis_name_plate_info.manf_name.param_name,"%s","Meter MFG Name");
			
			/* memcpy((char*)&g_np_params_obis_val_info[np_idx].param_value,&g_name_plate_info.manf_name,num_bytes);
			sprintf(g_np_params_obis_val_info[np_idx].param_name,"%s","Meter MFG Name"); */
			
			if(strstr(g_name_plate_info.manf_name,"LARSEN AND TOUBRO LIMITED")!=NULL)
			{
				g_meter_mfg_type = LNT_METER_MFG_TYPE;
			}
			else if (strstr("SECURE",g_name_plate_info.manf_name)!=NULL)
			{
				g_meter_mfg_type = SECURE_METER_MFG_TYPE;
			}
			else
			{
				g_meter_mfg_type = 0;
			}
		break;
		
		case 2:
			memset(g_name_plate_info.fw_vwesion,0,32);
			num_bytes = g_recv_buff[16+OFFSET];
			memcpy(g_name_plate_info.fw_vwesion,(char*)&g_recv_buff[17+OFFSET],num_bytes);
			
			memcpy(g_obis_name_plate_info.fw_vwesion.param_obis_code,name_plate_obis[np_idx],6);
			memcpy(g_obis_name_plate_info.fw_vwesion.param_value,&g_name_plate_info.fw_vwesion,num_bytes);
			sprintf(g_obis_name_plate_info.fw_vwesion.param_name,"%s","Meter FW Ver");
			
			
			/* memcpy((char*)&g_np_params_obis_val_info[np_idx].param_value,&g_name_plate_info.fw_vwesion,num_bytes);
			sprintf(g_np_params_obis_val_info[np_idx].param_name,"%s","Meter FW Ver"); */
		break;
		
		case 3:
		case 4:
		case 5:
		{
			uint8_t data_type = g_recv_buff[15+OFFSET];
			switch(data_type)
			{
				case	UNSIGNED_8BIT_TYPE:
					if(np_idx == 3)
					{
						g_name_plate_info.meter_type=g_recv_buff[16+OFFSET];
						
						memcpy(g_obis_name_plate_info.meter_type.param_obis_code,name_plate_obis[np_idx],6);
						memcpy(g_obis_name_plate_info.meter_type.param_value,&g_name_plate_info.meter_type,1);
						sprintf(g_obis_name_plate_info.meter_type.param_name,"%s","Meter Type");
			
						/* memcpy((int*)&g_np_params_obis_val_info[np_idx].param_value,&g_name_plate_info.meter_type,1);
						sprintf(g_np_params_obis_val_info[np_idx].param_name,"%s","Meter Type"); */
						/* if(g_name_plate_info.meter_type == 1)
						{
							g_secure_met_flag = 1;
						} */
					}
					else
					{
						dbg_log(REPORT,"%-20s : Invalid Data Type for np_idx : %d\n",fun_name,np_idx);
						return RET_VAL_OBIS_NP_FAIL;
					}
				break;
				
				case	UNSIGNED_16BIT_TYPE:
					if(np_idx == 4)
						p_loc_prt = (uint8_t*)&g_name_plate_info.int_ct_ratio;
					else if(np_idx == 5)
						p_loc_prt = (uint8_t*)&g_name_plate_info.int_pt_ratio;
					else
					{
						dbg_log(REPORT,"%-20s : Invalid Data Type for np_idx : %d\n",fun_name,np_idx);
						return RET_VAL_OBIS_NP_FAIL;
					}
					p_loc_prt[1]=g_recv_buff[16+OFFSET];
					p_loc_prt[0]=g_recv_buff[17+OFFSET];
					
					
					memcpy(g_obis_name_plate_info.int_ct_ratio.param_obis_code,name_plate_obis[np_idx],6);
					memcpy(g_obis_name_plate_info.int_ct_ratio.param_value,&g_name_plate_info.int_ct_ratio,2);
					sprintf(g_obis_name_plate_info.int_ct_ratio.param_name,"%s","Meter CT Ratio");
						
					memcpy(g_obis_name_plate_info.int_pt_ratio.param_obis_code,name_plate_obis[np_idx],6);
					memcpy(g_obis_name_plate_info.int_pt_ratio.param_value,&g_name_plate_info.int_pt_ratio,2);
					sprintf(g_obis_name_plate_info.int_pt_ratio.param_name,"%s","Meter PT Ratio");
						
						
					/* memcpy((float*)&g_np_params_obis_val_info[np_idx].param_value,&g_name_plate_info.int_ct_ratio,2);
					sprintf(g_np_params_obis_val_info[np_idx].param_name,"%s","Meter CT Ratio");
					
					memcpy((float*)&g_np_params_obis_val_info[np_idx].param_value,&g_name_plate_info.int_pt_ratio,2);
					sprintf(g_np_params_obis_val_info[np_idx].param_name,"%s","Meter PT Ratio"); */
						
				break;
				
				case	UNSIGNED_32BIT_TYPE:
				case	FLOAT_32BIT_TYPE:
					if(np_idx == 4)
						p_loc_prt = (uint8_t*)&g_name_plate_info.int_ct_ratio;
					else if(np_idx == 5)
						p_loc_prt = (uint8_t*)&g_name_plate_info.int_pt_ratio;
					else
					{
						dbg_log(REPORT,"%-20s : Invalid Data Type for np_idx : %d\n",fun_name,np_idx);
						return RET_VAL_OBIS_NP_FAIL;
					}
					p_loc_prt[3]=g_recv_buff[16+OFFSET];
					p_loc_prt[2]=g_recv_buff[17+OFFSET];
					p_loc_prt[1]=g_recv_buff[18+OFFSET];
					p_loc_prt[0]=g_recv_buff[19+OFFSET];
					
					memcpy(g_obis_name_plate_info.int_ct_ratio.param_obis_code,name_plate_obis[np_idx],6);
					memcpy(g_obis_name_plate_info.int_ct_ratio.param_value,&g_name_plate_info.int_ct_ratio,4);
					sprintf(g_obis_name_plate_info.int_ct_ratio.param_name,"%s","Meter CT Ratio");
						
					memcpy(g_obis_name_plate_info.int_pt_ratio.param_obis_code,name_plate_obis[np_idx],6);
					memcpy(g_obis_name_plate_info.int_pt_ratio.param_value,&g_name_plate_info.int_pt_ratio,4);
					sprintf(g_obis_name_plate_info.int_pt_ratio.param_name,"%s","Meter PT Ratio");
					
					/* memcpy((float*)&g_np_params_obis_val_info[np_idx].param_value,&g_name_plate_info.int_ct_ratio,4);
					sprintf(g_np_params_obis_val_info[np_idx].param_name,"%s","Meter CT Ratio");
					
					memcpy((float*)&g_np_params_obis_val_info[np_idx].param_value,&g_name_plate_info.int_pt_ratio,4);
					sprintf(g_np_params_obis_val_info[np_idx].param_name,"%s","Meter PT Ratio"); */
					
				default : break;
			}
		}
		default : break;
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: proc_read_resp()
*Input Parameters 			: buffer nad buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To proccessreceived buffer data.
********************************************************************************************************/
int32_t proc_read_resp(uint8_t* msg, int32_t len)
{
	static char fun_name[]="proc_read_resp()";
	int32_t fun_ret = RET_SUCCESS; 	
	
	fun_ret = validate_met_resp(msg, len);
	if(fun_ret<0)
	{
		return fun_ret;
	}
	
	if((g_query_type!=DISC_TYPE) && (g_query_type!=SNRM_TYPE))
	{
		if(len<9)
		{
			dbg_log(REPORT,"%-20s : Invalid/ Error response came from meter\n",fun_name);
			
			//send_diag_info(midx,"%-16s : Invalid/ Error response came from meter",g_curr_meter_ser_info);
			
			return RET_INCOMP_RESP;
		}
	}
	
	if (( msg[5+OFFSET] & 0x01 ) == 0 )
	{
		uint8_t tot_seq=0, s_send=0;
		tot_seq = msg[5+OFFSET];

		s_send = (tot_seq >> 1 ) & 0x07;
		g_recv_seq_num = (s_send + 1 ) % 8;
		
		//dbg_log(INFORM,"%-20s : tot_seq : %02X Send Seq No : %d stored recv sew num : %02X\n",
		//fun_name, tot_seq, s_send,g_recv_seq_num);
	}
	
	if(((msg[1]&0X08)==0x00) && (g_query_type==BLOCK_VALUES_TYPE))
	{
		g_ls_decode_flag = 1;
	}
	else
	{
		g_ls_decode_flag = 0;
	}
	
	if((g_rr_frame==0) && (g_recv_buff[12+OFFSET]==2) && (g_recv_buff[14+OFFSET]==0))
	{
		memset(g_block_num_det, 0, sizeof(g_block_num_det));
		
		g_block_num_det[3] = g_recv_buff[15+OFFSET];
		g_block_num_det[2] = g_recv_buff[16+OFFSET];
		g_block_num_det[1] = g_recv_buff[17+OFFSET];
		g_block_num_det[0] = g_recv_buff[18+OFFSET];
		
		uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
		
		//dbg_log(INFORM,"%-20s : >>>> RecvBlockVal Details : %d\n",fun_name,*g_block_num_val);
	}
	
	switch(g_query_type)
	{
		case AARQ_TYPE:
			if(len<32+OFFSET)
			{
				dbg_log(REPORT,"%-20s : Invalid Frame receive!!!\n",fun_name);
				fun_ret = RET_AUTH_FAIL;
			}
			
			if(msg[28+OFFSET]!=0)
			{
				dbg_log(REPORT,"%-20s : AARQ Response failed, Meter Password validation failed\n",fun_name);
				
				//send_diag_info(midx,"%-16s : Meter Password validation failed",g_curr_meter_ser_info);
				
				return RET_AUTH_FAIL;
			}
		break;
		
		case DATE_TIME_TYPE:
			if(len<32+OFFSET)
				fun_ret = RET_DT_TIME_FAILED_TYPE;
			else
				fun_ret = get_meter_date_time(msg,len);
		break;
		
		case NAME_PLATE_PARAMS_TYPE:
			fun_ret = get_name_plate_det(g_name_plate_idx);
		break;
		
		case CHECK_LIFO_OR_FIFO:
		{
			g_meter_store_order = 0;
			if( (msg[14+OFFSET] == 0) && (msg[15+OFFSET] == 0x16) && (msg[16+OFFSET] == 0x01) )
			{
				dbg_log(INFORM,"%-20s : Meter storing order is  : LI_FO\n",fun_name);
				g_meter_store_order = LI_FO;
				//g_secure_met_flag = 0;
			}
			else
			{
				dbg_log(INFORM,"%-20s : Meter storing order is  : FI_FO\n",fun_name);
				g_meter_store_order = FI_FO;
				//g_secure_met_flag = 1;
			}
		}
		break;
		
		case INST_SCALE_OBIS_TYPE:
			fun_ret = proc_inst_scalar_obis(msg,len);
		break;
		
		case INST_SCALE_VAL_TYPE:
			fun_ret = proc_inst_scalar_val(msg,len);
		break;
		
		case INST_VALUES_TYPE:
			fun_ret = proc_inst_value(msg,len);
		break;

		case INST_VAL_OBIS_TYPE:
			fun_ret = proc_inst_val_obis(msg,len);
		break;
		
		case BLOCK_VAL_OBIS_TYPE:
			fun_ret = proc_ls_val_obis(msg,len);
		break;
		
		case BLOCK_SCALER_OBIS_TYPE:
			fun_ret = proc_ls_scalar_obis(msg,len);
		break;
		
		case BLOCK_SCALER_VALUE_TYPE:
			fun_ret = proc_ls_scalar_val(msg,len);
		break;

		case BLOCK_VALUES_TYPE:
			if((msg[12+OFFSET]==0X01) && (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X01))
			{
				dbg_log(INFORM,"%-20s : no LS data available for this date qry.\n",fun_name);
				g_no_ls_data_avl_flag = 1;
				fun_ret = 0;
			}
			else
			{
				g_no_ls_data_avl_flag = 0;
				fun_ret = proc_ls_value(msg,len);
			}
			//fun_ret = proc_ls_value(midx,msg,len);
		break;

		case BLOCK_INT_PERIOD_TYPE:
		{
			g_int_period_blk = 0;
			g_num_blocks_blk_data = 0;
			
			g_int_period_blk |= msg[(len-5)] & 0x00FF;
			g_int_period_blk <<= 8;
			g_int_period_blk |= msg[(len-4)] & 0x00FF;
			g_num_blocks_blk_data = (uint8_t) (86400 / g_int_period_blk);
			g_int_period_blk = (g_int_period_blk / 60);
			
			dbg_log(INFORM,"%-20s : Periof interval : %d , Num of Blocks %d\n",
			fun_name,g_int_period_blk,g_num_blocks_blk_data);

			fun_ret = 0;
		}
		
		break;
		
		case EVENT_VALUE_OBIS_TYPE:
			fun_ret = proc_event_val_obis(msg,len);
		break;
		
		case EVENT_SCALER_OBIS_TYPE:
			fun_ret = proc_event_scalar_obis(msg,len);
		break;
		
		case EVENT_SCALER_VALUE_TYPE:
			fun_ret = proc_event_scalar_val(msg,len);
		break;
		
		case EVENT_VALUE_TYPE:
			fun_ret = proc_event_value(msg,len);
		break;
		
		case EVENT_ENTRIES_TYPE:
		{
			g_tot_event_entry = 0;
			
			g_tot_event_entry = msg[len-7]  | (g_tot_event_entry<<8);
			g_tot_event_entry = msg[len-6]  | (g_tot_event_entry<<8);
			g_tot_event_entry = msg[len-5]  | (g_tot_event_entry<<8);
			g_tot_event_entry = msg[len-4]  | (g_tot_event_entry);
			
			dbg_log(INFORM,"%-20s : Total Event entry : %d\n",fun_name,g_tot_event_entry);
			g_max_num_event[g_event_type_idx] = g_tot_event_entry;
			fun_ret = 0;
		}
		break;
		
		case DAILY_VAL_OBIS_TYPE:
			fun_ret = proc_daily_profile_val_obis(msg,len);
		break;
		
		case DAILY_SCALAR_OBIS_TYPE:
			fun_ret = proc_daily_profile_scalar_obis(msg,len);
		break;
		
		case DAILY_SCALAR_VALUE_TYPE:
			fun_ret = proc_daily_profile_scalar_val(msg,len);
		break;
		
		case DAILY_VALUES_TYPE:
			fun_ret = proc_daily_profile_value(msg,len);
		break;
		
		case BILL_ENTRIES_TYPE:
		{
			g_tot_bill_entry = 0;
			
			g_tot_bill_entry = msg[len-7]  | (g_tot_bill_entry<<8);
			g_tot_bill_entry = msg[len-6]  | (g_tot_bill_entry<<8);
			g_tot_bill_entry = msg[len-5]  | (g_tot_bill_entry<<8);
			g_tot_bill_entry = msg[len-4]  | (g_tot_bill_entry);
			
			dbg_log(INFORM,"%-20s : Total Billing entry : %d\n",fun_name,g_tot_bill_entry);
			fun_ret = 0;
		}
		break;
		
		case BILL_VAL_OBIS_TYPE:
			fun_ret = proc_billing_val_obis(msg,len);
		break;
		
		case BILL_SCALER_OBIS_TYPE:
			fun_ret = proc_billing_scalar_obis(msg,len);
		break;
		
		case BILL_SCALER_VALUE_TYPE:
			fun_ret = proc_billing_scalar_val(msg,len);
		break;
		
		case BILL_VALUE_TYPE:
			fun_ret = proc_billing_value(msg,len);
		break;
		
		default : break;
	}
	
	if(((msg[1]&0X08)==0x08) && (msg[12+OFFSET]==0X02)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X00))
	{
		g_rr_frame = 1;
		g_get_nxt_blk = 1;
		g_comp_blk_resp = 0;
		//printf("Setting RR frame and GetNextBlk Frame flag\n");
	}
	
	if(((msg[1]&0X08)==0x08) && (msg[12+OFFSET]==0X02) && (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X01))
	{
		g_rr_frame = 1;
		g_get_nxt_blk = 0;
		g_comp_blk_resp = 0;
	}
	
	if(((msg[1]&0X08)==0x08) && (msg[12+OFFSET]==0X01)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X00))
	{
		g_rr_frame = 1;
		g_get_nxt_blk = 0;
		g_comp_blk_resp = 0;
		//printf("Setting RR frame and Reseting GetNextBlk Frame flag\n");
	}
	
	if(((msg[1]&0X08)==0x00))
	{
		g_rr_frame = 0;
	}
	
	if(((msg[1]&0X08)==0x00) && (msg[12+OFFSET]==0X02)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X01))
	{
		g_rr_frame = 0;
		g_get_nxt_blk = 0;
		g_comp_blk_resp = 0;
	}
	
	if(((msg[1]&0X08)==0x00) && (msg[12+OFFSET]==0X02)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X00))
	{
		g_rr_frame = 0;
		g_get_nxt_blk = 1;
		g_comp_blk_resp = 0;
		//printf("Setting  GetNextBlk Frame flag only\n");
	}
	
	if(((msg[1]&0X08)==0x00) && (msg[12+OFFSET]==0X01)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X00))
	{
		g_rr_frame = 0;
		g_get_nxt_blk = 0;
		g_comp_blk_resp = 0;
		//printf("RESetting  All flag\n");
	}
	
	return fun_ret;
}

/**************************************************************************************************
*Function 					: pppfcs16()
*Input Parameters 			: checks sum, buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To give check sum value.
********************************************************************************************************/
uint16_t pppfcs16 (uint16_t fcs, uint8_t *cp, int32_t len)
{
	while (len--)
		fcs = (fcs >> 8) ^ fcstab[ (fcs ^ *cp++) & 0xFF];

	return fcs;
}

/**************************************************************************************************
*Function 					: validate_met_resp()
*Input Parameters 			: buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To validate buffer data.
********************************************************************************************************/
int32_t validate_met_resp(uint8_t* msg, int32_t len )
{
	static char fun_name[]="validate_met_resp()";
	uint16_t	loc_fcs=0, tmp=0;

	if ( msg[0] != DLMS_START_END_FLAG )
	{
		dbg_log(REPORT,"%-20s : DLMS Start Flag Not Found\n",fun_name);
		//send_diag_info(midx,"%-16s : DLMS Start Flag Not Found",g_curr_meter_ser_info);
		return RET_CRC_FAIL;
	}
	
	if ( msg[len-1] != DLMS_START_END_FLAG )
	{
		dbg_log(REPORT,"%-20s : DLMS End Flag Not Found\n",fun_name);
		//send_diag_info(midx,"%-16s : DLMS End Flag Not Found",g_curr_meter_ser_info);
		return RET_CRC_FAIL;
	}

	loc_fcs = msg[(len-2)];
	loc_fcs <<= 8;
	loc_fcs |= msg[(len-3)] & 0xFF;

	tmp = pppfcs16(PPPINITFCS16, &msg[1], len-4);
	tmp ^= 0xFFFF;
	
	if( loc_fcs != tmp )
	{
		print_data(msg,len);
		dbg_log(REPORT,"%-20s : Header FCS Not Matched, RecvFcs : %02X, CalCulated FCS : %02X\n",fun_name,loc_fcs,tmp);
		//send_diag_info(midx,"%-16s : DLMS Header FCS Not Matched",g_curr_meter_ser_info);
		return RET_CRC_FAIL;
	}

	loc_fcs = msg[7+OFFSET] & 0xFF;
	loc_fcs <<= 8;
	loc_fcs |= msg[6+OFFSET] & 0xFF;

	tmp = pppfcs16(PPPINITFCS16,&msg[1], 5 + OFFSET);
	tmp ^= 0xFFFF;
	
	if( loc_fcs != tmp )
	{
		print_data(msg,len);
		dbg_log(REPORT,"%-20s : Final FCS Not Matched RecvFcs : %02X, CalCulated FCS : %02X\n",fun_name,loc_fcs,tmp);
		//send_diag_info(midx,"%-16s : DLMS Final FCS Not Matched",g_curr_meter_ser_info);
		return RET_CRC_FAIL;
	}

	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: print_data()
*Input Parameters 			: buffer and buffer len.
*Output Parameters 			: None.
*Return	Value				: Success or appropriate error code.
*Description 				: To print buffer data.
********************************************************************************************************/
void print_data(uint8_t* msg, int32_t len)
{
	uint32_t idx=0, frame_cnt=1;
	uint8_t frame_len=16;
	char loc_buff[128],temp_buff[16];

	memset(loc_buff,0,sizeof(loc_buff));
	
	if(len>=1)
	{
		for(idx=0; idx<len; idx++)
		{
			memset(temp_buff,0,sizeof(temp_buff));
			sprintf(temp_buff,"%02X  ",msg[idx]&0xff);
			strcat(loc_buff,temp_buff);
			
			if((frame_cnt*frame_len-1==idx) && (idx>0))
			{
				dbg_log(INFORM,"%s\n",loc_buff);
				frame_cnt++;
				memset(loc_buff,0,sizeof(loc_buff));
			}
		}
		
		dbg_log(INFORM,"%s\n\n",loc_buff);
	}
}

/**************************************************************************************************
*Function 					: get_scaler_mf()
*Input Parameters 			: multiplication factor and value.
*Output Parameters 			: multiplication factor value.
*Return	Value				: Success or appropriate error code.
*Description 				: To get multiplication factor.
********************************************************************************************************/
int32_t get_scaler_mf(int8_t mf,float *mf_val)
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

/* End of File */