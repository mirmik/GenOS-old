


#ifndef _CPU_H
#define _CPU_H


#define CPU_NAME "i386"



static void outb(unsigned short port, unsigned char value)
{
asm volatile("outb %1, %0"::"dN"(port),"a"(value));
}


static unsigned char inb(unsigned short port)
{
unsigned char c;
asm volatile("inb %1, %0":"=a"(c):"dN"(port));
return(c);
}





#endif
