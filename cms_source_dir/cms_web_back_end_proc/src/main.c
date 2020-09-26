#include "gen_inc.h"
#include "log.h"
#include "dlms_api_config.h"
#include "dlms_api.h"
#include "dlms_fun.h"
#include "web_back_end.h"
#include "/home/iot-gateway/redis-5.0.8-bin/include/hiredis.h"
//#include "/home/iot-gateway/hiredis/hiredis.h"

#define WEB_BACK_END_LOG_FILE_NAME "cms_web_backend_proc.log"

uint16_t modbus_crc16(char *data,int32_t cnt);

/* Globals */
redisContext 			*p_redis_handler;
redisReply 				*p_redis_reply;

/* Structure */
dlms_dcu_config_t 		dlms_dcu_config;

char 					debug_file_name[64];

/* ------------------------------------------------------------------------------ */
int32_t read_cfg_from_redis(void)
{
	FILE *p_file_ptr=NULL;
	
	//printf("Sizeof cfg str : %d\n",sizeof(dlms_dcu_config_t));
	p_file_ptr=fopen("/usr/cms/config/dlms_api_config.cfg","r");
	
	if(p_file_ptr==NULL)
	{
		perror("fopen ");
		return -1;
	}
	
	memset(&dlms_dcu_config,0,sizeof(dlms_dcu_config_t));
	
	fread(&dlms_dcu_config,sizeof(dlms_dcu_config_t),1,p_file_ptr);
	
	fclose(p_file_ptr);
	
	if(dlms_dcu_config.start_flag==START_END_FLAG)
	{
		if(dlms_dcu_config.end_flag==START_END_FLAG)
		{
			if(dlms_dcu_config.crc==modbus_crc16((char*)&dlms_dcu_config,sizeof(dlms_dcu_config_t)-6))
			{
				printf("Start & End Flag and CRC Matched\n");
			}
			else
			{
				printf("Crc Not Matched\n");
				return -1;
			}
		}
		else
		{
			printf("End Flag Not Matched\n");
			return -1;
		}
	}
	else
	{
		printf("Start Flag Not Matched\n");
		return -1;
	}
	
	return 0;
}

void checkNUpdateData()
{
	
}

int main(int argc, char **argv)
{
	static char fun_name[]="main()";
	
	memset(debug_file_name,0,sizeof(debug_file_name));
	sprintf(debug_file_name,"%s/%s",LOG_DIR,WEB_BACK_END_LOG_FILE_NAME);
	
	if(redis_init("127.0.0.1",6379)!=RET_SUCCESS)
	{
		dbg_log(REPORT,"%-20s : Redis Client initialize failed\n",fun_name);
		return -1;
	}
	
	if(read_cfg_from_redis()!=RET_SUCCESS)
	{
		dbg_log(REPORT,"%-20s : To read config failed\n",fun_name);
		return -1;
	}
	
	gwsock_init(argc,argv);
	
	return RET_SUCCESS;
}