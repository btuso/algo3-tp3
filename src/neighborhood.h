#ifndef NEIGHBORHOOD_H_
#define NEIGHBORHOOD_H_

#include <vector>
#include <tuple>

#include "interchange.h"
#include "truck.h"

class Neighborhood {

	private:
		const std::vector<Truck> trucks;
		std::vector<std::tuple<int, int>> truckCombinations;
		std::vector<Interchange> interchanges;

		std::vector<std::tuple<int, int>>::iterator current_trucks;
		std::vector<Interchange>::iterator current_interchange;
		

		std::vector<std::tuple<int, int>> GetRouteCombinations(const std::vector<Truck> &trucks);
		std::vector<Interchange> GenerateInterchanges(const Truck &Rp, const Truck &Rq);

	public:
		Neighborhood(const std::vector<Truck> &trucks);
		
		// Returns the cost of the next neighbor
		float NextNeighbor();

		bool NeighborsLeft();
};

#endif
