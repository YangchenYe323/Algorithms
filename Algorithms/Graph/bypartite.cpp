#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
this function determins if the given graph is bypartite
it performs a BFS-like algorithm on every unvisited vertex
1. color that vertex 1, scan its neighbor, color them 0
2. repeat in its neighbor
if at some point a vertex has the same color as its neighbor, return false
if the whole graph can be colored, return true
*/
bool isBypartite(const vector<vector<int> > & adj_list){

	//array indicating the vertex has been visited
	vector<int> marked(adj_list.size(), 0);

	//array of vertex's color, initially uncolored
	vector<int> color(adj_list.size(), -1);

	//loop through all the vertex
	for (int v = 0; v < adj_list.size(); ++v){
		//v is unvisited
		if (marked[v] == 0){

			//do the BFS from that vertex
			queue<int> BFS{};

			BFS.push(v);
			marked[v] = 1;
			//color the vertex 1
			color[v] = 1;

			while (!BFS.empty()){

				int cur = BFS.front();
				BFS.pop();

				//loop through cur's adjacent
				for (int adj : adj_list[cur]){
					//if its adjacent has the same color as itself
					if (color[adj] == color[cur]) return false;
					//if its adjacent has not been visited and painted
					if (marked[adj] == 0 && color[adj] == -1){
						BFS.push(adj);
						marked[adj] = 1;
						color[adj] = 1 - color[cur];
					}
				}
			}

		}
	}

	//the graph is successfully painted, return true
	return true;

}


int main(){

	vector<vector<int> > adj_list(3, vector<int>());

	adj_list[0].push_back(1);
	adj_list[1].push_back(2);

	cout << isBypartite(adj_list) << endl;

}