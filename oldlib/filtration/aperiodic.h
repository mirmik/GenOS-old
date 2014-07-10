#ifndef APERIODIC_FILTRATION_H
#define APERIODIC_FILTRATION_H

/* Реализует линейную аппереодическую фильтрацию.
 * Передаточная функция фильтра W(s)=x/g=K/(Ts+1), где
 * x - накопленное значение. 
 * g - входное воздействие.
 * T - постоянная времени.
 * K - коэф. усиления.
 * 
 * Непосредственный расчет ведётся по формуле x(n+1) := x(n) + Az*(g(n) - x(n)) 
 * , где Az = (1 - exp(-h/T)) . 
 * h - шаг.
*/

//aperiodic_float_stepped_filter
class AFS_filter 
{public:
float x;
float Az;		

void init(float x0,float T,float h);
float calculate (float);
};
#endif
