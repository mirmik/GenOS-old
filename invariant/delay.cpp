
#include "delay.h"
#include "platform.h"

void delay (uint32_t d)
{
uint64_t m=millis()+d;
while (millis()<m); 	
}
