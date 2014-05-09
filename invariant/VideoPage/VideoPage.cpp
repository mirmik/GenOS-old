#include "VideoPage/VideoPage.h"
#include "cpu.h"
#include "debug/debug.h"
VideoPage::VideoPage(size_t _addr, uint _width, uint _height){
	init(_addr, _width, _height);
}


void VideoPage::init(size_t _addr, uint _width, uint _height){
	addr=(video_page_symbol_t*)_addr;
	w=_width;
	h=_height;
}

void VideoPage::putchar(uint x, uint y, char c){
if (x < w && y < h)
(addr+x+y*w)->c=c;
}

void VideoPage::putchar(uint x, uint y, char c, char f){
if (x < w && y < h)
{	(addr+x+y*w)->c=c;
	(addr+x+y*w)->f=f;	}}

void VideoPage::putcolor(uint x, uint y, char f){
if (x < w && y < h)
(addr+x+y*w)->f=f;
}

void VideoPage::charcpy(int x, int y, int xo, int yo){
video_page_symbol_t buffer = {0,0};
if (x < w && y < h && x >= 0 && y >= 0)
buffer = *(addr+x+y*w);
if (x+xo < w && y+yo < h && x+xo >= 0 && y+yo >= 0)
*(addr+x+xo+(y+yo)*w)=buffer;
}

void VideoPage::boxcpy(int x1, int y1, int x2, int y2, int xo, int yo)
{
if (yo>=0)
	{
		if (xo>=0) 
		{
		for (int x = x2; x >= x1; x--)
		for (int y = y2; y >= y1; y--)
		charcpy(x,y,xo,yo);
		}
		if (xo<0) 
		{
		for (int x = x1; x <= x2; x++)
		for (int y = y2; y >= y1; y--)
		charcpy(x,y,xo,yo);	
		}
	}
if  (yo<0)
	{
		if (xo>=0) 
		{
		for (int x = x2; x >= x1; x--)
		for (int y = y1; y <= y2; y++)
		charcpy(x,y,xo,yo);
		}
		if (xo<0) 
		{
		for (int x = x1; x <= x2; x++)
		for (int y = y1; y <= y2; y++)
		charcpy(x,y,xo,yo);
		}	
	}
}

void VideoPage::setbox(uint x1,uint y1, uint x2, uint y2, char c, char f){ 
	for (int x = x1; x <= x2 && x < w; x++)
	for (int y = y1; y <= y2 && y < h; y++)
	{putchar(x,y,c,f);}
	}

void VideoPage::clean(){
setbox(0,0,w-1,h-1,' ',0x0A);}

void VideoPage::clean_str(uint y){
if (y < h)
setbox(0,y,w-1,y,' ',0x0A);}

void VideoPage::scroll(int x , int y)
{
	boxcpy(0-x,0-y,w-1-x,h-1-y,x,y);
}

void VideoPage::setcursor(uint x , uint y)
{
if (x < w && y < h){
outb(0x3D4, 0x0E);
outb(0x3D5, ((uint16_t)(y*w+x)) >> 8);
outb(0x3D4,0x0F);
outb(0x3D5,(uint16_t)(y*w+x));}
}
