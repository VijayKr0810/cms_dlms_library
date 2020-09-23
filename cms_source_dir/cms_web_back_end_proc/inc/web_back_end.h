#ifndef	__WEB_BACK_END_H__
#define	__WEB_BACK_END_H__

#define DBL_QUOTES '"'

#define INST_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_inst_obis_det.json"
#define LS_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_ls_obis_det.json"
#define DP_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_dp_obis_det.json"
#define BILL_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_bill_obis_det.json"
#define EVENT_OBIS_PARAMS_JSON 		"/srv/www/htdocs/user_event_obis_det.json"

#define INST_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_inst_obis_det.json"
#define LS_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_ls_obis_det.json"
#define DP_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_dp_obis_det.json"
#define BILL_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_bill_obis_det.json"
#define EVENT_MASTER_OBIS_PARAMS_JSON "/srv/www/htdocs/master_event_obis_det.json"

/*  Local Micro*/
#define MET_POLL_LOG_FILE_NAME "cms_met_poll_proc.log"
#define INST_INFO_KEY 		"inst_info"
#define NP_INFO_KEY 		"np_info"
#define BILLING_INFO_KEY 	"billing_key_info"
#define EVENT_INFO_KEY 		"event_type_key_info"
#define LS_BLK_INFO_KEY 	"ls_blk_info"

#define DBL_QUOTES '"'

#define SER_MET 1
#define ETH_MET 2
#define BOTH_MET 3

typedef struct
{
	char 	obis_code[32];
	char 	param_name[32];
	char 	param_val[32];
	
}obis_param_val_info_t;


char 							json_text[200*1024]; //
char 							g_temp_str[256];



int32_t redis_init(char *hostname, uint16_t port);
int gwsock_init (int argc, char **argv);

int32_t send_msg(char *p_recv_msg);

void send_modem_status_det(uint32_t seq_num);
void send_commn_status_det(uint32_t seq_num);


int16_t get_port_met_det(const char *dir_name);
int16_t find_ser_num(const char *met_ser_num);
int32_t send_od_det(uint32_t seq_num, const char *met_ser_num, char *user_file_json, char *root_param_name, char *data_file_name, char *type, char *data_type);
int32_t send_od_billing_det(uint32_t seq_num, const char *met_ser_num);
int32_t send_od_midnight_det(uint32_t seq_num, const char *met_ser_num, uint8_t month, uint16_t year);
int32_t send_od_event_det(uint32_t seq_num, const char *met_ser_num, uint8_t event_type);
int32_t send_od_event_det11(uint32_t seq_num, const char *met_ser_num, uint8_t event_type);
void send_od_event_det1(uint32_t seq_num, const char *met_ser_num, uint8_t event_type);
void send_od_ls_range_det(uint32_t seq_num, const char *met_ser_num, date_time_t st_date_time, date_time_t end_date_time);
void send_od_inst_det(uint32_t seq_num, const char *met_ser_num);
void fill_user_obis_det(char *file_name, char *param_type);
int32_t send_met_ser_num_det(int32_t seq_num);
int32_t send_file_content_det(uint32_t seq_num, const char *met_ser_num, char *user_file_json, char *root_param_name, char *data_file_name,const char *dir_name, const char *file_name, const char *view_type, char *type);
int32_t send_event_file_content(uint32_t seq_num, const char *met_ser_num,const char *dir_name,const char *file_name,const char *view_type);
int32_t send_bill_file_content(uint32_t seq_num, const char *met_ser_num,const char *dir_name,const char *file_name,const char *view_type);
int32_t send_dp_file_content(uint32_t seq_num, const char *met_ser_num,const char *dir_name,const char *file_name,const char *view_type);
int32_t send_ls_file_content(uint32_t seq_num, const char *met_ser_num,const char *dir_name,const char *file_name,const char *view_type);
int32_t send_file_list_det(int32_t seq_num, const char *met_ser_num, char *type, char *dir_path, char *key_word, uint8_t read_ls, char* dir_name);
int32_t send_od_ls_file_list_det(int32_t seq_num, const char *met_ser_num);
int32_t send_ls_file_list_det(int32_t seq_num, const char *met_ser_num);
int32_t send_event_file_list_det(int32_t seq_num, const char *met_ser_num);
int32_t send_dp_file_list_det(int32_t seq_num, const char *met_ser_num);
int32_t send_bill_file_list_det(int32_t seq_num, const char *met_ser_num);
int32_t send_dir_list_det(int32_t seq_num);

#endif