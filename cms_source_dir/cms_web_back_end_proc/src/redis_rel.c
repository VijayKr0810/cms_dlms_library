#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/home/iot-gateway/hiredis/hiredis.h"
#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
#include "dlms_api.h"
#include "dlms_fun.h"

/* Extern  */
extern redisContext 			*p_redis_handler;
extern redisReply 				*p_redis_reply;


/* ================================================================== */
int32_t redis_init(char *hostname, uint16_t port)
{
	static char fun_name[]="redis_init()";
	
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	
	dbg_log(INFORM,"%-20s : Trying to connect on Redis Server : %s with port : %d\n",fun_name,hostname,port);
	
    p_redis_handler = redisConnectWithTimeout(hostname, port, timeout);
    if (p_redis_handler == NULL || p_redis_handler->err) 
	{
        if (p_redis_handler) 
		{
			dbg_log(INFORM,"%-20s : Connection error: %s\n",fun_name,p_redis_handler->errstr);
            
            redisFree(p_redis_handler);
        } 
		else 
		{
			dbg_log(INFORM,"%-20s : Connection error: can't allocate redis context\n",fun_name);
        }
    }
	
	dbg_log(INFORM,"%-20s : Connected on Redis Server : %s with port : %d\n",fun_name,hostname,port);
   
    freeReplyObject(p_redis_reply);
	
	return RET_SUCCESS;
}