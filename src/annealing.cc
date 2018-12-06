#include "annealing.h"

#include <vector>
#include <algorithm>
#include <tuple>

#include "auxiliares.h"
#include "savings.h"

//TODO delete this thing
#define ENUM_PRINT(x, y)  switch(x) {case shift_left: y = "shift_left";break;case shift_right: y = "shift_right";break;case exchange: y = "exchange";  break;} 

namespace annealing {

	std::vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity){
		vector<Truck> trucks = savings::solveCvrp(warehouse, points, capacity);
		
		return trucks;
	}

	std::vector<std::tuple<int, int>> GetRouteCombinations(std::vector<Truck> &trucks){
		std::vector<std::tuple<int, int>> routeCombinations;
		for(unsigned int i = 0; i < trucks.size() - 1; i++)
			for( unsigned int j = i + 1; j < trucks.size(); j++ )
				routeCombinations.push_back(std::make_tuple(i, j));

		std::random_shuffle(routeCombinations.begin(), routeCombinations.end());
		return routeCombinations;
	}

	std::vector<Interchange> GenerateInterchanges(Truck &Rp, Truck &Rq){
		std::vector<Interchange> interchanges;
		for(unsigned int left = 0; left < Rp.routes.size(); left++ )
			for(unsigned int right = 0; right < Rq.routes.size(); right++ ){
				interchanges.push_back(Interchange(left, right, shift_left));
				interchanges.push_back(Interchange(left, right, shift_right));
				interchanges.push_back(Interchange(left, right, exchange));
			}
		
		return interchanges;
	}
}
