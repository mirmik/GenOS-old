
#include "shed/subst_shed.h"


int thread::number=0;


	//Black magic
	void SubstShed::substitution () 
	{
		saveContext();
		now->sp=readSP();
		now=chg;
		setSP(now->sp);
		loadContext();
	};
	
	
	void SubstShed::create(uint8_t* stack, size_t sz,void(*func)())
	{
		thread* old = now;
		chg = new thread;
		L.add(chg);				
		
		chg->sp=(size_t)stack + sz - 1;		
		old->sp=readSP();
		
		now=chg;			//Хитрый мув ушами.
		setSP(now->sp);		//Смена контекста на самого себя.
		substitution(); 	//Приводит к образованию копии.
												
		if (now->status==UNDER_CONSTRUCTED) 
		{
			now->status=RUN;
			func();	
			while(1);
			
		}
		
		else
		{
			now->status=UNDER_CONSTRUCTED;
			now=old;				
			setSP(now->sp);
			return;
		};	
						
	};

	void SubstShed::change(int num)
	{	List_it pl;
		for_all_list_obj(pl,L,chg,thread) {if (chg->num==num) break;};
		substitution();		
	}
	
	SubstShed::SubstShed(){
		thread* thr = new thread;
		L.add(thr);
		now=thr;};	
