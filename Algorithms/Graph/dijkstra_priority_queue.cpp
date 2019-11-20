#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef pair<int, int> ii;

void dijkstra(const vector<vector<int> > & adj_list, const vector<vector<int> > & weight_matrix, int s){

	vector<int> distance(adj_list.size(), INT_MAX);
	vector<int> marked(adj_list.size(), 0);
	distance[s] = 0;

	priority_queue<ii, vector<ii>, greater<ii> > pq; 

	pq.push(make_pair(0, s));

	while (!pq.empty()){

		ii cur = pq.top();
		int v = cur.second;
		int dis = cur.first;
		pq.pop();

		//vertex v has been fixed before
		if (marked[v] == 2) continue;

		marked[v] = 2;

		for (int adj : adj_list[v]){

			if (marked[adj] == 0){
				marked[adj] = 1;
				distance[adj] = dis + weight_matrix[v][adj];
				pq.push(make_pair(distance[adj], adj));
			}
			else if (marked[adj] == 1 && distance[adj] > dis + weight_matrix[v][adj]){
				distance[adj] = dis + weight_matrix[v][adj];
				pq.push(make_pair(dis + weight_matrix[v][adj], adj));
			}

		}

	}

	for (int i = 0; i < distance.size(); ++i){ 
		cout << "index: " << i << ", " << "shortest path: " << distance[i] << endl;
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


	dijkstra(adj_list, weight_matrix, 0);
}

