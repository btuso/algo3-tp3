#ifndef POINT_H_
#define POINT_H_

#include <math.h>
#include <iostream>
#include <string>

struct Point {
    float x;
    float y;
    int demand;


    Point(float x, float y, int demand): x(x), y(y), demand(demand){}

	float DistanceTo(Point p) const{
		return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
	}

	bool operator==(const Point& p) const {
		return x == p.x and y == p.y and demand == p.demand;
	}

	bool operator!=(const Point& p) const {
		return not( this->Point::operator==(p));
	}

	bool operator<(const Point& other) const {
		return demand < other.demand;
	}
	
	std::string to_string(){
		return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(demand);
	}
};

struct DistanceToPointComparator{
	DistanceToPointComparator(const Point& _p) : p(_p) {}

	bool operator()(const Point& lhs, const Point& rhs) const{
		// uso > y no < para que los mas cercanos a p queden al final del vector y poder hacerles pop()
		return p.DistanceTo(lhs) > p.DistanceTo(rhs);
	}

	Point p;
};

#endif
