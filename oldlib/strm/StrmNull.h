
#ifndef NULL_STREAM_H
#define NULL_STREAM_H
#include "Stream.h"

class NullStream_t : public Stream
{
	public:
size_t write(uint8_t);

 int available();
 int read();
 int peek();
 void flush();

	
int begin();
int end();
};

extern NullStream_t NullStream;
#endif

