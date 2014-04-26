


#include "alloc_standart.h"


Standart_alloc galloc;

#define LOCAL_TRACERT 10

void * Standart_alloc::allocate (size_t size)
{	
	tpr("alloc global"); tprtab(); tprdec(size);
	void* ptr=malloc(size); tprtab(); tprlnhex(ptr);
	return ptr;
}


void Standart_alloc::deallocate (void * p)
{
	tpr ("alloc global free "); tprlnhex(p);
	free(p);
}
