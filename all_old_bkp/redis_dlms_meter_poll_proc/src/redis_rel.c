/***********************************************************************
* Copyright (c) 2020 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	main.c
* Summary:  Redis and DLMS Module.
*
**********************************************************************/

/* Includes */
#include "gen_inc.h"
//#include "gen_fun.h"
#include "log.h"
//#include "dlms_fun.h"
#include "dlms_api.h"
#include "hiredis.h"

int32_t fill_def_config(meter_comm_params_t *meter_comm_params);

#define NAME_PLATE_INFO_KEY "name_plate_info"
#define INST_INFO_KEY 		"inst_info"
/* ---------------------------------------------------------- */

/* Global */
redisContext 	*p_redis_handler;
redisReply 		*p_redis_reply;

int32_t redis_init(char *hostname, uint16_t port)
{
	static char fun_name[]="redis_init()";
	
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	
	printf("Trying to connect on Redis Server : %s with port : %d\n",hostname,port);
    p_redis_handler = redisConnectWithTimeout(hostname, port, timeout);
    if (p_redis_handler == NULL || p_redis_handler->err) 
	{
        if (p_redis_handler) 
		{
            printf("Connection error: %s\n", p_redis_handler->errstr);
            redisFree(p_redis_handler);
        } 
		else 
		{
            printf("Connection error: can't allocate redis context\n");
        }
    }
	
	printf("Connected on Redis Server : %s with port : %d\n",hostname,port);
    
	/* PING server */
    p_redis_reply = redisCommand(p_redis_handler,"PING");
    printf("PING Status : %s\n", p_redis_reply->str);
	
    freeReplyObject(p_redis_reply);
	
	return RET_SUCCESS;
}

int32_t send_np_det_to_redis(obis_name_plate_info_t name_plate_info)
{
	printf("Updating Name plate info into redis server.\n");
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s stat %b",NAME_PLATE_INFO_KEY, &name_plate_info, sizeof(obis_name_plate_info_t));
	
	printf("Name Plate Info Saved status : %s\n", p_redis_reply->str);//that shows +OK
		
	freeReplyObject(p_redis_reply);
		
	return RET_SUCCESS;
}

int32_t send_inst_det_to_redis(inst_val_info_t	inst_data_val)
{
	printf("Updating Instantaneous info into redis server.\n");
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s stat %b",INST_INFO_KEY, &inst_data_val, sizeof(inst_val_info_t));
	
	printf("Inst Info Saved status : %s\n", p_redis_reply->str); //that shows +OK
		
	freeReplyObject(p_redis_reply);
		
	return RET_SUCCESS;
}

int32_t send_det_to_redis(char *msg, uint32_t len, char *key_name)
{
	printf("Updating info into redis server for key_name : %s\n",key_name);
	
	p_redis_reply = redisCommand(p_redis_handler, "HMSET %s stat %b",key_name, msg, len);
	
	printf("Info Saved status : %s\n", p_redis_reply->str); //that shows +OK
		
	freeReplyObject(p_redis_reply);
		
	return RET_SUCCESS;
}

//
/* End Of File */