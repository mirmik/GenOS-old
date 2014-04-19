#ifndef INT_TABLE_H
#define INT_TABLE_H


#define INTRETURN -1
#define TINT0 32
#define TINT1 33
#define UART0INT 40
#define USBINT 12




void expanded_interrupt_init(int base);
void expanded_interrupt_attach(int base, int num, int p);
void interrupt_enable(int i);
void interrupt_disable(int i);

uint32_t check_interrupt_flag(int i);












#endif
