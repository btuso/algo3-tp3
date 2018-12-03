#ifndef TRUCK_H_
#define TRUCK_H_

#include "vector"
#include "point.h"
#define ninguno -1
using namespace std;

struct Truck {
	vector<Point> routes;
	int capacity_left;
	vector<int> predecesores; 
	int cliente_final;

	Truck(Point warehouse, int total_capacity): capacity_left(total_capacity){
		routes.push_back(warehouse);
	};
	Truck(int total_capacity, int cant_nodos, int i, int j, int demanda){
		predecesores = vector<int>(cant_nodos, ninguno);
		predecesores[j] = i;
		predecesores[i] = ninguno;
		cliente_final = j;
		capacity_left = total_capacity - demanda;
	};

	void visit(int existente, int nuevo, int demanda){
		if (predecesores[existente] == ninguno){
			predecesores[existente] = nuevo;
			predecesores[nuevo] = ninguno;
		}else{
			predecesores[nuevo] = existente;
			cliente_final = nuevo;
		}
		capacity_left -= demanda;
	}

	void visit(Point vertex){
		routes.push_back(vertex);
		capacity_left -= vertex.demand;
	}

	bool esPrimero(int punto){
		return predecesores[punto] == ninguno or cliente_final == punto;
	}

	bool hayEspacio(int demanda){
		return capacity_left >= demanda;
	}
};

#endif