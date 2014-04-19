
#ifndef RING_H
#define RING_H

#include "charqueue/queue.h"
#include <inttypes.h>
#include <stdio.h> // for size_t
#include "platform.h" // for kmalloc


class ring_t : public Queue_p
{
public:
size_t tail;
size_t head;
size_t size;
char* buffer;


ring_t(size_t a);
ring_t(char* _buffer, size_t a);
int peek(int n);
int available();

int push(char c);
int pop();

~ring_t();

};

#endif
