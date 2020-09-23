#ifndef	__GEN_FUN_H__
#define	__GEN_FUN_H__

/* Include */
#include "dlms_api.h"



int8_t init_tcp_conn(meter_comm_params_t *meter_comm_params);
int8_t init_serial(meter_comm_params_t *meter_comm_params);
int32_t write_ser_port(int32_t serial_fd, uint8_t *msg, int32_t len);
int32_t read_ser_port(int32_t serial_fd, uint8_t*trav, uint8_t time_out);

#endif

/* End of file */