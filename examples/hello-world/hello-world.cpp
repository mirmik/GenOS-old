/*
//#include "math/math.h"
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
//#include "math/matrix.h"
//#include "math/vector.h"

//#include "math/matrix_alg.h"
//#include "math/matrix_body.h"

//#include "container/List.h"
#include "genoslib.h"
#include "simple.h"
//#include <complex>
//#include "math/complex.h"
*/
#include <SDL2/SDL.h>
#include <iostream>

//complex<float> f;
//char Rmas [10000];
//Linear_allocator R;
int main(){
//R.engage(Rmas,10000);
//stdalloc=&R;
//registry_standart_utility();
//term.begin();

if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
}


//term.end();
}
