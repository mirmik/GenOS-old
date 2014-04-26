
#include "readline/readline.h"



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

void readline_t::insert_text(char* c)
{
	while(*c!=0) {insert_char(*c);c++;}
}


void readline_t::insert_char(char c)
{
//if (c != ENDL) {
	
	//**********************************************
	
	cmdlen++;
	if (cursor!=cmdlen-1)
		{
		//tprhex(cmdline + cursor); tprtab();tprhex(cmdline + cursor+1);tprtab();tprln(cmdlen - cursor);
		memmove (cmdline + cursor + 1,
						 cmdline + cursor,
						 cmdlen-cursor-1);
		}
		
	cmdline[cursor]=c;cursor++;
	
	//twrite(cmdline,cmdlen); tprtab(); tpr(cmdline); tprln();
	//}

	//*************************************************

/*
else {cmdline[cmdlen]='\0';cursor=0;
		
		tprln("execute call");
		if (execute!=0) {
		split();
		cmdlen=0;
		tprln("execute");
		execute(argc,argv);}; 
	} 	*/
}

int readline_t::move_cursor (int offset)
{
	int lastcursor=cursor;
	cursor=cursor+offset;
	if (cursor < 0) cursor=0;
	if (cursor > cmdlen) cursor=cmdlen;
	return (cursor - lastcursor);
}



void readline_t::backspace ()
{
if (cursor > 0) {
		memmove (cmdline + cursor-1,
						 cmdline + cursor,
						 cmdlen-cursor+1);
		cursor--;
		//cmdline [cmdlen] = '\0';
		cmdlen--;
	}	
}

//void readline_t::set_execute_callback (int (*_execute)(int, const char* const*))
//{execute=_execute;};



//#define DROP_SPACE(c); for (;(*c!=0) && (*c==' '); c++);
//#define DROP_OP(c); for (;(*c!=0) && (*c!=' '); c++);

// split cmdline to tkn array and return nmb of token
/*void readline_t::split ()
{	argc=0;
	char* temp = cmdline;
	while((*temp) !=0) {
	DROP_SPACE(temp);
	if (*temp != 0) {argv[argc]=temp;argc++;}
	DROP_OP(temp);
	if (*temp!=0) {*temp='\0';temp++;
		}
	}
	tprln(argc);
}*/
