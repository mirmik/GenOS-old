
#ifndef _KEY_COMMAND_H
#define _KEY_COMMAND_H

class KeyCommand
{
virtual int putchar(int c)=0;
virtual int del()=0;
virtual int backspase()=0;
virtual int home()=0;
virtual int end()=0;
virtual int up(int i)=0;
virtual int down(int i)=0;
virtual int left(int i)=0;
virtual int right(int i)=0;
};
#endif
