
#include "container/List.h"

class Point2 {
public:
float x, y;
Point2() : x(0) , y(0) {};
Point2(float _x, float _y) : x(_x) , y(_y) {};
void print() {*stdprint << x << ':' << y;};

Point2 operator- (Point2 a) {return Point2(x-a.x,y-a.y);}; 	
};

float abs(Point2 a); 	

class Geometry2
{
	public:
List Point;	
Point2* new_point(float _x, float _y);	
	
Point2& point(int i){return *((Point2*)(Point[i]));};
	
void print_point_list();	
};

#define G_for_all_point(G,pl,p) for_all_list_obj(pl,(G).Point,p,Point2)


float distance(Point2 a, Point2 b);
