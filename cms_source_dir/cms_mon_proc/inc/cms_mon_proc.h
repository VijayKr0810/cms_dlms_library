#ifndef	__CMS_MON_PROC_H__
#define	__CMS_MON_PROC_H__

#define 				CMS_MON_PROC_LOG_FILE_NAME "cms_mon_proc.log"

#define 				MAX_PROCESSES 				15

#define 				DCU_CSV_FILE_TYPE 			1
#define 				SEND_DIAG_MSG_TIME 			30
#define 				CHECK_PROC_TIME 			30

#define 				CMS_BIN_TO_REDIS_PROC		"/usr/cms/bin/cms_bin_to_redis_proc"
#define 				CMS_NTP_CLIENT_PROC			"/usr/cms/bin/cms_ntpclient_proc"
#define 				CMS_DLMS_MET_POLL_PROC		"/usr/cms/bin/cms_dlms_met_poll_proc"
#define 				CMS_WEB_BACK_END_PROC		"/usr/cms/bin/cms_web_back_end_proc"
#define 				CMS_GEN_CSV_FILE_PROC		"/usr/cms/bin/cms_gen_csv_proc"
#define 				CMS_RESET_SWITCH_PROC		"/usr/cms/bin/reset_switch_check.sh"
#define 				CMS_FTP_PUSH_PROC			"/usr/cms/bin/cms_ftp_push_proc"

#define 				CMS_ZOMBIE_CHECK_SCRIPT		"/usr/cms/bin/zombie_process_check.sh"
#define 				CMS_MODEM_STATUS_SCRIPT		"/usr/cms/bin/modem_status.sh"
#define 				CMS_REBOOT_WDT_SCRIPT		"/usr/cms/bin/reboot_wdt.sh"
#define 				CMS_FTP_SCRIPT				"/usr/cms/bin/curl_script.sh"
#define 				CMS_PING_SCRIPT				"/usr/cms/bin/ping_script.sh"

#define					VERSION_PATH				"/usr/cms/config/vinfo"
#define					RBT_INFO_PATH       		"/usr/cms/log/rbtinfo"

#define 				DLMS_POLL_PROC_ID 			1

#define 				RBT_PING_FAIL				0x0
#define 				RBT_DEF_RST_TO				0x1
#define					RBT_OTH_PROC				0X2
#define					RBT_FROM_WDT				0x3	
#define	 				SIGNAL_INTR					0x4
#define					RBT_LPC_HANG				0x5
#define 				PROC_UP						0x6
#define 				MAX_RBT_INFO_SIZE			50000

#define					MAX_PROC_RESTARTS			20
#define					MAX_PROC_HANG_CNT			5
#define					PROC_RESTART_TIME_DIFF		60
#define 				REFF_TIME_OUT				3*60 		//(3 Mint)

typedef	struct 
{
	int		status;									//status of the process, success or failure
	pid_t 	pid;									//pid of the process
	int		num_restart;							//number of times the process is restarted
	long	restart_time;							//time when the process is started ( restarted )
	char 	proc_name[SIZE_128];					//process name
	char 	proc_cfg_file[SIZE_128];				//cfg file used by the process
	char	cmd_line_arg1[SIZE_8];
	char	cmd_line_arg2[SIZE_8];
}proc_info_t;

#endif