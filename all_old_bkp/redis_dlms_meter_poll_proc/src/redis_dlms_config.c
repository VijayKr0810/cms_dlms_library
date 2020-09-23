/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	redis_dlms_config.c
* Summary:  Redis and DLMS Module.
*
**********************************************************************/

/* Includes */
#include "gen_inc.h"
#include "gen_fun.h"
#include "log.h"
#include "dlms_fun.h"
#include "dlms_api.h"

/* ---------------------------------------------------------- */

int32_t fill_def_config(meter_comm_params_t *meter_comm_params)
{
	serport_params_t serport_params;

	// Filling some default value to structure to start communication
	strcpy(serport_params.ser_port,"/dev/ttyS4");
	serport_params.baudrate=10;
	serport_params.databits=8;
	serport_params.stopbits=1;
	serport_params.parity=0;
	serport_params.handshake=NO_HANDSHAKE;
	serport_params.infmode=RS232_MODE;

	meter_comm_params->inf_type=INF_SERIAL;
	meter_comm_params->meter_type=LNT;
	meter_comm_params->meter_addr_format=1;
	
	if(meter_comm_params->meter_addr_format==1)
	{
		meter_comm_params->meter_id=3;
	}
	else
	{
		meter_comm_params->meter_id=19;
	}
	
	memcpy(&meter_comm_params->interface_params,&serport_params,sizeof(serport_params_t));
	sprintf(meter_comm_params->filename,"%s/meter_id_%02d",ROOT_DATA_DIR,meter_comm_params->meter_id);
	strcpy(meter_comm_params->meter_pass,"lnt1");
	
	return RET_SUCCESS;
}
