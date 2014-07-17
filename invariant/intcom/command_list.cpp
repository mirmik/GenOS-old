

#include "command_list.h"
#include "GenosPrint.h"
#include "string.h"

std::vector<command_t> command_vector;

 void command_add (char* a,size_t c)
 {command_t* temp=new command_t;
 temp->mnem=a;
 temp->func=c;
 command_vector.push_back(*temp);
 }


void command_print()
{
for (std::vector<command_t>::iterator it = command_vector.begin() ; it != command_vector.end() ; it++)
{
pr(it->mnem); 
prln();
};
};

int interpreter(int argc, const char* const* argv){

for (std::vector<command_t>::iterator it = command_vector.begin() ; it != command_vector.end() ; it++)

if (!strcmp(argv[0],it->mnem)) 
{
//tempstrm=(Stream*)stdio;
//stdio=strm;
((void (*)(int, const char* const*))(it->func))(argc,argv);
//stdio=tempstrm; 
return 0;
}
//pr("Command \"\033[35m");
pr("Command \"");
pr(argv[0]);
//prln("\033[0m\" not found. Use \"\033[33mlist\033[0m\" instruction.");
prln("\" not found. Use \"list\" instruction.");

return 0;
};
		

#define DROP_SPACE(c); for (;(*c!=0) && (*c==' '); c++);
#define DROP_OP(c); for (;(*c!=0) && (*c!=' '); c++);

// split cmdline to tkn array and return nmb of token
void split (char* temp, argvc_t &a)
{	a.argc=0;
	while((*temp) !=0) {
	DROP_SPACE(temp);
	if (*temp != 0) {
		a.argv[a.argc]=temp;
		a.argc++;}
	DROP_OP(temp);
	if (*temp!=0) {*temp='\0';temp++;
		}
	}
	//tprln(argc);
}


void sysexecute(char* c)
{
		argvc_t a;
		char* argv [10];
		a.argv=argv;
		split(c,a);
		interpreter(a.argc,a.argv);
};
