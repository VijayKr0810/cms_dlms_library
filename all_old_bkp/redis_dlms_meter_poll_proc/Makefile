#CC = gcc
CC = /home/ganesh/bin/arm-2011.09/bin/arm-none-linux-gnueabi-gcc
CFLAGS	= -I. -Wall -Wno-unused-variable -DSAM9X
CFLAGS2 = -DEMBED_TGT=1
LFLAGS  = -lrt 
#-lhiredis
CMS_DLMS_API_LIB = -L. ./lib/dlms_api_lib.so
rm       = rm -Rf

OBJDIR   = ./obj
BINDIR   = ./bin

MAIN_SRC_DIR = ./src
MAIN_INC_DIR = -I./inc
MAIN_SRC  := $(wildcard $(MAIN_SRC_DIR)/*.c)
MAIN_INC := $(wildcard $(MAIN_INC_DIR)/*.h)
MAIN_OBJECTS  := $(MAIN_SRC:$(MAIN_SRC_DIR)/%.c=$(OBJDIR)/%.o)

REDIS_SRC_DIR = /home/iot-gateway/hiredis/
REDIS_INC_DIR = -I /home/iot-gateway/hiredis/
REDIS_SRC  := $(wildcard $(REDIS_SRC_DIR)/*.c)
REDIS_INC := $(wildcard $(REDIS_INC_DIR)/*.h)
REDIS_OBJECTS  := $(REDIS_SRC:$(REDIS_SRC_DIR)/%.c=$(OBJDIR)/%.o)

# MQTT_SRC_DIR = ./mqtt_lib
# MQTT_INC_DIR = -I./inc
# MQTT_SRC  := $(wildcard $(MQTT_SRC_DIR)/*.c)
# MQTT_INC := $(wildcard $(MQTT_INC)/*.h)
# MQTT_OBJECTS  := $(MQTT_SRC:$(MQTT_SRC_DIR)/%.c=$(OBJDIR)/%.o)

TARGET = dlms_redis_proc

$(BINDIR)/$(TARGET): $(MAIN_OBJECTS) $(REDIS_OBJECTS)
	@$(CC) -o  $@ $(LFLAGS) $(CMS_DLMS_API_LIB) $(MAIN_OBJECTS) $(REDIS_OBJECTS)
	@echo "Linking complete!"
	
$(MAIN_OBJECTS): $(OBJDIR)/%.o : $(MAIN_SRC_DIR)/%.c
	@$(CC) $(MAIN_INC_DIR) $(REDIS_INC_DIR) $(CFLAGS) -c $< -o $@
	@echo "Main Source Compiled "$<" successfully!"
	
$(REDIS_OBJECTS): $(OBJDIR)/%.o : $(REDIS_SRC_DIR)/%.c
	@$(CC) $(REDIS_INC_DIR) $(CFLAGS2) -c $< -o $@
	@echo "Redis Source Compiled "$<" successfully!"
	
.PHONEY: clean

clean:
	@$(rm) $(OBJDIR)/*.o
	@$(rm) $(BINDIR)/$(TARGET)
	@echo $(MAIN_OBJECTS) $(REDIS_OBJECTS)
	@echo "Cleanup complete!" 