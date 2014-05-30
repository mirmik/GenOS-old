
#ifndef GENOSLIB_H
#define GENOSLIB_H

#include "genoslib/types.h"
//#include "genoslib/exports.h"


#ifdef __cplusplus
extern "C" {
#endif

void swap_char(char* a, char* b);
void num2base_str(char* dec_str, uint32_t value, int base);
void str_reverse(char* str);
int limitation(int a,int min,int max);

//#define stdfor(i,n) for(int i=0;i<n;i++) 
//#define dstdfor(i,n,j,m) for(int i=0;i<n;i++)for(int j=0;j<m;j++) 

//float exp(float,int iter=10);

#ifdef __cplusplus
}
#endif

#endif
