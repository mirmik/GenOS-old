


#ifndef U_ESH_H
#define U_ESH_H

#include "platform.h"
#include "types.h"
#include "linuxlist.h"
//#include "simple.h"

#include "allocator/allocator.h"
enum{
ONCE, 
REPEAT} ;


class sh_timer_t
{public:
	uint64_t start;
	uint64_t interval;
	uint8_t status;
	void (*task)(void);
	list_head list;
	void restart(); 
};


class TSH
{public:
	
	Allocator_p* alloc;
	TSH(void(*c)(void),Allocator_p* b);
	
	void (*idle)(void);
	uint8_t TimerPANIC;
	
	
	list_head timer_head;
	
	uint8_t timercount;
	
	void start(void);
	sh_timer_t* newTimer(void (*task) (void),unsigned int timer,uint8_t status);
	void stop(void);
	void deleteTimer(sh_timer_t* tPext);
	void deleteAllTimer();
	void deleteTimerPos(uint8_t i);
};

#endif
