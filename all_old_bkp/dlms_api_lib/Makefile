#CC = gcc
CC = /home/ganesh/bin/arm-2011.09/bin/arm-none-linux-gnueabi-gcc
CFLAGS	= -I. -Wall -Wno-unused-variable -DSAM9X

LFLAGS   = -Wall -L. -lm -lpthread -lrt 
CMS_DLMS_API_LIB = -L. ./lib/dlms_api_lib.so
INCS = -I./inc
# change these to set the proper directories where each files should be
SRCDIR   = .
OBJDIR   = ./obj
BINDIR   = ./bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS1 := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS  = test_lib.o
rm       = rm -Rf

TARGET=dlms_redis_api
 
$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CMS_DLMS_API_LIB)
	@echo "Linking complete!"

.c.o:
	$(CC) -c $^ $(INCS) $(LFLAGS)
	@echo "Compiled "$<" successfully!"
	
clean::
	rm $(OBJECTS) 
	rm $(TARGET)