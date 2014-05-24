#ifndef MATRIX2_H
#define MATRIX2_H

#include "math/matrix_alg.h"


class Index{public: int m;int n;Index(int _m, int _n):m(_m),n(_n){};};


template<uint m, uint n, typename Type>
class Matrix{
public: 
Type M[m*n];

Matrix(){};
Matrix(const Matrix<m,n,Type> &M2){matrix_copy(M2.M,m,n,M);};

Type& operator[](Index I){return *(M+I.m*n+I.n);};
Type operator[](Index I) const {return *(M+I.m*n+I.n);};
Type* operator[](int i){return (M+i*n);};
const Type* operator[](int i) const {return (M+i*n);};

Matrix<m,n,Type>& operator=(Matrix<m,n,Type> const &M2) {matrix_copy(M2.M,m,n,M); return *this;};

void zero() {for(int i=0;i<m;i++)for(int j=0;j<n;j++)  M[i*n+j]=0;};
void identity() {for(int i=0;i<m;i++)for(int j=0;j<n;j++)   M[i*n+j]=((i==j) ? 1 : 0);}
void print() {for(int i=0;i<m;i++) {for(int j=0;j<n;j++)  *stdprint << M[i*n+j]<<'\t'; *stdprint << '\n';};};
};

///////////////////////MUX/////////////////
template<uint n, uint p, uint m, typename T1,typename T2, typename T3>
class M_mux : public Matrix<n,m,T3>
{	
	public:
	
	M_mux(Matrix<m,p,T1> const &A, Matrix<p,n,T2> const &B)
	{matrix_mux(A.M,B.M,m,p,n,Matrix<m,n,T3>::M);};
	
	~M_mux(){};
};

template<uint m,uint p,uint n,typename T1,typename T2>
auto const operator*(Matrix<m,p,T1> const &A, Matrix <p,n,T2> const &B) -> M_mux<m,p,n,T1,T2,decltype(A[0][0]*B[0][0])>
{return M_mux<m,p,n,T1,T2,decltype(A[0][0]*B[0][0])>(A,B);};
//////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////SUM///////////////////////
template<uint m,uint n,typename T1, typename T2, typename T3>
class M_sum : public Matrix<m,n,T3>
{
	public:
	M_sum(Matrix<m,n,T1> const &A, Matrix<m,n,T2> const &B)
	{matrix_add(A.M,B.M,m,n,Matrix<m,n,T3>::M);};
	
	~M_sum(){};
};

template<uint m,uint n,typename T1,typename T2>
auto const operator+(Matrix<m,n,T1> const &A, Matrix <m,n,T2> const &B) -> M_sum<m,n,T1,T2,decltype(A[0][0]*B[0][0])>
{return M_sum<m,n,T1,T2,decltype(A[0][0]*B[0][0])>(A,B);};
//////////////////////////////////////////



/////////////////SUB///////////////////////
template<uint m,uint n,typename T1, typename T2, typename T3>
class M_sub : public Matrix<m,n,T3>
{
	public:
	
	M_sub(Matrix<m,n,T1> const &A, Matrix<m,n,T2> const &B)
	{matrix_sub(A.M,B.M,m,n,Matrix<m,n,T3>::M);};
	
	~M_sub(){};
};

template<uint m,uint n,typename T1,typename T2>
auto const operator-(Matrix<m,n,T1> const &A, Matrix <m,n,T2> const &B) -> M_sub<m,n,T1,T2,decltype(A[0][0]*B[0][0])>
{return M_sub<m,n,T1,T2,decltype(A[0][0]*B[0][0])>(A,B);};
//////////////////////////////////////////


/////////////////SCALE///////////////////////
template<uint m,uint n,typename T1, typename T2, typename T3>
class M_scale : public Matrix<m,n,T3>
{
	public:
	M_scale(T2 r, Matrix<m,n,T1> const &A)
	{matrix_scale(A.M,r,m,n,Matrix<m,n,T3>::M);};
	
	M_scale(Matrix<m,n,T1> const &A, T2 r)
	{matrix_scale(A.M,r,m,n,Matrix<m,n,T3>::M);};
	
	~M_scale(){};
};

template<uint m,uint n, typename T1, typename T2>
auto const operator*(Matrix<m,n,T1> const &A, T2 r) -> M_scale<m,n,T1,T2,decltype(A[0][0]*r)>
{return M_scale<m,n,T1,T2,decltype(r*A[0][0])>(A,r);};

template<uint m,uint n, typename T1, typename T2>
auto const operator*(T2 r, Matrix<m,n,T1> const &A) -> M_scale<m,n,T1,T2,decltype(r*A[0][0])>
{return M_scale<m,n,T1,T2,decltype(r*A[0][0])>(r,A);};
////////////////////////////////////////////

/////////////////INV///////////////////////
template<uint m,uint n,typename T1>
class M_inv : public Matrix<m,n,T1>
{
	public:
	M_inv(Matrix<m,n,T1> const &A)
	{matrix_inv(A.M,m,n,Matrix<m,n,T1>::M);};
	
	~M_inv(){};
};

template<uint m,uint n, typename T1>
Matrix<m,n,T1> inv(Matrix<m,n,T1> const &A)
{return M_inv<m,n,T1>(A);};
////////////////////////////////////////////

/////////////////EXP///////////////
template<uint n,typename T1>
class M_exp : public Matrix<n,n,T1>
{
	public:
	M_exp(Matrix<n,n,T1> const &A)
	{matrix_exp(A.M,n,Matrix<n,n,T1>::M);};
	
	~M_exp(){};
};

template<uint n, typename T1>
Matrix<n,n,T1> exp(Matrix<n,n,T1> const &A)
{return M_exp<n,T1>(A);};
///////////////////////////////////////



/////////////////TRANS///////////////
template<uint m, uint n, typename T1>
class M_trans : public Matrix<m,n,T1>
{
	public:
	M_trans(Matrix<n,m,T1> const &A)
	{matrix_transpose(A.M,m,n,Matrix<m,n,T1>::M);};
	
	~M_trans(){};
};

template<uint n, uint m, typename T1>
Matrix<m,n,T1> transpose(Matrix<n,m,T1> const &A)
{return M_trans<m,n,T1>(A);};
///////////////////////////////////////

#endif




