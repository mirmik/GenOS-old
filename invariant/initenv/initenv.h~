#include "debug_print.h"
#include "error.h"



extern unsigned long __preinit_array_start;
extern unsigned long __preinit_array_end;
extern unsigned long __init_array_start;
extern unsigned long __init_array_end;
extern unsigned long _ctor_start;
extern unsigned long _ctor_end;
extern unsigned long __fini_array_start;
extern unsigned long __fini_array_end;
extern unsigned int _text_begin;
extern unsigned int _text_end;
extern unsigned int _data_begin;
extern unsigned int _data_end;
extern unsigned int _bss_begin;
extern unsigned int _bss_end;

extern "C" volatile void initenv_cpp_global_constructors();
extern "C" volatile void initenv_bss_clean();
extern "C" void initenv_sections_info();
extern "C" void initenv_bss_test();
