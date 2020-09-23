/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	test_lib.c
* Summary:  To test the DLMS API Library.
*
**********************************************************************/

/* Include */
#include "gen_inc.h"
#include "gen_fun.h"
#include "log.h"
#include "dlms_fun.h"
#include "dlms_api.h"
 
/* -------------------------------------------------------------------------------- */

int main(void)
{
	static char fun_name[]="main()";
	float p_flt_ptr=0.0;
	uint8_t obis[6]={0};

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
	#if 1
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
	
	#endif
	gen_params_det_t 				gen_inst_param_det;
	gen_params_det_t 				gen_ls_param_det;
	gen_params_det_t 				gen_event_param_det;
	gen_params_det_t 				gen_bill_param_det;
	gen_params_det_t 				gen_daily_prof_param_det;
	
	if(get_obis_codes(&meter_comm_params,&gen_inst_param_det,&gen_ls_param_det,
	&gen_event_param_det,&gen_bill_param_det,&gen_daily_prof_param_det)<0)
	{
		printf("Failed to get obis codes..n");
		return -1;
	}
	
	inst_val_info_t				g_inst_data_val;
	memset(&g_inst_data_val,0,sizeof(g_inst_data_val));
	
	#if 0
	if(get_inst_values(&meter_comm_params,&g_inst_data_val)<0)
	{
		printf("Failed to get inst value..n");
		return -1;
	}
	else
	{
		p_flt_ptr=0.0;
		printf(">>>>>>>>>>>>>>>>>>>>>> Recv Inst success\n");
		printf("OBIS_CODE\t\tPARAMS_NAME\t\tPARAM_VALUE\n");
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.cur_iy.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.cur_iy.param_obis_code[0],g_inst_data_val.cur_iy.param_obis_code[1],
				g_inst_data_val.cur_iy.param_obis_code[2],g_inst_data_val.cur_iy.param_obis_code[3],
				g_inst_data_val.cur_iy.param_obis_code[4],g_inst_data_val.cur_iy.param_obis_code[5],
				g_inst_data_val.cur_iy.param_name,p_flt_ptr
				);
				
				p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.cur_ib.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.cur_ib.param_obis_code[0],g_inst_data_val.cur_ib.param_obis_code[1],
				g_inst_data_val.cur_ib.param_obis_code[2],g_inst_data_val.cur_ib.param_obis_code[3],
				g_inst_data_val.cur_ib.param_obis_code[4],g_inst_data_val.cur_ib.param_obis_code[5],
				g_inst_data_val.cur_ib.param_name,p_flt_ptr
				);
				
				p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.cur_iy.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.cur_iy.param_obis_code[0],g_inst_data_val.cur_iy.param_obis_code[1],
				g_inst_data_val.cur_iy.param_obis_code[2],g_inst_data_val.cur_iy.param_obis_code[3],
				g_inst_data_val.cur_iy.param_obis_code[4],g_inst_data_val.cur_iy.param_obis_code[5],
				g_inst_data_val.cur_iy.param_name,p_flt_ptr
				);
				
				p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.volt_r.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.volt_r.param_obis_code[0],g_inst_data_val.volt_r.param_obis_code[1],
				g_inst_data_val.volt_r.param_obis_code[2],g_inst_data_val.volt_r.param_obis_code[3],
				g_inst_data_val.volt_r.param_obis_code[4],g_inst_data_val.volt_r.param_obis_code[5],
				g_inst_data_val.volt_r.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.volt_b.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.volt_b.param_obis_code[0],g_inst_data_val.volt_b.param_obis_code[1],
				g_inst_data_val.volt_b.param_obis_code[2],g_inst_data_val.volt_b.param_obis_code[3],
				g_inst_data_val.volt_b.param_obis_code[4],g_inst_data_val.volt_b.param_obis_code[5],
				g_inst_data_val.volt_b.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.volt_y.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.volt_y.param_obis_code[0],g_inst_data_val.volt_y.param_obis_code[1],
				g_inst_data_val.volt_y.param_obis_code[2],g_inst_data_val.volt_y.param_obis_code[3],
				g_inst_data_val.volt_y.param_obis_code[4],g_inst_data_val.volt_y.param_obis_code[5],
				g_inst_data_val.volt_y.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.pf_r.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.pf_r.param_obis_code[0],g_inst_data_val.pf_r.param_obis_code[1],
				g_inst_data_val.pf_r.param_obis_code[2],g_inst_data_val.pf_r.param_obis_code[3],
				g_inst_data_val.pf_r.param_obis_code[4],g_inst_data_val.pf_r.param_obis_code[5],
				g_inst_data_val.pf_r.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.pf_y.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.pf_y.param_obis_code[0],g_inst_data_val.pf_y.param_obis_code[1],
				g_inst_data_val.pf_y.param_obis_code[2],g_inst_data_val.pf_y.param_obis_code[3],
				g_inst_data_val.pf_y.param_obis_code[4],g_inst_data_val.pf_y.param_obis_code[5],
				g_inst_data_val.pf_y.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.pf_b.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.pf_b.param_obis_code[0],g_inst_data_val.pf_b.param_obis_code[1],
				g_inst_data_val.pf_b.param_obis_code[2],g_inst_data_val.pf_b.param_obis_code[3],
				g_inst_data_val.pf_b.param_obis_code[4],g_inst_data_val.pf_b.param_obis_code[5],
				g_inst_data_val.pf_b.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.pf_avg.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.pf_avg.param_obis_code[0],g_inst_data_val.pf_avg.param_obis_code[1],
				g_inst_data_val.pf_avg.param_obis_code[2],g_inst_data_val.pf_avg.param_obis_code[3],
				g_inst_data_val.pf_avg.param_obis_code[4],g_inst_data_val.pf_avg.param_obis_code[5],
				g_inst_data_val.pf_avg.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.freq.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.freq.param_obis_code[0],g_inst_data_val.freq.param_obis_code[1],
				g_inst_data_val.freq.param_obis_code[2],g_inst_data_val.freq.param_obis_code[3],
				g_inst_data_val.freq.param_obis_code[4],g_inst_data_val.freq.param_obis_code[5],
				g_inst_data_val.freq.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_inst_data_val.kw.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_inst_data_val.kw.param_obis_code[0],g_inst_data_val.kw.param_obis_code[1],
				g_inst_data_val.kw.param_obis_code[2],g_inst_data_val.kw.param_obis_code[3],
				g_inst_data_val.kw.param_obis_code[4],g_inst_data_val.kw.param_obis_code[5],
				g_inst_data_val.kw.param_name,p_flt_ptr
				);
	}
	
	#endif
	/* 	get_ls_values_hour_range(&meter_comm_params,10);
	
	printf("TestLib ::: RespLen : %d\n",meter_comm_params.resp_len);
	
	get_ls_values_day_range(&meter_comm_params,10); */
	
	//if(get_ls_values_block_range(&meter_comm_params,1)<0)
	#if 0
	if(get_ls_values_day_range(&meter_comm_params,10)<0)
	{
		printf("Failed to get ls block data by block range\n");
	}
	else
	{
		block_val_info_t 			g_block_val_info;
		printf("Ls Block resp len : %d\n",meter_comm_params.resp_len);
		
		memcpy(&g_block_val_info,meter_comm_params.meter_response,sizeof(block_val_info_t));
		
		p_flt_ptr=0.0;
		printf(">>>>>>>>>>>>>>>>>>>>>> Recv LS Block data  success\n");
		printf("OBIS_CODE\t\tPARAMS_NAME\t\tPARAM_VALUE\n");
		
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.kwh_imp.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.kwh_imp.param_obis_code[0],g_block_val_info.kwh_imp.param_obis_code[1],
				g_block_val_info.kwh_imp.param_obis_code[2],g_block_val_info.kwh_imp.param_obis_code[3],
				g_block_val_info.kwh_imp.param_obis_code[4],g_block_val_info.kwh_imp.param_obis_code[5],
				g_block_val_info.kwh_imp.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.kwh_exp.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.kwh_exp.param_obis_code[0],g_block_val_info.kwh_exp.param_obis_code[1],
				g_block_val_info.kwh_exp.param_obis_code[2],g_block_val_info.kwh_exp.param_obis_code[3],
				g_block_val_info.kwh_exp.param_obis_code[4],g_block_val_info.kwh_exp.param_obis_code[5],
				g_block_val_info.kwh_exp.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.cur_iy.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.cur_iy.param_obis_code[0],g_block_val_info.cur_iy.param_obis_code[1],
				g_block_val_info.cur_iy.param_obis_code[2],g_block_val_info.cur_iy.param_obis_code[3],
				g_block_val_info.cur_iy.param_obis_code[4],g_block_val_info.cur_iy.param_obis_code[5],
				g_block_val_info.cur_iy.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.cur_iy.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.cur_iy.param_obis_code[0],g_block_val_info.cur_iy.param_obis_code[1],
				g_block_val_info.cur_iy.param_obis_code[2],g_block_val_info.cur_iy.param_obis_code[3],
				g_block_val_info.cur_iy.param_obis_code[4],g_block_val_info.cur_iy.param_obis_code[5],
				g_block_val_info.cur_iy.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.cur_iy.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.cur_iy.param_obis_code[0],g_block_val_info.cur_iy.param_obis_code[1],
				g_block_val_info.cur_iy.param_obis_code[2],g_block_val_info.cur_iy.param_obis_code[3],
				g_block_val_info.cur_iy.param_obis_code[4],g_block_val_info.cur_iy.param_obis_code[5],
				g_block_val_info.cur_iy.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.cur_ib.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.cur_ib.param_obis_code[0],g_block_val_info.cur_ib.param_obis_code[1],
				g_block_val_info.cur_ib.param_obis_code[2],g_block_val_info.cur_ib.param_obis_code[3],
				g_block_val_info.cur_ib.param_obis_code[4],g_block_val_info.cur_ib.param_obis_code[5],
				g_block_val_info.cur_ib.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.cur_iy.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.cur_iy.param_obis_code[0],g_block_val_info.cur_iy.param_obis_code[1],
				g_block_val_info.cur_iy.param_obis_code[2],g_block_val_info.cur_iy.param_obis_code[3],
				g_block_val_info.cur_iy.param_obis_code[4],g_block_val_info.cur_iy.param_obis_code[5],
				g_block_val_info.cur_iy.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.volt_r.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.volt_r.param_obis_code[0],g_block_val_info.volt_r.param_obis_code[1],
				g_block_val_info.volt_r.param_obis_code[2],g_block_val_info.volt_r.param_obis_code[3],
				g_block_val_info.volt_r.param_obis_code[4],g_block_val_info.volt_r.param_obis_code[5],
				g_block_val_info.volt_r.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.volt_b.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.volt_b.param_obis_code[0],g_block_val_info.volt_b.param_obis_code[1],
				g_block_val_info.volt_b.param_obis_code[2],g_block_val_info.volt_b.param_obis_code[3],
				g_block_val_info.volt_b.param_obis_code[4],g_block_val_info.volt_b.param_obis_code[5],
				g_block_val_info.volt_b.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.volt_y.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.volt_y.param_obis_code[0],g_block_val_info.volt_y.param_obis_code[1],
				g_block_val_info.volt_y.param_obis_code[2],g_block_val_info.volt_y.param_obis_code[3],
				g_block_val_info.volt_y.param_obis_code[4],g_block_val_info.volt_y.param_obis_code[5],
				g_block_val_info.volt_y.param_name,p_flt_ptr
				);
				
		p_flt_ptr=0.0;
		memcpy(&p_flt_ptr,&g_block_val_info.freq.param_value,4);
		printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
				g_block_val_info.freq.param_obis_code[0],g_block_val_info.freq.param_obis_code[1],
				g_block_val_info.freq.param_obis_code[2],g_block_val_info.freq.param_obis_code[3],
				g_block_val_info.freq.param_obis_code[4],g_block_val_info.freq.param_obis_code[5],
				g_block_val_info.freq.param_name,p_flt_ptr
				);
	}
	
	#endif
	
	#if 1
	uint8_t event_class_type=0;
	event_val_info_t event_val_info;
	
	for(event_class_type=0; event_class_type<7; event_class_type++)
	//for(event_class_type=3; event_class_type<5; event_class_type++)
	{
		events_type_info_t events_type_info;
		
		printf("requesting Event data for event class type : %d\n",event_class_type);
		if(get_event_data_all(&meter_comm_params, event_class_type)>0)
		{
			memcpy(&event_val_info,&meter_comm_params.meter_response,sizeof(event_val_info_t));
			
			p_flt_ptr=0.0;
			printf(">>>>>>>>>>>>>>>>>>>>>> Recv Event data  success for event type : %d\n",event_class_type);
			printf("OBIS_CODE\t\tPARAMS_NAME\t\tPARAM_VALUE\n");
			
			p_flt_ptr=0.0;
			memcpy(&p_flt_ptr,&event_val_info.kwh.param_value,4);
			printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
					event_val_info.kwh.param_obis_code[0],event_val_info.kwh.param_obis_code[1],
					event_val_info.kwh.param_obis_code[2],event_val_info.kwh.param_obis_code[3],
					event_val_info.kwh.param_obis_code[4],event_val_info.kwh.param_obis_code[5],
					event_val_info.kwh.param_name,p_flt_ptr
					);
					
			p_flt_ptr=0.0;
			memcpy(&p_flt_ptr,&event_val_info.cur_iy.param_value,4);
			printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
					event_val_info.cur_iy.param_obis_code[0],event_val_info.cur_iy.param_obis_code[1],
					event_val_info.cur_iy.param_obis_code[2],event_val_info.cur_iy.param_obis_code[3],
					event_val_info.cur_iy.param_obis_code[4],event_val_info.cur_iy.param_obis_code[5],
					event_val_info.cur_iy.param_name,p_flt_ptr
					);
									
			p_flt_ptr=0.0;
			memcpy(&p_flt_ptr,&event_val_info.cur_ib.param_value,4);
			printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
					event_val_info.cur_ib.param_obis_code[0],event_val_info.cur_ib.param_obis_code[1],
					event_val_info.cur_ib.param_obis_code[2],event_val_info.cur_ib.param_obis_code[3],
					event_val_info.cur_ib.param_obis_code[4],event_val_info.cur_ib.param_obis_code[5],
					event_val_info.cur_ib.param_name,p_flt_ptr
					);
					
			p_flt_ptr=0.0;
			memcpy(&p_flt_ptr,&event_val_info.cur_iy.param_value,4);
			printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
					event_val_info.cur_iy.param_obis_code[0],event_val_info.cur_iy.param_obis_code[1],
					event_val_info.cur_iy.param_obis_code[2],event_val_info.cur_iy.param_obis_code[3],
					event_val_info.cur_iy.param_obis_code[4],event_val_info.cur_iy.param_obis_code[5],
					event_val_info.cur_iy.param_name,p_flt_ptr
					);
					
			p_flt_ptr=0.0;
			memcpy(&p_flt_ptr,&event_val_info.volt_r.param_value,4);
			printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
					event_val_info.volt_r.param_obis_code[0],event_val_info.volt_r.param_obis_code[1],
					event_val_info.volt_r.param_obis_code[2],event_val_info.volt_r.param_obis_code[3],
					event_val_info.volt_r.param_obis_code[4],event_val_info.volt_r.param_obis_code[5],
					event_val_info.volt_r.param_name,p_flt_ptr
					);
					

			p_flt_ptr=0.0;
			memcpy(&p_flt_ptr,&event_val_info.volt_b.param_value,4);
			printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
					event_val_info.volt_b.param_obis_code[0],event_val_info.volt_b.param_obis_code[1],
					event_val_info.volt_b.param_obis_code[2],event_val_info.volt_b.param_obis_code[3],
					event_val_info.volt_b.param_obis_code[4],event_val_info.volt_b.param_obis_code[5],
					event_val_info.volt_b.param_name,p_flt_ptr
					);
					
			p_flt_ptr=0.0;
			memcpy(&p_flt_ptr,&event_val_info.volt_y.param_value,4);
			printf("%d.%d.%d.%d.%d.%d\t\t%s\t\t%0.5f\n",
					event_val_info.volt_y.param_obis_code[0],event_val_info.volt_y.param_obis_code[1],
					event_val_info.volt_y.param_obis_code[2],event_val_info.volt_y.param_obis_code[3],
					event_val_info.volt_y.param_obis_code[4],event_val_info.volt_y.param_obis_code[5],
					event_val_info.volt_y.param_name,p_flt_ptr
					);
		}
	}

	//get_event_data_all(&meter_comm_params,event_class_type);
	
	//get_event_data(&meter_comm_params,1);
	#endif
	
	get_billing_info(&meter_comm_params);
	
	//get_midnight_data_all(&meter_comm_params);
	//get_midnight_data(&meter_comm_params);
	
	disconnect_meter(&meter_comm_params);
	
	return 0;
}