



#include "StrmNull.h"


NullStream_t NullStream;

	
size_t NullStream_t::write(uint8_t c)
{}


 int NullStream_t::available(){};
 int NullStream_t::read(){return(fgetc(stdin));};
 int NullStream_t::peek(){};
 void NullStream_t::flush(){};


int NullStream_t::begin()
{
}

int NullStream_t::end()
{
 
}

