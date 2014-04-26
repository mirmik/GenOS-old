
// TODO


#include "local_linear_heap.h"


local_linear_heap::local_linear_heap(void * _pointer,size_t _sz)
{
pointer=_pointer;	
sz=_sz;
	
}	



	void* local_linear_heap::malloc(size_t __size)
{
	return pointer;
}	

	void local_linear_heap::free(void *__ptr)
{
	
}	



	void * operator new (size_t size, local_linear_heap & heap)
	{
	return(heap.malloc(size));	
	}


	void operator delete (void* p, local_linear_heap & heap)
	{
	heap.free(p);	
	}
