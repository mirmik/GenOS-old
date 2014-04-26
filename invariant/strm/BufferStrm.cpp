

#define LOCAL_TRACERT 5

#include "strm/BufferStrm.h"

BufferStream::BufferStream(uint32_t size, uint8_t buftype) {
tprln("constr BuffStream");
if 	(buftype == RING)
	{
		q = new (stdalloc) ring_t(size);
		 
	}

if	(buftype == DYNAMICRING)
	{
		q = new dynamicring(size); 
	}

on_write = 0;
}

BufferStream::BufferStream() {
on_write = 0;
}

BufferStream::BufferStream(Queue_p* _q) {

q=_q;
on_write = 0;
}

size_t BufferStream::write(uint8_t c){
	int temp = q->push(c);
	if (temp == 0) {
					if (on_write != 0) on_write();
					return(1);
					}
	else return 0;
	}
	

 int BufferStream::available(){}
 int BufferStream::read(){
	 return(q->pop());}
 int BufferStream::peek(){}
 void BufferStream::flush(){}
