#ifndef __MATH_H
#define __MATH_H

#include "types.h"

float sinx(float);
float cosx(float);



template <typename T> T min(const T a, const T b) {return (a>b ? b : a);}
template <typename T> T max(const T a, const T b) {return (a>b ? a : b);}
//template <typename T> T abs(const T x) {return (x>0 ? x : -x );}
 int abs(const int x);
 float abs(const float x);

float sqrt (float x);





#endif
