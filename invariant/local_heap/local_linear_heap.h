#ifndef LOCAL_LINEAR_HEAP_H
#define LOCAL_LINEAR_HEAP_H

#include "stdio.h"

class local_linear_heap{
public:

local_linear_heap(void * _pointer,size_t _sz);
	void* pointer;
	size_t sz;
	
	void* malloc(size_t __size);
	void free(void *__ptr);	


	
	};


	void * operator new (size_t size, local_linear_heap & heap);
	void operator delete (void* p, local_linear_heap & heap);



#endif
