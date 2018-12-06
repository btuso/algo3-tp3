#ifndef TEST_GREEDY_H_
#define TEST_GREEDY_H_

#include <utility>
#include "test_utils.h"
#include "../greedy.h"

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
