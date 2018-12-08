#ifndef ANNEALING_H_
#define ANNEALING_H_

#include <vector>
#include <tuple>

#include "point.h"
#include "truck.h"


namespace annealing {

	std::vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity);

	std::tuple<float, float> getTemperatureRange(const Point &warehouse, std::vector<Truck> &trucks);

	float calculateSolutionEnergy(const std::vector<Truck> &solution, const Point &warehouse);
}

#endif
