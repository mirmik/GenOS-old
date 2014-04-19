
GENOS = ../..
TARGET =native

OBJDIR = obj_$(TARGET)

MODULES = csh test microrl prototype transport intcom charqueue strm


VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/


PROJECT = hello-world


src = hello-world.cpp csh.cpp Print.cpp Stream.cpp
		
OBJ = $(src:%.cpp=$(OBJDIR)/%.o)


all: $(OBJDIR) $(OBJ) platform LINK
	mv hello-world hello-world.$(TARGET)



include $(GENOS)/invariant/Makefile.invariant
include $(GENOS)/platform/$(TARGET)/Makefile.$(TARGET)

platform: $(PLATFORMOBJ)
		
$(OBJDIR):
	- mkdir $(OBJDIR)

LINK:
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(OBJ) $(PLATFORMOBJ) -o hello-world

clean:
	- rm $(OBJDIR)/*.o
	
