#ifndef AUXILIARES_H_ 
#define AUXILIARES_H_

#include <iostream> 
#include <fstream> 
#include <vector>
#include "string"

#include "edge.h"
#include "point.h"

namespace aux {

	template <typename T>
	void print_vector(const std::vector<T> &S, std::ostream &output, std::string separator){
		for(unsigned int i = 0; i < S.size(); i++) {
			output << S[i];
			if (i != S.size() - 1) {
				output << separator;
			}
		}
	}

	template <typename T>
	void print_vector(const std::vector<T> &S){
		std::cout << "\n{ ";
		print_vector(S, std::cout, ", ");
		std::cout << " }";
	}

	void print_edges(const std::vector<Edge> &S);

}

#endif
