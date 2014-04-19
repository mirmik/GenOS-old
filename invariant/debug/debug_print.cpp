
#include "debug.h"


void debug_write(const char*c,int i)
{int k;
for (k=0;k<i;k++)
debug_putchar(*(c+k));
};


void debug_printhex_halfbyte(char b){
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
debug_putchar(c);
};

void debug_printhex_byte (char b){
debug_printhex_halfbyte((b & 0b11110000)>>4);	
debug_printhex_halfbyte(b & 0b00001111);
};




void debug_printhex_int32(int32_t a)
{
	char *p =(char*) &a;
	
debug_putchar('0');
debug_putchar('x');	
debug_printhex_byte(*(p+3));
debug_printhex_byte(*(p+2));
debug_printhex_byte(*(p+1));
debug_printhex_byte(*(p+0));
};


void debug_printhex_int16(int16_t a)
{
	char *p =(char*) &a;
	
debug_putchar('0');
debug_putchar('x');	
debug_printhex_byte(*(p+1));
debug_printhex_byte(*(p+0));
};

int debug_strlen(const char *c)
{int i;
for(i=0;c[i]!=0;i++);
return (i);
};

void debug_print(const char *c)
{	
	debug_write(c,debug_strlen(c));	
};


void debug_print_test(){
char * teststr = "TESTSTR";
debug_print(teststr);  
debug_write("\n\r",2);
debug_print("\n\rit should be 0xABCDABCD");
debug_write("\n\r",2);
debug_printhex_int32(0xABCDABCD);
debug_write("\n\r",2);


return;
};


void debug_print_memory_as_byte(int64_t start,int64_t count)
{int64_t i;
char* p=0;
for (i=start;i<start+count;i++){
debug_printhex_byte(*(p+i));
debug_write("\t",1);
}
};



void debug_print_memory_as_char(int64_t start,int64_t count)
{int64_t i;
int* p=0;
for (i=start;i<start+count;i++){
debug_putchar(*(p+i));
}
};

