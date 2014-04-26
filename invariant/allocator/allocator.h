
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "stdlib.h"
#include "simple.h"


struct monolist {
monolist* next;
};

class Allocator_p {
	public:
Allocator_p * father;
virtual void * allocate (size_t size)=0;
virtual void deallocate (void * p)=0;
};




class Object_cache : public Allocator_p {
public:
size_t objsz;

Object_cache(size_t _objsz,Allocator_p* _father = 0);
void init(size_t _objsz,Allocator_p* _father = 0);

monolist list;
void * allocate (size_t size);
void deallocate (void * p);

void engage(void* pointer, size_t cachesz);

int freeblocks();
};



void * operator new (size_t size,void*p);
void * operator new (size_t size,Allocator_p* a);
void operator delete (void * ptr,void*p);
void operator delete (void * ptr,Allocator_p* a);



#endif


