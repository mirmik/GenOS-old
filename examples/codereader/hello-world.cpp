
#include "platform.h"
#include "C_stream.h"
#include "allocator/allocator.h"
#include "delay.h"
#include "allocator/alloc_standart.h"
#include "intcom/command_list.h"
#include "utility.h"
#
#include "debug/debug.h"
Print* stdprint=&term;
Stream* tracert=&term;
Allocator_p * stdalloc=&galloc;

int main(){
term.begin();
while (1)
{
	int i = term.read();
	if (i!=-1)
		{
			switch (i){
			case '\n': 	stdprint->print("eq \\n");break;
			case '\t': 	stdprint->print("eq \\t");break;
			case '\r': 	stdprint->print("eq \\r");break;
			default:	stdprint->write(i);	  break;
			} 
			prtab(); dpr_inthex(i); prln();
		}	
	}
term.end();
	}
