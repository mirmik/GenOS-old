#ifndef COMMAND_LIST_H
#define COMMAND_LIST_H

#include "glist.h"
#include "simple.h"
//#include "allocator/allocator.h"
//#include "GenOS.h"

struct argvc_t {
	char ** argv;
	int argc;
	};

void split(char* temp, argvc_t &a);

void execute(char* c);

 extern list_head command_head;
  
 struct command_t
 {
char* mnem; 
list_head list;
size_t func;
 };
 
 #define command(a,c) command_add(a, (size_t) c)
  void command_add (char* a, size_t c);
 void command_print();
 int interpreter(int argv, const char* const* argc);
 /*
class list_t 
{public:
char* mnem; 
list_head list;
size_t address;
size_t type;
};*/



#endif
