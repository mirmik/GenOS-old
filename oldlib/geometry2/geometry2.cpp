
#include "geometry2/geometry2.h"




Point2* Geometry2::new_point (float _x, float _y)
{
	Point2* p = new Point2(_x,_y);
	Point.add(p);
};

#include "simple.h"
void Geometry2::print_point_list()
{
List_it pl;
Point2* p;
for_all_list_obj(pl,Point,p,Point2) {p->print(); prln();};
};

#include "math/math.h"
float abs(Point2 a) {return (sqrt(a.x*a.x+a.y*a.y));}; 	

float distance(Point2 a, Point2 b){
	return (abs(a-b));};
