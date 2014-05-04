#include "types.h"
#include "genoslib.h"
#include "abstract_irq/abstract_irq.h"
#include "debug/debug.h"
#include "error/error.h"
abstract_irq_handler * abstract_irq_table; 

void abstract_StubISR(interrupt_info_t* info){
dpr("abstract_irq_num:"); dpr_inthex((uint)(info->int_num));dln
systemError("abstract_irq_controller_StubIRQ");
};


size_t abstract_irq_table_size(uint n)
{
	return(sizeof(abstract_irq_handler) * n);
}

void abstract_irq_init(void* table, uint n)
{
	abstract_irq_table = (abstract_irq_handler*) table;
	memset(table,0,n*sizeof(abstract_irq_handler));
	for(int i=0;i<n;i++) (abstract_irq_table + i) -> func = (void*)abstract_StubISR; 
	for(int i=0;i<n;i++) (abstract_irq_table + i) -> type = DEBUG; 
}

void abstract_irq_controller(interrupt_info_t info)
{
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
