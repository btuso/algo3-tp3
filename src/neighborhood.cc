#include "neighborhood.h"

#include <stdexcept>
#include <algorithm>
#include <tuple>
#include <iterator>

#include "auxiliares.h"

// ===== Public  ====
Neighborhood::Neighborhood(const std::vector<Truck> &trucks) : trucks(trucks) {
	truckCombinations = GetRouteCombinations(trucks);
	current_trucks = truckCombinations.begin();
	interchanges = GenerateInterchanges(trucks[get<0>(*current_trucks)], trucks[get<1>(*current_trucks)]);
	// This will be advanced automatically when next neighbor is called
	current_interchange = std::prev(interchanges.begin(), 1); 
}

float Neighborhood::NextNeighbor(){

	if( not NeighborsLeft() ) 
		throw std::logic_error("No more neighbors to explore");
	
	if(  std::next(current_interchange, 1) == interchanges.end() ){
		std::advance(current_trucks, 1);
		interchanges = GenerateInterchanges(trucks[get<0>(*current_trucks)], trucks[get<1>(*current_trucks)]);
		current_interchange = interchanges.begin();
	} else {
		std::advance(current_interchange, 1);
	}

	return 1.0; //TODO calcular costo
}

bool Neighborhood::NeighborsLeft(){
	return not (std::next(current_trucks, 1) == truckCombinations.end() and std::next(current_interchange, 1) == interchanges.end());
}

// ===== Private ====

std::vector<std::tuple<int, int>> Neighborhood::GetRouteCombinations(const std::vector<Truck> &trucks){
	std::vector<std::tuple<int, int>> routeCombinations;
	for(unsigned int i = 0; i < trucks.size() - 1; i++)
		for( unsigned int j = i + 1; j < trucks.size(); j++ )
			routeCombinations.push_back(std::make_tuple(i, j));

	std::random_shuffle(routeCombinations.begin(), routeCombinations.end());
	return routeCombinations;
}

std::vector<Interchange> Neighborhood::GenerateInterchanges(const Truck &Rp, const Truck &Rq){
	std::vector<Interchange> interchanges;
	for(unsigned int left = 0; left < Rp.routes.size(); left++ )
		for(unsigned int right = 0; right < Rq.routes.size(); right++ ){
			interchanges.push_back(Interchange(left, right, shift_left));
			interchanges.push_back(Interchange(left, right, shift_right));
			interchanges.push_back(Interchange(left, right, exchange));
		}

	return interchanges;
}

