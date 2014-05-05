

#include "allocator/allocator.h"
//#include "stdlib.h"

Object_cache::Object_cache(size_t _objsz,Allocator_p* _father)
{
	init(_objsz, _father);
}

void Object_cache::init(size_t _objsz,Allocator_p* _father)
{
	objsz=_objsz;
	list.next=&list;
	father=_father;
}

void * Object_cache::allocate (size_t size)
{void* p = (void*) list.next; 
	list.next=list.next->next;
	return p;
	}

void Object_cache::deallocate (void * p)
{monolist* temp = list.next;
	list.next = (monolist*)p;
	((monolist*)p)->next=temp;
	}

void Object_cache::engage(void* pointer, size_t cachesz)
{
monolist* p = (monolist*) pointer;
for (int i=0;i < cachesz / objsz; i++)
	{p->next = (monolist*)((size_t)pointer + i*objsz);
	p=p->next;}
p->next=list.next;
list.next=(monolist*)pointer;
}

int Object_cache::freeinfo()
{//monolist* p = list.next;
	//while (p!=&list)	
	//{prlnhex(p);
	//p=p->next;}
	int temp=0;
	monolist* p =list.next;
	
	while (p!=&list)
	{temp++;
		p=p->next;
		}
		return temp*objsz;
}


void * operator new (size_t size,void*p)
{
return p;	
}

void operator delete (void * ptr,void*p)
{
}

void * operator new (size_t size,Allocator_p* a)
{
return a->allocate(size);	
}

void operator delete (void * ptr,Allocator_p* a)
{
a->deallocate(ptr);	
}

void * operator new (size_t size)
{
stdalloc->allocate(size);	
}

void operator delete (void * ptr)
{
stdalloc->deallocate(ptr);	
}
