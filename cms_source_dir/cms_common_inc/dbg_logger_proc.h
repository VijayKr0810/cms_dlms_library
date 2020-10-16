#ifndef	__DBG_LOGGER_PROC_H__
#define	__DBG_LOGGER_PROC_H__

#define RTUCG_104_SLAVE_PROC_ID                 0x03//0x01
#define RTUCG_MODBUS_MASTER_PROC_ID             0x02
#define RTUCG_RELAY_MASTER_PROC_ID              0x03
#define RTUCG_IOCARD_MASTER_PROC_ID             0x01//0x04
#define RTUCG_MONITOR_PROC_ID                   0X05
#define	RTUCG_CONN_MON_PROC_ID					0x07
#define	RTU_ANALOG_PROC_ID						0x08
#define	RTU_DIAG_PROC_ID						0x06
#define	RTU_DNP3_PROC_ID						0x09
#define RTUCG_MODTCP_SLAVE_PROC_ID              0x04//0x01
#define	RTUCG_RMS_PROC_ID						0x0C
#define	IEC61850_SERVER_PROC					0x0F
#define	NTPCLIENT_PROC							0x10


#define	DLMS_MASTER_PROC						0x12
#define	WEB_STATUS_PROC							0x13
#define	WEB_DIAG_PROC							0x14

#define	DBG_LOG_IPC_PORT				10100

typedef struct
{
	int proc_id;
	int msg_type;
	char	msg[256];
	
}dbg_log_msg_t;

struct 	sockaddr_in g_win_log_addr,g_loc_soc_addr;
int32_t g_addr_len = sizeof(g_win_log_addr);

int32_t create_ipc_socket(char *log_ip_addr, uint16_t loc_port)
{
	unsigned int on=1;
	int32_t win_sock_fd;
	
	/* create socket for sending dbglogs to window system */
	if( (win_sock_fd=socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("socket call failed - %s\n",strerror(errno));
		return -1;
	}
	
	(void)setsockopt(win_sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, (socklen_t)sizeof(on));
	
	memset((char *) &g_loc_soc_addr, 0, sizeof(g_loc_soc_addr));
	g_loc_soc_addr.sin_family = AF_INET;
	g_loc_soc_addr.sin_port = htons(loc_port);
	g_loc_soc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(win_sock_fd, (struct sockaddr *)&g_loc_soc_addr, sizeof(g_loc_soc_addr))==-1)
	{
		printf("Binding Error in Udp Socket : %s\n",strerror(errno));
		return -1;
	}
	
	memset((void *)&g_win_log_addr, 0, sizeof(struct sockaddr_in));
	g_win_log_addr.sin_family	 	= AF_INET;
	g_win_log_addr.sin_addr.s_addr  = inet_addr(log_ip_addr);
	g_win_log_addr.sin_port 		= htons(DBG_LOG_IPC_PORT);
	
	printf(">>>>>>Win Socket creation success Ip : %s, Port : %d, FD : %d\n",log_ip_addr,loc_port,win_sock_fd);
	
	return win_sock_fd;
}

int32_t send_dbglog_msg(int32_t win_sock_fd, char *msg ,int len)
{
	int addr_len=0, numBytesSent=0;
	
	addr_len = sizeof(struct sockaddr_in);

	numBytesSent = sendto (win_sock_fd, msg, len, 0,(struct sockaddr *)&g_win_log_addr, addr_len);

	if(numBytesSent < 0)
	{
		printf("Error in Windows dbglog send : %s\n",strerror(errno));
		return -1;
	}
	
	printf(">>>>Windows dbglog send success bytes : %d\n",numBytesSent);
	return 0;
}


#endif