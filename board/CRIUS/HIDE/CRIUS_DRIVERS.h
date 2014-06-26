


#ifndef CRIUS_DRIVERS_H
#define CRIUS_DRIVERS_H

#include "MirmOS.h"
#include "../CRIUS/dataflash.h"




//***************************************MirmOS.h
uint8_t spi_dataflash_on_mount();
uint8_t spi_dataflash_on_umount();
size_t spi_dataflash_write(uint64_t adr,uint32_t size,uint8_t* ptr);
size_t spi_dataflash_read(uint64_t adr,uint32_t size,uint8_t* ptr);	
//****************************************************************

















#endif