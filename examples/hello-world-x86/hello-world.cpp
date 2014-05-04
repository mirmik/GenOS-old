
//#include "video_page.h"
#include "debug/debug.h"
#include "prototype/Stream.h"
#include "strm/StrmDebug.h"
#include "delay.h"
//#include "video_page.h"
#include "genoslib.h"
#include "cpu_register.h"
#include "abstract_irq/abstract_irq.h"
#include "timer.h"
#include "strm/DBStream.h"
#include "charqueue/staticring.h"

staticring_t r1,r2;
DBStream vkstream(&r1,&r2);
Allocator_p* stdalloc=0; 
Stream* stdio = &dbgio; 


char ait[4096];
void DoNothing(){};
void kekeke(){//abstract_irq_handler* a=abstract_irq_table+0x20;
	//pr(a->irq_count);dpr(":");
	vkstream.rx_write(scan2ascii(inb(0x60)));
	//vkstream.rx_write(scan2ascii(inb(0x61)));
	}
void kekeke2(interrupt_info_t *info){dpr("Mirmik");  while(1);}

int main()
{//asm("int $31");
pr(abstract_irq_table_size(256));
//while(1);
abstract_irq_init(ait,256);
abstract_irq_attach(0x21, kekeke);
abstract_irq_attach(0x20, DoNothing);
init_timer(1000);
//abstract_irq_debug_attach(1, kekeke2);
debug_print_dump(ait, 256);
asm volatile("sti");
//asm("int $29");
//dpr_inthex(5/0);
int i;
while(1) {
	i = vkstream.read();
	if (i!=-1) {stdio->print(i,16);dln}
	}
}
