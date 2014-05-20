#ifndef __MATH_H
#define __MATH_H

#include "types.h"

float sinx(float);
float cosx(float);



#define min(a,b) (a>b ? b : a)
#define max(a,b) (a>b ? a : b)
#define abs(a)   (a>0 ? a : -a)
/*
float sqrt (float x)
{
	if (x<0) x=abs(x);
	if (x==0) return(0);
   float y1 , y2;
 
   y2 = x;
   for (int i=0;i<10;i++)
   {
      y1 = y2;
      y2 = (y1 + x/y1)/2;
   };
   return y2;
};*/





#endif
