




#include "error/error.h"


void systemError(const char* c)
{
	
	//FULLSTOP OS SERVICE
	
	debug_print("\r\nSYSTEM ERROR:\n\r");
	debug_print(c);
	systemError_platform();
	while(1);	
};
