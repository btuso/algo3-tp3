#include "sweep.h"

namespace sweep {
	vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int capacity){
		TransformPointsFromCartesianToPolar(warehouse, points);
		sort(points.begin(), points.end(), SweepComparator());
	}

	void TransformPointsFromCartesianToPolar(Point &warehouse, vector<Point> &points){
		int relative_x, relative_y;

		for(Point &p : points){
			relative_x = p.x - warehouse.x;
			relative_y = p.y - warehouse.y;

			p.angle = atan2(relative_y, relative_x);
			p.radius = sqrt(pow(relative_x, 2) + pow(relative_y, 2));
		}
	}
}