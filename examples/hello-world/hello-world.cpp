
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
memset(mas,0xFF,32);
strcpy(mas,"Mirmik");
debug_print_dump(mas,16*4);dln;
strcpy(mas+2,mas);
debug_print_dump(mas,16*4);dln;
strcpy(mas,mas+2);
debug_print_dump(mas,16*4);dln;

memmove(mas,mas+8,16);
debug_print_dump(mas,16*4);dln;

term.end();
	}
