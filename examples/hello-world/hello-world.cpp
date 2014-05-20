
#include "math/math.h"
#include "platform.h"
#include "C_stream.h"
#include "debug/debug.h"
#include "allocator/allocator.h"
//#include "math/matrix.h"
//#include "math/complex.h"
//#include "math/const.h"
#include "utility.h"
#include "intcom/command_list.h"
//#include "inttrans/fourier.h"
#include "queue/queue.h"
#include <complex>
//#include "filtration/linear_matrix.h"
Print* stdprint=&term;
Stream* tracert=&term;
Allocator_p * stdalloc;

#include "simple.h"
#include "glist.h"

#include "genoslib.h"
extern "C" void __cxa_pure_virtual() { debug_print("__cxa_pure_virtual"); while (1); }

char Rmas [10000];
Linear_allocator R;
int main(){
R.engage(Rmas,10000);
stdalloc=&R;

registry_standart_utility();
term.begin();

term.end();
}
