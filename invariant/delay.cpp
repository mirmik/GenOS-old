
#include "GenOS.h"

void delay (uint32_t d)
{
uint64_t m=millis()+d;
while (millis()<m); 	
}





volatile void delay_cpu (uint32_t d)
{volatile uint64_t dd;
	dd=d*2000;
while(1){
asm("nop");
dd--;
if ( dd == 0) return;
}
};
