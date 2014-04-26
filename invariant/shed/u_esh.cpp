

#include "shed/u_esh.h"

void sh_timer_t::restart() {start=millis();}


//***************************************************Основной цикл*******************************
void TSH::start()
{
	while(1)										
	{
	loop:
	uint64_t m = millis();
	
	sh_timer_t* tP,*next;
	list_for_each_entry_safe(tP,next,&timer_head,list)
		{
			if (m-(tP->start) >= tP->interval)	
			{
			if (tP->task == (void(*)(void))-1) return;
			tP->task();						
			if (tP->status==REPEAT) 
			{tP->restart();}
			else {deleteTimer(tP);}	
			goto loop;
			}			
		}		
	idle();
	}														
	
}
	
//*********************************************************************************
//функция останова.
void TSH::stop(void)
{newTimer((void(*)())-1,0,ONCE);
}
//*********************************************************************************

//*******************Timer manager является связным списком*****************************************
sh_timer_t* TSH::newTimer(void (*task) (void),unsigned int timer,uint8_t status)
{
uint64_t m=millis();
timercount++;
	//if (timercount > TimerPANIC)  {while(1);}
	sh_timer_t* tP=(sh_timer_t*)alloc->allocate(sizeof(sh_timer_t));
	new (tP) sh_timer_t;
	list_add(&tP->list,&timer_head);	
	tP->start=m;
	tP->interval=timer;
	tP->task=task;
	tP->status=status;
	//coreError(223);
	return (tP);
	
}


	void TSH::deleteTimer(sh_timer_t* tPext)
	{
	list_del(&tPext->list);
	alloc->deallocate(tPext);
	}
	
	
	void TSH::deleteAllTimer()
	{ sh_timer_t* tP,*next;
	list_for_each_entry_safe(tP,next,&timer_head,list)
		{
		deleteTimer(tP);
		}
	}
//***************************************************************************
	
	
	
	
	//**********************constructor*****************
TSH::TSH(void(*c)(void),Allocator_p* b)
{	
timercount=0;
	idle=c;
	INIT_LIST_HEAD(&timer_head);
	alloc = b;
}
