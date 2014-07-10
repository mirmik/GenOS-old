

#include "flag_sh.h"
#include "simple.h"

sh_flag_t* FlagSH::newFlag(void (*task) (void))
{
	sh_flag_t* tP=(sh_flag_t*)alloc->allocate(sizeof(sh_flag_t));
	new (tP) sh_flag_t;
	list_add(&tP->list,&flag_head);	
	tP->flag=STOP;
	tP->task=task;
	return (tP);	
}


void FlagSH::check()
{sh_flag_t* tP;
	list_for_each_entry(tP,&flag_head,list)		{
			if (tP->flag==GO) {tP->flag=STOP; tP->task();}
	
		}													
}

FlagSH::FlagSH(Allocator_p* a)
{
alloc=a;	
	INIT_LIST_HEAD(&flag_head);
}
