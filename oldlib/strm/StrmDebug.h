#ifndef STRMDEBUG_H
#define STRMDEBUG_H

#include "Stream.h"
#include "debug/debug.h"

class StrmDebug : public Stream
{
	public:
size_t write(uint8_t);
 int available();
 int read();
 int peek();
 void flush();

	
int begin();
int end();
using Stream::write; // pull in write(str) and write(buf, size) from Print
 operator bool() { return true; }

};

extern StrmDebug dbgio;

















#endif
