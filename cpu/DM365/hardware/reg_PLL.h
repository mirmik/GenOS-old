#include "types.h"

// modified for DM365.Referred to GEL file 
typedef struct _DEVICE_PLL_REGS_
{
  vuint32_t PID;			//0x00
  vuint8_t RSVD0[224];	//0x04
  vuint32_t RSTYPE;		//0xe4
  vuint8_t RSVD1[24];  	//0xe8
  vuint32_t PLLCTL;		//0x100
  vuint8_t RSVD2[4];  	//0x104
  vuint32_t SECCTL;		//0x108
  vuint32_t RV;			//0x10c
  vuint32_t PLLM;			//0x110
  vuint32_t PREDIV;		//0x114
  vuint32_t PLLDIV1;		//0x118
  vuint32_t PLLDIV2;		//0x11c
  vuint32_t PLLDIV3;  	//0x120
  vuint32_t OSCDIV1;		//0x124
  vuint32_t POSTDIV;		//0x128
  vuint32_t BPDIV;		//0x12c
  vuint8_t RSVD5[8];  	//0x130
  vuint32_t PLLCMD;		//0x138
  vuint32_t PLLSTAT;		//0x13c
  vuint32_t ALNCTL;		//0x140
  vuint32_t DCHANGE;		//0x144
  vuint32_t CKEN;			//0x148
  vuint32_t CKSTAT;		//0x14c
  vuint32_t SYSTAT;		//0x150
  vuint8_t RSVD6[12];		//0x154
  vuint32_t PLLDIV4;		//0x160
  vuint32_t PLLDIV5;		//0x164
  vuint32_t PLLDIV6;		//0x168
  vuint32_t PLLDIV7;		//0x16C
  vuint32_t PLLDIV8;		//0x170
  vuint32_t PLLDIV9;		//0x174
}
DEVICE_PLLRegs;

#define PLL1 ((DEVICE_PLLRegs*) 0x01C40800)
#define PLL2 ((DEVICE_PLLRegs*) 0x01C40C00)
