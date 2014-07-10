

#include "charqueue/dynamicring.h"
#include "simple.h"
#include "allocator/allocator.h"

#define LOCAL_TRACERT 5

//void * operator new (size_t size,Allocator_p* a);
//void operator delete (void * ptr,Allocator_p* a);

dynamicring::dynamicring(int _quantum)
{
tprln("constr dynamicring")
quantum=_quantum;
count=0;
INIT_LIST_HEAD(&ring_head);
engage_ring();
tail=head;
}

void dynamicring::engage_ring()
{
ring_list* temp = new ring_list;
temp->ring = new ring_t(quantum);
list_add_tail(&temp->list,&ring_head);
head=temp;
count++;
}

void dynamicring::absolve_ring()
{
ring_list* temp = container_of(tail->list.next, ring_list, list);
list_del(&tail->list);
delete tail->ring;
delete tail;
tail=temp;
count--;
}

int dynamicring::peek(int n){};
int dynamicring::available(){};

int dynamicring::push(char c){
if (head->ring->push(c))
	{
	//TODO dobavit proverku videlenia pamyati
	engage_ring();
	head->ring->push(c);	
	}
return 0;
};


int dynamicring::pop(){
	int c=tail->ring->pop();
	if (c==0)
		if (count>1)
		{
		absolve_ring();
		c=tail->ring->pop();	
		}
		else return -1;
return c;};
