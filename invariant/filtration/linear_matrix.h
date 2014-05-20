#ifndef LINEAR_MATRIX_H
#define LINEAR_MATRIX_H

#include "math/matrix.h"
template<uint n>
class linear_matrix_filter{
	public:
	Vector<n,float> Bz;
	Vector<n,float> Cz;
	Matrix<n,n,float> Az;
	
	Vector<n,float> x;
	
	
	
	void ABexp(Matrix<n,n,float> &A,Vector<n,float> &B,float h){
		 Matrix<n,n,float> E;
		 E.identity();
		 Az=exp(A*h); 
		 Bz=inv(A)*(exp(A*h)-E)*B;
		 };	
};




#endif
