#include <iostream> 
#include <fstream> 
#include <stdexcept>

#include "vector"
#include "tuple"
#include "map"
#include "string"

#include "lib/tiempo.h"

#include "auxiliares.h"
#include "savings.h"
#include "greedy.h"

using namespace std; 

typedef std::vector<Truck> (* CvrpHeuristic) (Point& warehouse, std::vector<Point> &points, int capacity);

void MeasureAlgorithm(string name, CvrpHeuristic function, string input, ofstream &output);
tuple<Point, vector<Point>, int> ReadDataset(); 
void PrintTrucks(vector<Point> &points, Point& warehouse, vector<Truck> &trucks);


int main(int argc, char** argv) { 
	map<string, CvrpHeuristic> algorithms;
	algorithms["savings"] = savings::solveCvrp;
	algorithms["greedy"] = greedy::solveCvrp;

	if ( argc == 1 ) {
		cout << "Se necesita pasar el algoritmo a usar como argumento.\nOpciones: savings, greedy, sweep, otra, annealing\n"; 
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
	} else if (algorithm == "dataset"){ // Format dataset for plotting
		ofstream output("out/" + input);
		
		ifstream dataset("resources/" +input);	
		if( dataset.is_open() ){
			cin.rdbuf(dataset.rdbuf());
			auto input = ReadDataset();
			Point warehouse = get<0>(input);
			vector<Point> points = get<1>(input);
			int capacity = get<2>(input);
			output << capacity << "\n";
			output << warehouse.to_string() << "\n";
debug("asdasd")
			for(unsigned int i = 0; i < points.size() - 1; i++)
				 output << points[i].to_string() << "\n";
			output << points.back().to_string();
		}
		output.close();	
		dataset.close();
	} else {
		if ( algorithms.count(algorithm) == 0 ) {
			cout << "Algoritmo invalido.\nOpciones: savings, greedy, sweep, otra, annealing\n"; 
			return 1;
		}

		ifstream dataset(input);	
		if( dataset.is_open() ){
			cin.rdbuf(dataset.rdbuf());
			auto heuristic = algorithms[algorithm];
			auto input = ReadDataset();
			Point warehouse = get<0>(input);
			vector<Point> points = get<1>(input);
			auto solution = heuristic(warehouse, points, get<2>(input));
			PrintTrucks(points, warehouse, solution);
		}
		dataset.close(); 
	}
	return 0; 
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

void MeasureAlgorithm(string name, CvrpHeuristic function, string input, ofstream &output){
	ifstream dataset(input);	
	if( dataset.is_open() ){
		cin.rdbuf(dataset.rdbuf());
		auto input = ReadDataset();
		Point warehouse = get<0>(input);
		vector<Point> points = get<1>(input);
		int capacity = get<2>(input);
		unsigned long start, end;
		MEDIR_TIEMPO_START(start);
		vector<Truck> sol = function(warehouse, points, capacity);
		MEDIR_TIEMPO_STOP(end);
		output << name << "," << points.size() << "," << capacity  << "," << (end-start) << "\n"; // Agregar lo que falta para los experimentos
	}
	dataset.close(); 
}

tuple<Point, vector<Point>, int> ReadDataset() {
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

	int x, y;
	cin >> ignore; // Id
	cin >> x;
	cin >> y;
	Point warehouse(x, y, 0);

	vector<Point> points;
	for(int i = 1; i < dimension; ++i){
		cin >> ignore; // Id
		cin >> x;
		cin >> y;
		points.push_back(Point(x, y, 0));
	}
	cin.ignore(); 			// Newline
	getline( cin, ignore );		// Demand Section
	getline( cin, ignore );		// warehouse
	for(int i = 0; i < dimension; ++i){
		int demand;
		cin >> ignore; // Id
		cin >> demand;
		points[i].demand = demand;
	}
	return std::make_tuple(warehouse, points, capacity);
}
