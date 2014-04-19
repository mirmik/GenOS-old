


#ifndef CSH_H
#define CSH_H

#include "platform.h"
#include "types.h"
#include <stdlib.h>
#include "linuxlist.h"
#include "simple.h"

#define ONCE 0
#define REPEAT 1

// Сигналы:
//#define TASKSHED 0
//#define SHEDULER 1




#define NOP 0x00			//Ничего у меня нету...
#define GO_CLB 	0x02	//Запусти меня и сними флаг
#define GO_NOCLB 0x03		//Запусти, но флаг не трож... 
#define DELETE 0x01		//Удали меня
/*
class progInterrupt_t : public ThreadedList_element
{public:
uint8_t* whatToDo;
void (*task) (void);
};
class ProgInterruptList : public ThreadedList
{public:
~ProgInterruptList(){delete_list();};
ThreadedList_element* create(){return((ThreadedList_element*) (new progInterrupt_t));};
};
*/





class sh_timer_t
{public:
	uint64_t timerStart;
	uint64_t timerValue;
	void (*task)(void);
	uint8_t taskStatus;
	list_head list;
	void restart() {timerStart=millis();}
};




class CSH_t
{public:
	CSH_t(void(*c)(void),uint8_t a,uint8_t b);
	//~CSH_t();
	
	uint64_t MaxDelay;
	
	void (*idle)(void);
	uint8_t TimerPANIC;
	uint8_t TaskOrderLength;
	
	
	list_head timer_head;
	//ProgInterruptList PL;
	//progInterrupt_t* pP;
	//TimerList TL;
	//timer_t* tP;
	typedef void (*TaskOrderMemb_t) (void) ;
	TaskOrderMemb_t * TaskOrder;
	
	uint8_t timercount;
	
	unsigned char TCL;
	unsigned char TCH;	

	void start(void);
	void newTask(void (*task) (void));
	sh_timer_t* newTimer(void (*task) (void),unsigned int timer,uint8_t status);
	void stop(void);
	void deleteTimer(sh_timer_t* tPext);
	void deleteAllTimer();

	void deleteTimerPos(uint8_t i);
	
//uint8_t	addInterrupt(void (*task) (void),uint8_t* a);
	
	
};

#endif
