


#ifndef SOCK_STREAM_H
#define SOCK_STREAM_H
#include "GenOS.h"

class Sock_stream_t : public Stream
{
	
	public:
	Socket* Server;
	Socket* Client;
//size_t write(const uint8_t *buffer, size_t size);	
size_t write(uint8_t);

 int available();
 int read();
 int peek();
 void flush();

	
int begin(Socket &s,Socket &d);
int end();

	
 using Stream::write; // pull in write(str) and write(buf, size) from Print
 //operator bool() { return true; }

};
#endif

