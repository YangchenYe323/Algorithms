#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
print out a topological sort 
*/
void queueTopoSort(const vector<vector<int> > & adj_list){

	//make an indegree map
	vector<int> indegree(adj_list.size(), 0);

	for (int v = 0; v < adj_list.size(); ++v){
		for (int num : adj_list[v])
			++indegree[num];
	}

	queue<int> topQueue{};

	for (int i = 0; i < indegree.size(); ++i){
		if (indegree[i] == 0)
			topQueue.push(i);
	}

	while (!topQueue.empty()){

		int cur = topQueue.front();
		topQueue.pop();
		cout << cur << " ";

		//scan its neighbor
		for (int adj : adj_list[cur]){
			//if indegree drops to 0, enqueue
			if (--indegree[adj] == 0) topQueue.push(adj);
		}

	}

}

int main(){

	vector<vector<int> > graph(11, vector<int>());

	graph[0].push_back(1);
	graph[0].push_back(2);
	graph[0].push_back(3);
	graph[1].push_back(4);
	graph[1].push_back(5);
	graph[2].push_back(3);
	graph[2].push_back(5);
	graph[2].push_back(6);
	graph[3].push_back(1);
	graph[3].push_back(5);
	graph[4].push_back(7);
	graph[5].push_back(7);
	graph[5].push_back(8);
	graph[5].push_back(9);
	graph[6].push_back(5);
	graph[6].push_back(9);
	graph[7].push_back(10);
	graph[8].push_back(7);
	graph[8].push_back(10);
	graph[9].push_back(8);
	graph[9].push_back(10);

	queueTopoSort(graph);
}