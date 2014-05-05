
#include "initenv/initenv.h"
#include "prototype/Stream.h"
#include "platform.h"
#include "abstract_irq/abstract_irq.h"
#include "strm/DBStream.h"
#include "keyscan.h"
#include "charqueue/staticring.h"
#include "allocator/allocator.h"
#include "readline/readline.h"
#include "readline/rl_terminal.h"
#include "utility.h"
#include "intcom/command_list.h"
#include "pci_search.h"
#include "keyboard_scan/keyboard_scan.h"

#include "video_page_command.h"

char O_buf[1000];
Object_cache O(sizeof(command_t));

<<<<<<< HEAD
Keyscan key;
=======
extern "C" void __cxa_pure_virtual() { while (1); }

>>>>>>> 878b7e1f524b31ee4cf5b7e3d54daba1032233c6
Allocator_p * stdalloc=&O;
Stream* stdio;
staticring_t rx,tx;
DBStream vkstream(&rx,&tx);
readline_t rl;
rl_terminal rlt(&vkstream,&rl);

char aic[0x900];

void DoNothing(){};
void KeyboardHandler()
{
key.scan2ascii(inb(0x60));
}

void KeyboardHandler_keyscan()
{
unsigned char i = inb(0x60);
dpr_inthex(i); dln;
}

int send(char c)
{debug_putchar(c);
return 1;}

void keyscan_init()
{
abstract_irq_attach(0x21, KeyboardHandler_keyscan);
}

video_page_command v;
void test()
{v.putchar('G');}

extern void kmain();
int main()
{	
	debug_print("HelloWorld");
//while(1);
	//Enviroment Init
	initenv_sections_info();
	initenv_bss_test();
	initenv_bss_clean();
	initenv_cpp_global_constructors();
	//Platform init
	platform_init();
	//
	abstract_irq_init(aic,256);
	abstract_irq_attach(0x20, DoNothing);
	abstract_irq_attach(0x21, KeyboardHandler);
	vkstream.send=send;
	O.engage(O_buf,1000);
	key.out_strm = &vkstream;
	
	SEI();	
	
	registry_standart_utility();
	registry_alloc_utility();
	command("pciscan",kmain);
	command("keyscan",keyscan_init);
	command("test",test);
	while(1) {
		//vkstream.write(vkstream.read());
		rlt.listen();
	}
	
	systemError("Programm end");
}
