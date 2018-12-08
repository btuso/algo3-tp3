#include "annealing.h"

#include <vector>

#include "savings.h"
#include "neighborhood.h"
#include "auxiliares.h"

namespace annealing {

	std::vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity){
		vector<Truck> trucks = savings::solveCvrp(warehouse, points, capacity);
		Neighborhood neighborhood(warehouse, trucks);

		aux::PrintTrucks(points, warehouse, trucks);
		neighborhood.NextNeighbor();
		neighborhood.AcceptNeighbor();
debug("-----")

		aux::PrintTrucks(points, warehouse, trucks);
		neighborhood.NextNeighbor();
		neighborhood.AcceptNeighbor();
debug("-----")

		aux::PrintTrucks(points, warehouse, trucks);
debug("-----")
		neighborhood.NextNeighbor();
		neighborhood.AcceptNeighbor();
		return trucks;
	}

}
