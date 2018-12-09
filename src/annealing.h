#ifndef ANNEALING_H_
#define ANNEALING_H_

#include "vector"
#include "point.h"
#include "truck.h"
#include "params.h"

namespace annealing {

	std::vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity, Params &params);

}

#endif
