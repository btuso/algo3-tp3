#ifndef POINT_H_
#define POINT_H_

#include <math.h>

struct Point {
    float x;
    float y;
    int demand;


    Point(float x, float y, int demand): x(x), y(y), demand(demand){}

	float DistanceTo(Point p){
		return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
	}

	bool operator==(const Point& p) const {
		return x == p.x and y == p.y and demand == p.demand;
	}

	bool operator<(const Point& other) const {
		return demand < other.demand;
	}
};

#endif
