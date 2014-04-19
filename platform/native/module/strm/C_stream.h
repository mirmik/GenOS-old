

#ifndef C_STREAM_H
#define C_STREAM_H
#include "Stream.h"
#include <termios.h>

class C_stream_t : public Stream
{
    struct termios orig_term_attr;
    
	public:
//size_t write(const uint8_t *buffer, size_t size);	
size_t write(uint8_t);

 int available();
 int read();
 int peek();
 void flush();

	
int begin();
int end();

	
 //using Stream::write; // pull in write(str) and write(buf, size) from Print
 //operator bool() { return true; }

};

extern C_stream_t term;

#endif

