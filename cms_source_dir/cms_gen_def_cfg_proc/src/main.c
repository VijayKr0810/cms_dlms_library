#include "gen_inc.h"
#include "dlms_api_config.h"

void generate_cfg_json(void);
void store_cfg_json(void);

dlms_dcu_config_t dlms_dcu_config;

char 	json_text[1024];
char 	temp_text[256];

//VPN Related
//Group 1 - 768 bit / Group 2 - 1024 bit / Group 5 - 1536 bit
#define	G1_768_BIT		0x01
#define	G2_1024_BIT		0x02
#define	G5_1536_BIT		0x03
//DES / 3DES / AES-128 / AES-192 / AES-256
#define	ENC_DES			0x04
#define	ENC_3DES		0x05
#define	ENC_AES_128		0x06
#define	ENC_AES_192		0x07
#define	ENC_AES_256		0x08
//MD5 / SHA1
#define	AUT_MD5			0x09
#define	AUT_SHA1		0x0A


//gprs connection
#define	LAN_TYPE				0x01
#define	THREEG_TYPE				0x02
#define	CDMA_TYPE				0x03
#define	TWOG_TYPE				0x04
#define	FOURG_TYPE				0x05

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
    uint16_t	temp=0,temp2=0,flag;

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

void fill_default_cfg(void)
{
	uint8_t idx=0;
	char loc_buff[16];
	
	dlms_dcu_config.start_flag=START_END_FLAG;
	dlms_dcu_config.dlms_dcu_info.num_ser_port=MAX_NO_OF_SERIAL_PORT;
	dlms_dcu_config.dlms_dcu_info.num_eth_port=MAX_NUM_DCU_ETH;
	dlms_dcu_config.dlms_dcu_info.meter_type=1;
	dlms_dcu_config.dlms_dcu_info.read_prev_ls_data=1;
	dlms_dcu_config.dlms_dcu_info.fault_to_1_supp=1;
	dlms_dcu_config.dlms_dcu_info.data_format_type=1;
	dlms_dcu_config.dlms_dcu_info.data_trf_type=1;
	dlms_dcu_config.dlms_dcu_info.master_proto_type=1;
	dlms_dcu_config.dlms_dcu_info.dcu_dev_id=1;
	dlms_dcu_config.dlms_dcu_info.dbglog_enable=1;
	dlms_dcu_config.dlms_dcu_info.dbglog_label=1;
	dlms_dcu_config.dlms_dcu_info.enable_allow_master=1;
	
	for(idx=0; idx<MAX_NUM_MASTER;idx++)
	{
		memset(loc_buff,0,sizeof(loc_buff));
		sprintf(loc_buff,"192.168.10.%d",108+idx);
		
		dlms_dcu_config.dlms_dcu_info.enable_allow_master_ip[idx]=1;
		strcpy(dlms_dcu_config.dlms_dcu_info.allow_master_ip[idx],loc_buff);
	}
	
	strcpy(dlms_dcu_config.dlms_dcu_info.dcu_location,"Bangalore");
	strcpy(dlms_dcu_config.dlms_dcu_info.dcu_gps_loc,"Bangalore");
	strcpy(dlms_dcu_config.dlms_dcu_info.dbglog_ip,"192.168.10.193");
	strcpy(dlms_dcu_config.dlms_dcu_info.ser_num,"DCU_0001");
	
	dlms_dcu_config.ser_prot_cfg.num_ser_port=MAX_NO_OF_SERIAL_PORT;
	for(idx=0;idx<MAX_NO_OF_SERIAL_PORT;idx++)
	{
		memset(loc_buff,0,sizeof(loc_buff));
		switch(idx)
		{
			case 0 : 
				strcpy(loc_buff, COMM_PORT0_DET);
			break;
				
			case 1 : 
				strcpy(loc_buff, COMM_PORT1_DET);
			break;
				
			case 2 : 
				strcpy(loc_buff, COMM_PORT2_DET);
			break;
				
			case 3 : 
				strcpy(loc_buff, COMM_PORT3_DET);
			break;
			
			case 4 : 
				strcpy(loc_buff, COMM_PORT4_DET);
			break;
				
			case 5 : 
				strcpy(loc_buff, COMM_PORT5_DET);
			break;
				
			default : break;
		}

		strcpy(dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].ser_port,loc_buff);
		dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].baudrate=10;
		dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].databits=8;
		dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].stopbits=1;
		dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].parity=0;
		dlms_dcu_config.ser_prot_cfg.ser_prot_param[idx].infmode=RS485_MODE;
	}
	
	uint8_t pidx=0;
	for(pidx=0; pidx<MAX_NO_OF_SERIAL_PORT; pidx++)
	{
		dlms_dcu_config.dlms_channel_cfg[pidx].num_meter=MAX_NO_OF_METER_PER_PORT;
		for(idx=0;idx<MAX_NO_OF_METER_PER_PORT;idx++)
		{	
			dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].enable=1;
			dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].meter_id=idx+1;
			dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].meter_addr_size=4;
			dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].meter_addr=22+idx;
			strcpy(dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].meter_pass,"lnt1");
			memset(loc_buff,0,sizeof(loc_buff));
			sprintf(loc_buff,"DCU_MET_LOC_%d",pidx*MAX_NO_OF_SERIAL_PORT+idx+1);
			strcpy(dlms_dcu_config.dlms_channel_cfg[pidx].met_cfg[idx].meter_loc,loc_buff);
		}
	}

	dlms_dcu_config.eth_meter_cfg.num_meter=MAX_NO_OF_ETH_METER;
	for(idx=0;idx<MAX_NO_OF_ETH_METER;idx++)
	{
		dlms_dcu_config.eth_meter_cfg.eth_param[idx].enable=1;
		dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_id=idx+1;
		dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_addr_size=4;
		dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_addr=22+idx;
		strcpy(dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_pass,"lnt1");
		memset(loc_buff,0,sizeof(loc_buff));
		sprintf(loc_buff,"DCU_MET_LOC_%d",idx);
		strcpy(dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_loc,loc_buff);
		
		memset(loc_buff,0,sizeof(loc_buff));
		sprintf(loc_buff,"254.254.256.254");
		strcpy(dlms_dcu_config.eth_meter_cfg.eth_param[idx].meter_ipaddr,loc_buff);
	}

	dlms_dcu_config.ethernate_cfg.num_dcu_eth_port=MAX_NUM_DCU_ETH;
	for(idx=0;idx<MAX_NUM_DCU_ETH;idx++)
	{
		sprintf(dlms_dcu_config.ethernate_cfg.eth_cfg[idx].ip_addr,"192.168.%d.55",10+idx);
		strcpy(dlms_dcu_config.ethernate_cfg.eth_cfg[idx].netmask,"255.255.255.0");
		sprintf(dlms_dcu_config.ethernate_cfg.eth_cfg[idx].gateway,"192.168.%d.201",10+idx);
	}

	dlms_dcu_config.dcu_poll_info.bill_poll_info.enable=1;
	dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_type=1;
	dlms_dcu_config.dcu_poll_info.bill_poll_info.periodicity=10;
	dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_sec=10;
	dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_mint=0;
	dlms_dcu_config.dcu_poll_info.bill_poll_info.poll_hr=2;
	
	dlms_dcu_config.dcu_poll_info.ls_poll_info.enable=1;
	dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_type=1;
	dlms_dcu_config.dcu_poll_info.ls_poll_info.periodicity=10;
	dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_sec=10;
	dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_mint=0;
	dlms_dcu_config.dcu_poll_info.ls_poll_info.poll_hr=0;
	
	dlms_dcu_config.dcu_poll_info.event_poll_info.enable=1;
	dlms_dcu_config.dcu_poll_info.event_poll_info.poll_type=1;
	dlms_dcu_config.dcu_poll_info.event_poll_info.periodicity=10;
	dlms_dcu_config.dcu_poll_info.event_poll_info.poll_sec=10;
	dlms_dcu_config.dcu_poll_info.event_poll_info.poll_mint=0;
	dlms_dcu_config.dcu_poll_info.event_poll_info.poll_hr=0;
	
	dlms_dcu_config.dcu_poll_info.inst_poll_info.enable=1;
	dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_type=1;
	dlms_dcu_config.dcu_poll_info.inst_poll_info.periodicity=10;
	dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_sec=10;
	dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_mint=0;
	dlms_dcu_config.dcu_poll_info.inst_poll_info.poll_hr=0;
	
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.enable=1;
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_type=1;
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.periodicity=10;
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_sec=10;
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_mint=0;
	dlms_dcu_config.dcu_poll_info.daily_prof_poll_info.poll_hr=1;
	
	strcpy(dlms_dcu_config.mqtt_cfg.broker_ip,"192.168.10.108");
	strcpy(dlms_dcu_config.mqtt_cfg.username,"user");
	strcpy(dlms_dcu_config.mqtt_cfg.password,"softel");
	strcpy(dlms_dcu_config.mqtt_cfg.pub_topic,"/cms/blr");
	strcpy(dlms_dcu_config.mqtt_cfg.sub_topic,"/cms/blr");
	strcpy(dlms_dcu_config.mqtt_cfg.event_pub_topic,"/cms/bangalore/event");
	strcpy(dlms_dcu_config.mqtt_cfg.diag_pub_topic,"/cms/bangalore/diag");
	
	dlms_dcu_config.mqtt_cfg.event_topic_enable=0;
	dlms_dcu_config.mqtt_cfg.enable=0;
	dlms_dcu_config.mqtt_cfg.diag_topic_enable=0;
	dlms_dcu_config.mqtt_cfg.pub_int_hour=0;
	dlms_dcu_config.mqtt_cfg.pub_int_mint=5;
	dlms_dcu_config.mqtt_cfg.pub_int_sec=0;
	dlms_dcu_config.mqtt_cfg.broker_port=1883;
	
	strcpy(dlms_dcu_config.cms_ems_cfg.broker_ip,"15.206.196.77");
	dlms_dcu_config.cms_ems_cfg.enable=0;
	dlms_dcu_config.cms_ems_cfg.pub_int_hour=0;
	dlms_dcu_config.cms_ems_cfg.pub_int_mint=5;
	dlms_dcu_config.cms_ems_cfg.pub_int_sec=0;
	dlms_dcu_config.cms_ems_cfg.broker_port=8010;

	strcpy(dlms_dcu_config.ntp_cfg.ntp1_ip_addr,"192.168.10.92");
	strcpy(dlms_dcu_config.ntp_cfg.ntp2_ip_addr,"192.168.10.75");
	dlms_dcu_config.ntp_cfg.enable_ntp1=1;
	dlms_dcu_config.ntp_cfg.enable_ntp2=1;
	dlms_dcu_config.ntp_cfg.ntp1_port=123;
	dlms_dcu_config.ntp_cfg.ntp2_port=123;
	dlms_dcu_config.ntp_cfg.interval=30; //in sec
	dlms_dcu_config.ntp_cfg.time_offset_hr=5; 
	dlms_dcu_config.ntp_cfg.time_offset_mint=30; 
	
	dlms_dcu_config.gprs_cfg.enable_gprs=0; 
	strcpy(dlms_dcu_config.gprs_cfg.username,"internet"); 
	strcpy(dlms_dcu_config.gprs_cfg.password,"internet"); 
	strcpy(dlms_dcu_config.gprs_cfg.phone_num,"*99***1#"); 
	strcpy(dlms_dcu_config.gprs_cfg.access_pt_name,"airtelgprs.com"); 
	strcpy(dlms_dcu_config.gprs_cfg.ping1_ip_addr,"192.168.10.108"); 
	strcpy(dlms_dcu_config.gprs_cfg.ping2_ip_addr,"192.168.10.201"); 
	dlms_dcu_config.gprs_cfg.conn_type=THREEG_TYPE; 
	dlms_dcu_config.gprs_cfg.enable_ping=1; 
	dlms_dcu_config.gprs_cfg.num_pings=10; 
	dlms_dcu_config.gprs_cfg.ping_int=5; 

	dlms_dcu_config.vpn_cfg.enable_vpn = 0 ; //0;//VPN_PPTP ; //VPN_IPSEC ;
	dlms_dcu_config.vpn_cfg.ipsec_cfg.key_life_time=2;
	dlms_dcu_config.vpn_cfg.ipsec_cfg.aggr_mode=0;
	dlms_dcu_config.vpn_cfg.ipsec_cfg.nat_trav=0;
	dlms_dcu_config.vpn_cfg.ipsec_cfg.pfs=1;
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.tunnel_name,"RTU100021");
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.pre_shared_key,"softel123");
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.right_ip,"122.166.196.34");
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.right_subnet,"192.168.101.0");
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.right_id,"mguard@cmsgp.com");
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.left,"122.166.196.34");
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.left_subnet,"192.168.0.1");
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.left_id,"RTU100021@cmsgp.com");
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.left_src_ip,"122.166.196.34");
	strcpy(dlms_dcu_config.vpn_cfg.ipsec_cfg.keying_mode,"ikev1");
	
	dlms_dcu_config.vpn_cfg.phase_cfg1.dhgrp = G2_1024_BIT;
	dlms_dcu_config.vpn_cfg.phase_cfg1.encrpt = ENC_3DES;
	dlms_dcu_config.vpn_cfg.phase_cfg1.authen = AUT_SHA1;

	dlms_dcu_config.vpn_cfg.phase_cfg2.dhgrp = G2_1024_BIT;
	dlms_dcu_config.vpn_cfg.phase_cfg2.encrpt = ENC_3DES;
	dlms_dcu_config.vpn_cfg.phase_cfg2.authen = AUT_SHA1 ;
	
	dlms_dcu_config.vpn_cfg.pptp_cfg.req_mmpe128 = 1 ;
	strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.conn_name,"pptn");
	strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.loc_username,"vpnuser");
	strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.loc_password,"abc123");
	strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.remote_username,"pptpd");
	strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.remote_password,"pptpd");
	//strcpy(dlms_dcu_config.vpn_cfg.pptp_cfg.rem_ip,"122.166.196.34");
	
	dlms_dcu_config.ftp_ser_cfg.enable=1;
	strcpy(dlms_dcu_config.ftp_ser_cfg.ser_ip,"192.168.101.193");
	strcpy(dlms_dcu_config.ftp_ser_cfg.username,"vijay");
	strcpy(dlms_dcu_config.ftp_ser_cfg.password,"radhey$123");
	strcpy(dlms_dcu_config.ftp_ser_cfg.loc_dir,"dlms_api_dir");
	dlms_dcu_config.ftp_ser_cfg.ser_port=21;
	dlms_dcu_config.ftp_ser_cfg.upload_period=15;
	dlms_dcu_config.ftp_ser_cfg.diff_log_ser=0;
	strcpy(dlms_dcu_config.ftp_ser_cfg.log_ser_ip,"192.168.101.193");
	strcpy(dlms_dcu_config.ftp_ser_cfg.log_username,"vijay");
	strcpy(dlms_dcu_config.ftp_ser_cfg.log_password,"radhey$123");
	strcpy(dlms_dcu_config.ftp_ser_cfg.log_loc_dir,"dlms_api_log_dir");
	dlms_dcu_config.ftp_ser_cfg.log_ser_port=21;
	dlms_dcu_config.ftp_ser_cfg.log_upload_period=15;
	
	dlms_dcu_config.modtcp_slave_cfg.enable=0;
	dlms_dcu_config.modtcp_slave_cfg.port=502;
	dlms_dcu_config.modtcp_slave_cfg.resp_all_id=1;
	dlms_dcu_config.modtcp_slave_cfg.slave_id=1;
	dlms_dcu_config.modtcp_slave_cfg.hold_reg_start_addr=3000;
	dlms_dcu_config.modtcp_slave_cfg.input_reg_start_addr=4000;
	dlms_dcu_config.modtcp_slave_cfg.read_coil_start_addr=1000;
	dlms_dcu_config.modtcp_slave_cfg.read_disc_start_addr=2000;
	
	dlms_dcu_config.iec104_slave_cfg.enable=0;
	dlms_dcu_config.iec104_slave_cfg.asdu_addr=3;
	dlms_dcu_config.iec104_slave_cfg.iec_t1=20;
	dlms_dcu_config.iec104_slave_cfg.iec_t2=15;
	dlms_dcu_config.iec104_slave_cfg.iec_t3=10;
	dlms_dcu_config.iec104_slave_cfg.iec_k=1;
	dlms_dcu_config.iec104_slave_cfg.iec_w=1;
	dlms_dcu_config.iec104_slave_cfg.cot_size=2;
	dlms_dcu_config.iec104_slave_cfg.ioa_size=3;
	dlms_dcu_config.iec104_slave_cfg.cyclic_int=30;
	dlms_dcu_config.iec104_slave_cfg.iec_port=2404;
	dlms_dcu_config.iec104_slave_cfg.start_data_ioa=1000;
	dlms_dcu_config.iec104_slave_cfg.start_dev_status_ioa=5000;
	
	dlms_dcu_config.crc=modbus_crc16((char*)&dlms_dcu_config,sizeof(dlms_dcu_config)-6);
	
	dlms_dcu_config.end_flag=START_END_FLAG;
}

void create_cfg_file(void)
{
	FILE *p_file_ptr=NULL;
	
	p_file_ptr=fopen("dlms_api_config.cfg","w");
	
	if(p_file_ptr==NULL)
	{
		//perror("fopen ");
		return ;
	}
	
	fwrite(&dlms_dcu_config,sizeof(dlms_dcu_config),1,p_file_ptr);
	//perror("fwrite ");
	
	fclose(p_file_ptr);
}

void create_version_file(void)
{
	char version_buff[128];
	char temp_buff[4];
	char time_buff[64];
	
	memset(version_buff,0,sizeof(version_buff));
	memset(time_buff,0,sizeof(time_buff));
	
	strcpy(version_buff,DCU_VERSION_PREFIX);
	
	memset(temp_buff,0,sizeof(temp_buff));
	sprintf(temp_buff,"%d",MAX_NO_OF_SERIAL_PORT);
	strcat(version_buff,temp_buff);
	
	memset(temp_buff,0,sizeof(temp_buff));
	sprintf(temp_buff,"%d",MAX_NUM_DCU_ETH);
	strcat(version_buff,temp_buff);
	
	strcat(version_buff,"X");

	//strcat(version_buff,"-");
	
	strcat(version_buff," ");
	
	strcat(version_buff,DCU_VERNUM);
	
	time_t 			currtime=time(NULL);
	struct tm 		*p_time_ptr=NULL;
	
	p_time_ptr = localtime(&currtime);
	strftime(time_buff, 64, " %d%b%Y", p_time_ptr);
	
	strcat(version_buff,time_buff);
	
	FILE *p_file_ptr=NULL;
	p_file_ptr = fopen("../cms_common_inc/version.h","w");
	if ( p_file_ptr == NULL )
		return;
	
	fprintf(p_file_ptr,"#define	VERSION_NUMBER ");
	fprintf(p_file_ptr,"%c",'"');
	fprintf(p_file_ptr,"%s",version_buff);
	fprintf(p_file_ptr,"%c",'"');
	fclose(p_file_ptr);
	
	p_file_ptr = fopen("version.txt","w");
	if ( p_file_ptr == NULL )
		return;
	
	fprintf(p_file_ptr,"%s",version_buff);
	fflush(p_file_ptr);
	
	fclose(p_file_ptr);
	
	printf("version_buff : %s\n",version_buff);
}

void create_feature_json(void)
{
	char dbl_qts='"';
	FILE *p_file_ptr=NULL;
	
	char dcu_ser_num[32];
	char dcu_fw_ver[32];
	char dcu_model_num[32];
	char version_buff[32];
	
	memset(version_buff,0,sizeof(version_buff));
	memset(dcu_ser_num,0,sizeof(dcu_ser_num));
	memset(dcu_fw_ver,0,sizeof(dcu_fw_ver));
	memset(dcu_model_num,0,sizeof(dcu_model_num));
	
	memset(json_text,0,sizeof(json_text));
	memset(temp_text,0,sizeof(temp_text));
	
	sprintf(dcu_ser_num,"%s",dlms_dcu_config.dlms_dcu_info.ser_num);
	
	p_file_ptr = fopen("version.txt","r");
	if ( p_file_ptr == NULL )
		return;
	
	fscanf(p_file_ptr,"%31s",version_buff);
	strcpy(dcu_model_num,version_buff);
	memset(version_buff,0,sizeof(version_buff));
	
	fscanf(p_file_ptr,"%31s",version_buff);
	strcat(dcu_fw_ver,version_buff);
	strcat(dcu_fw_ver,"_");
	
	fscanf(p_file_ptr,"%31s",version_buff);
	strcat(dcu_fw_ver,version_buff);
	
	//fgets(version_buff,128,p_file_ptr);
	
	fclose(p_file_ptr);
	
	//CS-MDAS-DCU-42X T_V1.00 18Sep2020
	//#define	VERSION_NUMBER "CS-MDAS-DCU-42X T_V1.00 18Sep2020"
	
	/*  "SER_NUM" : "DCU-DEFAULT-SERNO111",
    "MODEL_NO" : "CS-MDAS-DCU-160X-1001",
    "FW_VER" : "V3.0 27July2020", */
	
	
	strcat(json_text,"{\n");
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cEthernet%c:%c%d%c,\n",dbl_qts,dbl_qts,dbl_qts,MAX_NUM_DCU_ETH,dbl_qts);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cSER_NUM%c:%c%s%c,\n",dbl_qts,dbl_qts,dbl_qts,dcu_ser_num,dbl_qts);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cFW_VER%c:%c%s%c,\n",dbl_qts,dbl_qts,dbl_qts,dcu_fw_ver,dbl_qts);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cMODEL_NO%c:%c%s%c,\n",dbl_qts,dbl_qts,dbl_qts,dcu_model_num,dbl_qts);
	strcat(json_text,temp_text);
	
	
	memset(temp_text,0,sizeof(temp_text));
	sprintf(temp_text,"%cPort%c:%c%d%c,\n",dbl_qts,dbl_qts,dbl_qts,MAX_NO_OF_SERIAL_PORT,dbl_qts);
	strcat(json_text,temp_text);
	
	memset(temp_text,0,sizeof(temp_text));
	if(ATSAM91G)
		sprintf(temp_text,"%cHwType%c:%c%s%c\n",dbl_qts,dbl_qts,dbl_qts,"ATSAM91G",dbl_qts);
	else
		sprintf(temp_text,"%cHwType%c:%c%s%c\n",dbl_qts,dbl_qts,dbl_qts,"ATSAM91X",dbl_qts);
		
	strcat(json_text,temp_text);
	
	strcat(json_text,"}\n");
	
	p_file_ptr = fopen("cms_dcu_feature.json","w");
	if ( p_file_ptr == NULL )
		return;
	
	fprintf(p_file_ptr,"%s",json_text);
	fflush(p_file_ptr);
	
	fclose(p_file_ptr);
}

int main(int argc, char** argv)
{
	printf("Creating Default Config\n");
	
	//printf("Size of Config Structure : %ld\n",sizeof(dlms_dcu_config_t));
	
	fill_default_cfg();
	
	//generate_cfg_json();
	
	//store_cfg_json();
	
	create_cfg_file();
	
	create_version_file();
	
	create_feature_json();
	
	return 0;
}

/* End Of File */