#ifndef SAVINGS_H_
#define SAVINGS_H_

#include "vector"

#include "point.h"
#include "saving_struct.h"

namespace savings {

	std::vector<int> solveCvrp(Point& warehouse, std::vector<Point> &points, int capacity);
	void calcularDistancias(std::vector<std::vector<float> > &distances, std::vector<float> &distance_to_warehouse, std::vector<Point> &points, Point& warehouse);
	void calcularSavings(std::vector<std::vector<float> > &distances, std::vector<float> &distance_to_warehouse, std::vector<Point> &points, std::vector<Saving> &savings);


};


#endif
