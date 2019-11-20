#include <iostream> 
#include<fstream>
#include <vector> 
#include <list> 
#include <iterator> 
#include<stack>
#include<queue>
using namespace std; 

/**
Yangchen Ye
yyewm
*/

//add an edge (u1, u2) to adjacency list
void add_edge(vector<list<int> > & adj_list, int u1, int u2)
{
  adj_list[u1].push_back(u2);
  adj_list[u2].push_back(u1);
}

//recursively traverse the graph
void traverse(vector<list<int> > & adj_list, vector<int> & marked, int v)
{

  if (marked[v]==1) return;
  cout<<v<<" ";
  marked[v]=1;

  for(auto x : adj_list[v])
    traverse(adj_list, marked, x);

}

//traverse all nodes in the graph, in particular for disconnected graph

void traverseAll(vector<list<int> > & adj_list)
{
  vector<int> marked(adj_list.size());

  for(int i=0; i<adj_list.size(); i++)
    marked[i]=0;

  cout<<"Start to traverse the graph: \n";

  for(int i=0; i<adj_list.size(); i++)
      if (marked[i]==0)  traverse(adj_list, marked, i);
}

//helper method to use dfs to traverse the graph from one node
void dfsOneNode(vector<list<int> > & adj_list, vector<int> & marked, int v){

  //has visited
  if (marked[v] == 1) return;

  stack<int> dfsStack{};
  dfsStack.push(v);
  marked[v] = 1;

  while (!dfsStack.empty()){

    int node = dfsStack.top();
    dfsStack.pop();
    cout << node << " ";
    for (int adjacent : adj_list[node]){
      if (marked[adjacent] == 0){
        marked[adjacent] = 1;
        dfsStack.push(adjacent);
      }
    }
  }
}

//helper method to use bfs to traverse the graph from one node
void bfsOneNode(vector<list<int> > & adj_list, vector<int> & marked, int v){

  //has visited
  if (marked[v] == 1) return;

  queue<int> bfsQueue{};
  bfsQueue.push(v);
  marked[v] = 1;

  while (!bfsQueue.empty()){

    int node = bfsQueue.front();
    bfsQueue.pop();
    cout << node << " ";
    for (int adjacent : adj_list[node]){
      if (marked[adjacent] == 0){
        marked[adjacent] = 1;
        bfsQueue.push(adjacent);
      }
    }

  }

}

//use non-recursive method to implement bfs
void bfs(vector<list<int> > & adj_list)
{ 
  cout << "Start Bfs Using a Queue: " << endl;

  vector<int> marked(adj_list.size(), 0);
  for (int i = 0; i < adj_list.size(); ++i){
    bfsOneNode(adj_list, marked, i);
  }

  cout << endl;


}

//use non-recursive method to implement dfs
void dfs(vector<list<int> > & adj_list)
{
   cout << "Start Dfs Using a Stack: " << endl;

  vector<int> marked(adj_list.size(), 0);
  for (int i = 0; i < adj_list.size(); ++i){
    dfsOneNode(adj_list, marked, i);
  }

  cout << endl;
}



//fill in the adjacency matrix based on adjacency list
void convert2matrix(vector<list<int> > & adj_list, vector<vector<int> > & adj_matrix)
{
  for (int i = 0; i < adj_list.size(); ++i){
    for (int j : adj_list[i])
      adj_matrix[i][j] = 1;
  }
}

//show a square matrix NxN
void show_matrix( vector<vector<int> > & matrix)
{
    cout<<endl;
  cout<<"Start to show the adjacency matrix: \n";
    for(int i=0; i<matrix.size(); i++)
    {
      for (int j=0; j<matrix.size(); j++)
	cout<<matrix[i][j]<<" ";
      cout<<endl;
    }

}

// print out all edges from adjacency list
void show_graph(vector<list<int> > & adj_list)
{
  cout<<endl;

  cout<<"Start to show the graph: \n";

  for(int i=0; i<adj_list.size(); i++)
    {
      for (auto j : adj_list[i])
	cout<<"("<<i<<","<<j<<") ";
      cout<<endl;
}
}

int main() 
{ 

  ifstream dataFile;
  int NUM_VERTICES, v1, v2;

  //reading graph data 
  dataFile.open("gdata.txt");

  if (!dataFile.is_open()) return 0;

  //first line of gdata.txt is number of vertices in the graph
  if (!(dataFile>>NUM_VERTICES)) return 0;

  cout<<"The graph has "<<NUM_VERTICES<<" vertices."<<endl;

/*
declare adjacency list and adjacency matrix. 
marked is for graph traversal
*/

  vector<list<int> > adj_list(NUM_VERTICES);
  vector<vector<int> > adj_matrix(NUM_VERTICES, vector<int> (NUM_VERTICES, 0) );
  vector<int> marked(NUM_VERTICES);

  while ((dataFile>>v1) && (dataFile>>v2))
    add_edge(adj_list, v1, v2);

 dataFile.close();

 // for (int i=0; i<NUM_VERTICES; i++)
 //   marked[i]=0;

 traverseAll(adj_list);

 show_graph(adj_list);

 dfs(adj_list);
 bfs(adj_list);

 convert2matrix(adj_list, adj_matrix);
 show_matrix(adj_matrix);

 return 0; 
  
} 