#include "utility.h"




void about()
{pr(OS_NAME);
prln(OS_VERSION);}

void ptest(int argv,char** argc)
{
for (int i=0;i<argv;i++) prln(argc[i]);		
}
