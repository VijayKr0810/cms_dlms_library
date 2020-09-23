#ifndef	__DLMS_MODULE_H__
#define	__DLMS_MODULE_H__


#pragma pack(1)


#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <pthread.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/errno.h>
#include <linux/serial.h>
#include <asm/ioctls.h>
#include <assert.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <netdb.h>


#define		DISC_TYPE					0x64
#define 	BLOCK_VALUES_TYPE			0X63
#define		SNRM_TYPE 					0x00
#define		AARQ_TYPE 					0x01
#define     NAME_PLATE_PARAMS_TYPE      0x04
#define		DATE_TIME_TYPE 				0x06
#define		INST_SCALE_OBIS_TYPE		0x10
#define		INST_SCALE_VAL_TYPE 		0x11
#define		INST_VAL_OBIS_TYPE			0x12
#define		INST_VALUES_TYPE 			0x13
#define		BLOCK_SCALER_OBIS_TYPE		0x14
#define		BLOCK_VAL_OBIS_TYPE 		0x15
#define		BLOCK_SCALER_VALUE_TYPE		0x16
#define		BLOCK_INT_PERIOD_TYPE		0x17
#define		BILL_VAL_OBIS_TYPE 			0x18
#define		BILL_SCALER_OBIS_TYPE		0x19
#define		BILL_SCALER_VALUE_TYPE		0x1A
#define		BILL_VALUE_TYPE 			0x1B
#define		EVENT_VALUE_OBIS_TYPE		0x1C
#define		EVENT_SCALER_OBIS_TYPE		0x1D
#define		EVENT_SCALER_VALUE_TYPE		0x1E
#define		EVENT_VALUE_TYPE 			0x1F
#define		BILL_ENTRIES_TYPE			0x20
#define		CHECK_LIFO_OR_FIFO			0x21
#define		EVENT_ENTRIES_TYPE			0x22
#define		RR_TYPE						0x23
#define		DAILY_SCALAR_OBIS_TYPE		0x24
#define		DAILY_VAL_OBIS_TYPE 		0x25
#define		DAILY_SCALAR_VALUE_TYPE		0x26
#define		DAILY_VALUES_TYPE		0x27


#define     DLMS_START_END_FLAG         0x7E
#define     FRAME_FORMAT_TYPE       	0xA000
#define     POLL_FINAL_BIT          	0x10

#define     CTRL_SNRM_FRAME         	0x83
#define     CTRL_DISC_FRAME         	0x43
#define     I_FRAME                 	0x00 // last bit should be zero
#define     CTRL_RR_FRAME           	0x01
#define     CTRL_RNR_FRAME          	0x05
#define     AARQ_FRAME              	0x60
#define     AARE_FRAME              	0x61
#define     GET_REQUEST_NORMAL 			0xC001
#define     GET_REQUEST_NEXT_DATA_BLOCK	0xC002

#define     PPPINITFCS16    	0xFFFF  // Initial FCS value
#define     PPPGOODFCS16     	0xF0B8  // Good final FCS value

/****************************COSEM DATA TYPES*******************************/
#define		ARRAY_OF_ELE_TYPE		0x01
#define		STRUCTURE_OF_ELE_TYPE	0x02
#define		OCTET_STRING_TYPE		0x09
#define		VISIBLE_STRING_TYPE		0x0A
#define		SIGNED_8BIT_TYPE		0x0F
#define		UNSIGNED_8BIT_TYPE		0x11
#define		SIGNED_16BIT_TYPE		0x10
#define		UNSIGNED_16BIT_TYPE		0x12
#define		SIGNED_32BIT_TYPE		0x05
#define		UNSIGNED_32BIT_TYPE		0x06
#define		ENUM_TYPE 				0x16
#define		FLOAT_32BIT_TYPE		0x17

#define		LI_FO					0x01
#define		FI_FO					0x02



typedef enum
{
    SIZE_4=4,
	SIZE_8=8,
	SIZE_16=16,
	SIZE_32=32,
	SIZE_64=64,
	SIZE_128=128,
	SIZE_256=256,
	SIZE_512=512,
	SIZE_640=640,
	SIZE_1024=1024,
	SIZE_2048=2048,
	SIZE_6144=6144
}buffer_size_t;

#define RET_FAILURE -1

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
	RET_INST_VAL_FAILED_TYPE = -28 //Failed to get inst val from meter.
} error_type_t;


// Databits
#define		FIVE_BITS			5
#define		SIX_BITS			6
#define		SEVEN_BITS			7
#define		EIGHT_BITS			8

// Stop bits
#define		ONE					1
#define		TWO					2

//serial port constants
#define		NONE_PARITY			0x00
#define		ODD_PARITY			0x01
#define		EVEN_PARITY			0x02

//flow control
#define 	NO_HANDSHAKE		0x00
#define 	HW_HANDSHAKE		0x01
#define 	SW_HANDSHAKE		0x02

#define 	RS232_MODE			1
#define 	RS485_MODE			2


//#define     CMS_LOG_DIR			"/usr/cms/log"

#define INF_SERIAL 					1
#define INF_TCP 					2
#define MAX_NO_OF_METER_PER_PORT 	1
#define RET_OK RET_SUCCESS
#define DEBUG_LOG 					0

#define RTU_DLMS					1
#define CMS_LOG_DIR "."
#define FILE_SIZE_EXCEED 			1*1024*1024

#define LNT 1
#define LNT_METER_MFG_TYPE		1
#define SECURE_METER_MFG_TYPE	2


#define RTU_MODBUS_RTU		0X01
#define RTU_MODBUS_TCP		0X02
#define RTU_IEC_104S		0X03
#define RTU_DNP3S			0X04
#define RTU_GPRS			0X05
#define RTU_IO_POLL			0X06
#define RTU_MON_PROC		0X07
#define RTU_VPN_IPSEC		0X08
#define RTU_VPN_PPTP		0X09
#define RTU_DIAG			0X0A
#define RTU_NTP_CLIENT		0X0B

#define		INFORM				0
#define		WARNING				1
#define		SEVERE				2
#define		FATAL				3
#define		REPORT				4

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
}serport_params_t;

typedef struct
{	
	char				meter_ipaddr[32];
	uint32_t			port;
}eth_params_t;


//Structures
typedef struct 
{
	uint8_t			day;
	uint8_t			month;
	uint16_t		year;
	uint8_t			hour;
	uint8_t			minute;
	uint8_t			second;
} date_time_t;


typedef struct
{
	int32_t 		fd;
	int8_t			inf_type;
	int8_t			meter_type;
	int32_t			meter_id;
	int8_t			meter_addr_format;
	date_time_t		from;
	date_time_t		to;
	int32_t			inf_params_len;
	void			*interface_params;
	int32_t			other_info1;
	int32_t			other_info2;
	char			filename[SIZE_128]; //file where the big data has to be stored
	char			meter_pass[SIZE_16]; //file where the big data has to be stored
	int32_t			resp_len;
	char			*meter_response;

}meter_comm_params_t;


typedef struct 
{
	uint8_t			data_type;
	uint8_t			num_bytes;
	uint8_t			value[32];
} gen_data_val_info_t;

typedef struct 
{
	uint8_t				obis_code[6];
	int8_t				value;
} scalar_det_t;

typedef struct
{
	uint8_t 		obis_code[6];
	char	      	param_name[16];
}param_det_t;

typedef struct 
{
	uint8_t   			tot_num_scalar;
	uint8_t   			tot_num_val_obis;
	uint8_t   			tot_num_value;
	scalar_det_t		scalar_val[80];
	uint8_t				val_obis[80][6];
} gen_params_det_t;

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
	date_time_t			date_time;
	float				cur_ir;
	float				cur_iy;
	float				cur_ib;
	float				volt_r;
	float				volt_y;
	float				volt_b;
	float				pf_r;
	float				pf_y;
	float				pf_b;
	float				pf_avg;
	float				freq;
	float				kva;
	float				kw;
	float				kvar;
	float				num_pow_fail;
	float				cu_pf_dur;
	float				cu_ta_cnt;
	float				cu_bi_cnt;
	float				cu_pr_cnt;
	date_time_t			bill_date;
	float				kwh;
	float				kvarh_lag;
	float				kvarh_lead;
	float				kvah;
	float				kwmd;
	float				kvamd;
}inst_val_info_t;

typedef struct 
{
	date_time_t			date_time;
	float				freq;
	float				cur_ir;
	float 				cur_iy;
	float				cur_ib;
	float				volt_r;
	float				volt_y;
	float				volt_b;
	float				kwh_imp;
	float				kwh_exp;
	float				kvarh_lag;
	float				kvarh_lead;
	float				kvah_imp;
	float				kvah_exp;	
} block_val_info_t;


typedef struct
{
	block_val_info_t 	block_val_info[96];
}all_ls_data_info_t;

int8_t init_comm(meter_comm_params_t *meter_comm_params);
int8_t connect_to_meter();
int8_t get_nameplate_details(name_plate_info_t *name_plate_info);
int8_t get_obis_codes(gen_params_det_t *gen_inst_param_det,gen_params_det_t *gen_ls_param_det,gen_params_det_t *gen_event_param_det,gen_params_det_t *gen_bill_param_det,gen_params_det_t*gen_daily_prof_param_det);

int8_t get_curr_date_ls_data(void);
int32_t create_data_directory(void);

//int8_t get_obis_codes();
int8_t get_inst_values();
int8_t get_ls_values_block_range();
int8_t get_ls_values_hour_range();
int8_t get_ls_values_day_range();
int8_t get_midnight_data_all();
int8_t get_midnight_data();
int8_t get_event_data_all();
int8_t get_event_data();
int8_t get_billing_info();
int8_t disconnect_meter();


int32_t fill_inst_val(uint8_t midx);
int32_t send_disc(uint8_t midx);
int32_t send_snrm(uint8_t midx);
int32_t send_aarq(uint8_t midx);
int32_t get_inst_val(uint8_t midx);
int32_t send_rr_frame(uint8_t midx);
char* get_float_str(float recv_flt_val);
int32_t get_curr_date_time(uint8_t midx);
int8_t get_inst_obis_code_det(uint8_t midx);
int32_t get_event_entry_order(uint8_t midx);
int32_t get_scaler_mf(int8_t mf,float *mf_val);
void print_data(uint8_t midx, uint8_t* msg, int32_t len);
int32_t send_get_next_blk(uint8_t midx, uint32_t blk_val);
uint16_t pppfcs16 (uint16_t fcs, uint8_t *cp, int32_t len);
int32_t proc_read_resp(uint8_t midx, uint8_t* msg, int32_t len);
int32_t send_msg_meter(uint8_t midx, uint8_t* msg, int32_t len);
int32_t validate_met_resp(uint8_t midx, uint8_t* msg, int32_t len );
int32_t validate_met_resp(uint8_t midx, uint8_t* msg, int32_t len );
int32_t get_meter_date_time(uint8_t midx, uint8_t* msg, int32_t len);
int32_t send_get_request(uint8_t midx, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);
int32_t get_gen_val_obis(uint8_t midx, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);
int32_t get_gen_scalar_val(uint8_t midx, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);
int32_t get_gen_scalar_obis(uint8_t midx, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);

int32_t proc_inst_val_obis(uint8_t midx, uint8_t* msg, uint32_t len);
int32_t proc_inst_scalar_obis(uint8_t midx, uint8_t* msg, uint32_t len);
int32_t proc_inst_scalar_val(uint8_t midx, uint8_t* msg, uint32_t len);
int32_t proc_inst_value(uint8_t midx, uint8_t* msg, uint32_t len);

int8_t get_ls_obis_code_det(uint8_t midx);
int32_t get_int_blk_period(uint8_t midx);
int32_t proc_ls_val_obis(uint8_t midx, uint8_t* msg, uint32_t len);
int32_t proc_ls_scalar_obis(uint8_t midx, uint8_t* msg, uint32_t len);
int32_t proc_ls_scalar_val(uint8_t midx, uint8_t* msg, uint32_t len);
int32_t proc_ls_value(uint8_t midx, uint8_t* msg, uint32_t len);
int32_t fill_ls_val(uint8_t midx, uint8_t recv_ls_idx);
int32_t send_blk_profile_request(uint8_t midx, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);
int32_t store_ls_val(uint8_t midx, uint8_t ls_idx, uint8_t index, float recv_flt_val);
int32_t store_ls_date_time(uint8_t midx, uint8_t ls_idx, uint8_t index);
int32_t save_ls_data_file(uint8_t midx);
int32_t read_today_ls_data(uint8_t midx );
int32_t read_ls_data(uint8_t midx);

#endif