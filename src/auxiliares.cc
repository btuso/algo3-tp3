#include "auxiliares.h"

#include <iostream>
#include <cmath>
#include <assert.h> 

namespace aux { 
	std::ostream& operator<<(std::ostream &strm, const Point &p) {
		return strm << "(x: " << p.x << ", y: " << p.y << ", demand: " << p.demand << ")";
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
}