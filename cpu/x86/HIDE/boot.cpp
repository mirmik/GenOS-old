



#include "boot.h"


extern "C" __attribute__((naked)) void boot()
{
asm("ljmp $0,$0x600");
while(1);	
}
