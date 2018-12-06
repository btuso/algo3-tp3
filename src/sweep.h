#ifndef SWEEP_H_
#define SWEEP_H_

#include "vector"
#include "point.h"
#include "truck.h"
#include "compare.h"
#include "auxiliares.h"
#include <utility>
#include <assert.h>
#include <algorithm>

using namespace std;

typedef vector<Point> Bucket;
typedef vector<Bucket> Buckets;
typedef vector<Point> Cluster;
typedef vector<Cluster> Clusters;

namespace sweep {

	vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity);

	void TransformPointsFromCartesianToPolar(Point &warehouse, vector<Point> &points);
}

#endif
