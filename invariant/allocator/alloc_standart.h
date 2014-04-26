



#include "allocator.h"

class Standart_alloc : public Allocator_p {
	public:
void * allocate (size_t size);
void deallocate (void * p);
};


extern Standart_alloc galloc;

