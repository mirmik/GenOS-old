

#include "csh/csh.h"



// система внутренних прерываний***********************************************
/*
uint8_t CSH_t::addInterrupt(void (*task) (void),uint8_t* flag)
{	PL.create_element_on_last();
	((progInterrupt_t*)(PL.finish))->whatToDo=flag;
	((progInterrupt_t*)(PL.finish))->task=task;
	*(((progInterrupt_t*)(PL.finish))->whatToDo)=0;
	return (0);
}*/
//*******************************************************************************




//***************************************************Основной цикл*******************************


void CSH_t::start()
{
	while(1)										
	{
	//обработчик прерываний.
		/*pP=(progInterrupt_t*)PL.start;
	
		while (pP!=0)						
		{
		switch(*(pP->whatToDo)){
		case DELETE:PL.delete_on_ext_point((ThreadedList_element*)pP);break;
		case GO_CLB: *(pP->whatToDo)=NOP;
		case GO_NOCLB: newTask(pP->task); 
		case NOP:;
		}
		
		pP=(progInterrupt_t*)pP->next;
		}*/				
	
	uint64_t f,prev=0xFFFF;
	

	
	//Обработчик таймеров активируется, если очередь задач пуста							
	if (TCL==TCH)
	
	{
	uint64_t m = millis();
	//tP=(timer_t*)TL.start;
	sh_timer_t* tP,*next;
	
	list_for_each_entry_safe(tP,next,&timer_head,list)
		{
		//printd(" :");debug_serial_printhex_int((int)((m-(tP->timerStart))));dln
	
			
			if (m-(tP->timerStart) >= tP->timerValue)	
			{
			//if 	((m-tP->timerStart - tP->timerValue) > MaxDelay) 
			//MaxDelay = (m-tP->timerStart - tP->timerValue);
			newTask(tP->task);						
			if (tP->taskStatus) 
			{tP->timerStart=tP->timerStart+tP->timerValue;}
			else {deleteTimer(tP);}	
			}	
				
		}		
	}														
	
	
	
	
	//И, наконец сам вызыватель задач.
	if (TCL==TCH) 
	{idle();}						
																	
		else																
		{
		TCL++;	
		if (TCL>=TaskOrderLength) TCL=0;
		if ((int)TaskOrder[TCL]==-1) {
		return;};
													
		TaskOrder[TCL]();
		}	
		
	
	}
}
	
//*********************************************************************************
//функция останова.
void CSH_t::stop(void)
{newTask((void(*)())-1);
}
//*********************************************************************************

//**************************Task manager выполнен в виде кольцевого буфера*******************
void CSH_t::newTask(void (*task) (void))
{
TCH++;
if (TCH>=TaskOrderLength) TCH=0;
if (TCL==TCH) { 
while(1);
//coreError(222); 
}
TaskOrder[TCH]=task;						
}

//*******************Timer manager является связным списком*****************************************
sh_timer_t* CSH_t::newTimer(void (*task) (void),unsigned int timer,uint8_t status)
{
uint64_t m=millis();
timercount++;
	//if (timercount > TimerPANIC)  {while(1);}
	sh_timer_t* tP=new(sh_timer_t);
	list_add(&tP->list,&timer_head);	
	tP->timerStart=m;
	tP->timerValue=timer;
	tP->task=task;
	tP->taskStatus=status;
	//coreError(223);
	return (tP);
	
}


	void CSH_t::deleteTimer(sh_timer_t* tPext)
	{
	list_del(&tPext->list);
	}
	
	
	void CSH_t::deleteAllTimer()
	{ sh_timer_t* tP,*next;
	list_for_each_entry_safe(tP,next,&timer_head,list)
		{
		deleteTimer(tP);
		}
	}
//***************************************************************************
	
	
	
	
	//**********************constructor*****************
CSH_t::CSH_t(void(*c)(void),uint8_t a,uint8_t b)
{	
timercount=0;
	idle=c;
	TaskOrderLength=a;
	TimerPANIC=b;
	INIT_LIST_HEAD(&timer_head);
	TCL=0;
	TCH=0;
	MaxDelay=0;
	TaskOrder = (TaskOrderMemb_t *)  malloc(sizeof(TaskOrderMemb_t) *TaskOrderLength);
}
/*
CSH_t::~CSH_t()
{       
}*/
