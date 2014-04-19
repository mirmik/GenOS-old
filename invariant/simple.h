#ifndef SIMPLE_H
#define SIMPLE_H


#include "time.h"
#include <inttypes.h>
#include "prototype/Stream.h"


void DoNothing();

typedef uint8_t boolean;

class Stream;
extern Stream * stdio; 
#define prlnhex(a) 	stdio->println((int)a,HEX);
#define prhex(a) 	stdio->print((int)a,HEX);
#define pr(a) stdio->print(a);
#define prln(a) stdio->println(a);
#define prtab stdio->write('\t');

uint8_t statusBit(uint8_t &f,uint8_t a);
void setBit(uint8_t &f,uint8_t a);
void clrBit(uint8_t &f,uint8_t a);


#define DROP_SPACE(c); for (;(*c!=0) && (*c==' '); c++);

#define FIND_FIRST_OPERAND(c,d) \
{for (;(*c!=0) && (*c==' '); c++);\
d=c;                                                    \
for (;(*d!=0) && (*d!=' '); d++);}

#define CUT_FIRST_OPERAND(c,d) \
{FIND_FIRST_OPERAND(c,d); \
if (*d!=0) {*d=0;d++;}}


#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

/*
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */


#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})
	
	
	
	
	#endif
