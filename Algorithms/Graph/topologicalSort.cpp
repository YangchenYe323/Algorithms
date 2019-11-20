#include<iostream>
#include<vector>
using namespace std;

void eraseValue(std::vector<int>& myNumbers_in, int number_in)
{
    std::vector<int>::iterator iter = myNumbers_in.begin();
    while (iter != myNumbers_in.end())
    {
        if (*iter == number_in)
        {
            iter = myNumbers_in.erase(iter);
        }
        else
        {
           ++iter;
        }
    }

}
/*
privide the topological sort of the given graph represented
in an adjacency list
*/
void topologicalSort(vector<vector<int> > & adj_list){

	vector<int> marked(adj_list.size(), 0);
	int markedCount = 0;

	//reverse the adj_list to denote in degrees
	vector<vector<int> > in_adj_list(adj_list.size());

	for (int v = 0; v < adj_list.size(); ++v){
		for (int adj : adj_list[v]){
			in_adj_list[adj].push_back(v);
		}
	}

	//while there is still unvisited vertex
	while (markedCount < adj_list.size()){

		//select a vertex with 0 indegree
		for (int v = 0; v < in_adj_list.size(); ++v){
			if (in_adj_list[v].size() == 0 && marked[v] == 0){
				//mark as visited
				marked[v] = 1;
				markedCount++;
				//erase it from the graph by deleting all the edges that stems from it
				for (int adj: adj_list[v]){
					eraseValue(in_adj_list[adj], v);
				}
				//print
				cout << v << " ";
			}
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

	topologicalSort(graph);
}