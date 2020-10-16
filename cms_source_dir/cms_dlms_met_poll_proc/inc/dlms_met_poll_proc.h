#ifndef	__WEB_BACK_END_H__
#define	__WEB_BACK_END_H__


/* Local Micros */

#define	DLMS_MODULE_IPC_PORT				6000

#define   MAX_RESP_TIME_ENTRY 50
#define REFF_INST_POLL_TIME 	2
#define REFF_EVENT_POLL_TIME 	5*60
#define REFF_LS_POLL_TIME 		15*60
#define ROOT_LIB_DATA_DIR 		"/usr/cms/data/LibData"
#define ROOT_LIB_DATA_PORT_DIR 		"/usr/cms/data/LibData"
#define MET_POLL_LOG_FILE_NAME "cms_met_poll_proc"
#define INST_INFO_KEY 		"inst_info"
#define NP_INFO_KEY 		"np_info"
#define BILLING_INFO_KEY 	"billing_key_info"
#define EVENT_INFO_KEY 		"event_type_key_info"
#define LS_BLK_INFO_KEY 	"ls_blk_info"

/* Function ProtoTypes */
void send_hc_msg(void);
void check_met_ser_num(void);
void get_prev_met_ser_num(void);
void check_od_msg_request(void);
int32_t read_cfg_from_redis(void);
int get_prev_ls_data(uint8_t midx);
int32_t delete_old_files(uint8_t midx);
void clear_temp_lib_data(uint8_t midx);
int32_t delete_old_files(uint8_t midx);
int32_t get_inst_data_for_all_met(void);
int32_t fill_recv_inst_val(uint8_t midx);
int32_t read_meter_obis_code(uint8_t midx);
int32_t redis_init(char *hostname, uint16_t port);
int32_t get_act_scaler_mf(int8_t mf,float *mf_val);
int32_t check_ls_file_avl(char* file_name, uint8_t midx);
int32_t send_inst_det_to_redis(char *key_name, uint8_t midx);
void get_date(char *p_file_name,int *day,int *mon,int *year);
int32_t met_poll_dbg_log(uint8_t mode, const char *p_format, ...);
int32_t send_det_to_redis(char *msg, uint32_t len, char *key_name);
int32_t update_np_det_to_redis(obis_name_plate_info_t *name_plate_info, uint32_t len);
void fill_meter_comm_params_det(meter_comm_params_t *meter_comm_params ,uint8_t midx);
void print_val_scal_onis_val_info(uint8_t* val_obis, uint8_t* scalar_obis, int8_t scalar_val);
int8_t get_inst_values(meter_comm_params_t *meter_comm_params, gen_data_val_info_t *p_gen_data_val_info);
int32_t convert_to_decoded_data(char *in_file_path, char *in_file_name, gen_params_det_t *recv_gen_param_det);
void append_in_exist_file(char *out_file_path, char *in_file_name, gen_params_det_t *recv_gen_param_det);

#endif