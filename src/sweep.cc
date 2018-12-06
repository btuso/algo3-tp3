#include "sweep.h"

namespace sweep {
	vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int max_stock){
		TransformPointsFromCartesianToPolar(warehouse, points);
		sort(points.begin(), points.end(), AngleComparator());
		Clusters clusters = BuildClusters(points, max_stock);
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

	Clusters BuildClusters(vector<Point> &points, int max_stock){
		Clusters clusters;
		clusters.push_back(Cluster());
		int current_stock = max_stock;
		
		for(Point &p : points){
			if(current_stock >= p.demand){
				current_stock -= p.demand;
			}else{
				current_stock = max_stock;
				clusters.push_back(Cluster());
			}

			clusters.back().push_back(p);
		}

		return clusters;
	}
}