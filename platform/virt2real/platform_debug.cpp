
#include "hardware.h"

extern "C" void debug_putchar(char c)
{
 UART0->THR=c;
 while(((UART0->LSR) & (1<<5)) ==0);
};

