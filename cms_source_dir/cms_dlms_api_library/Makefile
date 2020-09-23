#CC = gcc
CC = /home/ganesh/bin/arm-2011.09/bin/arm-none-linux-gnueabi-gcc
CFLAGS	= -I. -Wall -Wno-unused-variable -DSAM9X
CFLAGS2 = -DEMBED_TGT=1
LFLAGS  = -lrt
CMS_DLMS_API_LIB = dlms_api_lib.so
rm       = rm -Rf

OBJDIR   = ./obj
BINDIR   = ./bin
LIB_DIR  = ./lib

DLMS_LIB_SRC_DIR = ./src
DLMS_LIB_INC_DIR = -I./inc
DLMS_LIB_SRC  := $(wildcard $(DLMS_LIB_SRC_DIR)/*.c)
DLMS_LIB_INC := $(wildcard $(DLMS_LIB_INC_DIR)/*.h)
DLMS_LIB_OBJECTS  := $(DLMS_LIB_SRC:$(DLMS_LIB_SRC_DIR)/%.c=$(OBJDIR)/%.o)

DLMS_API_LIB_TARGET = dlms_api_lib.so

TARGET = $(LIB_DIR)/$(DLMS_API_LIB_TARGET)

all : $(TARGET)

$(LIB_DIR)/$(DLMS_API_LIB_TARGET): $(DLMS_LIB_OBJECTS)
	$(CC) -shared -fPIC -o $(LIB_DIR)/$(DLMS_API_LIB_TARGET) $(DLMS_LIB_OBJECTS)
	@echo "Library Creation complete!"

$(DLMS_LIB_OBJECTS): $(OBJDIR)/%.o : $(DLMS_LIB_SRC_DIR)/%.c
	@$(CC) $(DLMS_LIB_INC_DIR) $(CFLAGS) -c $< -o $@
	@echo "DLMS API Source Compiled "$<" successfully!"
	
.PHONEY: clean

clean:
	@$(rm) $(OBJDIR)/*.o
	@echo "Cleanup complete!" 
