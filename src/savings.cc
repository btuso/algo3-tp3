#include "savings.h"

#include "vector"

#include "auxiliares.h"
#include "truck.h"

using namespace	std;

namespace savings {

	vector<int> solveCvrp(Point& warehouse,	vector<Point> &points, int capacity){
		/* Armo matriz de distancias entre cada par de nodos */
		vector<vector<float> > distances(points.size(), vector<float>(points.size(), 0));
		/* Vector de distancia de todo nodo a deposito */
		vector<float> distance_to_warehouse(points.size(), 0);
		/* Vector de savings de tamano Nc2 */
		vector<Saving> savings;
		savings.reserve(points.size()*(points.size()-1)/2);

		/* Inicializo distancias y calculo savings */
		calcularDistancias(distances, distance_to_warehouse, points, warehouse);
		calcularSavings(distances, distance_to_warehouse, points, savings);

		/* Ordeno los savings de mayor a menor */
		sort(savings.begin(), savings.end());
		reverse(savings.begin(), savings.end());
		
		// cout << "Saving size " << savings.size();
		// for (int i = 0; i < savings.size(); i++) cout << savings[i].saving << endl;

		vector<Truck> trucks;

		return	vector<int>();
	}

	void calcularDistancias(vector<vector<float> > &distances, vector<float> &distance_to_warehouse, vector<Point> &points, Point& warehouse){
		for (unsigned int i = 0; i < points.size(); i++){
			for (unsigned int j = i+1; j < points.size(); j++){
				float point_distance = points[i].DistanceTo(points[j]);
				distances[i][j] = point_distance;
				distances[j][i] = point_distance;
			}
		}
		for (unsigned int i = 0; i < points.size(); i++)
			distance_to_warehouse[i] = points[i].DistanceTo(warehouse);
	}
	void calcularSavings(vector<vector<float> > &distances, vector<float> &distance_to_warehouse, vector<Point> &points, vector<Saving> &savings){
		for(unsigned int i = 0; i < points.size(); i++){
			for (unsigned int j = i+1; j < points.size(); j++){
				savings.push_back(Saving(distances, distance_to_warehouse, i, j));
			}
		}
	}

}
