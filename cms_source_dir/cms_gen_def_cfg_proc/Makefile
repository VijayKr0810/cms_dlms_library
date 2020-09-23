CC = gcc
#CC = /home/ganesh/bin/arm-2011.09/bin/arm-none-linux-gnueabi-gcc
CFLAGS	= -I. -Wall -Wno-unused-variable

# linking flags here
LFLAGS   = -Wall -L. -lm -lpthread -lrt

CMS_COMMON_INC_DIR = -I ../cms_common_inc
CMS_LIB_INC_DIR = -I ../cms_dlms_api_library/inc
# change these to set the proper directories where each files should be
SRCDIR   = ./src
INCDIR	 = -I./inc
OBJDIR   = ./obj
BINDIR   = ./bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -Rf

TARGET = cms_gen_def_cfg
 
$(TARGET): $(OBJECTS)
	@$(CC) -o  $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CMS_COMMON_INC_DIR) $(INCDIR) $(CMS_LIB_INC_DIR) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJDIR)/*.o
	@$(rm) $(TARGET)
	@echo $(OBJECTS)
	@echo "Cleanup complete!" 
