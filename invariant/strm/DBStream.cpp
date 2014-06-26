

#include "strm/DBStream.h"

#define LOCAL_TRACERT 5

DBStream::DBStream(uint32_t tx_size,uint32_t rx_size, uint8_t buftype) {
tprln("constr DBStream");
if 	(buftype == RING)
	{
		tx = new ring_t(tx_size);
		rx = new ring_t(rx_size); 
	}

if	(buftype == DYNAMICRING)
	{
		tx = new dynamicring(tx_size);
		rx = new dynamicring(rx_size); 
	}

on_write = 0;
on_rx_write = 0;
send_func = 0;
}

DBStream::DBStream() {
on_write = 0;
on_rx_write = 0;
}

DBStream::DBStream(Queue_p* _rx, Queue_p* _tx) {
rx=_rx;
tx=_tx;
on_write = 0;
on_rx_write = 0;
send = 0;
}

size_t DBStream::write(uint8_t c){
	if (send(c)!=0) return(1);
	else 
	{
	int temp = tx->push(c);
	if (temp != -1) {
					if (on_write != 0) on_write();
					return(1);
					}
	else return 0;
	}
	}
	
 int DBStream::tx_read(){
	 return(tx->pop());
	 }

size_t DBStream::rx_write(uint8_t c){
rx->push(c);
};

 int DBStream::available(){}
 
 int DBStream::read(){
	 return(rx->pop());}
	 
 int DBStream::peek(){}
 void DBStream::flush(){}
