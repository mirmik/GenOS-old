
#include "types.h"



#ifndef mvirt_reg_PSC_h
#define mvirt_reg_PSC_h

#include <inttypes.h>

// Power/Sleep Ctrl Register structure - See sprufb3.pdf, Chapter 7
typedef struct _DEVICE_PSC_REGS_
{
  vuint32_t PID;        // 0x000
  vuint8_t RSVD0[16];   // 0x004
  vuint8_t RSVD1[4];    // 0x014
  vuint32_t INTEVAL;    // 0x018
  vuint8_t RSVD2[36];   // 0x01C
  vuint32_t MERRPR0;    // 0x040
  vuint32_t MERRPR1;    // 0x044
  vuint8_t RSVD3[8];    // 0x048
  vuint32_t MERRCR0;    // 0x050
  vuint32_t MERRCR1;    // 0x054
  vuint8_t RSVD4[8];    // 0x058
  vuint32_t PERRPR;     // 0x060
  vuint8_t RSVD5[4];    // 0x064
  vuint32_t PERRCR;     // 0x068
  vuint8_t RSVD6[4];    // 0x06C
  vuint32_t EPCPR;      // 0x070
  vuint8_t RSVD7[4];    // 0x074
  vuint32_t EPCCR;      // 0x078
  vuint8_t RSVD8[144];  // 0x07C
  vuint8_t RSVD9[20];   // 0x10C
  vuint32_t PTCMD;      // 0x120
  vuint8_t RSVD10[4];   // 0x124
  vuint32_t PTSTAT;     // 0x128
  vuint8_t RSVD11[212]; // 0x12C
  vuint32_t PDSTAT0;    // 0x200
  vuint32_t PDSTAT1;    // 0x204
  vuint8_t RSVD12[248]; // 0x208
  vuint32_t PDCTL0;     // 0x300
  vuint32_t PDCTL1;     // 0x304
  vuint8_t RSVD13[536]; // 0x308
  vuint32_t MCKOUT0;    // 0x520
  vuint32_t MCKOUT1;    // 0x524
  vuint8_t RSVD14[728]; // 0x528
  vuint32_t MDSTAT[52]; // 0x800
  vuint8_t RSVD15[304]; // 0x8D0
  vuint32_t MDCTL[52];  // 0xA00
}DEVICE_PSCRegs;
#define PSC ((DEVICE_PSCRegs*) 0x01C41000)

// PSC constants
#define LPSC_TPCC			(0)
#define LPSC_TPTC0			(1)
#define LPSC_TPTC1          (2)
#define LPSC_TPTC2          (3)
#define LPSC_TPTC3          (4)
#define LPSC_TIMER3         (5)
#define LPSC_SPI1           (6)
#define LPSC_MMC_SD1        (7)
#define LPSC_ASP1           (8)
#define LPSC_USB            (9)
#define LPSC_PWM3           (10)
#define LPSC_SPI2           (11)
#define LPSC_RTO            (12)
#define LPSC_DDR2           (13)
#define LPSC_AEMIF          (14)
#define LPSC_MMC_SD0        (15)
#define LPSC_MEMSTK         (16)
#define TIMER4				(17)
#define LPSC_I2C            (18)
#define LPSC_UART0          (19)
#define LPSC_UART1          (20)
#define LPSC_UHPI          	(21)
#define LPSC_SPIO           (22)
#define LPSC_PWM0           (23)
#define LPSC_PWM1           (24)
#define LPSC_PWM2           (25)
#define LPSC_GPIO           (26)
#define LPSC_TIMER0         (27)
#define LPSC_TIMER1         (28)
#define LPSC_TIMER2         (29)
#define LPSC_SYSMOD         (30)
#define LPSC_ARM            (31)
#define LPSC_SPI3			(38)
#define LPSC_SPI4			(39)
#define LPSC_CPGMAC			(40)
#define LPSC_RTC			(41)
#define LPSC_KEYSCAN        (42)
#define LPSC_ADC			(43)
#define LPSC_VOICECODEC		(44)
#define LPSC_IMCOP			(50)
#define LPSC_KALEIDO		(51)

#endif
