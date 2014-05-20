



#include "allocator.h"
#include "genoslib.h"

class Standart_alloc : public Allocator_p {
	public:
void * allocate (size_t size);
void deallocate (void * p);
size_t freeinfo (){};
};


extern Standart_alloc galloc;

