
GENOS = ../..
TARGET =avr

OBJDIR = obj_$(TARGET)

MODULES = 


VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/

GENOSLIB := $(wildcard $(GENOS)/invariant/genoslib/*.c)

PROJECT = hello-world


src = hello-world.cpp 


OBJ = $(src:%.cpp=$(OBJDIR)/%.o)


all: $(OBJDIR) platform LINK
	


include $(GENOS)/invariant/Makefile.invariant
include $(GENOS)/platform/$(TARGET)/Makefile.$(TARGET)

platform: $(PLATFORMOBJ)
		
$(OBJDIR):
	- mkdir $(OBJDIR)

LINK:
	$(CPP)  $(src) -o hello-world.hex -mmcu=atmega2560 

clean:
	- rm $(OBJDIR)/*.o
	
install: 
	sudo avrdude -P /dev/ttyUSB2 -c wiring -p m2560 -b 115200 -U flash:w:./hello-world.hex -D
