#ifndef QUEUE_H
#define QUEUE_H


#define FULL 2
#define EMPTY 0
#define READY 1


class Queue_p
{
public:
unsigned char status;
	Queue_p();
	virtual int push(char c) = 0;
	virtual int pop() = 0;	
	virtual int available() = 0;
	virtual int peek(int n) = 0;	
};
#endif
