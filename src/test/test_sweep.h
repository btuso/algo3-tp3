#ifndef TEST_SWEEP_H_
#define TEST_SWEEP_H_

#include <utility>
#include <math.h>
#include "test_utils.h"
#include "../sweep.h"

#define X 0
#define Y 0
#define EPSILON 0.00001

#define WHATEVER_DEMAND 2
#define WHATEVER_CAPACITY 2
#define WHATEVER_WAREHOUSE Point(0, 0, 0)

typedef vector<Point> Cluster;
typedef vector<Cluster> Clusters;

void RunAllTestsForSweep();
void TestTransformPointsFromCartesianToPolar();

#endif
