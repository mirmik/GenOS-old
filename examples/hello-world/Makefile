
GENOS = ../..
TARGET =native

OBJDIR = obj_$(TARGET)

MODULES = StreamPrint debug_print


VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/
GENOSFLAGS:= $(addprefix -I../../invariant/,$(MODULES))

GENOSLIB := $(wildcard $(GENOS)/invariant/genoslib/*.c)

PROJECT = hello-world


src = hello-world.cpp Print.cpp Stream.cpp debug_print.cpp

	
OBJ = $(src:%.cpp=$(OBJDIR)/%.o)


all: $(OBJDIR) $(OBJ) platform LINK
	mv hello-world hello-world.$(TARGET)



include $(GENOS)/platform/$(TARGET)/Makefile.$(TARGET)

platform: $(PLATFORMOBJ)
		
$(OBJDIR):
	- mkdir $(OBJDIR)

LINK:
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(OBJ) $(PLATFORMOBJ) -o hello-world

clean:
	- rm $(OBJDIR)/*.o
	
