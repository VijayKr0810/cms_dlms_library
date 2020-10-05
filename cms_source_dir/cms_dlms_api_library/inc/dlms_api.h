#ifndef	__DLMS_API_H__
#define	__DLMS_API_H__

//#pragma pack(1)

#define DLMS_API_VERSION 			"Dlms_Api_V1.00"
#define INF_SERIAL 					1
#define INF_TCP 					2
#define LNT 1
#define LNT_METER_MFG_TYPE			1
#define SECURE_METER_MFG_TYPE		2
#define LAST_NUM_DAYS_LS_READ 		45
#define OLD_DATA_FILES_TIME 		46

#define 	MAX_EVENT_TYPE			0X07
#define 	MAX_EVENT_NUM 			10

#define 	MAX_BILL_NUM			1

#define 	ROOT_DATA_DIR 			"/usr/cms/data/DlmsData"
#define 	LOG_DIR 				"/usr/cms/log"
#define 	CONFIG_FILE 			"/usr/cms/config/dlms_api_config.cfg"


/* Error Code	Error 	Description*/
typedef enum
{
	RET_SUCCESS = 0,//	Function completed successfully
	RET_NO_RESP = -1,//	Meter didn’t respond
	RET_INCOMP_RESP = -2,//	Incomplete response received
	RET_CRC_FAIL = -3,//	CRC failed
	RET_AUTH_FAIL = -4,//	Authentication failed
	RET_PORT_OPEN_FAIL = -5,//	Failed to open serial port
	RET_ETH_CONN_FAIL = -6,//	Failed to connect to ethernet meter
	RET_DATA_NOT_AVAIL = -7,//	Data not available for the interval requested
	RET_VAL_OBIS_NP_FAIL = -8,//	Failed to get obis code for nameplate values
	RET_VAL_OBIS_INST_FAIL = -9,//	Failed to get obis code for instantaneous values
	RET_VAL_OBIS_LS_FAIL = -10,//	Failed to get obis code for load survey values
	RET_VAL_OBIS_MN_FAIL = -11,//	Failed to get obis code for midnight data values
	RET_VAL_OBIS_BILL_FAIL = -12,//	Failed to get obis code for billing info values
	RET_VAL_OBIS_EVENT_FAIL = -13,//	Failed get obis code for event data values
	RET_SCAL_OBIS_NP_FAIL = -14,//	Failed to get obis code for nameplate scalar values
	RET_SCAL_OBIS_INST_FAIL = -15,//	Failed to get obis code for instantaneous scalar values
	RET_SCAL_OBIS_LS_FAIL = -16,//	Failed to get obis code for load survey scalar values
	RET_SCAL_OBIS_MN_FAIL = -17,//	Failed to get obis code for midnight data scalar values
	RET_SCAL_OBIS_BILL_FAIL = -18, //	Failed to get obis code for billing info scalar values
	RET_SCAL_OBIS_EVENT_FAIL = -19,//	Failed get obis code for event data scalar values
	RET_SCAL_VAL_INST_FAIL = -20,//	Failed to get the scalar values for instantaneous parameters
	RET_SCAL_VAL_LS_FAIL = -21,//	Failed to get the scalar values for load survey parameters
	RET_SCAL_VAL_MN_FAIL = -22,	//Failed to get the scalar values for midnight data parameters
	RET_SCAL_VAL_BILL_FAIL = -23,//	Failed to get the scalar values for billing data parameters
	RET_SCAL_VAL_EVENT_FAIL = -24, //	Failed to get the scalar values for event data parameters
	RET_INVALID_INF_TYPE = -25, //Invalid interface type selected (SERIAL/TCP)
	RET_SNRM_FAILED_TYPE = -26, //Failed to initiate dlms communication.
	RET_DT_TIME_FAILED_TYPE = -27, //Failed to get date time from meter.
	RET_INST_VAL_FAILED_TYPE = -28, //Failed to get inst val from meter.
	RET_SER_PORT_WRITE_FAIL = -29,//	Failed to write on serial port
	RET_SER_PORT_READ_FAIL = -30//	Failed to read from serial port.
} error_type_t;


typedef struct
{	
	char				ser_port[32];
	uint8_t             baudrate;     	// (index)Baudrate of serial port
	uint8_t             databits;      	// Num of databits
	uint8_t             stopbits;      	// Num of stop bits
	uint8_t             parity ;       	// Parity - ODD/EVEN/NONE
	uint8_t             handshake;     	// Handshake - SW/HW/NONE
	uint8_t             infmode;		// RS232 /485
	uint8_t             unused;
	uint8_t             unused1;
}serport_params_t;

typedef struct
{	
	uint8_t 			meter_id;
	uint8_t 			meter_addr_size;
	uint16_t			port;
	uint32_t			meter_addr;
	char				meter_pass[32];
	char				meter_ipaddr[32];
	char				meter_loc[32];
}eth_params_t;

//Structures
typedef struct 
{
	uint8_t			day;
	uint8_t			month;
	uint8_t			hour;
	uint8_t			minute;
	uint8_t			second;
	uint8_t         unused;
	uint16_t		year;
} date_time_t;

typedef struct
{
	uint8_t			inf_type;
	uint8_t			meter_type;
	uint8_t			meter_addr_format;
	uint8_t         unused;
	int32_t 		fd;
	int32_t			meter_id;
	int32_t			inf_params_len;
	date_time_t		from;
	date_time_t		to;
	//void			*interface_params;
	uint8_t			interface_params[128];
	int32_t			other_info1;
	int32_t			other_info2;
	char			filename[SIZE_128]; //file where the big data has to be stored
	char			meter_pass[SIZE_16]; 
	int32_t			resp_len;
	//void			*meter_response;
	uint8_t			meter_response[3000];

}meter_comm_params_t;

typedef struct
{
	uint8_t 		param_obis_code[6];
	char	      	param_name[16];
	char	      	param_value[32];
}param_obis_val_info_t;

typedef struct
{
	param_obis_val_info_t    	meter_ser_num;
	param_obis_val_info_t    	manf_name;
	param_obis_val_info_t    	fw_vwesion;
	param_obis_val_info_t    	meter_type;
	param_obis_val_info_t    	int_ct_ratio;
	param_obis_val_info_t    	int_pt_ratio;
	param_obis_val_info_t    	met_store_type; //LIFO,FIFO
}obis_name_plate_info_t;

typedef struct
{
	char    	meter_ser_num[32];
	char    	manf_name[32];
	char    	fw_vwesion[32];
	int32_t    	meter_type;
	int32_t    	int_ct_ratio;
	int32_t    	int_pt_ratio;
	int32_t    	met_store_type; //LIFO,FIFO
}name_plate_info_t;

typedef struct
{
	date_time_t							date_time;
	param_obis_val_info_t				cur_ir;
	param_obis_val_info_t				cur_iy;
	param_obis_val_info_t				cur_ib;
	param_obis_val_info_t				volt_r;
	param_obis_val_info_t				volt_y;
	param_obis_val_info_t				volt_b;
	param_obis_val_info_t				pf_r;
	param_obis_val_info_t				pf_y;
	param_obis_val_info_t				pf_b;
	param_obis_val_info_t				pf_avg;
	param_obis_val_info_t				freq;
	param_obis_val_info_t				kva;
	param_obis_val_info_t				kw;
	param_obis_val_info_t				kvar;
	param_obis_val_info_t				num_pow_fail;
	param_obis_val_info_t				cu_pf_dur;
	param_obis_val_info_t				cu_ta_cnt;
	param_obis_val_info_t				cu_bi_cnt;
	param_obis_val_info_t				cu_pr_cnt;
	date_time_t							bill_date;
	param_obis_val_info_t				kwh;
	param_obis_val_info_t				kvarh_lag;
	param_obis_val_info_t				kvarh_lead;
	param_obis_val_info_t				kvah;
	param_obis_val_info_t				kwmd;
	param_obis_val_info_t				kvamd;
}inst_val_info_t;

typedef struct 
{
	date_time_t							date_time;
	param_obis_val_info_t				freq;
	param_obis_val_info_t				cur_ir;
	param_obis_val_info_t 				cur_iy;
	param_obis_val_info_t				cur_ib;
	param_obis_val_info_t				volt_r;
	param_obis_val_info_t				volt_y;
	param_obis_val_info_t				volt_b;
	param_obis_val_info_t				kwh_imp;
	param_obis_val_info_t				kwh_exp;
	param_obis_val_info_t				kvarh_lag;
	param_obis_val_info_t				kvarh_lead;
	param_obis_val_info_t				kvah_imp;
	param_obis_val_info_t				kvah_exp;	
} block_val_info_t;

typedef struct
{
	date_time_t							date_time;
	param_obis_val_info_t				event_code;
	param_obis_val_info_t				cur_ir;
	param_obis_val_info_t 				cur_iy;
	param_obis_val_info_t				cur_ib;
	param_obis_val_info_t				volt_r;
	param_obis_val_info_t				volt_y;
	param_obis_val_info_t				volt_b;
	param_obis_val_info_t				kwh;
	param_obis_val_info_t				pf_r;
	param_obis_val_info_t				pf_y;
	param_obis_val_info_t				pf_b;
}event_val_info_t;

typedef struct
{
	uint32_t			num_event;
	event_val_info_t 	event_val_info[16];
	
}events_type_info_t;

typedef struct
{
	events_type_info_t events_type_info[8];
}all_events_data_value_t;

typedef struct
{
	date_time_t							date_time;
	param_obis_val_info_t				kwh_imp;
	param_obis_val_info_t 				kwh_exp;
	param_obis_val_info_t				kvah_imp;
	param_obis_val_info_t				kvah_exp;
	param_obis_val_info_t				react_enhi;
	param_obis_val_info_t				react_enlo;
	param_obis_val_info_t				kvarh_q1;
	param_obis_val_info_t				kvarh_q2;
	param_obis_val_info_t				kvarh_q3;
	param_obis_val_info_t				kvarh_q4;
}daily_profile_val_info_t;

typedef struct
{
	daily_profile_val_info_t daily_profile_val_info[64];
}all_daily_profile_data_value_t;

typedef struct 
{
	date_time_t							date_time;
	param_obis_val_info_t				sys_pf;
	param_obis_val_info_t				kwh;
	param_obis_val_info_t				kwh_tz1;
	param_obis_val_info_t				kwh_tz2;
	param_obis_val_info_t				kwh_tz3;
	param_obis_val_info_t				kwh_tz4;
	param_obis_val_info_t				kwh_tz5;
	param_obis_val_info_t				kwh_tz6;
	param_obis_val_info_t				kwh_tz7;
	param_obis_val_info_t				kwh_tz8;
	param_obis_val_info_t				kvarh_lag;
	param_obis_val_info_t				kvarh_lead;
	param_obis_val_info_t				kvah;
	param_obis_val_info_t				kvah_tz1;
	param_obis_val_info_t				kvah_tz2;
	param_obis_val_info_t				kvah_tz3;
	param_obis_val_info_t				kvah_tz4;
	param_obis_val_info_t				kvah_tz5;
	param_obis_val_info_t				kvah_tz6;
	param_obis_val_info_t				kvah_tz7;
	param_obis_val_info_t				kvah_tz8;
	param_obis_val_info_t				kwmd;
	date_time_t							kwmd_date_time;
	param_obis_val_info_t				kwmd_tz1;
	date_time_t							kwmd_tz1_date_time;
	param_obis_val_info_t				kwmd_tz2;
	date_time_t							kwmd_tz2_date_time;
	param_obis_val_info_t				kwmd_tz3;
	date_time_t							kwmd_tz3_date_time;
	param_obis_val_info_t				kwmd_tz4;
	date_time_t							kwmd_tz4_date_time;
	param_obis_val_info_t				kwmd_tz5;
	date_time_t							kwmd_tz5_date_time;
	param_obis_val_info_t				kwmd_tz6;
	date_time_t							kwmd_tz6_date_time;
	param_obis_val_info_t				kwmd_tz7;
	date_time_t							kwmd_tz7_date_time;
	param_obis_val_info_t				kwmd_tz8;
	date_time_t							kwmd_tz8_date_time;
	param_obis_val_info_t				kvamd;
	date_time_t							kvamd_date_time;
	param_obis_val_info_t				kvamd_tz1;
	date_time_t							kvamd_tz1_date_time;
	param_obis_val_info_t				kvamd_tz2;
	date_time_t							kvamd_tz2_date_time;
	param_obis_val_info_t				kvamd_tz3;
	date_time_t							kvamd_tz3_date_time;
	param_obis_val_info_t				kvamd_tz4;
	date_time_t							kvamd_tz4_date_time;
	param_obis_val_info_t				kvamd_tz5;
	date_time_t							kvamd_tz5_date_time;
	param_obis_val_info_t				kvamd_tz6;
	date_time_t							kvamd_tz6_date_time;
	param_obis_val_info_t				kvamd_tz7;
	date_time_t							kvamd_tz7_date_time;
	param_obis_val_info_t				kvamd_tz8;
	date_time_t							kvamd_tz8_date_time;
}bill_val_info_t;

int8_t init_comm(meter_comm_params_t *meter_comm_params);
int8_t connect_to_meter(meter_comm_params_t *meter_comm_params);
int8_t disconnect_meter(meter_comm_params_t *meter_comm_params);
int8_t get_nameplate_details(meter_comm_params_t *meter_comm_params, obis_name_plate_info_t *np_params_obis_val_info);
int8_t get_ls_values_block_range(meter_comm_params_t *meter_comm_params,uint8_t last_num_blk_read);
int8_t get_ls_values_hour_range(meter_comm_params_t *meter_comm_params,uint8_t last_num_hr_read);
int8_t get_ls_values_day_range(meter_comm_params_t *meter_comm_params,uint8_t last_num_days_read);
int8_t get_event_data_all(meter_comm_params_t *meter_comm_params,uint8_t event_class);
int8_t get_event_data(meter_comm_params_t *meter_comm_params,uint8_t event_class);

int8_t get_midnight_data(meter_comm_params_t *meter_comm_params);
int8_t get_midnight_data_all(meter_comm_params_t *meter_comm_params);

int8_t get_billing_info(meter_comm_params_t *meter_comm_params);
#endif

/* End Of File */