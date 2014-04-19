

#ifndef GENOS_H
#define GENOS_H

#include "classlist.h"

#include "def.h"

#include <inttypes.h>
#include "utility.h"
#include "simple.h"
//#include "socket.h"
#include "linuxlist.h"
//#include "Print.h"
//#include "Stream.h"
//#include "command_list.h"
//#include "delay.h"
//#include "microrl++.h"
//#include "handshake.h"
//#include "StrmNull.h"
//#include "csh.h"
//#include "transport.h"

//#include "config.h"

extern Stream * stdio;


void idle();
void OS_config();
void OS_end();
void setup();




#endif
