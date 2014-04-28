




#include "error/error.h"


void SystemError(char* c)
{
	
	//FULLSTOP OS SERVICE
	
	debug_print("SYSTEM ERROR:\n");
	debug_print(c); dln
	SystemError_platform();
	while(1);	
};
