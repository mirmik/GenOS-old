
GENOS = ../..
TARGET =native

OBJDIR = obj_$(TARGET)

MODULES = debug prototype error genoslib \
	math allocator intcom internalClib shed


VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/

GENOSLIB := $(wildcard $(GENOS)/invariant/genoslib/*.c)

PROJECT = hello-world


src = hello-world.cpp Print.cpp Stream.cpp error.cpp math.cpp debug_print.cpp allocator.cpp utility.cpp \
command_list.cpp  delay.cpp u_esh.cpp

	
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
	
