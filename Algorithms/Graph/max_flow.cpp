#include<iostream>
#include<vector>
#include<climits>
#include<queue>
using namespace std;

typedef struct{
	int id;
	int predecessor;
	int minCap;
	vector<int> * edges;
} vertex;


void clean_up(vector<vertex> & adj_list){
	for (vertex & v : adj_list){
		v.predecessor = -1;
		v.minCap = INT_MAX;
	}
}

/**
search a path from s to t in the graph
constraint: the minimun edge flow cannot be 0
*/
bool bfs_search(int s, int t, vector<vertex> & adj_list, vector<vector<int> > & weight_matrix){
	
	vector<int> marked(adj_list.size(), 0);

	queue<int> bfs{};

	bfs.push(s);
	marked[s] = 1;

	while (!bfs.empty()){

		int cur = bfs.front();
		bfs.pop();
		if (cur == t) return true;

		for (int adj : *(adj_list[cur].edges)){

			if (marked[adj] == 0 && weight_matrix[cur][adj] != 0){

				marked[adj] = 1;
				adj_list[adj].predecessor = cur;
				adj_list[adj].minCap = min(adj_list[cur].minCap, weight_matrix[cur][adj]);
				bfs.push(adj);

			}

		}

	}

	return false;

}

int update_residual(int t, vector<vertex> & adj_list, vector<vector<int> > & weight_matrix){
	int this_min = adj_list[t].minCap;

	//update the flow
	while (adj_list[t].predecessor != -1){
		int p = adj_list[t].predecessor;
		weight_matrix[p][t] -= this_min;
		weight_matrix[t][p] += this_min;
		t = p;
	}

	return this_min;

}

int max_flow(vector<vertex> & adj_list, vector<vector<int> > & weight_matrix, int s, int t){

	int max = 0;
	
	clean_up(adj_list);

	while (bfs_search(s, t, adj_list, weight_matrix)){

		max += update_residual(t, adj_list, weight_matrix);

		clean_up(adj_list);

	}

	return max;
	/*clean_up(adj_list);

	bfs_search(s, t, adj_list, weight_matrix);

	cout << adj_list[t].predecessor << endl;

	cout <<adj_list[adj_list[t].predecessor].predecessor << endl;

	cout <<adj_list[adj_list[adj_list[t].predecessor].predecessor].predecessor << endl;

	cout << adj_list[0].predecessor << endl;

	return adj_list[t].minCap;*/



}

int main(){

	vertex s; s.id = 0;
	vertex a; a.id = 1;
	vertex b; b.id = 2;
	vertex c; c.id = 3;
	vertex d; d.id = 4;
	vertex t; t.id = 5;

	s.edges = new vector<int>{1, 2};
	a.edges = new vector<int>{0, 2, 3, 4};
	b.edges = new vector<int>{0, 1, 4};
	c.edges = new vector<int>{1, 5};
	d.edges = new vector<int>{1, 2, 5};
	t.edges = new vector<int>{3, 4};

	vector<vertex> adj_list;
	adj_list.push_back(s);
	adj_list.push_back(a);
	adj_list.push_back(b);
	adj_list.push_back(c);
	adj_list.push_back(d);
	adj_list.push_back(t);

	vector<vector<int> > weight_matrix(6, vector<int>(6, -1));

	weight_matrix[0][1] = 4; weight_matrix[1][0] = 0;
	weight_matrix[0][2] = 2; weight_matrix[2][0] = 0;
	weight_matrix[1][2] = 1; weight_matrix[2][1] = 0;
	weight_matrix[1][3] = 2; weight_matrix[3][1] = 0;
	weight_matrix[1][4] = 4; weight_matrix[4][1] = 0;
	weight_matrix[2][4] = 2; weight_matrix[4][2] = 0;
	weight_matrix[3][5] = 3; weight_matrix[5][3] = 0;
	weight_matrix[4][5] = 3; weight_matrix[5][4] = 0;

	cout << max_flow(adj_list, weight_matrix, 0, 5) << endl;

	vertex s1; s1.id = 0;
	vertex a1; a1.id = 1;
	vertex b1; b1.id = 2;
	vertex t1; t1.id = 3;

	s1.edges = new vector<int>{1, 2};
	a1.edges = new vector<int>{0, 2, 3};
	b1.edges = new vector<int>{0, 1, 3};
	t1.edges = new vector<int>{1, 2};

	vector<vertex> adj_list1;
	adj_list1.push_back(s1);
	adj_list1.push_back(a1);
	adj_list1.push_back(b1);
	adj_list1.push_back(t1);

	vector<vector<int> > weight_matrix1(4, vector<int>(4, -1));

	weight_matrix1[0][1] = 1000; weight_matrix1[1][0] = 0;
	weight_matrix1[0][2] = 1000; weight_matrix1[2][0] = 0;
	weight_matrix1[1][2] = 1; weight_matrix1[2][1] = 0;
	weight_matrix1[1][3] = 1000; weight_matrix1[3][1] = 0;
	weight_matrix1[2][3] = 1000; weight_matrix1[3][2] = 0;

	cout << max_flow(adj_list1, weight_matrix1, 0, 3) << endl;

}