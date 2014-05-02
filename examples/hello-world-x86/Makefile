
GENOS = ../..
TARGET =PC_multiboot
CPU=x86

OBJDIR = obj_$(TARGET)

MODULES = 


VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/


PROJECT = hello-world


src = hello-world.cpp 
		
OBJ = $(src:%.cpp=$(OBJDIR)/%.o)


all: $(OBJDIR) $(OBJ) platform LINK
	mv hello-world hello-world.$(TARGET)
	cp hello-world.$(TARGET) kernel
	objdump -d kernel > kkk

include $(GENOS)/invariant/Makefile.invariant
include $(GENOS)/platform/$(TARGET)/Makefile.$(TARGET)

platform: $(PLATFORMOBJ)
		
$(OBJDIR):
	- mkdir $(OBJDIR)

LINK:
	$(CPP) $(LDFLAGS)  $(OBJ) $(PLATFORMOBJ) -o hello-world
	
	
clean:
	- rm $(OBJDIR)/*.o
	
install: 
	cp kernel /mnt/boot/kernel

start:
	qemu -hda ~/multiboot/hard_disk.img
