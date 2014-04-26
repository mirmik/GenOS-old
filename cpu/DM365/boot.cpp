
// This module's header file 
#include "boot.h"
#include "leds.h"
#include "debug/debug.h"
#include "platform_debug.h"
extern void boot2(void);

extern "C" void _init();
// Boot entry point to setup the C environment
//const int STACKStart=0x90000000; //it is DTCM top

extern "C" void boot(void)
{asm(".EQU IRQ_STACK_SIZE, 0x100 \n\r \
.EQU FIQ_STACK_SIZE, 0x100 \n\r \
.EQU ABT_STACK_SIZE, 0x100 \n\r \
.EQU UND_STACK_SIZE, 0x100 \n\r \
.EQU SVC_STACK_SIZE, 0x300 \n\r \
\n\r \
.include \"arm_asm_def.h\" \n\r \
");
	
  asm(" .global STACKStart");
  asm(" .global _stack");
 
 
 asm("msr cpsr , #ARM_MODE_SVC | I_BIT | F_BIT");
 
   asm("ldr r0, _stack");
  
 asm("msr cpsr , #ARM_MODE_IRQ | I_BIT | F_BIT");
  asm(" mov  sp, r0");
  asm(" sub  r0, r0, #IRQ_STACK_SIZE");
 
 
 asm("msr cpsr , #ARM_MODE_FIQ | I_BIT | F_BIT");
  asm(" mov  sp, r0");
  asm(" sub  r0, r0, #FIQ_STACK_SIZE");

 asm("msr cpsr , #ARM_MODE_ABT | I_BIT | F_BIT");
  asm(" mov  sp, r0");
  asm(" sub  r0, r0, #ABT_STACK_SIZE");
  
 asm("msr cpsr , #ARM_MODE_UND | I_BIT | F_BIT");
  asm(" mov  sp, r0");
  asm(" sub  r0, r0, #UND_STACK_SIZE");
  
 asm("msr cpsr , #ARM_MODE_SVC | I_BIT | F_BIT");
 asm(" mov  sp, r0");
  asm(" sub  r0, r0, #SVC_STACK_SIZE");
 
  
  // Setup the stack pointer
 // asm(" LDR  sp,_stack");
 // asm(" SUB  sp,sp,#4");
 // asm(" BIC  sp, sp, #7");
 
 
 
   //Enable ITCM
  asm(" MRC p15,#0,r0,c9,c1,#1");
  asm(" LDR r0,_itcm");
  asm(" MCR p15,#0,r0,c9,c1,#1");
    
  //Enable DTCM
  asm(" MRC p15,#0,r0,c9,c1,#0");
   asm(" LDR r0,_dtcm");
  asm(" MCR p15,#0,r0,c9,c1,#0");


  _init();
  printd("boot\r\n");

  // Call to boot2 entry point
  asm("b boot2");
  
  
  
  asm("__wh:");
  asm("b __wh");
  
  
  asm("_stack:");
  asm(" .word STACKStart");
asm("_itcm:");
asm(".word 0x00000019");
//asm(".word 0x00000000");
asm("_dtcm:");
asm(".word 0x00010019");
//asm(".word 0x00000000");

}
