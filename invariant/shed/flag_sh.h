#ifndef FLAG_SH_H
#define FLAG_SH_H

#include "types.h"
#include "linuxlist.h"
#include "allocator/allocator.h"


enum{
GO,
STOP	
};


class sh_flag_t 
{
	public:
void (*task) (void);
uint8_t flag;
list_head list;
};



class FlagSH {
	public:
FlagSH(Allocator_p*);
list_head flag_head;
sh_flag_t* newFlag(void (*task) (void));	

Allocator_p* alloc;
void check();
};

#endif
