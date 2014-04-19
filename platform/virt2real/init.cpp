
#include "simple.h"
#include "hardware.h"
#include "init.h"
#include "interrupts.h"
#include "timer.h"


volatile void stat_UART0()
{
  prlnhex(UART0->PWREMU_MGNT);         // Reset UART TX & RX components
 
 //delay_cpu(0x0000f000);
 
  prlnhex(UART0->MDR);
  prlnhex(UART0->DLL);               // Set baud rate	
  prlnhex(UART0->DLH);
  prlnhex(UART0->FCR);            // Clear UART TX & RX FIFOs
  prlnhex(UART0->IER);            // Enable interrupts
  prlnhex(UART0->LCR);            // 8-bit words,
                                  // 1 STOP bit generated,
                                  // No Parity, No Stick paritiy,
                                  // No Break control
  prlnhex(UART0->MCR);            // RTS & CTS disabled,
                                  // Loopback mode disabled,
                                  // Autoflow disabled
                                   
  //prlnhex(UART0->PWREMU_MGNT);    // Enable TX & RX componenets
  
};


volatile void init_UART0()
{  UART0->PWREMU_MGNT = 0;         // Reset UART TX & RX components

  delay_cpu( 100 );

  UART0->MDR = 0x1;
  uint32_t a = 24000000 / 115200 / 13;  
	UART0->DLL = a & 0xFF;               // Set baud rate	
	//UART0->DLH = (a>>8) & 0xFF;
 // UART0->DLL = 0xd;               // Set baud rate	
 // UART0->DLH = 0;
 

  UART0->FCR = 0x0007;            // Clear UART TX & RX FIFOs
  UART0->FCR = 0x0000;            // Non-FIFO mode
  UART0->IER = 0x0007;            // Enable interrupts
  
  UART0->LCR = 0x0003;            // 8-bit words,
                                  // 1 STOP bit generated,
                                  // No Parity, No Stick paritiy,
                                  // No Break control
  
  UART0->MCR = 0x0000;            // RTS & CTS disabled,
                                  // Loopback mode disabled,
                                  // Autoflow disabled

  UART0->PWREMU_MGNT = 0xE001;    // Enable TX & RX componenets
        

};




void second_init()
{

irq_link();

init_TIMER0();
DEVICE_TIMER0Start();
SYSTEM->PINMUX[2]=SYSTEM->PINMUX[2] & 0x00000015; 
//green led output
GPIO_BANK45->DIR &= ~(1<<9);
//red led output
GPIO_BANK45->DIR &= ~(1<<10);
init_UART0();
IRQ_E();
FIQ_E();
}


void drivers_init(){};

