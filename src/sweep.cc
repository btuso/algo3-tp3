#include "sweep.h"

namespace sweep {
	vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int max_stock){
		vector<Point> points_copy(points);
		
		TransformPointsFromCartesianToPolar(warehouse, points_copy);
		sort(points_copy.begin(), points_copy.end(), AngleComparator());
		float sweep_starting_angle = FindSweepStartingAngle(points_copy);
		sort(points_copy.begin(), points_copy.end(), AngleComparator(sweep_starting_angle));
		Clusters clusters = BuildClusters(points_copy, max_stock);
		return BuildRoutesFromClusters(clusters, warehouse, max_stock);
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

	float FindSweepStartingAngle(vector<Point> &points){
		Point prev = points[0];
		float greatest_angle_gap = 0;
		float ray_angle = 0;

		for(unsigned int i = 1; i <= points.size(); i++){
			unsigned int index = i % points.size();
			Point current = points[index];

			float gap = 0;
			if(prev.angle < current.angle)
				gap = fabs(prev.angle - current.angle);
			else
				gap = (2 - prev.angle + current.angle);

			if(gap > greatest_angle_gap){
				greatest_angle_gap = gap;
				ray_angle = aux::mod((prev.angle + gap / 2), 2);
			}

			prev = current;
		}

		return ray_angle;
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