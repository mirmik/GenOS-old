

#ifndef mvirt_DDR2_DEFS_H_
#define mvirt_DDR2_DEFS_H_

#include <inttypes.h>
#include "types.h"


// DDR2 Memory Ctrl Register structure - See sprueh7d.pdf for more details.
typedef struct _DEVICE_DDR2_REGS_
{
  vuint8_t RSVD0[4];        //0x00
  vuint32_t SDRSTAT;        //0x04
  vuint32_t SDBCR;          //0x08
  vuint32_t SDRCR;          //0x0C
  vuint32_t SDTIMR;         //0x10
  vuint32_t SDTIMR2;        //0x14
  vuint8_t RSVD1[4];        //0x18
  vuint32_t SDBCR2;         //0x1C
  vuint32_t PBBPR;          //0x20
  vuint8_t RSVD2[156];      //0x24 
  vuint32_t IRR;            //0xC0
  vuint32_t IMR;            //0xC4
  vuint32_t IMSR;           //0xC8
  vuint32_t IMCR;           //0xCC
  vuint8_t RSVD3[20];       //0xD0
  vuint32_t DDRPHYCR;       //0xE4
  vuint32_t DDRPHYCR2;       //0xE8
  vuint8_t RSVD4[4];        //0xEC
}
DEVICE_DDR2Regs;

#define DDR                         ((DEVICE_DDR2Regs*) 0x20000000)

#define DEVICE_DDR2_TEST_PATTERN    (0xA55AA55Au)
//the size of DDR is 1GB
#define DEVICE_DDR2_RAM_SIZE        (0x40000000u)

#define DEVICE_MAX_IMAGE_SIZE       (0x02000000u)
#define DEVICE_DDR2_START_ADDR      (0x80000000u)
#define DEVICE_DDR2_END_ADDR        ((DEVICE_DDR2_START_ADDR + DEVICE_DDR2_RAM_SIZE))

#endif
