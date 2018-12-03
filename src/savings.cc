#include "savings.h"

#include "vector"

#include "auxiliares.h"
#include "truck.h"

using namespace	std;
#define ninguno -1
namespace savings {

	vector<int> solveCvrp(Point& warehouse,	vector<Point> &points, int capacity){
		/* Armo matriz de distancias entre cada par de nodos */
		int n = points.size();
		int distancia_total = 0;
		vector<vector<float> > distancias(n, vector<float>(n, 0));
		/* Vector de distancia de todo nodo a deposito, vector con info de en que camion va cada nodo */
		vector<float> distancia_a_deposito(n, 0);
		vector<float> en_que_camion(n, ninguno);
		/* Vector de savings de tamano Nc2 */
		vector<Saving> savings;
		savings.reserve(n*(n-1)/2);

		/* Inicializo distancias y calculo savings */
		calcularDistancias(distancias, distancia_a_deposito, points, warehouse, distancia_total);
		calcularSavings(distancias, distancia_a_deposito, points, savings);

		/* Ordeno los savings de menor a mayor */
		sort(savings.begin(), savings.end());
		// cout << "Saving size " << savings.size();
		// for (int i = 0; i < savings.size(); i++) cout << savings[i].saving << endl;
		vector<Truck> trucks;
		int nodos_agregados = 0;
		int saving_total = 0;
		/* Recorro savings de mayor a menor*/
		for (int i = savings.size()-1; i >= 0 && nodos_agregados < n; i--){
			Saving &s = savings[i];
			int camion_A = en_que_camion[s.point_A];
			int camion_B = en_que_camion[s.point_A];
			int punto_A = s.point_A;
			int punto_B = s.point_B;
			

			if (camion_A == ninguno){
				if (camion_B == ninguno){
					/* Nuevo camion que vaya a ambos nodos */
					int demanda = points[punto_A].demand + points[punto_B].demand;
					if (capacity >= demanda){
						trucks.push_back(Truck(capacity, n, punto_A, punto_B, demanda));
						en_que_camion[punto_A] = trucks.size()-1;
						en_que_camion[punto_B] = trucks.size()-1;
						nodos_agregados+=2;
						saving_total += s.saving; 
					}
				}else{
					/* Va al camion de B*/
					int demanda = points[punto_A].demand;
					if (trucks[camion_B].capacity_left >= demanda){
						trucks[camion_B].agregarCliente(punto_B, punto_A, demanda);
						en_que_camion[punto_A] = camion_B;
						nodos_agregados++;
						saving_total += s.saving; 
					}
				}
			}else{
				if (camion_B == ninguno){
					/* Va al camion de A*/
					int demanda = points[punto_B].demand;
					if (trucks[camion_A].capacity_left >= demanda){
						trucks[camion_A].agregarCliente(punto_A, punto_B, demanda);
						en_que_camion[punto_B] = camion_A;
						nodos_agregados++;
						saving_total += s.saving; 
					}
				}
			}
		}
		cout << "Capacidad total " << capacity << endl;
		imprimirCamiones(trucks, points, warehouse);
		cout << "Distancia recorrida " << distancia_total-saving_total << endl;
		return	vector<int>();
	}

	void calcularDistancias(vector<vector<float> > &distances, vector<float> &distance_to_warehouse, vector<Point> &points, Point& warehouse, int &distancia_total){
		for (unsigned int i = 0; i < points.size(); i++){
			for (unsigned int j = i+1; j < points.size(); j++){
				float point_distance = points[i].DistanceTo(points[j]);
				distances[i][j] = point_distance;
				distances[j][i] = point_distance;
			}
		}
		for (unsigned int i = 0; i < points.size(); i++){
			distance_to_warehouse[i] = points[i].DistanceTo(warehouse);
			distancia_total += distance_to_warehouse[i];
		}
		distancia_total*=2;
	}
	void calcularSavings(vector<vector<float> > &distances, vector<float> &distance_to_warehouse, vector<Point> &points, vector<Saving> &savings){
		for(unsigned int i = 0; i < points.size(); i++){
			for (unsigned int j = i+1; j < points.size(); j++){
				savings.push_back(Saving(distances, distance_to_warehouse, i, j));
			}
		}
	}
	void imprimirCamiones(vector<Truck> &trucks, vector<Point> &points, Point& warehouse){
		for(Truck t : trucks){
			cout << "Quedó con " << t.capacity_left << " de capacidad" << endl;
			vector<Point> res;
			res.push_back(warehouse);
			int cliente = t.cliente_final;
			res.push_back(points[cliente]);
			while(t.predecesores[cliente] != ninguno){
				cliente = t.predecesores[cliente];
				res.push_back(points[cliente]);
			}
			res.push_back(warehouse);
			aux::print_vector(res);
			cout << endl << "----" << endl;
		}
	}

}
