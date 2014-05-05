
#include "debug/debug.h"
#include "error/error.h"

#include "initenv/initenv.h"

static void volatile call_constructors(unsigned long *start, unsigned long *end) __attribute__((noinline));
static void volatile call_constructors(unsigned long *start, unsigned long *end)
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

extern "C" volatile void initenv_cpp_global_constructors(){
printd(">>CALL GLOBAL CONSTRUCTORS\r\n");
printd("constr call:\r\n");
 call_constructors(&__preinit_array_start, &__preinit_array_end);
 call_constructors(&__init_array_start, &__init_array_end);
 call_constructors(&_ctor_start, &_ctor_end);
printd("constr call OK\r\n");

printd("global constructors succesfualy called...\r\n");
}




extern "C" volatile void initenv_bss_clean(){
unsigned int i;
printd(">>BSS_CLEAN...   ");
  for (i = (unsigned int)&_bss_begin; i < (unsigned int)&_bss_end; i++)
  {
    *((char*) i)=0;
  }
printd("OK\r\n");
}

extern "C" void initenv_bss_test(){
int b=0;int t=0;
printd(">>BSS_TEST:\r\n"); 
printd("bss_length:"); dpr_inthex((unsigned int)&_bss_end-(unsigned int)&_bss_begin);dln;
printd("scan bss_section (all nonNull bytes has been printed) .......\r\n"); 
for (unsigned int i = (unsigned int)&_bss_begin; i < (unsigned int)&_bss_end; i++)
  {
	t++;
    if (*((char*) i)!=0) {dpr_inthex(i);printd(":");debug_printhex_byte(*((char*) i));dln; b++;} 
  }
printd("************************* end scan\r\ntotal scaned:"); dpr_inthex(t);printd("\r\ntotal nonNull:"); dpr_inthex(b); dln;
printd("bss_test_end\r\n"); 
}


extern "C" void initenv_sections_info(){

printd(">>SECTIONS AND CONSTRUCTORS INFO:\r\n");
printd("_text_begin :"); dpr_inthex((int)&_text_begin);dln;
printd("_text_end   :"); dpr_inthex((int)&_text_end);dln;
printd("_data_begin :"); dpr_inthex((int)&_data_begin);dln;
printd("_data_end   :"); dpr_inthex((int)&_data_end);dln;
printd("_bss_begin  :"); dpr_inthex((int)&_bss_begin);dln;
printd("_bss_end    :"); dpr_inthex((int)&_bss_end);dln;
printd("Constructor info:\r\n");
printd("__preinit_array_start:");dpr_inthex((int)&__preinit_array_start);dln
printd("__preinit_array_end  :");dpr_inthex((int)&__preinit_array_end);dln
printd("__init_array_start   :");dpr_inthex((int)&__init_array_start);dln
printd("__init_array_end     :");dpr_inthex((int)&__init_array_end);dln
printd("_ctor_start          :");dpr_inthex((int)&_ctor_start);dln
printd("_ctor_end            :");dpr_inthex((int)&_ctor_end);dln
}
