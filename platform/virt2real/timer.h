#ifndef TIME_H
#define TIME_H

#include "types.h"
#include <inttypes.h>

uint64_t micros();
volatile uint64_t millis();
volatile uint64_t timer0_state();
volatile void init_TIMER0();
volatile void DEVICE_TIMER0Start();









#endif
