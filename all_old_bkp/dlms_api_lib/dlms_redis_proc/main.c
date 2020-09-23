/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	main.c
* Summary:  Redis and DLMS Module.
*
**********************************************************************/

/* Includes */
#include "gen_inc.h"
#include "gen_fun.h"
#include "log.h"
#include "dlms_fun.h"
#include "dlms_api.h"
//#include "/home/iot-gateway/hiredis/hiredis.h"
#include "hiredis.h"

/* ---------------------------------------------------------- */
int32_t main(int argc , char** argv)
{
	static char fun_name[]="main()";
	float p_flt_ptr=0.0;
	uint8_t obis[6]={0};
	
	printf("In Dlms Redis Programm\n");
	
	char p_msg[128];
	const char *hostname = "192.168.101.108";
    int port = 6379;
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    
	redisContext *c;
	redisReply *reply;

	printf("Try to connect to Redis Server : %s\n",hostname);
	c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) 
	{
        if (c) 
		{
            printf("Connection error: %s\n", c->errstr);
			printf("Disconnecting to Redis Server : %s\n",hostname);
            redisFree(c);
        } 
		else 
		{
            printf("Connection error: can't allocate redis context\n");
        }
		
        exit(1);
    }
	
	printf("Connected to Redis Server\n");
	
	/* PING server */
    reply = redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
	
    freeReplyObject(reply);

	meter_comm_params_t meter_comm_params;

	serport_params_t serport_params;

	// Filling some default value to structure to start communication
	strcpy(serport_params.ser_port,"/dev/ttyS4");
	serport_params.baudrate=10;
	serport_params.databits=8;
	serport_params.stopbits=1;
	serport_params.parity=0;
	serport_params.handshake=NO_HANDSHAKE;
	serport_params.infmode=RS232_MODE;

	meter_comm_params.inf_type=INF_SERIAL;
	meter_comm_params.meter_type=LNT;
	meter_comm_params.meter_addr_format=1;
	
	if(meter_comm_params.meter_addr_format==1)
	{
		meter_comm_params.meter_id=3;
	}
	else
	{
		meter_comm_params.meter_id=19;
	}
	meter_comm_params.interface_params=&serport_params;
	sprintf(meter_comm_params.filename,"%s/meter_id_%02d",ROOT_DATA_DIR,meter_comm_params.meter_id);
	strcpy(meter_comm_params.meter_pass,"lnt1");
	
	if(init_comm(&meter_comm_params)<0)
	{
		printf("Failed to initilized communication.\n");
		return -1;
	}
	
	printf("Initilized communication success\n");
	
	if(connect_to_meter(&meter_comm_params)<0)
	{
		printf("Failed to connect to meter\n");
		return -1;
	}
	
	obis_name_plate_info_t name_plate_info;
	if(get_nameplate_details(&meter_comm_params, &name_plate_info)<0)
	{
		printf("Failed to get nameplate details.\n");
		return -1;
	}
	else
	{
		printf("OBIS_CODE\t\tPARAMS_NAME\t\tPARAM_VALUE\n");
		
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%s\n",
				name_plate_info.meter_ser_num.param_obis_code[0],
				name_plate_info.meter_ser_num.param_obis_code[1],
				name_plate_info.meter_ser_num.param_obis_code[2],
				name_plate_info.meter_ser_num.param_obis_code[3],
				name_plate_info.meter_ser_num.param_obis_code[4],
				name_plate_info.meter_ser_num.param_obis_code[5],
				name_plate_info.meter_ser_num.param_name,
				name_plate_info.meter_ser_num.param_value
				);
		
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%s\n",
				name_plate_info.manf_name.param_obis_code[0],
				name_plate_info.manf_name.param_obis_code[1],
				name_plate_info.manf_name.param_obis_code[2],
				name_plate_info.manf_name.param_obis_code[3],
				name_plate_info.manf_name.param_obis_code[4],
				name_plate_info.manf_name.param_obis_code[5],
				name_plate_info.manf_name.param_name,
				name_plate_info.manf_name.param_value
				);
				
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%s\n",
				name_plate_info.fw_vwesion.param_obis_code[0],
				name_plate_info.fw_vwesion.param_obis_code[1],
				name_plate_info.fw_vwesion.param_obis_code[2],
				name_plate_info.fw_vwesion.param_obis_code[3],
				name_plate_info.fw_vwesion.param_obis_code[4],
				name_plate_info.fw_vwesion.param_obis_code[5],
				name_plate_info.fw_vwesion.param_name,
				name_plate_info.fw_vwesion.param_value
				);
				
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%d\n",
				name_plate_info.meter_type.param_obis_code[0],
				name_plate_info.meter_type.param_obis_code[1],
				name_plate_info.meter_type.param_obis_code[2],
				name_plate_info.meter_type.param_obis_code[3],
				name_plate_info.meter_type.param_obis_code[4],
				name_plate_info.meter_type.param_obis_code[5],
				name_plate_info.meter_type.param_name,
				name_plate_info.meter_type.param_value[0]
				);
		
		memcpy(&p_flt_ptr,&name_plate_info.int_ct_ratio.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				name_plate_info.int_ct_ratio.param_obis_code[0],
				name_plate_info.int_ct_ratio.param_obis_code[1],
				name_plate_info.int_ct_ratio.param_obis_code[2],
				name_plate_info.int_ct_ratio.param_obis_code[3],
				name_plate_info.int_ct_ratio.param_obis_code[4],
				name_plate_info.int_ct_ratio.param_obis_code[5],
				name_plate_info.int_ct_ratio.param_name,
				p_flt_ptr
				/* name_plate_info.int_ct_ratio.param_value */
				);
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&name_plate_info.int_pt_ratio.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				name_plate_info.int_pt_ratio.param_obis_code[0],
				name_plate_info.int_pt_ratio.param_obis_code[1],
				name_plate_info.int_pt_ratio.param_obis_code[2],
				name_plate_info.int_pt_ratio.param_obis_code[3],
				name_plate_info.int_pt_ratio.param_obis_code[4],
				name_plate_info.int_pt_ratio.param_obis_code[5],
				name_plate_info.int_pt_ratio.param_name,
				p_flt_ptr
				/* name_plate_info.int_pt_ratio.param_value */
				);
	
		printf("+++++++ Recv Nameplate info success\n");
	}
	
	//name_plate_info
	char key_name[32]="name_plate_det_key";
	
	reply = redisCommand(c, "HMSET %s stat %b", key_name, &name_plate_info, sizeof(name_plate_info));
	printf("Saveṣ status : %s\n", reply->str);//that shows +OK
		
	freeReplyObject(reply);

	printf("Disconnecting from Metere & closing connection\n",hostname);
	disconnect_meter(&meter_comm_params);
	
	/* Disconnects and frees the context */
	printf("Disconnecting to Redis Server : %s\n",hostname);
    
	redisFree(c);
	
	return RET_SUCCESS;
}