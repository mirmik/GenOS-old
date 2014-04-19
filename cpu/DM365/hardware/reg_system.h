#ifndef mvirt_SYSTEM_DEFS_H_
#define mvirt_SYSTEM_DEFS_H_
#include "types.h"

#include <inttypes.h>

typedef struct _DEVICE_SYS_MODULE_REGS_
{
  vuint32_t PINMUX[5];         //0x00
  vuint32_t BOOTCFG;           //0x14
  vuint32_t ARM_INTMUX;        //0x18
  vuint32_t EDMA_EVTMUX;       //0x1C
  vuint32_t DDR_SLEW;          //0x20
  vuint32_t CLKOUT;            //0x24
  vuint32_t DEVICE_ID;         //0x28
  vuint32_t VDAC_CONFIG;       //0x2C
  vuint32_t TIMER64_CTL;       //0x30
  vuint32_t USBPHY_CTL;        //0x34
  vuint32_t MISC;              //0x38
  vuint32_t MSTPRI[2];         //0x3C
  vuint32_t VPSS_CLKCTL;       //0x44
  vuint32_t PERI_CLKCTRL;      //0x48
  vuint32_t DEEPSLEEP;         //0x4C
  vuint32_t DFT_ENABLE;        //0x50
  vuint32_t DEBOUNCE[8];		 //0x54
  vuint32_t VTPIOCR;			 //0x74
  vuint32_t PUPDCTL0;          //0x78
  vuint32_t PUPDCTL1;          //0x7C
  vuint32_t HDIMCOPBT;		 //0x80
  vuint32_t PLL0_CONFIG;       //0x84
  vuint32_t PLL1_CONFIG;       //0x88
}
DEVICE_SysModuleRegs;

#define SYSTEM ((DEVICE_SysModuleRegs*) 0x01C40000)


#endif
