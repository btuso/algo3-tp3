#ifndef ANNEALING_H_
#define ANNEALING_H_

#include "vector"
#include "point.h"
#include "truck.h"
#include "auxiliares.h"

namespace annealing {

	enum Operation { shift_left, shift_right, exchange }; // (0,1) (1,0) (1,1) respectively
	struct Interchange {
		unsigned int left;
		unsigned int right;
		Operation operation;

		Interchange(unsigned int left, unsigned int right, Operation operation): left(left), right(right), operation(operation){}
	};

	vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity);
	std::vector<std::tuple<int, int>> GetRouteCombinations(std::vector<Truck> &trucks);
	std::vector<Interchange> GenerateInterchanges(Truck &Rp, Truck &Rq);

}

#endif
