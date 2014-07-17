
GENOS = ../..
TARGET =native

OBJDIR = obj_$(TARGET)

MODULES = StreamPrint debug_print intcom command_list GenosPrint PrintTransform readline \
	rl_terminal KeyCom GenosInfo stdutility
 

VPATH := $(addprefix ../../invariant/,$(MODULES))
VPATH += $(GENOS)/invariant/
GENOSFLAGS:= $(addprefix -I../../invariant/,$(MODULES))

GENOSLIB := $(wildcard $(GENOS)/invariant/genoslib/*.c)

PROJECT = hello-world


src = hello-world.cpp Print.cpp Stream.cpp debug_print.cpp command_list.cpp ASCII2KeyCom.cpp KeyCom.cpp \
	KeyCom2ASCII.cpp readline.cpp rl_terminal.cpp utility.cpp
	
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
	
