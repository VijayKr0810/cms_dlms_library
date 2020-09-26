/***********************************************************************
* Copyright (c) 2019 All Right Reserved
*
* Author:	Creative Micro Systems
* Contact:	support@cmsgp.com
* File: 	main.c
* Summary:  Iot gen md5 check sum proc.
*
**********************************************************************/

/*** Include ***/
#include "gen_inc.h"


/* Proto Type */
int32_t gen_signature(int32_t type);

/* Local Micro */
#define	FWFILE1					"../../cms_install_dir/cms_dcu_firmware.tar"
#define	FWFILE2					"../../cms_install_dir/bldStrswan.tar"
#define	FWFILE3					"../../cms_install_dir/lib.tar"
#define	FWFILE4					"../../cms_install_dir/newInstall.sh"

#define	TEMPFILE1				"Makefile"
#define	TEMPFILE2				"main.c"

/* Structures */

/* Globals */
char							fwFiles[5][64];
char							fwFilesMd5Sum[4][64];

int g_sign_cnt = 0;
int fileCnt = 0;

/* ============================================================================ */

/****************************************
*Function 		: main()
*Params 		: 
*Return			: 
*Description 	: Entry point of module
*****************************************/
int main( int argc, char *argv[] )
{
    static char fun_name[]="main()";
	int32_t ret;
	
	if ( argc < 2 )
	{
		printf("%-25s : Invalid arguments \n",fun_name);
		return -1;
	}
	
	int type = atoi(argv[1]);

	ret = gen_signature(type);

	if ( ret < 0 )
	{
		printf("%-25s : FAILED To generate SIGNATURES\n",fun_name);
		return -1;
	}

	printf("%-25s : Signatures generated\n",fun_name);	
	
	return 0;
}

int32_t gen_signature(int32_t type)
{
	static char fun_name[]="gen_signature()";
	char			file_check_sum[64];
	char 			temp_str[256];
	char 			line[128];
	char 			*p_file_cs_ptr = NULL;
	FILE 			*p_file_ptr,*p_file_ptr2;

	printf("%-25s : sign_cnt : %d\n",fun_name,g_sign_cnt);

	memset(temp_str,0,256);
	if ( type == 1 )
		sprintf(temp_str,"md5sum %s %s %s %s > sign.txt",FWFILE1,FWFILE2,FWFILE3,FWFILE4);
	else	
		sprintf(temp_str,"md5sum %s %s %s %s > sign.txt",FWFILE1,TEMPFILE1,TEMPFILE2,FWFILE4);

	printf("%-25s : temp_str : %s\n",fun_name,temp_str);

	system(temp_str);

	p_file_ptr = fopen("sign.txt","r");
	if ( p_file_ptr == NULL )
	{
		printf("%-25s : Failed find signature file\n",fun_name);
		return -1;
	}
	
	system("rm checksum");
	
	p_file_ptr2 = fopen("checksum","w+");
	if ( p_file_ptr2 == NULL )
	{
		printf("%-25s : Failed to open file for writing signatures, Error : %s\n",fun_name,strerror(errno));
		
		
		fclose(p_file_ptr);
		
		return -1;
	}
	
	memset(line,0,128);
	while ( fgets(line,128,p_file_ptr) != NULL )
	{
		printf("%-25s : LINE : %s strlen : %ld\n",fun_name,line,strlen(line));
		
		p_file_cs_ptr = strstr(line," ");
		if ( p_file_cs_ptr != NULL )
		{
			memset(file_check_sum,0,64);
			memcpy(file_check_sum,line,(p_file_cs_ptr-line));
			
			printf("%-25s : MD5Checksum is : %s\n",fun_name,file_check_sum);
			
			fprintf(p_file_ptr2,"%s\n",file_check_sum);
		}
		
		memset(line,0,128);
	}	

	fclose(p_file_ptr);
	fclose(p_file_ptr2);

	memset(temp_str,0,256);
	sprintf(temp_str,"cp checksum ../cms_dcu_firmware/checksum");
	
	system(temp_str);

	return 0;
}

/* End of File */

