/*
 * ntpclient.c - NTP client
 *
 * Copyright 1997, 1999, 2000  Larry Doolittle  <larry@doolittle.boa.org>
 * Last hack: 2 December, 2000
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License (Version 2,
 *  June 1991) as published by the Free Software Foundation.  At the
 *  time of writing, that license was published by the FSF with the URL
 *  http://www.gnu.org/copyleft/gpl.html, and is incorporated herein by
 *  reference.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  Possible future improvements:
 *      - Double check that the originate timestamp in the received packet
 *        corresponds to what we sent.
 *      - Verify that the return packet came from the host we think
 *        we're talking to.  Not necessarily useful since UDP packets
 *        are so easy to forge.
 *      - Complete phase locking code.
 *      - Write more documentation  :-(
 *
 *  Compile with -D_PRECISION_SIOCGSTAMP if your machine really has it.
 *  There are patches floating around to add this to Linux, but
 *  usually you only get an answer to the nearest jiffy.
 *  Hint for Linux hacker wannabes: look at the usage of get_fast_time()
 *  in net/core/dev.c, and its definition in kernel/time.c .
 *
 *  If the compile gives you any flak, check below in the section
 *  labelled "XXXX fixme - non-automatic build configuration".
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#ifdef _PRECISION_SIOCGSTAMP
#include <sys/ioctl.h>
#endif

#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
#include "/home/iot-gateway/hiredis/hiredis.h"

#define ENABLE_DEBUG
#define NTP_SECOND_SERVER 1

extern char *optarg;

/* XXXX fixme - non-automatic build configuration */
#ifdef linux
typedef u_int32_t __u32;
#include <sys/timex.h>
#else
extern int h_errno;
#define herror(hostname) \
	fprintf(stderr,"Error %d looking up hostname %s\n", h_errno,hostname)
typedef uint32_t __u32;
#endif

#define JAN_1970        0x83aa7e80      /* 2208988800 1970 - 1900 in seconds */
#define NTP_PORT (123)

/* How to multiply by 4294.967296 quickly (and not quite exactly)
 * without using floating point or greater than 32-bit integers.
 * If you want to fix the last 12 microseconds of error, add in
 * (2911*(x))>>28)
 */
#define NTPFRAC(x) ( 4294*(x) + ( (1981*(x))>>11 ) )

/* The reverse of the above, needed if we want to set our microsecond
 * clock (via settimeofday) based on the incoming time in NTP format.
 * Basically exact.
 */
#define USEC(x) ( ( (x) >> 12 ) - 759 * ( ( ( (x) >> 10 ) + 32768 ) >> 16 ) )

/* Converts NTP delay and dispersion, apparently in seconds scaled
 * by 65536, to microseconds.  RFC1305 states this time is in seconds,
 * doesn't mention the scaling.
 * Should somehow be the same as 1000000 * x / 65536
 */
#define sec2u(x) ( (x) * 15.2587890625 )

struct ntptime {
	unsigned int coarse;
	unsigned int fine;
};

void send_packet(int usd);
void rfc1305print(char *data, struct ntptime *arrival);
void udp_handle(int usd, char *data, int data_len, struct sockaddr *sa_source, int sa_len);

/* global variables (I know, bad form, but this is a short program) */
char incoming[1500];
struct timeval time_of_send;
int live=0;
int set_clock=0;   /* non-zero presumably needs root privs */
static	char						g_dbg_buff[256];

#ifdef ENABLE_DEBUG
int debug=0;
#define DEBUG_OPTION "d"
#else
#define debug 0
#define DEBUG_OPTION
#endif

#define	IST_TIME_ADJ	19800

//RTU_CONFIG		deviceConfig;//IEC_61850_CONV_CONFIG	pcCfg;
//DEVICE_CONFIG							deviceConfig;
unsigned int		iec61850SockFd=0;
struct sockaddr_in	iec61850Addr;
int contemplate_data(unsigned int absolute, double skew, double errorbar, int freq);


/* Structure */
dlms_dcu_config_t 				dlms_dcu_config;
redisContext 					*p_redis_handler;
redisReply 						*p_redis_reply;

/* Globals */
struct 	sockaddr_in					g_ntp_addr,g_status_addr;
int32_t 							g_addr_len = sizeof(g_ntp_addr);
int32_t 							g_ipc_sock_fd;
time_t 								g_last_hc_send_time;
char 								*p_ntp_ser_host;

time_t 								g_last_hc_send_time;
int get_current_freq()
{
//softel
#if 0
	/* OS dependent routine to get the current value of clock frequency.
	 */
#ifdef linux
	struct timex txc;
	txc.modes=0;
	if (__adjtimex(&txc) < 0) {
		perror("adjtimex"); exit(1);
	}
	return txc.freq;
#else
	return 0;
#endif
#endif
	return 0;
}

int set_freq(int new_freq)
{
	/* OS dependent routine to set a new value of clock frequency.
	 */
//softel
#if 0
#ifdef linux
	struct timex txc;
	txc.modes = ADJ_FREQUENCY;
	txc.freq = new_freq;
	if (__adjtimex(&txc) < 0) {
		perror("adjtimex"); exit(1);
	}
	return txc.freq;
#else
	return 0;
#endif
#endif
	return 0;
}

/* ----------------------------------------------------------------------------------------------- */
int32_t redis_init(char *hostname, uint16_t port)
{
	static char fun_name[]="redis_init()";
	
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	
	printf("%-20s : Trying to connect on Redis Server : %s with port : %d\n",fun_name,hostname,port);
	
    p_redis_handler = redisConnectWithTimeout(hostname, port, timeout);
    if (p_redis_handler == NULL || p_redis_handler->err) 
	{
        if (p_redis_handler) 
		{
			printf("%-20s : Connection error: %s\n",fun_name,p_redis_handler->errstr);
            
            redisFree(p_redis_handler);
        } 
		else 
		{
			printf("%-20s : Connection error: can't allocate redis context\n",fun_name);
        }
    }
	
	printf("%-20s : Connected on Redis Server : %s with port : %d\n",fun_name,hostname,port);
 
	return 0;
}

/*********************************************************************
	*Function 		: write_hc_on_redis()
	*In Params 		: void .
	*Output 		: None
	*Return			: status.
	*Description 	: This function is used to write hc message on redis  .
**********************************************************************/

int32_t write_hc_on_redis()
{
	time_t curr_time;
	curr_time=time(NULL);
	
	if ((curr_time-g_last_hc_send_time)>45)
	{
		p_redis_reply = redisCommand(p_redis_handler,"hmset ntp_hc_msg updatetime %d",curr_time);
		freeReplyObject(p_redis_reply);
		g_last_hc_send_time=time(NULL);
	}
	
	return 0;
}

void send_packet(int usd)
{
	__u32 data[12];
	struct timeval now;
#define LI 0
#define VN 3
#define MODE 3
#define STRATUM 0
#define POLL 4 
#define PREC -6

	if (debug) fprintf(stderr,"Sending ...\n");
	if (sizeof(data) != 48) {
		fprintf(stderr,"size error\n");
		return;
	}
	bzero(data,sizeof(data));
	data[0] = htonl (
		( LI << 30 ) | ( VN << 27 ) | ( MODE << 24 ) |
		( STRATUM << 16) | ( POLL << 8 ) | ( PREC & 0xff ) );
	data[1] = htonl(1<<16);  /* Root Delay (seconds) */
	data[2] = htonl(1<<16);  /* Root Dispersion (seconds) */
	gettimeofday(&now,NULL);
	data[10] = htonl(now.tv_sec + JAN_1970); /* Transmit Timestamp coarse */
	data[11] = htonl(NTPFRAC(now.tv_usec));  /* Transmit Timestamp fine   */
	send(usd,data,48,0);
	time_of_send=now;
}


void udp_handle(int usd, char *data, int data_len, struct sockaddr *sa_source, int sa_len)
{
	struct timeval udp_arrival;
	struct ntptime udp_arrival_ntp;

#ifdef _PRECISION_SIOCGSTAMP
	if ( ioctl(usd, SIOCGSTAMP, &udp_arrival) < 0 ) {
		perror("ioctl-SIOCGSTAMP");
		gettimeofday(&udp_arrival,NULL);
	}
#else
	gettimeofday(&udp_arrival,NULL);
#endif
	udp_arrival_ntp.coarse = udp_arrival.tv_sec + JAN_1970;
	udp_arrival_ntp.fine   = NTPFRAC(udp_arrival.tv_usec);

	if (debug) {
		struct sockaddr_in *sa_in=(struct sockaddr_in *)sa_source;
		printf("packet of length %d received\n",data_len);
		if (sa_source->sa_family==AF_INET) {
			printf("Source: INET Port %d host %s\n",
				ntohs(sa_in->sin_port),inet_ntoa(sa_in->sin_addr));
		} else {
			printf("Source: Address family %d\n",sa_source->sa_family);
		}
	}
	rfc1305print(data,&udp_arrival_ntp);
}

double ntpdiff( struct ntptime *start, struct ntptime *stop)
{
	int a;
	unsigned int b;
	a = stop->coarse - start->coarse;
	if (stop->fine >= start->fine) {
		b = stop->fine - start->fine;
	} else {
		b = start->fine - stop->fine;
		b = ~b;
		a -= 1;
	}
	
	return a*1.e6 + b * (1.e6/4294967296.0);
}

void rfc1305print(char *data, struct ntptime *arrival)
{
/* straight out of RFC-1305 Appendix A */
	int li, vn, mode, stratum, poll, prec;
	int delay, disp, refid;
	struct ntptime reftime, orgtime, rectime, xmttime;
	double etime,stime,skew1,skew2;
	int freq;

#define Data(i) ntohl(((unsigned int *)data)[i])
	li      = Data(0) >> 30 & 0x03;
	vn      = Data(0) >> 27 & 0x07;
	mode    = Data(0) >> 24 & 0x07;
	stratum = Data(0) >> 16 & 0xff;
	poll    = Data(0) >>  8 & 0xff;
	prec    = Data(0)       & 0xff;
	if (prec & 0x80) prec|=0xffffff00;
	delay   = Data(1);
	disp    = Data(2);
	refid   = Data(3);
	reftime.coarse = Data(4);
	reftime.fine   = Data(5);
	orgtime.coarse = Data(6);
	orgtime.fine   = Data(7);
	rectime.coarse = Data(8);
	rectime.fine   = Data(9);
	xmttime.coarse = Data(10);
	xmttime.fine   = Data(11);
#undef Data

	if (set_clock) {   /* you'd better be root, or ntpclient will crash! */
		struct timeval tv_set;
		/* it would be even better to subtract half the slop */
		//tv_set.tv_sec  = xmttime.coarse - JAN_1970;
		tv_set.tv_sec  = xmttime.coarse - JAN_1970;
		printf("Before adjustment sec %ld\n",tv_set.tv_sec);

		tv_set.tv_sec += IST_TIME_ADJ;//pcCfg.genInfo.timeAdj;

//		printf("After adjustment sec %d\n",tv_set.tv_sec);

		/* divide xmttime.fine by 4294.967296 */
		tv_set.tv_usec = USEC(xmttime.fine);
		if (settimeofday(&tv_set,NULL)<0) {
			perror("settimeofday");
			exit(1);
		}
		system("hwclock -w");
		system("hwclock;date");
		printf("set time to %lu.%.6lu\n", tv_set.tv_sec, tv_set.tv_usec);
		if (debug) {
			printf("set time to %lu.%.6lu\n", tv_set.tv_sec, tv_set.tv_usec);
		}
	}

	if (debug) 
	{
		printf("LI=%d  VN=%d  Mode=%d  Stratum=%d  Poll=%d  Precision=%d\n",li, vn, mode, stratum, poll, prec);
		printf("Delay=%.1f  Dispersion=%.1f  Refid=%d.%d.%d.%d\n",sec2u(delay),sec2u(disp),refid>>24&0xff, refid>>16&0xff, refid>>8&0xff, refid&0xff);
		printf("Reference %u.%.10u\n", reftime.coarse, reftime.fine);
		printf("Originate %u.%.10u\n", orgtime.coarse, orgtime.fine);
		printf("Receive   %u.%.10u\n", rectime.coarse, rectime.fine);
		printf("Transmit  %u.%.10u\n", xmttime.coarse, xmttime.fine);
		printf("Our recv  %u.%.10u\n", arrival->coarse, arrival->fine);
	}
	etime=ntpdiff(&orgtime,arrival);
	stime=ntpdiff(&rectime,&xmttime);
	skew1=ntpdiff(&orgtime,&rectime);
	skew2=ntpdiff(&xmttime,arrival);
	freq=get_current_freq();
	if (debug) 
	{
		printf("Total elapsed: %9.2f\n""Server stall:  %9.2f\n""Slop:%9.2f\n",etime, stime, etime-stime);
		//printf("Skew:%9.2f\n""Frequency:%9d\n"" day second     elapsed    stall     skew  dispersion  freq\n",(skew1-skew2)/2, freq);
	}
	printf("%u %5u.%.3u  %8.1f %8.1f  %8.1f %8.1f %9d\n",
		arrival->coarse/86400+15020, arrival->coarse%86400,
		arrival->fine/4294967, etime, stime,
		(skew1-skew2)/2, sec2u(disp), freq);
	fflush(stdout);
	if (live) 
	{
		/* int new_freq;
		new_freq = contemplate_data(arrival->coarse, (skew1-skew2)/2,etime+sec2u(disp), freq);
		if (!debug && new_freq != freq) 
			set_freq(new_freq); */
	}
}

int stuff_net_addr(struct in_addr *p, char *hostname)
{
	struct hostent *ntpserver;
	ntpserver=gethostbyname(hostname);
	if (ntpserver == NULL) {
		herror(hostname);
		//exit(1);
		return -1;
	}
	if (ntpserver->h_length != 4) {
		fprintf(stderr,"oops %d\n",ntpserver->h_length);
//		exit(1);
		return -1;
	}
	memcpy(&(p->s_addr),ntpserver->h_addr_list[0],4);
	return 0;
}

void setup_receive(int usd, unsigned int interface, short port)
{
	struct sockaddr_in sa_rcvr;
	bzero((char *) &sa_rcvr, sizeof(sa_rcvr));
	sa_rcvr.sin_family=AF_INET;
	sa_rcvr.sin_addr.s_addr=htonl(interface);
	sa_rcvr.sin_port=htons(port);
	if(bind(usd,(struct sockaddr *) &sa_rcvr,sizeof(sa_rcvr)) == -1) {
		fprintf(stderr,"could not bind to udp port %d\n",port);
		perror("bind");
		exit(1);
	}
	listen(usd,3);
}

int setup_transmit(int usd, char *host, short port)
{
	static int fail_cnt = 0;
	int ret = 0;
	struct sockaddr_in sa_dest;
	
	bzero((char *) &sa_dest, sizeof(sa_dest));
	sa_dest.sin_family=AF_INET;
	
	ret = stuff_net_addr(&(sa_dest.sin_addr),host);
	if ( ret < 0 )
	{
		fail_cnt++;
		if ( fail_cnt > 10 )
		{
			printf(" FAILED TO CONNECT TO THE NTP SERVER \n");
			//send_diag_info(0,"FAILED TO CONNECT TO THE NTP SERVER : %s",host);
			
		//exit(1);
			return -1;
		}
	}
	
	sa_dest.sin_port=htons(port);
	if (connect(usd,(struct sockaddr *)&sa_dest,sizeof(sa_dest))==-1)
	{
		perror("connect");
		fail_cnt++;
		if ( fail_cnt > 10 )
		{
			printf(" FAILED TO CONNECT TO THE NTP SERVER \n");
			//send_diag_info(0,"FAILED TO CONNECT TO THE NTP SERVER : %s",host);
		//exit(1);
			return -1;
		}
	}
	
	fail_cnt = 0;

	return 0;
}

void primary_loop(int usd, int num_probes, int interval)
{
	fd_set fds;
	struct sockaddr sa_xmit;
	int pack_len, probes_sent;
	struct timeval to;

	probes_sent=0;
	
	socklen_t sa_xmit_len=sizeof(sa_xmit);
	
	to.tv_sec=0;
	to.tv_usec=0;
	
	for (;;) 
	{
		FD_ZERO(&fds);
		FD_SET(usd,&fds);
		
		int i;
		i=select(usd+1,&fds,NULL,NULL,&to);  /* Wait on read or error */
		if ((i!=1)||(!FD_ISSET(usd,&fds))) 
		{
			if (i==EINTR) 
				continue;
			
			if (i<0) 
				perror("select");
			
			if (to.tv_sec == 0) 
			{
				if (probes_sent >= num_probes &&num_probes != 0) 
					break;
				
				printf("Sent request\n");
				
				send_packet(usd);
				
				++probes_sent;

				if ( probes_sent > 4 )
				{
					printf("No response received...... probes sent %d\n",probes_sent);
					
					//send_diag_info(0,"No response recv from Ntp server : %s",p_ntp_ser_host);
					
					return;
				}
				
				printf("Interval %d\n",interval);
				
				to.tv_sec=interval;
				to.tv_usec=0;
			}	
			continue;
		}
		
		pack_len=recvfrom(usd,incoming,sizeof(incoming),0,&sa_xmit,&sa_xmit_len);
		if (pack_len<0) 
		{
			printf("Error in Recv data, : %s\n",strerror(errno));
		}
		else if (pack_len>0 && pack_len<sizeof(incoming))
		{
			udp_handle(usd,incoming,pack_len,&sa_xmit,sa_xmit_len);
			
			printf("Got the response\n");
			
			//send_diag_info(0,"Got the response from Ntp server : %s",p_ntp_ser_host);
			
			probes_sent--;
		} 
		else 
		{
			printf("Ooops.  pack_len=%d\n",pack_len);
			fflush(stdout);
		}
		
		printf("Num probes %d probes sent %d\n",num_probes,probes_sent);
		
		if (probes_sent >= num_probes && num_probes != 0)
			break;
	}
}
#if 0
void do_replay(void)
{
	char line[100];
	int day, freq, absolute;
	float sec, etime, stime, disp;
	double skew, errorbar;
	int simulated_freq = 0;
	unsigned int last_fake_time = 0;
	double fake_delta_time = 0.0;

	while (fgets(line,sizeof(line),stdin)) 
	{
		int n;
		n=sscanf(line,"%d %f %f %f %lf %f %d",&day, &sec, &etime, &stime, &skew, &disp, &freq);
		
		if (n==7) 
		{
			fputs(line,stdout);
			absolute=(day-15020)*86400+(int)sec;
			errorbar=etime+disp;
			if (debug) printf("contemplate %d %.1f %.1f %d\n",
				absolute,skew,errorbar,freq);
				
			if (last_fake_time==0) 
				simulated_freq=freq;
			
			fake_delta_time += (absolute-last_fake_time)*((double)(freq-simulated_freq))/65536;
			
			if (debug) 
				printf("fake %f %d \n", fake_delta_time, simulated_freq);
			
			skew += fake_delta_time;
			freq = simulated_freq;
			
			last_fake_time=absolute;
			simulated_freq = contemplate_data(absolute, skew, errorbar, freq);
		} 
		else 
		{
			fprintf(stderr,"Replay input error\n");
			exit(2);
		}
	}
}

#endif

void usage(char *argv0)
{
	fprintf(stderr,
	"Usage: %s [-c count] [-d] -h hostname [-i interval] [-l]\n"
	"\t[-p port] [-r] [-s] \n",
	argv0);
}

int32_t read_cfg_from_redis(void)
{
	memset(&dlms_dcu_config,0,sizeof(dlms_dcu_config_t));
	
	p_redis_reply = redisCommand(p_redis_handler,"hmget NTP_INFO Ntp1Enable Ntp2Enable Ntp1Port Ntp2Port Interval Ntp1IpAddr Ntp2IpAddr");
	
	if(p_redis_reply!=NULL)
	{
		if(p_redis_reply->element[0]->str!=NULL)
		{
			dlms_dcu_config.ntp_cfg.enable_ntp1=atoi(p_redis_reply->element[0]->str);
		}
		else 
			return -1;
		
		if(p_redis_reply->element[1]->str!=NULL)
		{
			dlms_dcu_config.ntp_cfg.enable_ntp2=atoi(p_redis_reply->element[1]->str);
		}
		else 
			return -1;
		
		if(p_redis_reply->element[2]->str!=NULL)
		{
			dlms_dcu_config.ntp_cfg.ntp1_port=atoi(p_redis_reply->element[2]->str);
		}
		else 
			return -1;
		
		if(p_redis_reply->element[3]->str!=NULL)
		{
			dlms_dcu_config.ntp_cfg.ntp2_port=atoi(p_redis_reply->element[3]->str);
		}
		else 
			return -1;
		
		if(p_redis_reply->element[4]->str!=NULL)
		{
			dlms_dcu_config.ntp_cfg.interval=atoi(p_redis_reply->element[4]->str);
		}
		else 
			return -1;
		
		if(p_redis_reply->element[5]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ntp_cfg.ntp1_ip_addr,p_redis_reply->element[5]->str);
		}
		else 
			return -1;
		
		if(p_redis_reply->element[6]->str!=NULL)
		{
			strcpy(dlms_dcu_config.ntp_cfg.ntp2_ip_addr,p_redis_reply->element[6]->str);
		}
		else 
			return -1;
		
		freeReplyObject(p_redis_reply);
	}
	
	return 0;
}

int main(int argc, char *argv[]) 
{
	static char fun_name[]="main()";
	
	int usd;  /* socket */
	
	/* These parameters are settable from the command line
	   the initializations here provide default behavior */
	   
	short int udp_local_port=0;   /* default of 0 means kernel chooses */
	int cycle_time=600;           /* seconds */
	int probe_count=0;            /* default of 0 means loop forever */
	char *hostname=NULL;          /* must be set */
	char *altHostname=NULL;
	char *tempHostname=NULL;
	int replay=0;                 /* replay mode overrides everything */
	int ntpPort,altPort,tempPort;

	for (;;) 
	{
		int c;
		c = getopt( argc, argv, "c:" DEBUG_OPTION "h:i:lp:rs");
		if (c == EOF) break;
		switch (c) {
			case 'c':
				probe_count = atoi(optarg);
				break;
#ifdef ENABLE_DEBUG
			case 'd':
				++debug;
				break;
#endif
			case 'h':
				hostname = optarg;
				break;
			case 'i':
				cycle_time = atoi(optarg);
				break;
			case 'l':
				live++;
				break;
			case 'p':
				udp_local_port = atoi(optarg);
				break;
			case 'r':
				replay++;
				break;
			case 's':
				set_clock++;
				//probe_count = 1;
				cycle_time = 10;
				break;
			default:
				usage(argv[0]);
				exit(1);
		}
	}

	if(redis_init("127.0.0.1",6379)!=0)
	{
		printf("%-20s : Failed to initilised Redis Server\n",fun_name);
		return -1;
	}

	if(read_cfg_from_redis()<0)
	{
		printf("%-20s : Failed to read basic cfg from redis\n",fun_name);
		return -1;
	}
	
	hostname = dlms_dcu_config.ntp_cfg.ntp1_ip_addr;
	ntpPort = dlms_dcu_config.ntp_cfg.ntp1_port;
	//hostname = "192.168.10.15";

#ifdef NTP_SECOND_SERVER
	if (( dlms_dcu_config.ntp_cfg.enable_ntp1 == 1 ) && ( dlms_dcu_config.ntp_cfg.enable_ntp2 == 1 ))
	{
		hostname = dlms_dcu_config.ntp_cfg.ntp1_ip_addr;
		ntpPort = dlms_dcu_config.ntp_cfg.ntp1_port;
		
		altHostname = dlms_dcu_config.ntp_cfg.ntp1_ip_addr;
		altPort = dlms_dcu_config.ntp_cfg.ntp2_port;
	}
	else if ( dlms_dcu_config.ntp_cfg.enable_ntp1 == 1 )
	{
		hostname = dlms_dcu_config.ntp_cfg.ntp1_ip_addr;
		ntpPort = dlms_dcu_config.ntp_cfg.ntp1_port;
	}
	else if ( dlms_dcu_config.ntp_cfg.enable_ntp2 == 1 )
	{
		hostname = dlms_dcu_config.ntp_cfg.ntp2_ip_addr;
		ntpPort = dlms_dcu_config.ntp_cfg.ntp2_port;
	}
#endif

	cycle_time = dlms_dcu_config.ntp_cfg.interval;

	set_clock++;

	if (replay) 
	{
		//do_replay();
		exit(0);
	}
	
	if (hostname == NULL) 
	{
		usage(argv[0]);
		exit(1);
	}
	
	if (debug) 
	{
		printf("Configuration:\n"
		"  -c probe_count %d\n"
		"  -d (debug)     %d\n"
		"  -h hostname    %s\n"
		"  -i interval    %d\n"
		"  -l live        %d\n"
		"  -p local_port  %d\n"
		"  -s set_clock   %d\n",
		probe_count, debug, hostname, cycle_time,
		live, udp_local_port, set_clock );
	}

	/* Startup sequence */
	if ((usd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1)
		{perror ("socket");exit(1);}

	printf("Setup receive\n");
	setup_receive(usd, INADDR_ANY, udp_local_port);

	printf("Setup tx\n");

	while ( 1 )
	{
		int ret;
		p_ntp_ser_host = hostname;
		
		ret =	setup_transmit(usd, hostname, ntpPort);
		if ( ret < 0 )
		{
			printf("setup_transmit failed\n");

			sleep(5);

#ifdef	NTP_SECOND_SERVER

			if (( dlms_dcu_config.ntp_cfg.enable_ntp1 == 1 ) && ( dlms_dcu_config.ntp_cfg.enable_ntp2 == 1 ))
			{
				tempPort = ntpPort;
				tempHostname = hostname;
				hostname = altHostname;
				ntpPort = altPort;
				altHostname = tempHostname;
				altPort = tempPort;
				
				printf("TempHostname %s hostname %s altHostname %s\n",tempHostname,hostname,altHostname);			
			}
#endif
			continue;
		}
	//setup_transmit(usd, hostname, dlms_dcu_config.ntp_cfg.ntp1_port);

		printf("Main loop %s\n",hostname);
		
		//send_diag_info(0,"trying to connect Ntp server : %s",p_ntp_ser_host);
		
		primary_loop(usd, probe_count, cycle_time);

#ifdef	NTP_SECOND_SERVER

		if (( dlms_dcu_config.ntp_cfg.enable_ntp1 == 1 ) && ( dlms_dcu_config.ntp_cfg.enable_ntp2 == 1 ))
		{
			tempPort = ntpPort;
			tempHostname = hostname;
			hostname = altHostname;
			ntpPort = altPort;
			altHostname = tempHostname;
			altPort = tempPort;
			printf("*** TempHostname %s hostname %s altHostname %s\n",tempHostname,hostname,altHostname);			
		}
#endif
//		tempHostname = hostname;
//		hostname = altHostname;
//		altHostname = tempHostname;

//		printf("TempHostname %s hostname %s altHostname %s\n",tempHostname,hostname,altHostname);			
		sleep(5);
	}
	
	close(usd);
	
	return 0;
}

#if 0
int readConfigFile()
{
	int cfgFd,i,j;
	int numBytes=0,numMasters=0,numSlaves=0;
//	RTU_CG_GEN_INFO			genInfo;
//	RTU_CG_MASTER_CHAN_INFO tmpMastChanInfo;
	static char fn[] = "readConfigFile()";

	printf("In read config file\n");
	memset(&deviceConfig,0,sizeof(deviceConfig));

	if ( ( cfgFd = open(DEVICE_CFG_FILE,O_RDONLY )) < 0 )
	{
		printf("%s:%d:%s: Unable to open %s config file. error = %s Exiting..\n", 
		 				__FILE__, __LINE__, fn, DEVICE_CFG_FILE,strerror(errno));
		return -1;
	}
	
	//printf("Read 1\n");
	
	if ( ( numBytes = read(cfgFd,&deviceConfig,sizeof(DEVICE_CONFIG))) < sizeof(DEVICE_CONFIG) )
	{
		printf("%s:%d:%s: Failed to read PC_CFG %s file error = %s Exiting..\n",
		 				__FILE__, __LINE__, fn, DEVICE_CFG_FILE,strerror(errno));
		return -1;

	}
	printf("Config File Read\n");

	close(cfgFd);


	//printConfigFile();
	return 0;	
}

#endif
//create udp socket to communicate with 61850 server

#if 0
int createSockFor61850()
{

	if( (iec61850SockFd=socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("%s:%d: socket call failed - %s\n", 
		                    __FILE__, __LINE__, strerror(errno));
		return -1;
	}
	memset((void *)&iec61850Addr, 0, sizeof(struct sockaddr_in));
	iec61850Addr.sin_family		= AF_INET;
	iec61850Addr.sin_addr.s_addr  	= inet_addr(LOOP_BACK_ADDR);
	iec61850Addr.sin_port 		= htons(IPC_61850_PROC_BIND_PORT);
}
//send the msg to 61850 server 
int sendMsgTo61850()
{
	int 				addrLen=0, numBytesSent=0;
	IPC_DATA_INFO			ipcDataInfo;
	static char			fn[]="sendMsgTo61850()";

	memset(&ipcDataInfo,0,sizeof(ipcDataInfo));
	ipcDataInfo.procId = NTPCLIENT_PROC_ID;

	addrLen = sizeof(struct sockaddr_in);

	numBytesSent = sendto (iec61850SockFd, (void *)&ipcDataInfo, sizeof(ipcDataInfo), 0,
					(struct sockaddr *)&iec61850Addr, addrLen);

	if(numBytesSent < 0)
	{
		printf("%s:%d:%s:  sendto call failed - %s\n", 
		                    __FILE__, __LINE__, fn, strerror(errno));
		return -1;
	}

	printf("Send msg to 61850\n");
	return 0;
}
#endif	

/* EOF */
