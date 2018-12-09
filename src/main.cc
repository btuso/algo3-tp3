#include <iostream> 
#include <fstream> 

#include "vector"
#include "tuple"
#include "map"
#include "string"

#include "lib/tiempo.h"

#include "auxiliares.h"
#include "savings.h"
#include "greedy.h"
#include "sweep.h"
#include "annealing.h"

using namespace std; 

typedef std::vector<Truck> (* CvrpHeuristic) (Point& warehouse, std::vector<Point> &points, int capacity);

void MeasureAlgorithm(string name, CvrpHeuristic function, string input, ofstream &output);
tuple<Point, vector<Point>, int> ReadDataset(); 

vector<string> getFiles();


vector<string> getFiles() {
	vector<string> files;
	files.push_back("A-n32-k5.vrp");
	files.push_back("A-n33-k5.vrp");
	files.push_back("A-n33-k6.vrp");
	files.push_back("A-n34-k5.vrp");
	files.push_back("A-n36-k5.vrp");
	files.push_back("A-n37-k5.vrp");
	files.push_back("A-n37-k6.vrp");
	files.push_back("A-n38-k5.vrp");
	files.push_back("A-n39-k5.vrp");
	files.push_back("A-n39-k6.vrp");
	files.push_back("A-n44-k6.vrp");
	files.push_back("A-n45-k6.vrp");
	files.push_back("A-n45-k7.vrp");
	files.push_back("A-n46-k7.vrp");
	files.push_back("A-n48-k7.vrp");
	files.push_back("A-n53-k7.vrp");
	files.push_back("A-n54-k7.vrp");
	files.push_back("A-n55-k9.vrp");
	files.push_back("A-n60-k9.vrp");
	files.push_back("A-n61-k9.vrp");
	files.push_back("A-n62-k8.vrp");
	files.push_back("A-n63-k9.vrp");
	files.push_back("A-n63-k10.vrp");
	files.push_back("A-n64-k9.vrp");
	files.push_back("A-n65-k9.vrp");
	files.push_back("A-n69-k9.vrp");
	files.push_back("A-n80-k10.vrp");
	files.push_back("B-n31-k5.vrp");
	files.push_back("B-n34-k5.vrp");
	files.push_back("B-n35-k5.vrp");
	files.push_back("B-n38-k6.vrp");
	files.push_back("B-n39-k5.vrp");
	files.push_back("B-n41-k6.vrp");
	files.push_back("B-n43-k6.vrp");
	files.push_back("B-n44-k7.vrp");
	files.push_back("B-n45-k5.vrp");
	files.push_back("B-n45-k6.vrp");
	files.push_back("B-n50-k7.vrp");
	files.push_back("B-n50-k8.vrp");
	files.push_back("B-n51-k7.vrp");
	files.push_back("B-n52-k7.vrp");
	files.push_back("B-n56-k7.vrp");
	files.push_back("B-n57-k7.vrp");
	files.push_back("B-n57-k9.vrp");
	files.push_back("B-n63-k10.vrp");
	files.push_back("B-n64-k9.vrp");
	files.push_back("B-n66-k9.vrp");
	files.push_back("B-n67-k10.vrp");
	files.push_back("B-n68-k9.vrp");
	files.push_back("B-n78-k10.vrp");
	files.push_back("E-n22-k4.vrp");
	files.push_back("E-n23-k3.vrp");
	files.push_back("E-n30-k3.vrp");
	files.push_back("E-n33-k4.vrp");
	files.push_back("E-n51-k5.vrp");
	files.push_back("E-n76-k7.vrp");
	files.push_back("E-n76-k8.vrp");
	files.push_back("E-n76-k10.vrp");
	files.push_back("E-n76-k14.vrp");
	files.push_back("E-n101-k8.vrp");
	files.push_back("E-n101-k14.vrp");
	files.push_back("F-n45-k4.vrp");
	files.push_back("F-n72-k4.vrp");
	files.push_back("F-n135-k7.vrp");
	files.push_back("M-n101-k10.vrp");
	files.push_back("M-n121-k7.vrp");
	files.push_back("M-n151-k12.vrp");
	files.push_back("M-n200-k16.vrp");
	files.push_back("M-n200-k17.vrp");
	files.push_back("P-n16-k8.vrp");
	files.push_back("P-n19-k2.vrp");
	files.push_back("P-n20-k2.vrp");
	files.push_back("P-n21-k2.vrp");
	files.push_back("P-n22-k2.vrp");
	files.push_back("P-n22-k8.vrp");
	files.push_back("P-n23-k8.vrp");
	files.push_back("P-n40-k5.vrp");
	files.push_back("P-n45-k5.vrp");
	files.push_back("P-n50-k7.vrp");
	files.push_back("P-n50-k8.vrp");
	files.push_back("P-n50-k10.vrp");
	files.push_back("P-n51-k10.vrp");
	files.push_back("P-n55-k7.vrp");
	files.push_back("P-n55-k8.vrp");
	files.push_back("P-n55-k10.vrp");
	files.push_back("P-n55-k15.vrp");
	files.push_back("P-n60-k10.vrp");
	files.push_back("P-n60-k15.vrp");
	files.push_back("P-n65-k10.vrp");
	files.push_back("P-n70-k10.vrp");
	files.push_back("P-n76-k4.vrp");
	files.push_back("P-n76-k5.vrp");
	files.push_back("P-n101-k4.vrp");
	return files;
}


int main(int argc, char** argv) { 
	map<string, CvrpHeuristic> algorithms;
	algorithms["savings"] = savings::solveCvrp;
	algorithms["greedy"] = greedy::solveCvrp;
	algorithms["sweep"] = sweep::solveCvrp;
	// algorithms["annealing"] = annealing::solveCvrp;

	if ( argc == 1 ) {
		cout << "Se necesita pasar el algoritmo a usar como argumento.\nOpciones: savings, greedy, sweep, otra, annealing\n"; 
		return 1;
	// } else if ( argc == 2 ) {
	// 	cout << "Se necesita especificar el archivo de entrada, que debe estar en la carpeta 'resources'.\n";
	// 	return 1;
	}

	string algorithm = argv[1];
	// string input = argv[2];

	if( algorithm == "experimentos" ){
		vector<string> inputs = getFiles();
		for(auto it = algorithms.begin(); it != algorithms.end(); ++it) {
			ofstream output("out/" + it->first);
			cout << "Running for: " << it->first << "...\n";
			for (unsigned int r = 0; r < inputs.size(); r++) {
				MeasureAlgorithm(it->first, it->second, inputs[r], output);
			}
			cout << " done\n";
			output.close();	
		}
		
	} else if (algorithm == "dataset"){ // Format dataset for plotting
		string input = argv[2];
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
			for(unsigned int i = 0; i < points.size() - 1; i++)
				 output << points[i].to_string() << "\n";
			output << points.back().to_string();
		}
		output.close();	
		dataset.close();
	} else {
		string input = argv[2];
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
			aux::PrintTrucks(points, warehouse, solution);
		}
		dataset.close(); 
	}
	return 0; 
} 

void MeasureAlgorithm(string name, CvrpHeuristic function, string inputFile, ofstream &output){
	cout << "Start input " << inputFile << "\n";
	ifstream dataset("resources/pg/" + inputFile);	
	if( dataset.is_open() ){
		cin.rdbuf(dataset.rdbuf());
		tuple<Point, vector<Point>, int> input = ReadDataset();
		Point warehouse = get<0>(input);
		vector<Point> points = get<1>(input);
		int capacity = get<2>(input);
		for (unsigned int pasada = 1; pasada < 11; pasada++) {
			cout << "\tStart: " << pasada << "\n";
			unsigned long start, end;
			MEDIR_TIEMPO_START(start);
			vector<Truck> sol = function(warehouse, points, capacity);
			MEDIR_TIEMPO_STOP(end);
			// algorithm, inputFile, qtyPoints, capacityTruck, time
			output << name << "," << inputFile << "," << points.size() << "," << capacity << "," << pasada << "," << (end-start) << "\n"; // Agregar lo que falta para los experimentos
			cout << "\t\t" << name << "," << inputFile << "," << points.size() << "," << capacity << "," << (end-start) << "\n"; // Agregar lo que falta para los experimentos
			cout << "\tFinish: " << pasada << "\n";
		}
		dataset.close(); 
	}
	
	cout << "Finish input " << inputFile << "\n";
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
	
	float x, y;
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
	for(int i = 0; i < dimension - 1; ++i){
		int demand;
		cin >> ignore; // Id
		cin >> demand;
		points[i].demand = demand;
	}
	tuple<Point, vector<Point>, int> res = std::make_tuple(warehouse, points, capacity);
	return res;
}
