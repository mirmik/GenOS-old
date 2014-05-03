#ifndef PLATFORM_H
#define PLATFORM_H

#include "timer.h"


#include "Stream.h"
#include "types.h"
#include <inttypes.h>
/*static volatile void delay_cpu (uint32_t d)
{volatile uint64_t dd;
	dd=d*2000;
while(1){
asm("nop");
dd--;
if ( dd == 0) return;
}
};*/

#include "hardware.h"

//#define systemError(a) {PROCESSOR_STATE_PRINT();systemError_h(a);} 

extern "C" int SPSR_REGISTER();
extern "C" int CPU_MODE();
extern "C" int STACK_POINTER();

void processor_state();

void CPU_SET(int a);
#define PROCESSOR_STATE_PRINT() \
{get_PROCESSOR(); \
processor_state(); \
get_PROCESSOR_exit();} 

#define get_PROCESSOR()  \
asm("push {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,sp,lr,pc}"); \
SPSR_REGISTER(); \
asm("push {r0}"); \
CPU_MODE();\
asm("push {r0}"); \
PROCESSOR = (PROCESSOR_t *) (STACK_POINTER()); \

#define get_PROCESSOR_exit()  \
asm("add sp, #8");
asm("pop {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,sp,lr,pc}");\

struct PROCESSOR_t
{
int CPSR;
int SPSR;
int R[13];
int SP;
int LR;
int PC;
};
extern PROCESSOR_t *PROCESSOR;

volatile void systemError_h(const char * c)__attribute__((noreturn));


#include "stdlib.h"
#define kmalloc(a) malloc(a)
#define kfree(a) free(a)





#include "leds.h"
#include "int_macro.h"
#include "debug/debug.h"

#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

extern "C" void _exit(int status); 
extern "C" int _close(int file);
extern "C" int _execve(char *name, char **argv, char **env);
extern "C" int _fork();
extern "C" int _fstat(int file, struct stat *st);
extern "C" int _getpid();
extern "C" int _isatty(int file);
extern "C" int _kill(int pid, int sig);
extern "C" int _link(char *old, char *_new);
extern "C" int _lseek(int file, int ptr, int dir);
extern "C" caddr_t _sbrk(int incr);
extern "C" int _read(int file, char *ptr, int len);
extern "C" int _stat(const char *filepath, struct stat *st);
extern "C" clock_t _times(struct tms *buf);
extern "C" int _unlink(char *name);
extern "C" int _wait(int *status);
extern "C" int _write(int file, char *ptr, int len);









#endif

