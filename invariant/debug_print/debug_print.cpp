
#include "debug_print.h"
//#include "platform.h"


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


/*--------------------------------------------
// Печать дампа памяти заданного размера
//------------------------------------------*/
void debug_print_dump(void* address, uint32_t size)
{
  /* Преобразуем указатель в массив байт */
  uint8_t* dump = (uint8_t*) address; 
  /* Преобразуем указатель просто в число */  
  uint32_t addr_tmp = (size_t) address;
  /* Вспомогательные переменные */
  uint32_t i = 0;
  uint32_t mark = 0;
 
  for (i = 0; i < size; i++)
  {
    //set_text_color(LIGHT_GRAY);
   
    if (mark == 0)
    {
    dpr_inthex(addr_tmp);
   // char sss[20];
   // num2base_str(sss,addr_tmp,16);
   // dpr_str(sss);
    
    debug_print(": ");
    }
   
    if (dump[i] != 0)
   ;//   set_text_color(LIGHT_GREEN);
    else
     // set_text_color(LIGHT_GRAY);
   ;
    debug_printhex_byte(dump[i]);
   
    //set_text_color(LIGHT_GRAY);
   
    if ( mark == 7 )
    {
      debug_print("|");
      mark++;
    }
    else if ( mark == 15 )
    {
      debug_print("\n");
      mark = 0;
     
      addr_tmp += 0x10;
    }
    else
    {
      debug_print(" ");
      mark++;
    }
  } 
}
