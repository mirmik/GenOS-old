
//#include "video_page.h"
#include "debug/debug.h"
#include "prototype/Stream.h"
#include "strm/StrmDebug.h"
#include "delay.h"
//#include "video_page.h"
#include "genoslib.h"
#include "cpu_register.h"
#include "abstract_irq/abstract_irq.h"
Stream* stdio = &dbgio; 

char ait[4096];

void kekeke(){dpr("Mirmik"); while(1);}
void kekeke2(interrupt_info_t *info){dpr("Mirmik"); while(1);}

int main()
{//asm("int $31");
	
pr(abstract_irq_table_size(256));
//while(1);
abstract_irq_init(ait,256);
abstract_irq_attach(0, kekeke);
abstract_irq_debug_attach(1, kekeke2);
debug_print_dump(ait, 256);
asm("int $29");
dpr_inthex(5/0);
}
