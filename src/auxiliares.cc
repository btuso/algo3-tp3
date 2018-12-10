#include "auxiliares.h"

#include <stdexcept>
#include <iostream>
#include <cmath>
#include <assert.h>

namespace aux {
	std::ostream& operator<<(std::ostream &strm, const Point &p) {
		return strm << "(x: " << p.x << ", y: " << p.y << ", demand: " << p.demand << ")";
	}

	float mod(float a, float mod){
		while(a > mod or a < 0){
			if(a < 0)
				a += mod;
			else
				a -= mod;
		}

		return a;
	}

	int min(int a, int b){
		if(a < b)
			return a;

		return b;
	}

	int max(int a, int b){
		if(a > b)
			return a;

		return b;
	}

	void print_vector(const std::vector<float> &S){
		std::cout << '\n' << "{ ";
		for(unsigned int i = 0; i < S.size(); i++) {
			std::cout << S[i];
			if (i != S.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << " }";
	}

	void print_edges(const std::vector<Edge> &S){
		std::cout << '\n' << "{ ";
		for(unsigned int i = 0; i < S.size(); i++) {
			std::cout << "(" << S[i].u << ", " << S[i].v << ", " << S[i].distance << ")";
			if (i != S.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << " }";
	}

	void print_buckets(const std::vector<std::vector<Point>>& buckets){
		for(unsigned int i = 0; i < buckets.size(); i++){
			std::cout << "[" << i << "] = ";

			for(unsigned int k = 0; k < buckets[i].size(); k++){
				std::cout << buckets[i][k];

				if(k != buckets[i].size() - 1){
					std::cout << ", ";
				}
			}

			std::cout << std::endl;
		}
	}

	int GetPointId(vector<Point> &points, Point &point){
		unsigned int point_id = 0;
		while(point_id < points.size()) {
			if( points[point_id] == point )
				return point_id + 1; // Ids start from 1, and the warehouse id is ignored
			point_id++;
		}
		throw std::logic_error("GetPointId: No matching point");
	}

	void PrintTrucks(vector<Point> &points, Point &warehouse, vector<Truck> &trucks){
		unsigned int truck_qty = trucks.size();
		cout << truck_qty << "\n";

		for(unsigned int i = 0; i < truck_qty; i++){
			if (trucks[i].es_valido){
				vector<int> point_ids;
				for( Point& point : trucks[i].routes )
					if( point != warehouse )
						point_ids.push_back(GetPointId(points, point));
				aux::print_vector(point_ids, cout, " ");
				cout << endl;
			}
		}
	}

	void removeDeposits(vector<Truck> &trucks){
		for(Truck &t : trucks){
			print_vector(t.routes);
			if(not t.empty()){
				cout << "	popeando" << endl;
				t.routes.pop_back();
				cout << "	eraseando" << endl;
				t.routes.erase(t.routes.begin());
			}
		}
	}
}
