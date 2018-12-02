#include "greedy.h"

namespace greedy {

	vector<int> solveCvrp(vector<Point> &points, int capacity){
		pair<int, int> demands_ranges = GetDemandsRange(points);
		int min_demand_value = demands_ranges.first;
		int max_demand_value = demands_ranges.second;
		Buckets buckets = BucketSort(points, min_demand_value, max_demand_value);
		
		cout << "Entre en greedy eeeee\n";
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
		int buckets_size = max_demand_value - min_demand_value + 1;
		vector<vector<Point>> buckets(buckets_size);

		for(Point p : points){
			int index_in_bucket = p.demand - min_demand_value;
			buckets[index_in_bucket].push_back(p);
		}

		return buckets;
	}
}