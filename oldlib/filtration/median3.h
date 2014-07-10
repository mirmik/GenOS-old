#ifndef MEDIAN3_t_H
#define MEDIAN3_t_H

#include "types.h"

template <typename type>
class median3
{public:
uint8_t count;
type x[3];
type calculate(type);
void init();
};



template<typename type> type median3<type>::calculate (type g)
{
x[count] = g;
count = (++count) % 3;

uint8_t r[3]={0,0,0};

(x[0]<=x[1]) ? r[1]++ : r[0]++; 
(x[0]<=x[2]) ? r[2]++ : r[0]++;
(x[1]<=x[2]) ? r[2]++ : r[1]++;

for (uint8_t i=0;i<3;i++) if (r[i]==1) return x[i];  		
return(0);
} 


template<typename type> void median3<type>::init()
{
x[0]=0;x[1]=0;x[2]=0;
count=0;
} 



#endif
