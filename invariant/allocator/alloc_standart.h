



#include "allocator.h"
#include "types.h"

class Standart_alloc : public Allocator_p {
	public:
void * allocate (size_t size);
void deallocate (void * p);
int freeinfo (){};
};


extern Standart_alloc galloc;

