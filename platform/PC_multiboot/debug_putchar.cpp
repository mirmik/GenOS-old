



#include "platform.h"
#include "debug/debug.h"
#include "video_page.h"

int cursor __attribute__((section(".data")));


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
video_page_putchar(cursor,c);
cursor++;
break;
}
if (cursor >= SCREEN_WIDTH*SCREEN_HEIGHT) {video_page_drop_str();
cursor = cursor - SCREEN_WIDTH;}
video_page_move_cursor(cursor);
}

void debug_reset_cursor(){cursor=0;};
