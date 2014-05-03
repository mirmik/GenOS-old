




#include "StrmDebug.h"

#include "platform.h"

StrmDebug dbgio;

	
size_t StrmDebug::write(uint8_t c)
{debug_putchar(c);}



 int StrmDebug::available(){};
 int StrmDebug::read(){};
 int StrmDebug::peek(){};
 void StrmDebug::flush(){};


int StrmDebug::begin()
{
}

int StrmDebug::end()
{
 
}

