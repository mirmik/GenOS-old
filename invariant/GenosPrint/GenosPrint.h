#ifndef GENOS_PRINT
#define GENOS_PRINT

#include "Stream.h"
#include "Print.h"


extern Print * stdprint; 

#define prlnhex(a) 	stdprint->println((int)a,HEX);
#define prhex(a) 	stdprint->print((int)a,HEX);
#define pr(a) 	stdprint->print(a);
#define prln(a) stdprint->println(a);
#define prtab() stdprint->write('\t');







	
	#endif
