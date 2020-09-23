CC = /home/ganesh/bin/arm-2011.09/bin/arm-none-linux-gnueabi-gcc
#CC= /home/preethi/opt/crosstool/gcc-3.3-glibc-2.2.5/arm-9tdmi-linux-gnu/bin/arm-9tdmi-linux-gnu-gcc
#CC = gcc
INCLUDE = -I../inc


OBJS =  dlms_api.o  dlms_fun.o  log.o gen_fun.o
TGTLIB = ../lib/dlms_api_lib.so

$(TGTLIB): $(OBJS)
	$(CC) -shared -fPIC -o $(TGTLIB) $(OBJS)
.c.o:
	$(CC) -c -fPIC $^ $(INCLUDE)
clean::
	rm $(OBJS) $(TGTLIB)
 







