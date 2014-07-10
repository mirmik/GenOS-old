#ifndef SIMPLE_H
#define SIMPLE_H


//#include "time.h"
#include <inttypes.h>
#include "prototype/Stream.h"
#include "prototype/Print.h"
#include "allocator/allocator.h"
#include "charqueue/queue.h"

void DoNothing();

//typedef uint8_t boolean;

class Stream;
extern Print * stdprint; 
extern Stream * tracert;
class Allocator_p;
extern Allocator_p * stdalloc; 

#define prlnhex(a) 	stdprint->println((int)a,HEX);
#define prhex(a) 	stdprint->print((int)a,HEX);
#define pr(a) 	stdprint->print(a);
#define prln(a) stdprint->println(a);
#define prtab() stdprint->write('\t');

#define TRACERT 1

//#define DEBUG_TRACERT

#ifdef DEBUG_TRACERT
#include "debug/debug.h"
#define tprlnhex(a)  if (LOCAL_TRACERT<=TRACERT) {debug_printhex_int32((int)a); dln;}
#define tprhex(a) 	if (LOCAL_TRACERT<=TRACERT)	debug_printhex_int32((int)a);
#define tpr(a) 		if (LOCAL_TRACERT<=TRACERT)	debug_print(a);
#define tprdec(a) 		tprhex(a)
#define tprln(a) 		if (LOCAL_TRACERT<=TRACERT) {debug_print(a); dln;}
#define tprlndec(a) 	tprlnhex(a)
#define tprtab() 		if (LOCAL_TRACERT<=TRACERT) debug_putchar('\t');
#else
#ifdef TRACERT
#define tprlnhex(a)  if (LOCAL_TRACERT<=TRACERT) tracert->println((int)a,HEX);
#define tprhex(a) 	if (LOCAL_TRACERT<=TRACERT)	tracert->print((int)a,HEX);
#define tpr(a) 		if (LOCAL_TRACERT<=TRACERT)	tracert->print(a);
#define tprdec(a) 		tpr(a)
#define tprln(a) 		if (LOCAL_TRACERT<=TRACERT) tracert->println(a);
#define twrite(a,b) 		if (LOCAL_TRACERT<=TRACERT) tracert->write(a,b);
#define tprlndec(a) 	tprln(a);
#define tprtab() 		if (LOCAL_TRACERT<=TRACERT)	tracert->write('\t');
#else
#define tprlnhex(a) 	{}
#define tprhex(a) 		{}
#define tpr(a) 			{}
#define tprln(a) 		{}
#define twrite(a) 		{}
#define tprtab() 			{}
#endif //TRACERT
#endif //DEBUG_TRACERT





uint8_t statusBit(uint8_t &f,uint8_t a);
void setBit(uint8_t &f,uint8_t a);
void clrBit(uint8_t &f,uint8_t a);

#define FIND_FIRST_OPERAND(c,d) \
{for (;(*c!=0) && (*c==' '); c++);\
d=c;                                                    \
for (;(*d!=0) && (*d!=' '); d++);}

#define CUT_FIRST_OPERAND(c,d) \
{FIND_FIRST_OPERAND(c,d); \
if (*d!=0) {*d=0;d++;}}

	
	
	
	#endif
