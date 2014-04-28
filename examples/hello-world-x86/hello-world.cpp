
#include "platform.h"
#include "debug/debug.h"

extern "C" void _init();

//void putstr(char *s,int x, int y,char* q)
//{
//while(*s !=4) // 25 строк по 80 символов по 2
//{ // байта на символ
//*(q+y*25*2+x*2+0) = *s++; // запись символа в видеопамять
//*(q+y*25*2+x*2+1) = 0xE; // запись атрибута - желтый на черном
//x++;
//}}


	extern "C" void debug_str2();	extern "C" void debug_str();

int main(){
	//debug_str2();
	//while(1);
	
asm("push %ebx");
asm("push %eax");
asm("mov %ah,0x0E");
asm("mov %bx, 7");
asm("mov %al,0x63");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("int $0x10");
asm("pop %eax");
asm("pop %ebx");
	}




