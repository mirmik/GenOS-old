#ifndef QUEUE_H
#define QUEUE_H

#include "types.h"

template <uint N, typename T> class Cyclic_buffer 
{
	public:
	Cyclic_buffer(){head=0;	for (int i=0;i<N;i++) mas[i]=0;};
	uint head;
	T mas[N];
	int push(T a);
	void print();
};


template <uint N, typename T> int Cyclic_buffer<N,T>::push(T a)
{
		mas[head]=a;
		head = (head + 1) % N; 
}

#include "simple.h"
template <uint N, typename T> void Cyclic_buffer<N,T>::print()
{
	for (int i=0;i<N;i++) *stdprint << mas[i] << '\t';
	*stdprint << '\n';
}

#endif
