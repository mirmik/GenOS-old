
#include "platform.h"
//#include "C_stream.h"
#include "allocator/allocator.h"
#include "delay.h"
#include "allocator/alloc_standart.h"
#include "shed/u_esh.h"
#include "shed/flag_sh.h"
#include "strm/DBStream.h"
#include "strm/StrmNull.h"
#include "strm/BufferStrm.h"
#include "transport.h"
#include "microrl/microrl.h"
#include "intcom/command_list.h"
#include "utility.h"
#include "readline/readline.h" 
#include "readline/rl_terminal.h"

Stream* stdio=&NullStream;
Stream* tracert=&NullStream;
Allocator_p * stdalloc=&galloc;

//Serial0 term;

//readline_t rl;
//microrl_t m;
//rl_terminal r(&term,&rl);

int main(){

//m.init(term);
//term.begin();

debug_print("HelloWorld");
red_led_on();

while(1);

//BufferStream deb(500,RING);
//tracert = &deb;

//DBStream D(20,20,DYNAMICRING);
//DBStream Do(D.tx,D.rx);
	
	//D.println("HelloWorldHelloWorldHelloworld");
	//int c;
	//command("about",about);
	//command("ptest",ptest);
	//command("list",command_print);
	//r.set_execute_callback(interpreter);
	
	//execute("list");
	//execute("about");
	//rl.split();
	//prln(rl.argv);
	//prln(rl.argc[0]);
	//prln(rl.argc[1]);
	
//	stdio=0;
//while(1){r.listen();};
	
		
	
	
	//while ((c = Do.read())!=-1) 	//stdio->print((char)c);
	
	//transport_all(tracert,stdio);
	
	//transport_all(tracert,stdio);
	
//term.end();
	}
