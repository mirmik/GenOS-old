
#ifndef _KEYBOARD_SCAN_H
#define _KEYBOARD_SCAN_H

#include "prototype/Stream.h"
#include "strm/DBStream.h"
#define LEFT_SHIFT  0x01
#define RIGHT_SHIFT 0x02
#define LEFT_CTRL   0x04
#define RIGHT_CTRL  0x08
#define LEFT_ALT    0x10
#define RIGHT_ALT   0x20
#define SHIFT_MASK  (LEFT_SHIFT | RIGHT_SHIFT)
#define CTRL_MASK   (LEFT_CTRL | RIGHT_CTRL)
#define ALT_MASK    (LEFT_ALT | RIGHT_ALT)
class Keyscan 
{
public:
unsigned int s_shiftState;
Stream* in_strm;
Print* out_strm;
Keyscan();
void strm(const char* str);
void init();	
char scan2ascii();
char scan2ascii(char c);	
};
#endif
