
#ifndef mvirt_reg_UART_h
#define mvirt_reg_UART_h

#include "types.h"

// UART Register structure - See sprued9b.pdf for more details.
typedef struct _DEVICE_UART_REGS_
{
  vuint32_t RBR;			//0x00
  vuint32_t IER;			//0x04
  vuint32_t IIR;			//0x08
  vuint32_t LCR;			//0x0c
  vuint32_t MCR;			//0x10
  vuint32_t LSR;			//0x14
  vuint32_t MSR;			//0x18
  vuint8_t  RSVD0[4];		//0x1c         
  vuint8_t  DLL;			//0x20
  vuint8_t  RSVD1[3];
  vuint8_t  DLH;			//0x24
  vuint8_t  RSVD2[3];  
  vuint32_t PID1;			//0x28
  vuint32_t PID2;			//0x2c
  vuint32_t PWREMU_MGNT;	//0x30
  vuint32_t MDR;			//0x34
}
DEVICE_UartRegs;

#define THR RBR
#define FCR IIR

#define UART0 ((DEVICE_UartRegs*) 0x01C20000)

#define DEVICE_UART0_DESIRED_BAUD   (115200)
#define DEVICE_UART0_OVERSAMPLE_CNT (16)


#endif
