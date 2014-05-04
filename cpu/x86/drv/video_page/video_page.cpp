#include "drv/video_page/video_page.h"
#include "cpu.h"
char* videomem = (char*)0xB8000;
void video_page_putchar(int cursor, char c)
{
*(videomem + cursor * 2 + 1 ) = LIGHT_GREEN;
*(videomem + cursor * 2) = c;
cursor++; 
};

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
for (int i =str*SCREEN_WIDTH ;i< (str+1)*SCREEN_WIDTH; i++) 
 video_page_putchar(i, ' ');
 }

void video_page_copy_str(int src,int dest)
{
for (int i=0; i<SCREEN_WIDTH*2; i++) 
*(videomem + dest*SCREEN_WIDTH*2 + i) = *(videomem + src*SCREEN_WIDTH*2 + i);
}


void video_page_drop_str()
{
for (int i=1;i<SCREEN_HEIGHT;i++)
video_page_copy_str(i,i-1);
video_page_clr_str(24);
	}


