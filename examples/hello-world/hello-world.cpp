
#include "math/math.h"
#include "platform.h"
#include "C_stream.h"
#include "debug/debug.h"
#include "allocator/allocator.h"
#include "math/matrix.h"
#include "math/complex.h"
//#include "math/const.h"
#include "utility.h"
#include "intcom/command_list.h"
//#include "inttrans/fourier.h"
#include "queue/queue.h"
//#include "filtration/linear_matrix.h"
Print* stdprint=&term;
Stream* tracert=&term;
Allocator_p * stdalloc;


#define dstdfor(i,n,j,m) for(int i=0;i<n;i++)for(int j=0;j<m;j++)
#define for_all_points_atomspace(pl,A,i,j) dstdfor(i,A.discr,j,A.discr) for_all_list(pl,A.GLOBAL_MAS[i][j]) 

extern "C" void __cxa_pure_virtual() { debug_print("__cxa_pure_virtual"); while (1); };
//#include "math/matrix.h"
#include "math/vector.h"

//#include "math/matrix_alg.h"
//#include "math/matrix_body.h"

#include "container/List.h"
#include "genoslib.h"
#include "simple.h"
//#include <complex>
//#include "math/complex.h"
char Rmas [10000];
Linear_allocator R;
#include "delay.h"
#include "shed/u_esh.h"
TSH SH;
void task(){prln("k");};

int main(){
R.engage(Rmas,10000);
stdalloc=&R;
registry_standart_utility();

term.begin();

SH.newTimer(task,200,REPEAT);
while(1) SH.start();
term.end();
}



