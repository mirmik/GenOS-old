

#ifndef ABSTRACT_IRQ_H
#define ABSTRACT_IRQ_H

#include "isr.h" 

enum{
NORMAL,
DEBUG};

typedef void (*aic_func) (interrupt_info_t *info);

extern "C" void abstract_irq_controller(interrupt_info_t info);
size_t abstract_irq_table_size(uint n);
void abstract_irq_init(void* table, uint n);
void abstract_irq_attach(uint32_t n,void (*func)());
void abstract_irq_debug_attach(uint32_t n,aic_func func);


struct abstract_irq_handler
{
void* func;
uint32_t irq_count;
uint8_t type;
}__attribute__((packed));
	
extern abstract_irq_handler * abstract_irq_table;
	
#endif
