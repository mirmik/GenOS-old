#ifndef MATRIX2_H
#define MATRIX2_H

#include "genoslib.h"
#include "math/math.h"

class Index{public: int n;int m;Index(int _n, int _m):n(_n),m(_m){};};

template<uint n,uint m, typename Type>
class M_E{
public: 
M_E(){};
Type M[n][m];
Type& operator[](Index I){return M[I.n][I.m];};
Type operator[](Index I) const {return M[I.n][I.m];};
Type*& operator[](int i){return M[i];};
const Type* operator[](int i) const {return M[i];};
M_E(const M_E<n,m,Type> &M2){dstdfor(i,n,j,m) M[i][j]=M2[i][j];};

void identity() {dstdfor(i,n,j,m)  M_E<n,m,Type>::M[i][j]=((i==j) ? 1 : 0);}
void print() {stdfor(i,n) {stdfor(j,m) *stdprint << M_E<n,m,Type>::M[i][j]<<'\t'; *stdprint << '\n';};}
M_E<n,m,Type>& operator=(M_E<n,m,Type> const &M2) {dstdfor(i,n,j,m) M_E<n,m,Type>::M[i][j]=M2[i][j]; return *this;};
};

template<uint n,uint m, typename Type>
class Matrix : public M_E<n,m,Type>
{public:
Matrix(){dstdfor(i,n,j,m) M_E<n,m,Type>::M[i][j]=0;};
~Matrix(){};
Matrix<n,m,Type>& operator=(M_E<n,m,Type> const &M2) {dstdfor(i,n,j,m) M_E<n,m,Type>::M[i][j]=M2[i][j]; return *this;};
};

template<uint n, uint p, uint m, typename Type>
class M_mul : public M_E<n,m,Type>
{public:
M_mul(M_E<n,p,Type> const &A, M_E<p,m,Type> const &B)
{
dstdfor(i,n,j,m){ 
M_E<n,m,Type>::M[i][j]=0;
stdfor(k,p)  M_E<n,m,Type>::M[i][j]=M_E<n,m,Type>::M[i][j]+A[i][k]*B[k][j];};
};
~M_mul(){};
};

template<uint n,uint m, typename Type>
class M_sum : public M_E<n,m,Type>
{public:
M_sum(M_E<n,m,Type> const &A, M_E<n,m,Type> const &B){dstdfor(i,n,j,m) M_E<n,m,Type>::M[i][j]=A[i][j]+B[i][j];};
~M_sum(){}
};

template<uint n,uint m, typename Type>
class M_dif : public M_E<n,m,Type>
{public:
M_dif(M_E<n,m,Type> const &A, M_E<n,m,Type> const &B){dstdfor(i,n,j,m) M_E<n,m,Type>::M[i][j]=A[i][j]-B[i][j];};
~M_dif(){}
};


template<uint n,uint m, typename Type>
class M_scale : public M_E<n,m,Type>
{public:
M_scale(int r, M_E<n,m,Type> const &A){dstdfor(i,n,j,m) M_E<n,m,Type>::M[i][j]=A[i][j]*r;};
M_scale(M_E<n,m,Type> const &A, int r){dstdfor(i,n,j,m) M_E<n,m,Type>::M[i][j]=A[i][j]*r;};
~M_scale(){}
};


template<uint n,typename Type>
class M_inv : public M_E<n,n,Type>
{public:
M_inv(M_E<n,n,Type> const &B){
	
    dstdfor(i,n,j,n) M_E<n,n,Type>::M[i][j]=B.M[i][j];
    
    
	// A = input matrix AND result matrix
	// n = number of rows = number of columns in A (n x n)
	int pivrow;		// keeps track of current pivot row
	int k,i,j;		// k: overall index along diagonal; i: row index; j: col index
	int pivrows[n]; // keeps track of rows swaps to undo at end
	Type tmp;		// used for finding max value and making column swaps

	for (k = 0; k < n; k++)
	{
		// find pivot row, the row with biggest entry in current column
		tmp = 0;
		for (i = k; i < n; i++)
		{
			if (abs((M_E<n,n,Type>::M[i][k])) >= tmp)	// 'Avoid using other functions inside abs()?'
			{
				tmp = abs(M_E<n,n,Type>::M[i][k]);
				pivrow = i;
			}
		}

		// check for singular matrix
		if (M_E<n,n,Type>::M[pivrow][k] == 0.0f)
		{
			prln("Inversion failed due to singular matrix");
		}

		// Execute pivot (row swap) if needed
		if (pivrow != k)
		{
			// swap row k with pivrow
			for (j = 0; j < n; j++)
			{
				tmp = M_E<n,n,Type>::M[k][j];
				M_E<n,n,Type>::M[k][j] = M_E<n,n,Type>::M[pivrow][j];
				M_E<n,n,Type>::M[pivrow][j] = tmp;
			}
		}
		pivrows[k] = pivrow;	// record row swap (even if no swap happened)

		tmp = 1.0f/M_E<n,n,Type>::M[k][k];	// invert pivot element
		M_E<n,n,Type>::M[k][k] = 1.0f;		// This element of input matrix becomes result matrix

		// Perform row reduction (divide every element by pivot)
		for (j = 0; j < n; j++)
		{
			M_E<n,n,Type>::M[k][j] = M_E<n,n,Type>::M[k][j]*tmp;
		}

		// Now eliminate all other entries in this column
		for (i = 0; i < n; i++)
		{
			if (i != k)
			{
				tmp = M_E<n,n,Type>::M[i][k];
				M_E<n,n,Type>::M[i][k] = 0.0f;  // The other place where in matrix becomes result mat
				for (j = 0; j < n; j++)
				{
					M_E<n,n,Type>::M[i][j] = M_E<n,n,Type>::M[i][j] - M_E<n,n,Type>::M[k][j]*tmp;
				}
			}
		}
	}

	// Done, now need to undo pivot row swaps by doing column swaps in reverse order
	for (k = n-1; k >= 0; k--)
	{
		if (pivrows[k] != k)
		{
			for (i = 0; i < n; i++)
			{
				tmp = M_E<n,n,Type>::M[i][k];
				M_E<n,n,Type>::M[i][k] = M_E<n,n,Type>::M[i][pivrows[k]];
				M_E<n,n,Type>::M[i][pivrows[k]] = tmp;
			}
		}
	}
	
	};
~M_inv(){}
};


template<uint n, typename Type>
class M_exp : public M_E<n,n,Type>
{public:
M_exp(M_E<n,n,Type> const &a){
   int i, j, k, ii;
   Type am, em, emi;
   Type w[n*n];

   Type wm[n][n];
 
     em = 0.;
     for( i = 0; i < n; i++ ){
       for( j = 0; j < n; j++ ){
	 M_E<n,n,Type>::M[i][j] = 0;
	 wm[i][j] = 0;
	 am = abs(a[i][j]);
	 em = max(am,em);
       }
       M_E<n,n,Type>::M[i][i] = 1;
       wm[i][i] = 1;
     }
     emi = 1;
     ii = 0;
     while( emi > 0.1e-15 ){
       ii++;
       if( ii >= 50 ) break;
       emi = 0.;
       for( j = 0; j < n; j++ ){
	 for( i = 0; i < n; i++ )
	   w[i] = wm[i][j];
	 for( i = 0; i < n; i++ ){
	   wm[i][j] = 0.;
	   for( k = 0; k < n; k++ )
	     wm[i][j] += a[i][k] * w[k];
	 }
       }
       for( i = 0; i < n; i++ )
	 for( j = 0; j < n; j++ ){
	   wm[i][j] /= (float)ii;
	   M_E<n,n,Type>::M[i][j] += wm[i][j];
	   am = abs(wm[i][j]);
	   emi = max(am,emi);
	 }
     }
  
};

~M_exp(){}
};




template<uint n,uint m, typename Type>
M_sum<n,m,Type> const operator+(M_E<n,m,Type> const &A, M_E<n,m,Type> const &B){return M_sum<n,m,Type>(A,B);};

template<uint n,uint m, typename Type>
M_dif<n,m,Type> const operator-(M_E<n,m,Type> const &A, M_E<n,m,Type> const &B){return M_dif<n,m,Type>(A,B);};

template<uint n, uint p, uint m, typename Type>
M_mul<n,p,m,Type> const operator*(M_E<n,p,Type> const &A, M_E<p,m,Type> const &B){return M_mul<n,p,m,Type>(A,B);};

template<uint n,uint m, typename Type>
M_scale<n,m,Type> const operator*(M_E<n,m,Type> const &A, int r){return M_scale<n,m,Type>(A,r);};

template<uint n,uint m, typename Type>
M_scale<n,m,Type> const operator*(int r, M_E<n,m,Type> const &A){return M_scale<n,m,Type>(r,A);};

template<uint n, typename Type>
M_exp<n,Type> const exp(M_E<n,n,Type> const &A){return M_exp<n,Type>(A);};


template<uint n, typename Type>
M_inv<n,Type> const inv(M_E<n,n,Type> const &B){return M_inv<n,Type>(B);};

#endif




