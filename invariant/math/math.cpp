

#include "math/math.h"




float sinx(float x) {
 
    float n = x, sum = 0.L;
    int i = 1;
 
    do {
        sum += n;
        n *= -1.0 * x * x / ((2 * i) * (2 * i + 1));
        ++i;
    } while ((n > 0.0 ? n : -n) > 1e-9);
 
    return sum;
}
	
float cosx(float x) {

    float n = 1, sum = 1.L;
    int i = 1;
 
     do {
        n *= -1.0 * x * x / ((2 * i) * (2 * i - 1));
        sum += n;
        ++i;
    } while ((n > 0.0 ? n : -n) > 1e-9);
    
    return sum;
}

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


