#ifndef TYPES_H
#define TYPES_H



///////arm926ejs///////////
/*
typedef long long int64_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;
typedef unsigned char boolean;

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
typedef unsigned char byte;
*/

typedef unsigned char byte;
typedef unsigned int size_t;
typedef unsigned char boolean;

typedef volatile unsigned long long vuint64_t;
typedef volatile unsigned int vuint32_t; 
typedef volatile unsigned short vuint16_t; 
typedef volatile unsigned char vuint8_t; 

typedef volatile long long vint64_t;
typedef volatile int vint32_t; 
typedef volatile short vint16_t; 
typedef volatile char vint8_t;  

///////////////////////////




struct __freelist {
	size_t sz;
	struct __freelist *nx;
};



//#define NULL 0


#endif
