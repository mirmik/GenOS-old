
#include "VideoPage/VideoPagePrint.h"

#define ASCII_ESC 0x1B
#define ASCII_BS  0x08

VideoPagePrint::VideoPagePrint(VideoPage *_v){
v=_v;
x=0;y=0;
}

void VideoPagePrint::init()
{
x=0;y=0;
v->setcursor(0,0);
v->clean();
}

#include "genoslib.h"
void VideoPagePrint::d()
{
char c[]="          "; 
v->setbox(v->w-10,v->h-3,v->w-1,v->h-1,'#',0x3);
v->setbox(v->w-9,v->h-2,v->w-1,v->h-1,' ',0x3);
num2base_str(c, x, 10);
for (int j=0;j<8;j++) v->putchar(v->w-9+j,v->h-2,c[j],0x0A);
num2base_str(c, y, 10);
for (int j=0;j<8;j++) v->putchar(v->w-9+j,v->h-1,c[j],0x0A);
}


void VideoPagePrint::shift(int i)
{
	x 	+=	i;
	y 	+=	x>=0 ? 	x / v->w 	: - (-x / v->w) - 1;
	x	= (x + v->w) % v->w;
	//if (y < 0) 			{y = 0; x = 0;};
	//if (y > v->h -1) 	{y=v->h-1;x=v->w-1;};
}

void VideoPagePrint::needly_scroll(){
	int t;
	if (y >= v->h) {
	t = y - (v->h - 1);
	v->scroll(0,-t);
	y	-=	t;}
}
	
size_t VideoPagePrint::write(uint8_t c)
{int  t;
	switch(c){
	case '\n': x=0; y++;break;
	case '\r': x=0;break;
	case '\t': shift(8 - x%8);break;
	case '\b': shift(-1); v->putchar(x,y,' ',0xA);break;
	default:
	v->putchar(x,y,c,0xA);
	shift(1);break;
}
	needly_scroll();
	v->setcursor(x,y);
}

int VideoPagePrint::left(int i){
	shift(-i); limitation(x,0,v->w-1); v->setcursor(x,y);}

int VideoPagePrint::right(int i){
	shift(i); limitation(x,0,v->w-1); v->setcursor(x,y);}
	
int VideoPagePrint::up(int i){
	y-=i; y=limitation(y,0,v->h-1); v->setcursor(x,y);}

int VideoPagePrint::down(int i){
	y+=i; y=limitation(y,0,v->h-1); v->setcursor(x,y);}

int VideoPagePrint::del(int i){
	int xt=x, yt=y;
	v->putchar(x,y,' ',0xA);
	if (i>0) for (int j=0;j<i;j++) {shift( 1);	v->putchar(x,y,' ',0xA);}
	if (i<0) for (int j=0;j>i;j--) {shift(-1);	v->putchar(x,y,' ',0xA);}
	x=xt;y=yt;
	}



