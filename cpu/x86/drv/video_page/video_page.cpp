#include "drv/video_page/video_page.h"

#define WIDTH 80
#define LENGTH 25

char* videomem = (char*)0xB8000;
void video_page_putchar(int cursor, char c)
{
*(videomem + cursor * 2 + 1 ) = 10;
*(videomem + cursor * 2) = c;
cursor++; 
};

void outb(unsigned short port, unsigned char value)
{
asm volatile("outb %1, %0"::"dN"(port),"a"(value));
}

void video_page_move_cursor(int cur)
{
outb(0x3D4, 0x0E);
outb(0x3D5, cur >> 8);
outb(0x3D4,0x0F);
outb(0x3D5,cur);
}

void video_page_reset()
{
for (int i =0 ;i< 25*80; i++) 
 video_page_putchar(i, ' ');
 }
 
 
void video_page_clr_str(int str)
{
for (int i =str*WIDTH ;i< (str+1)*WIDTH; i++) 
 video_page_putchar(i, ' ');
 }

void video_page_copy_str(int src,int dest)
{
for (int i=0; i<WIDTH*2; i++) 
*(videomem + dest*WIDTH*2 + i) = *(videomem + src*WIDTH*2 + i);
}


void video_page_drop_str()
{
for (int i=1;i<LENGTH;i++)
video_page_copy_str(i,i-1);
video_page_clr_str(24);
	}


