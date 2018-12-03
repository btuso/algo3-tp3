#ifndef SAVINGS_H_
#define SAVINGS_H_

#include "vector"

#include "point.h"
#include "saving_struct.h"
#include "truck.h"

namespace savings {

	std::vector<int> solveCvrp(Point& warehouse, std::vector<Point> &points, int capacity);
	void calcularDistancias(std::vector<std::vector<float> > &distances, std::vector<float> &distance_to_warehouse, std::vector<Point> &points, Point& warehouse, float &distancia_total);
	void calcularSavings(std::vector<std::vector<float> > &distances, std::vector<float> &distance_to_warehouse, std::vector<Point> &points, std::vector<Saving> &savings);
	void imprimirCamiones(vector<Truck> &trucks, vector<Point> &points, Point& warehouse, vector<vector<float> > &distancias, vector<float> &distance_to_warehouse);
	bool puedoAgregarlo(Truck &t, int punto, int demanda);

};


#endif
