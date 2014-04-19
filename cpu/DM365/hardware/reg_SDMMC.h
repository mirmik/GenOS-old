
#include "types.h"

#ifndef mvirt_SDMMC_DEFS_H_
#define mvirt_SDMMC_DEFS_H_

#include <inttypes.h>

typedef struct _DEVICE_SDMMC_REGS_
{
    vuint16_t MMCCTL;
    vuint8_t RSVD0[2];
    vuint16_t MMCCLK;
    vuint8_t RSVD1[2];
    vuint16_t MMCST0;
    vuint8_t RSVD2[2];
    vuint16_t MMCST1;
    vuint8_t RSVD3[2];
    vuint16_t MMCIM;
    vuint8_t RSVD4[2];
    vuint16_t MMCTOR;
    vuint8_t RSVD5[2];
    vuint16_t MMCTOD;
    vuint8_t RSVD6[2];
    vuint16_t MMCBLEN;
    vuint8_t RSVD7[2];
    vuint16_t MMCNBLK;
    vuint8_t RSVD8[2];
    vuint16_t MMCNBLC;
    vuint8_t RSVD9[2];
    vuint32_t MMCDRR;
    vuint32_t MMCDXR;
    vuint32_t MMCCMD;
    vuint32_t MMCARGHL;
    vuint32_t MMCRSP01;
    vuint32_t MMCRSP23;
    vuint32_t MMCRSP45;
    vuint32_t MMCRSP67;
    vuint16_t MMCDRSP;
    vuint8_t RSVD10[2];
    vuint16_t MMCETOK;
    vuint8_t RSVD11[2];
    vuint16_t MMCCIDX;
    vuint8_t RSVD12[2];
    vuint16_t MMCCKC;
    vuint8_t RSVD13[2];
    vuint16_t MMCTORC;
    vuint8_t RSVD14[2];
    vuint16_t MMCTODC;
    vuint8_t RSVD15[2];
    vuint16_t MMCBLNC;
    vuint8_t RSVD16[2];
    vuint16_t SDIOCTL;
    vuint8_t RSVD17[2];
    vuint16_t SDIOST0;
    vuint8_t RSVD18[2];
    vuint16_t SDIOIEN;
    vuint8_t RSVD19[2];
    vuint16_t SDIOIST;
    vuint8_t RSVD20[2];
    vuint16_t MMCFIFOCTL;
} 
DEVICE_SDMMCRegs;

#define SDMMC ((DEVICE_SDMMCRegs*) 0x1D11000)
//0x01C40000
#define SDMMC_PERIPHERAL_CNT      (1)

#define DEVICE_SDMMC_MMCST0_DXRDY_MASK      (0x0200u)
#define DEVICE_SDMMC_MMCST0_DXRDY_SHIFT     (0x0009u)
#define DEVICE_SDMMC_MMCST0_DXRDY_RESETVAL  (0x0001u)

#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_MASK (0x0002u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_SHIFT (0x0001u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_RESETVAL (0x0000u)

/*----FIFODIR Tokens----*/
#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_READ (0x0000u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFODIR_WRITE (0x0001u)

#define DEVICE_SDMMC_MMCFIFOCTL_FIFORST_MASK (0x0001u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFORST_SHIFT (0x0000u)
#define DEVICE_SDMMC_MMCFIFOCTL_FIFORST_RESETVAL (0x0000u)


#endif
