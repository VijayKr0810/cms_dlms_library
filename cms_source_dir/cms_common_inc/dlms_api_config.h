#ifndef	__DLMS_API_CONFIG_H__
#define	__DLMS_API_CONFIG_H__

#include "gen_inc.h"

#define		DCU_VERSION_PREFIX	"CS-MDAS-DCU-"	
#define		DCU_VERNUM			"T_V1.00"

#define 	DCU_SERIAL 		1

#define 	DCU_SIGLE_PORT_TYPE	0 
#define 	DCU_DUAL_PORT_TYPE	0 
#define 	DCU_FOUR_PORT_TYPE	1 
#define 	DCU_SIX_PORT_TYPE	0 

#define 	COMM_PORT0_DET ""
#define 	COMM_PORT1_DET ""
#define 	COMM_PORT2_DET ""
#define 	COMM_PORT3_DET ""
#define 	COMM_PORT4_DET ""
#define 	COMM_PORT5_DET ""
	
#define 	PROD_NAME 		"DCU"

#if  DCU_SIGLE_PORT_TYPE
	#define		ATSAM91G				1
	#define		ATSAM91X				0
	#define		MAX_NUM_DCU_ETH			1
	#define		MAX_NO_OF_SERIAL_PORT	1
	
	#undef 		COMM_PORT0_DET
	#define 	COMM_PORT0_DET 			"/dev/ttyS4"
#endif

#if  DCU_DUAL_PORT_TYPE
	#define		ATSAM91G				0
	#define		ATSAM91X				1
	#define		MAX_NUM_DCU_ETH			2
	#define		MAX_NO_OF_SERIAL_PORT	2
	#undef 		COMM_PORT0_DET
	#undef 		COMM_PORT1_DET
	#define 	COMM_PORT0_DET 			"/dev/ttyS1"
	#define 	COMM_PORT1_DET 			"/dev/ttyS4"
#endif

#if  DCU_FOUR_PORT_TYPE
	#define		ATSAM91G				0
	#define		ATSAM91X				1
	#define		MAX_NUM_DCU_ETH			2
	#define		MAX_NO_OF_SERIAL_PORT	4
	#undef 		COMM_PORT0_DET
	#undef 		COMM_PORT1_DET
	#undef 		COMM_PORT2_DET
	#undef 		COMM_PORT3_DET
	#define 	COMM_PORT0_DET 			"/dev/ttyUSB0"
	#define 	COMM_PORT1_DET 			"/dev/ttyUSB1"
	#define 	COMM_PORT2_DET 			"/dev/ttyUSB2"
	#define 	COMM_PORT3_DET 			"/dev/ttyUSB3"
#endif

#if  DCU_SIX_PORT_TYPE
	#define		ATSAM91G				0
	#define		ATSAM91X				1
	#define		MAX_NUM_DCU_ETH			2
	#define		MAX_NO_OF_SERIAL_PORT	6
	#undef 		COMM_PORT0_DET
	#undef 		COMM_PORT1_DET
	#undef 		COMM_PORT2_DET
	#undef 		COMM_PORT3_DET
	#undef 		COMM_PORT4_DET
	#undef 		COMM_PORT5_DET
	#define 	COMM_PORT0_DET "/dev/ttyUSB0"
	#define 	COMM_PORT1_DET "/dev/ttyUSB1"
	#define 	COMM_PORT2_DET "/dev/ttyUSB2"
	#define 	COMM_PORT3_DET "/dev/ttyUSB3"
	#define 	COMM_PORT4_DET "/dev/ttyS1"
	#define 	COMM_PORT5_DET "/dev/ttyS4"
#endif

#define 	ROOT_DATA_DIR 			"/usr/cms/data/DlmsData"
#define 	LOG_DIR 				"/usr/cms/log"


#define MAX_NO_OF_METER_PER_PORT 	5
#define MAX_NO_OF_ETH_METER	 		10
#define MAX_NUM_MASTER	 			4

#define				START_END_FLAG				0x524E5243

//#define 			RET_SUCCESS 0
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
}serport_params1_t;

typedef struct
{	
	uint8_t 			meter_id;
	char				meter_ipaddr[32];
	uint16_t			port;
	uint8_t 			meter_addr_size;
	uint32_t			meter_addr;
	char				meter_pass[32];
	char				meter_loc[32];
}eth_params1_t;

typedef struct 
{
	uint8_t			day;
	uint8_t			month;
	uint8_t			hour;
	uint8_t			minute;
	uint8_t			second;
	uint8_t			unused;
	uint16_t		year;
} date_time1_t;

typedef struct
{
	uint32_t   	        enable_dbglog;
	char				dbglog_ip_addr[16];
}general_cfg_t;

typedef struct
{
	char				ip_addr[32];
	char				netmask[32];
	char				gateway[32];
}eth_cfg_t;

typedef struct 
{
	uint32_t 			num_dcu_eth_port;
	eth_cfg_t 			eth_cfg[MAX_NUM_DCU_ETH];
}
ethernate_cfg_t;

typedef struct
{	
	uint8_t 			enable;
	uint8_t 			meter_id;
	uint8_t 			meter_addr_size;
	uint8_t 			unused;
	uint8_t 			unused1;
	uint8_t 			unused2;
	uint16_t			port;
	uint32_t			meter_addr;
	char				meter_pass[32];
	char				meter_ipaddr[32];
	char				meter_loc[32];
}eth_met_params_t;

typedef struct
{
	uint8_t 			enable;
	uint8_t 			meter_id;
	uint8_t 			meter_addr_size;
	uint8_t 			unused;
	uint32_t			meter_addr;
	char				meter_pass[32];
	char				meter_loc[32];
}meter_cfg_t;

typedef struct
{
	uint32_t 			num_meter;
	meter_cfg_t 		met_cfg[MAX_NO_OF_METER_PER_PORT];
}dlms_channel_cfg_t;

// NTP Configuration
typedef struct
{
	uint8_t   	        enable_ntp1;
	uint8_t   	        enable_ntp2;
	uint8_t   	        unused;
	uint8_t   	        unused1;
	int32_t	   			ntp1_port;
	int32_t	   			ntp2_port;
	int32_t				interval;
	int32_t 			time_offset_hr;
	int32_t 			time_offset_mint;
	char   				ntp1_ip_addr[16];
	char   				ntp2_ip_addr[16];
} ntp_cfg_t;

//structure related to gprs cfguration
typedef struct
{
	int32_t				enable_gprs;
	char  				username[32];
	char  				password[32];
	char  				phone_num[32];
	char 				access_pt_name[32];
	char  				ping1_ip_addr[32];
	char  				ping2_ip_addr[32];
	uint8_t  		    conn_type;
	uint8_t  		    enable_ping;
	uint8_t 		    num_pings;
	uint8_t 		    ping_int;
}gprs_cfg_t;

//structure related to vpn cfguration
typedef struct 
{
	uint8_t				key_life_time;//in min
	uint8_t 		    aggr_mode;//yes(1) or no(0)
	uint8_t		        nat_trav;//yes(1) or no(0)
	uint8_t   	        unused;
	int32_t				pfs;//yes(1) or no(0)
	char				tunnel_name[64];
	char				pre_shared_key[128];
	char			 	right_ip[32];
	char				right_subnet[32];
	char				right_id[32];
	char				left[32];
	char				left_subnet[32];
	char				left_id[32];
	char				left_src_ip[32];
	char				keying_mode[8];
}ipsec_cfg_t;

typedef struct
{
	uint8_t 		    dhgrp;
	uint8_t		        encrpt;
	uint8_t		        authen;
	uint8_t   	        unused;
}phase_cfg_t;

typedef struct
{
	char 	conn_name[32];
	char 	loc_username[32];
	char 	loc_password[32];
	char 	remote_username[32];
	char 	remote_password[32];
	uint32_t req_mmpe128;
}pptp_cfg_t;

typedef struct
{
	uint32_t		    enable_vpn; //yes(1-Ipsec 2-pptp) or no(0)
	pptp_cfg_t			pptp_cfg;
	ipsec_cfg_t			ipsec_cfg;
	phase_cfg_t			phase_cfg1;
	phase_cfg_t			phase_cfg2;
}vpn_cfg_t;

typedef struct
{
	uint8_t num_ser_port;
	uint8_t num_eth_port;
	uint8_t meter_type;
	uint8_t data_format_type;
	uint8_t data_trf_type;
	uint8_t master_proto_type;
	uint8_t dcu_dev_id;
	uint8_t dbglog_enable;
	uint8_t dbglog_label;
	uint8_t	enable_allow_master_ip[MAX_NUM_MASTER];
	uint8_t	enable_allow_master;
	uint8_t	read_prev_ls_data;
	uint8_t	fault_to_1_supp;
	uint8_t	unused;
	uint8_t	unused1;
	uint8_t	unused2;
	char 	allow_master_ip[MAX_NUM_MASTER][16];
	char 	dcu_location[64];
	char 	dcu_gps_loc[64];
	char 	dbglog_ip[16];
	char 	ser_num[32];
}
dlms_dcu_info_t;

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
}dcu_serport_det_t;

typedef struct
{
	uint32_t 			num_ser_port;
	dcu_serport_det_t 	ser_prot_param[MAX_NO_OF_SERIAL_PORT];
}
ser_prot_cfg_t;

typedef struct
{
	uint32_t 			num_meter;
	eth_met_params_t 		eth_param[MAX_NO_OF_ETH_METER];
}
eth_meter_cfg_t;

typedef struct
{
	uint8_t enable;
	uint8_t poll_type;
	uint8_t periodicity;
	uint8_t poll_sec;
	uint8_t poll_mint;
	uint8_t poll_hr;
	uint8_t unused;
	uint8_t unused1;
}common_poll_info_t;

typedef struct
{
	common_poll_info_t inst_poll_info;
	common_poll_info_t ls_poll_info;
	common_poll_info_t event_poll_info;
	common_poll_info_t bill_poll_info;
	common_poll_info_t daily_prof_poll_info;
}
dcu_poll_info_t;

typedef struct
{
	uint8_t 	enable;
	uint8_t 	diff_log_ser;
	uint8_t 	log_upload_period;
	uint8_t 	upload_period;
	uint16_t 	ser_port;
	uint16_t 	log_ser_port;
	char 		ser_ip[16];
	char 		username[16];
	char 		password[16];
	char 		loc_dir[16];
	char 		log_ser_ip[16];
	char 		log_username[16];
	char 		log_password[16];
	char 		log_loc_dir[16];
}ftp_server_cfg_t;

typedef struct
{
	uint8_t 	enable;
	uint8_t 	iec_t1;
	uint8_t 	iec_t2;
	uint8_t 	iec_t3;
	uint8_t 	iec_k;
	uint8_t 	iec_w;
	uint8_t 	cot_size;
	uint8_t 	ioa_size;
	uint8_t 	cyclic_int;
	uint8_t 	unused;
	uint16_t 	iec_port;
	uint32_t 	start_data_ioa;
	uint32_t 	start_dev_status_ioa;
	uint32_t 	asdu_addr;
}iec104_slave_cfg_t;

typedef struct
{
	uint8_t 	enable;
	uint8_t 	resp_all_id;
	uint8_t 	slave_id;
	uint8_t 	unused;
	uint8_t 	unused1;
	uint8_t 	unused2;
	uint16_t 	hold_reg_start_addr;
	uint16_t 	input_reg_start_addr;
	uint16_t 	read_coil_start_addr;
	uint16_t 	port;
	uint16_t 	read_disc_start_addr;
}modtcp_slave_cfg_t;

typedef struct
{
	uint8_t				enable;
	uint8_t				event_topic_enable;
	uint8_t				diag_topic_enable;
	uint8_t				pub_int_hour;
	uint8_t				pub_int_mint;
	uint8_t				pub_int_sec;
	int16_t 			broker_port;
	char 				event_pub_topic[64];
	char 				periodic_data_topic[64];
	char 				cmd_sub_topic[64];
	char 				diag_pub_topic[64];
	char 				username[32];
	char 				password[32];
	char 				pub_topic[64];
	char 				sub_topic[32];
	char 				broker_ip[16];
}mqtt_broker_cfg_t;

typedef struct 
{
	uint8_t				enable;
	uint8_t				event_send_enable;
	uint8_t				diag_send_enable;
	uint8_t				pub_int_hour;
	uint8_t				pub_int_mint;
	uint8_t				pub_int_sec;
	int16_t 			broker_port;
	char 				broker_ip[16];
}cms_ems_broker_cfg_t;


typedef struct
{
	uint32_t			start_flag;
	dlms_dcu_info_t 	dlms_dcu_info;
	ser_prot_cfg_t 		ser_prot_cfg;
	dlms_channel_cfg_t 	dlms_channel_cfg[MAX_NO_OF_SERIAL_PORT];
	eth_meter_cfg_t 	eth_meter_cfg;
	ethernate_cfg_t		ethernate_cfg;
	dcu_poll_info_t 	dcu_poll_info;
	ftp_server_cfg_t 	ftp_ser_cfg;
	iec104_slave_cfg_t  iec104_slave_cfg;
	modtcp_slave_cfg_t 	modtcp_slave_cfg;
	ntp_cfg_t 			ntp_cfg;
	gprs_cfg_t 			gprs_cfg;
	vpn_cfg_t			vpn_cfg;
	mqtt_broker_cfg_t 	mqtt_cfg;
	cms_ems_broker_cfg_t cms_ems_cfg;
	uint16_t			unused;
	uint16_t			crc;
	uint32_t			end_flag;
}
dlms_dcu_config_t;

#endif

/* End Of File */