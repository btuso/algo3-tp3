#include "kmeans.h"

namespace kmeans {
	#define ninguno -1
	unsigned int n = 0;
	unsigned int k = 0;
	vector<Truck> solveCvrp(Point& warehouse, vector<Point> &points, int max_stock, Params&){
		vector<Point> points_copy(points);
		n = points_copy.size();
		k = calculateK(points_copy, max_stock);
		vector<int> in_cluster(n, ninguno);
		vector<Point> k_clusters;
		//sort(points_copy.begin(), points_copy.end());

		initializeClusters(points_copy, k_clusters, in_cluster, max_stock);
		bool sigueCambiando = true;
		while (sigueCambiando){
			sigueCambiando = false;
			for(unsigned int i = 0; i < n; i++){
				int last_cluster = in_cluster[i]; 
				int cluster = findNearestCentroid(k_clusters, points_copy[i], last_cluster);
				if (last_cluster != cluster){
					sigueCambiando = true;
					in_cluster[i] = cluster;
					if (last_cluster != ninguno) k_clusters[last_cluster].demand += points_copy[i].demand;
					k_clusters[cluster].demand -= points_copy[i].demand;
				}			
			}
			for (unsigned int i = 0; i < k; i++){
				int cluster_count;
				Point new_centroid = calculateCentroid(in_cluster, k_clusters[i].demand, i, points_copy, cluster_count);
				if (new_centroid != k_clusters[i]){
					k_clusters[i] = new_centroid;
				}
			}
		}

		Clusters clusters = BuildClusters(points_copy, in_cluster, k_clusters.size());
		/* Borro los que quedaron vacios */
		for(unsigned int i = clusters.size() - 1; i > 0; i--)
			if(clusters[i].size() == 0)
				clusters.erase(clusters.begin() + i);
		
		vector<Truck> trucks = sweep::BuildRoutesFromClusters(clusters, warehouse, max_stock);
		trucks.pop_back();

		return trucks;
	}

	int calculateK(vector<Point> &points, int max_stock){
		double new_k = 0;
		for (unsigned int i = 0; i < n; i++)
			new_k += points[i].demand;
		return ceil(new_k/max_stock);
	}

	void initializeClusters(vector<Point> &points, vector<Point> &k_clusters, vector<int> &in_cluster, int max_stock){
		for (unsigned int i = n-1; i > n-k-1; i--){
			k_clusters.push_back(Point(points[i].x, points[i].y, max_stock - points[i].demand));
			in_cluster[i] = k_clusters.size()-1;
		}
	}

	int findNearestCentroid(vector<Point> &k_clusters, Point &point, int cluster){
		vector<Point> clusters_copy(k_clusters);
		sort(clusters_copy.begin(), clusters_copy.end(), DistanceToPoint(point));
		unsigned int i;
		bool termine = false;
		for (i = 0; i < clusters_copy.size() and !termine; i++){
			if (aux::GetPointId(k_clusters, clusters_copy[i])-1 != cluster){
				int capacity_left = clusters_copy[i].demand;
				if (capacity_left >= point.demand) termine = true;
			}else{
				termine = true;
			}
		}
		if (!termine){
			k_clusters.push_back(point);
			k++;
			return k-1;
		} 

		return aux::GetPointId(k_clusters, clusters_copy[i-1])-1;
	}

	Point calculateCentroid(vector<int> &in_cluster, int demand, int cluster, vector<Point> &points_copy, int &cant){
		float mean_x = 0;
		float mean_y = 0;
		cant = 0;
		for (unsigned int i = 0; i < n; i++){
			if (in_cluster[i] == cluster){
				mean_x += points_copy[i].x;
				mean_y += points_copy[i].y;
				cant++;
			}
		}
		if (cant == 0) return Point(0, 0, -1);
		mean_x /= cant;
		mean_y /= cant;

		return Point(floor(mean_x), floor(mean_y), demand);
	}

	Clusters BuildClusters(vector<Point> &points_copy, vector<int> &in_cluster, unsigned int k){
		Clusters clusters(k, Cluster());
		for(unsigned int i = 0; i < in_cluster.size(); i++){
			clusters[in_cluster[i]].push_back(points_copy[i]);
		}

		return clusters;
	}
	
}