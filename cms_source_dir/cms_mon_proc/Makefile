
#CC = gcc
CC = /home/ganesh/bin/arm-2011.09/bin/arm-none-linux-gnueabi-gcc
CFLAGS	= -I. -Wall -Wno-unused-variable -DSAM9X

LIBS= -lhiredis

CMS_COMMON_INC_DIR = -I ../cms_common_inc
CMS_LIB_INC_DIR = -I ../cms_dlms_api_library/inc
CMS_DLMS_API_LIB = ../lib/dlms_api_lib.so
REDIS_LIB_DIR	= -L/home/iot-gateway/redis-5.0.8-bin/lib

# linking flags here
LFLAGS   = -Wall -L. -lm -lpthread -lrt 
#-I /home/iot-gateway/hiredis/libhiredis

# change these to set the proper directories where each files should be
SRCDIR   = ./src
INCDIR1	 = -I home/iot-gateway/hiredis
INCDIR	 = -I -I/home/iot-gateway/redis-5.0.8-bin/include
OBJDIR   = ./obj
BINDIR   = .
LOC_INCDIR = -I ./inc

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -Rf

GEN_FUN_DIR = /home/iot-gateway/hiredis/
SOURCES2  := $(wildcard $(GEN_FUN_DIR)/*.c)
OBJECTS2  := $(SOURCES2:$(GEN_FUN_DIR)/%.c=$(OBJDIR)/%.o)

TARGET = cms_mon_proc
 
$(BINDIR)/$(TARGET): $(OBJECTS) 
	@$(CC) -o  $@ $(LFLAGS) $(OBJECTS) $(REDIS_LIB_DIR) $(LIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(INCDIR) $(CMS_COMMON_INC_DIR) $(LOC_INCDIR) $(CMS_LIB_INC_DIR) $(CFLAGS) $(REDIS_LIB_DIR) $(LIBS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJDIR)/*.o
	@$(rm) $(BINDIR)/$(TARGET)
	@echo $(OBJECTS) 
	@echo "Cleanup complete!"