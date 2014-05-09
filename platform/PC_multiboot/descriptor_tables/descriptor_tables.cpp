
#include    "descriptor_tables.h"
#include "types.h"
#include "genoslib.h"
#include "debug/debug.h"

/* Загрузка регистра GDT */
extern "C" void gdt_flush(uint32_t);
/* Инициализация таблицы GDT */
static void init_gdt(void);
/* Создание записи в GDT */
static void gdt_set_gate(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);
/* Сама глобальная таблица дескрипторов */
gdt_entry_t    gdt_entries[5];
/* Структура указателей на GDT */
gdt_ptr_t      gdt_ptr;



void gdt_set_gate(uint32_t num,    /* Номер сегмента */
                  uint32_t base,   /* База сегмента */
                  uint32_t limit,  /* Лимит сегмента */
                  uint8_t access,  /* Байт доступа */
                  uint8_t gran)    /* Байт гранулярности */
{
  /* Заполняем поля базы */
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF; 
  /* Заполняем поля лимита */
  gdt_entries[num].limit_low = (limit & 0xFFFF);
  gdt_entries[num].granularity = (limit >> 16) & 0xF;   
  /* Заполняем байты доступа и гранулярности */
  gdt_entries[num].granularity |= gran & 0xF0;
  gdt_entries[num].access = access;   
}




 /*---------------------------------------------------
// Инициализация глобальной таблицы дескрипторов
//-------------------------------------------------*/
void init_gdt(void)
{
  /* Определяем размер GDT */
  gdt_ptr.limit = (sizeof(gdt_entry_t)*5) - 1;
  /* Вычисляем адрес размещения GDT в памяти*/
  gdt_ptr.base = (uint32_t) &gdt_entries;
 
  /* Нулевой дескриптор */
  gdt_set_gate(0, 0, 0, 0, 0);   
  /* Дескриптор кода ядра  (ring 0)*/
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  /* Дескриптор данных ядра (ring 0)*/  
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  /* Дескриптор кода пользовательского режима (ring 3)*/ 
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  /* Дескриптор данных пользовательского режима (ring 3)*/  
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   

  /* Включаем сегментную адресацию  */
  gdt_flush( (uint32_t) &gdt_ptr);
}



//**********************************************IDT



 /* Таблица дескрипторов прерываний */
idt_entry_t  idt_entries[256];
/* Структура указателей размещения IDT */
idt_ptr_t    idt_ptr;

/* Загрузка рагистра IDTR - внешняя ассемблерная функция */
extern "C" void idt_flush(uint32_t);
/* Инициализация IDT */
static void init_idt(void);
/* Добавление записи в таблицу IDT */
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);



/*-----------------------------------------------
// Создание записи в IDT
//---------------------------------------------*/
void idt_set_gate(uint8_t num,       /* номер прерывания */
                  uint32_t base,     /* адрес обработчика */
                  uint16_t selector, /* селектор сегмента ядра */
                  uint8_t flags)     /* флаги доступа */
{
  idt_entries[num].base_low = base & 0xFFFF;
  idt_entries[num].base_high = (base >> 16) & 0xFFFF;
 
  idt_entries[num].selector = selector;
  idt_entries[num].allways0 = 0;
 
  idt_entries[num].flags = flags; /* | 0x60 - для пользовательского */
                                  /* режима */ ;
}

#include "error/error.h"
void StubISR(){
systemError("StubIRQ");
	};

/*-----------------------------------------------
// Инициализация IDT 
//---------------------------------------------*/
 void init_idt(void)
{
  /* Инициализация структуры указателя размером и адресом IDT */
  idt_ptr.limit = sizeof(idt_entry_t)*256 - 1;
  idt_ptr.base = (uint32_t) &idt_entries;
 
  /* Очистка памяти */
  memset(&idt_entries, 0, sizeof(idt_entry_t)*256);   
 
  /* Инициализация обоих PIC */
  outb(0x20, PIC1_ICW1); /* ICW1 */
  outb(0xA0, PIC2_ICW1);

  outb(0x21, PIC1_ICW2); /* ICW2 */
  outb(0xA1, PIC2_ICW2);

  outb(0x21, PIC1_ICW3); /* ICW3 */
  outb(0xA1, PIC2_ICW3);

  outb(0x21, PIC1_ICW4); /* ICW4 */
  outb(0xA1, PIC2_ICW4);
 
  /* Разрешаем прерывания на всех линиях */
  outb(0x21, 0x00);      /* OCW1 */
  outb(0xA1, 0x00);
 
  /* Создание записей в таблице на первые 32 прерывания */ 
  for(int i=0;i<256;i++)
  idt_set_gate(i, (uint32_t) StubISR, 0x08, 0x8E);
  idt_set_gate(0, (uint32_t) isr0, 0x08, 0x8E);
  idt_set_gate(1, (uint32_t) isr1, 0x08, 0x8E);
  idt_set_gate(2, (uint32_t) isr2, 0x08, 0x8E);
  idt_set_gate(3, (uint32_t) isr3, 0x08, 0x8E);
  idt_set_gate(4, (uint32_t) isr4, 0x08, 0x8E);
  idt_set_gate(5, (uint32_t) isr5, 0x08, 0x8E);
  idt_set_gate(6, (uint32_t) isr6, 0x08, 0x8E);
  idt_set_gate(7, (uint32_t) isr7, 0x08, 0x8E);
  idt_set_gate(8, (uint32_t) isr8, 0x08, 0x8E);
  idt_set_gate(9, (uint32_t) isr9, 0x08, 0x8E);
  idt_set_gate(10, (uint32_t) isr0, 0x08, 0x8E);
  idt_set_gate(11, (uint32_t) isr11, 0x08, 0x8E);
  idt_set_gate(12, (uint32_t) isr12, 0x08, 0x8E);
  idt_set_gate(13, (uint32_t) isr13, 0x08, 0x8E);
  idt_set_gate(14, (uint32_t) isr14, 0x08, 0x8E);
  idt_set_gate(15, (uint32_t) isr15, 0x08, 0x8E);
  idt_set_gate(16, (uint32_t) isr16, 0x08, 0x8E);
  idt_set_gate(17, (uint32_t) isr17, 0x08, 0x8E);
  idt_set_gate(18, (uint32_t) isr18, 0x08, 0x8E);
  idt_set_gate(19, (uint32_t) isr19, 0x08, 0x8E);
  idt_set_gate(20, (uint32_t) isr20, 0x08, 0x8E);
  idt_set_gate(21, (uint32_t) isr21, 0x08, 0x8E);
  idt_set_gate(22, (uint32_t) isr22, 0x08, 0x8E);
  idt_set_gate(23, (uint32_t) isr23, 0x08, 0x8E);
  idt_set_gate(24, (uint32_t) isr24, 0x08, 0x8E);
  idt_set_gate(25, (uint32_t) isr25, 0x08, 0x8E);
  idt_set_gate(26, (uint32_t) isr26, 0x08, 0x8E);
  idt_set_gate(27, (uint32_t) isr27, 0x08, 0x8E);
  idt_set_gate(28, (uint32_t) isr28, 0x08, 0x8E);
  idt_set_gate(29, (uint32_t) isr29, 0x08, 0x8E);
  idt_set_gate(30, (uint32_t) isr30, 0x08, 0x8E);
  idt_set_gate(31, (uint32_t) isr31, 0x08, 0x8E);
 //Дескрипторы для IRQ
  idt_set_gate(32, (uint32_t) isr32, 0x08, 0x8E);
  idt_set_gate(33, (uint32_t) isr33, 0x08, 0x8E);
  idt_set_gate(34, (uint32_t) isr34, 0x08, 0x8E);
  idt_set_gate(35, (uint32_t) isr35, 0x08, 0x8E);
  idt_set_gate(36, (uint32_t) isr36, 0x08, 0x8E);
  idt_set_gate(37, (uint32_t) isr37, 0x08, 0x8E);
  idt_set_gate(38, (uint32_t) isr38, 0x08, 0x8E);
  idt_set_gate(39, (uint32_t) isr39, 0x08, 0x8E);
  idt_set_gate(40, (uint32_t) isr40, 0x08, 0x8E);
  idt_set_gate(41, (uint32_t) isr41, 0x08, 0x8E);
  idt_set_gate(42, (uint32_t) isr42, 0x08, 0x8E);
  idt_set_gate(43, (uint32_t) isr43, 0x08, 0x8E);
  idt_set_gate(44, (uint32_t) isr44, 0x08, 0x8E);
  idt_set_gate(45, (uint32_t) isr45, 0x08, 0x8E);
  idt_set_gate(46, (uint32_t) isr46, 0x08, 0x8E);
  idt_set_gate(47, (uint32_t) isr47, 0x08, 0x8E);
  
  /* Загрузка регистра IDTR */
  idt_flush((uint32_t) &idt_ptr);
}


/*---------------------------------------------
// Инициализация таблиц дескрипторов
//-------------------------------------------*/
void init_descriptor_tables(void)
{
  /* Инициализируем GDT */
  init_gdt();
  /* Инициализируем IDT */
  init_idt();
//set_bkground_color(BLACK);
debug_print("Global Descriptors Table GDT:\n");
debug_print_dump((uint32_t*) gdt_entries, 40);dln; 
debug_print("Global Descriptors Table IDT (begin):\n");
debug_print_dump((uint32_t*) idt_entries, 32);dln;
} 
