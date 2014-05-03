

#include "command_list.h"
#include "genoslib.h"


LIST_HEAD (command_head);


 void command_add (char* a,size_t c)
 {command_t* temp=new(command_t);
 list_add_tail(&temp->list,&command_head);
 temp->mnem=a;
 temp->func=c;
 }


void command_print()
{command_t* p;
list_for_each_entry(p,&command_head,list)
{
pr(p->mnem); 
prln();
};
};

int interpreter(int argc, const char* const* argv){
	//Stream* tempstrm
	command_t* p;
list_for_each_entry(p,&command_head,list)

if (!strcmp(argv[0],p->mnem)) 
{
//tempstrm=(Stream*)stdio;
//stdio=strm;
((void (*)(int, const char* const*))(p->func))(argc,argv);
//stdio=tempstrm; 
return 0;
}
pr("Command \"\033[35m");
pr(argv[0]);
prln("\033[0m\" not found. Use \"\033[33mlist\033[0m\" instruction.");

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


void execute(char* c)
{
		argvc_t a;
		char* argv [10];
		a.argv=argv;
		split(c,a);
		interpreter(a.argc,a.argv);
};
