
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/home/iot-gateway/hiredis/hiredis.h"
//#include "hiredis.h"
#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
#include "dlms_api.h"
#include "dlms_fun.h"
#include "nxjson.h"
#include "web_back_end.h"

int32_t send_msg(char *p_recv_msg);

/* Extern */
extern redisContext 			*p_redis_handler;
extern redisReply 				*p_redis_reply;
extern dlms_dcu_config_t 		dlms_dcu_config;

void send_modem_status_det(uint32_t seq_num)
{
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"GET_MODEM_DIAG_MESSAGE",DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATATYPE%c:%cMODEM_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cCMD_STATUS%c:%cSUCCESS%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATA%c:\n",DBL_QUOTES,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	strcat(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cStatus%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget MODEM_DIAG_INFO Status SignalStrength NwType RegStatus Operator IMEI");
	if(p_redis_reply!=NULL)
	{
		if(p_redis_reply->element[0]->str!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cStatus%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_redis_reply->element[0]->str,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		
		if(p_redis_reply->element[1]->str!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cSignalStrength%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_redis_reply->element[0]->str),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		
		if(p_redis_reply->element[2]->str!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNwType%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_redis_reply->element[0]->str),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		
		if(p_redis_reply->element[3]->str!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cRegStatus%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,atoi(p_redis_reply->element[0]->str),DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
		
		if(p_redis_reply->element[4]->str!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cOperator%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_redis_reply->element[0]->str,DBL_QUOTES);
			strcat(json_text,g_temp_str);
			
		}
		
		if(p_redis_reply->element[5]->str!=NULL)
		{
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cIMEI%c:%c%s%c\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,p_redis_reply->element[0]->str,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		}
	}
	
	strcat(json_text,"}\n"); // End of Data
	
	strcat(json_text,"}\n"); // End of Json

	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
}

void send_commn_status_det(uint32_t seq_num)
{
	uint8_t port_idx=0, midx=0;
	char 	port_det[16];
	
	memset(json_text,0,sizeof(json_text));
	memset(g_temp_str,0,sizeof(g_temp_str));
		
	sprintf(json_text,"{\n");
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cTYPE%c:%c%s%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,"GET_COMMN_STATUS_MESSAGE",DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cSEQ_NUM%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,seq_num,DBL_QUOTES);
	strcat(json_text,g_temp_str);
	
	memset(g_temp_str,0,sizeof(g_temp_str));
	sprintf(g_temp_str,"%cDATATYPE%c:%cDLMS_DIAG_MESSAGE%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,DBL_QUOTES);
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
			dlms_dcu_config.dlms_dcu_info.meter_type=atoi(p_redis_reply->element[0]->str);
		}
	}
	
	//printf("MeterType : %s\n",g_met_type_buff[meter_type]);
	
	if(dlms_dcu_config.dlms_dcu_info.meter_type==SER_MET)
	{
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cNUM_PORTS%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,MAX_NO_OF_SERIAL_PORT,DBL_QUOTES);
		strcat(json_text,g_temp_str);
	
		for(port_idx=0; port_idx<MAX_NO_OF_SERIAL_PORT;port_idx++)
		{
			p_redis_reply = redisCommand(p_redis_handler,"hmget P_%dSER_MET_INFO NumMeters",port_idx);
			if(p_redis_reply!=NULL)
			{
				if(p_redis_reply->element[0]->str!=NULL)
				{
					dlms_dcu_config.dlms_channel_cfg[port_idx].num_meter=atoi(p_redis_reply->element[0]->str);
				}
			}
			
			memset(port_det,0,sizeof(port_det));
			sprintf(port_det,"PORT%d",port_idx+1);
			
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%c%s%c:\n",DBL_QUOTES,port_det,DBL_QUOTES);
			strcat(json_text,g_temp_str);
			
			strcat(json_text,"{\n");
			
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cNUM_METERS%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,dlms_dcu_config.dlms_channel_cfg[port_idx].num_meter,DBL_QUOTES);
			strcat(json_text,g_temp_str);
		
			memset(g_temp_str,0,sizeof(g_temp_str));
			sprintf(g_temp_str,"%cSTATUS%c:\n",DBL_QUOTES,DBL_QUOTES);
			strcat(json_text,g_temp_str);
			
			strcat(json_text,"[");
			
			for(midx=0; midx<dlms_dcu_config.dlms_channel_cfg[port_idx].num_meter; midx++)
			{
				p_redis_reply = redisCommand(p_redis_handler, "HMGET SerPort%dMet%dStatus VALUE",port_idx,midx);
				if(p_redis_reply!=NULL)
				{
					if(p_redis_reply->element[0]->str!=NULL)
					{
						memset(g_temp_str,0,sizeof(g_temp_str));
						if(midx==dlms_dcu_config.dlms_channel_cfg[port_idx].num_meter-1)
							sprintf(g_temp_str,"%c%d%c",DBL_QUOTES,atoi(p_redis_reply->element[0]->str),DBL_QUOTES);
						else
							sprintf(g_temp_str,"%c%d%c,",DBL_QUOTES,atoi(p_redis_reply->element[0]->str),DBL_QUOTES);
						
						strcat(json_text,g_temp_str);
					}
				}
			
			}
			strcat(json_text,"]\n");
			
			if(port_idx==MAX_NO_OF_SERIAL_PORT-1)
				strcat(json_text,"}\n");
			else
				strcat(json_text,"},\n");
		}
	}
	else
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmget ETH_MET_INFO NumMeters");
		if(p_redis_reply!=NULL)
		{
			if(p_redis_reply->element[0]->str!=NULL)
			{
				dlms_dcu_config.eth_meter_cfg.num_meter=atoi(p_redis_reply->element[0]->str);
			}
		}
			
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cNUM_PORTS%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,1,DBL_QUOTES);
		strcat(json_text,g_temp_str);
		
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%c%s%c:\n",DBL_QUOTES,"ETH_PORT",DBL_QUOTES);
		strcat(json_text,g_temp_str);
			
		strcat(json_text,"{\n");
		
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cNUM_METERS%c:%c%d%c,\n",DBL_QUOTES,DBL_QUOTES,DBL_QUOTES,dlms_dcu_config.eth_meter_cfg.num_meter,DBL_QUOTES);
		strcat(json_text,g_temp_str);
		
		memset(g_temp_str,0,sizeof(g_temp_str));
		sprintf(g_temp_str,"%cSTATUS%c:\n",DBL_QUOTES,DBL_QUOTES);
		strcat(json_text,g_temp_str);
			
		strcat(json_text,"[");
		
		for(midx=0; midx<dlms_dcu_config.eth_meter_cfg.num_meter; midx++)
		{
			p_redis_reply = redisCommand(p_redis_handler, "HMGET EthPort%dMet%dStatus VALUE",port_idx,midx);
			if(p_redis_reply!=NULL)
			{
				if(p_redis_reply->element[0]->str!=NULL)
				{
					memset(g_temp_str,0,sizeof(g_temp_str));
					if(midx==dlms_dcu_config.eth_meter_cfg.num_meter-1)
						sprintf(g_temp_str,"%c%d%c",DBL_QUOTES,atoi(p_redis_reply->element[0]->str),DBL_QUOTES);
					else
						sprintf(g_temp_str,"%c%d%c,",DBL_QUOTES,atoi(p_redis_reply->element[0]->str),DBL_QUOTES);
					
					strcat(json_text,g_temp_str);
				}
			}
		}
			
		strcat(json_text,"]\n");
			
		strcat(json_text,"}\n");
	}
	
	strcat(json_text,"}\n"); // End of Data
	
	strcat(json_text,"}\n"); // End of Json

	printf("Sending Json text Len : %d\n",strlen(json_text));
	
	send_msg(json_text);
}

/* End Of File */