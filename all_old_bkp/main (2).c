/***********************************************************************
* Copyright (c) 2019 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	main.c
* Summary:  Iot modbus poll proc.
*
**********************************************************************/

/*** Include ***/
#include "iot_general.h"
#include "iot_modbus_rel.h"
#include "iot_dev_config.h"
#include "iot_ipc_msg.h"
#include <hiredis.h>
/* Local Micro */

#define DIAG_SEND_TIME_REFF 45
/* ==================================================================== */
/* Local Micro */

#define HC_MSG_SEND_TIME_REFF 15
/* Structures */
iot_dev_cfg_t 					iot_dev_cfg;
ipc_msg_t                       ipc_msg;
iot_data_list_t                 iot_data_list;
iot_stats_t						iot_stats[MAX_NO_OF_METER_PER_PORT];
iot_event_data_t  				iot_event_data;

/* Globals */
uint8_t                         g_pidx,g_midx;
uint8_t                   		g_meter_status[MAX_NO_OF_METER_PER_PORT];
uint8_t                   		g_recv_ser_buff[SIZE_1024];
uint16_t						g_met_reg_offset;
uint8_t							g_ser_mon_flag=0;

struct                          tm *p_info;
time_t                          g_rawtime;
time_t 							g_last_send_time,g_last_diag_time;



redisContext *c;
redisReply *reply; 

/* ============================================================================ */


/****************************************
*Function 		: write_hc_msg_on_redis()
*Params 		: None
*Return			: Success 
*Description 	: Entry point of module
*****************************************/

int32_t write_hc_msg_on_redis()
{
	time_t 		curr_time = 0;
	int idx=0;
	curr_time = time(NULL);
	for (idx=0;idx<MAX_NO_OF_SERIAL_PORT;idx++)
		reply = redisCommand(c,"hmset modbus_master_%d_hc_msg updatetime %d",idx,curr_time);

	return RET_OK;
}

/****************************************
*Function 		: read_ser_mon_flag()
*Params 		: None
*Return			: Success 
*Description 	: to read serial monitor flag from redis
*****************************************/
int32_t read_ser_mon_flag ()
{
	
	reply = redisCommand(c,"hmget serial_monitor status");
	if (reply->element[0]->str)
		g_ser_mon_flag=atoi(reply->element[0]->str);
		//printf("status is %d\n",g_ser_mon_flag);
	freeReplyObject(reply);
	return RET_OK;
	
}
/****************************************
*Function 		: main()
*Params 		: redis ip and port number 
*Return			: Success or error code
*Description 	: Entry point of module
*****************************************/
int main( int argc, char *argv[] )
{
    static char fun_name[]="main()";
    char ser_port_name[SIZE_32];
	//const char *hostname = (argc > 3) ? argv[3] : "127.0.0.1";
	//int port = (argc > 4) ? atoi(argv[4]) : 6379;
	const char *hostname = "127.0.0.1";
	int port = 6379;
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) 
	{
        if (c) 
		{
			dbg_log(INFORM,"%-25s : Redis Connection error: %s\n",fun_name, c->errstr);
            redisFree(c);
        } 
		else 
		{
			dbg_log(INFORM,"%-25s : Redis Connection error: can't allocate redis context\n",fun_name);
        }
        exit(1);
    }
	else
	{
		dbg_log(INFORM,"%-25s : Successfully connected with redis\n",fun_name);
	}
    if (argc<2)
    {
        dbg_log(FATAL,"Usage Msg !!! , please Use ./iotModPollProc PortNo ..\n ");
        return RET_FAILURE;
    }
	
    g_pidx =  atoi(argv[1]);
    printf("Selected Port : %d\n",g_pidx);
    write_hc_msg_on_redis();
    if(read_bin_cfg()<0)
    {
        dbg_log(FATAL,"%-25s : read_bin_cfg Initialization Failed !\n",fun_name);
        return RET_FAILURE;
    }
    write_hc_msg_on_redis();
    if(ipc_socket_create()<0)
    {
        dbg_log(FATAL,"%-25s : ipc_socket_create Initialization Failed !\n",fun_name);
        return RET_FAILURE;
    }
	write_hc_msg_on_redis();
    memset(ser_port_name,0,32);
    //strcpy(ser_port_name,"/dev/ttyS4");
    strcpy(ser_port_name,SER_PORT_4_DET);
	//strcpy(ser_port_name,SER_PORT_2_DET);
	dbg_log(INFORM,"%-25s : Starting Comm Port Det : %s\n",fun_name,ser_port_name);
	
	write_hc_msg_on_redis();
    if( init_serial_io(ser_port_name)<0)
    {
        dbg_log(FATAL,"%-25s : Communication Serial Port Initialization Failed !\n",fun_name);
        return RET_COMM_SER_PORT_INIT_FAIL;
    }
	write_hc_msg_on_redis();
	g_ser_mon_flag = 0;
	write_hc_msg_on_redis();
    init_and_sort_query();
    write_hc_msg_on_redis();
	g_last_send_time = time(NULL);
	g_last_diag_time = time(NULL);
	
    while(1)
    {
		write_hc_msg_on_redis();
		read_ser_mon_flag();
		
		write_hc_msg_on_redis();
        poll_mod_dev();
		
		g_midx = 0;
		
		write_devices_status();
        
		
		write_hc_msg_on_redis();
		
		send_diag_info_to_redis();
		
        usleep(500000);
    }
	
    return RET_OK;
}

/*********************************************************************
*Function 		: send_diag_info_to_redis()
*In Params 		: void.
*Output 		: None
*Return			: void.
*Description 	: To send diag message to status proc.
**********************************************************************/
void send_diag_info_to_redis(void)
{
	time_t curr_time=0;
	curr_time = time(NULL);
	int idx=0;
	if((curr_time - g_last_diag_time) > DIAG_SEND_TIME_REFF)
	{
		for(idx=0;idx<MAX_NO_OF_METER_PER_PORT;idx++)
		{
			reply = redisCommand(c,"hmset serport%d_meter%d_diag send_qry_cnt %d recv_resp_cnt %d",g_pidx,idx,iot_stats[idx].send_qry_cnt,iot_stats[idx].recv_resp_cnt);
			freeReplyObject(reply);
			reply = redisCommand(c,"hmset serport%d_meter%d_diag no_resp_cnt %d valid_resp_cnt %d",g_pidx,idx,iot_stats[idx].no_resp_cnt,iot_stats[idx].valid_resp_cnt);
			freeReplyObject(reply);
			reply = redisCommand(c,"hmset serport%d_meter%d_diag invalid_resp_cnt %d",g_pidx,idx,iot_stats[idx].invalid_resp_cnt);
			freeReplyObject(reply);
						
		}
		g_last_diag_time=time(NULL);

	}
}



/*********************************************************************
*Function 		: print_data()
*In Params 		: buffer and length.
*Output 		: None
*Return			: void.
*Description 	: print byte by byte buffer .
**********************************************************************/
void print_data(char *p_msg, int32_t len)
{
    uint32_t i=0,frame_cnt=1;
    uint8_t frame_len=16;
    char local_buff[SIZE_128],temp_buff[SIZE_16];
    
    memset(local_buff,0,sizeof(local_buff));

	for(i=0;i<len;i++)
	{
		memset(temp_buff,0,sizeof(temp_buff));
		sprintf(temp_buff,"%02x  ",p_msg[i]&0xff);
		strcat(local_buff,temp_buff);
		if((frame_cnt*frame_len-1==i) && (i>0))
		{
			dbg_log(INFORM,"%s\n",local_buff);
			frame_cnt++;
			memset(local_buff,0,sizeof(local_buff));
		}
	}   
	
	dbg_log(INFORM,"%s\n",local_buff);
}

/*********************************************************************
*Function 		: read_bin_cfg()
*In Params 		: void.
*Output 		: None
*Return			: status.
*Description 	: To read iot device configuration  .
**********************************************************************/
int32_t read_bin_cfg(void)
{
    static char fun_name[]="read_bin_cfg()";
    FILE *p_file_ptr=NULL;
    
    p_file_ptr=fopen(DEVICE_CFG_FILE,"r");
    if(p_file_ptr==NULL)
    {
        printf("Unable to open cfg file , Error : %s\n",strerror(errno));
        return -1;
    }
    
    fread((void*)&iot_dev_cfg,sizeof(iot_dev_cfg),1,p_file_ptr);
	printf("start flag :%x end flag :%x\n",iot_dev_cfg.start_flag,iot_dev_cfg.end_flag);
	printf("crc is %x\n",iot_dev_cfg.crc);
    if(iot_dev_cfg.start_flag==START_END_FLAG)
    {
        if(iot_dev_cfg.end_flag==START_END_FLAG)
        {
            if(iot_dev_cfg.crc==modbus_crc16((char*)&iot_dev_cfg,sizeof(iot_dev_cfg)-6))
            {
                dbg_log(INFORM,"%-25s : Device Config validation success\n",fun_name);
            }
            else
            {
                dbg_log(REPORT,"%-25s : Device CRC Not Matched\n",fun_name);
				fclose(p_file_ptr);
                return RET_FAILURE;
            }
        }
        else
        {
            dbg_log(REPORT,"%-25s : Device EndFlag Not Matched\n",fun_name);
			fclose(p_file_ptr);
            return RET_FAILURE;
        }
    }
    else
    {
        dbg_log(REPORT,"%-25s : Device StartFlag Not Matched\n",fun_name);
		fclose(p_file_ptr);
        return RET_FAILURE;
    }
	
	fclose(p_file_ptr);
    dbg_log(INFORM,"%-25s : Device Config struct reas success : SIZE : %d\n",fun_name,sizeof(iot_dev_cfg));
    
    return RET_OK;  
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

/* End of file */
