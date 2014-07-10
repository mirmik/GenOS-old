

#ifndef BUFFERSTREAM_H
#define BUFFERSTREAM_H

#include "charqueue/ring.h"
#include "charqueue/dynamicring.h"
#include "prototype/Stream.h"
#include "simple.h"

#define RING 0
#define DYNAMICRING 1

typedef void (*func_t)();

class BufferStream : public Stream
{
public:
BufferStream(uint32_t size, uint8_t buftype);
BufferStream(Queue_p* rx);
BufferStream();

Queue_p *q;		

func_t on_write;

size_t write(uint8_t c);

 int available();
 int read();
 int peek();
 void flush();

void set_on_write_func(func_t);
	
 using Stream::write; // pull in write(str) and write(buf, size) from Print
 operator bool() { return true; }
};
#endif
