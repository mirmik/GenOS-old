
#include "hardware.h"
#include "interrupts.h"
#include "string.h"
uint32_t uart0_irq,timer1_irq,timer0_irq;


extern void ISR_INTRETURN();
extern void ISR_TINT0();
extern void ISR_TINT1();
extern void ISR_UART0();


extern byte _int_vect_table_for_copy_h;

void irq_link()
{
memcpy((void*)0x04,&_int_vect_table_for_copy_h,0x40);

expanded_interrupt_init(0x80);
expanded_interrupt_attach(0x80, INTRETURN, (int)ISR_INTRETURN);
//expanded_interrupt_attach(0x80, TINT0, (int)ISR_TINT0);
//expanded_interrupt_attach(0x80, TINT1, (int)ISR_TINT1);

// Приоритеты прерываний 
AINTC->INTPRI0=0x22222222;
AINTC->INTPRI1=0x22222222;
AINTC->INTPRI2=0x22222222;
AINTC->INTPRI3=0x22222222;
AINTC->INTPRI4=0x22222222;
AINTC->INTPRI5=0x22222222;
AINTC->INTPRI6=0x22222222;
AINTC->INTPRI7=0x22222222;
AINTC->EINT0=0;
AINTC->EINT1=0;


//Настройка приоритетов:
//interrupt_enable(TINT0);
//interrupt_enable(TINT1);
//interrupt_enable(USBINT);

AINTC->INTCTL=0;   //Стратегия обработки обычная.
}




//void ISR_TINT1(){
  //      timer1_irq++;
//IRQ_FLAG_REMOVE(TINT1);
//        };


void ISR_INTRETURN(){
//printd("RETURN_INTERRUPT");
while(1);       };

