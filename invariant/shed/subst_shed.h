
#ifndef SUBST_SHED_H
#define SUBST_SHED_H

#include "container/List.h"
#include "SubstMacro.h"

enum{
UNDER_CONSTRUCTED,
RUN	
	};

class thread 
{	
	public:
	static int number;
	int num;
	int status;
	size_t sp;
	
	thread() : status(RUN) {num=number++;};  
};


class SubstShed 
{
	private:
	//var
	List L;
	thread* now;	
	thread* chg;
	
	public:
	//constr
	SubstShed();	
	//func
	 void create(uint8_t* stack, size_t sz,void(*func)());
	 void change(int num);
	 void substitution();
};


#endif
