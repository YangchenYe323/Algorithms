#include<iostream>
#include<vector>
#include<climits>
using namespace std;

/*
This function calculates the shortest path from source vertex s to all other vetexes
using dynamic programming. The adjacency list and weight matrix is assumed to be given
*/
void dijkstraDP(const vector<vector<int> > & adj_list, 
					const vector<vector<int> > & weight_matrix, int s){

	//make the reverse adjacency list, in which
	//in_adj_list[v] contains all the vertex that reaches v
	//count all the number of edges along the same loop
	int num_vertex = adj_list.size();
	int num_edge = 0;
	vector<vector<int> > in_adj_list(num_vertex);
	//poor spatial locality, might be better way of doing the same work
	for (int i = 0; i < num_vertex; ++i){
		for (int adj: adj_list[i]){
			++num_edge;
			in_adj_list[adj].push_back(i);
		}
	}

	//dynamic programming, d[v][k] stores the shortest path
	//from s to v using at most k edges. the final shortest
	//path will be stored at d[v][num_edge]
	vector<vector<int> > dp_map(num_vertex, vector<int>(num_edge+1));

	//initialize the first row
	for (int v = 0; v < num_vertex; ++v){

		//if the vertex is not reachable directly from s, d[v][1] is not possible
		if (weight_matrix[s][v] < 0)
			dp_map[v][1] = 9999;
		else
			dp_map[v][1] = weight_matrix[s][v];

	}

	//initialize trivial case, d[s][0] - d[s][k] are all 0
	for (int e = 1; e <= num_edge; ++e) 
		dp_map[s][e] = 0;

	//main dp loop
	//first fill in all vertex's distance by one edge,
	//then use it to fill in all vertexes' distance by
	//two edge, and so on
	for (int e = 2; e <= num_edge; ++e){
		for (int v = 0; v < num_vertex; ++v){

			if (v == s) continue;

			//the smaller one of using exactly k edges and using at most k-1 edges
			dp_map[v][e] = dp_map[v][e-1];
			//update the distance
			for (int adj: in_adj_list[v]){
				int thisPath = dp_map[adj][e-1] + weight_matrix[adj][v];
				if (thisPath < dp_map[v][e]) dp_map[v][e] = thisPath;
			}

			//the smaller one of using exactly k edges and using at most k-1 edges

		}

	}

	cout << num_edge << endl;

	for (int v = 0; v < num_vertex; ++v){
		for (int e = 1; e <= num_edge; ++e){
			cout << dp_map[v][e] << " ";
		}
		cout << endl;
	}

	for (int v = 0; v < num_vertex; ++v)
		cout << "Index: " << v << ", distance: " << dp_map[v][num_edge] << endl;





}


int main(){

	vector<vector<int> > adj_list{
		{1, 3},
		{3, 4},
		{0, 5},
		{2, 4, 5, 6},
		{6},
		{},
		{5}
	};

	vector<vector<int> > weight_matrix(7, vector<int>(7, -1));

	weight_matrix[0][1] = 2;
	weight_matrix[0][3] = 1;
	weight_matrix[1][3] = 3;
	weight_matrix[1][4] = 10;
	weight_matrix[2][0] = 4;
	weight_matrix[2][5] = 5;
	weight_matrix[3][2] = 2;
	weight_matrix[3][4] = 2;
	weight_matrix[3][5] = 8;
	weight_matrix[3][6] = 4;
	weight_matrix[4][6] = 6;
	weight_matrix[6][5] = 1;

	dijkstraDP(adj_list, weight_matrix, 0);

}