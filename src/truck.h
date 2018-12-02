#ifndef TRUCK_H_
#define TRUCK_H_

#include "vector"
#include "point.h"

using namespace std;

struct Truck {
	vector<Point> routes;
	int capacity_left;

	Truck(Point warehouse, int total_capacity): capacity_left(total_capacity){
		routes.push_back(warehouse);
	};

	void visit(Point vertex){
		routes.push_back(vertex);
		capacity_left -= vertex.demand;
	}
};

#endif