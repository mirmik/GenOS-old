
// BEGIN C++ support (1/2)
extern unsigned long __preinit_array_start;
extern unsigned long __preinit_array_end;
extern unsigned long __init_array_start;
extern unsigned long __init_array_end;
extern unsigned long _ctor_start;
extern unsigned long _ctor_end;
extern unsigned long __fini_array_start;
extern unsigned long __fini_array_end;


extern int main();

extern unsigned long _bss_start;
extern unsigned long _bss_end;


extern "C" void debug_str2();
extern "C" void PrintChar2();
extern "C" void PrintChar(char c);
extern "C" void debug_str2();


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
extern "C" void _init();extern "C" void _start();

extern "C" void boot2()
{//debug_str2();
  //for (int i = (int) _bss_start; i < (int)_bss_end; i++)
  //{
  //  *((char*) i)=0;
  //}
//debug_str2();
 
// BEGIN C++ support (2/2)
  //Call C++ global constructors
 //debug_str2();
 
//  call_constructors(&__preinit_array_start, &__preinit_array_end);
 // call_constructors(&__init_array_start, &__init_array_end);
 // call_constructors(&_ctor_start, &_ctor_end);
  // END C++ support (2/2)
//	second_init();
//PrintChar2();
//PrintChar('f');
//PrintChar('d');
	//drivers_init();
	//main();
//debug_str2();
	//systemError("MAIN FUNCTION END. Kernel bewilderment :)");	
//while(1);
asm("push %ebx");
asm("push %eax");
asm("mov %ah,0x0E");
asm("mov %bx, 7");
asm("mov %al,0x63");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("pop %eax");
asm("pop %ebx");
 for (int i = (int) _bss_start; i < (int)_bss_end; i++)
  {
  //  *((char*) i)=0;
  }

//_start();
//call_constructors(&__preinit_array_start, &__preinit_array_end);
//call_constructors(&__init_array_start, &__init_array_end);
//call_constructors(&_ctor_start, &_ctor_end);

asm("push %ebx");
asm("push %eax");
asm("mov %ah,0x0E");
asm("mov %bx, 7");
asm("mov %al,0x63");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("pop %eax");
asm("pop %ebx");


while(1);
} 
