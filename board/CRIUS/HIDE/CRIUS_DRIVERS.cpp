

#include "../CRIUS/CRIUS_DRIVERS.h"


//**********MirmOS Dataflash Driver**************//
#include "utility/BlockDevShedule.h"
df_LinearSpace drv_df_LinearSpace;

uint8_t spi_dataflash_on_mount()								
{df_Init();}

uint8_t spi_dataflash_on_umount()			
{}

size_t spi_dataflash_write(uint64_t adr,uint32_t size,uint8_t* ptr)
{drv_df_LinearSpace.GoTo(adr);
drv_df_LinearSpace.Write( ptr, size );
}

size_t spi_dataflash_read(uint64_t adr,uint32_t size,uint8_t* ptr)
{drv_df_LinearSpace.GoTo(adr);
drv_df_LinearSpace.Read( ptr, size );
}						
//**********************************************************************

//***************************Serial Function*****************************
#include "utility/AllStreamClasses.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "wiring_private.h"
#define SERIAL_BUFFER_SIZE 200
uint32_t writeSerial(HardwareSerial2* ptr,uint8_t c)
{
int i = (ptr->_tx_buffer->head + 1) % SERIAL_BUFFER_SIZE;
while (i == ptr->_tx_buffer->tail);
  ptr->_tx_buffer->buffer[ptr->_tx_buffer->head] = c;
  ptr->_tx_buffer->head = i;
	
  sbi(*(ptr->_ucsrb), (ptr->_udrie));
  ptr->transmitting = true;
  ptr->_tx_buffer->transmitting=2;
  // clear the TXC bit -- "can be cleared by writing a one to its bit location"
  sbi(*(ptr->_ucsra), TXC0);
  
  return 1;
}


uint32_t writeMasSerial(HardwareSerial2* ptr,uint8_t* c,uint32_t n)
{
ptr->write(c,n);}
//**********************************************************************




extern blockdriver_t spi_dataflash;
extern func_struct serial_func;
void device_drivers_init()
{
serial_func.write=(write_type_t)writeMasSerial;
serial_func.write_smp=(write_simple_type_t)writeSerial;
serial_func.on_close=(on_close_type_t)DoNothing;
serial_func.on_open=(on_open_type_t)DoNothing;

spi_dataflash.on_mount=spi_dataflash_on_mount;
spi_dataflash.on_umount=spi_dataflash_on_umount;
spi_dataflash.write_block=spi_dataflash_write;
spi_dataflash.read_block=spi_dataflash_read;

}
