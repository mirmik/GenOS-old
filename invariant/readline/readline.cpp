
#include "readline/readline.h"
#include "genoslib.h"
#include "intcom/command_list.h"

readline_t::readline_t()
{
init();	
}
void readline_t::init(){
cursor=0;	
cmdlen=0;
}


char* readline_t::get_line()
{
cmdline[cmdlen]=0;
return cmdline;	
}

#include "simple.h"
#define LOCAL_TRACERT 7



size_t readline_t::write(uint8_t c)
{	
	switch(c)
	{
	case '\b': backspace();break;
	case '\n': if(cmdlen!=0) {get_line();execute(cmdline);} ;init();break;
	default:
	cmdlen++;
	if (cursor!=cmdlen-1)
		{
		memmove (cmdline + cursor + 1,
						 cmdline + cursor,
						 cmdlen-cursor-1);
		}
		
	cmdline[cursor]=c;cursor++;
	}
	return(1);
}


int readline_t::backspace ()
{
if (cursor > 0) {
		memmove (cmdline + cursor-1,
						 cmdline + cursor,
						 cmdlen-cursor+1);
		cursor--;
		//cmdline [cmdlen] = '\0';
		cmdlen--;
		return 1;
	}	
return 0;
}

int readline_t::move_cursor (int offset)
{
	int lastcursor=cursor;
	cursor=cursor+offset;
	if (cursor < 0) cursor=0;
	if (cursor > cmdlen) cursor=cmdlen;
	return (cursor - lastcursor);
}


int readline_t::right (int i)
{return(move_cursor(i));}

int readline_t::left (int i)
{return(-move_cursor(-i));}


int readline_t::del (int i)
{
if (cmdlen - cursor > 0) {
		memmove (cmdline + cursor,
						 cmdline + cursor + 1,
						 cmdlen-cursor -1);
		cmdlen--;
		return 1;
	}	
return 0;
}
