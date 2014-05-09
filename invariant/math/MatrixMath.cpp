/*
 *  MatrixMath.cpp Library for Matrix Math
 *
 *  Created by Charlie Matlack on 12/18/10.
 *  Modified from code by RobH45345 on Arduino Forums, taken from unknown source.
 *  
 */
#include "simple.h"
#include "genoslib.h"
#include "MatrixMath.h"

#define NR_END 1

// Matrix Printing Routine
// Uses tabs to separate numbers under assumption printed float width won't cause problems
void MatrixPrint(float* A, int m, int n, char* label){
	// A = input matrix (m x n)
	int i,j;
	prln();
	prln(label);
	for (i=0; i<m; i++){
		for (j=0;j<n;j++){
			stdprint->print(A[n*i+j],15);
			pr("\t");
		}
		prln();
	}
}

void MatrixCopy(float* A, int n, int m, float* B)
{
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			B[n*i+j] = A[n*i+j];
		}
}

void MatrixZero(float* A, int n, int m)
{
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			A[n*i+j] = 0;
		}
}
//Matrix Multiplication Routine
// C = A*B
void MatrixMultiply(float* A, float* B, int m, int p, int n, float* C)
{
	// A = input matrix (m x p)
	// B = input matrix (p x n)
	// m = number of rows in A
	// p = number of columns in A = number of rows in B
	// n = number of columns in B
	// C = output matrix = A*B (m x n)
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			C[n*i+j]=0;
			for (k=0;k<p;k++)
				C[n*i+j]= C[n*i+j]+A[p*i+k]*B[n*k+j];
		}
}


//Matrix Addition Routine
void MatrixAdd(float* A, float* B, int m, int n, float* C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A+B (m x n)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[n*i+j]=A[n*i+j]+B[n*i+j];
}


//Matrix Subtraction Routine
void MatrixSubtract(float* A, float* B, int m, int n, float* C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A-B (m x n)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[n*i+j]=A[n*i+j]-B[n*i+j];
}


//Matrix Transpose Routine
void MatrixTranspose(float* A, int m, int n, float* C)
{
	// A = input matrix (m x n)
	// m = number of rows in A
	// n = number of columns in A
	// C = output matrix = the transpose of A (n x m)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[m*j+i]=A[n*i+j];
}

void MatrixScale(float* A, int m, int n, float k)
{
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
			A[n*i+j] = A[n*i+j]*k;
}


//Matrix Inversion Routine
// * This function inverts a matrix based on the Gauss Jordan method.
// * Specifically, it uses partial pivoting to improve numeric stability.
// * The algorithm is drawn from those presented in 
//	 NUMERICAL RECIPES: The Art of Scientific Computing.
// * The function returns 1 on success, 0 on failure.
// * NOTE: The argument is ALSO the result matrix, meaning the input matrix is REPLACED
int MatrixInvert(float* A, int n)
{
	// A = input matrix AND result matrix
	// n = number of rows = number of columns in A (n x n)
	int pivrow;		// keeps track of current pivot row
	int k,i,j;		// k: overall index along diagonal; i: row index; j: col index
	int pivrows[n]; // keeps track of rows swaps to undo at end
	float tmp;		// used for finding max value and making column swaps

	for (k = 0; k < n; k++)
	{
		// find pivot row, the row with biggest entry in current column
		tmp = 0;
		for (i = k; i < n; i++)
		{
			if (abs(A[i*n+k]) >= tmp)	// 'Avoid using other functions inside abs()?'
			{
				tmp = abs(A[i*n+k]);
				pivrow = i;
			}
		}

		// check for singular matrix
		if (A[pivrow*n+k] == 0.0f)
		{
			prln("Inversion failed due to singular matrix");
			return 0;
		}

		// Execute pivot (row swap) if needed
		if (pivrow != k)
		{
			// swap row k with pivrow
			for (j = 0; j < n; j++)
			{
				tmp = A[k*n+j];
				A[k*n+j] = A[pivrow*n+j];
				A[pivrow*n+j] = tmp;
			}
		}
		pivrows[k] = pivrow;	// record row swap (even if no swap happened)

		tmp = 1.0f/A[k*n+k];	// invert pivot element
		A[k*n+k] = 1.0f;		// This element of input matrix becomes result matrix

		// Perform row reduction (divide every element by pivot)
		for (j = 0; j < n; j++)
		{
			A[k*n+j] = A[k*n+j]*tmp;
		}

		// Now eliminate all other entries in this column
		for (i = 0; i < n; i++)
		{
			if (i != k)
			{
				tmp = A[i*n+k];
				A[i*n+k] = 0.0f;  // The other place where in matrix becomes result mat
				for (j = 0; j < n; j++)
				{
					A[i*n+j] = A[i*n+j] - A[k*n+j]*tmp;
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
				tmp = A[i*n+k];
				A[i*n+k] = A[i*n+pivrows[k]];
				A[i*n+pivrows[k]] = tmp;
			}
		}
	}
	return 1;
}


#define EPS 0.1e-15
#define Max(A,B) (((A)>(B))?(A):(B))
#define Min(A,B) (((A)<(B))?(A):(B))
#define Abs(A) (((A) > 0.)?(A): -(A))
//need dinamyc memory
void MatrixExponent(float *a, int n,float* ea)
 {
   int i, j, k, ii;
   float am, em, emi;

   float *w = new float[n*n];

   float **wm = new float*[n];
   for(i=0;i<n;i++)
	   wm[i] = new float[n];


     em = 0.;
     for( i = 0; i < n; i++ ){
       for( j = 0; j < n; j++ ){
	 ea[i*n+j] = 0.;
	 wm[i][j] = 0.;
	 am = Abs(a[i*n+j]);
	 em = Max(am,em);
       }
       ea[i*n+i] = 1.;
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
	     wm[i][j] += a[i*n+k] * w[k];
	 }
       }
       for( i = 0; i < n; i++ )
	 for( j = 0; j < n; j++ ){
	   wm[i][j] /= (float)ii;
	   ea[i*n+j] += wm[i][j];
	   am = Abs(wm[i][j]);
	   emi = Max(am,emi);
	 }
     }
   
   delete w;
   delete []wm;

 }
