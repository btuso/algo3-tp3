#include <iostream> 
#include <fstream> 

#include "vector"
#include "tuple"
#include "map"
#include "string"

#include "lib/tiempo.h"

#include "auxiliares.h"
#include "savings.h"

#define DEBUG(x) std::cout << "Debug: " << x << "\n";

using namespace std; 

typedef std::vector<int> (* CvrpHeuristic) (std::vector<Point> &points, int capacity);

void MeasureAlgorithm(string name, CvrpHeuristic function, string input, ofstream &output);
tuple<vector<Point>, int> ReadDataset(); 


int main(int argc, char** argv) { 
	map<string, CvrpHeuristic> algorithms;
	algorithms["savings"] = savings::solveCvrp;

	if ( argc == 1 ) {
		cout << "Se necesita pasar el algoritmo a usar como argumento.\nOpciones: savings, golosa, sweep, otra, annealing\n"; 
		return 1;
	} else if ( argc == 2 ) {
		cout << "Se necesita especificar el archivo de entrada, que debe estar en la carpeta 'resources'.\n";
		return 1;
	}

	string algorithm = argv[1];
	string input = argv[2];

	if( algorithm == "experimentos" ){
		ofstream output("out/" + input);
		for(auto it = algorithms.begin(); it != algorithms.end(); ++it) {
			cout << "Running for: " << it->first << "...";
			MeasureAlgorithm(it->first, it->second, input, output);
			cout << " done\n";
		}
		output.close();	
	} else {
		if ( algorithms.count(algorithm) == 0 ) {
			cout << "Algoritmo invalido.\nOpciones: savings, golosa, sweep, otra, annealing\n"; 
			return 1;
		}

		ifstream dataset("resources/" + input);	
		if( dataset.is_open() ){
			cin.rdbuf(dataset.rdbuf());
			auto heuristic = algorithms[algorithm];
			auto input = ReadDataset();
			auto solution = heuristic(get<0>(input), get<1>(input));
			aux::print_vector(solution);
		}
		dataset.close(); 
	}
	return 0; 
} 

void MeasureAlgorithm(string name, CvrpHeuristic function, string input, ofstream &output){
	ifstream dataset("resources/" + input);	
	if( dataset.is_open() ){
		cin.rdbuf(dataset.rdbuf());
		while( dataset.peek() != EOF && !dataset.eof() ) {
			auto input = ReadDataset();
			vector<Point> points = get<0>(input);
			int capacity = get<1>(input);
			unsigned long start, end;
			MEDIR_TIEMPO_START(start);
			vector<int> sol = function(points, capacity);
			MEDIR_TIEMPO_STOP(end);
			output << name << "," << points.size() << "," << capacity  << "," << (end-start) << "\n"; // Agregar lo que falta para los experimentos
		}
	}
	dataset.close(); 
}

tuple<vector<Point>, int> ReadDataset() {
	string ignore;
	int dimension, capacity;
	getline( cin, ignore ); 	// Name
	getline( cin, ignore ); 	// Commment
	getline( cin, ignore ); 	// Type
	cin >> ignore >> ignore;  	// Dimension :
	cin >> dimension;		// read dimension
	cin.ignore(); 			// Newline
	getline( cin, ignore ); 	// Edge Weight Type
	cin >> ignore >> ignore;  	// Capacity :
	cin >> capacity;		// read capacity
	cin.ignore(); 			// Newline
	getline( cin, ignore );		// Node Coord Section
	cin.ignore(); 			// Newline

	vector<Point> points;
	for(int i = 0; i < dimension; ++i){
		int x, y;
		cin >> ignore; // Id
		cin >> x;
		cin >> y;
		points.push_back(Point(x, y, 0));
	}
	cin.ignore(); 			// Newline
	getline( cin, ignore );		// Demand Section
	for(int i = 0; i < dimension; ++i){
		int demand;
		cin >> ignore; // Id
		cin >> demand;
		points[i].demand = demand;
	}
	return std::make_tuple(points, capacity);
}
