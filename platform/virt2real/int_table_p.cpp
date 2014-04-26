#include "virtboard.h"
#include "platform_debug.h"
#include "debug/debug.h"
#include "int_macro.h"
#include <inttypes.h>
#include "string.h"
#include "platform.h"

extern "C" int SPSR_REGISTER();
extern "C" int CPU_MODE();
extern "C" int STACK_POINTER();

uint32_t irqcount;


extern "C" void empty_INT(){
IRQ_D();FIQ_D();
printd("BAD IRQ!!!");dln
while(1);
};


extern "C" void undefined_instruction()__attribute__((naked,weak));
extern "C" void software_interrupt()__attribute__((naked,weak));
extern "C" void prefetch_abort()__attribute__((naked,weak));
extern "C" void data_abort()__attribute__((naked,weak));
extern "C" void not_used()__attribute__((naked,weak));
extern "C" void irq()__attribute__((interrupt("IRQ")));
extern "C" void fiq()__attribute__((interrupt("FIQ")));

extern "C" void undefined_instruction(){systemError("UNDEFINED_INSTRUCTION");};
extern "C" void software_interrupt(){systemError("SOFTWARE_INTERRUPT");};
extern "C" void prefetch_abort(){systemError("PREF_ABORT");};
extern "C" void data_abort(){systemError("DATA_ABORT");};
extern "C" void not_used(){systemError("NOT_USED");};
extern "C" void irq(){
	//printd("IRQ_CALL");	
	void (*p)();p=(void (*)())AINTC->IRQENTRY;
	//debug_serial_printhex_int(p);
	irqcount++;
	p();};
extern "C" void fiq(){systemError("FIQ_CALL");};


extern "C" void interrupt_copy_def();

void expanded_interrupt_init(int base)
{int i=0;
AINTC->EABASE = (0x80) | 1;
for (i=0;i<65;i++) memcpy((void*)(base+i*8),(const void *)interrupt_copy_def,8);}	

void expanded_interrupt_attach(int base, int num, int p)
{
*((int*)(base+8*(num+1)+4)) = p;
}	


void interrupt_enable(int i)
{
if (i<32)
AINTC->EINT0|=(1<<i);
else
AINTC->EINT1|=(1<<(i-32));
}

void interrupt_disable(int i)
{
if (i<32)
AINTC->EINT0&=~(1<<i);
else
AINTC->EINT1&=~(1<<(i-32));
}

uint32_t check_interrupt_flag(int i)
{uint32_t k;
	k = (i<32) ? AINTC->IRQ0 : AINTC->IRQ1;
	return( k >> (i%32));
}


void REMOVE_ALL_FLAGS() {
AINTC->FIQ0=0xFFFFFFFF;
AINTC->IRQ0=0xFFFFFFFF;
AINTC->FIQ1=0xFFFFFFFF;
AINTC->IRQ1=0xFFFFFFFF;

}
