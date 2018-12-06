#ifndef COMPARE_H
#define COMPARE_H

#include <utility>

struct DistanceToPointComparator{
	DistanceToPointComparator(const Point& _p) : p(_p) {}

	bool operator()(const Point& lhs, const Point& rhs) const{
		// uso > y no < para que los mas cercanos a p queden al final del vector y poder hacerles pop()
		return p.DistanceTo(lhs) > p.DistanceTo(rhs);
	}

	Point p;
};

struct SweepComparator{
	bool operator()(const Point& lhs, const Point& rhs) const{
		return lhs.angle > rhs.angle;
	}
};
#endif