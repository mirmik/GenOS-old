



#include "platform.h"
#include "debug/debug.h"
#include "video_page.h"
#include "genoslib.h"

#define        SCREEN_WIDTH  80
#define        SCREEN_HEIGHT 25
int cursor __attribute__((section(".data")));

char* videomem = (char*)0xB8000;
extern "C" void debug_putchar(char c)
{
switch (c){
case '\n': 
cursor = (cursor - cursor % SCREEN_WIDTH) + SCREEN_WIDTH;
break;
case '\r':
cursor = (cursor - cursor % SCREEN_WIDTH);
break;
default:
*(videomem + cursor * 2)=c;
*(videomem + cursor * 2 + 1)=0xA;
cursor++;
break;
}
if (cursor >= SCREEN_WIDTH*SCREEN_HEIGHT) {
	//cursor=0;
	//for (int i=0;i< SCREEN_WIDTH*SCREEN_HEIGHT;i++) 
	//	{
	//	*(videomem + i * 2)=' ';
	//	*(videomem + i * 2 + 1)=0xA;
	//}
	memmove(videomem,videomem + SCREEN_WIDTH*2,SCREEN_WIDTH*2*(SCREEN_HEIGHT-1));
	for (int i= SCREEN_WIDTH*(SCREEN_HEIGHT-1);i< SCREEN_WIDTH*SCREEN_HEIGHT;i++) 
	{
		*(videomem + i * 2)=' ';
		*(videomem + i * 2 + 1)=0xA;
	}
	cursor=SCREEN_WIDTH*(SCREEN_HEIGHT-1);
	}
}
