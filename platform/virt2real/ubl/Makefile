
CCFLAGS= -I$(TOPDIR)/drivers/include -I$(TOPDIR)/include -mcpu=arm926ej-s  -O2 -DUBL_SD_MMC
LDFLAGS = -Tubl.lds -nostartfiles
DEVDIR=${shell pwd}/..
CSPATH = $(DEVDIR)/codesourcery/arm-2013.05

CROSS_COMPILE=$(TOPDIR)/../g++_arm_none_eabi/bin/arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump
TOPDIR=${shell pwd}

PROGRAMM = ubl uart debug device util uartboot boot selfcopy sdmmcboot
DPROGRAMM = sdmmc 

OBJS = $(addprefix src/,$(PROGRAMM))
OBJS := $(addsuffix .o,$(OBJS))
OBJD = $(addprefix drivers/src/,$(DPROGRAMM))
OBJD := $(addsuffix .o,$(OBJD))


all: all2

all2: $(OBJSA) $(OBJLIB) $(OBJS) $(OBJD) LINK DISASM OCPY 

LINK: 
	$(CC) $(CCFLAGS) $(LDFLAGS) $(OBJSA) $(OBJS) $(OBJLIB) $(OBJD) -o ubl

DISASM:
	$(OBJDUMP) -d ubl > disasm


OCPY:
	$(OBJCOPY) -O binary ubl ubl.bin
	$(OBJCOPY) -O binary ubl ubl.bin
 

%.o:%.S
	$(CC) $(CCFLAGS) -c $< -o $@


%.o:%.c
	$(CC) $(CCFLAGS) -c $< -o $@



clean:
	rm -f $(TOPDIR)/src/*.o
	rm -f $(TOPDIR)/drivers/src/*.o


