#include "auxiliares.h"

#include <iostream>
#include <cmath>
#include <assert.h> 

namespace aux { 

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
}
