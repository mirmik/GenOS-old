



#ifndef DELAY_H
#define DELAY_H

#include "inttypes.h"

void delay (uint32_t d);

extern "C" volatile void delay_cpu (uint32_t d);













#endif
