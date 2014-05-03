#include "debug/debug.h"
#include "platform.h"
#include "delay.h"
#include "error/error.h"

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
	  
	  debug_print("call constr:");
	debug_printhex_int32((int)i);dln;

    funcptr=(void (*)())(*i);
    funcptr();
  }
}
// END C++ support (1/2)

//extern void hmain();
extern int boot3();
extern unsigned int _text_begin;
extern unsigned int _text_end;
extern unsigned int _data_begin;
extern unsigned int _data_end;
extern unsigned int _bss_begin;
extern unsigned int _bss_end;

extern "C" void boot2(){
printd("GenOS boot2 function successful load\r\n");
printd("Section info:\r\n");
printd("_text_begin :"); dpr_inthex((int)&_text_begin);dln;
printd("_text_end   :"); dpr_inthex((int)&_text_end);dln;
printd("_data_begin :"); dpr_inthex((int)&_data_begin);dln;
printd("_data_end   :"); dpr_inthex((int)&_data_end);dln;
printd("_bss_begin  :"); dpr_inthex((int)&_bss_begin);dln;
printd("_bss_end    :"); dpr_inthex((int)&_bss_end);dln;


printd("bss clean...   ");
//delay_cpu(10);

  for (unsigned int i = (unsigned int)&_bss_begin; i < (unsigned int)&_bss_end; i++)
  {
    *((char*) i)=0;
  }
printd("OK\r\n");
//delay_cpu(10);

printd("Constructor info:\r\n");
printd("__preinit_array_start:");dpr_inthex((int)&__preinit_array_start);dln
printd("__preinit_array_end  :");dpr_inthex((int)&__preinit_array_end);dln
printd("__init_array_start   :");dpr_inthex((int)&__init_array_start);dln
printd("__init_array_end     :");dpr_inthex((int)&__init_array_end);dln
printd("_ctor_start          :");dpr_inthex((int)&_ctor_start);dln
printd("_ctor_end            :");dpr_inthex((int)&_ctor_end);dln

printd("constr call:\r\n");
// BEGIN C++ support (2/2)
  //Call C++ global constructors
  call_constructors(&__preinit_array_start, &__preinit_array_end);
  call_constructors(&__init_array_start, &__init_array_end);
 call_constructors(&_ctor_start, &_ctor_end);
  // END C++ support (2/2)
printd("constr call OK\r\n");

delay_cpu(10);
//	second_init();


//	drivers_init();
printd("Call boot3 function...");

	boot3();
	
systemError("BOOT2 FUNCTION END. Kernel bewilderment :)");	
}
