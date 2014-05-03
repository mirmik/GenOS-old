


#ifndef        PROC_CONTEXT_H
#define        PROC_CONTEXT_H
#include "types.h"
/*--------------------------------------------------------------------------------
// Структура для хранения регистров процессора (Используется обработчиком прерываний)
//--------------------------------------------------------------------------------*/
struct context
{
  uint32_t    ds;
  uint32_t    edi, esi, ebp, esp, ebx, edx, esx, eax;
  uint32_t    eip, cs, eflags, useresp, ss;
}__attribute__((packed));

typedef    struct    context    context_t;



#define SAVE_CONTEXT() asm("pusha");
#define LOAD_CONTEXT() asm("popa");





#endif

