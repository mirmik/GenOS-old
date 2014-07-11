

#ifndef        ISR_H
#define        ISR_H
//#include "types.h"
#include "stdint.h"
/*--------------------------------------------------------------------------------
// Структура для хранения регистров процессора (Используется обработчиком прерываний)
//--------------------------------------------------------------------------------*/
struct interrupt_info
{
  uint32_t    ds;
  uint32_t    edi, esi, ebp, esp, ebx, edx, esx, eax;
  uint32_t    int_num, err_code; /* Номер прерывания и код ошибки */
  uint32_t    eip, cs, eflags, useresp, ss;
}__attribute__((packed));

typedef    struct    interrupt_info    interrupt_info_t;

#endif

