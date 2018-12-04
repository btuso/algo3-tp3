#ifndef SAVINGS_H_
#define SAVINGS_H_

#include "vector"

#include "point.h"
#include "saving_struct.h"
#include "truck.h"

namespace savings {

	vector<int> solveCvrp(Point& warehouse, vector<Point> &points, int capacity);
	void calcularDistancias(vector<vector<float> > &distances, vector<float> &distance_to_warehouse, vector<Point> &points, Point& warehouse, float &distancia_total);
	void calcularSavings(vector<vector<float> > &distances, vector<float> &distance_to_warehouse, vector<Point> &points, vector<Saving> &savings);
	void imprimirCamiones(vector<Truck> &trucks, vector<Point> &points, Point& warehouse, vector<vector<float> > &distancias, vector<float> &distance_to_warehouse);
	bool puedoAgregarlo(Truck &t, int punto, int demanda);
	void camionNuevo(vector<Truck> &trucks, vector<int> &en_que_camion, int punto_A, int punto_B, int demanda);
	void visitarCliente(Truck &t, vector<int> &en_que_camion, int existente, int nuevo, int demanda);

};


#endif
