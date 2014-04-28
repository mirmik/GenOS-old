
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

Stream* stdio=&term;
Stream* tracert=&term;
Allocator_p * stdalloc=&galloc;

readline_t rl;
rl_terminal r(&term,&rl);

int main(){

term.begin();

debug_print("HelloWorld");

command ("list",command_print);
command ("ptest",ptest);
command ("about",about);



	execute("list");
	execute("about");
	/*
	while(1){
		int i;
		i = term.read();
		if (i!=-1) {pr(i);	prtab();
			  prln((char)i);
			  }
		}*/
	
while(1){r.listen();};
	
		
	
term.end();
	}
