#ifndef COMPLEX_H
#define COMPLEX_H




template <typename T> class complex
{
public:
T Re;
T Im;	
complex() : Re(0),Im(0) {};
complex(T a, T b) : Re(a),Im(b){};

complex<T> operator*(int b){return complex<T>(Re*b,Im*b);};
void operator=(complex<T> a){Re=a.Re;Im=a.Im;};
void operator=(int a){Re=a;Im=0;};

void print() {pr (Re);
	if (Im >= 0) pr('+');
	pr(Im); pr("i");};

complex<T> operator*(complex<T> b){return complex<T>(Re*b.Re - Im*b.Im , Re*b.Im + Im*b.Re);};
complex<T> operator+(complex<T> b){return complex<T>(Re+b.Re , Im+b.Im);};
friend complex<T> operator*(int a,complex<T> b){return complex<T>(b.Re*a,b.Im*a);};
};

template<typename T> T abs(complex<T> a)
{return(sqrt
	(a.Re*a.Re+a.Im*a.Im));};

template<typename T>
Print& operator<<(Print& p,complex<T> t){p << t.Re;
	if (t.Im >= 0) pr('+');
	p << t.Im << "i\t";};



#endif
