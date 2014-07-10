#ifndef MATRIX_BODY_H
#define MATRIX_BODY_H

class Index{public: int m;int n;Index(int _m, int _n):m(_m),n(_n){};};

template <uint n, uint m, typename Type>
class Matrix_Body {
public:
Type M[m*n];	
Type& operator[](Index I){return *(M+I.m*n+I.n);};
Type operator[](Index I) const {return *(M+I.m*n+I.n);};
Type* operator[](int i){return (M+i*n);};
const Type* operator[](int i) const {return (M+i*n);};
};


#endif
