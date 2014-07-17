
#ifndef VIDEOPAGEPRINT_H
#define VIDEOPAGEPRINT_H

#include "KeyCom.h"
#include "inttypes.h"
#include "VideoPage.h"

class VideoPagePrint : public KeyCom {
public:
VideoPage* v;
int x,y;

void init();

VideoPagePrint(VideoPage* _v);
size_t write(uint8_t c);	

void shift(int i);
void needly_scroll();
int left(int i);
int right(int i);
int up(int i);
int down(int i);
int del(int i);

//debug
void d();

using Print::write; // pull in write(str) and write(buf, size) from Print
operator bool() { return true; }
};
#endif
