




#include "Sock_stream.h"
#include <sys/socket.h>
#include <arpa/inet.h>

size_t Sock_stream_t::write(uint8_t c)
{send(Client->sock,&c,1,0);}


 int Sock_stream_t::available(){}
 int Sock_stream_t::read(){
	 char c;
if ((recv(Server->sock,&c,1,0)) == -1) return -1;
return c;}
 int Sock_stream_t::peek(){}
 void Sock_stream_t::flush(){}


int Sock_stream_t::begin(Socket &s,Socket &d)
{
	Server=&s;
	Client=&d;
}

int Sock_stream_t::end()
{
}
