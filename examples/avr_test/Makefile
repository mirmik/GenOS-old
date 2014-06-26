
GENOS = ../..
TARGET =avr
BOARD =CRIUS

OBJDIR = obj_$(TARGET)

MODULES = prototype debug strm charqueue shed readline intcom PrintTransformer


VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/

GENOSLIB := $(wildcard $(GENOS)/invariant/genoslib/*.c)

PROJECT = hello-world 


src = hello-world.cpp  debug_print.cpp StrmDebug.cpp Stream.cpp Print.cpp \
	DBStream.cpp ring.cpp dynamicring.cpp queue.cpp \
	u_esh.cpp command_list.cpp rl_terminal.cpp ASCII2KeyCom.cpp readline.cpp KeyCom.cpp \
	KeyCom2ASCII.cpp utility.cpp subst_shed.cpp


OBJ = $(src:%.cpp=$(OBJDIR)/%.o)


all: $(OBJDIR) $(OBJ) platform LINK
	


include $(GENOS)/invariant/Makefile.invariant
include $(GENOS)/platform/$(TARGET)/Makefile.$(TARGET)
include $(GENOS)/board/$(BOARD)/Makefile.$(BOARD)

platform: $(PLATFORMOBJ)
		
$(OBJDIR):
	- mkdir $(OBJDIR)

LINK:
	$(CPP) $(CPPFLAGS)  $(LDFLAGS) -mmcu=atmega2560  $(OBJ) $(PLATFORMOBJ) -o hello-world.hex

clean:
	- rm $(OBJDIR)/*.o
	
install: 
	sudo avrdude -P /dev/ttyUSB0 -c wiring -p m2560 -b 115200 -U flash:w:./hello-world.hex -D
