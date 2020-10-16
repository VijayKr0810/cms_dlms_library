/* Includes */
#include "gen_inc.h"
#include "dlms_api_config.h"
#include <curl/curl.h>
#include "log.h"

/* Extern */
extern dlms_dcu_config_t 		dlms_dcu_config;

int create_dir(char *ip_addr,int port_no,char *uname,char *pwd,char *dir, char *local_file,char *rem_file);
/* ------------------------------------------------------ */
int32_t curl_init(uint8_t ser_type)
{
	if(ser_type==1)
	{
		return create_dir(dlms_dcu_config.ftp_ser_cfg.ser_ip,
					dlms_dcu_config.ftp_ser_cfg.ser_port,
					dlms_dcu_config.ftp_ser_cfg.username,
					dlms_dcu_config.ftp_ser_cfg.password,
					dlms_dcu_config.ftp_ser_cfg.loc_dir,
					"/usr/cms/log/cms_temp.log","temp_file");
	}
	else
	{
		return create_dir(dlms_dcu_config.ftp_ser_cfg.log_ser_ip,
					dlms_dcu_config.ftp_ser_cfg.log_ser_port,
					dlms_dcu_config.ftp_ser_cfg.log_username,
					dlms_dcu_config.ftp_ser_cfg.log_password,
					dlms_dcu_config.ftp_ser_cfg.log_loc_dir,
					"/usr/cms/log/cms_temp.log","temp_file");
	}
	
	return 0;
}

/* NOTE: if you want this example to work on Windows with libcurl as a
   DLL, you MUST also provide a read callback with CURLOPT_READFUNCTION.
   Failing to do so will give you a crash since a DLL may not use the
   variable's memory when passed in to it from an app like this. 
*/
   
static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
	static char fun_name[]="read_callback()";
	
	curl_off_t nread;
	
	/* in real-world cases, this would probably get this data differently
	as this fread() stuff is exactly what the library already would do
	by default internally */
	
	size_t retcode = fread(ptr, size, nmemb, stream);

	/* nread = (curl_off_t)retcode; */

	//dbg_log(INFORM,"%-20s : *** We read %" CURL_FORMAT_CURL_OFF_T" bytes from file\n",fun_name,nread);

	//fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T" bytes from file\n", nread);
	
	return retcode;
}

int32_t create_dir(char *ip_addr,int port_no,char *uname,char *pwd,char *dir, char *local_file,char *rem_file)
{
	static char fun_name[]="create_dir()";
	CURL *curl;
	CURLcode res;
	FILE *hd_src;
	struct stat file_info;
	curl_off_t fsize;
	char temp_str_buff[128];

	dbg_log(INFORM,"%-20s : ip %s port %d uname %s pwd %s dir %s\n",fun_name,ip_addr,port_no,uname,pwd,dir);

	struct curl_slist *headerlist=NULL;
	static char buf_1 [64];

	memset(buf_1,0,64);
	sprintf(buf_1,"DELE %s",rem_file);
	
	if(stat(local_file, &file_info)) 
	{
		dbg_log(INFORM,"%-20s : Couldnt open Local File : %s, Error : %s\n",fun_name,local_file, strerror(errno));

		dbg_log(INFORM,"%-20s : Failed to create remote directory : %s, reason : %s\n",fun_name,dir,strerror(errno));

		return 1;
	}

	dbg_log(INFORM,"%-20s : local file size : %ld Mode : %lo\n",fun_name,(long)file_info.st_size,file_info.st_mode);

	fsize = (curl_off_t)file_info.st_size;

	dbg_log(INFORM,"%-20s : Local file size : %d " CURL_FORMAT_CURL_OFF_T " bytes.\n",fun_name,fsize);

	/* get a FILE * of the same file */
	hd_src = fopen(local_file, "rb");
	
	/* get the file size of the local file */

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if(curl) 
	{
		/* build a list of commands to pass to libcurl */
		headerlist = curl_slist_append(headerlist, buf_1);
		//		headerlist = curl_slist_append(headerlist, buf_2);

		/* we want to use our own read function */
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

		/* enable uploading */
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

		/* specify target */
		memset(temp_str_buff,0,sizeof(temp_str_buff));
		sprintf(temp_str_buff,"ftp://%s/%s/%s",ip_addr,dir,rem_file);
		
		//curl_easy_setopt(curl, CURLOPT_URL, REMOTE_URL);
		curl_easy_setopt(curl, CURLOPT_URL, temp_str_buff);

		/* now specify which file to upload */
		curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);

		
		/* set user name and password for the authentication */ 
		memset(temp_str_buff,0,sizeof(temp_str_buff));
		sprintf(temp_str_buff,"%s:%s",uname,pwd);

		curl_easy_setopt(curl, CURLOPT_USERPWD, temp_str_buff);
		
		/* Switch on full protocol/debug output */
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		//change the port..
		curl_easy_setopt(curl,CURLOPT_PORT,port_no);
		
		//create dir
		curl_easy_setopt(curl,CURLOPT_FTP_CREATE_MISSING_DIRS,CURLFTP_CREATE_DIR_RETRY);

		/* Now run off and do what you've been told! */
		res = curl_easy_perform(curl);
		
		/* Check for errors */
		if(res != CURLE_OK)
		{
			dbg_log(REPORT,"%-20s : curl_easy_perform() failed : Error : %s\n",fun_name,curl_easy_strerror(res));
			
			fclose(hd_src); /* close the local file */
			
			curl_easy_cleanup(curl);
			curl_global_cleanup();

			return -1;
		}

		dbg_log(INFORM,"%-20s : ************* After creating file***************\n",fun_name);

		curl_easy_reset(curl);
		
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
		
		memset(temp_str_buff,0,sizeof(temp_str_buff));
		sprintf(temp_str_buff,"ftp://%s/%s/%s",ip_addr,dir,rem_file);
		curl_easy_setopt(curl, CURLOPT_URL, temp_str_buff);

		memset(temp_str_buff,0,sizeof(temp_str_buff));
		sprintf(temp_str_buff,"%s:%s",uname,pwd);
		curl_easy_setopt(curl, CURLOPT_USERPWD, temp_str_buff);
		
		/* Switch on full protocol/debug output */
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		
		/* pass in that last of FTP commands to run after the transfer */
		curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);
		res = curl_easy_perform(curl);

		/* clean up the FTP commands list */
		curl_easy_cleanup(curl);	
	}
	
	fclose(hd_src); /* close the local file */

	curl_global_cleanup();

	dbg_log(INFORM,"%-20s : Succesfully created remote directory : %s\n",fun_name,dir);

	return 0;
}

int32_t push_data_over_ftp_server(char *ipAddr,int portNo,char *uname,char *pwd,char *dir,char *filename,char *localfile)
{
	static char fun_name[]="push_ftp_data()";
	CURL *curl;
	CURLcode res;
	FILE *hd_src;
	struct stat file_info;
	curl_off_t fsize;
	char tmpStr[128];
	
	/* get the file size of the local file */
	//if(stat(LOCAL_FILE, &file_info)) {
	if(stat(localfile, &file_info)) 
	{
		dbg_log(INFORM,"%-20s : Couldnt open Local File : %s, Error : %s\n",fun_name,localfile, strerror(errno));

		dbg_log(INFORM,"%-20s : Failed to create remote directory : %s, reason : %s\n",fun_name,dir,strerror(errno));
		
		return 1;
	}

	/* fsize = (curl_off_t)file_info.st_size; */

	/* get a FILE * of the same file */
	hd_src = fopen(localfile, "rb");

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if(curl) 
	{
		/* we want to use our own read function */
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

		/* enable uploading */
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

		/* specify target */
		memset(tmpStr,0,sizeof(tmpStr));
		sprintf(tmpStr,"ftp://%s/%s/%s",ipAddr,dir,filename);
		//curl_easy_setopt(curl, CURLOPT_URL, REMOTE_URL);
		curl_easy_setopt(curl, CURLOPT_URL, tmpStr);

		/* pass in that last of FTP commands to run after the transfer */
		//curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);

		/* now specify which file to upload */
		curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
		

		/* set user name and password for the authentication */ 
		memset(tmpStr,0,sizeof(tmpStr));
		sprintf(tmpStr,"%s:%s",uname,pwd);
		curl_easy_setopt(curl, CURLOPT_USERPWD, tmpStr);
		
		/* Switch on full protocol/debug output */
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		//change the port..
		curl_easy_setopt(curl,CURLOPT_PORT,portNo);
		//create dir
		curl_easy_setopt(curl,CURLOPT_FTP_CREATE_MISSING_DIRS,CURLFTP_CREATE_DIR_RETRY);

		/* Now run off and do what you've been told! */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if(res != CURLE_OK)
		{
			dbg_log(REPORT,"%-20s : curl_easy_perform() failed :, Error : %s\n",fun_name,curl_easy_strerror(res));
			
			fclose(hd_src); /* close the local file */
			
			curl_easy_cleanup(curl);
			curl_global_cleanup();
			
			return -1;
		}

		/* clean up the FTP commands list */
		curl_easy_cleanup(curl);	
	}
	
	fclose(hd_src); /* close the local file */

	curl_global_cleanup();
	
	return 0;
}

int send_file_data(char *dir_name,char *parent_dir,char *file_name,char *ip_addr,int port_no,char *uname,char *pwd,char*loc_dir)
{
	static char fun_name[]="send_file_data()";
	uint8_t file_count=0;
	char loc_file_name[128],rem_dir[128];
	DIR *dp = NULL;
	struct dirent *p;
	struct stat v;

	//dbg_log(INFORM,"%-20s : DIR : %s parent dir : %s file_name : %s\n",fun_name,dir_name,parent_dir,file_name);

	stat(dir_name, &v);
	
	switch(v.st_mode & S_IFMT)
	{
		case S_IFREG:
		{
			file_count++;
			
			memset(rem_dir,0,sizeof(rem_dir));
			
			sprintf(rem_dir,"%s/%s",loc_dir,parent_dir);
			if ( strstr(file_name,"tgz") != NULL )
			{
				dbg_log(INFORM,"%-20s : No need to send tgz file !!!\n",fun_name);
			}
			else
			{
				dbg_log(INFORM,"%-20s : Trying to push ftp data to server : %s, Remote directory : %s\n",
				fun_name,ip_addr,rem_dir);
				
				push_data_over_ftp_server(ip_addr,port_no,uname,pwd,rem_dir,file_name,dir_name);
			}
		}

		break;
			
		case S_IFDIR:
		{
			//dbg_log(INFORM,"%-20s : Current DIR : %s\n",fun_name,dir_name);

			if ( dp != NULL )
				closedir(dp);

			if(strstr(dir_name,"upstream"))
			{
				dbg_log(INFORM,"%-20s : Upstream DIR : %s, No need to send over ftp\n",fun_name,dir_name);
				return 0;
			}
			dp=opendir(dir_name);

			if ( dp != NULL )
			{
				while((p=readdir(dp))!=NULL)
				{
					memset(loc_file_name,0,sizeof(loc_file_name));
					
					//strcpy(loc_file_name,p->d_name);
					if(strcmp(p->d_name,".")&&strcmp(p->d_name,"..")&&strcmp(p->d_name,"od"))
					{
						strcat(loc_file_name,dir_name);
						strcat(loc_file_name,"/");
						strcat(loc_file_name,p->d_name);
						
						send_file_data(loc_file_name,file_name,p->d_name,ip_addr,port_no,uname,pwd,loc_dir);
					}
				}
			}
			
			if ( dp != NULL )
				closedir(dp);
		}
		break;
	}
	
	return 0;
}

void send_dcu_log_data(void)
{
	send_file_data(LOG_DIR,NULL,NULL,dlms_dcu_config.ftp_ser_cfg.log_ser_ip,
	dlms_dcu_config.ftp_ser_cfg.log_ser_port,dlms_dcu_config.ftp_ser_cfg.log_username,
	dlms_dcu_config.ftp_ser_cfg.log_password,dlms_dcu_config.ftp_ser_cfg.log_loc_dir);
}

void send_meter_data(void)
{
	static char fun_name[]="send_meter_data()";
	
	dbg_log(INFORM,"%-20s : Sending Data Files to FTP Server !!!\n",fun_name);
	
	send_file_data(ROOT_DATA_DIR,NULL,NULL,dlms_dcu_config.ftp_ser_cfg.ser_ip,
	dlms_dcu_config.ftp_ser_cfg.ser_port,dlms_dcu_config.ftp_ser_cfg.username,
	dlms_dcu_config.ftp_ser_cfg.password,dlms_dcu_config.ftp_ser_cfg.loc_dir);
	
	if(dlms_dcu_config.ftp_ser_cfg.diff_log_ser!=1)
	{
		dbg_log(INFORM,"%-20s : Sending Log Files to FTP Server !!!\n",fun_name);
	
		send_file_data(LOG_DIR,NULL,"log",dlms_dcu_config.ftp_ser_cfg.ser_ip,
		dlms_dcu_config.ftp_ser_cfg.ser_port,dlms_dcu_config.ftp_ser_cfg.username,
		dlms_dcu_config.ftp_ser_cfg.password,dlms_dcu_config.ftp_ser_cfg.loc_dir);
		
		/* send_file_data("/var/log/messages",NULL,"log",dlms_dcu_config.ftp_ser_cfg.ser_ip,
		dlms_dcu_config.ftp_ser_cfg.ser_port,dlms_dcu_config.ftp_ser_cfg.username,
		dlms_dcu_config.ftp_ser_cfg.password,dlms_dcu_config.ftp_ser_cfg.loc_dir); */
		
		push_data_over_ftp_server(	dlms_dcu_config.ftp_ser_cfg.ser_ip,
									dlms_dcu_config.ftp_ser_cfg.ser_port,
									dlms_dcu_config.ftp_ser_cfg.username,
									dlms_dcu_config.ftp_ser_cfg.password,
		dlms_dcu_config.ftp_ser_cfg.loc_dir,"/var/log/messages","/var/log/messages");
		//int push_data_over_ftp_server(char *ipAddr,int portNo,char *uname,char *pwd,char *dir,char *filename,char *localfile)
	}
}

/* End Of File */