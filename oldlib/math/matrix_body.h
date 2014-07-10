#ifndef MATRIX_BODY_H
#define MATRIX_BODY_H

//#include "allocator/allacator.h"
#include "simple.h"
class Index{public: int m;int n;Index(int _m, int _n):m(_m),n(_n){};};

template <typename Type>
class Matrix_Body {
public:
uint m;
uint n;
Type* M;	

Matrix_Body(uint _m, uint _n) : m(_m) , n(_n) {M = new Type[n*m];};
//~Matrix_Body() {delete };

Type& operator[](Index I){return *(M+I.m*n+I.n);};
Type operator[](Index I) const {return *(M+I.m*n+I.n);};
Type* operator[](int i){return (M+i*n);};
const Type* operator[](int i) const {return (M+i*n);};

void zero() {for(int i=0;i<m;i++)for(int j=0;j<n;j++)  M[i*n+j]=0;};
void identity() {for(int i=0;i<m;i++)for(int j=0;j<n;j++)   M[i*n+j]=((i==j) ? 1 : 0);}
void print() {for(int i=0;i<m;i++) {for(int j=0;j<n;j++)  *stdprint << M[i*n+j]<<'\t'; *stdprint << '\n';};};
};


#endif
