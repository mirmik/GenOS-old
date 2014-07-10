

#include "shed/u_esh.h"

void sh_timer_t::restart() {start=millis();}


//***************************************************Основной цикл*******************************
void TSH::start()
{
	//while(1)										
	//{
	uint64_t m = millis();
	uint64_t mm;
	sh_timer_t* tP;
	List_it pl;
	for_all_list_obj(pl,L,tP,sh_timer_t)
		{
			if (m-(tP->start) >= tP->interval)	
			{
			if (tP->task == (void(*)(void))-1) return;
			mm=millis();
			tP->task();						
			uint64_t mmm = millis()-mm;
			if (maxdel < mmm) maxdel=mmm; 
			if (tP->status==REPEAT) 
			{tP->restart();}
			else {pl.del_obj();
			};	
			}			
		}		
	//idle();
	//}														
	
}
	/*
//*********************************************************************************
//функция останова.
void TSH::stop(void)
{newTimer((void(*)())-1,0,ONCE);
}
//*********************************************************************************
*/
//*******************Timer manager является связным списком*****************************************
sh_timer_t* TSH::newTimer(void (*task) (void),unsigned int timer,uint8_t status)
{
uint64_t m=millis();
	//if (timercount > TimerPANIC)  {while(1);}
	//List_it pl;
	
	sh_timer_t* tP = new sh_timer_t;
	
	tP->start=m;
	tP->interval=timer;
	tP->task=task;
	tP->status=status;
	L.add(tP);
	//coreError(223);
	return (tP);
	
};
/*

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
	
*/	
	
	
	//**********************constructor*****************
TSH::TSH()
{	
};

