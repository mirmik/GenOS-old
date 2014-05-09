
#include "video_page_command.h"

int video_page_command::putchar(int c){video_page_putchar(y*SCREEN_WIDTH + x, c);}

video_page_command::video_page_command(){x=0;y=0;}

int video_page_command::del(){}
int video_page_command::backspase(){}
int video_page_command::home(){}
int video_page_command::end(){}
int video_page_command::up(int i){}
int video_page_command::down(int i){}
int video_page_command::left(int i){}
int video_page_command::right(int i){}
void video_page_command::new_cursor(){}
void video_page_command::move_cursor(){}	
