
#include "timer.h"
#include "types.h"
#include <inttypes.h>
#include "hardware.h"
#include "interrupts.h"

#define MILLIS_INC 4096

uint64_t __system_timer_clock=0;
uint64_t timer0_millis=0;


volatile uint64_t timer0_state ()
{uint64_t m;
IRQ_D();
m=TIMER0->TIM12 << 32;
m = m | TIMER0->TIM34;
IRQ_E();	
	return(m);}

volatile uint64_t millis ()
{uint64_t m=0,m2=0;
IRQ_D();
m=TIMER0->TIM12;
m2 =  TIMER0->TIM34;
m2 = m2 << 32;
m = (m+m2 ) / 0x5DC0;
IRQ_E();	
	return(m);}
	
	/*
uint64_t micros ()
{IRQ_D();
	uint64_t res=__system_timer_clock *0x3E8000;
	uint32_t m= TIMER0->TIM12 / 0x18;
	res=res + m;
IRQ_E();	
	return(res);}
*/
/*
void ISR_TINT0(){
//uint64_t m = timer0_millis;	
__system_timer_clock++;
//m += MILLIS_INC;
	timer0_irq++;
timer0_millis+=MILLIS_INC;
IRQ_FLAG_REMOVE(TINT0);
	};
*/


volatile void init_TIMER0()
{
  // Put timer into reset
  TIMER0->EMUMGT_CLKSPD = 0x00000003;
  TIMER0->TCR           = 0x00000000;
  
  // Enable TINT0, TINT1 interrupt
  TIMER0->INTCTL_STAT   = 0x00000001;
	
  // // Set to 64-bit GP Timer mode, enable TIMER12 & TIMER34
  TIMER0->TGCR = 0x00000003;
//TIMER0->TGCR = 0x00000003 | (1<<2);

  // Reset timers to zero 
  TIMER0->TIM12 = 0x00000000;
  TIMER0->TIM34 = 0x00000000;
  
  // Set timer period (5 second timeout = (24000000 * 5) cycles = 0x07270E00) 
  TIMER0->PRD34 = 0xFFFFFFFF;
  TIMER0->PRD12 = 0xFFFFFFFF;
}

//interrupt for Timer0 in DM35x and DM36x is the same
volatile void DEVICE_TIMER0Start(void)
{
  // Clear interrupt
  AINTC->IRQ1   |=  0x00000003;

  // Put timer in reset
  TIMER0->TGCR  =   0x00000000;

  // Reset timer count to zero 
  TIMER0->TIM12 =   0x00000000;
TIMER0->TIM34 =   0x00000000;

  // Setup for one-shot mode
 // TIMER0->TCR   =   0x00000040;
TIMER0->TCR = (2 << 6) | (2 << 22);
  // Start TIMER12
 // TIMER0->TGCR  = 0x00000005;
  TIMER0->TGCR  = 3;
}

