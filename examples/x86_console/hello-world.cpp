
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

char O_buf[1000];
Object_cache O(sizeof(command_t));

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
vkstream.rx_write(scan2ascii(inb(0x60)));
}

int send(char c)
{debug_putchar(c);
return 1;}

int main()
{	
	debug_print("HelloWorld");

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
	SEI();	
	
	registry_standart_utility();
	registry_alloc_utility();
	
	while(1) {
		//vkstream.write(vkstream.read());
		rlt.listen();
	}
	
	systemError("Programm end");
}
