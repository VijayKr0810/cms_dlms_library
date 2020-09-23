#ifndef	__GEN_FUN_H__
#define	__GEN_FUN_H__

/* Include */
#include "dlms_api.h"

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

int8_t init_tcp_conn(meter_comm_params_t *meter_comm_params);
int8_t init_serial(meter_comm_params_t *meter_comm_params);
int32_t write_ser_port(int32_t serial_fd, uint8_t *msg, int32_t len);
int32_t read_ser_port(int32_t serial_fd, uint8_t*trav, uint8_t time_out);

#endif

/* End of file */