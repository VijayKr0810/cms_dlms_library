#ifndef	__DLMS_FUN_H__
#define	__DLMS_FUN_H__


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


#define 	LNT_METER_MFG_TYPE		1
#define 	SECURE_METER_MFG_TYPE	2

/* Qry Type */
#define		SNRM_TYPE 					0x00
#define		AARQ_TYPE 					0x01
#define 	BLOCK_VALUES_TYPE			0X63
#define		DISC_TYPE					0x64
#define     NAME_PLATE_PARAMS_TYPE      0x04
#define		DATE_TIME_TYPE 				0x06
#define		CHECK_LIFO_OR_FIFO			0x21
#define		EVENT_ENTRIES_TYPE			0x22
#define		RR_TYPE						0x23
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
#define		BILL_ENTRIES_TYPE			0x20
#define		EVENT_VALUE_OBIS_TYPE		0x1C
#define		EVENT_SCALER_OBIS_TYPE		0x1D
#define		EVENT_SCALER_VALUE_TYPE		0x1E
#define		EVENT_VALUE_TYPE 			0x1F
#define		DAILY_SCALAR_OBIS_TYPE		0x24
#define		DAILY_VAL_OBIS_TYPE 		0x25
#define		DAILY_SCALAR_VALUE_TYPE		0x26
#define		DAILY_VALUES_TYPE			0x27

#define     DLMS_START_END_FLAG         0x7E
#define     FRAME_FORMAT_TYPE       	0xA000
#define     POLL_FINAL_BIT          	0x10


#define     PPPINITFCS16    			0xFFFF  // Initial FCS value
#define     PPPGOODFCS16     			0xF0B8  // Good final FCS value
#define     CTRL_SNRM_FRAME         	0x83
#define     CTRL_DISC_FRAME         	0x43
#define     I_FRAME                 	0x00 // last bit should be zero
#define     CTRL_RR_FRAME           	0x01
#define     CTRL_RNR_FRAME          	0x05
#define     AARQ_FRAME              	0x60
#define     AARE_FRAME              	0x61
#define     GET_REQUEST_NORMAL 			0xC001
#define     GET_REQUEST_NEXT_DATA_BLOCK	0xC002

#define 	BILL_DATA_VAL_OBIS_STR 		"1.0.98.1.0.255"
#define 	BILL_VAL_OBIS_STR 			"1.0.98.1.0.255"
#define 	BILL_SCALAR_OBIS_STR 		"1.0.94.91.6.255"
#define 	BILL_SCALAR_VAL_STR 		"1.0.94.91.6.255"
#define 	BILL_ENTRY_OBIS_STR			"1.0.98.1.0.255"

#define 	BILL_DATA_INT_CLASS 		0X0007
#define 	BILL_VAL_INT_CLASS 			0x0007
#define 	BILL_SCALAR_INT_CLASS 		0x0007
#define 	BILL_SCALAR_VAL_INT_CLASS 	0x0007
#define 	BILL_ENTRY_INT_CLASS 		0x0007

#define 	BILL_DATA_ATTR_NO 			0X0000
#define 	BILL_VAL_ARR_NO 			0x0003
#define 	BILL_SCARAR_ARR_NO 			0x0003
#define 	BILL_SCALAR_VAL_ARR_NO 		0x0002
#define 	BILL_ENTRY_ARR_NO 			0x0007

#define 	DP_VAL_OBIS_STR 				"1.0.99.2.0.255"
#define 	DP_SCALAR_OBIS_STR 				"1.0.94.91.5.255"
#define 	DP_SCALAR_VAL_STR 				"1.0.94.91.5.255"
#define 	DP_DATA_VAL_OBIS_STR 			"1.0.99.2.0.255"
	
#define 	DP_VAL_INT_CLASS				0x0007
#define 	DP_SCALAR_INT_CLASS				0x0007
#define 	DP_SCALAR_VAL_INT_CLASS			0x0007
#define 	DP_DATA_VAL_INT_CLASS			0x0007
	
#define 	DP_VAL_ATTR_NO 					0x0003
#define 	DP_SCALAR_ATTR_NO 				0x0003
#define 	DP_SCALAR_VAL_ATTR_NO 			0x0002
#define 	DP_DATA_VAL_ATTR_NO 			0x0002

#define EVENT_DATA_VAL_OBIS_STR 		"0.0.99.98.0.255" 
#define EVENT_VAL_OBIS_STR 				"0.0.99.98.0.255" 
#define EVENT_SCALAR_OBIS_STR 			"1.0.94.91.7.255" 
#define EVENT_SCALAR_VAL_OBIS_STR 		"1.0.94.91.7.255" 
#define EVENT_ENTRY_OBIS_STR 			"0.0.99.98.0.255" 

#define EVENT_VAL_INT_CLASS				0x0007
#define EVENT_SCALAR_INT_CLASS			0x0007
#define EVENT_SCALAR_VAL_INT_CLASS		0x0007
#define EVENT_DATA_VAL_INT_CLASS		0x0007
#define EVENT_ENTRY_INT_CLASS			0X0007
	
#define EVENT_VAL_ATTR_NO 				0x0003
#define EVENT_SCALAR_ATTR_NO 			0x0003
#define EVENT_SCALAR_VAL_ATTR_NO 		0x0002
#define EVENT_DATA_VAL_ATTR_NO 			0x0000
#define EVENT_ENTRY_ATTR_NO 			0X0007

#define LS_VAL_OBIS_STR 				"1.0.99.1.0.255"
#define LS_SCALAR_OBIS_STR 				"1.0.94.91.4.255"
#define LS_SCALAR_VAL_STR 				"1.0.94.91.4.255"
#define LS_DATA_VAL_OBIS_STR 			"1.0.99.1.0.255"
#define LS_BLK_INT_PER_OBIS_STR 		"1.0.0.8.4.255" 
	
#define LS_VAL_INT_CLASS				0x0007
#define LS_SCALAR_INT_CLASS				0x0007
#define LS_SCALAR_VAL_INT_CLASS			0x0007
#define LS_DATA_VAL_INT_CLASS			0x0007
#define LS_BLK_INT_PER_INT_CLASS 		0X0001

#define LS_VAL_ATTR_NO 					0x0003
#define LS_SCALAR_ATTR_NO 				0x0003
#define LS_SCALAR_VAL_ATTR_NO 			0x0002
#define LS_DATA_VAL_ATTR_NO 			0x0001
#define LS_BLK_INT_PER_ATTR_NO 			0X0002


#define INST_VAL_OBIS_STR 				"1.0.94.91.0.255"
#define INST_SCALAR_OBIS_STR 			"1.0.94.91.3.255"
#define INST_SCALAR_VAL_STR 			"1.0.94.91.3.255"
#define INST_DATA_VAL_OBIS_STR 			"1.0.94.91.0.255"
	
#define INST_VAL_INT_CLASS				0x0007
#define INST_SCALAR_INT_CLASS			0x0007
#define INST_SCALAR_VAL_INT_CLASS		0x0007
#define INST_DATA_VAL_INT_CLASS			0x0007
	
#define INST_VAL_ATTR_NO 				0x0003
#define INST_SCALAR_ATTR_NO 			0x0003
#define INST_SCALAR_VAL_ATTR_NO 		0x0002
#define INST_DATA_VAL_ATTR_NO 			0x0002

#define DATE_TIME_OBIS_STR				"0.0.1.0.0.255" 
#define DATE_TIME_INT_CLASS 			0X0008 
#define DATE_TIME_ATTR_NO 				0X0002

#define NP_INT_CLASS					0X0001
#define NP_ATTR_NO 						0X0002

//printf("Recv Obis : %s\n",obis_code1);
#define GET_OBIS_OCTETS(obis_code1,arr){const char s[2] = ".";char obis_code[32] ;memset(obis_code,0,sizeof(obis_code));strcpy(obis_code,obis_code1);char *token=NULL;int8_t i = 0;token = strtok(obis_code, s);while( token != NULL  ){arr[i] = atoi(token);token = strtok(NULL, s);i++;}}


#define get_obis_octets_bkp(obis_code1,arr)\
{\
	const char s[2] = ".";\
	char obis_code[32] ;\
	printf("%s\n\n",obis_code);\
	memset(obis_code,0,sizeof(obis_code));\
	strcpy(obis_code,obis_code1);\
	char *token=strtok(obis_code, s);\
	int8_t i = 0;\
	token = strtok(obis_code, s);\
	while( token != NULL  )\
	{\
		arr[i] = atoi(token);\
		token = strtok(NULL, s);\
		i++;\
	}\
}

#define get_obis_octets12(obis_code,arr) \
{\
	const char s[2] = ".";\
   char *token;\
   int8_t i = 0;\
   printf("%s\n",obis_code);\
   token = strtok(obis_code, s);\
   printf(" %s\n", token );\
   while( token != NULL ) \
   {\
      printf(" %s\n", token );\
	  arr[i++] = atoi(token);\
      token = strtok(NULL, s);\
   }\
}

#define get_obis_octets1(obis_code,arr) \
{\
	int i = 0;\
	char *token;\
	printf("%s\n",obis_code);\
	token = strtok(obis_code,".");\
	while( token != NULL ) \
	{\
		arr[i] = atoi(token);\
		i = i+1;\
		token = strtok(NULL, ".");\
	}\
}
		

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
	scalar_det_t		scalar_val[128];
	uint8_t				val_obis[128][6];
} gen_params_det_t;

int32_t send_disc(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size );
int32_t send_snrm(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size);
int32_t send_aarq(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size, char*meter_pass);
int32_t send_msg_meter(uint8_t g_serial_fd, uint8_t* msg, int32_t len);
uint16_t pppfcs16 (uint16_t fcs, uint8_t *cp, int32_t len);
int32_t validate_met_resp(uint8_t* msg, int32_t len );
void print_data(uint8_t* msg, int32_t len);
int32_t proc_read_resp(uint8_t* msg, int32_t len);


int32_t get_curr_date_time(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size);

int32_t get_event_entry_order(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size);
int32_t send_get_next_blk(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size, uint32_t blk_val);
int32_t send_get_request(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);

//int8_t get_nameplate_info(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size, params_obis_val_info_t *np_params_obis_val_info);

int8_t get_nameplate_info(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size, obis_name_plate_info_t *np_params_obis_val_info);

int32_t send_rr_frame(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size);

int8_t get_obis_codes( meter_comm_params_t *meter_comm_params,
						gen_params_det_t *recv_gen_inst_param_det,
						gen_params_det_t *recv_gen_ls_param_det,
						gen_params_det_t *recv_gen_event_param_det,
						gen_params_det_t *recv_gen_bill_param_det,
						gen_params_det_t *recv_gen_daily_prof_param_det);
int32_t get_inst_obis_code_det(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size,gen_params_det_t *recv_gen_inst_param_det);

int32_t get_gen_val_obis(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);

int32_t get_gen_scalar_obis(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size,uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);

int32_t get_gen_val_obis(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size, uint8_t recv_qry_type, uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);


int32_t fill_inst_val(void);

int32_t get_scaler_mf(int8_t mf,float *mf_val);
char* get_float_str(float recv_flt_val);

int32_t get_inst_val(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size, inst_val_info_t *recv_inst_data_val);


int8_t get_ls_obis_code_det(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size,gen_params_det_t*recv_gen_ls_param_det);
int32_t read_ls_data(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size);
int32_t read_today_ls_data(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size );
int32_t get_int_blk_period(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size);
int32_t send_blk_profile_request( uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size,uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);
int32_t store_ls_date_time( uint8_t ls_idx, uint8_t index);
int32_t store_ls_val( uint8_t ls_idx, uint8_t index, float recv_flt_val);
int32_t fill_ls_val( uint8_t recv_ls_idx);
int32_t save_ls_data_file(void);

int32_t recv_ls_hour_range_data(meter_comm_params_t *meter_comm_params,date_time_t st_date_time, date_time_t end_date_time);
int32_t recv_ls_day_range_data(meter_comm_params_t *meter_comm_params,uint8_t last_num_days_read);
int32_t recv_ls_blk_range_data(meter_comm_params_t *meter_comm_params,date_time_t st_date_time, date_time_t end_date_time);


int32_t store_event_det_file(uint8_t event_class);
int32_t get_num_event_entries(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size, uint8_t* obis);
int32_t store_event_date_time( uint8_t ls_idx, uint8_t index);
int32_t store_event_val( uint8_t event_class, uint8_t index, float recv_flt_val);
int32_t proc_event_val_obis( uint8_t* msg, uint32_t len);
int32_t proc_event_scalar_obis( uint8_t* msg, uint32_t len);
int32_t proc_event_scalar_val( uint8_t* msg, uint32_t len);
int32_t proc_event_value(uint8_t* msg, uint32_t len);
int32_t fill_event_val( uint8_t event_idx);
int32_t get_event_class_data(meter_comm_params_t *meter_comm_params, uint8_t event_class, uint8_t read_all_event_flag);
int8_t get_event_obis_code_det(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size,gen_params_det_t*recv_gen_ls_param_det);
int32_t send_get_event_request (uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size,uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no, uint8_t event_read_flag);

int32_t store_dp_date_time(uint8_t dp_index, uint8_t index);
int32_t store_dp_val(uint8_t dp_index, uint8_t index, float recv_flt_val);
int32_t save_dp_data_file(void);
int32_t get_daily_profile_value(meter_comm_params_t*meter_comm_params, uint8_t dp_all);
int32_t proc_daily_profile_val_obis( uint8_t* msg, uint32_t len);
int32_t proc_daily_profile_scalar_obis( uint8_t* msg, uint32_t len);
int32_t proc_daily_profile_scalar_val( uint8_t* msg, uint32_t len);
int32_t proc_daily_profile_value( uint8_t* msg, uint32_t len);
int32_t fill_daily_profile_val(uint8_t dp_index);
int32_t get_dp_obis_code_det(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size,gen_params_det_t *recv_gen_inst_param_det);


int32_t get_billing_obis_code_det(uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size,gen_params_det_t *recv_gen_billing_param_det);

int32_t fill_billing_val(uint8_t bill_index);
int32_t get_bill_data_info(meter_comm_params_t *meter_comm_params);

int32_t send_get_bill_request (uint8_t comm_fd, uint32_t dlms_met_addr, uint8_t met_addr_size,uint16_t int_class, uint8_t*obis_code, uint8_t obis_len, uint16_t attr_no);
#endif
/* end of file */