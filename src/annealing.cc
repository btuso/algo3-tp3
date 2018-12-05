#include "annealing.h"

#include "greedy.h"

namespace annealing {

	vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity){
		vector<Truck> trucks = greedy::solveCvrp(warehouse, points, capacity);

		return trucks;
	}
}
