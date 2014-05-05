#include "utility.h"


#include "intcom/command_list.h"
#include "allocator/allocator.h"
#include "initenv/initenv.h"
void about()
{pr(OS_NAME);
prln(OS_VERSION);}

void ptest(int argv,char** argc)
{
for (int i=0;i<argv;i++) prln(argc[i]);		
}

void meminfo(int argv,char** argc)
{
pr(stdalloc->freeinfo());		
}

void registry_standart_utility()
{
command("about",about);
command("ptest",ptest);
command("list",command_print);
command("sectioninfo",initenv_sections_info);
}

void registry_alloc_utility()
{
command("memlist",meminfo);
}


