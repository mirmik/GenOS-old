



#include "charqueue/ring.h"

ring_t::ring_t(size_t sz)
{	size=sz;
	buffer=(char*)kmalloc(sz);
	tail=0;
	head=0;
	status = EMPTY;
}

ring_t::~ring_t()
{
kfree(buffer);	
}


int ring_t::pop()
{
if (status == EMPTY) return -1;
char c = buffer[tail];
tail = (tail + 1) % size;
if (head==tail) status = EMPTY;
else status = READY;
return c;

}

int ring_t::push(char c)
{
  if (status == FULL) return(-1);
  buffer[head] = c;
  head = (head + 1) % size;
if (head==tail) status = FULL;
else status = READY;
return 0;
}


int ring_t::available()
{
return((head-tail+size)%size);	
}

int ring_t::peek(int n)
{
return(0);	
}
