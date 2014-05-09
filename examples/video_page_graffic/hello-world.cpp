
#include "initenv/initenv.h"
#include "prototype/Stream.h"
#include "platform.h"
#include "VideoPage/VideoPage.h"
#include "VideoPage/VideoPagePrint.h"

VideoPage 		v(0xB8000,80,25);
VideoPagePrint 	vp(&v);

extern "C" void __cxa_pure_virtual() { while (1); }

void OS_init();
Print* stdout;

extern void kmain();
int main()
{	
	OS_init();

	vp.init();

	vp.println("kekeke\tGenOS here... In your mind...");
	vp.println("keke\tke\tk");

	v.setbox(10,10,v.w-11,v.h-10,'#',0x3);
	v.setbox(11,11,v.w-12,v.h-11,' ',0x3);
	vp.x=((10+v.w-11)/2 - 5);
	vp.y=((10+v.h-10)/2);
	vp.print("HelloWorld");

while(1) {}
	
	systemError("Programm end");
}

void OS_init()
{
	debug_print("HelloWorld");
	initenv_sections_info();
	initenv_bss_test();
	initenv_bss_clean();
	initenv_cpp_global_constructors();
}
