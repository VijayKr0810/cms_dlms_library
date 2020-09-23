CC = gcc
CFLAGS	= -I. -Wall -Wno-unused-variable -DSAM9X

# linking flags here
LFLAGS   = -Wall -L. -lm -lpthread -lrt

# change these to set the proper directories where each files should be
SRCDIR   = .
INCDIR	 = -I ../cms_common_inc
OBJDIR   = .
BINDIR   = .

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -Rf

TARGET = cms_fw_md5_check_sum
 
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(CC) -o  $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(INCDIR) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJDIR)/*.o
	@$(rm) $(BINDIR)/$(TARGET)
	@echo $(OBJECTS)
	@echo "Cleanup complete!" 
