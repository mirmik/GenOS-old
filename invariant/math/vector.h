
#ifndef __VECTOR_H
#define __VECTOR_H

#include "simple.h"

template<uint n, typename Type>
class Vector
{public:
Type V[n];

Type& operator[](int i){return (*(V+i));};
Type operator[](int i) const {return (*(V+i));};


Vector<n,Type>& operator=(Vector<n,Type> const &V2) {for (int i=0;i<n;i++) V[n]=V2[n]; return *this;};

void zero() {for(int i=0;i<n;i++) V[i]=0;};
void print() const {for(int i=0;i<n;i++) *stdprint << V[i] << '\t'; *stdprint << '\n';};
};




/////////////////SUM///////////////////////
template<uint n,typename T1, typename T2, typename T3>
class V_sum : public Vector<n,T3>
{
	public:
	V_sum(Vector<n,T1> const &A, Vector<n,T2> const &B)
	{
		for(int i=0;i<n;i++) Vector<n,T3>::V[i]=A[i]+B[i];
		};
	
	~V_sum(){};
};

template<uint n,typename T1,typename T2>
auto const operator+(Vector<n,T1> const &A, Vector <n,T2> const &B) -> V_sum<n,T1,T2,decltype(A[0]+B[0])>
{return V_sum<n,T1,T2,decltype(A[0]+B[0])>(A,B);};
//////////////////////////////////////////


/////////////////SUB///////////////////////
template<uint n,typename T1, typename T2, typename T3>
class V_sub : public Vector<n,T3>
{
	public:
	V_sub(Vector<n,T1> const &A, Vector<n,T2> const &B)
	{		
		for(int i=0;i<n;i++) Vector<n,T3>::V[i]=A[i]-B[i];
		};
	
	~V_sub(){};
};

template<uint n,typename T1,typename T2>
auto const operator-(Vector<n,T1> const &A, Vector <n,T2> const &B) -> V_sub<n,T1,T2,decltype(A[0]-B[0])>
{return V_sub<n,T1,T2,decltype(A[0]-B[0])>(A,B);};
//////////////////////////////////////////





///////////////////////MUX////////////////
template<uint n,typename T1,typename T2>
auto const operator*(Vector<n,T1> const &A, Vector <n,T2> const &B) -> decltype(A[0]*B[0])
{
	decltype(A[0]*B[0]) ex=0;
	for(int i=0;i<n;i++) ex=ex+A[i]*B[i];
	return ex;};
//////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////ABS////////////////
template<uint n,typename T1>
T1 abs(Vector<n,T1> const &A)
{	
	T1 ex;
	for(int i=0;i<n;i++) ex=ex+A[i]*A[i];
	return sqrt(ex);};
//////////////////////////////////////////////////////////////////////////////////////////////////





















#endif
