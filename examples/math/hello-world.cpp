
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
#include "math/MatrixMath.h"
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
float a[9] = {1,0,0,0,1,0,0,0,1};
float b[9] = {2,0,0,2,2,2,2,1,1};
float c[9];
int main(){
term.begin();
MatrixPrint(a,3,3,"kkekek");
MatrixExponent(a,3,c);
MatrixPrint(c,3,3,"kkekek");

term.end();
	}
