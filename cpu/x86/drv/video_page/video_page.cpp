#include "drv/video_page/video_page.h"
#include "cpu.h"

void video_page_putchar(uint8_t* videomem, uint offset, uint8_t c){
*(videomem + offset * 2) = c; 
};

void video_page_putcolor(uint8_t* videomem, uint offset, uint8_t color){
*(videomem + offset * 2 + 1 ) = color;
};

void video_page_move_cursor(uint8_t* videomem, uint offset)
{
outb(0x3D4, 0x0E);
outb(0x3D5, offset >> 8);
outb(0x3D4,0x0F);
outb(0x3D5,offset);
}

void video_page_reset(uint8_t* videomem, uint size)
{
for (int i =0 ;i < size; i++) 
video_page_putchar(videomem, ' ', 0x00);
}
 
 
void video_page_clr(uint8_t* videomem, uint offset, uint size)
{
for (uint i = 0; i< size; i++) 
video_page_putchar(videomem, i, ' ');
video_page_color(videomem, i, ' ');
}

void video_page_copy_str(uint8_t* videomem, uint src_offset,uint dest_offset, uint size)
{
for (uint i = 0 ; i < size; i++) 
*(videomem + dest*SCREEN_WIDTH*2 + i) = *(videomem + src*SCREEN_WIDTH*2 + i);
}


void video_page_scroll(uint8_t* videomem, uint width, uint height)
{
for (int i=;i<SCREEN_HEIGHT;i++)
video_page_copy_str(i,i-1);
video_page_clr_str(24);
}


