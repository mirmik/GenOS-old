
#include "hardware.h" 
#include "platform.h"
#include "debug/debug.h"
#include "simple.h"
#include "leds.h"
#include "GenOS.h"

uint8_t statusBit(uint8_t &f,uint8_t a)
{return(f & (1<<a));}

void setBit(uint8_t &f,uint8_t a)
{f=f | (1<<a);}

void clrBit(uint8_t &f,uint8_t a)
{f=f & (~(1<<a)); }

void CPU_SET(int a)
{asm("msr cpsr , r0");}


void (*zeroFunc)(void) =0;

extern "C" int SPSR_REGISTER();
extern "C" int CPU_MODE();
void processor_state()
{printd("PROCESSOR STATE: ");dln;
printd("CPSR:\t");debug_printhex_int32(PROCESSOR->CPSR);dln
printd("SPSR:\t");debug_printhex_int32(PROCESSOR->SPSR);dln
printd("R0:\t");debug_printhex_int32(PROCESSOR->R[0]);dln
printd("R1:\t");debug_printhex_int32(PROCESSOR->R[1]);dln
printd("R2:\t");debug_printhex_int32(PROCESSOR->R[2]);dln
printd("R3:\t");debug_printhex_int32(PROCESSOR->R[3]);dln
printd("R4:\t");debug_printhex_int32(PROCESSOR->R[4]);dln
printd("R5:\t");debug_printhex_int32(PROCESSOR->R[5]);dln
printd("R6:\t");debug_printhex_int32(PROCESSOR->R[6]);dln
printd("R7:\t");debug_printhex_int32(PROCESSOR->R[7]);dln
printd("R8:\t");debug_printhex_int32(PROCESSOR->R[8]);dln
printd("R9:\t");debug_printhex_int32(PROCESSOR->R[9]);dln
printd("R10:\t");debug_printhex_int32(PROCESSOR->R[10]);dln
printd("R11|FP:\t");debug_printhex_int32(PROCESSOR->R[11]);dln
printd("R12:\t");debug_printhex_int32(PROCESSOR->R[12]);dln
printd("SP:\t");debug_printhex_int32(PROCESSOR->SP);dln
printd("LR:\t");debug_printhex_int32(PROCESSOR->LR);dln
printd("PC:\t");debug_printhex_int32(PROCESSOR->PC);dln
}

PROCESSOR_t *PROCESSOR;
#include "interrupts.h"

#define SYSERRORLEDPERIOD 100
void systemError_platform() 
{//asm("mov r0,lr");
IRQ_D();
FIQ_D();
while(1)	
{	
	red_led_on();	
	delay_cpu(SYSERRORLEDPERIOD);	
	red_led_off();	
	delay_cpu(SYSERRORLEDPERIOD);	
}
}	

