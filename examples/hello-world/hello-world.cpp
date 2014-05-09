
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
#include "PrintTransformer/ASCII2KeyCom.h"
#include "debug/debug.h"
#include "strm/StrmDebug.h"

#include "PrintTransformer/KeyCom2ASCII.h"
Print* stdprint=&term;
Stream* tracert=&term;
Allocator_p * stdalloc=&galloc;

KeyCom2ASCII t(&term);
readline_t rl;
rl_terminal r(&rl,&t);
ASCII2KeyCom f(&r);

char mas[16*4];

extern "C" void __cxa_pure_virtual() { while (1); }

int main(){
term.begin();

registry_standart_utility();
r.print_prompt();
while(1) {
int i =term.read();
if (i!=-1)f.write(i);	
}

term.end();
	}
