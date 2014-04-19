
#include "socket.h"
#include "string.h"
#include "GenOS.h"
#include "stdio.h"
#include <sys/ioctl.h>

#include <fcntl.h>
#include <unistd.h>


int Socket::create(int _type, char* _ip, unsigned int _port)
{
strcpy(ip,_ip);
port=_port;
type=_type;		
	int i;
int flags = 1;

	switch(type)
	{
//Socket create
case UDP_SERVER:

_socket();    
    //Socket configuration
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
if (_bind() == -1) return -1;


  flags = fcntl(sock,F_GETFL,0);
    //assert(flags != -1);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

break;
case UDP_CLIENT:

_socket();    
    //Socket configuration
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);  
  _connect();
break;
}

return 0;
}


int Socket::_socket(){	
	sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {pr("socket_err");return -1;}	
	}

int Socket::_bind(){
	//Try to bind port for Socket
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {return -1;}
}
 int Socket::_connect(){
   if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        pr("connect_err");
        return -1;
    }}
  
 int Socket::_close(){
   if(close(sock))
    {
        pr("close");
        return -1;
    }}
