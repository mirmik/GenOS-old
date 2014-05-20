#ifndef __MATRIX__H
#define __MATRIX__H



#include "types.h"
template <uint N, typename T>
class Vector {
	public:
	
	Vector(){
	for(uint i=0;i<N;i++)
	mas[i]=0;
	};
		
	T mas[N];
	
	void print();
	void print(char*);
	T& operator[](int i){return mas[i];};
	
	
	friend Print& operator<<(Print& p,Vector<N,T> &t){
	t.print();};
	
	Vector<N,T>& operator/(float f){
		Vector<N,T> VM;
		for(int i=0;i<N;i++) VM.mas[i]=mas[i]/f;
		return VM;		
		};
};




template <uint rows, uint columns, typename T>
class Matrix {
	public:
	Matrix(){};			
	Vector<columns,T> mas[rows];
	
	void print();
	void print(char*);
	Vector<columns,T>& operator[](int i){return (mas[i]);};
	void identity();
	
};






#include "simple.h"
template <uint rows, uint columns, typename T> void Matrix<rows,columns,T>::print()
{
	for(uint i=0;i<rows;i++)
	mas[i].print();	
};

#include "math/math.h"
template <uint rows, uint columns, typename T> void Matrix<rows,columns,T>::identity()
{
	for(uint i=0;i<min(rows,columns);i++)
	mas[i][i]=1;
};



template <uint N, typename T> void Vector<N,T>::print()
{
		for(int i=0;i<N;i++)
		*stdprint << mas[i] << '\t';
		*stdprint <<'\n';
};


template <uint rows, uint columns, typename T> void Matrix<rows,columns,T>::print(char* c)
{	
	*stdprint << c << '\n';
	for(uint i=0;i<rows;i++)
	mas[i].print();	
};

template <uint N, typename T> void Vector<N,T>::print(char* c)
{
		*stdprint << c << '\n';
		for(int i=0;i<N;i++)
		*stdprint << mas[i] << '\t';
		*stdprint <<'\n';
};

template <uint a, typename TM,typename TV> auto operator*(Matrix<a,a,TM> &M , Vector<a,TV> &V) ->
Vector<a,decltype(M[0][0]*V[0])>
{
	Vector<a,decltype(M[0][0]*V[0])> VM;
	for (int i=0;i<a;i++) 
	{VM[i]=0;
	for (int j=0;j<a;j++) 
	VM[i]=VM[i] + M[i][j] * V[j];}
	return VM;
};


template <uint a, typename TM> auto operator*(Matrix<a,a,TM> &M , float b) ->
Matrix<a,a,decltype(M[0][0]*b)>
{
	Matrix<a,a,decltype(M[0][0]*b)> VM;
	for (int i=0;i<a;i++) 
	for (int j=0;j<a;j++) 
	VM[i][j]=M[i][j] * b;
	return VM;
};

template <uint a, typename TM> auto operator*(float b, Matrix<a,a,TM> &M) ->
Matrix<a,a,decltype(M[0][0]*b)>
{
	Matrix<a,a,decltype(M[0][0]*b)> VM;
	for (int i=0;i<a;i++) 
	for (int j=0;j<a;j++) 
	VM[i][j]=M[i][j] * b;
	return VM;
};


template <uint a, typename TM> auto operator*(Matrix<a,a,TM> &M , int b) ->
Matrix<a,a,decltype(M[0][0]*b)>
{
	Matrix<a,a,decltype(M[0][0]*b)> VM;
	for (int i=0;i<a;i++) 
	for (int j=0;j<a;j++) 
	VM[i][j]=M[i][j] * b;
	return VM;
};

template <uint a, typename TM> auto operator*(int b, Matrix<a,a,TM> &M) ->
Matrix<a,a,decltype(M[0][0]*b)>
{
	Matrix<a,a,decltype(M[0][0]*b)> VM;
	for (int i=0;i<a;i++) 
	for (int j=0;j<a;j++) 
	VM[i][j]=M[i][j] * b;
	return VM;
};


template <uint m,uint p,uint n, typename T1,typename T2> auto operator*(Matrix<m,p,T1> A, Matrix<p,n,T2> B) ->
Matrix<m,n,decltype(A[0][0]*B[0][0])>
{
	Matrix<m,n,decltype(A[0][0]*B[0][0])> C;
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			C[i][j]=0;
			for (k=0;k<p;k++)
				C[i][j]= C[i][j]+A[i][k]*B[k][j];
		//*stdprint<<A[i][j]<<B[i][j]<<C[i][j]<<" ";
		}
	return C;
};










#include "math/math.h"
#define EPS 0.1e-15
template <uint n, typename T> Matrix<n,n,T> exp (Matrix<n,n,T> a)
 {
	Matrix<n,n,T> ea;
   
   int i, j, k, ii;
   T am, em, emi;

   T w[n*n];

   Matrix<n,n,T> wm;

     em = 0.;
     for( i = 0; i < n; i++ ){
       for( j = 0; j < n; j++ ){
	 ea[i][j] = 0.;
	 wm[i][j] = 0.;
	 am = abs(a[i][j]);
	 em = max(am,em);
       }
       ea[i][i] = 1.;
       wm[i][i] = 1.;
     }
     emi = 1.;
     ii = 0;
     while( emi > EPS ){
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
	   ea[i][j] += wm[i][j];
	   am = abs(wm[i][j]);
	   emi = max(am,emi);
	 }
     }
   return (ea);
 }






//Matrix Inversion Routine
// * This function inverts a matrix based on the Gauss Jordan method.
// * Specifically, it uses partial pivoting to improve numeric stability.
// * The algorithm is drawn from those presented in 
//	 NUMERICAL RECIPES: The Art of Scientific Computing.
// * The function returns 1 on success, 0 on failure.
// * NOTE: The argument is ALSO the result matrix, meaning the input matrix is REPLACED
//int MatrixInvert(float* A, int n)
template <uint n, typename T> Matrix<n,n,T> inv (Matrix<n,n,T> A)
{
	// A = input matrix AND result matrix
	// n = number of rows = number of columns in A (n x n)
	int pivrow;		// keeps track of current pivot row
	int k,i,j;		// k: overall index along diagonal; i: row index; j: col index
	int pivrows[n]; // keeps track of rows swaps to undo at end
	T tmp;		// used for finding max value and making column swaps

	for (k = 0; k < n; k++)
	{
		// find pivot row, the row with biggest entry in current column
		tmp = 0;
		for (i = k; i < n; i++)
		{
			if (abs(A[i][k]) >= tmp)	// 'Avoid using other functions inside abs()?'
			{
				tmp = abs(A[i][k]);
				pivrow = i;
			}
		}

		// check for singular matrix
		if (A[pivrow][k] == 0.0f)
		{
			prln("Inversion failed due to singular matrix");
			return A;
		}

		// Execute pivot (row swap) if needed
		if (pivrow != k)
		{
			// swap row k with pivrow
			for (j = 0; j < n; j++)
			{
				tmp = A[k][j];
				A[k][j] = A[pivrow][j];
				A[pivrow][j] = tmp;
			}
		}
		pivrows[k] = pivrow;	// record row swap (even if no swap happened)

		tmp = 1.0f/A[k][k];	// invert pivot element
		A[k][k] = 1.0f;		// This element of input matrix becomes result matrix

		// Perform row reduction (divide every element by pivot)
		for (j = 0; j < n; j++)
		{
			A[k][j] = A[k][j]*tmp;
		}

		// Now eliminate all other entries in this column
		for (i = 0; i < n; i++)
		{
			if (i != k)
			{
				tmp = A[i][k];
				A[i][k] = 0.0f;  // The other place where in matrix becomes result mat
				for (j = 0; j < n; j++)
				{
					A[i][j] = A[i][j] - A[k][j]*tmp;
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
				tmp = A[i][k];
				A[i][k] = A[i][pivrows[k]];
				A[i][pivrows[k]] = tmp;
			}
		}
	}
	return A;
}



template<uint n,uint m, typename T> 
Matrix<n,m,T> operator+ (Matrix<n,m,T>A,Matrix<n,m,T>B){
Matrix<n,m,T> C;
for(int i=0;i<n;i++)for(int j=0;j<n;j++) C[i][j]=A[i][j]+B[i][j];
return C; 
};

template<uint n,uint m, typename T> 
Matrix<n,m,T> operator- (Matrix<n,m,T>A,Matrix<n,m,T>B){
Matrix<n,m,T> C;
for(int i=0;i<n;i++)for(int j=0;j<n;j++) C[i][j]=A[i][j]-B[i][j];
return C; 
};




#endif
