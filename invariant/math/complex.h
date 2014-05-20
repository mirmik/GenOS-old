#ifndef COMPLEX_H
#define COMPLEX_H




template <typename T> class complex_t
{
public:
T Re;
T Im;	
complex_t(){Re=0;Im=0;};
complex_t(T a, T b){Re=a;Im=b;};

complex_t<T> operator*(int b){return complex_t<T>(Re*b,Im*b);};
void operator=(complex_t<T> a){Re=a.Re;Im=a.Im;};
void operator=(int a){Re=a;Im=0;};

friend Print& operator<<(Print& p,complex_t<T> &t){p << t.Re;
	if (t.Im >= 0) pr('+');
	p << t.Im << "i\t";};
	

complex_t<T> operator*(complex_t<T> b){return complex_t<T>(Re*b.Re - Im*b.Im , Re*b.Im + Im*b.Re);};
complex_t<T> operator+(complex_t<T> b){return complex_t<T>(Re+b.Re , Im+b.Im);};

friend complex_t<T> operator*(int a,complex_t<T> b){return complex_t<T>(b.Re*a,b.Im*a);};

};

template<typename T> T abs_complex(complex_t<T> a)
{return(sqrt
	(a.Re*a.Re+a.Im*a.Im));};


#endif
