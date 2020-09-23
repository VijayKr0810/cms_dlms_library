#include "dlms_module.h"

int main(void)
{
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
	meter_comm_params.meter_id=18;
	meter_comm_params.meter_addr_format=1;
	meter_comm_params.interface_params=&serport_params;
	strcpy(meter_comm_params.filename,"./DlmsData");
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
	
	name_plate_info_t name_plate_info;
	
	if(get_nameplate_details(&name_plate_info)<0)
	{
		printf("Failed to get nameplate details.\n");
		return -1;
	}

	printf("+++++++ Recv Nameplate info success\n");

	gen_params_det_t 				gen_inst_param_det;
	gen_params_det_t 				gen_ls_param_det;
	gen_params_det_t 				gen_event_param_det;
	gen_params_det_t 				gen_bill_param_det;
	gen_params_det_t 				gen_daily_prof_param_det;
	
	if(get_obis_codes(&gen_inst_param_det,&gen_ls_param_det,
	&gen_event_param_det,&gen_bill_param_det,&gen_daily_prof_param_det)<0)
	{
		printf("Failed to get obis codes..n");
		return -1;
	}

	inst_val_info_t					inst_data_val;

	if(get_inst_values(&inst_data_val)<0)
	{
		printf("Failed to get inst value..n");
		return -1;
	}
	
	get_curr_date_ls_data();
	
	return 0;
}