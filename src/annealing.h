#ifndef ANNEALING_H_
#define ANNEALING_H_

#include "vector"
#include "point.h"
#include "truck.h"

namespace annealing {

	std::vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity);

}

#endif
