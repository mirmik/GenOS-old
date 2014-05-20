
#ifndef GENOSLIB_H
#define GENOSLIB_H

#include "genoslib/types.h"
#include "genoslib/exports.h"


#ifdef __cplusplus
extern "C" {
#endif

void swap_char(char* a, char* b);
void num2base_str(char* dec_str, uint32_t value, int base);
void str_reverse(char* str);
int limitation(int a,int min,int max);

//#ifndef abs
//#define abs(__x) (__x>0 ? __x : -__x)
//#endif

//float exp(float,int iter=10);

#ifdef __cplusplus
}
#endif

#endif
