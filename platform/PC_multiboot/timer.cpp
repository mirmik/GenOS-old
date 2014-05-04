

#include "cpu.h"
#include    "timer.h"
#include    "isr.h"

/*----------------------------------------------
// Инициализация таймера 
//--------------------------------------------*/
void init_timer(uint32_t frequency)
{
 
  uint32_t divisor; /* Делитель частоты */
  uint8_t low;      /* Младший байт делителя */
  uint8_t high;     /* Старший байт делителя */
 
  /* Регистрируем в системе обработчик для IRQ0 */
 // register_interrupt_handler(IRQ0, &timer_callback);
 
  /* Расчитываем делитель по заданной частоте */
  divisor = 1193180/frequency;
 
  /* Задаем режим работы таймера */
  outb(0x43, 0x36);
 
  /* Разбираем делитель на байты */
  low = (uint8_t) (divisor & 0xFF);
  high = (uint8_t) ( (divisor >> 8) & 0xFF );
 
  /* Отсылаем делитель в канал 0 PIT */
  outb(0x40, low);
  outb(0x40, high); 
}
