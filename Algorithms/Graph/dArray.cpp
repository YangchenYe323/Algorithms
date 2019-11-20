#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;

void dijstraUsingArray(const vector<vector<int> > & adj_list, const vector<vector<int> > & weight_matrix, int s, int K){

	vector<int> distance(adj_list.size(), INT_MAX);

	vector<int> marked(adj_list.size(), 0);

	vector<queue<int> > array_queue(K+1);

	array_queue[0].push(s);

	distance[s] = 0;

	for (int i = 0; i < K * adj_list.size(); ++i){

		int cursor = i % (K+1);

		while (!array_queue[cursor].empty()){
			int v = array_queue[cursor].front();
			array_queue[cursor].pop();

			if (marked[v] == 1) continue;
			
			marked[v] = 1;

			int zeroPoint = distance[v];

			for (int adj: adj_list[v]){
				if (distance[adj] > distance[v] + weight_matrix[v][adj]){
					distance[adj] = distance[v] + weight_matrix[v][adj];
					int index = (distance[v] + weight_matrix[v][adj]) % K+1;
					array_queue[index].push(adj);
				}
			}
		}

	}

	for (int i = 0; i < distance.size(); ++i){
		cout << "Vertex: " << i << ", " << "ShortestPath: " << distance[i] << endl;
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

	vector<vector<int> > weight_matrix(7, vector<int>(7));

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

	dijstraUsingArray(adj_list, weight_matrix, 0, 10);

}