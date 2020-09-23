#ifndef	__LOG_H__
#define	__LOG_H__

#include <stdint.h>

#define DEBUG_LOG 					1
#define RTU_DLMS					1
#define CMS_LOG_DIR 				"/usr/cms/log"
#define FILE_SIZE_EXCEED 			1*1024*1024

#define		INFORM				0
#define		WARNING				1
#define		SEVERE				2
#define		FATAL				3
#define		REPORT				4

#define GW_FATAL(fmt, ...) do {                                                  \
  fprintf (stderr, "\nFatal error has occurred");                             \
  fprintf (stderr, "\nError occured at: %s - %s - %d\n", __FILE__,            \
           __FUNCTION__, __LINE__);                                           \
  fprintf (stderr, fmt, ##__VA_ARGS__);                                       \
  fprintf (stderr, "\n\n");                                                   \
  exit(EXIT_FAILURE);                                                         \
} while (0)

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define LOG(x) do { if (DEBUG_TEST) dbg_printf x; } while (0)
//#define LOG(x) do { if (1) dbg_printf x; } while (0)
	
/* access requests log */
#define ACCESS_LOG(x, ...) do { access_fprintf x; } while (0)

int access_log_open (const char *path);
void access_fprintf (const char *fmt, ...);
void access_log_close (void);
void dbg_printf (const char *fmt, ...);

int32_t dbg_log(uint8_t mode, const char *p_format, ...);
FILE* write_dbglog(FILE*p_dbg_fptr_arr, char*g_file_path, char *p_data);


#endif
/* End of file */