#include "test_sweep.h"

void RunAllTestsForSweep(){
	TestTransformPointsFromCartesianToPolar();
}

void TestTransformPointsFromCartesianToPolar(){
	TEST

	given("A list of cartesian points and some warehouse")
		vector<Point> points = {Point(5, 5, WHATEVER_DEMAND), Point(2, 4, WHATEVER_DEMAND)};
		Point warehouse(4, 4, WHATEVER_DEMAND);

	when("Calling TransformPointsFromCartesianToPolar")
		sweep::TransformPointsFromCartesianToPolar(warehouse, points);

	then("The points should have their polar attributes loaded")
		float first_point_expected_angle = M_PI / 4;
		float first_point_expected_radius = sqrt(2);

		float second_point_expected_angle = M_PI;
		float second_point_expected_radius = 2;

		assert(fabs(first_point_expected_angle - points[0].angle) < EPSILON);
		assert(fabs(first_point_expected_radius - points[0].radius) < EPSILON);
		assert(fabs(second_point_expected_angle - points[1].angle) < EPSILON);
		assert(fabs(second_point_expected_radius - points[1].radius) < EPSILON);

	END_TEST
}