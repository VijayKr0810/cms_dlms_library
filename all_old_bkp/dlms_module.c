#include "dlms_module.h"






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

/* Global */
uint8_t						g_raw_data_buff[8*1024];
uint32_t 					g_raw_data_idx,g_meter_mfg_type;
uint8_t 					read_midx,g_pidx,g_od_ls_flag,g_max_num_meter=MAX_NO_OF_METER_PER_PORT;
uint8_t 					g_query_type,g_src_addr=0x41,g_meter_store_order;
char 						loc_buff[1024];
int32_t 					g_ser_read_ret=-1;
uint8_t						g_time_out=2,OFFSET,g_met_addr_size;
uint8_t						g_block_num_det[4];
uint8_t						g_ls_decode_flag;
char 						g_float_str[16];
uint8_t						g_send_buff[256],g_temp_buff[256];
uint8_t						g_recv_buff[1024];
uint8_t						g_no_ls_data_avl_flag[MAX_NO_OF_METER_PER_PORT];
uint8_t 					g_secure_met_flag[MAX_NO_OF_METER_PER_PORT];
int32_t						g_dev_dest_addr[MAX_NO_OF_METER_PER_PORT],g_serial_fd;
uint32_t					g_get_nxt_blk_val[MAX_NO_OF_METER_PER_PORT],g_dlms_met_addr;

uint8_t						g_met_status[MAX_NO_OF_METER_PER_PORT],g_rr_frame[MAX_NO_OF_METER_PER_PORT],
							g_get_nxt_blk[MAX_NO_OF_METER_PER_PORT],g_first_time_resp[MAX_NO_OF_METER_PER_PORT],
							g_comp_blk_resp[MAX_NO_OF_METER_PER_PORT];

uint8_t						g_send_seq_num[MAX_NO_OF_METER_PER_PORT],g_recv_seq_num[MAX_NO_OF_METER_PER_PORT],
							g_name_plate_idx[MAX_NO_OF_METER_PER_PORT],g_event_type_idx[MAX_NO_OF_METER_PER_PORT];

uint8_t						g_recvd_inst_obs[MAX_NO_OF_METER_PER_PORT],g_recvd_ls_obs[MAX_NO_OF_METER_PER_PORT],
							g_recvd_event_obs[MAX_NO_OF_METER_PER_PORT],g_recvd_dp_obs[MAX_NO_OF_METER_PER_PORT];
uint32_t					g_int_period_blk[MAX_NO_OF_METER_PER_PORT],g_num_blocks_blk_data[MAX_NO_OF_METER_PER_PORT];
uint32_t					g_max_num_event[8];

uint8_t						ls_poll_flag[MAX_NO_OF_METER_PER_PORT],
							dp_poll_flag[MAX_NO_OF_METER_PER_PORT],
							event_poll_flag[MAX_NO_OF_METER_PER_PORT];

char						p_comm_port_det[16];
char						p_meter_passwd[MAX_NO_OF_METER_PER_PORT][16];
char						g_ls_data_dir_path[32];

uint8_t 					g_print_ls_flag,g_num_event_param;							
uint8_t  					g_last_num_days=45,g_num_ls_param,g_ls_entry_idx;
uint8_t						g_dp_entry_idx;
uint8_t						g_recvd_np_obs[MAX_NO_OF_METER_PER_PORT];

FILE 						p_ls_file_ptr[MAX_NO_OF_METER_PER_PORT];
time_t						g_last_no_resp_time[MAX_NO_OF_METER_PER_PORT],g_last_hc_send_time;
uint8_t 					g_read_today_ls_file[MAX_NO_OF_METER_PER_PORT];
time_t 						g_last_ls_read_time[MAX_NO_OF_METER_PER_PORT],
							g_last_dp_read_time[MAX_NO_OF_METER_PER_PORT],
							g_last_event_read_time[MAX_NO_OF_METER_PER_PORT];


name_plate_info_t			g_name_plate_info[MAX_NO_OF_METER_PER_PORT];


date_time_t					g_last_met_on_time_info[MAX_NO_OF_METER_PER_PORT];
date_time_t					meter_date_time[MAX_NO_OF_METER_PER_PORT],bill_date_time[MAX_NO_OF_METER_PER_PORT];
date_time_t					g_st_date_time, g_end_date_time;
	

inst_val_info_t					g_inst_data_val[MAX_NO_OF_METER_PER_PORT];
all_ls_data_info_t				all_ls_data_info[MAX_NO_OF_METER_PER_PORT];
//all_events_data_value_t			all_events_data_value[MAX_NO_OF_METER_PER_PORT];
//all_daily_profile_data_value_t	all_daily_profile_data_value[MAX_NO_OF_METER_PER_PORT];


gen_data_val_info_t				gen_data_val_info[80];

gen_params_det_t 				gen_inst_param_det[MAX_NO_OF_METER_PER_PORT];
gen_params_det_t 				gen_ls_param_det[MAX_NO_OF_METER_PER_PORT];
gen_params_det_t 				gen_event_param_det[MAX_NO_OF_METER_PER_PORT];
gen_params_det_t 				gen_bill_param_det[MAX_NO_OF_METER_PER_PORT];
gen_params_det_t 				gen_daily_prof_param_det[MAX_NO_OF_METER_PER_PORT];
	
param_det_t					inst_param_det[80]={
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
										
param_det_t					ls_param_det[32]={
										{ {0,0,1,0,0,255}, "date_time" 	},	{ {1,0,31,27,0,255},"cur_ir"},
										{ {1,0,51,27,0,255},"cur_iy" 	},{ {1,0,71,27,0,255},"cur_ib" 	},
										{ {1,0,32,27,0,255},"volt_r"   	},{ {1,0,52,27,0,255},"volt_y"  },
										{ {1,0,72,27,0,255},"volt_b"   	},{ {1,0,14,27,0,255},"freq"   	},
										{ {1,0,2,29,0,255},"kwh_exp"   	},{ {1,0,1,29,0,255},"kwh_imp"   	},
										{ {1,0,5,29,0,255},"kvarh_lag"   },{ {1,0,8,29,0,255},"kvarh_lead" },
										{ {1,0,10,29,0,255},"kvah_exp"   	},{ {1,0,9,29,0,255},"kvah_imp"   }
};

param_det_t					event_param_det[28]={
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
									{ {0,0,96,11,0,255},"event_code"}
};

param_det_t					daily_profile_param_det[24]={
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
						
/* =================================================================================================== */
/*** Globals ***/
static	char						*p_dbg_msgs[5] = { "[Inform]", "[Warning]", "[Severe]","[Fatal]", "[Report]" };
static	char						g_msg_str[256],g_dbg_buff[256],g_file_path[64];
static	FILE 						*g_modbus_file_ptr[5], *g_io_poll_file_ptr,*g_dlms_file_ptr[5],
									*g_modtcp_file_ptr,*g_iec104s_file_ptr,*g_gprs_file_ptr,
									*g_diag_file_ptr,*g_vpn_pptp_file_ptr,*g_ntp_client_file_ptr,
									*g_vpn_ipsec_file_ptr,*g_mon_proc_file_ptr,*g_dnp3s_file_ptr;

/* =========================================================================== */
int32_t dbg_log(uint8_t proc_id, uint8_t g_pidx, uint8_t g_midx, uint8_t mode, const char *p_format, ...);
FILE* write_dbglog(FILE*p_dbg_fptr_arr, char*g_file_path, char *p_data);
uint32_t 	g_position;

/* ------------------------------------------------------------ */

/*************************************
*Function 		: dbg_log()
*Params 		: 
*Return			: 
*Description 	: 
**************************************/

int32_t dbg_log(uint8_t proc_id, uint8_t g_pidx, uint8_t g_midx, uint8_t mode, const char *p_format, ...)
{
	uint32_t done = 0;
	va_list arg;

	memset(g_dbg_buff,0,sizeof(g_dbg_buff));
	va_start (arg, p_format);
	done = vsprintf ((char *)g_dbg_buff, (const char *)p_format, arg);
	
	time_t		curr_time_sec=0;
	struct tm	*p_curr_time_tm;
	char		time_str[64];
	char		temp_str[8];
	char		file_name[64];

	curr_time_sec = time(NULL);
	p_curr_time_tm = localtime(&curr_time_sec);
	strftime(time_str, 64,"%d_%b_%Y_%H_%M_%S", p_curr_time_tm);
	
	memset(g_msg_str,0,sizeof(g_msg_str));
	strcpy(g_msg_str, time_str);
	strcat(g_msg_str, " : ");
	strcat(g_msg_str, p_dbg_msgs[ mode ]);
	strcat(g_msg_str, " : ");
	
	switch(proc_id)
	{
		case RTU_DLMS:
			strcat(g_msg_str,"Port-");
			memset(temp_str,0,8);
			sprintf(temp_str,"%d",g_pidx);
			strcat(g_msg_str,temp_str);
			strcat(g_msg_str, " : ");
			strcat(g_msg_str,"Meter-");
			memset(temp_str,0,8);
			sprintf(temp_str,"%d",g_midx);
			strcat(g_msg_str,temp_str);
			strcat(g_msg_str, " : ");
		break;
		
		default : break;
	}
	
	strcat(g_msg_str, g_dbg_buff);
	g_msg_str[strlen(g_msg_str)] = 0;
	
	printf("%s",g_msg_str);
	fflush(stdout);
	
	//printf("Before ::: Ptr %p : Pos : %d\n",g_dlms_file_ptr[g_pidx],g_position);
	switch(proc_id)
	{
		case RTU_DLMS:
			memset(file_name,0,sizeof(file_name));
			sprintf(file_name,"%s/cms_dlms_lib.log",CMS_LOG_DIR);
			
			#if DEBUG_LOG
			g_dlms_file_ptr[g_pidx] = write_dbglog(g_dlms_file_ptr[g_pidx], file_name, g_msg_str);
			#endif
			
		break;
		
		default : break;
	}
	
	//printf("After ::: Ptr %p : Pos : %d\n",g_dlms_file_ptr[g_pidx],g_position);
	va_end(arg);
	
	return done;
}

/*************************************
*Function 		: write_dbglog()
*Params 		: 
*Return			: 
*Description 	: 
**************************************/

FILE* write_dbglog(FILE*p_dbg_fptr_arr, char*g_file_path, char *p_data)
{
	uint64_t			position;
	
	if(p_dbg_fptr_arr==NULL)
	{
		p_dbg_fptr_arr = fopen(g_file_path, "w");
		if(p_dbg_fptr_arr == NULL)
		{
			printf("Write Mode open call failed for file : %s , Error : %s\n",g_file_path,strerror(errno));
			return NULL;
		}
	}
	else
	{
		p_dbg_fptr_arr = fopen(g_file_path, "a");
		if(p_dbg_fptr_arr == NULL)
		{
			printf("Append Mode open call failed for file : %s , Error : %s\n",g_file_path,strerror(errno));
			return NULL;
		}
	}
	
	p_data[255] = '\0';
	fprintf(p_dbg_fptr_arr,"%s",p_data);
	fflush(p_dbg_fptr_arr);

	position = ftell(p_dbg_fptr_arr);
	g_position = position;
	
	if(position>=FILE_SIZE_EXCEED)
	{
		printf("Dbg File size reached max.\n");
		if(p_dbg_fptr_arr!=NULL)
		{
			fclose(p_dbg_fptr_arr);
			//perror("fclose:");
		}
		
		p_dbg_fptr_arr = fopen(g_file_path, "w");
		//perror("fopen:");
		if(p_dbg_fptr_arr == NULL)
		{
			printf("open call failed for file : %s , Error : %s\n",g_file_path,strerror(errno));
			return NULL;
		}
	}
	
	fclose(p_dbg_fptr_arr);
	return p_dbg_fptr_arr;
}

/* =================================================================================================== */
int8_t init_serial(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="init_serial()";
	int32_t						serial_fd; //for Communication port
	static tcflag_t				port_speed[SIZE_16] = { 0, B50,B75,B110,B200,B300,B600,B1200,B2400,B4800,B9600, B19200, B38400, B57600, B115200};
	tcflag_t 					baudrate, hw_flow_ctrl, databits, stopbits, parity_on, parity, sw_flow_ctrl;
	uint8_t midx=0;
	
	serport_params_t serport_params;
	
	memset(&serport_params,0,sizeof(serport_params));
	
	memcpy(&serport_params,meter_comm_params->interface_params,sizeof(serport_params));
	
	switch (serport_params.handshake)
	{
		case HW_HANDSHAKE:
			hw_flow_ctrl = CRTSCTS;
			sw_flow_ctrl = 0;
			printf("HW Handshake\n");
			break;
			
		case SW_HANDSHAKE:
			hw_flow_ctrl = 0;
			sw_flow_ctrl = (tcflag_t) (IXON | IXOFF | IXANY);
			printf("SW Handshake\n");
			break;
			
		case NO_HANDSHAKE:
		default:
			hw_flow_ctrl = 0;
			sw_flow_ctrl = 0;
			printf("No Handshake\n");
			break;
	};
	
	// Databits
	switch(serport_params.databits)
	{
		case FIVE_BITS:
			databits = CS5;
			printf("databits 5\n");
			break;
		case SIX_BITS:
			databits = CS6;
			printf("databits 6\n");
			break;
		case SEVEN_BITS:
			databits = CS7;
			printf("databits 7\n");
			break;
		case EIGHT_BITS:
		default:
			databits = CS8;
			printf("databits %d \n",CS8);
			break;
	};

	// Parity
	switch(serport_params.parity)
	{
		case ODD_PARITY: 
				parity_on = PARENB;
				parity   = PARODD;
				printf("Odd parity\n");
				break;
		case EVEN_PARITY: 
				parity_on = PARENB;
				parity   = 0;
				printf("Even parity\n");
				break;
		case NONE_PARITY: 
		default:
				parity_on = 0;
				parity   = 0;
				printf("None parity\n");
				break;
	};

	// stopbits
	switch(serport_params.stopbits)
	{
		case ONE:
		default:
			stopbits = 0;
			printf("One - def stopbits\n");
			break;
			
		case TWO:
			stopbits = CSTOPB;
			printf("Two stopbits\n");
			break;
	};
	
	baudrate = 	port_speed[serport_params.baudrate];

dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : SerPort Param details :: BaudRate : %d FlowCtrl %d sw_flow_ctrl %d DataBits %d Parity %d StopBits %d\n",fun_name,baudrate,hw_flow_ctrl,sw_flow_ctrl,databits,parity,stopbits);

	struct termios		set_termios;
	
	memset((void *)&set_termios, 0, sizeof(struct termios));
	
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Opening Comm Uart Port : %s\n",fun_name,serport_params.ser_port);
	if ( (meter_comm_params->fd = open(serport_params.ser_port, O_RDWR | O_NOCTTY)) == -1)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,FATAL,"%-20s : Serial port open() failed - %s: %s\n",fun_name,serport_params.ser_port, strerror(errno));
		return RET_PORT_OPEN_FAIL;
	}

	// CREAD - enable receiver, CLOCAL - ignore modem ctrl lines
    set_termios.c_cflag = baudrate | hw_flow_ctrl | databits | stopbits | parity | parity_on | CLOCAL | CREAD;

	if (parity_on > 0) // Parity checking to be done
		set_termios.c_iflag = (tcflag_t) (INPCK);
	else
		set_termios.c_iflag = IGNPAR;

	// Enable software flow control, if set
	set_termios.c_iflag |= sw_flow_ctrl;
	set_termios.c_oflag = 0;

    // set input mode (non-canonical, no echo,...) 
	set_termios.c_lflag = 0;
	//printf("cflag %x ciflag %x oflag %x lflag %x\n",set_termios.c_cflag,set_termios.c_iflag,set_termios.c_oflag,set_termios.c_lflag);

	(void)tcflush(meter_comm_params->fd, TCIFLUSH);
	int8_t ret_val;
	
	ret_val=tcsetattr(meter_comm_params->fd,TCSANOW,&set_termios);
	if ( ret_val == -1)
	{
		/* dbg_log(FATAL,"%-25s : Serial port tcsetaddtr() failed - %s\n",fun_name,strerror(errno)); */
		return RET_PORT_OPEN_FAIL;
	}
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : RS232 - COmmunication Port UART Init End\n",fun_name);

	g_serial_fd = meter_comm_params->fd;
	return RET_SUCCESS;
}

int32_t write_ser_port(int32_t serial_fd, uint8_t *msg, int32_t len)
{
	if(write(serial_fd, msg, len)<0)
	{
		return -1;
	}
	
	return 0;
}

int32_t read_ser_port(int32_t serial_fd, uint8_t*trav, uint8_t time_out)
{
	int32_t tot_byte_read=0, byte_present=0, loc_byte_read=0;
	int32_t wait_cnt=0,max_wait_cnt=0,break_cnt = 0;

	max_wait_cnt = (time_out*1000)/50;

	while ( wait_cnt < max_wait_cnt )
	{
		if(ioctl(serial_fd, FIONREAD, &byte_present) == -1)
		{
			printf("read_ser_port ::: ioctl Failed : Error : %s\n",strerror(errno));
			return -1;
		}
	
		if(byte_present > 0)
			break;

		else if(byte_present == 0)
		{
			usleep(50000);
			wait_cnt++;
		}
	}

	if ( wait_cnt == max_wait_cnt )
	{
		printf("Reched Max WaitCount : %d\n",max_wait_cnt);
		return -1;
	}

	printf("Start Recv Data at  WaitCount : %d\n",wait_cnt);
	
	while(1)
	{
		memset(loc_buff, 0, sizeof(loc_buff));
		if((loc_byte_read = read(serial_fd, loc_buff, byte_present)) == -1)
		{
			printf("Failed to read serial\n");
			return -1;
		}

		//memcpy((void *)trav, loc_buff, loc_byte_read);
		//trav += loc_byte_read;
		
		memcpy((void *)&trav[tot_byte_read], loc_buff, loc_byte_read);
		tot_byte_read += loc_byte_read;
		
		//printf("Local Byte reads : %d, Total Bytes Read : %d\n",loc_byte_read,tot_byte_read);
		//printf("0. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
		
		byte_present = 0;
		if(ioctl(serial_fd, FIONREAD, &byte_present) == -1)
		{
			printf("11 read_ser_port ::: ioctl Failed : Error : %s\n",strerror(errno));
			return -1;
		}

		if(byte_present > 0)
		{
			if(tot_byte_read == 1024)
				break;
			else 
				continue;
		}
		else if(byte_present == 0)
		{
			usleep(50000);
			break_cnt = 1;

			//printf("1. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
			while ( wait_cnt < max_wait_cnt )
			{
				if(tot_byte_read>=2)
				//if((break_cnt>=3)||(trav[tot_byte_read-1]==0X7E))
				//if((break_cnt>=3)&&(trav[tot_byte_read-1]==0X7E))
				if((trav[0]==0X7E)&&(trav[tot_byte_read-1]==0X7E))
				{
					if(validate_met_resp(read_midx,trav,tot_byte_read)==-1)
					{
						printf(">>>Inside Inner while recv partial data, need to read more\n");
					}
					else
					{
						printf("Inside Inner while recv total data, breaking loop\n");
						wait_cnt++;
						break;
					}
				}
				
				byte_present = 0;
				if(ioctl(serial_fd, FIONREAD,&byte_present) == -1)
				{
					//printf("22 read_ser_port ::: ioctl Failed : Error : %s\n",strerror(errno));
					return -1;
				}

				if(byte_present > 0)
				{
					//printf("Inside Inner while Some extra bytes aval to read. Breaking inner loop\n");
					wait_cnt++;
					break;
				}
				else
				{
					usleep(50000);
					wait_cnt++;
					break_cnt++;
					continue;
				}
			}
			
			if(tot_byte_read>=2)
			//if((break_cnt>=3)||(trav[tot_byte_read-1]==0X7E))
			//if((break_cnt>=3)&&(trav[tot_byte_read-1]==0X7E))
			//printf("2. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
		
			if((trav[0]==0X7E)&&(trav[tot_byte_read-1]==0X7E))
			{
				if(validate_met_resp(read_midx,trav,tot_byte_read)==-1)
				{
					;//printf("Inside Main while loop recv partial data, need to read more\n");
				}
				else
				{
					//printf("Inside Main while loop recv total data, breaking loop\n");
					wait_cnt++;
					break;
				}
			}
			
			if ( wait_cnt >= max_wait_cnt )
			{
				//printf("Main while loop Reached Max Wait Cnt, breaking loop\n");
				//printf("3. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
				break;
			}
		}
	}
	
	//printf("End Recv Data at  WaitCount : %d, break_cnt : %d\n",wait_cnt,break_cnt);
	
	//printf("4. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
	
	return tot_byte_read;
}

/* ================================================================================================= */
int8_t init_tcp_conn(meter_comm_params_t *meter_comm_params)
{
	return RET_SUCCESS;
}

int32_t create_data_directory(void)
{
	static char fun_name[]="create_data_directory()";
	uint8_t met_dir_idx=0,midx=0;
	char curr_ls_file_path[64];
	struct stat dir_st = {0};
	
	memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
	sprintf(curr_ls_file_path,"%s","DlmsData");
	
	
	if (stat(curr_ls_file_path, &dir_st) == -1) 
	{
		if( (mkdir(curr_ls_file_path,0777) ) < 0 )					
		{
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Created Root ls data dir : %s\n",fun_name,curr_ls_file_path);
		}
	}
	
	for(met_dir_idx=0; met_dir_idx<g_max_num_meter; met_dir_idx++)
	{
		//if(dev_config.channelCfg[g_pidx].meterCfg[met_dir_idx].enableDevice)
		{
			memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
			sprintf(curr_ls_file_path,"%s/M%d",g_ls_data_dir_path,(g_pidx*5 + met_dir_idx+1));
			
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Creating ls data dir : %s\n",fun_name,curr_ls_file_path);
			if (stat(curr_ls_file_path, &dir_st) == -1) 
			{
				mkdir(curr_ls_file_path, 0777);
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Created ls data dir : %s\n",fun_name,curr_ls_file_path);
			}
			
			memset(curr_ls_file_path,0,sizeof(curr_ls_file_path));
			sprintf(curr_ls_file_path,"%s/M%d/od",g_ls_data_dir_path,(g_pidx*5 + met_dir_idx+1));
			
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Creating od ls data dir : %s\n",fun_name,curr_ls_file_path);
			if (stat(curr_ls_file_path, &dir_st) == -1) 
			{
				mkdir(curr_ls_file_path, 0777);
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Created ls od data dir : %s\n",fun_name,curr_ls_file_path);
			}
		}
	}

	return RET_OK;
}

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
	uint8_t midx=0;
	
	strcpy(p_meter_passwd[0],meter_comm_params->meter_pass);
	g_dev_dest_addr[0]=meter_comm_params->meter_id;
	g_met_addr_size = meter_comm_params->meter_addr_format;
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : MetPass : %s, DestAddr : %d, AddrSize : %d\n",
	fun_name,p_meter_passwd[0],g_dev_dest_addr[0],g_met_addr_size); 
	
	strcpy(g_ls_data_dir_path,"./DlmsData");
	
	create_data_directory();
	
	switch(g_met_addr_size)
	{
		case 1:
			OFFSET=0;
			g_dev_dest_addr[0] = 3;
		break;
		
		case 2:
			OFFSET=1;
		break;
		
		case 4:
			OFFSET=3;
		break;
		
		default:
			OFFSET=0;
			g_dev_dest_addr[0] = 3;
		break;
	}
	
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
*Description 				: Sends SNRM and AARQ packets to the meter and get the response.
********************************************************************************************************/
int8_t connect_to_meter(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="connect_to_meter()";
	uint8_t comm_fd, meter_id, meter_type;
	char password[16];
	int8_t ret_val=0,midx=0;
	
	ret_val = send_disc(0);
	if(ret_val<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : DISC Frame Qry  failed\n",fun_name);
		return ret_val;
	}
	
	ret_val = send_snrm(0);
	if(ret_val<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : SNRM Qry  failed\n",fun_name);
		return ret_val;
	}
	
	//ret_val = send_aarq(comm_fd, meter_id, meter_type, password);
	ret_val = send_aarq(0);
	if(ret_val<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : AARQ Qry  failed\n",fun_name);
		return ret_val;
	}
	
	dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Meter connected succfully\n",fun_name);
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: get_nameplate_details()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response structure with all the nameplate details.
*Return	Value				: Success or appropriate error code.
*Description 				: Get the nameplate information of the meter and return the decoded nameplate values in appropriate structure.
********************************************************************************************************/
int8_t get_nameplate_details(name_plate_info_t *name_plate_info)
{
	static char fun_name[]="get_name_plate()";
	uint8_t 	idx = 0;
	float 		p_flt_ptr = 0.0;
	uint16_t  	int_class=0x0001, attr_no=0x0002;
	time_t 		curr_time = time(NULL);
	uint8_t 	midx=0;
	
	if(get_curr_date_time(midx)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get Meter curr date time\n",fun_name); 
		return RET_FAILURE;
	}
	
	for(idx=0; idx<6; idx++)
	{
		g_query_type = NAME_PLATE_PARAMS_TYPE;
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : NAME_PLATE_PARAMS_TYPE : %d\n",fun_name,idx);
		g_name_plate_idx[midx] = idx;
		
		if(send_get_request(midx, int_class, name_plate_obis[idx], 6, attr_no)<0)
		{
			dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get Name plae info for obis : %d,%d,%d,%d,%d,%d\n",
			fun_name,name_plate_obis[idx][0],
			name_plate_obis[idx][1],name_plate_obis[idx][2],
			name_plate_obis[idx][3],name_plate_obis[idx][4],
			name_plate_obis[idx][5]);
			
			continue;
		}
	}
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter Serial Num : %s\n",fun_name,g_name_plate_info[midx].meter_ser_num);
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter MNF Name : %s\n",fun_name,g_name_plate_info[midx].manf_name);
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter FW Name : %s\n",fun_name,g_name_plate_info[midx].fw_vwesion);
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter Type : %d\n",fun_name,g_name_plate_info[midx].meter_type);
	
	memcpy(&p_flt_ptr,&g_name_plate_info[midx].int_ct_ratio,4);
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter CT Ratio : %0.5f\n",fun_name,(p_flt_ptr));
	
	p_flt_ptr = 0.0;
	memcpy(&p_flt_ptr,&g_name_plate_info[midx].int_pt_ratio,4);
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter PT Ratio : %0.5f\n",fun_name,(p_flt_ptr));
		
	if(get_event_entry_order(midx)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get meter storing entry order\n",fun_name);
		
		return RET_FAILURE;
	}
	
	g_name_plate_info[midx].met_store_type = g_meter_store_order;
	
	name_plate_info = (name_plate_info_t*)&g_name_plate_info;
	
	dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Total time taken to proc Name plate details : %ld\n",fun_name,(time(NULL)-curr_time));
	
	return RET_SUCCESS;
}

	
/**************************************************************************************************
*Function 					: get_obis_codes()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: This function does the following tasks
								•	gets values obis code of all the types of data . 
								•	get the scalar obis codes of all the types of data. 
								•	get the scalar 
********************************************************************************************************/
int8_t get_obis_codes(gen_params_det_t *recv_gen_inst_param_det,
gen_params_det_t *recv_gen_ls_param_det,
gen_params_det_t *recv_gen_event_param_det,
gen_params_det_t *recv_gen_bill_param_det,
gen_params_det_t *recv_gen_daily_prof_param_det)
{
	int8_t ret_val = 0;
	
	/* ret_val = get_inst_obis_code_det(0);
	if(ret_val<0)
	{
		return ret_val;
	}
	else
	{
		recv_gen_inst_param_det=(gen_params_det_t*)&gen_inst_param_det[0];
	} */
	
	ret_val = get_ls_obis_code_det(0);
	if(ret_val<0)
	{
		return ret_val;
	}
	else
	{
		recv_gen_ls_param_det=(gen_params_det_t*)&gen_ls_param_det[0];
	}
	
	return RET_OK;
}

/**************************************************************************************************
*Function 					: get_inst_values()
*Input Parameters 			: Structure containing Commn  fd, meter id , password , type of meter.
*Output Parameters 			: Response packet.
*Return	Value				: Success or appropriate error code.
*Description 				: Get the instantaneous data  of the meter and return the decoded values of instantaneous data in appropriate structure
********************************************************************************************************/
int8_t get_inst_values(inst_val_info_t *recv_inst_data_val)
{
	if(get_inst_val(0)<0)
	{
		return RET_INST_VAL_FAILED_TYPE;
	}
	else
	{
		recv_inst_data_val = (inst_val_info_t*)&g_inst_data_val[0];
	}
	
	return 0;
}

int8_t get_curr_date_ls_data(void)
{
	return read_today_ls_data(0);
}

/*************************************************************** Helping Functions************************************************ */
int32_t fill_val_obis_det(uint8_t midx, uint8_t type)
{
	static char fun_name[]="fill_val_obis_det()";
	uint8_t idx=0, jdx=0, data_type=0;
	
	switch(type)
	{
		#if 0
		case DAILY_VAL_OBIS_TYPE:
			idx = 0;
			for(idx=0;idx<gen_daily_prof_param_det[midx].tot_num_val_obis;idx++)
			{
				memcpy(gen_daily_prof_param_det[midx].val_obis[idx],&g_raw_data_buff[(18*idx)+7],6);
			}
			
		break;
		
		case DAILY_SCALAR_OBIS_TYPE:
			idx = 0;
			for(idx=0;idx<gen_daily_prof_param_det[midx].tot_num_scalar;idx++)
			{
				memcpy(gen_daily_prof_param_det[midx].scalar_val[idx].obis_code,&g_raw_data_buff[(18*idx)+7],6);
			}
		break;
		
		case DAILY_SCALAR_VALUE_TYPE:
		{
			uint8_t index =3;
			idx = 0;
			for(idx=0;idx<gen_daily_prof_param_det[midx].tot_num_val_obis;idx++)
			{
				for(jdx=0;jdx<gen_daily_prof_param_det[midx].tot_num_scalar;jdx++)
				{
					if(memcmp(gen_daily_prof_param_det[midx].val_obis[idx],gen_daily_prof_param_det[midx].scalar_val[jdx].obis_code,6)==0)
					{
						gen_daily_prof_param_det[midx].scalar_val[idx].value=g_raw_data_buff[index];
						//printf("%02X, ",g_raw_data_buff[index]);
						index += 6;
						break;
					}
				}
			}
			//printf("\n");
		}
		break;
		
		case DAILY_VALUES_TYPE:
		{
			uint8_t dp_index=0;
			uint32_t index = 0;
			idx = 0;
			
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : tottal num of dp entry : %d\n",fun_name,gen_daily_prof_param_det[midx].tot_num_value);
			
			for(dp_index=0; dp_index<gen_daily_prof_param_det[midx].tot_num_value; dp_index++)
			{
				if(index>=g_raw_data_idx)
				{
					printf(">>>>Reached MAX decode index from raw data\n");
					
					break;
				}
				
				index = index+2;
				printf("Before decode index : %d Value : %X\n",index,g_raw_data_buff[index]);
				
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
				
				if(fill_daily_profile_val(midx, dp_index)<0)
				{
					dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Failed to filled for ls index : %d\n",fun_name,dp_index);
						continue;
				}
			}
		}
		break;
		#endif
		
		case INST_VAL_OBIS_TYPE:
			idx = 0;
			dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Total NumOf Val Obis : %d\n",
			fun_name,gen_inst_param_det[midx].tot_num_val_obis);
			
			for(idx=0;idx<gen_inst_param_det[midx].tot_num_val_obis;idx++)
			{
				memcpy(gen_inst_param_det[midx].val_obis[idx], &g_raw_data_buff[(18*idx)+7], 6);
			}
			
		break;
		
		case INST_SCALE_OBIS_TYPE:
			idx = 0;
			dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Total NumOf Scalar Obis : %d\n",
			fun_name,gen_inst_param_det[midx].tot_num_scalar);
			
			for(idx=0;idx<gen_inst_param_det[midx].tot_num_scalar;idx++)
			{
				memcpy(gen_inst_param_det[midx].scalar_val[idx].obis_code,&g_raw_data_buff[(18*idx)+7],6);
			}
		break;
		
		case INST_SCALE_VAL_TYPE:
		{
			uint8_t index =3;
			idx = 0;
			for(idx=0;idx<gen_inst_param_det[midx].tot_num_val_obis;idx++)
			{
				jdx = 0;
				
				for(jdx=0;jdx<gen_inst_param_det[midx].tot_num_scalar;jdx++)
				{
					if(memcmp(gen_inst_param_det[midx].val_obis[idx],gen_inst_param_det[midx].scalar_val[jdx].obis_code,6)==0)
					{
						gen_inst_param_det[midx].scalar_val[idx].value=g_raw_data_buff[index]&0XFF;
						//gen_inst_param_det[midx].scalar_val[jdx].value=g_raw_data_buff[index];
						
						printf("Idx : %d, Jdx : %d\n",idx,jdx);
						
						print_data(midx,gen_inst_param_det[midx].val_obis[idx],6);
						print_data(midx,gen_inst_param_det[midx].scalar_val[jdx].obis_code,6);
						printf("%02X\t",g_raw_data_buff[index]);
						printf("%02X\n",gen_inst_param_det[midx].scalar_val[idx].value);
						index += 6;
						break;
					}
				}
			}
			printf("\n");
		}
		break;
		
		case INST_VALUES_TYPE:
		{
			uint32_t index =0;
			index = index+2;
			
			idx = 0;
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Tot_num of Inst value : %d\n",fun_name,gen_inst_param_det[midx].tot_num_value);
			
			for(idx=0; idx<gen_inst_param_det[midx].tot_num_value; idx++)
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
			for(idx=0;idx<gen_ls_param_det[midx].tot_num_val_obis;idx++)
			{
				memcpy(gen_ls_param_det[midx].val_obis[idx],&g_raw_data_buff[(18*idx)+7],6);
				//print_data(midx,gen_ls_param_det[midx].val_obis[idx],6);
			}
			
		break;
		
		case BLOCK_SCALER_OBIS_TYPE:
			idx = 0;
			for(idx=0;idx<gen_ls_param_det[midx].tot_num_scalar;idx++)
			{
				memcpy(gen_ls_param_det[midx].scalar_val[idx].obis_code,&g_raw_data_buff[(18*idx)+7],6);
				//print_data(midx,gen_ls_param_det[midx].scalar_val[idx].obis_code,6);
			}
		break;
		
		case BLOCK_SCALER_VALUE_TYPE:
		{
			uint8_t index =3;
			idx = 0;
			
			//printf("-->>>tot_num_val_obis : %d tot_num_scalar : %d\n",gen_ls_param_det[midx].tot_num_val_obis, gen_ls_param_det[midx].tot_num_scalar);
			for(idx=0; idx<gen_ls_param_det[midx].tot_num_val_obis; idx++)
			{
				for(jdx=0; jdx<gen_ls_param_det[midx].tot_num_scalar; jdx++)
				{
					if(memcmp(gen_ls_param_det[midx].val_obis[idx], gen_ls_param_det[midx].scalar_val[jdx].obis_code, 6)==0)
					{
						gen_ls_param_det[midx].scalar_val[idx].value = g_raw_data_buff[index];
						//printf("ParamIdx : %d ScalValue : %02X, ",idx,g_raw_data_buff[index]);
						index += 6;
						break;
					}
				}
			}
			//printf("\n");
		}
		break;
		
		#if 0
		case BLOCK_VALUES_TYPE:
		{
			//print_data(midx,g_raw_data_buff,g_raw_data_idx);
			//printf("-->>>Tot Ls Val : %d, num of param per val : %d g_ls_entry_idx %d g_raw_data_idx %d\n",
			//gen_ls_param_det[midx].tot_num_value,g_num_ls_param,g_ls_entry_idx,g_raw_data_idx);
			
			uint32_t index =0;
			uint8_t ls_index =0;

			for(ls_index=0; ls_index<gen_ls_param_det[midx].tot_num_value; ls_index++)
			{
				//memset(gen_data_val_info,0,sizeof(gen_data_val_info));
				index =index+2;
				//printf("ls_index : %d Before decode index : %d Value : %X\n",ls_index,index,g_raw_data_buff[index]);
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
					//print_data(midx,gen_data_val_info[idx].value,gen_data_val_info[idx].num_bytes);
				}

				//printf("ls_index : %d After decode index : %d\n",ls_index, index);
				
				if(fill_ls_val(midx,ls_index)<0)
				{
					dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Failed to filled for ls index : %d\n",fun_name,ls_index);
						continue;
				}
				else
				{
					//g_ls_entry_idx++;
					//printf("!!!!!!!!!!!!!Filled ls data for ls_entry_idx : %d ls_index : %d \n",g_ls_entry_idx,ls_index);
				}
			}
		}
		break;

		case EVENT_VALUE_OBIS_TYPE:
		{
			for(idx=0;idx<gen_event_param_det[midx].tot_num_val_obis;idx++)
			{
				memcpy(gen_event_param_det[midx].val_obis[idx],&g_raw_data_buff[(18*idx)+7],6);
				//print_data(midx,gen_event_param_det[midx].val_obis[idx],6);
			}
		}
		break;
		
		case EVENT_SCALER_OBIS_TYPE:
		{
			idx = 0;
			//printf("--- Tot num of event scalear : %d\n",gen_event_param_det[midx].tot_num_scalar);
			for(idx=0; idx<gen_event_param_det[midx].tot_num_scalar; idx++)
			{
				memcpy(gen_event_param_det[midx].scalar_val[idx].obis_code,&g_raw_data_buff[(18*idx)+7],6);
				//print_data(midx, gen_event_param_det[midx].scalar_val[idx].obis_code, 6);
			}
		}
		break;
		
		case EVENT_SCALER_VALUE_TYPE:
		{
			uint8_t index =3;
			
			for(idx=0;idx<gen_event_param_det[midx].tot_num_val_obis;idx++)
			{
				for(jdx=0;jdx<gen_event_param_det[midx].tot_num_scalar;jdx++)
				{
					if(memcmp(gen_event_param_det[midx].val_obis[idx],gen_event_param_det[midx].scalar_val[jdx].obis_code,6)==0)
					{
						gen_event_param_det[midx].scalar_val[idx].value=g_raw_data_buff[index];
						//printf("%02X, ",g_raw_data_buff[index]);
						//print_data(midx,&gen_event_param_det[midx].scalar_val[idx].value,1);
						index += 6;
						break;
					}
				}
			}
			//printf("\n");
		}
		break;
		
		case EVENT_VALUE_TYPE:
		{
			//g_num_event_param
			uint32_t index =0;
			uint8_t event_idx =0;

			event_idx = g_event_type_idx[midx];
			
			all_events_data_value[midx].events_type_info[event_idx].num_event = gen_event_param_det[midx].tot_num_value;
			printf("EVENT_VALUE_TYPE : event_idx : %d tot_num_value : %d g_num_event_param : %d\n",
					event_idx,gen_event_param_det[midx].tot_num_value,g_num_event_param);
			
			event_idx = 0;
			
			for(event_idx=0; event_idx<gen_event_param_det[midx].tot_num_value; event_idx++)
			{
				//printf("event_idx : %d Before decode index : %d\n",event_idx,index);
				
				//memset(gen_data_val_info,0,sizeof(gen_data_val_info));
				
				index = index+2;
				//printf("EtypeIdx : %d event_val_idx : %d Before decode index : %d Value : %X g_num_event_param : %d\n",
				//g_event_type_idx[midx],event_idx,index,g_raw_data_buff[index],g_num_event_param);
				
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
				//index = index+2;
				//printf("event_idx : %d After decode index : %d\n",event_idx, index);
				
				if(fill_event_val(midx, event_idx)<0)
				{
					dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Failed to filled for event index : %d\n",fun_name,event_idx);
						continue;
				}
			}
			
		}
			#endif
		break;
		
		default : break;
	}
	
	return RET_OK;
}

int8_t get_ls_obis_code_det(uint8_t midx)
{
	if(get_int_blk_period(midx)<0)
		return RET_VAL_OBIS_LS_FAIL;
	
	static char fun_name[]="get_ls_obis_code_det()";
	uint8_t val_obis[6] = {1,0,99,1,0,255};
	uint16_t  int_class=0x0007, attr_no=0x0003;
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : BLOCK_VAL_OBIS_TYPE\n",fun_name);
	if(get_gen_val_obis(midx, BLOCK_VAL_OBIS_TYPE,int_class,val_obis,6,attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_LS_FAIL;
	}
	
	 val_obis[0] = 1;
	 val_obis[1] = 0;
	 val_obis[2] = 94;
	 val_obis[3] = 91;
	 val_obis[4] = 4;
	 val_obis[5] = 255;
	 
	 int_class=0x0007, attr_no=0x0003;
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : BLOCK_SCALER_OBIS_TYPE\n",fun_name);
	if(get_gen_scalar_obis(midx, BLOCK_SCALER_OBIS_TYPE,int_class,val_obis,6,attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_LS_FAIL;
	}
	
	val_obis[0] = 1;
	val_obis[1] = 0;
	val_obis[2] = 94;
	val_obis[3] = 91;
	val_obis[4] = 4;
	val_obis[5] = 255;
	 
	int_class=0x0007, attr_no=0x0002;
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : BLOCK_SCALER_VALUE_TYPE\n",fun_name);
	if(get_gen_scalar_val(midx, BLOCK_SCALER_VALUE_TYPE,int_class,val_obis,6,attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_LS_FAIL;
	}
	
	return RET_OK;
}

int8_t get_inst_obis_code_det(uint8_t midx)
{
	static char fun_name[]="get_inst_obis_code_det()";
	uint8_t val_obis[6] = {1,0,94,91,0,255};
	uint16_t  int_class=0x0007, attr_no=0x0003;
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : INST_VAL_OBIS_TYPE\n",fun_name);
	if(get_gen_val_obis(midx, INST_VAL_OBIS_TYPE,int_class,val_obis,6,attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	 val_obis[0] = 1;
	 val_obis[1] = 0;
	 val_obis[2] = 94;
	 val_obis[3] = 91;
	 val_obis[4] = 3;
	 val_obis[5] = 255;
	 
	 int_class=0x0007, attr_no=0x0003;
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : INST_SCALE_OBIS_TYPE\n",fun_name);
	if(get_gen_scalar_obis(midx, INST_SCALE_OBIS_TYPE,int_class,val_obis,6,attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	val_obis[0] = 1;
	val_obis[1] = 0;
	val_obis[2] = 94;
	val_obis[3] = 91;
	val_obis[4] = 3;
	val_obis[5] = 255;
	 
	int_class=0x0007, attr_no=0x0002;
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : INST_SCALE_VAL_TYPE\n",fun_name);
	if(get_gen_scalar_val(midx, INST_SCALE_VAL_TYPE,int_class,val_obis,6,attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : failed to get inst val obis code\n",fun_name);
		return RET_VAL_OBIS_INST_FAIL;
	}
	
	return RET_OK;
}

int32_t proc_inst_val_obis(uint8_t midx, uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_inst_val_obis()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp[midx] == 1)
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
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return RET_FAILURE;
		}

		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_inst_param_det[midx].tot_num_val_obis = msg[loc_idx-1];

		g_first_time_resp[midx]=0;
	}
	else
	{
		if(g_rr_frame[midx])
		{
			loc_idx=8+OFFSET;
		}
		else if(g_get_nxt_blk[midx])
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
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen in Getnext block\n",fun_name);
				
				return RET_FAILURE;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_OK;
}

int32_t proc_inst_scalar_obis(uint8_t midx, uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_inst_scalar_obis()";

	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp[midx] == 1)
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
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return RET_FAILURE;
		}
	
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_inst_param_det[midx].tot_num_scalar = msg[loc_idx-1];

		g_first_time_resp[midx]=0;
	}
	else
	{
		if(g_rr_frame[midx])
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk[midx])
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
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return RET_FAILURE;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_OK;
}

int32_t proc_inst_scalar_val(uint8_t midx, uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_inst_scalar_val()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp[midx] == 1)
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
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return RET_FAILURE;
		}
			
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		g_first_time_resp[midx]=0;
	}
	else
	{
		if(g_rr_frame[midx])
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk[midx])
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
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return RET_FAILURE;
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_OK;
}

int32_t proc_inst_value(uint8_t midx, uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_inst_value()";
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp[midx] == 1)
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
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return RET_FAILURE;
			}
		}

		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx+1],len-(loc_idx+3));

		gen_inst_param_det[midx].tot_num_value = msg[loc_idx+1];

		g_first_time_resp[midx]=0;
	}
	else
	{
		if(g_rr_frame[midx])
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk[midx])
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

					dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);

					return RET_FAILURE;
				}
			}
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_OK;
}

int32_t get_inst_val(uint8_t midx)
{
	static char fun_name[]="get_inst_val()";
	
	uint8_t obis[6] = {1,0,94,91,0,255};
	uint16_t  int_class=0x0007, attr_no=0x0002;
	uint8_t temp_nxt_blk_flag = 0;
	
	memset(gen_data_val_info,0,sizeof(gen_data_val_info));
	
	g_rr_frame[midx] = 0;
	g_get_nxt_blk[midx]= 0;
	g_get_nxt_blk_val[midx]=1;
	g_query_type = INST_VALUES_TYPE;
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : INST_VALUES_TYPE\n",fun_name);
	
	g_first_time_resp[midx]=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	
	if(send_get_request(midx, int_class, obis, 6, attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler obis info\n",fun_name);
		return RET_FAILURE;
	}
	
	while(g_rr_frame[midx] || g_get_nxt_blk[midx])
	{
		if(g_get_nxt_blk[midx])
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame[midx])
		{
			if(send_rr_frame(midx)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler value rr frame\n",fun_name);
				return RET_FAILURE;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			//if(send_get_next_blk(midx, g_get_nxt_blk_val[midx])<0)
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(midx, *g_block_num_det)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler value next block frame\n",fun_name);
				g_get_nxt_blk_val[midx]=g_get_nxt_blk_val[midx]+1;
				return RET_FAILURE;
			}
		}
	}
	
	if(fill_val_obis_det(midx, INST_VALUES_TYPE)<0)
		return RET_FAILURE;
	
	if(fill_inst_val(midx)<0)
		return RET_FAILURE;

	//send_inst_data(midx);
	
	return RET_OK;
}

int32_t store_inst_val(uint8_t midx, uint8_t index, float recv_flt_val)
{
	uint8_t idx=0;
	static char fun_name[] = "store_inst_val()";
	
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Index : %d, RecvFltVal : %0.5f\n",fun_name,index,recv_flt_val);
	
	for(idx=0; idx<gen_inst_param_det[midx].tot_num_value; idx++)
	{
		if( (memcmp(gen_inst_param_det[midx].val_obis[index], inst_param_det[idx].obis_code, 6)) == 0)
		{
			if( (memcmp(inst_param_det[idx].param_name,"cur_ir",strlen(inst_param_det[idx].param_name))) == 0)
			{
				g_inst_data_val[midx].cur_ir=recv_flt_val;
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Stored CURIR : %0.5f\n",fun_name,(g_inst_data_val[midx].cur_ir));
				//dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Index : %d Idx : %d recvFltVAl : %0.5f\n",fun_name,index,idx,g_inst_data_val[midx].cur_ir);
			}

			else if( (memcmp(inst_param_det[idx].param_name,"cur_iy",strlen(inst_param_det[idx].param_name))) == 0)
			{
				g_inst_data_val[midx].cur_iy=recv_flt_val;
				//dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Stored CURIY : %0.5f\n",fun_name,(g_inst_data_val[midx].cur_iy));
			}
		
			else if( (memcmp(inst_param_det[idx].param_name,"cur_ib",strlen(inst_param_det[idx].param_name))) == 0)
			{
				g_inst_data_val[midx].cur_ib=recv_flt_val;
				//dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Stored CURIB : %0.5f\n",fun_name,(g_inst_data_val[midx].cur_ib));
			}
			
			else if( (memcmp(inst_param_det[idx].param_name,"volt_r",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].volt_r=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"volt_y",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].volt_y=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"volt_b",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].volt_b=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"pf_r",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].pf_r=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"pf_y",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].pf_y=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"pf_b",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].pf_b=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"pf_avg",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].pf_avg=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"freq",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].freq=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"kva",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].kva=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"kw",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].kw=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"kvar",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].kvar=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"num_pow_fail",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].num_pow_fail=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"cu_pf_dur",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].cu_pf_dur=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"cu_ta_cnt",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].cu_ta_cnt=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"cu_bi_cnt",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].cu_bi_cnt=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"cu_pr_cnt",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].cu_pr_cnt=recv_flt_val;
			
			else if( (memcmp(inst_param_det[idx].param_name,"kwh",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].kwh=recv_flt_val/(float)1000;
			
			else if( (memcmp(inst_param_det[idx].param_name,"kvarh_lag",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].kvarh_lag=recv_flt_val/(float)1000;
			
			else if( (memcmp(inst_param_det[idx].param_name,"kvarh_lead",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].kvarh_lead=recv_flt_val/(float)1000;
			
			else if( (memcmp(inst_param_det[idx].param_name,"kvah",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].kvah=recv_flt_val/(float)1000;
			
			else if( (memcmp(inst_param_det[idx].param_name,"kwmd",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].kwmd=recv_flt_val/(float)1000;
			
			else if( (memcmp(inst_param_det[idx].param_name,"kvamd",strlen(inst_param_det[idx].param_name))) == 0)
				g_inst_data_val[midx].kvamd=recv_flt_val/(float)1000;
		}
	}
	
	return RET_OK;
}

int32_t store_inst_date_time(uint8_t midx, uint8_t index)
{
	uint16_t 	year=0;

	if(memcmp(gen_inst_param_det[midx].val_obis[index],g_date_time_obis,6)==0)
	{
		year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
		meter_date_time[midx].day = g_inst_data_val[midx].date_time.day= gen_data_val_info[index].value[3];
		meter_date_time[midx].month = g_inst_data_val[midx].date_time.month= gen_data_val_info[index].value[2];
		meter_date_time[midx].year = g_inst_data_val[midx].date_time.year =  year;
		meter_date_time[midx].hour = g_inst_data_val[midx].date_time.hour= gen_data_val_info[index].value[5];
		meter_date_time[midx].minute = g_inst_data_val[midx].date_time.minute= gen_data_val_info[index].value[6];
		meter_date_time[midx].second = g_inst_data_val[midx].date_time.second= gen_data_val_info[index].value[7];
		
		return RET_OK;
	}
	else if(memcmp(gen_inst_param_det[midx].val_obis[index],g_date_time_bill_obis,6)==0)
	{
		year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
		bill_date_time[midx].day = g_inst_data_val[midx].bill_date.day= gen_data_val_info[index].value[3];
		bill_date_time[midx].month = g_inst_data_val[midx].bill_date.month= gen_data_val_info[index].value[2];
		bill_date_time[midx].year = g_inst_data_val[midx].bill_date.year =  year;
		bill_date_time[midx].hour = g_inst_data_val[midx].bill_date.hour= gen_data_val_info[index].value[5];
		bill_date_time[midx].minute = g_inst_data_val[midx].bill_date.minute= gen_data_val_info[index].value[6];
		bill_date_time[midx].second = g_inst_data_val[midx].bill_date.second= gen_data_val_info[index].value[7];
								
		return RET_OK;
	}
	else
	{
		return RET_FAILURE;
	}
}

int32_t fill_inst_val(uint8_t midx)
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
	
	for(idx=0; idx<gen_inst_param_det[midx].tot_num_value; idx++)
	{
		//printf("fill_inst_val : Idx : %d , scalar val : %d\n",idx,gen_inst_param_det[midx].scalar_val[idx].value);
		switch(gen_data_val_info[idx].data_type)
		{
			case	FLOAT_32BIT_TYPE:
				p_tmp_str=(int8_t*)&float_temp_val;
				p_tmp_str[3] = gen_data_val_info[idx].value[0];
				p_tmp_str[2] = gen_data_val_info[idx].value[1];
				p_tmp_str[1] = gen_data_val_info[idx].value[2];
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				
				get_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				
				flt_val = (float)((float)float_temp_val * scal_flt_val);
				if(store_inst_val(midx, idx, flt_val) < 0)
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
				
				get_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					flt_val = (float)((float)uint32_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int32_temp_val * scal_flt_val);
				
				if(store_inst_val(midx, idx, flt_val) < 0)
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
				
				get_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					flt_val = (float)((float)uint16_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int16_temp_val * scal_flt_val);
				
				if(store_inst_val(midx, idx, flt_val) < 0)
					continue;

			break;
			
			case UNSIGNED_8BIT_TYPE:
				p_tmp_str=(int8_t*)&uint8_temp_val;
				p_tmp_str[0] = gen_data_val_info[idx].value[3];
				get_scaler_mf(gen_inst_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				flt_val = (float)((float)uint8_temp_val * scal_flt_val);
				
				if(store_inst_val(midx, idx, flt_val) < 0)
					continue;
			break;
			
			case OCTET_STRING_TYPE:
				if(store_inst_date_time(midx, idx)<0)
					continue;

			break;
			
			default : break;
		}
	}
	
#if 1
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : INST TIME STAMP : %02d/%02d/%04d %02d:%02d:%02d\n",fun_name,
											g_inst_data_val[midx].date_time.day,
											g_inst_data_val[midx].date_time.month,
											g_inst_data_val[midx].date_time.year,
											g_inst_data_val[midx].date_time.hour,
											g_inst_data_val[midx].date_time.minute,
											g_inst_data_val[midx].date_time.second);

	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : CURIR : %s\n",fun_name,get_float_str(g_inst_data_val[midx].cur_ir));
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : CURIB : %s\n",fun_name,get_float_str(g_inst_data_val[midx].cur_ib));
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : CURIY : %s\n",fun_name,get_float_str(g_inst_data_val[midx].cur_iy));
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : VOLT1 : %s\n",fun_name,get_float_str(g_inst_data_val[midx].volt_r));
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : VOLT2 : %s\n",fun_name,get_float_str(g_inst_data_val[midx].volt_b));	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : VOLT3 : %s\n",fun_name,get_float_str(g_inst_data_val[midx].volt_y)); 	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : FREQ : %s\n",fun_name,get_float_str(g_inst_data_val[midx].freq)); 	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : PF - R phase : %s\n",fun_name,get_float_str(g_inst_data_val[midx].pf_r)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : PF - B phase : %s\n",fun_name,get_float_str(g_inst_data_val[midx].pf_b)); 	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : PF - Y phase : %s\n",fun_name,get_float_str(g_inst_data_val[midx].pf_y)); 	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : PF 3 phases : %s\n",fun_name,get_float_str(g_inst_data_val[midx].pf_avg)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : App Power KVA : %s\n",fun_name,get_float_str(g_inst_data_val[midx].kva)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Signed Active Power kW : %s\n",fun_name,get_float_str(g_inst_data_val[midx].kw)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Reactive Power kvar : %s\n",fun_name,get_float_str(g_inst_data_val[midx].kvar));	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Num Power Failure : %s\n",fun_name,get_float_str(g_inst_data_val[midx].num_pow_fail)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Cumm Power Failure Duration : %s\n",fun_name,get_float_str(g_inst_data_val[midx].cu_pf_dur));
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Cumm Tamper Count : %s\n",fun_name,get_float_str(g_inst_data_val[midx].cu_ta_cnt)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Cumm Billing Count : %s\n",fun_name,get_float_str(g_inst_data_val[midx].cu_bi_cnt)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Cumm Programming Count : %s\n",fun_name,get_float_str(g_inst_data_val[midx].cu_pr_cnt)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Cumm energy kWh : %s\n",fun_name,get_float_str(g_inst_data_val[midx].kwh)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Cumm energy kvarh Lag : %s\n",fun_name,get_float_str(g_inst_data_val[midx].kvarh_lag)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Cumm energy kvarh : %s\n",fun_name,get_float_str(g_inst_data_val[midx].kvarh_lead)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Cumm energy kVAh : %s\n",fun_name,get_float_str(g_inst_data_val[midx].kvah)); 
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Bill Date stamp : %02d/%02d/%04d %02d:%02d:%02d\n",fun_name,
											bill_date_time[midx].day,
											bill_date_time[midx].month,
											bill_date_time[midx].year,
											bill_date_time[midx].hour,
											bill_date_time[midx].minute,
											bill_date_time[midx].second);
#endif

	return RET_OK;
}

int32_t read_today_ls_data(uint8_t midx )
{
	static char fun_name[]="read_today_ls_data()";
	uint8_t idx=0;
	char	curr_day_file_name[32];
	
	struct tm st_time,time_stamp,next_date_tm;
	time_t time_of_day=0,local_tm=0,next_time_day;
	
	struct stat st;
	
	if(get_curr_date_time(midx)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get Meter curr date time\n",fun_name); 
		return RET_FAILURE;
	}

	memset(&g_st_date_time,0,sizeof(g_st_date_time));
	memset(&g_end_date_time,0,sizeof(g_end_date_time));
	
	g_st_date_time.day = meter_date_time[midx].day;
	g_st_date_time.month = meter_date_time[midx].month;
	g_st_date_time.year = meter_date_time[midx].year;
	g_st_date_time.hour = 0;
	g_st_date_time.minute = 4;
	g_st_date_time.second = 0;
	
	g_end_date_time.day = meter_date_time[midx].day;
	g_end_date_time.month = meter_date_time[midx].month;
	g_end_date_time.year = meter_date_time[midx].year;
	g_end_date_time.hour = meter_date_time[midx].hour;
	g_end_date_time.minute = meter_date_time[midx].minute;
	g_end_date_time.second = 0;
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Getting  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
	g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
	g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Getting  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
	g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
	g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
	
	memset(curr_day_file_name,0,32);
	sprintf(curr_day_file_name,"%s/M%d/%02d_%02d_%04d",
	g_ls_data_dir_path,(((g_pidx)*5)+(midx+1)),g_st_date_time.day,g_st_date_time.month,g_st_date_time.year);
	
/* 	if(check_ls_file_avl(midx,curr_day_file_name)==1)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Already available ls data for date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
		g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
	} */
	
	/* if(stat(curr_day_file_name, &st)==-1) */
		
	dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Removing Current days LS file : %s\n",fun_name,curr_day_file_name);
	
	if(remove(curr_day_file_name)!=0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Failed to Current days LS file, Error : %s, \n",fun_name,strerror(errno));
	}
	
	if(read_ls_data(midx)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get ls data for date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
		g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
		
		return RET_FAILURE;
	}
	else
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Received  ls data for start date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_st_date_time.day,g_st_date_time.month,g_st_date_time.year,
		g_st_date_time.hour,g_st_date_time.minute,g_st_date_time.second);
		
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Received  ls data for end date_time : %02d_%02d_%04d %02d:%02d:%02d\n",fun_name,
		g_end_date_time.day,g_end_date_time.month,g_end_date_time.year,
		g_end_date_time.hour,g_end_date_time.minute,g_end_date_time.second);
	}
		
	//zip_folder(midx);
	
	return RET_OK;
}

int32_t read_ls_data(uint8_t midx)
{
	static char fun_name[]="read_ls_data()";
	
	uint8_t obis[6] = {1,0,99,1,0,255};
	uint16_t  int_class=0x0007, attr_no=0x0001;
	uint8_t temp_nxt_blk_flag = 0;
	
	g_get_nxt_blk_val[midx]=1;
	g_rr_frame[midx] = 0;
	g_get_nxt_blk[midx]= 0;
	
	memset(gen_data_val_info,0,sizeof(gen_data_val_info));
	
	g_first_time_resp[midx]=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	
	g_query_type = BLOCK_VALUES_TYPE;
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : BLOCK_VALUES_TYPE\n",fun_name);
	
	if(send_blk_profile_request(midx, int_class, obis, 6, attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get load survey data\n",fun_name);
		return RET_FAILURE;
	}
	else if(g_no_ls_data_avl_flag[midx]==1)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : No block data available for this date time stamp\n",fun_name);
		return RET_FAILURE;
	}
	
	while(g_rr_frame[midx] || g_get_nxt_blk[midx])
	{
		if(g_get_nxt_blk[midx])
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame[midx])
		{
			if(send_rr_frame(midx)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler value rr frame\n",fun_name);
				return RET_FAILURE;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			//if(send_get_next_blk(midx, g_get_nxt_blk_val[midx])<0)
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(midx, *g_block_num_val)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler value next block frame\n",fun_name);
				return RET_FAILURE;
			}
			temp_nxt_blk_flag=0;
			g_get_nxt_blk_val[midx]=g_get_nxt_blk_val[midx]+1;
		}
	}
	
	return RET_OK;
}

int32_t get_int_blk_period(uint8_t midx)
{
	static char fun_name[]="get_int_blk_period()";
	uint8_t obis[6] = {1,0,0,8,4,255};
	uint16_t  int_class=0x0001, attr_no=0x0002;
	uint8_t temp_nxt_blk_flag = 0;
	
	g_rr_frame[midx] = 0;
	g_get_nxt_blk[midx]= 0;
	g_get_nxt_blk_val[midx]=1;
	g_raw_data_idx = 0;
	g_first_time_resp[midx]=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_query_type = BLOCK_INT_PERIOD_TYPE;
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : BLOCK_INT_PERIOD_TYPE\n",fun_name);
	
	if(send_get_request(midx, int_class, obis, 6, attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get block interval period info\n",fun_name);
		return RET_FAILURE;
	}
	
	while(g_rr_frame[midx] || g_get_nxt_blk[midx])
	{
		if(g_get_nxt_blk[midx])
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame[midx])
		{
			if(send_rr_frame(midx)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get load survey val obis rr frame\n",fun_name);
				return RET_FAILURE;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			//if(send_get_next_blk(midx, g_get_nxt_blk_val[midx])<0)
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(midx, *g_block_num_det)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get block interval period get next frame frame\n",fun_name);
				return RET_FAILURE;
			}
			temp_nxt_blk_flag = 0;
		}
	}
	
	return RET_OK;
}

int32_t proc_ls_val_obis(uint8_t midx, uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_ls_val_obis()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp[midx] == 1)
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
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return RET_FAILURE;
		}
		
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_ls_param_det[midx].tot_num_val_obis = msg[loc_idx-1];

		g_first_time_resp[midx]=0;
	}
	else
	{
		if(g_rr_frame[midx])
		{
			loc_idx=8+OFFSET;
		}
		else if(g_get_nxt_blk[midx])
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
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen in Getnext block\n",fun_name);
				
				return RET_FAILURE;
			}
			
			/* loc_idx=21+OFFSET; */
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	return RET_OK;
}

int32_t proc_ls_scalar_obis(uint8_t midx, uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_ls_scalar_obis()";
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp[midx] == 1)
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
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return RET_FAILURE;
		}
		
		/* loc_idx=17+OFFSET; */

		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		gen_ls_param_det[midx].tot_num_scalar = msg[loc_idx-1];

		g_first_time_resp[midx]=0;
	}
	else
	{
		if(g_rr_frame[midx])
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk[midx])
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
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return RET_FAILURE;
			}
			/* loc_idx=21+OFFSET; */
		}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_OK;
}

int32_t proc_ls_scalar_val(uint8_t midx, uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_ls_scalar_val()";
	
	uint32_t loc_idx=0,idx=0;
	
	if(g_first_time_resp[midx] == 1)
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
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
			
			return RET_FAILURE;
		}
		
		/* loc_idx=19+OFFSET; */

		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : num_of_element : %d First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));

		g_first_time_resp[midx]=0;
	}
	else
	{
		if(g_rr_frame[midx])
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk[midx])
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
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : No start resp stamp seen\n",fun_name);
				
				return RET_FAILURE;
			}
			
				/* loc_idx=21+OFFSET; */
			}
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s :  Resp copied byte : %d, g_raw_data_idx : %d\n",fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	return RET_OK;
}

int32_t proc_ls_value(uint8_t midx, uint8_t* msg, uint32_t len)
{
	static char fun_name[]="proc_ls_value()";
	uint32_t loc_idx=0,idx=0;
	uint32_t index =0;
	uint8_t ls_index =0, data_type = 0;
		
	if((msg[12+OFFSET]==0X01) && (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X01))
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : no LS data available for this date qry.\n",fun_name);
		return 1;
	}
	
	if(g_first_time_resp[midx] == 1)
	{
		for(index=0; index<len; index++)
		{
			//if(((msg[idx]==0X02)&&(msg[idx+2]==0X09)&&(msg[idx+3]==0X0C)) || (((msg[idx]==0X02)&&((msg[idx+2]==0X06)||(msg[idx+2]==0X05)))))
			if((msg[index] == 0X02) && ((msg[index+2] == 0X09)) && ((msg[index+3] == 0X0C)))
			{
				loc_idx = index;
				g_num_ls_param = msg[index+1];
				break;
			}
		}
		
		if(index == len)
		{
			dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : No start stamp seen.\n",fun_name);
			return RET_FAILURE;
		}
		
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Numof ls block : %d, First Time Resp copied byte : %d\n",
		fun_name,msg[loc_idx-1],len-(loc_idx+3));
		
/* 		loc_idx=25+OFFSET;
		{
			gen_ls_param_det[midx].tot_num_value = msg[loc_idx-1];
			g_num_ls_param = msg[26];
			
		} */
		
		g_first_time_resp[midx]=0;
		
	}
	else
	{
		if(g_rr_frame[midx])
		{
			loc_idx=8+OFFSET;
		}
		
		else if(g_get_nxt_blk[midx] || g_comp_blk_resp[midx])
		{
			for(index=0; index<len; index++)
			{
				//if(((msg[idx]==0X02)&&(msg[idx+2]==0X09)&&(msg[idx+3]==0X0C)) || (((msg[idx]==0X02)&&((msg[idx+2]==0X06)||(msg[idx+2]==0X05)))))
				if((msg[index] == 0X02) && ((msg[index+2] == 0X09)) && ((msg[index+3] == 0X0C)))
				{
					loc_idx = index;
					g_num_ls_param = msg[index+1];
					break;
				}
			}
			
			if(index == len)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : No start stamp seen.\n",fun_name);
				return RET_FAILURE;
			}
				/* loc_idx=23+OFFSET; */
			}
		else
			goto EXIT;
	}
	
	memcpy(&g_raw_data_buff[g_raw_data_idx],&msg[loc_idx],(len-(loc_idx+3)));
	g_raw_data_idx = g_raw_data_idx+len-(loc_idx+3);
	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Resp copied byte : %d, g_raw_data_idx : %d\n",
	fun_name,len-(loc_idx+3),g_raw_data_idx);
	
	if(g_ls_decode_flag == 1)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : g_num_ls_param : %d g_raw_data_idx : %d\n",fun_name,g_num_ls_param,g_raw_data_idx);
	
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
			
			if(fill_ls_val(midx,ls_index)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Failed to filled for ls index : %d\n",fun_name,ls_index);
					continue;
			}
		}
		g_raw_data_idx = 0;
	}
	
	EXIT :
	return RET_OK;
}

int32_t send_blk_profile_request(uint8_t midx, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
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

	switch(g_met_addr_size)
	{
		case 1:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;

		case 2:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		case 4:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((g_dlms_met_addr>>7)<<1)&0XFF);
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		default:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;
	}

	g_send_buff[idx++] = g_src_addr;
	
	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num[midx] << 1 );
	g_send_seq_num[midx] = ( g_send_seq_num[midx] + 1 ) % 8;

	ctrl_field |= ( g_recv_seq_num[midx] << 5 );
	
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

	send_fun_ret = send_msg_meter(midx, g_send_buff, idx);
	
	return send_fun_ret;
}

int32_t fill_ls_val(uint8_t midx, uint8_t recv_ls_idx)
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
				
				get_scaler_mf(gen_ls_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				
				flt_val = (float)((float)float_temp_val * scal_flt_val);
				if(store_ls_val(midx, recv_ls_idx, idx, flt_val) < 0)
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
				
				get_scaler_mf(gen_ls_param_det[midx].scalar_val[idx].value,&scal_flt_val);
/* 				printf(":::::::::recv_ls_idx : %d Idx : %d ScalarVal : %d scal_flt_val : %f\n",
				recv_ls_idx,idx,gen_ls_param_det[midx].scalar_val[idx].value,scal_flt_val); */
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_32BIT_TYPE)
					flt_val = (float)((float)uint32_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int32_temp_val * scal_flt_val);
				
				if(store_ls_val(midx, recv_ls_idx, idx, flt_val) < 0)
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
				
				get_scaler_mf(gen_ls_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				
				/* printf("16BIT_TYPE :::::recv_ls_idx : %d Idx : %d ScalarVal : %d scal_flt_val : %f\n",
				recv_ls_idx,idx,gen_ls_param_det[midx].scalar_val[idx].value,scal_flt_val); */
				
				/* printf("p_tmp_str[0] : %X, p_tmp_str[1] : %X p_tmp_str[2] : %X, p_tmp_str[3] : %X\n",
									gen_data_val_info[idx].value[0],
									gen_data_val_info[idx].value[1],
									gen_data_val_info[idx].value[2],
									gen_data_val_info[idx].value[3]); */
				
				if(gen_data_val_info[idx].data_type==UNSIGNED_16BIT_TYPE)
					flt_val = (float)((float)uint16_temp_val * scal_flt_val);
				else
					flt_val = (float)((float)int16_temp_val * scal_flt_val);
				
				if(store_ls_val(midx, recv_ls_idx, idx, flt_val) < 0)
					continue;

			break;
			
			case UNSIGNED_8BIT_TYPE:
				p_tmp_str=(int8_t*)&uint8_temp_val;
				p_tmp_str[0] = gen_data_val_info[idx].value[0];
				get_scaler_mf(gen_ls_param_det[midx].scalar_val[idx].value,&scal_flt_val);
				flt_val = (float)((float)uint8_temp_val * scal_flt_val);
				
				if(store_ls_val(midx, recv_ls_idx, idx, flt_val) < 0)
					continue;
				
			break;
			
			case OCTET_STRING_TYPE:
				if(store_ls_date_time(midx, recv_ls_idx, idx)<0)
					continue;

			break;
			
			default : break;
		}
	}
	
	save_ls_data_file(midx);
	
	return RET_OK;
}

int32_t search_time_entry(uint8_t midx, char* filepath, char* time_entry)
{
	char *p_file_read = NULL;
	struct stat st;
	int32_t		file_fd=0;
	
	if(stat(filepath,&st)==-1)
	{
		return RET_FAILURE;
	}
	else
	{
		file_fd = open(filepath, O_RDONLY);
		if (file_fd == -1) 
		{
			printf("can't open file - %s", filepath);
			return RET_FAILURE;
		}

		p_file_read = (char*)malloc(st.st_size+1);
		if (st.st_size!=read(file_fd, p_file_read, st.st_size)) 
		{
			printf("can't read file - %s", filepath);
			close(file_fd);
			free(p_file_read);
			return RET_FAILURE;
		}
		
		close(file_fd);
		
		p_file_read[st.st_size]='\0';
		
		if ( strstr(p_file_read,time_entry) != NULL )
		{
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"search_time_entry  ::: file_name : %s Time entry : %s found \n",filepath,time_entry);
			free(p_file_read);
			return 1;
		}
	}
	free(p_file_read);
	return RET_OK;
}

int32_t save_ls_data_file(uint8_t midx)
{
	static char fun_name[]="save_ls_data_file()";
	struct stat st;
	char 		curr_ls_file_name[64],time_str[32];
	uint8_t		idx = 0;
	FILE 		*p_ls_file_ptr = NULL;
	uint8_t		fun_ret = 0, avl_file=0;
	
	struct tm st_time,time_stamp;
	time_t time_of_day=0;
	
	memset(curr_ls_file_name,0,sizeof(curr_ls_file_name));
	sprintf(curr_ls_file_name,"%s/M%d/%02d_%02d_%04d",g_ls_data_dir_path,(((g_pidx)*5)+(midx+1)),
									all_ls_data_info[midx].block_val_info[idx].date_time.day,
									all_ls_data_info[midx].block_val_info[idx].date_time.month,
									all_ls_data_info[midx].block_val_info[idx].date_time.year);
	
	printf("1. Currp_file_name : %s\n",curr_ls_file_name);
	
	if(all_ls_data_info[midx].block_val_info[idx].date_time.day==0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Day value can't be Zero.\n",fun_name);
		return RET_FAILURE;
	}
	
	if(g_od_ls_flag == 1)
	{
		//save_od_ls_data_file(midx);
		
		return RET_OK;
	}
	
	if((all_ls_data_info[midx].block_val_info[idx].date_time.hour==0)&&
		(all_ls_data_info[midx].block_val_info[idx].date_time.minute==0))
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : g_meter_mfg_type : %d , No LS data flag status : %d .This is 00:00 entry for Curr file_name : %s\n",
		fun_name,g_meter_mfg_type,g_no_ls_data_avl_flag[midx],curr_ls_file_name);
		
		if(g_meter_mfg_type==LNT_METER_MFG_TYPE)
		{
			if(g_no_ls_data_avl_flag[midx]==1)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : >>>>This entry no need to store in prev day file\n",fun_name);
				
				return RET_OK;
			}
			
			//printf("2. Entry 00:00 Currp_file_name : %s\n",curr_ls_file_name);
			
			st_time.tm_mday = all_ls_data_info[midx].block_val_info[idx].date_time.day;
			st_time.tm_mon =  all_ls_data_info[midx].block_val_info[idx].date_time.month - 1;
			st_time.tm_year = all_ls_data_info[midx].block_val_info[idx].date_time.year - 1900;
			st_time.tm_hour = all_ls_data_info[midx].block_val_info[idx].date_time.hour;
			st_time.tm_min = all_ls_data_info[midx].block_val_info[idx].date_time.minute;
			st_time.tm_sec = all_ls_data_info[midx].block_val_info[idx].date_time.second;
			
			time_of_day = mktime(&st_time);
			time_of_day -= (24*60*60);
			localtime_r(&time_of_day,&time_stamp);

			all_ls_data_info[midx].block_val_info[idx].date_time.hour=23;
			all_ls_data_info[midx].block_val_info[idx].date_time.minute=59;

			memset(curr_ls_file_name,0,sizeof(curr_ls_file_name));
			sprintf(curr_ls_file_name,"%s/M%d/%02d_%02d_%04d",g_ls_data_dir_path,(((g_pidx)*5)+(midx+1)),
								time_stamp.tm_mday,
								time_stamp.tm_mon+1,
								time_stamp.tm_year+1900);
				
			dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : After -1 day Curr file_name : %s\n",fun_name,curr_ls_file_name);		
		}
		
		//printf("3. After -1 day Currp_file_name : %s\n",curr_ls_file_name);
	}
	
	//printf("-->>>>>Before Stat Currp_file_name : %s\n",curr_ls_file_name);
	
	if(stat(curr_ls_file_name,&st)==-1)
	{
		avl_file = 0;
	}
	else
	{
		avl_file = 1;
	}
	
	memset(time_str,0,sizeof(time_str));
	sprintf(time_str,"%02d:%02d",all_ls_data_info[midx].block_val_info[idx].date_time.hour,
								all_ls_data_info[midx].block_val_info[idx].date_time.minute);
	
	fun_ret = search_time_entry(midx,curr_ls_file_name,time_str);
	if(fun_ret == 1)
	{
		return RET_OK;
	}
	
	if(avl_file == 0)
	{
		p_ls_file_ptr = fopen(curr_ls_file_name,"w");
		if(p_ls_file_ptr == NULL)
		{
			dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : File is not opened write mode, Error : %s\n",fun_name,strerror(errno));
			return RET_FAILURE;
		}
		
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Adding Header for new file : %s\n",fun_name,curr_ls_file_name);
		fprintf(p_ls_file_ptr,"TIME\tAI\tRI\tAE\tRE\tkvarhLead\tkvarhLag\tI1\tI2\tI3\tV1\tV2\tV3\tF\n");
		fflush(p_ls_file_ptr);
	}
	else
	{
		p_ls_file_ptr = fopen(curr_ls_file_name,"a");
		if(p_ls_file_ptr == NULL)
		{
			dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : File is not opened Append mode, Error : %s\n",fun_name,strerror(errno));
			return RET_FAILURE;
		}
	}
	
	dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : New time entry found need to store , %02d:%02d \n",
	fun_name,all_ls_data_info[midx].block_val_info[idx].date_time.hour,
	all_ls_data_info[midx].block_val_info[idx].date_time.minute);
	
	fprintf(p_ls_file_ptr,"%02d:%02d\t%0.5f\t%0.5f\t%0.5f\t%0.5f\t%0.5f\t%0.5f\t%0.5f\t%0.5f\t%0.5f\t%0.5f\t%0.5f\t%0.5f\t%0.5f\n",
					all_ls_data_info[midx].block_val_info[idx].date_time.hour,
					all_ls_data_info[midx].block_val_info[idx].date_time.minute,
					all_ls_data_info[midx].block_val_info[idx].kwh_imp,
					all_ls_data_info[midx].block_val_info[idx].kvah_imp,
					all_ls_data_info[midx].block_val_info[idx].kwh_exp,
					all_ls_data_info[midx].block_val_info[idx].kvah_exp,
					all_ls_data_info[midx].block_val_info[idx].kvarh_lead,
					all_ls_data_info[midx].block_val_info[idx].kvarh_lag,
					all_ls_data_info[midx].block_val_info[idx].cur_ir,
					all_ls_data_info[midx].block_val_info[idx].cur_iy,
					all_ls_data_info[midx].block_val_info[idx].cur_ib,
					all_ls_data_info[midx].block_val_info[idx].volt_r,
					all_ls_data_info[midx].block_val_info[idx].volt_y,
					all_ls_data_info[midx].block_val_info[idx].volt_b,
					all_ls_data_info[midx].block_val_info[idx].freq);
	
	fflush(p_ls_file_ptr);
	fclose(p_ls_file_ptr);
	
	//added newly on 28Jan2k20 to support secure meter.
	//sort the entries in time order
	if(g_secure_met_flag[midx]==1)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter storing order is FIFO need to sort the LS file\n",fun_name);
		//sort_ls_file(midx,curr_ls_file_name);
	}
	
	return RET_OK;
}

int32_t store_ls_val(uint8_t midx, uint8_t ls_idx, uint8_t index, float recv_flt_val)
{
	uint8_t idx=0;
	
	//ls_idx = 0;
	//printf("store_ls_val:::: ls_idx : %d Index : %d, Value : %0.5f\n",ls_idx,index,recv_flt_val);
	
	for(idx=0;idx<gen_ls_param_det[midx].tot_num_val_obis;idx++)
	{
		if( (memcmp(gen_ls_param_det[midx].val_obis[index],ls_param_det[idx].obis_code,6)) == 0)
		{
/* 			printf("--->>>>Param Obis and Val Obis matched:: Index : %d Idx : %d g_ls_entry_idx : %d recv_flt_val : %0.5f\n",
			index,idx,g_ls_entry_idx,recv_flt_val); */
			
			if( (memcmp(ls_param_det[idx].param_name,"cur_ir",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].cur_ir=recv_flt_val;
			
			else if( (memcmp(ls_param_det[idx].param_name,"cur_iy",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].cur_iy=recv_flt_val;
			
			else if( (memcmp(ls_param_det[idx].param_name,"cur_ib",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].cur_ib=recv_flt_val;
			
			else if( (memcmp(ls_param_det[idx].param_name,"volt_r",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].volt_r=recv_flt_val;
			
			else if( (memcmp(ls_param_det[idx].param_name,"volt_y",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].volt_y=recv_flt_val;
			
			else if( (memcmp(ls_param_det[idx].param_name,"volt_b",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].volt_b=recv_flt_val;
			
			else if( (memcmp(ls_param_det[idx].param_name,"kwh_imp",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].kwh_imp=recv_flt_val/(float)1000;
			
			else if( (memcmp(ls_param_det[idx].param_name,"kwh_exp",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].kwh_exp=recv_flt_val/(float)1000;
			
			else if( (memcmp(ls_param_det[idx].param_name,"kvarh_lag",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].kvarh_lag=recv_flt_val/(float)1000;
			
			else if( (memcmp(ls_param_det[idx].param_name,"kvarh_lead",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].kvarh_lead=recv_flt_val/(float)1000;
			
			else if( (memcmp(ls_param_det[idx].param_name,"kvah_imp",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].kvah_imp=recv_flt_val/(float)1000;
			
			else if( (memcmp(ls_param_det[idx].param_name,"kvah_exp",strlen(ls_param_det[idx].param_name))) == 0)
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].kvah_exp=recv_flt_val/(float)1000;
			
			else if( (memcmp(ls_param_det[idx].param_name,"freq",strlen(ls_param_det[idx].param_name))) == 0)
			{
				//printf("--->>>>Param Obis and Val Obis matched:: Index : %d Idx : %d g_ls_entry_idx : %d recv_flt_val : %0.5f\n",
					//index,idx,g_ls_entry_idx,recv_flt_val);
				all_ls_data_info[midx].block_val_info[g_ls_entry_idx].freq=recv_flt_val;
			}
			//else
				//printf("Not Matched with anything in load survey params.\n");
		}
	}
	
	return RET_OK;
}

int32_t store_ls_date_time(uint8_t midx, uint8_t ls_idx, uint8_t index)
{
	uint16_t 	year=0;

/* 	printf(" Storing date for ls_idx : %d -->>> %d_%d %02d:%02d \n",ls_idx,
														gen_data_val_info[index].value[3],
														gen_data_val_info[index].value[2],
														gen_data_val_info[index].value[5],
														gen_data_val_info[index].value[6]); */
														
	//if(memcmp(gen_ls_param_det[midx].val_obis[index],g_date_time_obis,6)==0)
	if(1)
	{
		g_ls_entry_idx = 0;
		
		/* g_ls_entry_idx = (gen_data_val_info[index].value[5])*(60/g_int_period_blk[midx]) + (gen_data_val_info[index].value[6]/g_int_period_blk[midx]); */
		
/* 		printf(" Storing date for g_ls_entry_idx : %d -->>> %d_%d %02d:%02d \n",g_ls_entry_idx,
														gen_data_val_info[index].value[3],
														gen_data_val_info[index].value[2],
														gen_data_val_info[index].value[5],
														gen_data_val_info[index].value[6]); */

		year = (gen_data_val_info[index].value[0]<<8)|(gen_data_val_info[index].value[1]);
		all_ls_data_info[midx].block_val_info[g_ls_entry_idx].date_time.day= gen_data_val_info[index].value[3];
		all_ls_data_info[midx].block_val_info[g_ls_entry_idx].date_time.month= gen_data_val_info[index].value[2];
		all_ls_data_info[midx].block_val_info[g_ls_entry_idx].date_time.year =  year;
		all_ls_data_info[midx].block_val_info[g_ls_entry_idx].date_time.hour= gen_data_val_info[index].value[5];
		all_ls_data_info[midx].block_val_info[g_ls_entry_idx].date_time.minute= gen_data_val_info[index].value[6];
		all_ls_data_info[midx].block_val_info[g_ls_entry_idx].date_time.second= 0;
		
/* 		printf("ls_idx ::: %d Stored date %02d-%02d  %02d:%02d \n",ls_idx,
				all_ls_data_info[midx].block_val_info[ls_idx].date_time.day,
				all_ls_data_info[midx].block_val_info[ls_idx].date_time.month,
				all_ls_data_info[midx].block_val_info[ls_idx].date_time.hour,
				all_ls_data_info[midx].block_val_info[ls_idx].date_time.minute
		); */
		
		return RET_OK;
	}
	else
	{
		//printf("Ls date time not matched for ls_idx : %d index : %d\n",ls_idx,index);
		return RET_FAILURE;
	}
}

/* ========================================================================================================= */
int32_t get_gen_scalar_val(uint8_t midx, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
{
	static char fun_name[]="get_inst_scalar_val()";

	uint8_t temp_nxt_blk_flag = 0;
	
	g_rr_frame[midx] = 0;
	g_get_nxt_blk[midx]= 0;
	g_get_nxt_blk_val[midx]=1;
	g_first_time_resp[midx]=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = recv_qry_type;

	if(send_get_request(midx, int_class, obis_code, obis_len, attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler obis info\n",fun_name);
		return RET_FAILURE;
	}
	
	while(g_rr_frame[midx] || g_get_nxt_blk[midx])
	{
		if(g_get_nxt_blk[midx])
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame[midx])
		{
			if(send_rr_frame(midx)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler value rr frame\n",fun_name);
				return RET_FAILURE;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(midx, *g_block_num_det)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler value next block frame\n",fun_name);
				return RET_FAILURE;
			}
		}
	}
	
	if(fill_val_obis_det(midx, recv_qry_type)<0)
		return RET_FAILURE;
	
	return RET_OK;
}

int32_t get_gen_scalar_obis(uint8_t midx, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
{
	static char fun_name[]="get_gen_scalar_obis()";

	uint8_t temp_nxt_blk_flag = 0;
	
	g_rr_frame[midx] = 0;
	g_get_nxt_blk[midx]= 0;
	g_get_nxt_blk_val[midx]=1;
	g_first_time_resp[midx]=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;

	g_query_type = recv_qry_type;
	
	
	if(send_get_request(midx, int_class, obis_code, obis_len, attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler obis info\n",fun_name);
		return RET_FAILURE;
	}
	
	while(g_rr_frame[midx] || g_get_nxt_blk[midx])
	{
		if(g_get_nxt_blk[midx])
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame[midx])
		{
			if(send_rr_frame(midx)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler obis rr frame\n",fun_name);
				return RET_FAILURE;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(midx, *g_block_num_det)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst scaler obis next block frame\n",fun_name);
				return RET_FAILURE;
			}
		}
	}

	if(fill_val_obis_det(midx, recv_qry_type)<0)
		return RET_FAILURE;
	
	return RET_OK;
}

int32_t get_gen_val_obis(uint8_t midx, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
{
	static char fun_name[]="get_inst_val_obis()";
	
	uint8_t temp_nxt_blk_flag = 0;
	
	g_get_nxt_blk_val[midx]=1;
	g_rr_frame[midx] = 0;
	g_get_nxt_blk[midx]= 0;
	
	g_first_time_resp[midx]=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = recv_qry_type;
	
	if(send_get_request(midx, int_class, obis_code, obis_len, attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get val obis info\n",fun_name);
		return RET_FAILURE;
	}
	
	while(g_rr_frame[midx] || g_get_nxt_blk[midx])
	{
		if(g_get_nxt_blk[midx])
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame[midx])
		{
			if(send_rr_frame(midx)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst val obis rr frame\n",fun_name);
				return RET_FAILURE;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(midx, *g_block_num_det)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get inst val obis get next blk frame\n",fun_name);
				return RET_FAILURE;
			}
			temp_nxt_blk_flag=0;
			g_get_nxt_blk_val[midx] = g_get_nxt_blk_val[midx]+1;
		}
	}
	
	if(fill_val_obis_det(midx, recv_qry_type)<0)
		return RET_FAILURE;
	
	return RET_OK;
}

int32_t send_disc(uint8_t midx)
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

	switch(g_met_addr_size)
	{
		case 1:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;

		case 2:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		case 4:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((g_dlms_met_addr>>7)<<1)&0XFF);
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		default:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
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

	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : sending disconnect frame\n",fun_name);
	
	send_fun_ret = send_msg_meter(midx, g_send_buff, idx);
	
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

int32_t send_snrm(uint8_t midx)
{
	static char 	fun_name[] = "send_snrm()";
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0;
	uint16_t		fcs=0, frm_format=0, frame_len=(0x07)+OFFSET;
	int32_t			send_fun_ret = -1;

	g_query_type = SNRM_TYPE;

	memset((void *)g_send_buff, 0, sizeof(g_send_buff));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	frm_format = FRAME_FORMAT_TYPE | frame_len;
	p_gen_ptr = (uint8_t *)&frm_format;

	g_send_buff[idx++] = p_gen_ptr[1];
	g_send_buff[idx++] = p_gen_ptr[0];

	switch(g_met_addr_size)
	{
		case 1:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;

		case 2:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		case 4:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((g_dlms_met_addr>>7)<<1)&0XFF);
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		default:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
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

	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : sending SNRM frame\n",fun_name);
	
	send_fun_ret = send_msg_meter(midx, g_send_buff, idx);
	
	return send_fun_ret;
}

int32_t send_aarq(uint8_t midx)
{
	static char 	fun_name[] = "send_aarq()";
	uint8_t			*p_gen_ptr=NULL;
	uint8_t			idx=0,ctrl_field=0;
	uint16_t		fcs=0, frm_format = 0;
	int32_t			send_fun_ret = -1;
	
	g_query_type = AARQ_TYPE;

	memset((void *)g_send_buff, 0, sizeof(g_send_buff));
	
	//dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : MeterPassword : %s , PassLen : %d\n",fun_name,(p_meter_passwd[midx]),strlen(p_meter_passwd[midx]));
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;

	switch(g_met_addr_size)
	{
		case 1:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;

		case 2:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		case 4:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((g_dlms_met_addr>>7)<<1)&0XFF);
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		default:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;
	}

	g_send_buff[idx++] = g_src_addr;

	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num[midx] << 1 );
	g_send_seq_num[midx] = ( g_send_seq_num[midx] + 1 ) % 8;

	ctrl_field |= ( g_recv_seq_num[midx] << 5 );
	
	g_send_buff[idx++] = ctrl_field;

	g_send_buff[idx++] = 0;
	g_send_buff[idx++] = 0;
	
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0xE6;
	g_send_buff[idx++] = 0x00;

	g_send_buff[idx++] = AARQ_FRAME;

	g_send_buff[idx++] = 46 + strlen(p_meter_passwd[midx]);

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
	g_send_buff[idx++] = 2 + strlen(p_meter_passwd[midx]);
	g_send_buff[idx++] = 0x80;
	g_send_buff[idx++] = strlen(p_meter_passwd[midx]);

	memcpy((void *)&g_send_buff[idx],(const void*)p_meter_passwd[midx],strlen(p_meter_passwd[midx]));
	idx += strlen(p_meter_passwd[midx]);

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

	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : sending AARQ frame\n",fun_name);
	
	send_fun_ret = send_msg_meter(midx, g_send_buff, idx);
	
	return send_fun_ret;
}

int32_t send_get_request(uint8_t midx, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no)
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
	
	switch(g_met_addr_size)
	{
		case 1:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;

		case 2:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		case 4:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((g_dlms_met_addr>>7)<<1)&0XFF);
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		default:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;
	}

	g_send_buff[idx++] = g_src_addr;
	
	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num[midx] << 1 );
	
	g_send_seq_num[midx] = ( g_send_seq_num[midx] + 1 ) % 8;
	ctrl_field |= ( g_recv_seq_num[midx] << 5 );

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

	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : sending get_request frame\n","send_get_request()");
	send_fun_ret = send_msg_meter(midx, g_send_buff, idx);
	
	return send_fun_ret;
}

int32_t send_msg_meter(uint8_t midx, uint8_t* msg, int32_t len)
{
	static char fun_name[]="send_msg_meter()";
	uint8_t retry=0;
	
	//printf("---->>>>Sending Meter Addr : %d, AddrSize : %d\n",g_dlms_met_addr,g_met_addr_size);
	
	memset(g_recv_buff,0,sizeof(g_recv_buff));
	for(retry=0; retry<3; retry++)
	{
		memset(g_recv_buff,0,sizeof(g_recv_buff));
		if(write_ser_port(g_serial_fd, msg, len)<0)
		{
			dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Write serial failed, Retry Val : %d\n",fun_name,retry+1);
			//send_diag_info(midx,"%-16s : Write serial failed, Retry Val : %d",g_curr_meter_ser_info[midx],retry+1);
			usleep(500000);
			continue;
		}
		else
		{
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Num Bytes Write %d\n",fun_name,len);
			print_data(midx, msg, len);
			
			memset(g_recv_buff,0,sizeof(g_recv_buff));
			g_ser_read_ret = -1;
			
			 read_midx = midx; 
			
			g_ser_read_ret = read_ser_port(g_serial_fd, g_recv_buff, g_time_out);
			if(g_ser_read_ret<0)
			{
				g_met_status[midx]=0;
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Read serial failed, Retry Val : %d\n",fun_name,retry+1);
				
				//(midx,"%-16s : Read serial failed, Retry Val : %d",g_curr_meter_ser_info[midx],retry+1);
				
				memset(&g_last_met_on_time_info[midx],0,sizeof(date_time_t));
				memcpy(&g_last_met_on_time_info[midx],&meter_date_time[midx],sizeof(date_time_t));
				usleep(500000);
				continue;
			}
			else
			{
				g_met_status[midx]=1;
				if((time(NULL)-g_last_no_resp_time[midx])>=60*60*1)
				{
					//dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter has not responsed since 1 Hr. enable read_today_ls_file flag \n",fun_name);
					g_read_today_ls_file[midx] = 1;
				}
				else
				{
					//g_read_today_ls_file[midx] = 0;
				}
				
				g_last_no_resp_time[midx] = time(NULL);
				
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Num Bytes Read %d\n",fun_name,g_ser_read_ret);
				print_data(midx, g_recv_buff, g_ser_read_ret);
				
				if(proc_read_resp(midx, g_recv_buff, g_ser_read_ret)<0)
				{
					//send_diag_info(midx,"%-16s : Processing response failed, Retry Val : %d",g_curr_meter_ser_info[midx],retry+1);
					
					dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Processing response failed, Retry Val : %d\n",fun_name,retry+1);
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
	
	if(retry<3)
		return RET_OK;
	else
		return RET_NO_RESP;
}

int32_t get_name_plate_det(uint8_t midx, uint8_t np_idx)
{
	static char fun_name[]="get_name_plate_det()";
	uint8_t num_bytes = 0;
	uint8_t* p_loc_prt = NULL;

	switch(np_idx)
	{
		case 0:
			memset(g_name_plate_info[midx].meter_ser_num,0,32);
			num_bytes = g_recv_buff[16+OFFSET];
			memcpy(g_name_plate_info[midx].meter_ser_num,(char*)&g_recv_buff[17+OFFSET],num_bytes);
			
			//memset(g_curr_meter_ser_info[midx],0,32);
			//strcpy(g_curr_meter_ser_info[midx],g_name_plate_info[midx].meter_ser_num);
		break;
		
		case 1:
			memset(g_name_plate_info[midx].manf_name,0,32);
			num_bytes = g_recv_buff[16+OFFSET];
			memcpy(g_name_plate_info[midx].manf_name,(char*)&g_recv_buff[17+OFFSET],num_bytes);
			
			if(strstr(g_name_plate_info[midx].manf_name,"LARSEN AND TOUBRO LIMITED")!=NULL)
			{
				g_meter_mfg_type = LNT_METER_MFG_TYPE;
			}
			else if (strstr("SECURE",g_name_plate_info[midx].manf_name)!=NULL)
			{
				g_meter_mfg_type = SECURE_METER_MFG_TYPE;
			}
			else
			{
				g_meter_mfg_type = 0;
			}
		break;
		
		case 2:
			memset(g_name_plate_info[midx].fw_vwesion,0,32);
			num_bytes = g_recv_buff[16+OFFSET];
			memcpy(g_name_plate_info[midx].fw_vwesion,(char*)&g_recv_buff[17+OFFSET],num_bytes);
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
						g_name_plate_info[midx].meter_type=g_recv_buff[16+OFFSET];
						/* if(g_name_plate_info[midx].meter_type == 1)
						{
							g_secure_met_flag[midx] = 1;
						} */
					}
					else
					{
						dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Invalid Data Type for np_idx : %d\n",fun_name,np_idx);
						return RET_FAILURE;
					}
				break;
				
				case	UNSIGNED_16BIT_TYPE:
					if(np_idx == 4)
						p_loc_prt = (uint8_t*)&g_name_plate_info[midx].int_ct_ratio;
					else if(np_idx == 5)
						p_loc_prt = (uint8_t*)&g_name_plate_info[midx].int_pt_ratio;
					else
					{
						dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Invalid Data Type for np_idx : %d\n",fun_name,np_idx);
						return RET_FAILURE;
					}
					p_loc_prt[1]=g_recv_buff[16+OFFSET];
					p_loc_prt[0]=g_recv_buff[17+OFFSET];
				break;
				
				case	UNSIGNED_32BIT_TYPE:
				case	FLOAT_32BIT_TYPE:
					if(np_idx == 4)
						p_loc_prt = (uint8_t*)&g_name_plate_info[midx].int_ct_ratio;
					else if(np_idx == 5)
						p_loc_prt = (uint8_t*)&g_name_plate_info[midx].int_pt_ratio;
					else
					{
						dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Invalid Data Type for np_idx : %d\n",fun_name,np_idx);
						return RET_FAILURE;
					}
					p_loc_prt[3]=g_recv_buff[16+OFFSET];
					p_loc_prt[2]=g_recv_buff[17+OFFSET];
					p_loc_prt[1]=g_recv_buff[18+OFFSET];
					p_loc_prt[0]=g_recv_buff[19+OFFSET];
				default : break;
			}
		}
		default : break;
	}
	
	return RET_OK;
}

int32_t get_event_entry_order(uint8_t midx)
{
	static char fun_name[]="get_event_entry_order()";
	
	uint8_t idx=0;
	uint16_t  int_class=0x0007, attr_no=0x0005;
	uint8_t temp_nxt_blk_flag = 0;
	uint8_t obis[6] = {0,0,99,98,0,255};
	
	g_rr_frame[midx] = 0;
	g_get_nxt_blk[midx]= 0;
	g_get_nxt_blk_val[midx]=1;
	g_first_time_resp[midx]=1;
	
	memset(g_raw_data_buff,0,sizeof(g_raw_data_buff));
	g_raw_data_idx = 0;
	g_query_type = CHECK_LIFO_OR_FIFO;
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : CHECK_LIFO_OR_FIFO\n",fun_name);

	if(send_get_request(midx, int_class, obis, 6, attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get event entry data info\n",fun_name);
		return RET_FAILURE;
	}
	
	while(g_rr_frame[midx] || g_get_nxt_blk[midx])
	{
		if(g_get_nxt_blk[midx])
			temp_nxt_blk_flag=1;
		else
			temp_nxt_blk_flag=0;
		
		while(g_rr_frame[midx])
		{
			if(send_rr_frame(midx)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get event entry rr frame\n",fun_name);
				return RET_FAILURE;
			}
		}
		
		if(temp_nxt_blk_flag)
		{
			//if(send_get_next_blk(midx, g_get_nxt_blk_val[midx])<0)
			uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
			if(send_get_next_blk(midx, *g_block_num_det)<0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get event entry get next frame frame\n",fun_name);
				return RET_FAILURE;
			}
		}
	}
	
	return RET_OK;
}

int32_t get_curr_date_time(uint8_t midx)
{
	static char fun_name[]="get_curr_date_time()";
	uint16_t  int_class=0x0008, attr_no=0x0002;
	
	g_query_type = DATE_TIME_TYPE;
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Sending QryType : DATE_TIME_TYPE\n",fun_name);
	
	if(send_get_request(midx, int_class, g_date_time_obis, 6, attr_no)<0)
	{
		dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : failed to get Meter date time info info\n",fun_name);
		return RET_FAILURE;
	}
	
	return RET_OK;
}

int32_t send_get_next_blk(uint8_t midx, uint32_t blk_val)
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

	switch(g_met_addr_size)
	{
		case 1:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;

		case 2:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		case 4:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((g_dlms_met_addr>>7)<<1)&0XFF);
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		default:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;
	}

	g_send_buff[idx++] = g_src_addr;
	
	ctrl_field = I_FRAME | POLL_FINAL_BIT;
	ctrl_field |= ( g_send_seq_num[midx] << 1 );
	g_send_seq_num[midx] = ( g_send_seq_num[midx] + 1 ) % 8;

	ctrl_field |= ( g_recv_seq_num[midx] << 5 );
	
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
	//dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : sending Next block val : %d\n",fun_name,blk_val_data);
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : sending Next block val : %d\n",fun_name,blk_val);
	
	send_fun_ret = send_msg_meter(midx, g_send_buff, idx);
	
	return send_fun_ret;
}

int32_t send_rr_frame(uint8_t midx)
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

	switch(g_met_addr_size)
	{
		case 1:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;

		case 2:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		case 4:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = 0x00;
			g_send_buff[idx++] = 0x02;
			g_send_buff[idx++] = (((g_dlms_met_addr>>7)<<1)&0XFF);
			g_send_buff[idx++] = ((g_dlms_met_addr<<1)|0X01);
		break;

		default:
			g_dlms_met_addr = g_dev_dest_addr[midx];
			g_send_buff[idx++] = g_dlms_met_addr;
		break;
	}

	g_send_buff[idx++] = g_src_addr;

	ctrl_field = (CTRL_RR_FRAME | POLL_FINAL_BIT);
	ctrl_field |= ( g_recv_seq_num[midx] << 5 );
	g_send_buff[idx++] = ctrl_field;

	fcs = pppfcs16(PPPINITFCS16, &g_send_buff[1], idx-1);
	fcs ^= 0xFFFF;
	
	p_gen_ptr = (uint8_t *)&fcs;
	g_send_buff[idx++] = p_gen_ptr[0];
	g_send_buff[idx++] = p_gen_ptr[1];
	
	g_send_buff[idx++] = DLMS_START_END_FLAG;

	send_fun_ret = send_msg_meter(midx, g_send_buff, idx);
	
	return send_fun_ret;
}

int32_t get_meter_date_time(uint8_t midx, uint8_t* msg, int32_t len)
{
	static char fun_name[]="get_meter_date_time()";

	meter_date_time[midx].day = msg[20+OFFSET];
	meter_date_time[midx].month = msg[19+OFFSET];
	meter_date_time[midx].year = (msg[17+OFFSET]<<8)|(msg[18+OFFSET]);
	meter_date_time[midx].hour = msg[22+OFFSET];
	meter_date_time[midx].minute = msg[23+OFFSET];
	meter_date_time[midx].second = msg[24+OFFSET];

	
	dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Current Meter Date Time : %02d_%02d_%04d %02d:%02d:%02d\n",
												fun_name,
												meter_date_time[midx].day,
												meter_date_time[midx].month,
												meter_date_time[midx].year,
												meter_date_time[midx].hour,
												meter_date_time[midx].minute,
												meter_date_time[midx].second
												);
	
	return RET_OK;
}

int32_t validate_met_resp(uint8_t midx, uint8_t* msg, int32_t len )
{
	static char fun_name[]="validate_met_resp()";
	uint16_t	loc_fcs=0, tmp=0;

	if ( msg[0] != DLMS_START_END_FLAG )
	{
		//dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : DLMS Start Flag Not Found\n",fun_name);
		//send_diag_info(midx,"%-16s : DLMS Start Flag Not Found",g_curr_meter_ser_info[midx]);
		return RET_CRC_FAIL;
	}
	
	if ( msg[len-1] != DLMS_START_END_FLAG )
	{
		//dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : DLMS End Flag Not Found\n",fun_name);
		//send_diag_info(midx,"%-16s : DLMS End Flag Not Found",g_curr_meter_ser_info[midx]);
		return RET_CRC_FAIL;
	}

	loc_fcs = msg[(len-2)];
	loc_fcs <<= 8;
	loc_fcs |= msg[(len-3)] & 0xFF;

	tmp = pppfcs16(PPPINITFCS16, &msg[1], len-4);
	tmp ^= 0xFFFF;
	
	if( loc_fcs != tmp )
	{
		//dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Header FCS Not Matched\n",fun_name);
		//send_diag_info(midx,"%-16s : DLMS Header FCS Not Matched",g_curr_meter_ser_info[midx]);
		return RET_CRC_FAIL;
	}

	loc_fcs = msg[7+OFFSET] & 0xFF;
	loc_fcs <<= 8;
	loc_fcs |= msg[6+OFFSET] & 0xFF;

	tmp = pppfcs16(PPPINITFCS16,&msg[1], 5 + OFFSET);
	tmp ^= 0xFFFF;
	
	if( loc_fcs != tmp )
	{
		//dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Final FCS Not Matched\n",fun_name);
		//send_diag_info(midx,"%-16s : DLMS Final FCS Not Matched",g_curr_meter_ser_info[midx]);
		return RET_CRC_FAIL;
	}

	return RET_SUCCESS;
}

int32_t proc_read_resp(uint8_t midx, uint8_t* msg, int32_t len)
{
	static char fun_name[]="proc_read_resp()";
	int32_t fun_ret = RET_OK;
	
	fun_ret = validate_met_resp(midx, msg, len);
	if(fun_ret<0)
	{
		return fun_ret;
	}
	
	if((g_query_type!=DISC_TYPE) && (g_query_type!=SNRM_TYPE))
	{
		if(len<9)
		{
			dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : Invalid/ Error response came from meter\n",fun_name);
			
			//send_diag_info(midx,"%-16s : Invalid/ Error response came from meter",g_curr_meter_ser_info[midx]);
			
			return RET_INCOMP_RESP;
		}
	}
	
	if (( msg[5+OFFSET] & 0x01 ) == 0 )
	{
		uint8_t tot_seq=0, s_send=0;
		tot_seq = msg[5+OFFSET];

		s_send = (tot_seq >> 1 ) & 0x07;
		g_recv_seq_num[midx] = (s_send + 1 ) % 8;
		
		//dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : tot_seq : %02X Send Seq No : %d stored recv sew num : %02X\n",
		//fun_name, tot_seq, s_send,g_recv_seq_num[midx]);
	}
	
	if(((msg[1]&0X08)==0x00) && (g_query_type==BLOCK_VALUES_TYPE))
	{
		g_ls_decode_flag = 1;
	}
	else
	{
		g_ls_decode_flag = 0;
	}
	
	//if( (rrFrameSent==0) && (( recvSerBuffer[14+OFFSET] == 0 ) && (recvSerBuffer[12+OFFSET] == DATA_BLOCK_G ) ) )
/* 	if((g_query_type==BLOCK_VALUES_TYPE)||
		(g_query_type==INST_VALUES_TYPE)||
		(g_query_type==DAILY_VALUES_TYPE)||
		(g_query_type==EVENT_VALUE_TYPE)
		) */
		
	if((g_rr_frame[midx]==0) && (g_recv_buff[12+OFFSET]==2) && (g_recv_buff[14+OFFSET]==0))
	{
		memset(g_block_num_det, 0, sizeof(g_block_num_det));
		
		g_block_num_det[3] = g_recv_buff[15+OFFSET];
		g_block_num_det[2] = g_recv_buff[16+OFFSET];
		g_block_num_det[1] = g_recv_buff[17+OFFSET];
		g_block_num_det[0] = g_recv_buff[18+OFFSET];
		
		uint32_t *g_block_num_val = (uint32_t *)g_block_num_det;
		
		//dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : >>>> RecvBlockVal Details : %d\n",fun_name,*g_block_num_val);
	}
	
	switch(g_query_type)
	{
		case AARQ_TYPE:
			if(len<32+OFFSET)
				fun_ret = RET_AUTH_FAIL;
			
			if(msg[28+OFFSET]!=0)
			{
				dbg_log(RTU_DLMS,g_pidx,midx,REPORT,"%-20s : AARQ Response failed\n",fun_name);
				
				//send_diag_info(midx,"%-16s : Meter Password validation failed",g_curr_meter_ser_info[midx]);
				
				return RET_AUTH_FAIL;
			}
		break;
		
		case DATE_TIME_TYPE:
			if(len<32+OFFSET)
				fun_ret = RET_DT_TIME_FAILED_TYPE;
			else
				fun_ret = get_meter_date_time(midx,msg,len);
		break;
		
		case NAME_PLATE_PARAMS_TYPE:
			fun_ret = get_name_plate_det(midx, g_name_plate_idx[midx]);
		break;
		
		case CHECK_LIFO_OR_FIFO:
		{
			g_meter_store_order = 0;
			if( (msg[14+OFFSET] == 0) && (msg[15+OFFSET] == 0x16) && (msg[16+OFFSET] == 0x01) )
			{
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter storing order is  : LI_FO\n",fun_name);
				g_meter_store_order = LI_FO;
				//g_secure_met_flag[midx] = 0;
			}
			else
			{
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Meter storing order is  : FI_FO\n",fun_name);
				g_meter_store_order = FI_FO;
				//g_secure_met_flag[midx] = 1;
			}
		}
		break;
		
		case INST_SCALE_OBIS_TYPE:
			fun_ret = proc_inst_scalar_obis(midx,msg,len);
		break;
		
		case INST_SCALE_VAL_TYPE:
			fun_ret = proc_inst_scalar_val(midx,msg,len);
		break;
		
		case INST_VALUES_TYPE:
			fun_ret = proc_inst_value(midx,msg,len);
		break;

		case INST_VAL_OBIS_TYPE:
			fun_ret = proc_inst_val_obis(midx,msg,len);
		break;
		case BLOCK_VAL_OBIS_TYPE:
			fun_ret = proc_ls_val_obis(midx,msg,len);
		break;
		
		case BLOCK_SCALER_OBIS_TYPE:
			fun_ret = proc_ls_scalar_obis(midx,msg,len);
		break;
		
		case BLOCK_SCALER_VALUE_TYPE:
			fun_ret = proc_ls_scalar_val(midx,msg,len);
		break;

		case BLOCK_VALUES_TYPE:
			if((msg[12+OFFSET]==0X01) && (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X01))
			{
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : no LS data available for this date qry.\n",fun_name);
				g_no_ls_data_avl_flag[midx] = 1;
				fun_ret = 0;
			}
			else
			{
				g_no_ls_data_avl_flag[midx] = 0;
				fun_ret = proc_ls_value(midx,msg,len);
			}
			//fun_ret = proc_ls_value(midx,msg,len);
		break;

		case BLOCK_INT_PERIOD_TYPE:
		{
			g_int_period_blk[midx] = 0;
			g_num_blocks_blk_data[midx] = 0;
			
			g_int_period_blk[midx] |= msg[(len-5)] & 0x00FF;
			g_int_period_blk[midx] <<= 8;
			g_int_period_blk[midx] |= msg[(len-4)] & 0x00FF;
			g_num_blocks_blk_data[midx] = (uint8_t) (86400 / g_int_period_blk[midx]);
			g_int_period_blk[midx] = (g_int_period_blk[midx] / 60);
			
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Periof interval : %d , Num of Blocks %d\n",
			fun_name,g_int_period_blk[midx],g_num_blocks_blk_data[midx]);

			fun_ret = 0;
		}
		
		break;
		#if 0
		case EVENT_VALUE_OBIS_TYPE:
			fun_ret = proc_event_val_obis(midx,msg,len);
		break;
		
		case EVENT_SCALER_OBIS_TYPE:
			fun_ret = proc_event_scalar_obis(midx,msg,len);
		break;
		
		case EVENT_SCALER_VALUE_TYPE:
			fun_ret = proc_event_scalar_val(midx,msg,len);
		break;
		
		case EVENT_VALUE_TYPE:
			fun_ret = proc_event_value(midx,msg,len);
		break;
	
		case EVENT_ENTRIES_TYPE:
		{
			g_tot_event_entry = 0;
			
			g_tot_event_entry = msg[len-7]  | (g_tot_event_entry<<8);
			g_tot_event_entry = msg[len-6]  | (g_tot_event_entry<<8);
			g_tot_event_entry = msg[len-5]  | (g_tot_event_entry<<8);
			g_tot_event_entry = msg[len-4]  | (g_tot_event_entry);
			
			dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : Total Event entry : %d\n",fun_name,g_tot_event_entry);
			g_max_num_event[g_event_type_idx[midx]] = g_tot_event_entry;
			fun_ret = 0;
		}
		break;
		
		case DAILY_VAL_OBIS_TYPE:
			fun_ret = proc_daily_profile_val_obis(midx,msg,len);
		break;
		
		case DAILY_SCALAR_OBIS_TYPE:
			fun_ret = proc_daily_profile_scalar_obis(midx,msg,len);
		break;
		
		case DAILY_SCALAR_VALUE_TYPE:
			fun_ret = proc_daily_profile_scalar_val(midx,msg,len);
		break;
		
		case DAILY_VALUES_TYPE:
			fun_ret = proc_daily_profile_value(midx,msg,len);
		break;
		
		#endif

		default : break;
	}

	if(((msg[1]&0X08)==0x08) && (msg[12+OFFSET]==0X02)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X00))
	{
		g_rr_frame[midx] = 1;
		g_get_nxt_blk[midx] = 1;
		g_comp_blk_resp[midx] = 0;
		//printf("Setting RR frame and GetNextBlk Frame flag\n");
	}
	
	if(((msg[1]&0X08)==0x08) && (msg[12+OFFSET]==0X02) && (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X01))
	{
		g_rr_frame[midx] = 1;
		g_get_nxt_blk[midx] = 0;
		g_comp_blk_resp[midx] = 0;
	}
	
	if(((msg[1]&0X08)==0x08) && (msg[12+OFFSET]==0X01)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X00))
	{
		g_rr_frame[midx] = 1;
		g_get_nxt_blk[midx] = 0;
		g_comp_blk_resp[midx] = 0;
		//printf("Setting RR frame and Reseting GetNextBlk Frame flag\n");
	}
	
	if(((msg[1]&0X08)==0x00))
	{
		g_rr_frame[midx] = 0;
	}
	
	if(((msg[1]&0X08)==0x00) && (msg[12+OFFSET]==0X02)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X01))
	{
		g_rr_frame[midx] = 0;
		g_get_nxt_blk[midx] = 0;
		g_comp_blk_resp[midx] = 0;
	}
	
	if(((msg[1]&0X08)==0x00) && (msg[12+OFFSET]==0X02)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X00))
	{
		g_rr_frame[midx] = 0;
		g_get_nxt_blk[midx] = 1;
		g_comp_blk_resp[midx] = 0;
		//printf("Setting  GetNextBlk Frame flag only\n");
	}
	
	if(((msg[1]&0X08)==0x00) && (msg[12+OFFSET]==0X01)&& (msg[13+OFFSET]==0X81) && (msg[14+OFFSET]==0X00))
	{
		g_rr_frame[midx] = 0;
		g_get_nxt_blk[midx] = 0;
		g_comp_blk_resp[midx] = 0;
		//printf("RESetting  All flag\n");
	}
	
	//dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%-20s : After Decode resp and setting flag Status, RR frame : %d GetNextBlk : %d\n",fun_name,g_rr_frame[midx],g_get_nxt_blk[midx]);
	
	return fun_ret;
}

uint16_t  pppfcs16 (uint16_t fcs, uint8_t *cp, int32_t len)
{
	while (len--)
		fcs = (fcs >> 8) ^ fcstab[ (fcs ^ *cp++) & 0xFF];

	return fcs;
}

void print_data(uint8_t midx, uint8_t* msg, int32_t len)
{
	#if 1
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
				dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%s\n",loc_buff);
				frame_cnt++;
				memset(loc_buff,0,sizeof(loc_buff));
			}
		}
		
		dbg_log(RTU_DLMS,g_pidx,midx,INFORM,"%s\n\n",loc_buff);
	}
	#endif
}

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

	return RET_OK;
}

char* get_float_str(float recv_flt_val)
{
	int32_t int_val=0, flt_val=0,diff=0;
	
	memset(g_float_str,0,sizeof(g_float_str)); //global buffer
	
	int_val = (int32_t)recv_flt_val;
	flt_val = (int32_t)(recv_flt_val*10000);
	diff = (int32_t)(flt_val-(int_val*10000));
	if( diff<0 )
		diff *= -1;
	
	if( diff>9999 )
		diff = 0;
	
	sprintf(g_float_str,"%d.%04d",int_val,diff);

	return g_float_str;
}

/* End Of File */