/*
 *  MatrixMath.h Library for Matrix Math
 *
 *  Created by Charlie Matlack on 12/18/10.
 *  Modified from code by RobH45345 on Arduino Forums, taken from unknown source.
 */

#ifndef MatrixMath_h
#define MatrixMath_h

	void MatrixPrint(float* A, int m, int n, char* label);
	void MatrixCopy(float* A, int n, int m, float* B);
	void MatrixZero(float* A, int n, int m);
	void MatrixMultiply(float* A, float* B, int m, int p, int n, float* C);
	void MatrixAdd(float* A, float* B, int m, int n, float* C);
	void MatrixSubtract(float* A, float* B, int m, int n, float* C);
	void MatrixTranspose(float* A, int m, int n, float* C);
	void MatrixScale(float* A, int m, int n, float k);
	int MatrixInvert(float* A, int n);
	void MatrixExponent(float *a, int n,float* ea);


#endif
