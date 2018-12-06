#include "sweep.h"

namespace sweep {
	#define PI 3.14159265358979323846
	vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int max_stock){
		vector<Point> points_copy(points);
		
		TransformPointsFromCartesianToPolar(warehouse, points_copy);
		sort(points_copy.begin(), points_copy.end(), AngleComparator());
		Clusters clusters = BuildClusters(points_copy, max_stock);
		return BuildRoutesFromClusters(clusters, warehouse, max_stock);
	}

	void TransformPointsFromCartesianToPolar(Point &warehouse, vector<Point> &points){
		int relative_x, relative_y;

		for(Point &p : points){
			relative_x = p.x - warehouse.x;
			relative_y = p.y - warehouse.y;

			p.radius = sqrt(pow(relative_x, 2) + pow(relative_y, 2));
			if (relative_x > 0) p.angle = atan2(relative_y, p.radius + relative_x);
			if (relative_x <= 0 and relative_y!=0) p.angle = atan2(p.radius - relative_x, relative_y);
			if (relative_x < 0 and relative_y==0) p.angle = PI;

			if (p.angle < 0) p.angle += 2*PI;

		}
	}

	Clusters BuildClusters(vector<Point> &points, int max_stock){
		Clusters clusters;
		clusters.push_back(Cluster());
		int current_stock = max_stock;
		
		for(Point &p : points){
			if(current_stock < p.demand){
				current_stock = max_stock;
				clusters.push_back(Cluster());
			}

			current_stock -= p.demand;
			clusters.back().push_back(p);
		}

		return clusters;
	}

	vector<Truck> BuildRoutesFromClusters(Clusters &clusters, Point &warehouse, int max_stock){
		vector<Truck> trucks = { Truck(warehouse, max_stock) };

		for(Cluster &cluster : clusters){
			while(not cluster.empty()){
				Truck &last_truck = trucks.back();
				Point &last_visited = last_truck.LastVisited();

				last_truck.visit(PopClosestVertexTo(cluster, last_visited));
			}

			trucks.back().visit(warehouse); // chequear
			trucks.push_back(Truck(warehouse, max_stock));
		}

		return trucks;
	}

	Point PopClosestVertexTo(Cluster &cluster, Point &point){
		sort(cluster.begin(), cluster.end(), DistanceToPointComparator(point));
		Point closest = cluster.back();
		cluster.erase(cluster.end() - 1);

		return closest;
	}
}