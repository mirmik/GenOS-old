
GENOS = ../..
TARGET =native

OBJDIR = obj_$(TARGET)

MODULES = debug local_heap prototype allocator shed charqueue strm  intcom readline error strm


VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/


PROJECT = hello-world


src = hello-world.cpp Print.cpp Stream.cpp allocator.cpp delay.cpp alloc_standart.cpp u_esh.cpp flag_sh.cpp \
	ring.cpp queue.cpp DBStream.cpp dynamicring.cpp StrmNull.cpp BufferStrm.cpp debug_print.cpp \
	command_list.cpp utility.cpp readline.cpp rl_terminal.cpp error.cpp StrmDebug.cpp genoslib.cpp
		
OBJ = $(src:%.cpp=$(OBJDIR)/%.o)


all: $(OBJDIR) $(OBJ) platform LINK
	mv hello-world hello-world.$(TARGET)



include $(GENOS)/invariant/Makefile.invariant
include $(GENOS)/platform/$(TARGET)/Makefile.$(TARGET)

platform: $(PLATFORMOBJ)
		
$(OBJDIR):
	- mkdir $(OBJDIR)

LINK:
	$(CPP) $(CPPFLAGS)  $(LDFLAGS) $(OBJ) $(PLATFORMOBJ) -o hello-world

clean:
	- rm $(OBJDIR)/*.o
	
