
#ifndef STATICRING_H
#define STATICRING_H

#include "queue.h"
#include <inttypes.h>
#include <stdio.h> // for size_t

#define STATICRING_SIZE 40

class staticring_t : public Queue_p
{
public:
size_t tail;
size_t head;
size_t size;
char buffer[STATICRING_SIZE];

staticring_t();
int peek(int n);
int available();

int push(char c);
int pop();

};

#endif
