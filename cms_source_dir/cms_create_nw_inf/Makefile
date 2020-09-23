CC = /home/ganesh/bin/arm-2011.09/bin/arm-none-linux-gnueabi-gcc -pthread

INCLUDE= -I.
LIBS= -ldl 
CFLAGS_TGT=  -DEMBED_TGT=1


OBJS= main.o

TARGET=cms_create_nw_inf

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIB_DIR) $(LIBS)

.c.o:
	$(CC) $(CFLAGS_TGT) -c $^ $(INCLUDE)
clean::
	rm $(OBJS) $(TARGET)
