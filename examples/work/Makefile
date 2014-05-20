
GENOS = ../..
TARGET =PC_multiboot
CPU=x86

OBJDIR = obj_$(TARGET)

MODULES = debug delay error prototype strm abstract_irq initenv readline intcom \
	keyboard_scan VideoPage PrintTransformer allocator shed genoslib ATAPI filtration


VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/


PROJECT = hello-world


src := hello-world.cpp debug_print.cpp delay_cpu.cpp \
	error.cpp Stream.cpp Print.cpp abstract_irq.cpp \
	initenv.cpp \
	rl_terminal.cpp readline.cpp command_list.cpp utility.cpp \
	keyboard_scan.cpp VideoPage.cpp VideoPagePrint.cpp KeyCom.cpp Scan2KeyCom.cpp allocator.cpp \
	u_esh.cpp aperiodic.cpp

src += $(wildcard $(GENOS)/invariant/genoslib/*.c)
#src += $(wildcard $(GENOS)/invariant/ATAPI/*.c)



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
