
#include "transport.h"

 void transport_char(Stream& a, Stream& b)
{
int c=a.read();	
if (c!=-1) b.write(c);	
}

void transport_char(Stream& a, Stream* b)
{
int c=a.read();	
if (c!=-1) b->write(c);	
}

void transport_char(Stream& a, microrl_t& m)
{
int c=a.read();	
if (c!=-1) m.insert_char(c);	
}
/*

 void double_transport_char(Stream& a, microrl_t& m,Stream* b)
{
int c=a.read();	
if (c!=-1) m.insert_char(c);
if (c!=-1) b->write(c);	
}

 void double_transport_char(Stream& a, microrl_t& m,Stream& b)
{
int c=a.read();	
if (c!=-1) m.insert_char(c);
if (c!=-1) b.write(c);	
}*/

void double_transport_char(Stream& a, Stream& d,Stream* b)
{
int c=a.read();	
if (c!=-1) d.write(c);
if (c!=-1) b->write(c);	
}


void transport_all(Stream* a, Stream* d)
{int c;
while ((c=a->read()) != -1) d->write((char)c);
}


