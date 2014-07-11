#ifndef        DESCRIPTOR_TABLES_H
#define        DESCRIPTOR_TABLES_H
#include "stdint.h"

#define        PIC1_ICW1    0x11
#define        PIC1_ICW2    0x20
#define        PIC1_ICW3    0x04
#define        PIC1_ICW4    0x01

#define        PIC2_ICW1    0x11
#define        PIC2_ICW2    0x28
#define        PIC2_ICW3    0x02
#define        PIC2_ICW4    0x01

/*---------------------------------------------------
//    Запись глобальной таблицы дескрипторов (GDT)
//-------------------------------------------------*/
struct gdt_entry_struct
{
  uint16_t    limit_low;   /* Младшее слово лимита */
  uint16_t    base_low;    /* Младшее слово базы */
  uint8_t     base_middle; /* Средняя часть базы */
  uint8_t     access;      /* Байт доступа */
  uint8_t     granularity; /* Байт гранулярности */
  uint8_t     base_high;   /* Старшая часть базы */
 
}__attribute__((packed));

typedef    struct    gdt_entry_struct    gdt_entry_t;

/*---------------------------------------------------
//  Структура с указателями на GDT
//-------------------------------------------------*/
struct gdt_ptr_struct
{
  uint16_t    limit;
  uint32_t    base;
 
}__attribute__((packed));

typedef    struct    gdt_ptr_struct    gdt_ptr_t;

/* Инициализация таблиц дескрипторов */
void init_descriptor_tables(void);




//****************IDT

/*------------------------------------------------
// Запись в таблице дескрипторов прерываний (IDT)
//----------------------------------------------*/
struct idt_entry_struct
{
  uint16_t    base_low;  /* Младшее слово адреса обработчика */
  uint16_t    selector;  /* Селектор сегмента ядра */
  uint8_t     allways0;  /* Всегда нули */
  uint8_t     flags;     /* Байт флагов доступа */
  uint16_t    base_high; /* Старшее слово адреса обработчика */
 
}__attribute__((packed));

typedef    struct    idt_entry_struct    idt_entry_t;

/*----------------------------------------------
// Структура указателей размещения IDT
//--------------------------------------------*/
struct    idt_ptr_struct
{

  uint16_t    limit; /* Размер таблицы IDT*/
  uint32_t    base;  /* Адрес первой записи IDT */
 
}__attribute__((packed));

typedef    struct    idt_ptr_struct idt_ptr_t;


/* Обработчики прерываний процессора */
extern "C" void isr0(void);
extern "C" void isr1(void);
extern "C" void isr2(void);
extern "C" void isr3(void);
extern "C" void isr4(void);
extern "C" void isr5(void);
extern "C" void isr6(void);
extern "C" void isr7(void);
extern "C" void isr8(void);
extern "C" void isr9(void);
extern "C" void isr10(void);
extern "C" void isr11(void);
extern "C" void isr12(void);
extern "C" void isr13(void);
extern "C" void isr14(void);
extern "C" void isr15(void);
extern "C" void isr16(void);
extern "C" void isr17(void);
extern "C" void isr18(void);
extern "C" void isr19(void);
extern "C" void isr20(void);
extern "C" void isr21(void);
extern "C" void isr22(void);
extern "C" void isr23(void);
extern "C" void isr24(void);
extern "C" void isr25(void);
extern "C" void isr26(void);
extern "C" void isr27(void);
extern "C" void isr28(void);
extern "C" void isr29(void);
extern "C" void isr30(void);
extern "C" void isr31(void);
extern "C" void isr32(void);
extern "C" void isr33(void);
extern "C" void isr34(void);
extern "C" void isr35(void);
extern "C" void isr36(void);
extern "C" void isr37(void);
extern "C" void isr38(void);
extern "C" void isr39(void);
extern "C" void isr40(void);
extern "C" void isr41(void);
extern "C" void isr42(void);
extern "C" void isr43(void);
extern "C" void isr44(void);
extern "C" void isr45(void);
extern "C" void isr46(void);
extern "C" void isr47(void);
#endif
