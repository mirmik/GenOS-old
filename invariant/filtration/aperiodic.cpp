#include "filtration/aperiodic.h"
#include "genoslib.h"



void AFS_filter::init(float x0,float T, float h)
{
x=x0;
Az = 1 - exp(-h/T);		
}  


float AFS_filter::calculate(float g)
{
	x = x + Az*(g - x);
	return x;
}  
