


#ifndef mvirt_leds_h
#define mvirt_leds_h


#include "hardware.h"


#define green_led_on() GPIO_BANK45->OUT_DATA |= (1<<9);
#define red_led_on() GPIO_BANK45->OUT_DATA |= (1<<10);


#define green_led_off() GPIO_BANK45->OUT_DATA &= ~(1<<9);
#define red_led_off() GPIO_BANK45->OUT_DATA &= ~(1<<10);






#endif
