
GENOS = ../..
TARGET =PC_multiboot
CPU=x86

OBJDIR = obj_$(TARGET)

MODULES = debug_print delay error StreamPrint abstract_irq initenv charqueue intcom allocator \
KeyCom intcom Delay GenosInfo readline rl_terminal GenosPrint InternalClib
 

VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/
GENOSFLAGS:= $(addprefix -I../../invariant/,$(MODULES))


PROJECT = hello-world


src = hello-world.cpp debug_print.cpp delay_cpu.cpp \
	error.cpp Stream.cpp Print.cpp abstract_irq.cpp \
	initenv.cpp string.cpp
		
OBJ = $(src:%.cpp=$(OBJDIR)/%.o)


include $(GENOS)/platform/$(TARGET)/Makefile.$(TARGET)

platform: $(PLATFORMOBJ)
		
$(OBJDIR):
	- mkdir $(OBJDIR)

LINK:
	$(CPP) $(CPPFLAGS) $(LDFLAGS)  $(OBJ) $(PLATFORMOBJ) -o hello-world
	
	
clean:
	- rm $(OBJDIR)/*.o
	
start:
	qemu -hda ~/multiboot/hard_disk.img
