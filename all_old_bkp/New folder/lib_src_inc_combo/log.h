#ifndef	__LOG_H__
#define	__LOG_H__

#include <stdint.h>
#define DEBUG_LOG 					0
#define RTU_DLMS					1
#define CMS_LOG_DIR "."
#define FILE_SIZE_EXCEED 			1*1024*1024

#define		INFORM				0
#define		WARNING				1
#define		SEVERE				2
#define		FATAL				3
#define		REPORT				4

int32_t dbg_log(uint8_t mode, const char *p_format, ...);
FILE* write_dbglog(FILE*p_dbg_fptr_arr, char*g_file_path, char *p_data);

#endif
/* End of file */
