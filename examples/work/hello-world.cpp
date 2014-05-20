
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
#include "genoslib.h"
#include "filtration/aperiodic.h"
#include "filtration/median3.h"
//#include "filtration/median3_t.h"

VideoPage 		v(0xB8000,80,25);
VideoPagePrint 	vp(&v);

void OS_init();
Allocator_p * stdalloc;
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

char Rmas[10000];


void reset()
{unsigned char c;
	c=inb(0x92);
	outb(0x92,c|1);
}
void clr(){vp.init();}

#include "shed/u_esh.h"
TSH sh;

AFS_filter f;
void ddd2()
{
//prln(f.calculate(1000));	
}

Linear_allocator R;
extern void kmain();
int main()
{	
	
	OS_init();
	
R.engage (Rmas,10000);

stdalloc=&R;	
	SEI();	
	registry_standart_utility();
	registry_alloc_utility();
	command("pciscan",kmain);
	command("test",test);
	command("timer",timerprint);
	command("clr",clr);
	command("reset",reset);
vp.init();
sh.newTimer(ddd2,100,REPEAT);

f.init(300,1,0.1);

median3<uint> m;
//median m;
m.init();
prln(m.calculate(2));
prln(m.calculate(10));
prln(m.calculate(3));
prln(m.calculate(4));
prln(m.calculate(3));
prln(m.calculate(2));
prln(m.calculate(1));


rlt.print_prompt();
	while(1) {
		sh.start();
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
	init_timer(1000);
}
