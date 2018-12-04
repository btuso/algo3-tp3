#ifndef TEST_GREEDY_H_
#define TEST_GREEDY_H_

#include <utility>
#include "test_utils.h"
#include "../greedy.h"

#define X 0
#define Y 0

#define WHATEVER_DEMAND 2
#define WHATEVER_CAPACITY 2
#define WHATEVER_WAREHOUSE Point(0, 0, 0)

typedef vector<Point> Bucket;
typedef vector<Bucket> Buckets;

void RunAllTestsForGreedy();

void TestGetDemandsRange();
void TestBucketSort();
void TestSortEachBucketByClosenessTo();
void TestFindFittestBucket1();
void TestFindFittestBucket2();
void TestPopNextVertex1();
void TestPopNextVertex2();

#endif
