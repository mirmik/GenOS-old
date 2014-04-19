
#ifndef mvirt_AINTC_DEFS_H_
#define mvirt_AINTC_DEFS_H_

#include <inttypes.h>
#include "types.h"

// ARM Interrupt Controller register structure - See sprufb3.pdf, Chapter 8 for more details.
typedef struct _DEVICE_AINTC_REGS_
{
  vuint32_t FIQ0;		//0x00
  vuint32_t FIQ1;		//0x04
  vuint32_t IRQ0;		//0x08
  vuint32_t IRQ1;		//0x0c
  vuint32_t FIQENTRY;	//0x10
  vuint32_t IRQENTRY;	//0x14
  vuint32_t EINT0;	//0x18
  vuint32_t EINT1;	//0x1c
  vuint32_t INTCTL;	//0x20
  vuint32_t EABASE;	//0x24
  vuint8_t RSVD0[8];	//0x28
  vuint32_t INTPRI0;	//0x30
  vuint32_t INTPRI1;	//0x34
  vuint32_t INTPRI2;	//0x38
  vuint32_t INTPRI3;	//0x3c
  vuint32_t INTPRI4;	//0x40
  vuint32_t INTPRI5;	//0x44
  vuint32_t INTPRI6;	//0x48
  vuint32_t INTPRI7;	//0x4c
}
DEVICE_AIntcRegs;

#define AINTC ((DEVICE_AIntcRegs*) 0x01C48000)

#endif
