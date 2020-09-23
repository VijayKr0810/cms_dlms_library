#ifndef	__GEN_INC_H__
#define	__GEN_INC_H__

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <pthread.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/errno.h>
#include <linux/serial.h>
#include <asm/ioctls.h>
#include <assert.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <netdb.h>
#include <stdint.h>
typedef enum
{
    SIZE_4=4,
	SIZE_8=8,
	SIZE_16=16,
	SIZE_32=32,
	SIZE_64=64,
	SIZE_128=128,
	SIZE_256=256,
	SIZE_512=512,
	SIZE_640=640,
	SIZE_1024=1024,
	SIZE_2048=2048,
	SIZE_6144=6144
}buffer_size_t;

#endif

/* End of file */
