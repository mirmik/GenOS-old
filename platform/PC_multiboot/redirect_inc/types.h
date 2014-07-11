#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>
typedef unsigned char byte;
typedef unsigned int size_t;
typedef unsigned char boolean;

typedef volatile unsigned long long vuint64_t;
typedef volatile unsigned int vuint32_t; 
typedef volatile unsigned short vuint16_t; 
typedef volatile unsigned char vuint8_t; 

typedef signed long long sint64_t;
typedef signed int sint32_t; 
typedef signed short sint16_t; 
typedef signed char sint8_t; 

typedef volatile long long vint64_t;
typedef volatile int vint32_t; 
typedef volatile short vint16_t; 
typedef volatile char vint8_t;  


typedef unsigned long long uint64_t;
typedef unsigned int uint32_t; 
typedef unsigned short uint16_t; 
typedef unsigned char uint8_t; 

typedef  uint64_t u64 ;
typedef  uint32_t u32; 
typedef  uint16_t u16; 
typedef  uint8_t  u8 ; 


///////////////////////////




struct __freelist {
	size_t sz;
	struct __freelist *nx;
};



//#define NULL 0


#endif
