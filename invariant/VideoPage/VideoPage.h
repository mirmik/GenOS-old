#ifndef _VIDEOo_PAGE_H
#define _VIDEOo_PAGE_H

#include <inttypes.h>
#include "stdio.h"

struct video_page_symbol_t {
volatile char c;
volatile char f;	
}__attribute__((packed));

class VideoPage
{
public:
VideoPage(size_t _addr, unsigned int _width, unsigned int _height);	
void init(size_t _addr, unsigned int _width, unsigned int _height);	
video_page_symbol_t* addr;
unsigned int w;
unsigned int h;

void putchar(unsigned int x, unsigned int y, char c);
void putchar(unsigned int x, unsigned int y, char c, char f);
void putcolor(unsigned int x, unsigned int y, char f);
void setbox(unsigned int x1,unsigned int y1, unsigned int x2, unsigned int y2, char c, char f);

void clean();
void clean_str(unsigned int y);

void charcpy(int x, int y, int xo, int yo);
void scroll(int x , int y);
void boxcpy(int x1, int y1, int x2, int y2, int xo, int yo);
void setcursor(unsigned int x , unsigned int y);

};
#endif