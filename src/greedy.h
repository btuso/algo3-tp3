#ifndef GREEDY_H_
#define GREEDY_H_

#define K 4

#include "vector"
#include "point.h"
#include "truck.h"
#include "auxiliares.h"
#include <utility>
#include <assert.h>

using namespace std;

typedef vector<Point> Bucket;
typedef vector<Bucket> Buckets;

namespace greedy {

	vector<int> solveCvrp(Point& warehouse, vector<Point> &points, int capacity);

	pair<int, int> GetDemandsRange(vector<Point> &points);

	Buckets BucketSort(vector<Point> &points, int min_demand_value, int max_demand_value);

	void SortEachBucketByClosenessTo(Buckets& buckets, Point& point);

	Bucket* FindFittestBucket(Buckets &buckets, vector<Truck> &trucks, Point warehouse, int capacity);

	Point PopNextVertex(Bucket* bucket, vector<Truck> &trucks);
}

#endif