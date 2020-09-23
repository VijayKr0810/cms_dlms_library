#if 0
#include "gen_inc.h"
#include "dlms_api_config.h"
#include "nxjson.h"

extern dlms_dcu_config_t dlms_dcu_config;

#define MAX_JSON_SIZE 3*1024
#define DBL_QT '"'

#define DCU_INFO_JSON 		"dcu_info.json"
#define SER_MET_INFO_JSON 	"ser_met_info.json"
#define ETH_MET_INFO_JSON 	"eth_met_info.json"
#define IEC104_INFO_JSON 	"iec104_info.json"
#define MODTCP_INFO_JSON 	"modtcp_info.json"
#define DCU_POLL_INFO_JSON 	"dcu_poll_info.json"
#define MQTT_INFO_JSON 		"mqtt_info.json"
#define CMS_EMS_INFO_JSON 	"cms_ems_info.json"
#define DCU_ETH_INFO_JSON 	"dcu_eth_info.json"
#define GPRS_INFO_JSON 		"gprs_info.json"
#define VPN_INFO_JSON 		"vpn_info.json"
#define NTP_INFO_JSON 		"ntp_info.json"
#define FTP_SER_INFO_JSON 	"ftp_ser_info.json"

char 	json_text[MAX_JSON_SIZE];
char 	temp_text[256];

void store_json_text(char *json_file)
{
	FILE *p_file_ptr=NULL;
	
	p_file_ptr = fopen(json_file,"w");
	if(p_file_ptr==NULL)
	{
		return;
	}

	fwrite(json_text,strlen(json_text),1,p_file_ptr);
	
	fclose(p_file_ptr); 
	
	const   nx_json *root_value=NULL;
	root_value = nx_json_parse(json_text, 0);
	if (root_value != NULL) 
	{
		printf("This is valid Json File : %s, Size : %ld\n",json_file,strlen(json_text));
	}
	else
		printf("parsing failed - improper JSon file : %s\n",json_file);
	
	nx_json_free(root_value);
}

void store_cfg_json(void)
{

}

void generate_cms_ems_info_json(void)
{
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cCMS_EMS_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{\n");
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.cms_ems_cfg.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cBrokerIp%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.cms_ems_cfg.broker_ip,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEventSendEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.cms_ems_cfg.event_send_enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDiagSendEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.cms_ems_cfg.diag_send_enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPubSec%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.cms_ems_cfg.pub_int_sec,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPubMint%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.cms_ems_cfg.pub_int_mint,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPubHr%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.cms_ems_cfg.pub_int_hour,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cBrokerPort%c:%c%d%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.cms_ems_cfg.broker_port,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"}\n");
	strcat(json_text,"}\n");
	
	store_json_text(CMS_EMS_INFO_JSON);
}

void generate_mqtt_info_json(void)
{
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cMQTT_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cBrokerIp%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.broker_ip,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cSubTopic%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.sub_topic,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPubTopic%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.pub_topic,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cBrokerPass%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.password,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cBrokerUname%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.username,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cBrokerPort%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.broker_port,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPubSec%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.pub_int_sec,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPubMint%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.pub_int_mint,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPubHr%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.pub_int_hour,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDiagPubTopic%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.diag_pub_topic,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDiagTopicEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.diag_topic_enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cCmdSubTopic%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.cmd_sub_topic,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPerDataTopic%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.periodic_data_topic,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEventPubTopic%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.event_pub_topic,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEventTopicEnable%c:%c%d%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.mqtt_cfg.event_topic_enable,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"}\n");
	strcat(json_text,"}");
	
	store_json_text(MQTT_INFO_JSON);
}

void generate_dcu_poll_info_json(void)
{
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDCU_POLL_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cINST_POLL_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"{");

	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.inst_poll_info.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollType%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPeriodicity%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.inst_poll_info.periodicity,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollSec%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_sec,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollMint%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_mint,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollHr%c:%c%d%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_hr,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"},\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDP_POLL_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"{");

	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollType%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPeriodicity%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.periodicity,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollSec%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_sec,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollMint%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_mint,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollHr%c:%c%d%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_hr,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"},\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cBILL_POLL_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"{");

	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.bill_poll_info.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollType%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPeriodicity%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.bill_poll_info.periodicity,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollSec%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_sec,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollMint%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_mint,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollHr%c:%c%d%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_hr,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"},\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEVENT_POLL_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"{");

	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.event_poll_info.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollType%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.event_poll_info.poll_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPeriodicity%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.event_poll_info.periodicity,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollSec%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.event_poll_info.poll_sec,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollMint%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.event_poll_info.poll_mint,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollHr%c:%c%d%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.event_poll_info.poll_hr,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"},\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cLS_POLL_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"{");

	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.ls_poll_info.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollType%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPeriodicity%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.ls_poll_info.periodicity,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollSec%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_sec,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollMint%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_mint,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPollHr%c:%c%d%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_hr,DBL_QT);
	strcat(json_text,temp_text);
	strcat(json_text,"}\n");
	
	strcat(json_text,"}\n");
	strcat(json_text,"}");
	
	store_json_text(DCU_POLL_INFO_JSON);
}

void generate_modtcp_info_json(void)
{
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cMODTCP_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{");

	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.modtcp_slave_cfg.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cRespAllId%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.modtcp_slave_cfg.resp_all_id,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cSlaveId%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.modtcp_slave_cfg.slave_id,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cHoldRegStAddr%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.modtcp_slave_cfg.hold_reg_start_addr,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cInputRegStAddr%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.modtcp_slave_cfg.input_reg_start_addr,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cReadCoilStAddr%c:%c%d%c\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.modtcp_slave_cfg.read_coil_start_addr,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"}\n");
	strcat(json_text,"}");
	
	store_json_text(MODTCP_INFO_JSON);
}

void generate_iec104_info_json(void)
{
	uint8_t idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cIEC104_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cAsduAddr%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.asdu_addr,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cTime1%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.iec_t1,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cTime2%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.iec_t2,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cTime3%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.iec_t3,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cSentAck%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.iec_k,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cRecvAck%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.iec_w,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cCotSize%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.cot_size,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cIoaSize%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.ioa_size,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cCycInterval%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.cyclic_int,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cIecPort%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.iec_port,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cStDataIoa%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.start_data_ioa,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cStDevStatusIoa%c:%c%d%c\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.iec104_slave_cfg.start_dev_status_ioa,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"}\n");
	strcat(json_text,"}");
	
	store_json_text(IEC104_INFO_JSON);
}

void generate_eth_meter_info_json(void)
{
	uint8_t idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cETH_MET_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNumMeters%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.eth_meter_cfg.num_meter,DBL_QT);
	strcat(json_text,temp_text);
	
	for(idx=0;idx<MAX_NO_OF_METER_PER_PORT;idx++)
	{
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cEthMeter_%dConfig%c:",DBL_QT,idx+1,DBL_QT);
		strcat(json_text,temp_text);
		
		strcat(json_text,"{");
		
		/* memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cEnable%c:%c%d%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_channel_cfg.met_cfg[idx].enable,DBL_QT);
		strcat(json_text,temp_text); */
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterId%c:%c%d%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_id,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterAddrSize%c:%c%d%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_addr_size,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterAddr%c:%c%d%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_addr,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterPass%c:%c%s%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_pass,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterIp%c:%c%s%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_ipaddr,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterLoc%c:%c%s%c",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_loc,DBL_QT);
		strcat(json_text,temp_text);
		
		if(idx==MAX_NO_OF_METER_PER_PORT-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}

	strcat(json_text,"}\n");
	strcat(json_text,"}");
	
	store_json_text(ETH_MET_INFO_JSON);
}

void generate_ser_meter_info_json(void)
{
	uint8_t idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cSER_MET_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNumMeters%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_channel_cfg.num_meter,DBL_QT);
	strcat(json_text,temp_text);
	
	for(idx=0;idx<MAX_NO_OF_METER_PER_PORT;idx++)
	{
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cSerMeter_%dConfig%c:",DBL_QT,idx+1,DBL_QT);
		strcat(json_text,temp_text);
		
		strcat(json_text,"{");
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cEnable%c:%c%d%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_channel_cfg.met_cfg[idx].enable,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterId%c:%c%d%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_channel_cfg.met_cfg[idx].meter_id,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterAddrSize%c:%c%d%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_channel_cfg.met_cfg[idx].meter_addr_size,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterAddr%c:%c%d%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_channel_cfg.met_cfg[idx].meter_addr,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterPass%c:%c%s%c,",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_channel_cfg.met_cfg[idx].meter_pass,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMeterLoc%c:%c%s%c",
		DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_channel_cfg.met_cfg[idx].meter_loc,DBL_QT);
		strcat(json_text,temp_text);
		
		if(idx==MAX_NO_OF_METER_PER_PORT-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}

	strcat(json_text,"}\n");
	strcat(json_text,"}");
	
	store_json_text(SER_MET_INFO_JSON);
}

void generate_dcu_info_json(void)
{
	uint8_t idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDCU_GEN_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDcuDevId%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.dcu_dev_id,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNumSerPort%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.num_ser_port,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNumEthPort%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.num_eth_port,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cMeterType%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.meter_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDataFormatType%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.data_format_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDataTrfType%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.data_trf_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cMasterProtoType%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.master_proto_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDbgLogEnable%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.dbglog_enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDcuDevLoc%c:%c%s%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.dcu_location,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDcuGpsLoc%c:%c%s%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.dcu_gps_loc,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDbgLogIp%c:%c%s%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.dbglog_ip,DBL_QT);
	strcat(json_text,temp_text);
	
	for(idx=0; idx<MAX_NUM_MASTER;idx++)
	{
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cMasterIp_%dEnable%c:%c%d%c,\n",
		DBL_QT,idx+1,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.enable_allow_master_ip[idx],DBL_QT);
		
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		if(idx==MAX_NUM_MASTER-1)
		{
			sprintf(temp_text,"%cMaster_%dIp%c:%c%s%c\n",
			DBL_QT,idx+1,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.allow_master_ip[idx],DBL_QT);
		}
		else
		{
			sprintf(temp_text,"%cMaster_%dIp%c:%c%s%c,\n",
			DBL_QT,idx+1,DBL_QT,DBL_QT,dlms_dcu_config.dlms_dcu_info.allow_master_ip[idx],DBL_QT);
		}
		
		strcat(json_text,temp_text);
	}
	
	strcat(json_text,"}\n");
	strcat(json_text,"}");
	
	store_json_text(DCU_INFO_JSON);
}

void generate_ntp_info_json(void)
{
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNTP_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNtp1Enable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ntp_cfg.enable_ntp1,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNtp2Enable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ntp_cfg.enable_ntp2,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNtp1Port%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ntp_cfg.ntp1_port,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNtp2Port%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ntp_cfg.ntp2_port,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cInterval%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ntp_cfg.interval,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNtp2IpAddr%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ntp_cfg.ntp2_ip_addr,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNtp1IPAddr%c:%c%s%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ntp_cfg.ntp1_ip_addr,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"}\n");
	strcat(json_text,"}");
	
	store_json_text(NTP_INFO_JSON);
	
}
void generate_dcu_eth_info_json(void)
{
	uint8_t idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cDCU_ETH_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNumDcuEth%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ethernate_cfg.num_dcu_eth_port,DBL_QT);
	strcat(json_text,temp_text);
	
	for(idx=0;idx<MAX_NUM_DCU_ETH;idx++)
	{
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cDcuEth%dIp%c:%c%s%c,\n",
		DBL_QT,idx+1,DBL_QT,DBL_QT,dlms_dcu_config.ethernate_cfg.eth_cfg[idx].ip_addr,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		sprintf(temp_text,"%cDcuEth%dGw%c:%c%s%c,\n",
		DBL_QT,idx+1,DBL_QT,DBL_QT,dlms_dcu_config.ethernate_cfg.eth_cfg[idx].gateway,DBL_QT);
		strcat(json_text,temp_text);
		
		memset(temp_text,0,sizeof(temp_text));
		
		if(idx==MAX_NUM_DCU_ETH-1)
			sprintf(temp_text,"%cDcuEth%dNetMask%c:%c%s%c\n",
			DBL_QT,idx+1,DBL_QT,DBL_QT,dlms_dcu_config.ethernate_cfg.eth_cfg[idx].netmask,DBL_QT);
		else
			sprintf(temp_text,"%cDcuEth%dNetMask%c:%c%s%c,\n",
			DBL_QT,idx+1,DBL_QT,DBL_QT,dlms_dcu_config.ethernate_cfg.eth_cfg[idx].netmask,DBL_QT);
		
		strcat(json_text,temp_text);
	}
	
	strcat(json_text,"}\n");
	
	strcat(json_text,"}");
	
	store_json_text(DCU_ETH_INFO_JSON);
}

void generate_gprs_info_json(void)
{
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cGPRS_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cGprsEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.enable_gprs,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPingInterval%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.ping_int,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNumPing%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.num_pings,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cConnType%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.conn_type,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPingEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.enable_ping,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPing1IpAddr%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.ping1_ip_addr,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPing2IpAddr%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.ping2_ip_addr,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cAccPtName%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.access_pt_name,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPhoneNum%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.phone_num,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPassword%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.password,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cUserName%c:%c%s%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.gprs_cfg.username,DBL_QT);
	strcat(json_text,temp_text);

	strcat(json_text,"}\n");
	
	strcat(json_text,"}");
	
	store_json_text(GPRS_INFO_JSON);
}

void generate_ftp_server_info_json(void)
{
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cFTP_SER_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEnable%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ftp_ser_cfg.enable,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cSerPort%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ftp_ser_cfg.ser_port,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cUploadPeriod%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ftp_ser_cfg.upload_period,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cLocDir%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ftp_ser_cfg.loc_dir,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPassword%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ftp_ser_cfg.password,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cUserName%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ftp_ser_cfg.username,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cSerIp%c:%c%s%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.ftp_ser_cfg.ser_ip,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"}\n");
	
	strcat(json_text,"}");
	
	store_json_text(FTP_SER_INFO_JSON);
}

void generate_vpn_info_json(void)
{
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cVPN_INFO%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cVpnEnable%c:%c%d%c,\n",DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.enable_vpn,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPptpCfg%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cConnName%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.pptp_cfg.conn_name,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cLocUserName%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.pptp_cfg.loc_username,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cLocPassword%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.pptp_cfg.loc_password,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cRemUserName%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.pptp_cfg.remote_username,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cRemPassword%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.pptp_cfg.remote_password,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cReqMemoryMap%c:%c%d%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.pptp_cfg.req_mmpe128,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"},\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cIpSecCfg%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cKeyLifeTime%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.key_life_time,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cAggrMode%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.aggr_mode,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cNatTrav%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.nat_trav,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPfs%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.pfs,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cTunnelName%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.tunnel_name,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPreSharedKey%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.pre_shared_key,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cRightIp%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.right_ip,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cRightSubnet%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.right_subnet,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cRightId%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.right_id,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cLeft%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.left,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cLeftSubnet%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.left_subnet,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cLeftId%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.left_id,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cLeftSrcIp%c:%c%s%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.left_src_ip,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cKeyingMode%c:%c%s%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.ipsec_cfg.keying_mode,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"},\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPhaseCfg%c:\n",DBL_QT,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPhase1DhGrp%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.phase_cfg1.dhgrp,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPhase2DhGrp%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.phase_cfg2.dhgrp,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPhase1Encrpt%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.phase_cfg1.encrpt,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPhase2Encrpt%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.phase_cfg2.encrpt,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPhase1Authen%c:%c%d%c,\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.phase_cfg1.authen,DBL_QT);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPhase2Authen%c:%c%d%c\n",
	DBL_QT,DBL_QT,DBL_QT,dlms_dcu_config.vpn_cfg.phase_cfg2.authen,DBL_QT);
	strcat(json_text,temp_text);
	
	strcat(json_text,"}\n");
	
	strcat(json_text,"}\n");
	
	strcat(json_text,"}\n");
	
	store_json_text(VPN_INFO_JSON);
}

void generate_cfg_json(void)
{
	generate_dcu_info_json();
	generate_ser_meter_info_json();
	generate_eth_meter_info_json();
	generate_iec104_info_json();
	generate_modtcp_info_json();
	generate_dcu_poll_info_json();
	generate_mqtt_info_json();
	generate_cms_ems_info_json();
	generate_ntp_info_json();
	generate_dcu_eth_info_json();
	generate_gprs_info_json();
	generate_vpn_info_json();
	generate_ftp_server_info_json();
}
#endif

/* End Of File */