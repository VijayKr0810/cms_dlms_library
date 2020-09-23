/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	gen_fun.c
* Summary:  General used functions.
*
**********************************************************************/

/* Includes */
#include "gen_inc.h"
#include "gen_fun.h"
#include "log.h"
#include "dlms_api.h"
#include "dlms_fun.h"

/* Local Micro */
// Databits
#define		FIVE_BITS			5
#define		SIX_BITS			6
#define		SEVEN_BITS			7
#define		EIGHT_BITS			8

// Stop bits
#define		ONE					1
#define		TWO					2

//serial port constants
#define		NONE_PARITY			0x00
#define		ODD_PARITY			0x01
#define		EVEN_PARITY			0x02

//flow control
#define 	NO_HANDSHAKE		0x00
#define 	HW_HANDSHAKE		0x01
#define 	SW_HANDSHAKE		0x02

#define 	RS232_MODE			1
#define 	RS485_MODE			2
/* Globals */
char 						loc_buff[1024];

/* -------------------------------------------------------------------------------------------------- */
/**************************************************************************************************
*Function 					: init_tcp_conn()
*Input Parameters 			: Structure containing type of communication and the required parameters. 
							  Type identifying serial or ethernet.
*Output Parameters 			: Serial fd or socket fd.
*Return	Value				: Success or appropriate error code.
*Description 				: Initilised TCP connection.
********************************************************************************************************/
int8_t init_tcp_conn(meter_comm_params_t *meter_comm_params)
{
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: init_serial()
*Input Parameters 			: Structure containing type of communication and the required parameters. 
							  Type identifying serial or ethernet.
*Output Parameters 			: Serial fd or socket fd.
*Return	Value				: Success or appropriate error code.
*Description 				: Initilised Serial connection.
********************************************************************************************************/
int8_t init_serial(meter_comm_params_t *meter_comm_params)
{
	static char fun_name[]="init_serial()";
	static tcflag_t				port_speed[SIZE_16] = { 0, B50,B75,B110,B200,B300,B600,B1200,B2400,B4800,B9600, B19200, B38400, B57600, B115200};
	tcflag_t 					baudrate, hw_flow_ctrl, databits, stopbits, parity_on, parity, sw_flow_ctrl;
	uint8_t midx=0;
	
	serport_params_t serport_params;
	
	memset(&serport_params,0,sizeof(serport_params));
	
	memcpy(&serport_params,meter_comm_params->interface_params,sizeof(serport_params));
	
	printf("meter_comm_params Library side size : %d\n",sizeof(meter_comm_params));
	printf("Library side size : %d\n",sizeof(serport_params));
	
	switch (serport_params.handshake)
	{
		case HW_HANDSHAKE:
			hw_flow_ctrl = CRTSCTS;
			sw_flow_ctrl = 0;
			printf("HW Handshake\n");
			break;
			
		case SW_HANDSHAKE:
			hw_flow_ctrl = 0;
			sw_flow_ctrl = (tcflag_t) (IXON | IXOFF | IXANY);
			printf("SW Handshake\n");
			break;
			
		case NO_HANDSHAKE:
		default:
			hw_flow_ctrl = 0;
			sw_flow_ctrl = 0;
			printf("No Handshake\n");
			break;
	};
	
	// Databits
	switch(serport_params.databits)
	{
		case FIVE_BITS:
			databits = CS5;
			printf("databits 5\n");
			break;
		case SIX_BITS:
			databits = CS6;
			printf("databits 6\n");
			break;
		case SEVEN_BITS:
			databits = CS7;
			printf("databits 7\n");
			break;
		case EIGHT_BITS:
		default:
			databits = CS8;
			printf("databits %d \n",CS8);
			break;
	};

	// Parity
	switch(serport_params.parity)
	{
		case ODD_PARITY: 
				parity_on = PARENB;
				parity   = PARODD;
				printf("Odd parity\n");
				break;
		case EVEN_PARITY: 
				parity_on = PARENB;
				parity   = 0;
				printf("Even parity\n");
				break;
		case NONE_PARITY: 
		default:
				parity_on = 0;
				parity   = 0;
				printf("None parity\n");
				break;
	};

	// stopbits
	switch(serport_params.stopbits)
	{
		case ONE:
		default:
			stopbits = 0;
			printf("One - def stopbits\n");
			break;
			
		case TWO:
			stopbits = CSTOPB;
			printf("Two stopbits\n");
			break;
	};
	
	baudrate = 	port_speed[serport_params.baudrate];

	dbg_log(INFORM,"%-20s : SerPort Param details :: BaudRate : %d FlowCtrl %d sw_flow_ctrl %d DataBits %d Parity %d StopBits %d\n",fun_name,baudrate,hw_flow_ctrl,sw_flow_ctrl,databits,parity,stopbits);

	struct termios		set_termios;
	
	memset((void *)&set_termios, 0, sizeof(struct termios));
	
	dbg_log(INFORM,"%-20s : Opening Comm Uart Port : %s\n",fun_name,serport_params.ser_port);
	if ( (meter_comm_params->fd = open(serport_params.ser_port, O_RDWR | O_NOCTTY)) == -1)
	{
		dbg_log(FATAL,"%-20s : Serial port open() failed - %s: %s\n",fun_name,serport_params.ser_port, strerror(errno));
		return RET_PORT_OPEN_FAIL;
	}

	// CREAD - enable receiver, CLOCAL - ignore modem ctrl lines
    set_termios.c_cflag = baudrate | hw_flow_ctrl | databits | stopbits | parity | parity_on | CLOCAL | CREAD;

	if (parity_on > 0) // Parity checking to be done
		set_termios.c_iflag = (tcflag_t) (INPCK);
	else
		set_termios.c_iflag = IGNPAR;

	// Enable software flow control, if set
	set_termios.c_iflag |= sw_flow_ctrl;
	set_termios.c_oflag = 0;

    // set input mode (non-canonical, no echo,...) 
	set_termios.c_lflag = 0;
	//printf("cflag %x ciflag %x oflag %x lflag %x\n",set_termios.c_cflag,set_termios.c_iflag,set_termios.c_oflag,set_termios.c_lflag);

	(void)tcflush(meter_comm_params->fd, TCIFLUSH);
	int8_t ret_val;
	
	ret_val=tcsetattr(meter_comm_params->fd,TCSANOW,&set_termios);
	if ( ret_val == -1)
	{
		 dbg_log(FATAL,"%-25s : Serial port tcsetaddtr() failed - %s\n",fun_name,strerror(errno)); 
		return RET_PORT_OPEN_FAIL;
	}
	
	dbg_log(INFORM,"%-20s : RS232 - COmmunication Port UART Init End\n",fun_name);

	/* g_serial_fd = meter_comm_params->fd; */
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: write_ser_port()
*Input Parameters 			: Serial fd, buffer, buffer length
*Output Parameters 			: None
*Return	Value				: Success or appropriate error code.
*Description 				: Write buffer to serial port.
********************************************************************************************************/
int32_t write_ser_port(int32_t serial_fd, uint8_t *msg, int32_t len)
{
	static char fun_name[]="write_ser_port()";
	if(write(serial_fd, msg, len)<0)
	{
		dbg_log(FATAL,"%-25s : FD : %d, Serial write failed, Error : %s\n",fun_name,serial_fd,strerror(errno)); 
		return RET_SER_PORT_WRITE_FAIL;
	}
	
	return RET_SUCCESS;
}

/**************************************************************************************************
*Function 					: read_ser_port()
*Input Parameters 			: Serial fd, buffer, read timeout
*Output Parameters 			: Buffer
*Return	Value				: Total num bytes read or appropriate error code.
*Description 				: Read data from serial port.
********************************************************************************************************/
int32_t read_ser_port(int32_t serial_fd, uint8_t*trav, uint8_t time_out)
{
	static char fun_name[]="read_ser_port()";
	int32_t tot_byte_read=0, byte_present=0, loc_byte_read=0;
	int32_t wait_cnt=0,max_wait_cnt=0,break_cnt = 0;

	max_wait_cnt = (time_out*1000)/50;

	while ( wait_cnt < max_wait_cnt )
	{
		if(ioctl(serial_fd, FIONREAD, &byte_present) == -1)
		{
			dbg_log(FATAL,"%-25s : ioctl Failed : Error : %s\n",fun_name,strerror(errno)); 
			return RET_SER_PORT_READ_FAIL;
		}
	
		if(byte_present > 0)
			break;

		else if(byte_present == 0)
		{
			usleep(50000);
			wait_cnt++;
		}
	}

	if ( wait_cnt == max_wait_cnt )
	{
		//printf("Reched Max WaitCount : %d\n",max_wait_cnt);
		dbg_log(FATAL,"%-25s : Reached maxium wait time.\n",fun_name);
		return RET_SER_PORT_READ_FAIL;
	}

	//printf("Start Recv Data at  WaitCount : %d\n",wait_cnt);
	
	while(1)
	{
		memset(loc_buff, 0, sizeof(loc_buff));
		if((loc_byte_read = read(serial_fd, loc_buff, byte_present)) == -1)
		{
			dbg_log(FATAL,"%-25s : Serial read failed : Error : %s\n",fun_name,strerror(errno));
			
			return RET_SER_PORT_READ_FAIL;
		}

		//memcpy((void *)trav, loc_buff, loc_byte_read);
		//trav += loc_byte_read;
		
		memcpy((void *)&trav[tot_byte_read], loc_buff, loc_byte_read);
		tot_byte_read += loc_byte_read;
		
		//printf("Local Byte reads : %d, Total Bytes Read : %d\n",loc_byte_read,tot_byte_read);
		//printf("0. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
		
		byte_present = 0;
		if(ioctl(serial_fd, FIONREAD, &byte_present) == -1)
		{
			printf("11 read_ser_port ::: ioctl Failed : Error : %s\n",strerror(errno));
			return RET_SER_PORT_READ_FAIL;
		}

		if(byte_present > 0)
		{
			if(tot_byte_read == 1024)
				break;
			else 
				continue;
		}
		else if(byte_present == 0)
		{
			usleep(50000);
			break_cnt = 1;

			//printf("1. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
			while ( wait_cnt < max_wait_cnt )
			{
				if(tot_byte_read>=2)
				//if((break_cnt>=3)||(trav[tot_byte_read-1]==0X7E))
				//if((break_cnt>=3)&&(trav[tot_byte_read-1]==0X7E))
				if((trav[0]==0X7E)&&(trav[tot_byte_read-1]==0X7E))
				{
					//if(validate_met_resp(trav,tot_byte_read)==-1)
					if(validate_met_resp(trav,tot_byte_read)<0)
					{
						printf(">>>Inside Inner while recv partial data, need to read more tot_byte_read  : %d\n",tot_byte_read);
					}
					else
					{
						printf("Inside Inner while recv total data, breaking loop tot_byte_read  : %d\n",tot_byte_read);
						wait_cnt++;
						break;
					}
				}
				
				byte_present = 0;
				if(ioctl(serial_fd, FIONREAD,&byte_present) == -1)
				{
					dbg_log(FATAL,"%-25s : ioctl Failed : Error : %s\n",fun_name,strerror(errno));
					
					return RET_SER_PORT_READ_FAIL;
				}

				if(byte_present > 0)
				{
					//printf("Inside Inner while Some extra bytes aval to read. Breaking inner loop\n");
					wait_cnt++;
					break;
				}
				else
				{
					usleep(50000);
					wait_cnt++;
					break_cnt++;
					continue;
				}
			}
			
			if(tot_byte_read>=2)
			//if((break_cnt>=3)||(trav[tot_byte_read-1]==0X7E))
			//if((break_cnt>=3)&&(trav[tot_byte_read-1]==0X7E))
			//printf("2. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
		
			if((trav[0]==0X7E)&&(trav[tot_byte_read-1]==0X7E))
			{
				//if(validate_met_resp(trav,tot_byte_read)==-1)
				if(validate_met_resp(trav,tot_byte_read)<0)
				{
					printf("Inside Main while loop recv partial data, need to read more tot_byte_read  : %d\n",tot_byte_read);
				}
				else
				{
					printf("Inside Main while loop recv total data, breaking loop tot_byte_read  : %d\n",tot_byte_read);
					wait_cnt++;
					break;
				}
			}
			
			if ( wait_cnt >= max_wait_cnt )
			{
				//printf("Main while loop Reached Max Wait Cnt, breaking loop\n");
				//printf("3. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
				break;
			}
		}
	}
	
	//printf("End Recv Data at  WaitCount : %d, break_cnt : %d\n",wait_cnt,break_cnt);
	
	//printf("4. 1st byte read : %02X, Last Byte Read : %02X\n",trav[0],trav[tot_byte_read-1]);
	
	return tot_byte_read;
}

/* End of file */