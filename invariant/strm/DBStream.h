

#ifndef DBSTREAM_H
#define DBSTREAM_H

#include "charqueue/ring.h"
#include "charqueue/dynamicring.h"
#include "prototype/Stream.h"
#include "simple.h"
//#include "types.h"



#define RING 0
#define DYNAMICRING 1

typedef void (*func_t)();

class DBStream : public Stream
{
	public:
DBStream(uint32_t tx_size,uint32_t rx_size, uint8_t buftype);
DBStream(Queue_p* rx, Queue_p* tx);
DBStream();

Queue_p *tx; 	
Queue_p *rx;		

int (*send)(char c);
func_t on_write;
func_t on_rx_write;
func_t send_func;

size_t write(uint8_t c);
size_t rx_write(uint8_t c);
int tx_read();

 int available();
 int read();
 int peek();
 void flush();

void set_on_write_func(func_t);
void set_on_tx_write_func(func_t);
	
 using Stream::write; // pull in write(str) and write(buf, size) from Print
 operator bool() { return true; }
};
#endif
