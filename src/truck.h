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
	vector<int> siguientes; 
	int cliente_final;
	bool es_valido;

	Truck(Point warehouse, int total_capacity): capacity_left(total_capacity){
		routes.push_back(warehouse);
	};
	Truck(int total_capacity, int cant_nodos, int i, int j, int demanda){
		predecesores = vector<int>(cant_nodos, ninguno);
		siguientes = vector<int>(cant_nodos, ninguno);
		predecesores[j] = i;
		siguientes[i] = j;
		cliente_final = j;
		capacity_left = total_capacity - demanda;
		es_valido = true;
	};

	void visit(int existente, int nuevo, int demanda){
		if (predecesores[existente] == ninguno){
			predecesores[existente] = nuevo;
			siguientes[nuevo] = existente;
		}else{
			predecesores[nuevo] = existente;
			siguientes[existente] = nuevo;
			cliente_final = nuevo;
		}
		capacity_left -= demanda;
	}

	void visit(Point vertex){
		routes.push_back(vertex);
		capacity_left -= vertex.demand;
	}

	bool noEsInterno(int punto){
		return predecesores[punto] == ninguno or cliente_final == punto;
	}

	bool hayEspacio(int demanda){
		return capacity_left >= demanda;
	}

	void mergearRuta(int punto_A, int punto_B, Truck &truck_B, int nueva_capacidad, vector<int> &en_que_camion){
		capacity_left = nueva_capacidad;
		vector<int> &predecesores_B = truck_B.predecesores;
		vector<int> &siguientes_B = truck_B.siguientes;
		en_que_camion[punto_B] = en_que_camion[punto_A];

		if (predecesores[punto_A] == ninguno){
			predecesores[punto_A] = punto_B;
			siguientes[punto_B] = punto_A;

			if (predecesores_B[punto_B] == ninguno){
				int i = punto_B;
				while (siguientes_B[i] != ninguno){
					predecesores[i] = siguientes_B[i];
					siguientes[predecesores[i]] = i;
					i = predecesores[i];
					en_que_camion[i] = en_que_camion[punto_A];
				}
			}else{
				copiarNodos(punto_A, predecesores_B, siguientes_B, en_que_camion);
			}
		}else{
			siguientes[punto_A] = punto_B; 
			predecesores[punto_B] = punto_A; 

			if (siguientes_B[punto_B] == ninguno){
				int i = punto_B;
				while (predecesores_B[i] != ninguno){
					siguientes[i] = predecesores_B[i];
					predecesores[siguientes[i]] = i;
					i = siguientes[i];
					en_que_camion[i] = en_que_camion[punto_A];
				}
				cliente_final = i;
			}else{
				cliente_final = truck_B.cliente_final;
				copiarNodos(punto_A, predecesores_B, siguientes_B, en_que_camion);
			}
			
		}
		truck_B.es_valido = false;
	}

	void copiarNodos(int punto_A, vector<int> &predecesores_B, vector<int> &siguientes_B, vector<int> &en_que_camion){
		for (unsigned int i = 0; i < predecesores_B.size(); i++){
			if (predecesores_B[i] != ninguno){
				predecesores[i] = predecesores_B[i];
				en_que_camion[i] = en_que_camion[punto_A];
			}
			if (siguientes_B[i] != ninguno){
				siguientes[i] = siguientes_B[i];
				en_que_camion[i] = en_que_camion[punto_A];
			}
		}
	}
};

#endif