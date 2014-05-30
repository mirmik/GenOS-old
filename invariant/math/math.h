#ifndef __MATH_H
#define __MATH_H

#include "types.h"

float sinx(float);
float cosx(float);



template <typename T> T min(const T a, const T b) {return (a>b ? b : a);}
template <typename T> T max(const T a, const T b) {return (a>b ? a : b);}
//template <typename T> T abs(const T x) {return (x>0 ? x : -x );}
 int abs(const int x) {return (x>0 ? x : -x );}
 float abs(const float x) {return (x>0 ? x : -x );}

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
};





#endif
