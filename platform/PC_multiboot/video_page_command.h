
#ifndef VIDEO_PAGE_COMMAND_H
#define VIDEO_PAGE_COMMAND_H

#include "types.h"
#include "drv/video_page/video_page.h"
#include "prototype/KeyCommand.h"
class video_page_command : public KeyCommand
{
public:
uint8_t x;
uint8_t y;
video_page_command();
int putchar(int c);
int del();
int backspase();
int home();
int end();
int up(int i);
int down(int i);
int left(int i);
int right(int i);

void new_cursor();
void move_cursor();	
};
#endif
