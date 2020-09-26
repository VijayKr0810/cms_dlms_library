#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/home/iot-gateway/hiredis/hiredis.h"

#include "websocket.h"

#include "base64.h"
#include "log.h"
#include "gslist.h"
#include "sha1.h"
#include "xmalloc.h"

#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
#include "dlms_api.h"
#include "dlms_fun.h"
#include "nxjson.h"
#include "web_back_end.h"

/* Extern */
extern redisContext 			*p_redis_handler;
extern redisReply 				*p_redis_reply;
extern dlms_dcu_config_t 		dlms_dcu_config;

/* proto type */
int32_t send_org_client(WSClient * client, WSOpcode opcode, char *msg, int32_t len);
/* Structure */

/* Globals */
int 							g_send_cliend_fd;
int32_t 						g_ser_baud[16]={0,50,75,110,200,300,600,1200,2400,4800,9600,19200,38400,57600,115200};
char 							g_inf_mode_buff[3][16]={"","RS232_MODE","RS485_MODE"};
char 							g_parity_buff[3][16]={"None","EVEN","ODD"};
char 							g_conn_type_buff[4][16]={"","2G_TYPE","3G_TYPE","4G_TYPE"};
char 							g_vpn_type_buff[4][16]={"No","IPSEC","PPTP"};
char 							g_file_format_buff[4][16]={"Not Supported","CSV","CDF"};
char 							g_met_type_buff[4][16]={"","Serial","Ethernet","Both"};

char 							g_poll_type_buff[4][16]={"","PERIODIC","SCHEDULE"};

WSClient 						*p_client;
WSOpcode 						g_opcode;

/*********************************************************************
*Function 		: modbus_crc16()
*In Params 		: buffer and length.
*Output 		: None
*Return			: calculated crc of received buffer.
*Description 	: To calculate crc for given buffer.
**********************************************************************/

uint16_t modbus_crc16(char *data,int32_t cnt)
{
	uint32_t	i,j;
    uint16_t	temp,temp2=0,flag;

    temp=0xFFFF;
	
	for (i=0; i<cnt; i++)
	{
		temp=temp^(data[i]&0xFF);
		for (j=1; j<=8; j++)
		{
			flag=(temp&0x0001);
			temp=(temp>>1);
			if (flag) 
			{
				temp=(temp ^ 0xA001);
			}
		}
    }
	
	temp2=temp >> 8;
	temp=(temp << 8) | temp2;
	temp &= 0xFFFF;
	
	//printf("Calculated CRC : %X\n",temp);
	
	return(temp);
}

void create_cfg_file(void)
{
	static char fun_name[]="create_cfg_file()";
	
	FILE *p_file_ptr=NULL;
	
	p_file_ptr=fopen("/usr/cms/config/dlms_api_config.cfg","w");
	
	if(p_file_ptr==NULL)
	{
		dbg_log(REPORT,"%-20s : Failed to open config file, Error : %s\n",fun_name,strerror(errno));
		return ;
	}
	
	dlms_dcu_config.start_flag=START_END_FLAG;
	dlms_dcu_config.crc=modbus_crc16((char*)&dlms_dcu_config,sizeof(dlms_dcu_config_t)-6);
	
	dlms_dcu_config.end_flag=START_END_FLAG;
	
	fwrite(&dlms_dcu_config, sizeof(dlms_dcu_config_t),1,p_file_ptr);

	fclose(p_file_ptr);
	
	dbg_log(REPORT,"%-20s : Updated Config file has written successfully\n",fun_name);
}

void set_ip_addr(void)
{
	uint8_t idx=0;
	char 	cmd_str[128];
	
	for(idx=0; idx<MAX_NUM_DCU_ETH; idx++)
	{
		memset(cmd_str,0,sizeof(cmd_str));
		sprintf(cmd_str,"/usr/cms/bin/cms_create_nw_inf %s %s %s eth%d",
		dlms_dcu_config.ethernate_cfg.eth_cfg[idx].ip_addr,
		dlms_dcu_config.ethernate_cfg.eth_cfg[idx].netmask,
		dlms_dcu_config.ethernate_cfg.eth_cfg[idx].gateway,idx);
		
		system(cmd_str);
	
		memset(cmd_str,0,sizeof(cmd_str));
		sprintf(cmd_str,"cp /etc/network/interfaces1 /etc/network/interfaces");
					
		system(cmd_str);
	}
}

void restart_unit(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cRESTART_UNIT%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATATYPE%c:%cRESTART_UNIT%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	system("/sbin/poweroff");
}

void update_config_restart_procs(uint32_t seq_num)
{
	static  char fun_name[]="update_config_restart_procs()";
	
	uint8_t idx=0, need_to_set_ip=0;
	char *p_gen_ptr=NULL;
	
	create_cfg_file();
	
	for(idx=0; idx<MAX_NUM_DCU_ETH; idx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_ETH_INFO DcuEth%dIp",idx+1);
		
		if(p_redis_reply!=NULL)
		{
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				if(strcmp(p_gen_ptr,dlms_dcu_config.ethernate_cfg.eth_cfg[idx].ip_addr)!=0)
				{
					dbg_log(INFORM,"%-20s : Device Ip got change, PrevIp : %s, NewIp : %s\n",
					fun_name,p_gen_ptr,dlms_dcu_config.ethernate_cfg.eth_cfg[idx].ip_addr);
					need_to_set_ip=1;
					break;
				}
			}
		}
	}
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cSAVENAPPLY_CFG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATATYPE%c:%cSAVENAPPLY_CFG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	
	send_msg(json_text);
	
	
	sleep(10);
	//dbg_log(INFORM,"%-20s : Killing cms mon proc\n",fun_name);
	
	//system("killall cms_mon_proc");
	
	sleep(2);
	
	if(need_to_set_ip)
	{
		dbg_log(INFORM,"%-20s : Ip got updated, need to update interface file\n",fun_name);
		
		set_ip_addr();
		
		dbg_log(INFORM,"%-20s : Ip Setted, restating network\n",fun_name);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset reboot_msg reboot_status %d process_name %s reason %s",1,"save_reset_ip","configuration_updation_from_device_webPage");
	  
	  freeReplyObject(p_redis_reply);
	  
		//system("/etc/init.d/S40network restart");
	}
	else
	{
		dbg_log(INFORM,"%-20s : Device Ip does not change, PrevIp : %s, NewIp : %s\n",
					fun_name,p_gen_ptr,dlms_dcu_config.ethernate_cfg.eth_cfg[0].ip_addr);
					
		p_redis_reply = redisCommand(p_redis_handler,"hmset reboot_msg reboot_status %d process_name %s reason %s",1,"save_reset","configuration_updation_from_device_webPage");
		
		freeReplyObject(p_redis_reply);	
	}
}

int32_t send_dlms_inst_master_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_INST_MAST_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cGET_DLMS_MASTER_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(INST_MASTER_OBIS_PARAMS_JSON,"InstParams");
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	//printf("\n%s\n",json_text);
	
	//send_org_client(p_client, g_opcode, json_text, strlen(json_text));
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_ls_master_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_LS_MAST_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cGET_DLMS_MASTER_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(LS_MASTER_OBIS_PARAMS_JSON,"LsParams");
	
	strcat(json_text,"}"); // End of Json
	
	printf("send_dlms_ls_master_param_cfg_det : Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	
	//strcat(json_text,"!"); 
	//send_org_client(p_client, g_opcode, json_text, strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_bill_master_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_BILL_MAST_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cGET_DLMS_MASTER_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(BILL_MASTER_OBIS_PARAMS_JSON,"BillParams");
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_dp_master_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_MN_MAST_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cGET_DLMS_MASTER_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(DP_MASTER_OBIS_PARAMS_JSON,"DpParams");
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_event_master_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_EVENT_MAST_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cGET_DLMS_MASTER_PARAM_LIST%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(EVENT_MASTER_OBIS_PARAMS_JSON,"EventParams");  
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_dp_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_MN_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cDLMS_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(DP_OBIS_PARAMS_JSON,"DpParams");
	
	strcat(json_text,"}"); // End of Json
	
	printf("\n%s\n",json_text);
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_inst_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_INST_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cDLMS_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(INST_OBIS_PARAMS_JSON,"InstParams");

	strcat(json_text,"}"); // End of Json
	
	printf("\n%s\n",json_text);
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_event_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_EVENT_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cDLMS_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(EVENT_OBIS_PARAMS_JSON,"EventParams"); 

	strcat(json_text,"}"); // End of Json
	
	printf("\n%s\n",json_text);
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_bill_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_BILL_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cDLMS_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(BILL_OBIS_PARAMS_JSON,"BillParams");
	
	strcat(json_text,"}"); // End of Json
	
	printf("\n%s\n",json_text);
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_ls_param_cfg_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_LS_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cDLMS_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	fill_user_obis_det(LS_OBIS_PARAMS_JSON,"LsParams");
	
	strcat(json_text,"}"); // End of Json
	
	printf("\n%s\n",json_text);
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_cyclic_inst_data_det(uint32_t seq_num)
{
	uint8_t tot_num_meters=0, meter_type=0,file_num_param=0;
	uint8_t idx;
	
	char 	*p_loc_data=NULL;
	char 	*p_loc_data1=NULL;
	char 	*p_loc_data2=NULL;
	int32_t file_fd=0;
	struct 	stat obis_st;
	
	if(stat(INST_OBIS_PARAMS_JSON,&obis_st)==-1)
	{
		printf("can't Find original file - %s\n", INST_OBIS_PARAMS_JSON);
	}
	
	p_loc_data=malloc(obis_st.st_size+1);
	p_loc_data1=malloc(obis_st.st_size+4);
	p_loc_data2=malloc(obis_st.st_size+5);
	
	memset(p_loc_data,0,(obis_st.st_size+1));
	memset(p_loc_data1,0,(obis_st.st_size+4));
	memset(p_loc_data2,0,(obis_st.st_size+5));
	
	file_fd=open(INST_OBIS_PARAMS_JSON, O_RDONLY);
	if (file_fd == -1) 
	{
		printf("can't open to read original file - %s\n", INST_OBIS_PARAMS_JSON);
	}
	
	if (obis_st.st_size != read(file_fd, p_loc_data, obis_st.st_size)) 
	{
		printf("can't read original file - %s\n", INST_OBIS_PARAMS_JSON);
		close(file_fd);
	}
	else
	{
		printf("tot bytes read from user json file : %ld\n",obis_st.st_size);
	}
	
	sprintf(p_loc_data1,"%s",p_loc_data);
	
	close(file_fd);
	
	const   nx_json *p_root_value = NULL;
	const   nx_json *p_gen_trav = NULL;
	const   nx_json *p_item_trav = NULL;
	const char *p_gen_ptr=NULL;
	const char *gen_ptr=NULL;
	
	strcpy(p_loc_data2, p_loc_data1);
	
	p_root_value = nx_json_parse(p_loc_data1,0);

	if (p_root_value != NULL) 
	{
		p_gen_trav = nx_json_get(p_root_value,"InstParams");
		if(p_gen_trav != NULL)
		{
			p_gen_ptr = nx_json_get(p_gen_trav,"NumParams")->text_value;
			printf("p_gen_ptr : %s\n",p_gen_ptr);
			if(p_gen_ptr!=NULL)
			{
				file_num_param = atoi(p_gen_ptr);
			}
			else
			{
				printf("InstParams(): failed to get NumParams\n");
			}
		}
		else
		{
			printf("failed to get InstParams\n");
		}
	}
	
	nx_json_free(p_root_value);
	
	printf("total NUM_PARAM from File : %d\n",file_num_param);
	
	obis_param_val_info_t user_obis_param_val[file_num_param];
	
	p_root_value = nx_json_parse(p_loc_data2,0);

	if (p_root_value != NULL) 
	{
		p_gen_trav = nx_json_get(p_root_value,"InstParams");
		if(p_gen_trav != NULL)
		{
			const nx_json *obis_list_trav=NULL;
			
			obis_list_trav = nx_json_get(p_gen_trav,"ObisCodeList");
			if(obis_list_trav != NULL)
			{
				for(idx=0; idx<file_num_param; idx++)
				{
					p_item_trav = nx_json_item(obis_list_trav, idx);
					if(p_item_trav!=NULL)
					{
						p_gen_ptr = nx_json_get(p_item_trav,"obis")->text_value;
						if(p_gen_ptr!=NULL)
						{
							strcpy(user_obis_param_val[idx].obis_code,p_gen_ptr);
						}
						else
						{
							printf("ObisCodeList(): failed to get Item obis for idx : %d\n",idx);
						}
						
						p_gen_ptr = nx_json_get(p_item_trav,"assign")->text_value;
						if(p_gen_ptr!=NULL)
						{
							strcpy(user_obis_param_val[idx].param_name,p_gen_ptr);
						}
						else
						{
							printf("ObisCodeList(): failed to get Item assign for idx : %d\n",idx);
						}
					}
					else
					{
						printf("ObisCodeList(): failed to get Item for idx : %d\n",idx);
					}
				}
			}
			else
			{
				printf("failed to get ObisCodeList\n");
			}
		}
		else
		{
			printf("failed to get InstParams\n");
		}
	}
	else
	{
		printf("Improper Json format\n");
	}

	free(p_loc_data);
	free(p_loc_data1);
	free(p_loc_data2);
	nx_json_free(p_root_value);
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cCYCLIC_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cCYCLIC_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO MeterType");
	if(p_redis_reply!=NULL)
	{
		if(p_redis_reply->element[0]->str!=NULL)
		{
			meter_type=atoi(p_redis_reply->element[0]->str);
			
			if(atoi(p_redis_reply->element[0]->str)==1)
				tot_num_meters=MAX_NO_OF_METER_PER_PORT*MAX_NO_OF_SERIAL_PORT;
			else if((atoi(p_redis_reply->element[0]->str)==2))
				tot_num_meters=MAX_NO_OF_ETH_METER;
			else
				tot_num_meters=MAX_NO_OF_METER_PER_PORT*MAX_NO_OF_SERIAL_PORT;
		}
	}
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNUM_METERS%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,tot_num_meters,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cINST_PARAM%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	
	uint8_t meter_idx=0;
	if(meter_type==1)
	{
		uint8_t pidx;
		for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
		{
			uint8_t midx;
			for(midx=0; midx<MAX_NO_OF_METER_PER_PORT; midx++)
			{
				uint8_t status=0;
				uint8_t num_params=0;
				
				strcat(json_text,"{");
				char 	key_name[32];
				memset(key_name,0,sizeof(key_name));
				sprintf(key_name,"Port%dMet%d%s",pidx,midx,INST_INFO_KEY);
				p_redis_reply = redisCommand(p_redis_handler, "HMGET %s NUM_PARAM",key_name);
				if(p_redis_reply!=NULL)
				{
					if(p_redis_reply->element[0]->str!=NULL)
					{
						num_params=atoi(p_redis_reply->element[0]->str);
					}
				}
				
				freeReplyObject(p_redis_reply);
				
				printf("total NUM_PARAM from meter : %d\n",num_params);
				
				obis_param_val_info_t met_obis_param_val[num_params];
				
				for(idx=0; idx<num_params; idx++)
				{
					memset(key_name,0,sizeof(key_name));
					sprintf(key_name,"Port%dMet%d%s",pidx,midx,INST_INFO_KEY);
					p_redis_reply = redisCommand(p_redis_handler, "HMGET %s Obis_%d Value_%d",key_name,idx+1,idx+1);
					if(p_redis_reply!=NULL)
					{
						gen_ptr = p_redis_reply->element[0]->str;
						if(gen_ptr!=NULL)
						{
							strcpy(met_obis_param_val[idx].obis_code,gen_ptr);
						}
						else
						{
							//printf("HMGET Failed to get param obis for idx : %d\n",idx);
						}
						
						gen_ptr = p_redis_reply->element[1]->str;
						if(gen_ptr!=NULL)
						{
							strcpy(met_obis_param_val[idx].param_val,gen_ptr);
						}
						else
						{
							//printf("HMGET Failed to get param value for idx : %d\n",idx);
						}
						
						freeReplyObject(p_redis_reply);
					}
				}
	
				p_redis_reply = redisCommand(p_redis_handler, "HMGET Port%dMet%dSerNum SER_NUM",pidx,midx);
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cMET_SERNUM%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"",DBL_QUOTES);
				if(p_redis_reply!=NULL)
				{
					if(p_redis_reply->element[0]->str!=NULL)
					{
						memset(g_temp_str,0,sizeof(g_temp_str));
						sprintf(g_temp_str,"%cMET_SERNUM%c:%c%s%c,\n",
						DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_redis_reply->element[0]->str,DBL_QUOTES);
					}
					
				}
				strcat(json_text,g_temp_str);
				
				p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSerMeter_%dConfig MeterLoc",pidx,midx+1);
				if(p_redis_reply!=NULL)
				{
					if(p_redis_reply->element[0]->str!=NULL)
					{
						memset(g_temp_str,0,sizeof(g_temp_str));
						sprintf(g_temp_str,"%cMET_LOC%c:%c%s%c,",
						DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_redis_reply->element[0]->str,DBL_QUOTES);
						strcat(json_text,g_temp_str);
					}
				}
				
				memset(key_name,0,sizeof(key_name));
				sprintf(key_name,"Port%dMet%d%s",pidx,midx,INST_INFO_KEY);
				p_redis_reply = redisCommand(p_redis_handler, "HMGET %s UPDATE_TIME",key_name);
				if(p_redis_reply!=NULL)
				{
					if(p_redis_reply->element[0]->str!=NULL)
					{
						memset(g_temp_str,0,sizeof(g_temp_str));
						sprintf(g_temp_str,"%cUPDATE_TIME%c:%c%s%c,",
						DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_redis_reply->element[0]->str,DBL_QUOTES);
						strcat(json_text,g_temp_str);
					}
				}
				
				p_redis_reply = redisCommand(p_redis_handler, "HMGET SerPort%dMet%dStatus VALUE",pidx,midx);
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cCOMM_STATUS%c:%c%d%c,",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,status,DBL_QUOTES);
				
				if(p_redis_reply!=NULL)
				{
					if(p_redis_reply->element[0]->str!=NULL)
					{
						status = atoi(p_redis_reply->element[0]->str);
						memset(g_temp_str,0,sizeof(g_temp_str));
						sprintf(g_temp_str,"%cCOMM_STATUS%c:%c%d%c,",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,status,DBL_QUOTES);
					}
				}
				
				strcat(json_text,g_temp_str);
				
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cNUM_PARAM%c:%c%d%c,\n",
				DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,file_num_param,DBL_QUOTES);
				strcat(json_text,g_temp_str);
				
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cPARAMS%c:\n",DBL_QUOTES,DBL_QUOTES);
				strcat(json_text,g_temp_str);
	
				strcat(json_text,"[\n");
				for(idx=0; idx<file_num_param; idx++)
				{
					uint8_t jdx;
					strcat(json_text,"{");
					for(jdx=0; jdx<num_params; jdx++)
					{
						if(strcmp(user_obis_param_val[idx].obis_code, met_obis_param_val[jdx].obis_code)==0)
						{
							memset(g_temp_str,0,sizeof(g_temp_str));
							sprintf(g_temp_str,"%cPN%c:%c%s%c,",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,user_obis_param_val[idx].param_name,DBL_QUOTES);
							strcat(json_text,g_temp_str);
						
							memset(g_temp_str,0,sizeof(g_temp_str));
							sprintf(g_temp_str,"%cPV%c:%c%s%c",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,met_obis_param_val[jdx].param_val,DBL_QUOTES);
							strcat(json_text,g_temp_str);
							
							break;
						}
					}
					
					if(jdx==num_params)
					{
						memset(g_temp_str,0,sizeof(g_temp_str));
						sprintf(g_temp_str,"%cPN%c:%c%s%c,",
						DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,user_obis_param_val[idx].param_name,DBL_QUOTES);
						strcat(json_text,g_temp_str);
					
						memset(g_temp_str,0,sizeof(g_temp_str));
						sprintf(g_temp_str,"%cPV%c:%c%s%c",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"NA",DBL_QUOTES);
						strcat(json_text,g_temp_str);
					}

					if(idx==file_num_param-1)
						strcat(json_text,"}");
					else
						strcat(json_text,"},");
				}
				
				strcat(json_text,"]\n"); // End of PARAMS
				
				if(meter_idx==tot_num_meters-1)
					strcat(json_text,"}\n");
				else
					strcat(json_text,"},\n");
				
				printf("Completed for meter_idx : %d\n",meter_idx);
				
				meter_idx++;
			}
		}
	}
	
	strcat(json_text,"]\n");// End of INST_PARAM
	
	strcat(json_text,"}\n"); // End of DATA
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	//printf("\n%s\n",json_text);
	
	send_msg(json_text);
	
	return RET_SUCCESS;
}

int32_t send_dlms_cfg_det(uint32_t seq_num)
{
	char *p_gen_ptr=NULL;
	uint8_t idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_DLMS_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cDLMS_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDLMSCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO ReadPrevLsData MeterType FaultTolSupp");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cReadPrevLsData%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cMeterType%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_met_type_buff[atoi(p_gen_ptr)],DBL_QUOTES);
			//DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_met_type_buff[2],DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cFaultTolSupp%c:%c%s%c,\n",
			//DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cMaxMeters%c:%c%d%c,\n",
		DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,MAX_NO_OF_METER_PER_PORT*MAX_NO_OF_SERIAL_PORT,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	printf("getting INST_POLL_INFO Enable\n");
	p_redis_reply = redisCommand(p_redis_handler,"hmget INST_POLL_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableInstData%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	printf("getting BILL_POLL_INFO Enable\n");
	p_redis_reply = redisCommand(p_redis_handler,"hmget BILL_POLL_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableBillingData%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	printf("getting EVENT_POLL_INFO Enable\n");
	p_redis_reply = redisCommand(p_redis_handler,"hmget EVENT_POLL_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableEventData%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	printf("getting DP_POLL_INFO Enable\n");
	p_redis_reply = redisCommand(p_redis_handler,"hmget DP_POLL_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableMidnightData%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	printf("getting LS_POLL_INFO Enable\n");
	p_redis_reply = redisCommand(p_redis_handler,"hmget LS_POLL_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableLSData%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cMidnightPollPer%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,1,DBL_QUOTES);
	strcat(json_text,g_temp_str);
			
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cBillingPollPer%c:%c%d%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,2,DBL_QUOTES);
	strcat(json_text,g_temp_str);
			
	strcat(json_text,"},\n"); // End of DLMSGenCfg

	printf("getting DLMSEthMetCfg\n");
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDLMSEthMetCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	uint8_t tot_eth_num_meters=0;
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget ETH_MET_INFO NumMeters");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			tot_eth_num_meters = atoi(p_gen_ptr);
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNumMeters%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
			
			printf(">>>ETH_MET_INFO NumMeters : %d\n",atoi(p_gen_ptr));
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cEthMeters%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	//for(idx=0; idx<MAX_NO_OF_ETH_METER; idx++)
	for(idx=0; idx<tot_eth_num_meters; idx++)
	{
		strcat(json_text,"{\n");
		
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cTO%c:%c%d%c,",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,2,DBL_QUOTES);
		strcat(json_text,g_temp_str);
		
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cRetCnt%c:%c%d%c,",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,3,DBL_QUOTES);
		strcat(json_text,g_temp_str);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmget EthMeter_%dConfig Enable MeterPass MeterIp MeterLoc Port",idx+1);
		if(p_redis_reply!=NULL)
		{
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cEnable%c:%c%d%c,",
				DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[1]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cPwd%c:%c%d%c,",
				DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[2]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cIp%c:%c%d%c,",
				DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[3]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cLoc%c:%c%s%c,",
				DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[4]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cPort%c:%c%d%c",
				DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
		}
		
		freeReplyObject(p_redis_reply);
		//if(idx==MAX_NO_OF_ETH_METER-1)
		if(idx==tot_eth_num_meters-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}
	
	strcat(json_text,"]\n");
	
	strcat(json_text,"},\n"); // End of DLMSEthMetCfg
	
	uint8_t port_idx=0;
	printf("getting DLMSPortSerMetCfg\n");
	
	for (port_idx=0; port_idx<MAX_NO_OF_SERIAL_PORT; port_idx++)
	{
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cDLMSP%dMetCfg%c:\n",DBL_QUOTES,port_idx,DBL_QUOTES);
		strcat(json_text,g_temp_str);
		
		/* strcat(json_text,"{\n");
	
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cDLMSSerMetCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
		strcat(json_text,g_temp_str); */
		
		strcat(json_text,"{\n");
		
		uint8_t tot_ser_num_met=0;
		
		p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSER_MET_INFO NumMeters",port_idx);
		if(p_redis_reply!=NULL)
		{
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				tot_ser_num_met = atoi(p_gen_ptr);
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cNumMeters%c:%c%d%c,\n",
				DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
				strcat(json_text,g_temp_str);
				
				//printf(">>>NumMeters : %d\n",atoi(p_gen_ptr));
			}
			else 
				goto EXIT;
			
			freeReplyObject(p_redis_reply);
		}
		
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cMeters%c:\n",DBL_QUOTES,DBL_QUOTES);
		strcat(json_text,g_temp_str);
		
		strcat(json_text,"[\n");
		//for(idx=0; idx<MAX_NO_OF_METER_PER_PORT; idx++)
		for(idx=0; idx<tot_ser_num_met; idx++)
		{
			strcat(json_text,"{\n");
			
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cTO%c:%c%d%c,",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,2,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cRetCnt%c:%c%d%c,",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,3,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		
			p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSerMeter_%dConfig Enable MeterAddrSize MeterAddr MeterPass MeterLoc",port_idx,idx+1);
		
			if(p_redis_reply!=NULL)
			{
				p_gen_ptr=p_redis_reply->element[0]->str;
				if(p_gen_ptr!=NULL)
				{
					memset(g_temp_str,0,sizeof(g_temp_str));
					sprintf(g_temp_str,"%cEnable%c:%c%d%c,",
					DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
					strcat(json_text,g_temp_str);
				}
				else 
					goto EXIT;
				
				p_gen_ptr=p_redis_reply->element[1]->str;
				if(p_gen_ptr!=NULL)
				{
					memset(g_temp_str,0,sizeof(g_temp_str));
					sprintf(g_temp_str,"%cAddrType%c:%c%d%c,",
					DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
					strcat(json_text,g_temp_str);
				}
				else 
					goto EXIT;
				
				p_gen_ptr=p_redis_reply->element[2]->str;
				if(p_gen_ptr!=NULL)
				{
					memset(g_temp_str,0,sizeof(g_temp_str));
					sprintf(g_temp_str,"%cAddr%c:%c%d%c,",
					DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
					strcat(json_text,g_temp_str);
				}
				else 
					goto EXIT;
				
				p_gen_ptr=p_redis_reply->element[3]->str;
				if(p_gen_ptr!=NULL)
				{
					memset(g_temp_str,0,sizeof(g_temp_str));
					sprintf(g_temp_str,"%cPwd%c:%c%s%c,",
					DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
					strcat(json_text,g_temp_str);
				}
				else 
					goto EXIT;
				
				p_gen_ptr=p_redis_reply->element[4]->str;
				if(p_gen_ptr!=NULL)
				{
					memset(g_temp_str,0,sizeof(g_temp_str));
					sprintf(g_temp_str,"%cLoc%c:%c%s%c",
					DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
					strcat(json_text,g_temp_str);
				}
				else 
					goto EXIT;
			}
			
			freeReplyObject(p_redis_reply);
			//if(idx==MAX_NO_OF_METER_PER_PORT-1)
			if(idx==tot_ser_num_met-1)
				strcat(json_text,"}\n");
			else
				strcat(json_text,"},\n");
		}
		
		strcat(json_text,"]\n");
		
		/* strcat(json_text,"}\n"); // End of DLMSSerMetCfg */
		
		if(port_idx==MAX_NO_OF_SERIAL_PORT-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
		
	} // End of DLMSSerMetCfg Port wise
	
	strcat(json_text,"}\n"); // End of DATA
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	send_msg(json_text);
	
	printf("Sucess\n");
	return RET_SUCCESS;
	
	EXIT:
		printf("Failure\n");
		return RET_NO_RESP;
}

int32_t send_upstream_cfg_det(uint32_t seq_num)
{
	char *p_gen_ptr=NULL;
	uint8_t idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_UPSTREAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cUPSTREAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cUpstreamDataCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget FTP_SER_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cFtpPushSupp%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget MQTT_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cMQTTSupp%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget CMS_EMS_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cCMSEMSSupp%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}

	memset(g_temp_str,0,sizeof(g_temp_str)); // Hard Coded
	sprintf(g_temp_str,"%cSMSSupp%c:%c%s%c,\n",
	DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"No",DBL_QUOTES);
	strcat(json_text,g_temp_str);
			
	p_redis_reply = redisCommand(p_redis_handler,"hmget IEC104_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cIEC104Supp%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget MODTCP_INFO Enable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cModTcpSupp%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO DataFormatType");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cFileFormatSupp%c:%c%s%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_file_format_buff[atoi(p_gen_ptr)],DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	strcat(json_text,"},\n"); //end of UpstreamDataCfg
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cIEC104Cfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget IEC104_INFO AsduAddr CotSize IoaSize CycInterval IecPort StDataIoa StDevStatusIoa");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cStationAddr%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cCotSize%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cIoaSize%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cCycInt%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPortNo%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cMetStartIoa%c:%c%d%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;

		freeReplyObject(p_redis_reply);
	}
	
	strcat(json_text,"},\n"); // End of IEC104Cfg
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSMSCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNoOfPhoneNum%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,1,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDetails%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"["); 
	
	strcat(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cName%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"User",DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNum%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"8080XXXXX",DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"}\n");
	
	strcat(json_text,"]\n"); 
	
	strcat(json_text,"},\n"); // End of SMSCfg

	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cModTcpCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget MODTCP_INFO RespAllId SlaveId HoldRegStAddr InputRegStAddr ReadCoilStAddr ReadDiscStAddr Port");
	
	//printf("MODTCP_INFO Total num of elements : %d\n",p_redis_reply->elements);
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cRespToAllSlaveId%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cModDevId%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cHoldRegStartAddr%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cInputRegStartAddr%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cReadCoilStartAddr%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cReadDiscriteInputStartAddr%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[6]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPortNo%c:%c%d%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	strcat(json_text,"},\n"); // End of ModTcpCfg
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cFtpServerCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget FTP_SER_INFO SerPort UploadPeriod LocDir Password UserName SerIp DiffLogSer LogSerPort LogUploadPeriod LogLocDir LogPassword LogUserName LogSerIp");
	
	//printf("FTP_SER_INFO Total num of elements : %d\n",p_redis_reply->elements);
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPortNo%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cUploadPeriod%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cRemoteDir%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPassword%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cUserName%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cServerIp%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[6]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cDiffServerForLogs%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[7]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLogPortNo%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[8]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLogUploadPeriod%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[9]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLogRemoteDir%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[10]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLogPassword%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[11]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLogUserName%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[12]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLogServerIp%c:%c%s%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;

		freeReplyObject(p_redis_reply);
	}
	
	strcat(json_text,"},\n"); // End of FtpServerCfg
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cMQTTCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget MQTT_INFO BrokerIp BrokerPass BrokerUname BrokerPort PerDataTopic CmdSubTopic DiagTopicEnable DiagPubTopic EventTopicEnable EventPubTopic PubHr PubMint PubSec");
	
	//printf("MQTT_INFO Total num of elements : %d\n",p_redis_reply->elements);
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cBrokerIp%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPassword%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cUserName%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPortNo%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cCycDataTopic%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cCmdTopic%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[6]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableDiagTopics%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[7]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cDiagTopic%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[8]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableEventTopics%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[9]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEventTopic%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[10]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPubHr%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[11]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPubMint%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[12]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cCycPeriod%c:%c%d%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;

		freeReplyObject(p_redis_reply);
	}
	
	strcat(json_text,"},\n"); // End of MQTTCfg
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMSEMSCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget CMS_EMS_INFO BrokerIp BrokerPort EventSendEnable DiagSendEnable PubHr PubMint PubSec");
	
	//printf("CMSEMSCfg Total num of elements : %d\n",p_redis_reply->elements);
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cBrokerIp%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPortNo%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
				p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableEvent%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableDiag%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPubHr%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPubMint%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[6]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cCycPeriod%c:%c%d%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	strcat(json_text,"}\n"); // End of CMSEMSCfg
	
	strcat(json_text,"}\n"); // End of DATA
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	send_msg(json_text);
	
	printf("Sucess\n");
	return RET_SUCCESS;
	
	EXIT:
		printf("Failure\n");
		return RET_NO_RESP;
}

int32_t send_gen_config_det(uint32_t seq_num)
{
	char *p_gen_ptr=NULL;
	uint8_t idx=0;
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_GEN_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cGEN_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cGenCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO DcuDevId DcuDevLoc DbgLogEnable DbgLogIp DbgLogLevel SerNum");
	//printf("Total num of elements for dcu general : %d\n",p_redis_reply->elements);
	
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cDcuID%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_redis_reply->element[0]->str),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLocation%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(p_redis_reply->element[1]->str),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableDbgLog%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_redis_reply->element[2]->str))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cSerNum%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(p_redis_reply->element[5]->str),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cDbgLogLevel%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_redis_reply->element[4]->str),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cDbgLogIp%c:%c%s%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(p_redis_reply->element[3]->str),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
	}

	strcat(json_text,"},\n"); // End of GenCfg
	
	printf("getting EthCfg info\n");
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cEthCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_ETH_INFO NumDcuEth");
	
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNumEthPorts%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
	}
	freeReplyObject(p_redis_reply);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cEthCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[\n");
	for(idx=0;idx<MAX_NUM_DCU_ETH;idx++)
	{
		strcat(json_text,"{\n");
		
		p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_ETH_INFO DcuEth%dIp DcuEth%dGw DcuEth%dNetMask",idx+1,idx+1,idx+1);
		//freeReplyObject(p_redis_reply);
		if(p_redis_reply!=NULL)
		{
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cCurrIp%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cNewIp%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[1]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cGW%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[2]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cNetMask%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
		}
		freeReplyObject(p_redis_reply);
		if(idx==MAX_NUM_DCU_ETH-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}
	
	strcat(json_text,"]\n");
	
	strcat(json_text,"},\n"); // End of EthCfg
	
	printf("getting SerPortCfg info\n");
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSerPortCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_SERIAL_INFO NumDcuSer");
	
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNumSerPorts%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
	}
	
	freeReplyObject(p_redis_reply);
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cPortCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"[");
	
	for(idx=0; idx<MAX_NO_OF_SERIAL_PORT; idx++)
	{
		strcat(json_text,"{");
		
		p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_SERIAL_INFO DcuSer%dBaudrate DcuSer%dDataBits DcuSer%dStopBits DcuSer%dParity DcuSer%dInfMode",idx+1,idx+1,idx+1,idx+1,idx+1);
		
		if(p_redis_reply!=NULL)
		{
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cBaudRate%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_ser_baud[atoi(p_gen_ptr)],DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[1]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cDatabits%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[2]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cStopbits%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[3]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cParity%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_parity_buff[atoi(p_gen_ptr)],DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[4]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cInfMode%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_inf_mode_buff[atoi(p_gen_ptr)],DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
		}
		
		freeReplyObject(p_redis_reply);
		if(idx==MAX_NO_OF_SERIAL_PORT-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}
	
	strcat(json_text,"]");
	
	strcat(json_text,"},"); // end Of SerPortCfg
	
	printf("getting AllowedMasterCfg info\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cAllowedMasterCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO EnableAllowedMaster");
	
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableAllowMaster%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
	}
	
	freeReplyObject(p_redis_reply);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cAllowedMasterList%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);

	strcat(json_text,"[\n");
	for(idx=0; idx<MAX_NUM_MASTER;idx++)
	{
		strcat(json_text,"{");
		
		p_redis_reply = redisCommand(p_redis_handler,"hmget DCU_GEN_INFO MasterIp_%dEnable Master_%dIp",idx+1,idx+1);
		
		if(p_redis_reply!=NULL)
		{
			p_gen_ptr=p_redis_reply->element[0]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cEnable%c:%c%s%c,",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
			
			p_gen_ptr=p_redis_reply->element[1]->str;
			if(p_gen_ptr!=NULL)
			{
				memset(g_temp_str,0,sizeof(g_temp_str));
				sprintf(g_temp_str,"%cIp%c:%c%s%c",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
				strcat(json_text,g_temp_str);
			}
			else 
				goto EXIT;
		}
		
		freeReplyObject(p_redis_reply);
		if(idx==MAX_NUM_MASTER-1)
			strcat(json_text,"}\n");
		else
			strcat(json_text,"},\n");
	}
	
	strcat(json_text,"]\n");
	strcat(json_text,"},\n"); // end Of AllowedMasterCfg
	
	printf("getting NtpCfg info\n");
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cNtpCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget NTP_INFO Ntp1Enable Ntp2Enable Ntp1Port Ntp2Port Interval Ntp1IpAddr Ntp2IpAddr");
	
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableNtp1%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableNtp2%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNtpPort1%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNtpPort2%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cInterval%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNtpIpAddr1%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		p_gen_ptr=p_redis_reply->element[6]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNtpIpAddr2%c:%c%s%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
	}
	
	freeReplyObject(p_redis_reply);
	strcat(json_text,"},\n"); // end of NtpCfg
	
	printf("getting ModemCfg info\n");
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cModemCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget GPRS_INFO GprsEnable PingInterval NumPing ConnType PingEnable Ping1IpAddr AccPtName PhoneNum Password UserName");
	
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableModem%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPingInt%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNumPings%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cConnType%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_conn_type_buff[atoi(p_gen_ptr)],DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnablePing%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cIpAddr%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[6]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cAccessPtName%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[7]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPhoneNum%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[8]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPassword%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[9]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cUsername%c:%c%s%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
	}
	
	freeReplyObject(p_redis_reply);
	strcat(json_text,"},\n"); // end of ModemCfg
	
	printf("getting VpnCfg info\n");
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cVpnCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget VPN_INFO VpnEnable");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEnableVpn%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,(atoi(p_gen_ptr))?"Yes":"No",DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		printf("getting vpn Type info : %d\n",atoi(p_gen_ptr));
		
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cType%c:%c%s%c,\n",
		DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,g_vpn_type_buff[(atoi(p_gen_ptr))],DBL_QUOTES);
		strcat(json_text,g_temp_str);
			
		freeReplyObject(p_redis_reply);
	}
	
	printf("getting ipsec info\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cIPSecConfig%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	strcat(json_text,"{\n");
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget IPSECCFG KeyLifeTime AggrMode NatTrav Pfs TunnelName PreSharedKey RightIp RightId Left LeftSubnet LeftId LeftSrcIp KeyingMode RightSubnet");
	
	//printf("IPSECCFG, tot num of elements : %d\n",p_redis_reply->elements);
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cKeyLifeTime%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cAggrMode%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNatTrav%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPfs%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cTunnelName%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[5]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cPreSharedKey%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[6]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cRightIp%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[7]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cRightId%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
/* 		p_gen_ptr=p_redis_reply->element[8]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cKeyLifeTime%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT; */
		
		p_gen_ptr=p_redis_reply->element[9]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLeftSubnet%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[10]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLeftId%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[12]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cKeyingMode%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[13]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cRightSubnet%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	printf("Phase1, tot num of elements : %d\n",p_redis_reply->elements);
	p_redis_reply = redisCommand(p_redis_handler,"hmget Phase1 DhGrp Encrpt Authen");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cDhGrp%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEncrpt%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cAuthen%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	printf("Phase2, tot num of elements : %d\n",p_redis_reply->elements);
	p_redis_reply = redisCommand(p_redis_handler,"hmget Phase2 DhGrp Encrpt Authen");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cDhGrp2%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cEncrpt2%c:%c%d%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cAuthen2%c:%c%d%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		freeReplyObject(p_redis_reply);
	}
	
	strcat(json_text,"},\n"); // end of IPSecConfig
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cPPTPCfg%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	strcat(json_text,"{\n");

	p_redis_reply = redisCommand(p_redis_handler,"hmget PPTPCFG LocUserName LocPassword RemUserName RemPassword ReqMemoryMap");
	if(p_redis_reply!=NULL)
	{
		p_gen_ptr=p_redis_reply->element[0]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLocalUName%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[1]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cLocalPwd%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[2]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cRemUName%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[3]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cRemPass%c:%c%s%c,\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_gen_ptr,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		p_gen_ptr=p_redis_reply->element[4]->str;
		if(p_gen_ptr!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cReq_mmpe128%c:%c%d%c\n",
			DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_gen_ptr),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		else 
			goto EXIT;
		
		freeReplyObject(p_redis_reply);
	}
	
	strcat(json_text,"}\n"); // end of PPTPCfg
	
	strcat(json_text,"}\n"); // end of VpnCfg
	
	strcat(json_text,"}\n"); // End of DATA
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	send_msg(json_text);
	
	printf("Sucess\n");
	return RET_SUCCESS;
	
	EXIT:
		printf("GET_GEN_CONFIG Failure\n");
		return RET_NO_RESP;
}

int32_t send_set_upstream_cfg_det(uint32_t seq_num, char *temp_json)
{
	static char fun_name[]="send_set_gen_cfg_det()";
	int32_t 	idx=0,cnt=0;
	char 		*update_json = NULL;
	char 		status[32];
	
	for(idx=0; idx<strlen(temp_json); idx++)
	{
		if(temp_json[idx]=='{')
		{
			cnt++;
			if(cnt>=2)
			{
				printf("Found point where need to copy\n");
				
				uint32_t update_len = 0;
				
				update_len = &temp_json[idx]-temp_json;
				
				printf("Need to copy bytes : %d\n",strlen(temp_json)-update_len);
				
				update_json = (char*)malloc(strlen(temp_json)-update_len+1);
				memset(update_json,0,strlen(temp_json)-update_len+1);
				
				memcpy(update_json, &temp_json[idx],strlen(temp_json)-update_len-1);
				
				printf("copied all bytes. %d : \n",strlen(update_json));
				
				break;
			}
		}
	}
	
	const   nx_json *root_value=NULL;
	const   nx_json *json_trav=NULL, *gen_trav=NULL;
	const   nx_json *item_trav=NULL;
	const char  	*gen_ptr=NULL;

	memset(status,0,sizeof(status));
	
	root_value = nx_json_parse(update_json, 0);
	if (root_value != NULL) 
	{
		strcpy(status,"SUCCESS");
		gen_trav = nx_json_get(root_value,"UpstreamDataCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"FtpPushSupp")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ftp_ser_cfg.enable=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("UpstreamDataCfg(): getting FtpPushSupp failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"MQTTSupp")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.mqtt_cfg.enable=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("UpstreamDataCfg(): getting MQTTSupp failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"CMSEMSSupp")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.cms_ems_cfg.enable=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("UpstreamDataCfg(): getting CMSEMSSupp failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"SMSSupp")->text_value;
			if(gen_ptr != NULL)
			{
				//dlms_dcu_config.cms_ems_cfg.enable=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("UpstreamDataCfg(): getting SMSSupp failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"IEC104Supp")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.iec104_slave_cfg.enable=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("UpstreamDataCfg(): getting IEC104Supp failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"ModTcpSupp")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.modtcp_slave_cfg.enable=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("UpstreamDataCfg(): getting ModTcpSupp failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"FileFormatSupp")->text_value;
			if(gen_ptr != NULL)
			{
				uint8_t loc_idx;
				for(loc_idx=0; loc_idx<4; loc_idx++)
				{
					if(strcmp(gen_ptr, g_file_format_buff[loc_idx])==0)
					{
						break;
					}
				}
				dlms_dcu_config.dlms_dcu_info.data_format_type=loc_idx;
			}
			else
			{
				printf("UpstreamDataCfg(): getting FileFormatSupp failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");
		
		gen_trav = nx_json_get(root_value,"IEC104Cfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"StationAddr")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.iec104_slave_cfg.asdu_addr = atoi(gen_ptr);
			}
			else
			{
				printf("IEC104Cfg(): getting StationAddr failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"MetStartIoa")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.iec104_slave_cfg.start_data_ioa = atoi(gen_ptr);
			}
			else
			{
				printf("IEC104Cfg(): getting MetStartIoa failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"CycInt")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.iec104_slave_cfg.cyclic_int = atoi(gen_ptr);
			}
			else
			{
				printf("IEC104Cfg(): getting CycInt failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"PortNo")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.iec104_slave_cfg.iec_port = atoi(gen_ptr);
			}
			else
			{
				printf("IEC104Cfg(): getting PortNo failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"IoaSize")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.iec104_slave_cfg.ioa_size = atoi(gen_ptr);
			}
			else
			{
				printf("IEC104Cfg(): getting IoaSize failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"CotSize")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.iec104_slave_cfg.cot_size = atoi(gen_ptr);
			}
			else
			{
				printf("IEC104Cfg(): getting CotSize failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");
		
		gen_trav = nx_json_get(root_value,"ModTcpCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"ModDevId")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.modtcp_slave_cfg.slave_id = atoi(gen_ptr);
			}
			else
			{
				printf("ModTcpCfg(): getting ModDevId failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"RespToAllSlaveId")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.modtcp_slave_cfg.resp_all_id = strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("ModTcpCfg(): getting RespToAllSlaveId failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"PortNo")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.modtcp_slave_cfg.port = atoi(gen_ptr);
			}
			else
			{
				printf("ModTcpCfg(): getting PortNo failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"HoldRegStartAddr")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.modtcp_slave_cfg.hold_reg_start_addr = atoi(gen_ptr);
			}
			else
			{
				printf("ModTcpCfg(): getting HoldRegStartAddr failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"InputRegStartAddr")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.modtcp_slave_cfg.input_reg_start_addr = atoi(gen_ptr);
			}
			else
			{
				printf("ModTcpCfg(): getting InputRegStartAddr failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"ReadDiscriteInputStartAddr")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.modtcp_slave_cfg.read_disc_start_addr = atoi(gen_ptr);
			}
			else
			{
				printf("ModTcpCfg(): getting ReadDiscriteInputStartAddr failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"ReadCoilStartAddr")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.modtcp_slave_cfg.read_coil_start_addr = atoi(gen_ptr);
			}
			else
			{
				printf("ModTcpCfg(): getting ReadCoilStartAddr failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");
		
		gen_trav = nx_json_get(root_value,"CMSEMSCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"PortNo")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.cms_ems_cfg.broker_port = atoi(gen_ptr);
			}
			else
			{
				printf("CMSEMSCfg(): getting PortNo failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"BrokerIp")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.cms_ems_cfg.broker_ip,gen_ptr);
			}
			else
			{
				printf("CMSEMSCfg(): getting BrokerIp failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EnableEvent")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.cms_ems_cfg.event_send_enable=strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("CMSEMSCfg(): getting EnableEvent failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"CycPeriod")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.cms_ems_cfg.pub_int_sec=atoi(gen_ptr);
			}
			else
			{
				printf("CMSEMSCfg(): getting CycPeriod failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EnableDiag")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.cms_ems_cfg.diag_send_enable=strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("CMSEMSCfg(): getting EnableDiag failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");
		
		gen_trav = nx_json_get(root_value,"MQTTCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"BrokerIp")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.mqtt_cfg.broker_ip,gen_ptr);
			}
			else
			{
				printf("MQTTCfg(): getting BrokerIp failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"CycPeriod")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.mqtt_cfg.pub_int_sec=atoi(gen_ptr);
			}
			else
			{
				printf("CMSEMSCfg(): getting CycPeriod failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"UserName")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.mqtt_cfg.username,gen_ptr);
			}
			else
			{
				printf("MQTTCfg(): getting UserName failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"Password")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.mqtt_cfg.password,gen_ptr);
			}
			else
			{
				printf("MQTTCfg(): getting Password failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"CycDataTopic")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.mqtt_cfg.periodic_data_topic,gen_ptr);
			}
			else
			{
				printf("MQTTCfg(): getting CycDataTopic failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"CmdTopic")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.mqtt_cfg.cmd_sub_topic,gen_ptr);
			}
			else
			{
				printf("MQTTCfg(): getting CmdTopic failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EventTopic")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.mqtt_cfg.event_pub_topic,gen_ptr);
			}
			else
			{
				printf("MQTTCfg(): getting EventTopic failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EnableDiagTopics")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.mqtt_cfg.diag_topic_enable=strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("MQTTCfg(): getting EnableDiagTopics failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EnableEventTopics")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.mqtt_cfg.event_topic_enable=strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("MQTTCfg(): getting EnableEventTopics failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"DiagTopic")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.mqtt_cfg.diag_pub_topic,gen_ptr);
			}
			else
			{
				printf("MQTTCfg(): getting DiagTopic failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"PortNo")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.mqtt_cfg.broker_port=atoi(gen_ptr);
			}
			else
			{
				printf("MQTTCfg(): getting PortNo failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");

		gen_trav = nx_json_get(root_value,"FtpServerCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"UploadPeriod")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ftp_ser_cfg.upload_period = atoi(gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting UploadPeriod failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"LogUploadPeriod")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ftp_ser_cfg.log_upload_period = atoi(gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting LogUploadPeriod failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"PortNo")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ftp_ser_cfg.ser_port = atoi(gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting PortNo failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"LogPortNo")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ftp_ser_cfg.log_ser_port = atoi(gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting LogPortNo failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"DiffServerForLogs")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ftp_ser_cfg.diff_log_ser = strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("FtpServerCfg(): getting DiffServerForLogs failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"UserName")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.ftp_ser_cfg.username,gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting UserName failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"LogUserName")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.ftp_ser_cfg.log_username,gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting LogUserName failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"Password")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.ftp_ser_cfg.password,gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting Password failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"LogPassword")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.ftp_ser_cfg.log_password,gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting LogPassword failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"RemoteDir")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.ftp_ser_cfg.loc_dir,gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting RemoteDir failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"LogRemoteDir")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.ftp_ser_cfg.log_loc_dir,gen_ptr);
			}
			else
			{
				printf("FtpServerCfg(): getting LogRemoteDir failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");
	}
	else
	{
		printf("parsing failed - improper config file format\n");
		strcpy(status,"FAILURE");
	}
	
	nx_json_free(root_value);
	
	if(update_json!=NULL)
		free(update_json);
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cSET_UPSTREAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cUPSTREAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,status,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	
	send_msg(json_text);
	
	//update_config_restart_procs();
	
	return RET_SUCCESS;
}

int32_t send_set_dlms_cfg_det(uint32_t seq_num, char *temp_json)
{
	static char fun_name[]="send_set_gen_cfg_det()";
	int32_t 	idx=0,cnt=0;
	char 		*update_json = NULL;
	char 		status[32];
	
	for(idx=0; idx<strlen(temp_json); idx++)
	{
		if(temp_json[idx]=='{')
		{
			cnt++;
			if(cnt>=2)
			{
				printf("Found point where need to copy\n");
				
				uint32_t update_len = 0;
				
				update_len = &temp_json[idx]-temp_json;
				
				printf("Need to copy bytes : %d\n",strlen(temp_json)-update_len);
				
				update_json = (char*)malloc(strlen(temp_json)-update_len+1);
				memset(update_json,0,strlen(temp_json)-update_len+1);
				
				memcpy(update_json, &temp_json[idx],strlen(temp_json)-update_len-1);
				
				printf("copied all bytes. %d : \n",strlen(update_json));
				
				break;
			}
		}
	}
	
	//printf("\n%s\n",update_json);
	
	const   nx_json *root_value=NULL;
	const   nx_json *json_trav=NULL, *gen_trav=NULL;
	const   nx_json *item_trav=NULL;
	const char  	*gen_ptr=NULL;

	memset(status,0,sizeof(status));
	
	root_value = nx_json_parse(update_json, 0);
	if (root_value != NULL) 
	{
		strcpy(status,"SUCCESS");
		gen_trav = nx_json_get(root_value,"DLMSCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"ReadPrevLsData")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dlms_dcu_info.read_prev_ls_data = strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("DLMSCfg(): getting ReadPrevLsData failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"FaultTolSupp")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dlms_dcu_info.fault_to_1_supp = strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("DLMSCfg(): getting FaultTolSupp failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"MeterType")->text_value;
			if(gen_ptr != NULL)
			{
				uint8_t loc_idx;
				for(loc_idx=0; loc_idx<3; loc_idx++)
				{
					if(strcmp(gen_ptr, g_met_type_buff[loc_idx])==0)
						break;
				}
				dlms_dcu_config.dlms_dcu_info.meter_type = loc_idx;
			}
			else
			{
				printf("DLMSCfg(): getting MeterType failed\n");
				strcpy(status,"FAILURE");
			}

			gen_ptr = nx_json_get(gen_trav,"EnableInstData")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dcu_poll_info.inst_poll_info.enable = strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("DLMSCfg(): getting EnableInstData failed\n");
				strcpy(status,"FAILURE");
			}
			
			
			gen_ptr = nx_json_get(gen_trav,"EnableLSData")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dcu_poll_info.ls_poll_info.enable = strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("DLMSCfg(): getting EnableLSData failed\n");
				strcpy(status,"FAILURE");
			}
			
			
			gen_ptr = nx_json_get(gen_trav,"EnableMidnightData")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.enable = strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("DLMSCfg(): getting EnableMidnightData failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"MidnightPollPer")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_hr = atoi(gen_ptr);
			}
			else
			{
				printf("DLMSCfg(): getting MidnightPollPer failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EnableEventData")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dcu_poll_info.event_poll_info.enable = strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("DLMSCfg(): getting EnableEventData failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EnableBillingData")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dcu_poll_info.bill_poll_info.enable = strcmp(gen_ptr,"Yes")?0:1;
			}
			else
			{
				printf("DLMSCfg(): getting Enable failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"BillingPollPer")->text_value;
			if(gen_ptr != NULL)
			{
				
				dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_hr = atoi(gen_ptr);
			}
			else
			{
				printf("DLMSCfg(): getting BillingPollPer failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");


		gen_trav = nx_json_get(root_value,"DLMSEthMetCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"NumMeters")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.eth_meter_cfg.num_meter = atoi(gen_ptr);
			}
			else
			{
				printf("DLMSEthMetCfg(): getting NumMeters failed\n");
				strcpy(status,"FAILURE");
			}
			
			const nx_json *eth_met_trav=NULL;
			eth_met_trav=nx_json_get(gen_trav,"EthMeters");
			if(eth_met_trav != NULL)
			{
				for(idx=0; idx<dlms_dcu_config.eth_meter_cfg.num_meter; idx++)
				{
					item_trav = nx_json_item(eth_met_trav, idx);
					if(item_trav!=NULL)
					{
						gen_ptr = nx_json_get(item_trav,"Enable")->text_value;
						if(gen_ptr != NULL)
						{
							dlms_dcu_config.eth_meter_cfg.eth_param[idx].enable = strcmp(gen_ptr,"Yes")?0:1;
						}
						else
						{
							printf("EthMeters(): getting Enable failed ItemId : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
		
						gen_ptr = nx_json_get(item_trav,"Port")->text_value;
						if(gen_ptr != NULL)
						{
							dlms_dcu_config.eth_meter_cfg.eth_param[idx].port = atoi(gen_ptr);
						}
						else
						{
							printf("EthMeters(): getting Port failed for ItemId : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"Pwd")->text_value;
						if(gen_ptr != NULL)
						{
							strcpy(dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_pass,gen_ptr);
						}
						else
						{
							printf("EthMeters(): getting MeterPass failed for ItemId : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"Loc")->text_value;
						if(gen_ptr != NULL)
						{
							strcpy(dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_loc,gen_ptr);
						}
						else
						{
							printf("EthMeters(): getting MeterLoc failed for ItemId : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"Ip")->text_value;
						if(gen_ptr != NULL)
						{
							strcpy(dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_ipaddr,gen_ptr);
						}
						else
						{
							printf("EthMeters(): getting MeterIp failed for ItemId : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
					}
					else
					{
						printf("EthMeters() : Failed to get EthMeters details for ItemId : %d\n",idx);
						strcpy(status,"FAILURE");
						break;
					}
				}
			}
			else
			{
				printf("DLMSEthMetCfg(): getting NumMeters failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");
		
		uint8_t pidx=0;
		char 	port_det_buff[32];
		
		for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
		{
			memset(port_det_buff,0,sizeof(port_det_buff));
			sprintf(port_det_buff,"DLMSP%dMetCfg",pidx);
			
			gen_trav = nx_json_get(root_value,port_det_buff);
			if(gen_trav != NULL)
			{
				gen_ptr = nx_json_get(gen_trav,"NumMeters")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.dlms_channel_cfg[pidx].num_meter = atoi(gen_ptr);
				}
				else
				{
					printf("DLMSSerMetCfg(): getting NumMeters failed for PortId : %d\n", pidx);
					strcpy(status,"FAILURE");
					break;
				}
				
				const nx_json *ser_met_trav=NULL;
				
				ser_met_trav=nx_json_get(gen_trav,"Meters");
				if(ser_met_trav != NULL)
				{
					for(idx=0; idx<dlms_dcu_config.dlms_channel_cfg[pidx].num_meter; idx++)
					{
						item_trav = nx_json_item(ser_met_trav, idx);
						if(item_trav!=NULL)
						{
							gen_ptr = nx_json_get(item_trav,"Enable")->text_value;
							if(gen_ptr != NULL)
							{
								dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].enable = atoi(gen_ptr);
							}
							else
							{
								printf("SerMeters(): getting Enable failed for PortId : %d, ItemId : %d\n", pidx,idx);
								strcpy(status,"FAILURE");
								break;
							}
							
							gen_ptr = nx_json_get(item_trav,"AddrType")->text_value;
							if(gen_ptr != NULL)
							{
								dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].meter_addr_size = atoi(gen_ptr);
							}
							else
							{
								printf("SerMeters(): getting AddrType failed for PortId : %d, ItemId : %d\n", pidx,idx);
								strcpy(status,"FAILURE");
								break;
							}
							
							gen_ptr = nx_json_get(item_trav,"Addr")->text_value;
							if(gen_ptr != NULL)
							{
								dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].meter_addr = atoi(gen_ptr);
							}
							else
							{
								printf("SerMeters(): getting MeterAddr failed for PortId : %d, ItemId : %d\n", pidx,idx);
								strcpy(status,"FAILURE");
								break;
							}
							
							gen_ptr = nx_json_get(item_trav,"Pwd")->text_value;
							if(gen_ptr != NULL)
							{
								strcpy(dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].meter_pass,gen_ptr);
							}
							else
							{
								printf("SerMeters(): getting MeterPass failed for PortId : %d, ItemId : %d\n", pidx,idx);
								strcpy(status,"FAILURE");
								break;
							}
							
							gen_ptr = nx_json_get(item_trav,"Loc")->text_value;
							if(gen_ptr != NULL)
							{
								strcpy(dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].meter_loc,gen_ptr);
							}
							else
							{
								printf("SerMeters(): getting MeterLoc failed for PortId : %d, ItemId : %d\n", pidx,idx);
								strcpy(status,"FAILURE");
								break;
							}
						}
						else
						{
							printf("%s() : Failed to get SerMeters details for PortId : %d, Item Id : %d\n",port_det_buff,pidx,idx);
							strcpy(status,"FAILURE");
							break;
						}
					}
				}
				else
				{
					printf("%s() : Failed to get SerMeters details for PortId : %d\n",port_det_buff,pidx);
					strcpy(status,"FAILURE");
					break;
				}
			}
			else
			{
				printf("%s() : Failed to get details for PortId : %d\n",port_det_buff,pidx);
				strcpy(status,"FAILURE");
				break;
			}
		}
	}
	else
	{
		printf("parsing failed - improper config file format\n");
		strcpy(status,"FAILURE");
	}
	
	nx_json_free(root_value);
	
	if(update_json!=NULL)
		free(update_json);
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cSET_DLMS_PARAM_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cDLMS_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,status,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	
	send_msg(json_text);
	
	//update_config_restart_procs();
	
	uint8_t port_idx=0;
	
	for (port_idx=0; port_idx<MAX_NO_OF_SERIAL_PORT; port_idx++)
	{
		for(idx=0; idx<MAX_NO_OF_METER_PER_PORT; idx++)
		{
			printf("Port : %d, Met : %d, > %d,%d,%d,%d,%s,%s\n",port_idx,idx,
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].enable,
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_id,
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_addr_size,
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_addr,
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_pass,
					dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_loc
					);
		}
	}
			
	return RET_SUCCESS;
}

int32_t send_set_dlms_param_cfg_det(uint32_t seq_num, char *temp_json, char *type, char *file_name)
{
	static char fun_name[]="send_set_gen_cfg_det()";
	FILE		*p_file_ptr=NULL;
	int32_t 	idx=0,cnt=0;
	char 		*update_json = NULL;
	char 		status[32];
	
	memset(status,0,sizeof(status));
	strcpy(status,"SUCCESS");
	
	for(idx=0; idx<strlen(temp_json); idx++)
	{
		if(temp_json[idx]=='{')
		{
			cnt++;
			if(cnt>=2)
			{
				printf("Found point where need to copy\n");
				
				uint32_t update_len = 0;
				
				update_len = &temp_json[idx]-temp_json;
				
				printf("Need to copy bytes : %d\n",strlen(temp_json)-update_len);
				
				update_json = (char*)malloc(strlen(temp_json)-update_len+1);
				memset(update_json,0,strlen(temp_json)-update_len+1);
				
				memcpy(update_json, &temp_json[idx],strlen(temp_json)-update_len-1);
				
				printf("copied all bytes. %d : \n",strlen(update_json));
				
				break;
			}
		}
	}
	
	p_file_ptr = fopen(file_name,"w");
	if(p_file_ptr!=NULL)
	{
		fprintf(p_file_ptr,"%s",update_json);
		fflush(p_file_ptr);
		fclose(p_file_ptr);
	}
	else
	{
		printf("Unable to open dlms param file : %s, Error : %s\n",file_name,strerror(errno));
		strcpy(status,"FAILURE");
	}
	
	if(update_json!=NULL)
		free(update_json);
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,type,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cDLMS_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,status,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	
	send_msg(json_text);
	
	//update_config_restart_procs();
	return RET_SUCCESS;
}

void send_version_cfg_det(uint32_t seq_num)
{
	char file_name[]="/srv/www/htdocs/cms_dcu_feature.json";
	char dcu_ser_num[32];
	char dcu_fw_ver[32];
	char dcu_model_num[32];
	char status[32];
	int file_fd;
	
	memset(dcu_ser_num,0,sizeof(dcu_ser_num));
	memset(dcu_fw_ver,0,sizeof(dcu_fw_ver));
	memset(dcu_model_num,0,sizeof(dcu_model_num));
	memset(status,0,sizeof(status));
	
	char *p_loc_data=NULL;
	const char *gen_ptr=NULL;
	
	struct stat file_st;
	
	strcpy(status,"SUCCESS");
	
	if(stat(file_name,&file_st)==-1)
	{
		printf("can't Find original file - %s\n", file_name);
		strcpy(status,"FAILURE");
	}
		
	p_loc_data=malloc(file_st.st_size+1);
	memset(p_loc_data,0,file_st.st_size+1);
	
	file_fd=open(file_name, O_RDONLY);
	if (file_fd == -1) 
	{
		printf("can't open to read original file - %s\n", file_name);
		strcpy(status,"FAILURE");
	}
	
	if (file_st.st_size != read(file_fd, p_loc_data, file_st.st_size)) 
	{
		printf("can't read original file - %s\n", file_name);
		close(file_fd);
		strcpy(status,"FAILURE");
	}
	else
	{
		printf("tot bytes read from user json file : %ld\n",file_st.st_size);
	}
	close(file_fd);
	
	const nx_json *root_value=NULL;

	root_value = nx_json_parse(p_loc_data, 0);
	if (root_value != NULL) 
	{
		gen_ptr = nx_json_get(root_value,"SER_NUM")->text_value;
		if(gen_ptr!=NULL)
		{
			strcpy(dcu_ser_num,gen_ptr);
		}
		else
		{
			strcpy(status,"FAILURE");
		}
		
		gen_ptr = nx_json_get(root_value,"MODEL_NO")->text_value;
		if(gen_ptr!=NULL)
		{
			strcpy(dcu_model_num,gen_ptr);
		}
		else
		{
			strcpy(status,"FAILURE");
		}
		
		gen_ptr = nx_json_get(root_value,"FW_VER")->text_value;
		if(gen_ptr!=NULL)
		{
			strcpy(dcu_fw_ver,gen_ptr);
		}
		else
		{
			strcpy(status,"FAILURE");
		}
	}
	
	free(p_loc_data);
	nx_json_free(root_value);
		
	/* {
"TYPE":"GET_VERSION_CONFIG",
"SEQ_NUM":"4587",
"CMD_TYPE":"VERSION_CONFIG",
"CMD_STATUS":"SUCCESS",
"DATA":
{
    "SER_NUM" : "DCU-DEFAULT-SERNO111",
    "MODEL_NO" : "CS-MDAS-DCU-160X-1001",
    "FW_VER" : "V3.0 27July2020",
}
} */

	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cGET_VERSION_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cVERSION_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,status,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSER_NUM%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,dcu_ser_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cMODEL_NO%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,dcu_model_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cFW_VER%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,dcu_fw_ver,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"}\n"); // End of Data
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	
	send_msg(json_text);

}

int32_t send_set_gen_cfg_det(uint32_t seq_num, char *temp_json)
{
	static char fun_name[]="send_set_gen_cfg_det()";
	int32_t 	idx=0,cnt=0;
	char 		*update_json = NULL;
	char 		status[32];
	
	for(idx=0; idx<strlen(temp_json); idx++)
	{
		if(temp_json[idx]=='{')
		{
			cnt++;
			if(cnt>=2)
			{
				printf("Found point where need to copy\n");
				
				uint32_t update_len = 0;
				
				update_len = &temp_json[idx]-temp_json;
				
				printf("Need to copy bytes : %d\n",strlen(temp_json)-update_len);
				
				update_json = (char*)malloc(strlen(temp_json)-update_len+1);
				memset(update_json,0,strlen(temp_json)-update_len+1);
				
				memcpy(update_json, &temp_json[idx],strlen(temp_json)-update_len-1);
				
				printf("copied all bytes. %d : \n",strlen(update_json));
				
				break;
			}
		}
	}
	
	//printf("\n%s\n",update_json);
	
	const   nx_json *root_value=NULL;
	const   nx_json *json_trav=NULL, *gen_trav=NULL;
	const   nx_json *item_trav=NULL;
	const char  	*gen_ptr=NULL;

	memset(status,0,sizeof(status));
	
	root_value = nx_json_parse(update_json, 0);
	if (root_value != NULL) 
	{
		strcpy(status,"SUCCESS");
		
		gen_trav = nx_json_get(root_value,"GenCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"DcuID")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dlms_dcu_info.dcu_dev_id = atoi(gen_ptr);
			}
			else
			{
				printf("GenCfg(): getting DcuID failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"Location")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.dlms_dcu_info.dcu_location,(gen_ptr));
			}
			else
			{
				printf("GenCfg(): getting Location failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"SerNum")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.dlms_dcu_info.ser_num,(gen_ptr));
			}
			else
			{
				printf("GenCfg(): getting SerNum failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EnableDbgLog")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dlms_dcu_info.dbglog_enable=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("GenCfg(): getting EnableDbgLog failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"DbgLogLevel")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dlms_dcu_info.dbglog_label=atoi(gen_ptr);
			}
			else
			{
				printf("GenCfg(): getting DbgLogLevel failed\n");
				strcpy(status,"FAILURE");
			}
			
			
			gen_ptr = nx_json_get(gen_trav,"DbgLogIp")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.dlms_dcu_info.dbglog_ip,(gen_ptr));
			}
			else
			{
				printf("GenCfg(): getting DbgLogIp failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");
		
		gen_trav = nx_json_get(root_value,"EthCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"NumEthPorts")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dlms_dcu_info.num_eth_port = atoi(gen_ptr);
			}
			else
			{
				printf("EthCfg(): getting NumEthPorts failed\n");
				strcpy(status,"FAILURE");
			}
			
			const   nx_json *eth_trav=NULL;
			
			eth_trav = nx_json_get(gen_trav,"EthCfg");
			if(eth_trav!=NULL)
			{
				for(idx=0; idx<dlms_dcu_config.dlms_dcu_info.num_eth_port; idx++)
				{
					item_trav = nx_json_item(eth_trav, idx);
					if(item_trav!=NULL)
					{
						gen_ptr = nx_json_get(item_trav,"CurrIp")->text_value;
						if(gen_ptr != NULL)
						{
							strcpy(dlms_dcu_config.ethernate_cfg.eth_cfg[idx].ip_addr, gen_ptr);
						}
						else
						{
							printf("EthCfg(): getting CurrIp failed for IDx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"NewIp")->text_value;
						if(gen_ptr != NULL)
						{
							strcpy(dlms_dcu_config.ethernate_cfg.eth_cfg[idx].ip_addr, gen_ptr);
						}
						else
						{
							printf("EthCfg(): getting NewIp failed for IDx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"GW")->text_value;
						if(gen_ptr != NULL)
						{
							strcpy(dlms_dcu_config.ethernate_cfg.eth_cfg[idx].gateway, gen_ptr);
						}
						else
						{
							printf("EthCfg(): getting GW failed for IDx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"NetMask")->text_value;
						if(gen_ptr != NULL)
						{
							strcpy(dlms_dcu_config.ethernate_cfg.eth_cfg[idx].netmask, gen_ptr);
						}
						else
						{
							printf("EthCfg(): getting NetMask failed for IDx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
					}
					else
					{
						printf("EthCfg(): failed to get item for IDx : %d\n",idx);
						strcpy(status,"FAILURE");
						break;
					}
				}
			}
			else
				strcpy(status,"FAILURE");
		}
		else
			strcpy(status,"FAILURE");		
		
		gen_trav = nx_json_get(root_value,"SerPortCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"NumSerPorts")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dlms_dcu_info.num_ser_port = atoi(gen_ptr);
			}
			else
			{
				printf("SerPortCfg(): getting NumSerPorts failed\n");
				strcpy(status,"FAILURE");
			}
			
			const   nx_json *ser_trav=NULL;
			
			ser_trav = nx_json_get(gen_trav,"PortCfg");
			if(ser_trav!=NULL)
			{
				//printf("Tot num of NumSerPorts : %d\n",dlms_dcu_config.dlms_dcu_info.num_ser_port);
				
				for(idx=0; idx<dlms_dcu_config.dlms_dcu_info.num_ser_port; idx++)
				{
					item_trav = nx_json_item(ser_trav, idx);
					if(item_trav!=NULL)
					{
						uint8_t loc_idx;
						gen_ptr = nx_json_get(item_trav,"BaudRate")->text_value;
						if(gen_ptr != NULL)
						{
							for(loc_idx=0; loc_idx<16; loc_idx++)
							{
								if(atoi(gen_ptr)==g_ser_baud[loc_idx])
									break;
							}
							
							dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].baudrate = loc_idx;
						}
						else
						{
							printf("SerPortCfg(): getting BaudRate failed for idx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"Parity")->text_value;
						if(gen_ptr != NULL)
						{
							for(loc_idx=0; loc_idx<3; loc_idx++)
							{
								if(strcmp(gen_ptr,g_parity_buff[loc_idx])==0)
									break;
							}
							
							dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].parity = loc_idx;
						}
						else
						{
							printf("SerPortCfg(): getting Parity failed for idx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"InfMode")->text_value;
						if(gen_ptr != NULL)
						{
							for(loc_idx=0; loc_idx<3; loc_idx++)
							{
								if(strcmp(gen_ptr,g_inf_mode_buff[loc_idx])==0)
									break;
							}
							
							dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].infmode = loc_idx;
						}
						else
						{
							printf("SerPortCfg(): getting InfMode failed for idx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"Databits")->text_value;
						if(gen_ptr != NULL)
						{
							dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].databits = atoi(gen_ptr);
						}
						else
						{
							printf("SerPortCfg(): getting Databits failed for idx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"Stopbits")->text_value;
						if(gen_ptr != NULL)
						{
							dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].stopbits = atoi(gen_ptr);
						}
						else
						{
							printf("SerPortCfg(): getting Stopbits failed for idx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
					}
					else
					{
						printf("SerPortCfg(): getting Item failed for Idx : %d\n",idx);
						strcpy(status,"FAILURE");
						break;
					}
				}
			}
			else
				strcpy(status,"FAILURE");
		}
		else
			strcpy(status,"FAILURE");
		
		gen_trav = nx_json_get(root_value,"AllowedMasterCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"EnableAllowMaster")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.dlms_dcu_info.enable_allow_master=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("AllowedMasterCfg(): getting EnableAllowMaster failed\n");
				strcpy(status,"FAILURE");
			}
			
			const   nx_json *all_mas_trav=NULL;
			
			all_mas_trav = nx_json_get(gen_trav,"AllowedMasterList");
			if(all_mas_trav!=NULL)
			{
				for(idx=0; idx<MAX_NUM_MASTER; idx++)
				{
					item_trav = nx_json_item(all_mas_trav, idx);
					if(item_trav!=NULL)
					{
						gen_ptr = nx_json_get(item_trav,"Enable")->text_value;
						if(gen_ptr!=NULL)
						{
							dlms_dcu_config.dlms_dcu_info.enable_allow_master_ip[idx]=(strcmp(gen_ptr,"Yes")?0:1);
						}
						else
						{
							printf("AllowedMasterCfg(): getting Enable failed for idx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
						
						gen_ptr = nx_json_get(item_trav,"Ip")->text_value;
						if(gen_ptr!=NULL)
						{
							strcpy(dlms_dcu_config.dlms_dcu_info.allow_master_ip[idx],gen_ptr);
						}
						else
						{
							printf("AllowedMasterCfg(): getting Ip failed for idx : %d\n",idx);
							strcpy(status,"FAILURE");
							break;
						}
					}
					else
					{
						printf("AllowedMasterCfg(): getting Item failed for Idx : %d\n",idx);
						strcpy(status,"FAILURE");
						break;
					}
				}
			}
			else
				strcpy(status,"FAILURE");
		}
		else
			strcpy(status,"FAILURE");
		
		gen_trav = nx_json_get(root_value,"NtpCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"EnableNtp1")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ntp_cfg.enable_ntp1=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("NtpCfg(): getting EnableNtp1 failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EnableNtp2")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ntp_cfg.enable_ntp2=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("NtpCfg(): getting EnableNtp2 failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"NtpPort1")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ntp_cfg.ntp1_port=atoi(gen_ptr);
			}
			else
			{
				printf("NtpCfg(): getting NtpPort1 failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"NtpPort2")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ntp_cfg.ntp2_port=atoi(gen_ptr);
			}
			else
			{
				printf("NtpCfg(): getting NtpPort2 failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"Interval")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.ntp_cfg.ntp2_port=atoi(gen_ptr);
			}
			else
			{
				printf("NtpCfg(): getting Interval failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"NtpIpAddr1")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.ntp_cfg.ntp1_ip_addr,gen_ptr);
			}
			else
			{
				printf("NtpCfg(): getting NtpIpAddr1 failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"NtpIpAddr2")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.ntp_cfg.ntp2_ip_addr,gen_ptr);
			}
			else
			{
				printf("NtpCfg(): getting NtpIpAddr2 failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");
		
		gen_trav = nx_json_get(root_value,"ModemCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"EnableModem")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.gprs_cfg.enable_gprs=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("ModemCfg(): getting EnableModem failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"EnablePing")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.gprs_cfg.enable_ping=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("ModemCfg(): getting EnablePing failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"PingInt")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.gprs_cfg.ping_int=atoi(gen_ptr);
			}
			else
			{
				printf("ModemCfg(): getting PingInt failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"NumPings")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.gprs_cfg.num_pings=atoi(gen_ptr);
			}
			else
			{
				printf("ModemCfg(): getting NumPings failed\n");
				strcpy(status,"FAILURE");
			}
			
/* 			gen_ptr = nx_json_get(gen_trav,"ConnType")->text_value;
			if(gen_ptr != NULL)
			{
				for(loc_idx=0; loc_idx<4; loc_idx++)
				{
					if(strcmp(gen_ptr, g_conn_type_buff[loc_idx])==0)
						break;
				}
				
				dlms_dcu_config.gprs_cfg.conn_type=loc_idx;
			}
			else
			{
				printf("ModemCfg(): getting ConnType failed\n");
				strcpy(status,"FAILURE");
			} */
			
			gen_ptr = nx_json_get(gen_trav,"IpAddr")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.gprs_cfg.ping1_ip_addr,gen_ptr);
			}
			else
			{
				printf("ModemCfg(): getting IpAddr failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"AccessPtName")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.gprs_cfg.access_pt_name,gen_ptr);
			}
			else
			{
				printf("ModemCfg(): getting AccessPtName failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"PhoneNum")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.gprs_cfg.phone_num,gen_ptr);
			}
			else
			{
				printf("ModemCfg(): getting PhoneNum failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"Username")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.gprs_cfg.username,gen_ptr);
			}
			else
			{
				printf("ModemCfg(): getting Username failed\n");
				strcpy(status,"FAILURE");
			}
			
			gen_ptr = nx_json_get(gen_trav,"Password")->text_value;
			if(gen_ptr != NULL)
			{
				strcpy(dlms_dcu_config.gprs_cfg.password,gen_ptr);
			}
			else
			{
				printf("ModemCfg(): getting Password failed\n");
				strcpy(status,"FAILURE");
			}
		}
		else
			strcpy(status,"FAILURE");
		
		gen_trav = nx_json_get(root_value,"VpnCfg");
		if(gen_trav != NULL)
		{
			gen_ptr = nx_json_get(gen_trav,"EnableVpn")->text_value;
			if(gen_ptr != NULL)
			{
				dlms_dcu_config.vpn_cfg.enable_vpn=(strcmp(gen_ptr,"Yes")?0:1);
			}
			else
			{
				printf("VpnCfg(): getting EnableVpn failed\n");
				strcpy(status,"FAILURE");
			}
			
			const nx_json *ipsec_ptr=NULL;
			const nx_json *pptp_ptr=NULL;
			
			ipsec_ptr = nx_json_get(gen_trav,"IPSecConfig");
			if(ipsec_ptr != NULL)
			{
				gen_ptr = nx_json_get(ipsec_ptr,"KeyLifeTime")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.ipsec_cfg.key_life_time = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting KeyLifeTime failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"AggrMode")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.ipsec_cfg.aggr_mode = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting AggrMode failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"NatTrav")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.ipsec_cfg.nat_trav = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting NatTrav failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"Pfs")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.ipsec_cfg.pfs = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting Pfs failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"DhGrp")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.phase_cfg1.dhgrp = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting DhGrp failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"DhGrp2")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.phase_cfg2.dhgrp = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting DhGrp2 failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"Encrpt")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.phase_cfg1.encrpt = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting Encrpt failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"Encrpt2")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.phase_cfg2.encrpt = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting Encrpt2 failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"Authen")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.phase_cfg1.authen = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting Authen failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"Authen2")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.phase_cfg2.authen = atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting Authen2 failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"KeyingMode")->text_value;
				if(gen_ptr != NULL)
				{
					strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.keying_mode,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting KeyingMode failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"RightSubnet")->text_value;
				if(gen_ptr != NULL)
				{
					strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.right_subnet,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting RightSubnet failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"LeftId")->text_value;
				if(gen_ptr != NULL)
				{
					strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.left_id,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting LeftId failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"LeftSubnet")->text_value;
				if(gen_ptr != NULL)
				{
					strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.left_subnet,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting LeftSubnet failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"RightId")->text_value;
				if(gen_ptr != NULL)
				{
					strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.right_id,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting RightId failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"RightIp")->text_value;
				if(gen_ptr != NULL)
				{
					stpcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.right_ip,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting RightIp failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"PreSharedKey")->text_value;
				if(gen_ptr != NULL)
				{
					stpcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.pre_shared_key,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting PreSharedKey failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(ipsec_ptr,"TunnelName")->text_value;
				if(gen_ptr != NULL)
				{
					stpcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.tunnel_name,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting TunnelName failed\n");
					strcpy(status,"FAILURE");
				}
			}
			
			pptp_ptr = nx_json_get(gen_trav,"PPTPCfg");
			if(pptp_ptr != NULL)
			{
				gen_ptr = nx_json_get(pptp_ptr,"LocalUName")->text_value;
				if(gen_ptr != NULL)
				{
					strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.loc_username,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting LocalUName failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(pptp_ptr,"LocalPwd")->text_value;
				if(gen_ptr != NULL)
				{
					strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.loc_password,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting LocalPwd failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(pptp_ptr,"RemUName")->text_value;
				if(gen_ptr != NULL)
				{
					strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.remote_username,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting RemUName failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(pptp_ptr,"RemPass")->text_value;
				if(gen_ptr != NULL)
				{
					strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.remote_password,gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting RemPass failed\n");
					strcpy(status,"FAILURE");
				}
				
				gen_ptr = nx_json_get(pptp_ptr,"Req_mmpe128")->text_value;
				if(gen_ptr != NULL)
				{
					dlms_dcu_config.vpn_cfg.pptp_cfg.req_mmpe128=atoi(gen_ptr);
				}
				else
				{
					printf("VpnCfg(): getting Req_mmpe128 failed\n");
					strcpy(status,"FAILURE");
				}
			}
		}
		else
			strcpy(status,"FAILURE");
	}
	else
	{
		printf("parsing failed - improper config file format\n");
		strcpy(status,"FAILURE");
	}
	
	nx_json_free(root_value);
	
	if(update_json!=NULL)
		free(update_json);
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%cSET_GEN_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%u%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_TYPE%c:%cGEN_CONFIG%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,status,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"}"); // End of Json
	
	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	printf("\n%s\n",json_text);
	
	send_msg(json_text);
	
	//update_config_restart_procs();
	
	return RET_SUCCESS;
}

/*********************************************************************
*Function 		: proc_client_msg()
*In Params 		: Void .
*Output 		: Status
*Return			: void.
*Description 	: To proc web client request.
**********************************************************************/
int32_t proc_recv_client_msg(WSClient * client, WSOpcode opcode, int client_fd, char *msg)
{
	static char fun_name[]="proc_client_msg()";
	const   nx_json *p_root_value = NULL;
	const   nx_json *p_gen_trav = NULL;
	const char 	*p_gen_ptr=NULL,*p_other=NULL;
	char send_cmd_str[64];

	uint16_t year=0,year2=0;
	uint8_t	 day=0,mon=0,hr=0,min=0;
	uint8_t	 day2=0,mon2=0,hr2=0,min2=0;
	const char 	*p_time_val_ptr=NULL;
	const   nx_json *p_time_ptr=NULL;
	
	uint32_t idx = 0,seq_num=0;
	
	p_client=client;
	g_opcode=opcode;

	g_send_cliend_fd = client_fd;
	printf("Recv from client : %d, msgLen  : %d\n",g_send_cliend_fd,strlen(msg));
	
	//send_org_client(p_client, g_opcode, msg, strlen(msg));
	
	//return 0;
	
	char *temp_bckp_msg = NULL;
	
	temp_bckp_msg = (char*)malloc(strlen(msg)+1);
	memset(temp_bckp_msg,0,strlen(msg)+1);
	
	strcpy(temp_bckp_msg,msg);

	memset(send_cmd_str,0,sizeof(send_cmd_str));
	p_root_value = nx_json_parse(msg,0);

	if (p_root_value != NULL) 
	{
		p_gen_trav = nx_json_get(p_root_value,"TYPE");
		if(p_gen_trav != NULL)
		{
			p_gen_ptr = nx_json_get(p_root_value,"TYPE")->text_value;
			if(p_gen_ptr != NULL)
			{
				dbg_log(INFORM,"%-20s : Recv Command from client : %s\n",fun_name,p_gen_ptr);
			}
			else
				goto EXIT;
			
			p_gen_ptr = nx_json_get(p_root_value,"SEQ_NUM")->text_value;
			if(p_gen_ptr != NULL)
			{
				dbg_log(INFORM,"%-20s : Recv SEQ_NUM : %s\n",fun_name,p_gen_ptr);
				seq_num = atoi(p_gen_ptr);
			}
			else
				goto EXIT;
			
			p_gen_ptr = nx_json_get(p_root_value,"CMD_TYPE")->text_value;
			if(p_gen_ptr != NULL)
			{
				dbg_log(INFORM,"%-20s : Recv Command Type from client : %s\n",fun_name,p_gen_ptr);
				if(!strcmp(p_gen_ptr,"GET_GEN_CONFIG"))
				{
					send_gen_config_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"CYCLIC_INST"))
				{
					send_cyclic_inst_data_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"RESTART_UNIT"))
				{
					restart_unit(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"SAVENAPPLY_CFG"))
				{
					update_config_restart_procs(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_MODEM_DIAG_MESSAGE"))
				{
					send_modem_status_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_COMMN_STATUS_MESSAGE"))
				{
					send_commn_status_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"SET_GEN_CONFIG"))
				{
					send_set_gen_cfg_det(seq_num, temp_bckp_msg);
				}
				else if(!strcmp(p_gen_ptr,"GET_VERSION_CONFIG"))
				{
					send_version_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_UPSTREAM_CONFIG"))
				{
					send_upstream_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"SET_UPSTREAM_CONFIG"))
				{
					send_set_upstream_cfg_det(seq_num, temp_bckp_msg);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_CONFIG"))
				{
					send_dlms_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"SET_DLMS_CONFIG"))
				{
					send_set_dlms_cfg_det(seq_num,temp_bckp_msg);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_MN_PARAM_CONFIG"))
				{
					send_dlms_dp_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_EVENT_PARAM_CONFIG"))
				{
					send_dlms_event_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_INST_PARAM_CONFIG"))
				{
					send_dlms_inst_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_BILL_PARAM_CONFIG"))
				{
					send_dlms_bill_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_LS_PARAM_CONFIG"))
				{
					send_dlms_ls_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_INST_MAST_PARAM_LIST"))
				{
					send_dlms_inst_master_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_BILL_MAST_PARAM_LIST"))
				{
					send_dlms_bill_master_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_MN_MAST_PARAM_LIST"))
				{
					send_dlms_dp_master_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_LS_MAST_PARAM_LIST"))
				{
					send_dlms_ls_master_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DLMS_EVENT_MAST_PARAM_LIST"))
				{
					send_dlms_event_master_param_cfg_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"SET_DLMS_INST_PARAM_CONFIG"))
				{
					send_set_dlms_param_cfg_det(seq_num,temp_bckp_msg,"SET_DLMS_INST_PARAM_CONFIG",INST_OBIS_PARAMS_JSON);
				}
				else if(!strcmp(p_gen_ptr,"SET_DLMS_LS_PARAM_CONFIG"))
				{
					send_set_dlms_param_cfg_det(seq_num,temp_bckp_msg,"SET_DLMS_LS_PARAM_CONFIG",LS_OBIS_PARAMS_JSON);
				}
				else if(!strcmp(p_gen_ptr,"SET_DLMS_MN_PARAM_CONFIG"))
				{
					send_set_dlms_param_cfg_det(seq_num,temp_bckp_msg,"SET_DLMS_MN_PARAM_CONFIG",DP_OBIS_PARAMS_JSON);
				}
				else if(!strcmp(p_gen_ptr,"SET_DLMS_EVENT_PARAM_CONFIG"))
				{
					send_set_dlms_param_cfg_det(seq_num,temp_bckp_msg,"SET_DLMS_EVENT_PARAM_CONFIG",EVENT_OBIS_PARAMS_JSON);
				}
				else if(!strcmp(p_gen_ptr,"SET_DLMS_BILL_PARAM_CONFIG"))
				{
					send_set_dlms_param_cfg_det(seq_num,temp_bckp_msg,"SET_DLMS_BILL_PARAM_CONFIG",BILL_OBIS_PARAMS_JSON);
				}
				else if(!strcmp(p_gen_ptr,"GET_OD_LS_FILE_LIST"))
				{
					const char *ser_num=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						send_od_ls_file_list_det(seq_num,ser_num);
					}
					else
						goto EXIT;
				}
				else if(!strcmp(p_gen_ptr,"OD_BILLING"))
				{
					const char *ser_num=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						send_od_billing_det(seq_num,ser_num);
					}
					else
						goto EXIT;
				}
				else if(!strcmp(p_gen_ptr,"GET_LS_FILE_LIST"))
				{
					const char *ser_num=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						send_ls_file_list_det(seq_num,ser_num);
					}
					else
						goto EXIT;
				}
				else if(!strcmp(p_gen_ptr,"GET_EVENT_FILE_LIST"))
				{
					const char *ser_num=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						send_event_file_list_det(seq_num,ser_num);
					}
					else
						goto EXIT;
				}
				else if(!strcmp(p_gen_ptr,"GET_DP_FILE_LIST"))
				{
					const char *ser_num=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						send_dp_file_list_det(seq_num,ser_num);
					}
					else
						goto EXIT;
				}
				else if(!strcmp(p_gen_ptr,"GET_BILL_FILE_LIST"))
				{
					const char *ser_num=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						send_bill_file_list_det(seq_num,ser_num);
					}
					else
						goto EXIT;
				}
				else if(!strcmp(p_gen_ptr,"GET_METER_SER_LIST"))
				{
					send_met_ser_num_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"GET_DIR_LIST"))
				{
					send_dir_list_det(seq_num);
				}
				else if(!strcmp(p_gen_ptr,"OD_MID_NIGHT"))
				{
					const char 	*ser_num=NULL;
					const char 	*p_loc_ptr=NULL;
					const char 	*p_loc_ptr1=NULL;
					//int16_t 	year;
					
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						p_loc_ptr = nx_json_get(p_root_value,"YEAR")->text_value;
						if(p_loc_ptr!=NULL)
						{
							//year = atoi(p_loc_ptr);
							
							p_loc_ptr1 = nx_json_get(p_root_value,"MONTH")->text_value;
							if(p_loc_ptr1!=NULL)
							{
								send_od_midnight_det(seq_num,ser_num,atoi(p_loc_ptr1),atoi(p_loc_ptr));
							}
							else
								goto EXIT;
						}
						else
							goto EXIT;
					}
					else
						goto EXIT; 
				}
				else if(!strcmp(p_gen_ptr,"OD_EVENT"))
				{
					const char 	*ser_num=NULL;
					const char 	*p_loc_ptr=NULL;
					
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						p_loc_ptr = nx_json_get(p_root_value,"EVENT_TYPE")->text_value;
						if(p_loc_ptr!=NULL)
						{
							send_od_event_det(seq_num,ser_num,atoi(p_loc_ptr));
						}
						else
							goto EXIT;
					}
					else
						goto EXIT; 
				}
				else if(!strcmp(p_gen_ptr,"OD_INST"))
				{
					const char *ser_num=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						send_od_inst_det(seq_num,ser_num);
					}
					else
						goto EXIT;
				}
				else if(!strcmp(p_gen_ptr,"OD_LS_RANGE"))
				{
					const char *ser_num=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						const nx_json *time_trav=NULL;
						const char 	*p_loc_ptr=NULL;
						
						date_time_t st_date_time,end_date_time;
						
						time_trav = nx_json_get(p_root_value,"START_DT_TIME");
						if(time_trav!=NULL)
						{
							p_loc_ptr = nx_json_get(p_root_value,"YEAR")->text_value;
							if(p_loc_ptr!=NULL)
							{
								st_date_time.year = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
							
							p_loc_ptr = nx_json_get(p_root_value,"MON")->text_value;
							if(p_loc_ptr!=NULL)
							{
								st_date_time.month = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
							
							p_loc_ptr = nx_json_get(p_root_value,"DAY")->text_value;
							if(p_loc_ptr!=NULL)
							{
								st_date_time.day = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
							
							p_loc_ptr = nx_json_get(p_root_value,"HOUR")->text_value;
							if(p_loc_ptr!=NULL)
							{
								st_date_time.hour = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
							
							p_loc_ptr = nx_json_get(p_root_value,"MIN")->text_value;
							if(p_loc_ptr!=NULL)
							{
								st_date_time.minute = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
						}
						
						time_trav = nx_json_get(p_root_value,"END_DATE_TIME");
						if(time_trav!=NULL)
						{
							p_loc_ptr = nx_json_get(p_root_value,"YEAR")->text_value;
							if(p_loc_ptr!=NULL)
							{
								end_date_time.year = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
							
							p_loc_ptr = nx_json_get(p_root_value,"MON")->text_value;
							if(p_loc_ptr!=NULL)
							{
								end_date_time.month = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
							
							p_loc_ptr = nx_json_get(p_root_value,"DAY")->text_value;
							if(p_loc_ptr!=NULL)
							{
								end_date_time.day = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
							
							p_loc_ptr = nx_json_get(p_root_value,"HOUR")->text_value;
							if(p_loc_ptr!=NULL)
							{
								end_date_time.hour = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
						
							p_loc_ptr = nx_json_get(p_root_value,"MIN")->text_value;
							if(p_loc_ptr!=NULL)
							{
								end_date_time.minute = atoi(p_loc_ptr);
							}
							else
								goto EXIT;
						}
						else
							goto EXIT;
							
						send_od_ls_range_det(seq_num,ser_num,st_date_time,end_date_time);
					}
					else
						goto EXIT;
				}
				else if(!strcmp(p_gen_ptr,"GET_DP_FILE_CONTENT"))
				{
					const char *ser_num=NULL,*dir_name=NULL,*file_name=NULL,*view_type=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						dir_name = nx_json_get(p_root_value,"DIR_NAME")->text_value;
						if(dir_name!=NULL)
						{
							file_name = nx_json_get(p_root_value,"FILE_NAME")->text_value;
							if(file_name!=NULL)
							{
								view_type = nx_json_get(p_root_value,"VIEW_TYPE")->text_value;
								if(view_type!=NULL)
								{
									send_dp_file_content(seq_num,ser_num,dir_name,file_name,view_type);
								}
								else
									goto EXIT;
							}
							else
								goto EXIT;
						}
						else
							goto EXIT;
					}
					else
						goto EXIT; 
				}
				else if(!strcmp(p_gen_ptr,"GET_EVENT_FILE_CONTENT"))
				{
					const char *ser_num=NULL,*dir_name=NULL,*file_name=NULL,*view_type=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						dir_name = nx_json_get(p_root_value,"DIR_NAME")->text_value;
						if(dir_name!=NULL)
						{
							file_name = nx_json_get(p_root_value,"FILE_NAME")->text_value;
							if(file_name!=NULL)
							{
								view_type = nx_json_get(p_root_value,"VIEW_TYPE")->text_value;
								if(view_type!=NULL)
								{
									send_event_file_content(seq_num,ser_num,dir_name,file_name,view_type);
								}
								else
									goto EXIT;
							}
							else
								goto EXIT;
						}
						else
							goto EXIT;
					}
					else
						goto EXIT; 
				}
				else if(!strcmp(p_gen_ptr,"GET_BILL_FILE_CONTENT"))
				{
					const char *ser_num=NULL,*dir_name=NULL,*file_name=NULL,*view_type=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						dir_name = nx_json_get(p_root_value,"DIR_NAME")->text_value;
						if(dir_name!=NULL)
						{
							file_name = nx_json_get(p_root_value,"FILE_NAME")->text_value;
							if(file_name!=NULL)
							{
								view_type = nx_json_get(p_root_value,"VIEW_TYPE")->text_value;
								if(view_type!=NULL)
								{
									send_bill_file_content(seq_num,ser_num,dir_name,file_name,view_type);
								}
								else
									goto EXIT;
							}
							else
								goto EXIT;
						}
						else
							goto EXIT;
					}
					else
						goto EXIT; 
				}
				else if(!strcmp(p_gen_ptr,"GET_LS_FILE_CONTENT"))
				{
					const char *ser_num=NULL,*dir_name=NULL,*file_name=NULL,*view_type=NULL;
					ser_num = nx_json_get(p_root_value,"MET_SERNUM")->text_value;
					if(ser_num!=NULL)
					{
						dir_name = nx_json_get(p_root_value,"DIR_NAME")->text_value;
						if(dir_name!=NULL)
						{
							file_name = nx_json_get(p_root_value,"FILE_NAME")->text_value;
							if(file_name!=NULL)
							{
								view_type = nx_json_get(p_root_value,"VIEW_TYPE")->text_value;
								if(view_type!=NULL)
								{
									send_ls_file_content(seq_num,ser_num,dir_name,file_name,view_type);
								}
								else
									goto EXIT;
							}
							else
								goto EXIT;
						}
						else
							goto EXIT;
					}
					else
						goto EXIT; 
				}
				else
					goto EXIT; 
			}
			else
				goto EXIT;
		}
		else
			goto EXIT;
	}
	else
	{
		dbg_log(REPORT,"%-20s : parsing failed - improper json format\n",fun_name);
		sprintf(send_cmd_str,"{\n%cmsg_type%c:%cImproper json%c\n}\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
		send_msg(send_cmd_str);
		
		free(temp_bckp_msg);
		
		return -1;
	}

	dbg_log(INFORM,"%-20s : client request msg responded. Need to free json handler.\n",fun_name);
	nx_json_free(p_root_value);
	
	free(temp_bckp_msg);
	return RET_SUCCESS;
	
	EXIT:
	dbg_log(REPORT,"%-20s : Invalid Command recv from client. send NACK\n",fun_name);
	sprintf(send_cmd_str,"{\n%cmsg_type%c:%cInvalid Commad%c\n}\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	
	send_msg(send_cmd_str);
	
	free(temp_bckp_msg);
	
	return RET_SUCCESS;
}

/* End Of File */