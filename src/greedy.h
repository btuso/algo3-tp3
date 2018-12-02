#ifndef GREEDY_H_
#define GREEDY_H_

#include "vector"
#include "point.h"
#include "auxiliares.h"
#include <utility>
#include <assert.h>

using namespace std;

typedef vector<vector<Point>> Buckets;

namespace greedy {

	vector<int> solveCvrp(vector<Point> &points, int capacity);

	pair<int, int> GetDemandsRange(vector<Point> &points);

	Buckets BucketSort(vector<Point> &points, int min_demand_value, int max_demand_value);
}

#endif
