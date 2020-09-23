#CC = gcc
CC = /home/ganesh/bin/arm-2011.09/bin/arm-none-linux-gnueabi-gcc
CFLAGS	= -I. -Wall -Wno-unused-variable -DSAM9X

#LIBS2= -L/home/preethi/Projects/SAM9G25/addOns/curl-master/lib/.libs -lcurl -ldl
# linking flags here
LFLAGS   = -Wall -L. -lm -lpthread -lrt

#INCLUDE2= -I/home/preethi/Projects/SAM9G25/addOns/curl-master/include
INCS = -I

# change these to set the proper directories where each files should be
SRCDIR   = .
OBJDIR   = .
BINDIR   = .

SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -Rf

TARGET=dlms_c_library
 
$(TARGET): $(OBJECTS)
	@$(CC) -o  $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(INCS) $(CFLAGS) -c $< -o $@
	cp $(TARGET) ./bin/$(TARGET)
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJDIR)/*.o
	@$(rm) $(BINDIR)/$(TARGET)
	@echo $(OBJECTS)
	@echo "Cleanup complete!" 