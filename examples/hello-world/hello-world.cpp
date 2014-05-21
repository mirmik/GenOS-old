
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
//#include "filtration/linear_matrix.h"
Print* stdprint=&term;
Stream* tracert=&term;
Allocator_p * stdalloc;

extern "C" void __cxa_pure_virtual() { debug_print("__cxa_pure_virtual"); while (1); };

#include "genoslib.h"
#include "simple.h"
#include "glist.h"
//#include <complex>
#include "math/matrix2.h"





char Rmas [10000];
Linear_allocator R;
int main(){
R.engage(Rmas,10000);
stdalloc=&R;
registry_standart_utility();
term.begin();
Matrix<3,3,float> M;
Matrix<3,3,float> M2,M3;
M2.identity();
M2[Index(2,1)]=1;
M2[Index(2,0)]=1;
M2[Index(1,0)]=1;
M3.identity();
M3[Index(2,1)]=1;
M3[Index(2,0)]=1.5;
M3[Index(1,0)]=1;

M.identity();
M=2*(M2+M2*2-M2)*2;
M2.print();
M=inv(M2);
prln();
M.print();

prln();
term.end();
}
