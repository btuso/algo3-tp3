#ifndef SAVINGS_H_
#define SAVINGS_H_

#include "vector"

#include "point.h"

namespace savings {

	std::vector<int> solveCvrp(std::vector<Point> &points, int capacity);

}

#endif
