#include "annealing.h"

#include <vector>

#include "savings.h"
#include "neighborhood.h"

//TODO delete this thing
#define ENUM_PRINT(x, y)  switch(x) {case shift_left: y = "shift_left";break;case shift_right: y = "shift_right";break;case exchange: y = "exchange";  break;} 

namespace annealing {

	std::vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity){
		vector<Truck> trucks = savings::solveCvrp(warehouse, points, capacity);
		Neighborhood neighborhood(trucks);
		while(neighborhood.NeighborsLeft()) {
			neighborhood.NextNeighbor();
		}
		std::cout<< "out of neighbors" << endl;
		return trucks;
	}

}
