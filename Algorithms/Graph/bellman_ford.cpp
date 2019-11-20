#include<iostream>
#include<vector>
#define INFINITY 9999
#define N_INFINITY -9999
using namespace std;

/*
use bellman ford algorithm to find the single-source shortest path,
set d[v] to negative infinity if there is a negative cycle on the path
to v
*/
void bellman_ford(vector<vector<int> > & adj_list, vector<vector<int> > &weight_matrix, int s){

	int n = adj_list.size();
	int E = 0;
	//make the reverse adjacency list
	vector<vector<int> > in_adj_list(n, vector<int>{});
	//poor spatial locality, might be better way of doing the same work
	for (int i = 0; i < n; ++i){
		for (int adj: adj_list[i]){
			++E;
			in_adj_list[adj].push_back(i);
		}
	}

	//dp[k][v] stores the shortest path from s to v using at most k edges
	//|E| more row is used to detect all the negative cycles
	//the final answer is stored in dp[n+E-1][0:v]
	vector<vector<int> > dp(n+E, vector<int>(n, INFINITY));
	//run the algorithm n-1 times to get the shortest path if no negative cycle
	//initialize
	for (int v = 0; v < n; ++v){
		dp[0][v] = weight_matrix[s][v] == -1 ? INFINITY: weight_matrix[s][v];
	}
	dp[0][0] = 0;
	for (int k = 1; k < n-1; ++k){
		for (int v = 0; v < n; ++v){
			dp[k][v] = dp[k-1][v];
			for (int adj: in_adj_list[v]){
				int thisPath = dp[k-1][adj] + weight_matrix[adj][v];
				if (thisPath < dp[k][v]) dp[k][v] = thisPath;
			}
		}
	}

	//run the algorithm |E| more times to find all the negative cycles
	for (int k = n-1; k < n+E; ++k){
		for (int v = 0; v < n; ++v){
			dp[k][v] = dp[k-1][v];
			for (int adj: in_adj_list[v]){
				int thisPath = dp[k-1][adj] + weight_matrix[adj][v];
				//there is a negative cycle
				if (thisPath < dp[k][v])
					dp[k][v] = N_INFINITY;
			}
		}
	}

	//print out outcome
	for (int v = 0; v < n; ++v){
		cout << "vertex: " << v << ", shortest path: " << dp[n+E-1][v] << endl;
	}
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

	bellman_ford(adj_list, weight_matrix, 0);

	vector<vector<int> > test_list{
		{1},
		{2},
		{0}
	};

	vector<vector<int> > test_matrix(3, vector<int>(3, -1));
	
	test_matrix[0][1] = 1;
	test_matrix[1][2] = 2;
	test_matrix[2][0] = -100;

	bellman_ford(test_list, test_matrix, 0);

}