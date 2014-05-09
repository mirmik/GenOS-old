
GENOS = ../..
TARGET =PC_multiboot
CPU=x86
#TARGET=native

OBJDIR = obj_$(TARGET)

MODULES = debug delay error prototype strm abstract_irq initenv \
	 VideoPage 


VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/


PROJECT = hello-world


src = hello-world.cpp debug_print.cpp delay_cpu.cpp \
	error.cpp Stream.cpp Print.cpp abstract_irq.cpp genoslib.cpp \
	initenv.cpp  \
	VideoPage.cpp VideoPagePrint.cpp
		
OBJ = $(src:%.cpp=$(OBJDIR)/%.o)


include $(GENOS)/invariant/Makefile.invariant
include $(GENOS)/platform/$(TARGET)/Makefile.$(TARGET)

platform: $(PLATFORMOBJ)
		
$(OBJDIR):
	- mkdir $(OBJDIR)

LINK:
	$(CPP) $(LDFLAGS) $(CFLAGS)  $(OBJ) $(PLATFORMOBJ) -o hello-world
	
	
clean:
	- rm $(OBJDIR)/*.o
	
start:
	qemu -hda ~/multiboot/hard_disk.img
