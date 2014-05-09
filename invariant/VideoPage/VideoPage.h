#ifndef _VIDEOo_PAGE_H
#define _VIDEOo_PAGE_H

#include "types.h"

struct video_page_symbol_t {
volatile char c;
volatile char f;	
}__attribute__((packed));

class VideoPage
{
public:
VideoPage(size_t _addr, uint _width, uint _height);	
void init(size_t _addr, uint _width, uint _height);	
video_page_symbol_t* addr;
uint w;
uint h;

void putchar(uint x, uint y, char c);
void putchar(uint x, uint y, char c, char f);
void putcolor(uint x, uint y, char f);
void setbox(uint x1,uint y1, uint x2, uint y2, char c, char f);

void clean();
void clean_str(uint y);

void charcpy(int x, int y, int xo, int yo);
void scroll(int x , int y);
void boxcpy(int x1, int y1, int x2, int y2, int xo, int yo);
void setcursor(uint x , uint y);

};
#endif
