#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "gen_inc.h"
#include "dlms_api_config.h"
#include "log.h"
#include "/home/iot-gateway/redis-5.0.8-bin/include/hiredis.h"

int32_t redis_init(char *hostname, uint16_t port);

redisContext 			*p_redis_handler=NULL;
redisReply 				*p_redis_reply=NULL;
char 					debug_file_name[64];
dlms_dcu_config_t 		dlms_dcu_config;

int RET_SUCCESS=0;

/*  Local Micro*/
#define BIN_TO_LOG_FILE_NAME "cms_bin_to_redis.log"

int32_t redis_init(char *hostname, uint16_t port)
{
	static char fun_name[]="redis_init()";
	
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	
	dbg_log(INFORM,"%-20s : Trying to connect on Redis Server : %s with port : %d\n",fun_name,hostname,port);
	
    p_redis_handler = redisConnectWithTimeout(hostname, port, timeout);
    if (p_redis_handler == NULL || p_redis_handler->err) 
	{
        if (p_redis_handler) 
		{
			dbg_log(INFORM,"%-20s : Connection error: %s\n",fun_name,p_redis_handler->errstr);
            
            redisFree(p_redis_handler);
        } 
		else 
		{
			dbg_log(INFORM,"%-20s : Connection error: can't allocate redis context\n",fun_name);
        }
    }
	
	dbg_log(INFORM,"%-20s : Connected on Redis Server : %s with port : %d\n",fun_name,hostname,port);
 
	return RET_SUCCESS;
}

void gen_all_config(void)
{
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s stat %b", "DLMS_DCU_CONFIG", &dlms_dcu_config, sizeof(dlms_dcu_config));
	//printf("Save statuṣs %s\n", p_redis_reply->str);//that shows +OK
	freeReplyObject(p_redis_reply);
}

void gen_vpn_info_redis(void)
{
	p_redis_reply = redisCommand(p_redis_handler,"hmset VPN_INFO VpnEnable %d",dlms_dcu_config.vpn_cfg.enable_vpn);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset PPTPCFG LocUserName %s",dlms_dcu_config.vpn_cfg.pptp_cfg.loc_username);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset PPTPCFG LocPassword %s",dlms_dcu_config.vpn_cfg.pptp_cfg.loc_password);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset PPTPCFG RemUserName %s",dlms_dcu_config.vpn_cfg.pptp_cfg.remote_username);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset PPTPCFG RemPassword %s",dlms_dcu_config.vpn_cfg.pptp_cfg.remote_password);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset PPTPCFG ReqMemoryMap %d",dlms_dcu_config.vpn_cfg.pptp_cfg.req_mmpe128);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG KeyLifeTime %d",dlms_dcu_config.vpn_cfg.ipsec_cfg.key_life_time);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG AggrMode %d",dlms_dcu_config.vpn_cfg.ipsec_cfg.aggr_mode);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG NatTrav %d",dlms_dcu_config.vpn_cfg.ipsec_cfg.nat_trav);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG Pfs %d",dlms_dcu_config.vpn_cfg.ipsec_cfg.pfs);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG TunnelName %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.tunnel_name);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG PreSharedKey %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.pre_shared_key);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG RightIp %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.right_ip);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG RightId %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.right_id);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG RightSubnet %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.right_subnet);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG Left %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.left);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG LeftSubnet %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.left_subnet);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG LeftId %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.left_id);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG LeftSrcIp %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.left_src_ip);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IPSECCFG KeyingMode %s",dlms_dcu_config.vpn_cfg.ipsec_cfg.keying_mode);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Phase1 DhGrp %d",dlms_dcu_config.vpn_cfg.phase_cfg1.dhgrp);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Phase2 DhGrp %d",dlms_dcu_config.vpn_cfg.phase_cfg2.dhgrp);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Phase1 Encrpt %d",dlms_dcu_config.vpn_cfg.phase_cfg1.encrpt);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Phase2 Encrpt %d",dlms_dcu_config.vpn_cfg.phase_cfg2.encrpt);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Phase1 Authen %d",dlms_dcu_config.vpn_cfg.phase_cfg1.authen);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset Phase2 Authen %d",dlms_dcu_config.vpn_cfg.phase_cfg2.authen);
	freeReplyObject(p_redis_reply);
}

void gen_ftp_server_info_redis(void)
{
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO Enable %d",dlms_dcu_config.ftp_ser_cfg.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO DiffLogSer %d",dlms_dcu_config.ftp_ser_cfg.diff_log_ser);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO SerPort %d",dlms_dcu_config.ftp_ser_cfg.ser_port);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO UploadPeriod %d",dlms_dcu_config.ftp_ser_cfg.upload_period);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO LocDir %s",dlms_dcu_config.ftp_ser_cfg.loc_dir);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO Password %s",dlms_dcu_config.ftp_ser_cfg.password);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO UserName %s",dlms_dcu_config.ftp_ser_cfg.username);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO SerIp %s",dlms_dcu_config.ftp_ser_cfg.ser_ip);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO LogSerPort %d",dlms_dcu_config.ftp_ser_cfg.log_ser_port);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO LogUploadPeriod %d",dlms_dcu_config.ftp_ser_cfg.log_upload_period);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO LogLocDir %s",dlms_dcu_config.ftp_ser_cfg.log_loc_dir);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO LogPassword %s",dlms_dcu_config.ftp_ser_cfg.log_password);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO LogUserName %s",dlms_dcu_config.ftp_ser_cfg.log_username);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset FTP_SER_INFO LogSerIp %s",dlms_dcu_config.ftp_ser_cfg.log_ser_ip);
	freeReplyObject(p_redis_reply);
	
	printf("LogSerIp %s\n",dlms_dcu_config.ftp_ser_cfg.log_ser_ip);
}
	
void gen_gprs_info_redis(void)
{
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO GprsEnable %d",dlms_dcu_config.gprs_cfg.enable_gprs);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO PingInterval %d",dlms_dcu_config.gprs_cfg.ping_int);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO NumPing %d",dlms_dcu_config.gprs_cfg.num_pings);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO ConnType %d",dlms_dcu_config.gprs_cfg.conn_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO PingEnable %d",dlms_dcu_config.gprs_cfg.enable_ping);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO Ping1IpAddr %s",dlms_dcu_config.gprs_cfg.ping1_ip_addr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO Ping2IpAddr %s",dlms_dcu_config.gprs_cfg.ping2_ip_addr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO AccPtName %s",dlms_dcu_config.gprs_cfg.access_pt_name);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO PhoneNum %s",dlms_dcu_config.gprs_cfg.phone_num);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO Password %s",dlms_dcu_config.gprs_cfg.password);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset GPRS_INFO UserName %s",dlms_dcu_config.gprs_cfg.username);
	freeReplyObject(p_redis_reply);
}

void gen_dcu_serial_info_redis(void)
{
	uint8_t idx=0;
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_SERIAL_INFO NumDcuSer %d",dlms_dcu_config.ser_prot_cfg.num_ser_port);
	freeReplyObject(p_redis_reply);
	
	for(idx=0;idx<MAX_NO_OF_SERIAL_PORT;idx++)
	{
		printf("Idx : %d, SerPort Uart : %s\n",idx+1,dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].ser_port);
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_SERIAL_INFO DcuSer%dPort %s",
		idx+1,dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].ser_port);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_SERIAL_INFO DcuSer%dBaudrate %d",
		idx+1,dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].baudrate);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_SERIAL_INFO DcuSer%dDataBits %d",
		idx+1,dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].databits);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_SERIAL_INFO DcuSer%dStopBits %d",
		idx+1,dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].stopbits);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_SERIAL_INFO DcuSer%dParity %d",
		idx+1,dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].parity);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_SERIAL_INFO DcuSer%dInfMode %d",
		idx+1,dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].infmode);
		freeReplyObject(p_redis_reply);
	}
}

void gen_dcu_eth_info_redis(void)
{
	uint8_t idx=0;
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_ETH_INFO NumDcuEth %d",dlms_dcu_config.ethernate_cfg.num_dcu_eth_port);
	freeReplyObject(p_redis_reply);
	
	for(idx=0;idx<MAX_NUM_DCU_ETH;idx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_ETH_INFO DcuEth%dIp %s",
		idx+1,dlms_dcu_config.ethernate_cfg.eth_cfg[idx].ip_addr);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_ETH_INFO DcuEth%dGw %s",
		idx+1,dlms_dcu_config.ethernate_cfg.eth_cfg[idx].gateway);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_ETH_INFO DcuEth%dNetMask %s",
		idx+1,dlms_dcu_config.ethernate_cfg.eth_cfg[idx].netmask);
		freeReplyObject(p_redis_reply);
	}
}

void gen_ntp_info_redis(void)
{
	p_redis_reply = redisCommand(p_redis_handler,"hmset NTP_INFO Ntp1Enable %d",dlms_dcu_config.ntp_cfg.enable_ntp1);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset NTP_INFO Ntp2Enable %d",dlms_dcu_config.ntp_cfg.enable_ntp2);
	freeReplyObject(p_redis_reply);
	
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset NTP_INFO Ntp1Port %d",dlms_dcu_config.ntp_cfg.ntp1_port);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset NTP_INFO Ntp2Port %d",dlms_dcu_config.ntp_cfg.ntp2_port);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset NTP_INFO Interval %d",dlms_dcu_config.ntp_cfg.interval);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset NTP_INFO Ntp1IpAddr %s",dlms_dcu_config.ntp_cfg.ntp1_ip_addr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset NTP_INFO Ntp2IpAddr %s",dlms_dcu_config.ntp_cfg.ntp2_ip_addr);
	freeReplyObject(p_redis_reply);
}

void gen_cms_ems_info_redis(void)
{
	p_redis_reply = redisCommand(p_redis_handler,"hmset CMS_EMS_INFO Enable %d",dlms_dcu_config.cms_ems_cfg.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset CMS_EMS_INFO BrokerIp %s",dlms_dcu_config.cms_ems_cfg.broker_ip);
	freeReplyObject(p_redis_reply);

	p_redis_reply = redisCommand(p_redis_handler,"hmset CMS_EMS_INFO EventSendEnable %d",
	dlms_dcu_config.cms_ems_cfg.event_send_enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset CMS_EMS_INFO DiagSendEnable %d",
	dlms_dcu_config.cms_ems_cfg.diag_send_enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset CMS_EMS_INFO PubSec %d",dlms_dcu_config.cms_ems_cfg.pub_int_sec);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset CMS_EMS_INFO PubMint %d",dlms_dcu_config.cms_ems_cfg.pub_int_mint);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset CMS_EMS_INFO PubHr %d",dlms_dcu_config.cms_ems_cfg.pub_int_hour);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset CMS_EMS_INFO BrokerIp %s",dlms_dcu_config.cms_ems_cfg.broker_ip);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset CMS_EMS_INFO BrokerPort %d",dlms_dcu_config.cms_ems_cfg.broker_port);
	
	freeReplyObject(p_redis_reply);
}

void gen_mqtt_info_redis(void)
{
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO Enable %d",dlms_dcu_config.mqtt_cfg.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO BrokerIp %s",dlms_dcu_config.mqtt_cfg.broker_ip);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO SubTopic %s",dlms_dcu_config.mqtt_cfg.sub_topic);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO PubTopic %s",dlms_dcu_config.mqtt_cfg.pub_topic);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO BrokerPass %s",dlms_dcu_config.mqtt_cfg.password);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO BrokerUname %s",dlms_dcu_config.mqtt_cfg.username);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO BrokerPort %d",dlms_dcu_config.mqtt_cfg.broker_port);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO PubSec %d",dlms_dcu_config.mqtt_cfg.pub_int_sec);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO PubMint %d",dlms_dcu_config.mqtt_cfg.pub_int_mint);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO PubHr %d",dlms_dcu_config.mqtt_cfg.pub_int_hour);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO DiagPubTopic %s",dlms_dcu_config.mqtt_cfg.diag_pub_topic);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO DiagTopicEnable %d",dlms_dcu_config.mqtt_cfg.diag_topic_enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO CmdSubTopic %s",dlms_dcu_config.mqtt_cfg.cmd_sub_topic);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO PerDataTopic %s",dlms_dcu_config.mqtt_cfg.periodic_data_topic);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO EventPubTopic %s",dlms_dcu_config.mqtt_cfg.event_pub_topic);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MQTT_INFO EventTopicEnable %d",dlms_dcu_config.mqtt_cfg.event_topic_enable);
	freeReplyObject(p_redis_reply);
}

void gen_dcu_poll_info_redis(void)
{
	p_redis_reply = redisCommand(p_redis_handler,"hmset INST_POLL_INFO Enable %d",
	dlms_dcu_config.dcu_poll_info.inst_poll_info.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset INST_POLL_INFO PollType %d",
	dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset INST_POLL_INFO Periodicity %d",
	dlms_dcu_config.dcu_poll_info.inst_poll_info.periodicity);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset INST_POLL_INFO PollSec %d",
	dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_sec);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset INST_POLL_INFO PollMint %d",
	dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_mint);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset INST_POLL_INFO PollHr %d",
	dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_hr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DP_POLL_INFO Enable %d",
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DP_POLL_INFO PollType %d",
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DP_POLL_INFO Periodicity %d",
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.periodicity);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DP_POLL_INFO PollSec %d",
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_sec);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DP_POLL_INFO PollMint %d",
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_mint);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DP_POLL_INFO PollHr %d",
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_hr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset BILL_POLL_INFO Enable %d",
	dlms_dcu_config.dcu_poll_info.bill_poll_info.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset BILL_POLL_INFO PollType %d",
	dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset BILL_POLL_INFO Periodicity %d",
	dlms_dcu_config.dcu_poll_info.bill_poll_info.periodicity);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset BILL_POLL_INFO PollSec %d",
	dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_sec);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset BILL_POLL_INFO PollMint %d",
	dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_mint);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset BILL_POLL_INFO PollHr %d",
	dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_hr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset EVENT_POLL_INFO Enable %d",
	dlms_dcu_config.dcu_poll_info.event_poll_info.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset EVENT_POLL_INFO PollType %d",
	dlms_dcu_config.dcu_poll_info.event_poll_info.poll_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset EVENT_POLL_INFO Periodicity %d",
	dlms_dcu_config.dcu_poll_info.event_poll_info.periodicity);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset EVENT_POLL_INFO PollSec %d",
	dlms_dcu_config.dcu_poll_info.event_poll_info.poll_sec);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset EVENT_POLL_INFO PollMint %d",
	dlms_dcu_config.dcu_poll_info.event_poll_info.poll_mint);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset EVENT_POLL_INFO PollHr %d",
	dlms_dcu_config.dcu_poll_info.event_poll_info.poll_hr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset LS_POLL_INFO Enable %d",
	dlms_dcu_config.dcu_poll_info.ls_poll_info.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset LS_POLL_INFO PollType %d",
	dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset LS_POLL_INFO Periodicity %d",
	dlms_dcu_config.dcu_poll_info.ls_poll_info.periodicity);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset LS_POLL_INFO PollSec %d",
	dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_sec);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset LS_POLL_INFO PollMint %d",
	dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_mint);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset LS_POLL_INFO PollHr %d",
	dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_hr);
	freeReplyObject(p_redis_reply);
}

void gen_modtcp_info_redis(void)
{
	p_redis_reply = redisCommand(p_redis_handler,"hmset MODTCP_INFO Enable %d",dlms_dcu_config.modtcp_slave_cfg.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MODTCP_INFO RespAllId %d",dlms_dcu_config.modtcp_slave_cfg.resp_all_id);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MODTCP_INFO SlaveId %d",dlms_dcu_config.modtcp_slave_cfg.slave_id);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MODTCP_INFO HoldRegStAddr %d",
	dlms_dcu_config.modtcp_slave_cfg.hold_reg_start_addr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MODTCP_INFO InputRegStAddr %d",
	dlms_dcu_config.modtcp_slave_cfg.input_reg_start_addr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MODTCP_INFO ReadCoilStAddr %d",
	dlms_dcu_config.modtcp_slave_cfg.read_coil_start_addr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MODTCP_INFO Port %d",
	dlms_dcu_config.modtcp_slave_cfg.port);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset MODTCP_INFO ReadDiscStAddr %d",
	dlms_dcu_config.modtcp_slave_cfg.read_disc_start_addr);
	freeReplyObject(p_redis_reply);
}

void gen_iec104_info_redis(void)
{
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO Enable %d",dlms_dcu_config.iec104_slave_cfg.enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO AsduAddr %d",dlms_dcu_config.iec104_slave_cfg.asdu_addr);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO Time1 %d",dlms_dcu_config.iec104_slave_cfg.iec_t1);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO Time2 %d",dlms_dcu_config.iec104_slave_cfg.iec_t2);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO Time3 %d",dlms_dcu_config.iec104_slave_cfg.iec_t3);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO SentAck %d",dlms_dcu_config.iec104_slave_cfg.iec_k);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO RecvAck %d",dlms_dcu_config.iec104_slave_cfg.iec_w);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO CotSize %d",dlms_dcu_config.iec104_slave_cfg.cot_size);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO IoaSize %d",dlms_dcu_config.iec104_slave_cfg.ioa_size);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO CycInterval %d",dlms_dcu_config.iec104_slave_cfg.cyclic_int);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO IecPort %d",dlms_dcu_config.iec104_slave_cfg.iec_port);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO StDataIoa %d",dlms_dcu_config.iec104_slave_cfg.start_data_ioa);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset IEC104_INFO StDevStatusIoa %d",dlms_dcu_config.iec104_slave_cfg.start_dev_status_ioa);
	freeReplyObject(p_redis_reply);
}

void gen_eth_meter_info_redis(void)
{
	uint8_t idx=0;
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset ETH_MET_INFO NumMeters %d",dlms_dcu_config.eth_meter_cfg.num_meter);
	freeReplyObject(p_redis_reply);
	
	for(idx=0;idx<MAX_NO_OF_ETH_METER;idx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmset EthMeter_%dConfig Enable %d",
		idx+1,dlms_dcu_config.eth_meter_cfg.eth_param[idx].enable);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset EthMeter_%dConfig MeterId %d",
		idx+1,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_id);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset EthMeter_%dConfig MeterAddrSize %d",
		idx+1,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_addr_size);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset EthMeter_%dConfig MeterAddr %d",
		idx+1,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_addr);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset EthMeter_%dConfig MeterPass %s",
		idx+1,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_pass);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset EthMeter_%dConfig MeterIp %s",
		idx+1,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_ipaddr);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset EthMeter_%dConfig MeterLoc %s",
		idx+1,dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_loc);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset EthMeter_%dConfig Port %d",
		idx+1,dlms_dcu_config.eth_meter_cfg.eth_param[idx].port);
		freeReplyObject(p_redis_reply);
	}
}

void gen_ser_meter_info_redis(void)
{
	uint8_t idx=0,port_idx=0;
	
	for (port_idx=0; port_idx<MAX_NO_OF_SERIAL_PORT; port_idx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmset P_%dSER_MET_INFO NumMeters %d",
		port_idx,dlms_dcu_config.dlms_channel_cfg[port_idx].num_meter);
		freeReplyObject(p_redis_reply);
		
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
			
			p_redis_reply = redisCommand(p_redis_handler,"hmset P_%dSerMeter_%dConfig Enable %d",port_idx,
			idx+1,dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].enable);
			freeReplyObject(p_redis_reply);
			
			p_redis_reply = redisCommand(p_redis_handler,"hmset P_%dSerMeter_%dConfig MeterId %d",port_idx,
			idx+1,dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_id);
			freeReplyObject(p_redis_reply);
			
			p_redis_reply = redisCommand(p_redis_handler,"hmset P_%dSerMeter_%dConfig MeterAddrSize %d",port_idx,
			idx+1,dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_addr_size);
			freeReplyObject(p_redis_reply);
			
			p_redis_reply = redisCommand(p_redis_handler,"hmset P_%dSerMeter_%dConfig MeterAddr %d",port_idx,
			idx+1,dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_addr);
			freeReplyObject(p_redis_reply);
			
			p_redis_reply = redisCommand(p_redis_handler,"hmset P_%dSerMeter_%dConfig MeterPass %s",port_idx,
			idx+1,dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_pass);
			freeReplyObject(p_redis_reply);
			
			p_redis_reply = redisCommand(p_redis_handler,"hmset P_%dSerMeter_%dConfig MeterLoc %s",port_idx,
			idx+1,dlms_dcu_config.dlms_channel_cfg[port_idx].met_cfg[idx].meter_loc);
			freeReplyObject(p_redis_reply);
		}
	}
}

void gen_dcu_info_redis(void)
{
	uint8_t idx=0;
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO DcuDevId %d",dlms_dcu_config.dlms_dcu_info.dcu_dev_id);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO ReadPrevLsData %d",dlms_dcu_config.dlms_dcu_info.read_prev_ls_data);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO FaultTolSupp %d",dlms_dcu_config.dlms_dcu_info.fault_to_1_supp);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO NumEthPort %d",dlms_dcu_config.dlms_dcu_info.num_eth_port);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO MeterType %d",dlms_dcu_config.dlms_dcu_info.meter_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO DataFormatType %d",dlms_dcu_config.dlms_dcu_info.data_format_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO DataTrfType %d",dlms_dcu_config.dlms_dcu_info.data_trf_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO MasterProtoType %d",dlms_dcu_config.dlms_dcu_info.master_proto_type);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO DbgLogEnable %d",dlms_dcu_config.dlms_dcu_info.dbglog_enable);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO DcuDevLoc %s",dlms_dcu_config.dlms_dcu_info.dcu_location);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO DcuGpsLoc %s",dlms_dcu_config.dlms_dcu_info.dcu_gps_loc);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO DbgLogIp %s",dlms_dcu_config.dlms_dcu_info.dbglog_ip);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO DbgLogLevel %d",dlms_dcu_config.dlms_dcu_info.dbglog_label);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO SerNum %s",dlms_dcu_config.dlms_dcu_info.ser_num);
	freeReplyObject(p_redis_reply);
	
	p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO EnableAllowedMaster %d",dlms_dcu_config.dlms_dcu_info.enable_allow_master);
	freeReplyObject(p_redis_reply);
	
	for(idx=0; idx<MAX_NUM_MASTER;idx++)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO MasterIp_%dEnable %d",
		idx+1,dlms_dcu_config.dlms_dcu_info.enable_allow_master_ip[idx]);
		freeReplyObject(p_redis_reply);
		
		p_redis_reply = redisCommand(p_redis_handler,"hmset DCU_GEN_INFO Master_%dIp %s",idx+1,dlms_dcu_config.dlms_dcu_info.allow_master_ip[idx]);
		freeReplyObject(p_redis_reply);
		
		//printf("%s\n",dlms_dcu_config.dlms_dcu_info.allow_master_ip[idx]);
	}
}

/*********************************************************************
*Function 		: modbus_crc16()
*In Params 		: buffer and length.
*Output 		: None
*Return			: calculated crc of received buffer.
*Description 	: To calculate crc for given buffer.
**********************************************************************/

uint16_t modbus_crc16(char *data,int32_t cnt)
{
	uint32_t	i=0,j=0;
    uint16_t	temp=0,temp2=0,flag=0;

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
	
	printf("Calculated CRC : %X\n",temp);
	
	return(temp);
}

int32_t read_bin_cfg(char *cfg_file_name)
{
	FILE *p_file_ptr=NULL;
	
	printf("Sizeof cfg str : %d\n",sizeof(dlms_dcu_config));
	p_file_ptr=fopen(cfg_file_name,"r");
	
	if(p_file_ptr==NULL)
	{
		perror("fopen ");
		return -1;
	}
	
	memset(&dlms_dcu_config,0,sizeof(dlms_dcu_config));
	
	fread(&dlms_dcu_config,sizeof(dlms_dcu_config),1,p_file_ptr);
	
	fclose(p_file_ptr);
	
	if(dlms_dcu_config.start_flag==START_END_FLAG)
	{
		if(dlms_dcu_config.end_flag==START_END_FLAG)
		{
			if(dlms_dcu_config.crc==modbus_crc16((char*)&dlms_dcu_config,sizeof(dlms_dcu_config)-6))
			{
				printf("Start & End Flag and CRC Matched\n");
			}
			else
			{
				printf("Crc Not Matched\n");
				return -1;
			}
		}
		else
		{
			printf("End Flag Not Matched\n");
			return -1;
		}
	}
	else
	{
		printf("Start Flag Not Matched\n");
		return -1;
	}
	
	return 0;
}

int main(int argc, char **argv)
{	
	static char fun_name[]="main()";
	
	memset(debug_file_name,0,sizeof(debug_file_name));
	sprintf(debug_file_name,"%s/%s",LOG_DIR,BIN_TO_LOG_FILE_NAME);
	
	if(redis_init("127.0.0.1",6379)!=RET_SUCCESS)
	{
		dbg_log(INFORM,"%-20s : Failed to initilised Redis Server\n",fun_name);
		return -1;
	}
	
	if(read_bin_cfg("/usr/cms/config/dlms_api_config.cfg")!=RET_SUCCESS)
	{
		dbg_log(INFORM,"%-20s : Failed to read binary configuration\n",fun_name);
		return -1;
	}
	
	dbg_log(INFORM,"%-20s : Generating gen_dcu_info_redis from bin to redis\n",fun_name);
	gen_dcu_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_ser_meter_info_redis from bin to redis\n",fun_name);
	gen_ser_meter_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_eth_meter_info_redis from bin to redis\n",fun_name);
	gen_eth_meter_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_iec104_info_redis from bin to redis\n",fun_name);
	gen_iec104_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_modtcp_info_redis from bin to redis\n",fun_name);
	gen_modtcp_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_dcu_poll_info_redis from bin to redis\n",fun_name);
	gen_dcu_poll_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_mqtt_info_redis from bin to redis\n",fun_name);
	gen_mqtt_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_cms_ems_info_redis from bin to redis\n",fun_name);
	gen_cms_ems_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_ntp_info_redis from bin to redis\n",fun_name);
	gen_ntp_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_dcu_eth_info_redis from bin to redis\n",fun_name);
	gen_dcu_eth_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_dcu_serial_info_redis from bin to redis\n",fun_name);
	gen_dcu_serial_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_gprs_info_redis from bin to redis\n",fun_name);
	gen_gprs_info_redis();
	
	dbg_log(INFORM,"%-20s : Generating gen_ftp_server_info_redis from bin to redis\n",fun_name);
	gen_ftp_server_info_redis(); 
	
	dbg_log(INFORM,"%-20s : Generating gen_vpn_info_redis from bin to redis\n",fun_name);
	gen_vpn_info_redis();
	
	dbg_log(INFORM,"%-20s : All Config generated, need to free redis hanfler\n",fun_name);
	
	redisFree(p_redis_handler);
	
	return RET_SUCCESS;
}

/* End Of File */