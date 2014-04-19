
#include "init.h"
#include "int_macro.h"
#include "debug_serial.h"
#include "platform.h"
#include "delay.h"


// BEGIN C++ support (1/2)
extern unsigned long __preinit_array_start;
extern unsigned long __preinit_array_end;
extern unsigned long __init_array_start;
extern unsigned long __init_array_end;
extern unsigned long _ctor_start;
extern unsigned long _ctor_end;
extern unsigned long __fini_array_start;
extern unsigned long __fini_array_end;



static void call_constructors(unsigned long *start, unsigned long *end) __attribute__((noinline));
static void call_constructors(unsigned long *start, unsigned long *end)
{
  unsigned long *i;
  void (*funcptr)();
  for ( i = start; i < end; i++)
  {
    funcptr=(void (*)())(*i);
    funcptr();
  }
}
// END C++ support (1/2)

//extern void hmain();
extern int main();

extern unsigned long _bss_start;
extern unsigned long _bss_end;

extern "C" void boot2(){
IRQ_D();
	dln
printd("memset\r\n");
delay_cpu(10);
  for (int i = (int) _bss_start; i < (int)_bss_end; i++)
  {
    *((char*) i)=0;
  }


	dln
printd("boot2\r\n");
delay_cpu(10);

debug_serial_printhex_int((int)&__preinit_array_start);dln
debug_serial_printhex_int((int)&__preinit_array_end);dln
debug_serial_printhex_int((int)&__init_array_start);dln
debug_serial_printhex_int((int)&__init_array_end);dln
debug_serial_printhex_int((int)&_ctor_start);dln
debug_serial_printhex_int((int)&_ctor_end);dln


// BEGIN C++ support (2/2)
  //Call C++ global constructors
  call_constructors(&__preinit_array_start, &__preinit_array_end);
  call_constructors(&__init_array_start, &__init_array_end);
 call_constructors(&_ctor_start, &_ctor_end);
  // END C++ support (2/2)

dln
printd("callconstrend\r\n");
delay_cpu(10);
	second_init();

	drivers_init();
	main();
	
	systemError("MAIN FUNCTION END. Kernel bewilderment :)");	
}
