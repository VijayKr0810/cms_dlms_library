#include <stdio.h>

#define EVENT_INFO_KEY1(x) {char buff[32]; sprintf(buff,"event_type_%d_key_info",x); return buff;}

char* EVENT_INFO_KEY(int x) 
{
	char buff[32]; 
	sprintf(buff,"event_type_%d_key_info",x); 
	printf("%s\n",buff);
	return buff;
}

void main(void)
{
	printf("Key Val : %s\n",EVENT_INFO_KEY(5));
}