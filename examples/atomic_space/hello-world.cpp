#include "shed/u_esh.h"
#include "math/math.h"
#include "platform.h"
#include "C_stream.h"
#include "debug/debug.h"
#include "allocator/allocator.h"
#include "math/matrix.h"
#include "math/complex.h"
//#include "math/const.h"
#include "utility.h"
#include "intcom/command_list.h"
//#include "inttrans/fourier.h"
#include "queue/queue.h"
//#include "filtration/linear_matrix.h"
Print* stdprint=&term;
Stream* tracert=&term;
Allocator_p * stdalloc;


#define dstdfor(i,n,j,m) for(int i=0;i<n;i++)for(int j=0;j<m;j++)
#define for_all_points_atomspace(pl,A,i,j) dstdfor(i,A.discr,j,A.discr) for_all_list(pl,A.GLOBAL_MAS[i][j]) 

extern "C" void __cxa_pure_virtual() { debug_print("__cxa_pure_virtual"); while (1); };
//#include "math/matrix.h"
#include "math/vector.h"

//#include "math/matrix_alg.h"
//#include "math/matrix_body.h"

#include "container/List.h"
#include "genoslib.h"
#include "simple.h"
#include "geometry2/geometry2.h"
//#include <complex>
//#include "math/complex.h"
#define WIDTH 200
#define DISCR 8
#define WD (WIDTH/DISCR)

Vector<2,float>* new_pointer(float x, float y)
{
Vector<2,float>* p;
p = new Vector<2,float>;
p->V[0]=x;p->V[1]=y;
return p;
};


template<uint Width, uint Discr>
class AtomisticSpace2
{public:
	uint width;
	uint discr;
	List GLOBAL_MAS[Discr][Discr];
	List L;
	AtomisticSpace2() : width(Width) , discr(Discr){};	
	void add(Vector<2,float> *VV) {
	ListNode* node = new ListNode ; node->Object=VV;
	L.add(node);
	};

	void reconsider(){
		List_it pl;
		dstdfor(i,discr,j,discr) GLOBAL_MAS[i][j].del_all();
		for_all_list(pl,L)
		{ 		
		ListNode* node = (ListNode*)(((ListNode*)(pl.get())));
		GLOBAL_MAS[((int)((*((Vector<2,float>*)(node->Object)))[0]/(Width/Discr)))%Discr]
		[((int)((*((Vector<2,float>*)(node->Object)))[1]/(Width/Discr)))%Discr].add_node(node);
		};
		}; 

	void print(){
		for(int i=0;i<Discr;i++)
	{
	for(int j=0;j<Discr;j++)
	*stdprint << GLOBAL_MAS[i][j].number() << ' ';
	prln();
	};

		};
};
TSH SH;
AtomisticSpace2<600,30> A;

typedef Vector<2,float> TV;
void task()
{
List_it pl;	
ListNode* ll;
for_all_list_obj(pl,A.L,ll,ListNode) {(*((TV*)(ll->Object)))[0]+=1;(*((TV*)(ll->Object)))[1]+=0.5;};
A.reconsider();
prln();
A.print();
prln(SH.maxdel);
}



char Rmas [10000];
Linear_allocator R;
#include "delay.h"
int main(){
R.engage(Rmas,10000);
stdalloc=&R;
registry_standart_utility();

term.begin();
List_it pl1,pl2;
ListNode* ll1,*ll2;
A.add(new_pointer(100,11));
A.add(new_pointer(100,50));
A.add(new_pointer(100,101));
A.add(new_pointer(100,152));
A.add(new_pointer(100,203));
A.add(new_pointer(100,250));
A.add(new_pointer(100,301));
//A.add(new_pointer(100,352));
//A.add(new_pointer(100,403));
//A.add(new_pointer(100,454));
//A.add(new_pointer(100,465));
//A.add(new_pointer(100,506));
A.add(new_pointer(100,557));
for_all_list_obj(pl1,A.L,ll1,ListNode) ((TV*)(ll1->Object))->print();

//for_all_list_obj(pl1,A.L,ll1,ListNode) {for_all_list_obj(pl2,A.L,ll2,ListNode)
//*stdprint << (abs((*((TV*)(ll1->Object)))-*((TV*)(ll2->Object)))) << '\t';
//prln();
//};

A.reconsider();

prln();
Point2 P;
P.x=2; P.y= 10;
P.print();


prln();
Geometry2 G;
G.new_point(10,56);
G.new_point(11,57);

prln();

G.print_point_list();

Point2* p;
List_it pl;
prln();
prln();
prln(distance(G.point(0),G.point(1)));
(G.point(0)-G.point(1)).print();
prln();

//	A.print();

//SH.newTimer(task,100,REPEAT);
//while(1) SH.start();
term.end();
}



