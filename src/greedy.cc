#include "greedy.h"

namespace greedy {
	vector<int> solveCvrp(Point& warehouse, vector<Point> &points, int capacity){
		pair<int, int> demands_ranges = GetDemandsRange(points);
		int min_demand_value = demands_ranges.first;
		int max_demand_value = demands_ranges.second;
		Buckets buckets = BucketSort(points, min_demand_value, max_demand_value);

		SortEachBucketByClosenessTo(buckets, warehouse);

		int vertex_covered = 0;
		vector<Truck> trucks;
		trucks.push_back(Truck(warehouse, capacity));

		while(vertex_covered < points.size()){
			Bucket* biggest_fitting_bucket = FindFittestBucket(buckets, trucks, warehouse, capacity);
			Point next_vertex = PopNextVertex(biggest_fitting_bucket, trucks);
			trucks.back().visit(next_vertex);

			vertex_covered ++;
		}

		/* resultado: */
		cout << "#trucks = " << trucks.size() << endl;
		
		for(Truck t : trucks){
			cout << "quedó con " << t.capacity_left << " de capacidad" << endl;
			aux::print_vector(t.routes);
			cout << "----";
		}

		return vector<int>();
	}

	pair<int, int> GetDemandsRange(vector<Point> &points){
		assert(not points.empty());

		int max = points[0].demand;
		int min = max;

		for(Point p : points){
			if(p.demand > max)
				max = p.demand;

			if(p.demand < min)
				min = p.demand;
		}

		return make_pair(min, max);
	}

	Buckets BucketSort(vector<Point> &points, int min_demand_value, int max_demand_value){
		int buckets_size = max_demand_value + 1; //- min_demand_value + 1;
		Buckets buckets(buckets_size);

		for(Point p : points){
			int index_in_bucket = p.demand; // - min_demand_value;
			buckets[index_in_bucket].push_back(p);
		}

		return buckets;
	}

	void SortEachBucketByClosenessTo(Buckets &buckets, Point &point){
		for(Bucket& bucket : buckets){
			std::sort(bucket.begin(), bucket.end(), DistanceToPointComparator(point));
		}
	}

	Bucket* FindFittestBucket(Buckets &buckets, vector<Truck> &trucks, Point warehouse, int capacity){
		int capacity_left = trucks.back().capacity_left;
		// entre este while y el que viene se hacen buckets.size() iteraciones
		// o sea como mucho este while va desde [0; capacity_left]
		int i = aux::min(capacity_left, buckets.size() - 1);
		while(i >= 0 and buckets[i].empty()){
			i--;
		}

		if(i < 0){ // no quedan mas clientes con demanda ≤ lo que me queda en el camion. tengo que crear uno
			trucks.back().visit(warehouse); // mando el camión lleno devuelta al warehouse
			trucks.push_back(Truck(warehouse, capacity)); // creo un nuevo camión

			// como dije antes, este while va desde (capacity_left; buckets.size() - 1] creo
			i = buckets.size() - 1;
			while(buckets[i].empty()){
				i--;
			}
		}

		return &(buckets[i]);
	}

	Point PopNextVertex(Bucket* bucket, vector<Truck> &trucks){
		int starting_index = aux::max(bucket->size() - K - 1, 0);

		// vector<Point> last_k_vertex = copy(bucket, bucket->begin() + starting_index, bucket->end()); // O(K)?
		Point last_vertex = trucks.back().routes.back();
		std::sort(bucket->begin() + starting_index, bucket->end(), DistanceToPointComparator(last_vertex));
		
		Point next_vertex = bucket->back();
		bucket->erase(bucket->end() - 1);
		return next_vertex;
	}
}

/*
anotaciones:
	• el bucket sort no hace index = (valor - min) para que sea mas facil de entender el tema de los indices
*/