




#include "error.h"


void systemError(const char* c)
{
	
	//FULLSTOP OS SERVICE
	
	debug_print(">>SYSTEM ERROR:");
	debug_print(c);dln;
	systemError_platform();
	while(1);	
};
