#ifndef FOURIER_H
#define FOURIER_H



template<uint a> void transform_massive_construct(complex_t<float>  *w)
{
		complex_t<float> step;
		step.Re=cosx(2*PI/a);
		step.Im=sinx(2*PI/a);
		
		w[0]=1;
		for(int i=1;i<a;i++) w[i]=w[i-1]*step;
};

#include "queue/queue.h"
template <uint a>
class fourier_stream_transform{
	public:
	uint count;
	complex_t<float> w[a];
	complex_t<float> C[a];
	Cyclic_buffer<a,int> Cb;

	fourier_stream_transform<a>(){for(int i;i<a;i++)C[i]=0;transform_massive_construct<a>(w);count = 0;}
	
	void counting(int in){
	int& out = Cb.mas[Cb.head];
	complex_t<float> t;
	t=(in-out);
 	for (int i=0;i<a;i++)
	{C[i]=C[i]+t*w[(i*count)%a];}	
	Cb.push(in);
	count = ( count + 1 ) % a;	
	};
	
	void print(){
	//for (int i=0;i<a;i++) *stdprint << C[i] << '\t';
	//prln();
	for (int i=0;i<a;i++) *stdprint << abs_complex(C[i])/a << '\t';
	prln();
	};
};

#include "math/math.h"
#include "simple.h"
template<uint a> void transform_matrix_construct(Matrix<a,a,complex_t<float> > &M)
{
		complex_t<float> step;
		step.Re=cosx(2*PI/a);
		step.Im=sinx(2*PI/a);
		
		complex_t<float> w[a];
		w[0]=1;
		for(int i=1;i<a;i++) w[i]=w[i-1]*step;
				
		for (int i=0;i<a;i++)
		for (int j=0;j<a;j++)
		M[i][j] = w[(j*i)%a];
};



template<uint a> Vector<a,float> abs_complex(Vector<a, complex_t<float> > &V)
{
	Vector<a,float> VM;
	for (int i=0;i<a;i++)
	VM[i]=V[i].Re*V[i].Re+V[i].Im*V[i].Im;
	return VM;
};

#endif

