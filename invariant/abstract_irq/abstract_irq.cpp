
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "abstract_irq.h"
#include "debug_print.h"
#include "error.h"
abstract_irq_handler * abstract_irq_table; 
uint8_t abstract_irq_status=0;
void abstract_StubISR(interrupt_info_t* info){
dpr(">>AIC_UNDEFINED_IRQ: irq_num:"); dpr_inthex((unsigned int)(info->int_num));dln
systemError("abstract_irq_controller_StubIRQ");
};


size_t abstract_irq_table_size(unsigned int n)
{
	return(sizeof(abstract_irq_handler) * n);
}

void abstract_irq_init(void* table, unsigned int n)
{
	abstract_irq_table = (abstract_irq_handler*) table;
	memset(table,0,n*sizeof(abstract_irq_handler));
	for(int i=0;i<n;i++) (abstract_irq_table + i) -> func = (void*)abstract_StubISR; 
	for(int i=0;i<n;i++) (abstract_irq_table + i) -> type = DEBUG; 
	abstract_irq_status = 1;
}

void abstract_irq_controller(interrupt_info_t info)
{
if (abstract_irq_status == 0) systemError("aic has been called, but not init");
uint32_t num = info.int_num;
(abstract_irq_table+num)->irq_count++;
platform_abstract_irq_handler(&info);
((aic_func)((abstract_irq_table+num)->func))(&info);
}

void abstract_irq_debug_attach(uint32_t n,aic_func func)
{
(abstract_irq_table + n) -> func = (void*)func;
(abstract_irq_table + n) -> type = DEBUG;
}

void abstract_irq_attach(uint32_t n,void (*func)())
{
(abstract_irq_table + n) -> func = (void*)func; 
(abstract_irq_table + n) -> type = NORMAL; 
}
