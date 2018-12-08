#include "annealing.h"

#include <vector>

#include "greedy.h"
#include "neighborhood.h"
#include "auxiliares.h"

namespace annealing {

	std::vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity){
		int iterations = 0;
		std::vector<Truck> current_solution, best_solution;
		float current_energy, best_energy;

		current_solution = greedy::solveCvrp(warehouse, points, capacity);
		current_energy = calculateSolutionEnergy(current_solution, warehouse);
		best_solution = current_solution; // Copy
		best_energy = current_energy; 

		float starting_temp, final_temp, current_temp, best_temp;
		float alpha, gamma;

		auto temperature_range = getTemperatureRange(warehouse, current_solution);
		final_temp = get<0>(temperature_range);
		starting_temp = get<1>(temperature_range);
		current_temp = starting_temp;
		best_temp = current_temp;

//		aux::PrintTrucks(points, warehouse, trucks);

		Neighborhood neighborhood(warehouse, current_solution); // Neighborhood holds a reference to solution in order to modify it.

		while (current_temp > final_temp) {
			if (neighborhood.HasNeighborsLeft()) {
				float cost = neighborhood.NextNeighbor();
				iterations++;
				if (cost < 0 /* or prob */) {
					neighborhood.AcceptNeighbor();
					current_energy += cost;
					std::cout << "---" << endl;
					std::cout << iterations << endl;
					std::cout << current_energy << endl;
					aux::PrintTrucks(points, warehouse, current_solution);
				}
				if (current_energy < best_energy) {
					best_energy = current_energy;
					best_solution = current_solution; // Copy
					best_temp = current_temp;
				}
//				coolDown(); // TODO
			} else {
//				heatUp();  // TODO
				break;
			}
		}

		return best_solution;
	}

	std::tuple<float, float> getTemperatureRange(const Point &warehouse, std::vector<Truck> &solution){
		Neighborhood neighborhood(warehouse, solution);
		float best, worst;
		best = neighborhood.NextNeighbor();
		worst = best;
		while (neighborhood.HasNeighborsLeft()) {
			float cost = neighborhood.NextNeighbor();
			if (cost < best)
				best = cost;
			else if (cost > worst)
				worst = cost;
		}
		return std::make_tuple(best, worst);
	}

	float calculateSolutionEnergy(const std::vector<Truck> &solution, const Point &warehouse){
		float energy = 0;
		for (const Truck &truck : solution)
			energy += truck.distanceTravelled(warehouse);
		return energy;
	}
}
