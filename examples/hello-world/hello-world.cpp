
#include "C_stream.h"
#include "debug_print.h"
#include "platform.h"
#include <vector>
#include "readline.h"
#include "rl_terminal.h"

#include "command_list.h"

#include "ASCII2KeyCom.h"
#include "KeyCom2ASCII.h"

KeyCom2ASCII K2A(&term);
readline_t rl;
rl_terminal rl_term(&rl, &K2A);
ASCII2KeyCom A2K(&rl_term);

void task1 () {};

Print* stdprint = &term; 

extern "C" void __cxa_pure_virtual() { while (1); }
std::vector<float> F;

int main(){
term.begin();
term.print("helloWorld\n");

command("task1",task1);
command_print();

int c;
while(1){if ((c = term.read()) !=-1) A2K.write(c);};

term.end();
}



