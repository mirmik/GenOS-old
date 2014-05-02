



#include "platform.h"
#include "debug/debug.h"
#include "video_page.h"

int cursor __attribute__((section(".data")));
#define WIDTH 80
#define LENGTH 25


extern "C" void debug_putchar(char c)
{
switch (c){
case '\n': 
cursor = (cursor - cursor % WIDTH) + WIDTH;
break;
case '\r':
cursor = (cursor - cursor % WIDTH);
break;
default:
video_page_putchar(cursor,c);
cursor++;
break;
}
if (cursor >= WIDTH*LENGTH) {video_page_drop_str();
cursor = cursor - WIDTH;}
video_page_move_cursor(cursor);
}

void debug_reset_cursor(){cursor=0;};
