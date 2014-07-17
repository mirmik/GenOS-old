


#include "staticring.h"

staticring_t::staticring_t()
{	size=STATICRING_SIZE;
	tail=0;
	head=0;
	status = EMPTY;
}


int staticring_t::pop()
{
if (status == EMPTY) return -1;
char c = buffer[tail];
tail = (tail + 1) % size;
if (head==tail) status = EMPTY;
else status = READY;
return c;

}

int staticring_t::push(char c)
{
  if (status == FULL) return(-1);
  buffer[head] = c;
  head = (head + 1) % size;
if (head==tail) status = FULL;
else status = READY;
return 1;
}


int staticring_t::available()
{
return((head-tail+size)%size);	
}

int staticring_t::peek(int n)
{
return(-1);	
}
