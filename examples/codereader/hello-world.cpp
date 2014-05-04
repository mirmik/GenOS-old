
#include "platform.h"
#include "C_stream.h"
#include "allocator/allocator.h"
#include "delay.h"
#include "allocator/alloc_standart.h"
#include "shed/u_esh.h"
#include "shed/flag_sh.h"
#include "strm/DBStream.h"
#include "strm/StrmNull.h"
#include "strm/BufferStrm.h"
//#include "transport.h"
//#include "microrl/microrl.h"
#include "intcom/command_list.h"
#include "utility.h"
#include "readline/readline.h" 
#include "readline/rl_terminal.h"

#include "debug/debug.h"
#include "strm/StrmDebug.h"
Stream* stdio=&term;
Stream* tracert=&term;
Allocator_p * stdalloc=&galloc;

readline_t rl;
rl_terminal r(&term,&rl);

char mas[16*4];

int main(){
StrmDebug k;
term.begin();
while (1)
{
	int i = term.read();
	if (i!=-1)
		{
			switch (i){
			case '\n': 	stdio->print("eq \\n");break;
			case '\t': 	stdio->print("eq \\t");break;
			case '\r': 	stdio->print("eq \\r");break;
			default:	stdio->write(i);	  break;
			} 
			prtab(); dpr_inthex(i); prln();
		}	
	}
term.end();
	}
