 /*-------------------------------------------------
// Макрос для обработчика без возврата кода ошибки
//-----------------------------------------------*/
.macro ISR_NOERRCODE isr_num

.global    isr\isr_num

isr\isr_num:

    cli                     /* Запрет всех прерываний */
    push    $0              /* Проталкиваем 0 в стек */
                            /* этот ноль - фиктивный код ошибки */
    push    $\isr_num       /* Сохраняем в стек номер прерывания */
    jmp    isr_common_stub  /* Передаем управление обработчику */
   
.endm
   
/*-----------------------------------------------------------
// Макрос для обработчика прерывания с возвратом кода ошибки
//---------------------------------------------------------*/
.macro ISR_ERRCODE isr_num

.global    isr\isr_num

isr\isr_num:

    cli                     /* Запрет всех прерываний */
    push    $\isr_num       /* Номер прерывания  - в стек */
    jmp    isr_common_stub  /* Переходим к обработчику */
   
.endm

/*-------------------------------------------------
//    Обработчики на первые 32 прерывания
//-----------------------------------------------*/
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 32
ISR_NOERRCODE 33
ISR_NOERRCODE 34
ISR_NOERRCODE 35
ISR_NOERRCODE 36
ISR_NOERRCODE 37
ISR_NOERRCODE 38
ISR_NOERRCODE 39
ISR_NOERRCODE 40
ISR_NOERRCODE 41
ISR_NOERRCODE 42
ISR_NOERRCODE 43
ISR_NOERRCODE 44
ISR_NOERRCODE 45
ISR_NOERRCODE 46
ISR_NOERRCODE 47

/*-------------------------------------------------
// Общая части обработчика прерываний
//-----------------------------------------------*/
.extern isr_handler

isr_common_stub:

      pusha                /* Проталкиваем в стек все регистры */
                           /* общего назначения (РОН) */
   
      mov    %ds, %ax      /* Спасаем в стеке селектор */ 
      push   %eax          /* сегмента данных */
     
      mov    $0x10, %ax    /* Загружаем сегмент данных ядра */
      mov    %ax, %ds
      mov    %ax, %es
      mov    %ax, %fs
      mov    %ax, %gs
     
//      call   isr_handler   /* Вызываем наш обработчик */
     call abstract_irq_controller /* Вызываем абстрактный контроллер GenOS*/
     
      pop    %eax          /* Восстанавливаем оригинальный */
      mov    %ax, %ds      /* селектор сегмента данных */
      mov    %ax, %es
      mov    %ax, %fs
      mov    %ax, %gs
     
      popa                 /* Выталкиваем РОН из стека */
      add    $8, %esp      /* Убираем из стека код ошибки */
                           /* и помещаем туда номер ISR */
      sti                  /* Вновь разрешаем все прерывания */
      iret                                /* Возвращаемся из обработчика */
                           /* при этом из стека выталкиваются */
                           /* значения регистров CS, EIP, EFLAGS, */
                           /* SS и ESP */
