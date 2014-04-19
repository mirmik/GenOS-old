
#include <sys/socket.h>
#include <arpa/inet.h>


#ifndef SOCKET_H
#define SOCKET_H


//#include <sys/socket.h>

#define UDP_SERVER 6
#define UDP_CLIENT 7


class Socket{
	char ip[16];
	int port;
    struct sockaddr_in addr;
   int type;
    
public:
	int sock;

int create(int _type, char* _ip, unsigned int _port);   
int _socket();
int _bind();
int _connect(); 
int _close(); 	
	
	
	
};













#endif
