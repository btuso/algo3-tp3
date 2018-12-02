#include "test_greedy.h"

void RunAllTestsForGreedy(){
	TestGetDemandsRange();
	TestBucketSort();
}

void TestGetDemandsRange(){
	TEST

	given("A list of points with their respective demands")
		vector<Point> points = {Point(X, Y, 1),
								Point(X, Y, 2),
								Point(X, Y, 3),
								Point(X, Y, 4),
								Point(X, Y, 5)};

	when("GetDemandsRange is called")
		pair<int, int> range = greedy::GetDemandsRange(points);

	then("1 should be minimum and 5 should be maximum")
		assert(range.first == 1);
		assert(range.second == 5);

	END_TEST
}

void TestBucketSort(){
	TEST

	given("A list of points with their respective demands")
		vector<Point> points = {Point(X, Y, 2),
								Point(X, Y, 5),
								Point(X, Y, 1),
								Point(X, Y, 2),
								Point(X, Y, 1)};
		int MIN_DEMAND = 1;
		int MAX_DEMAND = 5;

	when("BucketSort is called")
		vector<vector<Point>> buckets = greedy::BucketSort(points, MIN_DEMAND, MAX_DEMAND);

	then("Should be correctly sorted")
		vector<vector<Point>> expected_buckets(5);
		expected_buckets[0].push_back(Point(X, Y, 1));
		expected_buckets[0].push_back(Point(X, Y, 1));
		expected_buckets[1].push_back(Point(X, Y, 2));
		expected_buckets[1].push_back(Point(X, Y, 2));
		expected_buckets[4].push_back(Point(X, Y, 5));

		assert(buckets.size() == 5);
		assert(buckets == expected_buckets);

	END_TEST
}