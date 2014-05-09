
#include "initenv/initenv.h"
#include "prototype/Stream.h"
#include "platform.h"
#include "abstract_irq/abstract_irq.h"
//#include "strm/DBStream.h"
#include "keyscan.h"
#include "charqueue/staticring.h"
#include "allocator/allocator.h"
#include "readline/readline.h"
#include "readline/rl_terminal.h"
#include "utility.h"
#include "intcom/command_list.h"
#include "pci_search.h"
#include "keyboard_scan/keyboard_scan.h"
#include "VideoPage/VideoPage.h"
#include "VideoPage/VideoPagePrint.h"
#include "PrintTransformer/Scan2KeyCom.h"

VideoPage 		v(0xB8000,80,25);
VideoPagePrint 	vp(&v);

void OS_init();
char O_buf[10000];
Object_cache O(500);

Allocator_p * stdalloc=&O;
readline_t rl;
rl_terminal rlt(&rl,&vp);
//Keyscan key;
Scan2KeyCom s2k(&rlt);

extern "C" void __cxa_pure_virtual() { while (1); }

uint64_t tim=0;

void timerprint()
{
prln((uint32_t)millis());	
}
char aic[0x900];

Print* stdprint = &vp;
void DoNothing(){};
void KeyboardHandler()
{
s2k.scan2ascii(inb(0x60));
}

void TimerHandler()
{
tim++;
}
int a=0;
void ddd()
{
prln(a++);
}


//void KeyboardHandler_keyscan()
//{
//unsigned char i = inb(0x60);
//dpr_inthex(i); dln;
//}

//void keyscan_init()
//{
//abstract_irq_attach(0x21, KeyboardHandler_keyscan);
//}

void test()
{//v.putchar('G');
}

void clr(){v.clean();}

#include "shed/u_esh.h"
TSH sh;

extern void kmain();
int main()
{	
	
	OS_init();
	
//	O.engage(O_buf,1000);
	
	SEI();	
	O.engage(O_buf,10000);
	registry_standart_utility();
	registry_alloc_utility();
	command("pciscan",kmain);
	command("test",test);
	command("timer",timerprint);
	command("clr",clr);

vp.init();
rlt.print_prompt();
//sh.newTimer(ddd,1000,REPEAT);
//ddd();
alloca(28);
init_timer(1000);
prlnhex(sh.timer_head.next);
prlnhex(sh.timer_head.next->next);
prlnhex(sh.timer_head.next->next->next);
//prln((uint32_t)tim);
//sh.start();
	while(1) {
		sh.start();
		//vkstream.write(vkstream.read());
//		rlt.listen();
	}
	
	systemError("Programm end");
}





void OS_init()
{
	debug_print("HelloWorld");
	//Enviroment Init
	initenv_sections_info();
	//delay_cpu(10000000);
	initenv_bss_test();
	//delay_cpu(10000000);
	initenv_bss_clean();
	//delay_cpu(10000000);
	initenv_cpp_global_constructors();
	//delay_cpu(10000000);
	//Platform init
	platform_init();
	//delay_cpu(10000000);
	//abstract_irq_system_init
	abstract_irq_init(aic,256);
	abstract_irq_attach(0x20, TimerHandler);
	abstract_irq_attach(0x21, KeyboardHandler);
	//delay_cpu(10000000);
}
