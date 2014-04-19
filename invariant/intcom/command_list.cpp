

#include "command_list.h"


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

int interpreter(int argv, const char* const* argc){
	//Stream* tempstrm
	command_t* p;
list_for_each_entry(p,&command_head,list)

if (!strcmp(argc[0],p->mnem)) 
{
//tempstrm=(Stream*)stdio;
//stdio=strm;
((void (*)(int, const char* const*))(p->func))(argv,argc);
//stdio=tempstrm; 
return 0;
}
prln("Command not found. Use \"\033[33mlist\033[0m\" instruction.");

return 0;
};
		
