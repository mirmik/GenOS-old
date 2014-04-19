
#include "hardware.h"
#include "debug_serial.h"

void debug_serial_putchar(char c)
{
 UART0->THR=c;
 while(((UART0->LSR) & (1<<5)) ==0);
};


void debug_serial_write(const char*c,int i)
{int k;
for (k=0;k<i;k++)
debug_serial_putchar(*(c+k));
};


void debug_serial_printhex_halfbyte(char b){
char c;
switch (b)
{
case 0b00000000 : 	c='0';break;
case 0b00000001 : 	c='1';break;
case 0b00000010 : 	c='2';break;
case 0b00000011 : 	c='3';break;
case 0b00000100 : 	c='4';break;
case 0b00000101 : 	c='5';break;
case 0b00000110 : 	c='6';break;
case 0b00000111 : 	c='7';break;
case 0b00001000 : 	c='8';break;
case 0b00001001 : 	c='9';break;
case 0b00001010 : 	c='A';break;
case 0b00001011 : 	c='B';break;
case 0b00001100 : 	c='C';break;
case 0b00001101 : 	c='D';break;
case 0b00001110 : 	c='E';break;
case 0b00001111 : 	c='F';break;
}
debug_serial_putchar(c);
};

void debug_serial_printhex_byte (char b){
debug_serial_printhex_halfbyte((b & 0b11110000)>>4);	
debug_serial_printhex_halfbyte(b & 0b00001111);
};




void debug_serial_printhex_int(int a)
{
	char *p =(char*) &a;
	
debug_serial_putchar('0');
debug_serial_putchar('x');	
debug_serial_printhex_byte(*(p+3));
debug_serial_printhex_byte(*(p+2));
debug_serial_printhex_byte(*(p+1));
debug_serial_printhex_byte(*(p+0));
};


int debug_serial_strlen(const char *c)
{int i;
for(i=0;c[i]!=0;i++);
return (i);
};

void printd(const char *c)
{	
	debug_serial_write(c,debug_serial_strlen(c));	
};


void debug_UART_test(){
char * teststr = "TESTSTR";
printd(teststr); dln
debug_serial_printhex_int((int)teststr); dln
debug_serial_putchar('M');
debug_serial_putchar('i');
debug_serial_putchar('r');

debug_serial_putchar('M');
debug_serial_putchar('i');
debug_serial_putchar('r');

debug_serial_putchar('M');
debug_serial_putchar('i');
debug_serial_putchar('r');
debug_serial_putchar('M');
debug_serial_putchar('i');
debug_serial_putchar('r');
debug_serial_putchar('M');
debug_serial_putchar('i');

printd("\n\rit should be 0xABCDABCD");
debug_serial_write("\n\r",2);
debug_serial_printhex_int(0xABCDABCD);
debug_serial_write("\n\r",2);


return;
};


void debug_print_memory_piece_as_byte(int64_t start,int64_t finish)
{int64_t i;
char* p=0;
for (i=start;i<finish;i++){
debug_serial_printhex_int(i);
debug_serial_putchar('\t');
debug_serial_printhex_byte(*(p+i));
dln
}
};

void debug_print_memory_piece_as_int(int64_t start,int64_t finish)
{int64_t i;
char* p=0;
for (i=start/4;i<finish/4;i++){
debug_serial_printhex_int(i*4);
debug_serial_putchar('\t');
debug_serial_printhex_int(*((int*)(((int)p*4)+i*4)));
dln
}
};

void debug_print_int_as_4char(int a)
{char c;
	c=(a & 0xFF000000)>>24;
debug_serial_putchar(c);
	c=(a & 0x00FF0000)>>16;
debug_serial_putchar(c);
	c=(a & 0x0000FF00)>>8;
debug_serial_putchar(c);
	c=a & 0x000000FF;
debug_serial_putchar(c);
	};


void debug_print_memory_piece_as_char(int64_t start,int64_t finish)
{int64_t i;
int* p=0;
for (i=start/4;i<finish/4+1;i++){
debug_serial_printhex_int(i);
debug_serial_putchar('\t');
debug_print_int_as_4char(*(p+i));
dln
}
};

void debug_print_memory_piece_as_char_string(int64_t start,int64_t finish)
{int64_t i;
int* p=0;
for (i=start;i<finish+1;i++){
debug_print_int_as_4char(*(p+i));
}
};

//#include "interface.h"
//void debug_print_ringbuffer(struct ring_buffer *b)
//{
//printd("*");debug_serial_printhex_int(b); dln
//printd("buff:");debug_serial_printhex_int(b->buffer);dln
//printd("tail:");debug_serial_printhex_int(b->tail);dln
//printd("head:");debug_serial_printhex_int(b->head);dln
//printd("size:");debug_serial_printhex_int(b->size);dln
//debug_print_memory_piece_as_char_string(uart0_tx->buffer,uart0_tx->buffer+uart0_tx->size);dln
//}
