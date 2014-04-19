
#ifndef mvirt_TIMER_DEFS_H_
#define mvirt_TIMER_DEFS_H_
#include "types.h"

#include <inttypes.h>

// Timer Register structure - See spruee5a.pdf for more details.
typedef struct _DEVICE_TIMER_REGS_
{
    vuint32_t PID12;          // 0x00
    vuint32_t EMUMGT_CLKSPD;  // 0x04
    vuint8_t  RSVD0[8];       // 0x08
    vuint32_t TIM12;          // 0x10
    vuint32_t TIM34;          // 0x14
    vuint32_t PRD12;          // 0x18
    vuint32_t PRD34;          // 0x1C
    vuint32_t TCR;            // 0x20
    vuint32_t TGCR;           // 0x24
    vuint32_t WDTCR;          // 0x28
    vuint8_t  RSVD1[8];       // 0x2C
    vuint32_t REL12;          // 0x34
    vuint32_t REL34;          // 0x38
    vuint32_t CAP12;          // 0x3C
    vuint32_t CAP34;          // 0x40
    vuint32_t INTCTL_STAT;    // 0x44
}
DEVICE_TimerRegs;

#define TIMER0 ((DEVICE_TimerRegs*) 0x01C21400)

#endif
