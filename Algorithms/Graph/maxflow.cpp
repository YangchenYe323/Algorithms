
/*
//Edmond-Karp Algorithm

set f-total = 0
repeat until there is no path from s to t
{
run bfs from s to find a flow path to t
let f be the minimum capacity value on the path
increase f-total by f
for each edge (u,v) on the path
{
increase flow f(u,v) by f
f(v,u)=-f(u,v)
decrease c(u,v) by f
increase c(v,u) by f
}
}
 */

#include <iostream> 
#include <fstream>
#include <vector> 
#include <queue>
#include <list> 
#include <iterator> 
using namespace std; 


struct Edge
{
  int capacity; //edge capacity
  int residual_capacity; //capacity in residual graph
  int flow; //how much flow is on this edge
};

struct Vertex
{
  bool visited; //has been visited in BFS?
  int path; //previous node on the path; 
  //use path to track the BFS path from s to the sink
};


//run breadth first search to find an augmenting path
bool bfs(vector<Vertex> & nodes, vector<vector<Edge> > & adj_matrix, int s, int t)
{
  queue<int> bfs_queue;

  for (int i=0; i< nodes.size(); i++)
    {
      nodes[i].visited = 0;
      nodes[i].path = -1;
    }

  //push the first node (source) to the queue. 
  //every time you push a node in the queue, mark it visited.
  //do not push viisted node in the queue
  nodes[s].visited = 1;
  bfs_queue.push(s);


  //put your program here
  while (!bfs_queue.empty()){

    int cur = bfs_queue.front();
    bfs_queue.pop();

    Vertex & cur_vertex = nodes[cur];

    for (int i = 0; i < adj_matrix[cur].size(); ++i){

      //if a valid edge
      if (adj_matrix[cur][i].residual_capacity > 0 && !nodes[i].visited){

        nodes[i].visited = 1;
        nodes[i].path = cur;

        bfs_queue.push(i);

        if (i == t){
          while (i != -1){
            cout << i << " ";
            i = nodes[i].path;
          }
          cout << endl;
         return true;

        } 
      }

    }

  }

  cout << 9999999 << endl;
  return false;


}

//find max-flow by modifying residual_capacity and flow
void max_flow(vector<Vertex> & nodes, vector<vector<Edge> > & adj_matrix, int s, int t)
{

  //put your program here
  while (bfs(nodes, adj_matrix, s, t)){

    int minFlow = 99999;
    int iter = t;
    //retrieve the min Capacity
    while (nodes[iter].path != -1){
      int pred = nodes[iter].path;
      int this_weight = adj_matrix[pred][iter].residual_capacity;
      if (this_weight < minFlow) minFlow = this_weight;
      iter = nodes[iter].path;
    }
    //update flow
    iter = t;
    while (nodes[iter].path != -1){
      int pred = nodes[iter].path;
      adj_matrix[pred][iter].flow += minFlow;
      adj_matrix[pred][iter].residual_capacity -= minFlow;
      adj_matrix[iter][pred].residual_capacity += minFlow;
      adj_matrix[iter][pred].flow = -adj_matrix[pred][iter].flow;
      iter = nodes[iter].path;
    }

  }

}

void show_graph(vector<vector<Edge> > adj_matrix)
{
  cout<<"comes show"<<endl;

  for (int i=0;i<adj_matrix.size();i++)
    {
      for (int j=0; j< adj_matrix.size(); j++)
	{
	  cout<<"["<<i<<","<<j<<"] "<<adj_matrix[i][j].capacity<<" "<<adj_matrix[i][j].residual_capacity<<" "<< adj_matrix[i][j].flow<<endl;
	}

    }
}

// show flow on each edge and show total flow
void show_flow(vector<vector<Edge> > adj_matrix, int s)
{
  cout<<"Flow on each edge:"<<endl;

  for (int i=0;i<adj_matrix.size();i++)
    {
      for (int j=0; j< adj_matrix.size(); j++)
	{
	  if (adj_matrix[i][j].flow > 0) 
	  cout<<"["<<i<<","<<j<<"] "<<adj_matrix[i][j].capacity<<" "<<adj_matrix[i][j].residual_capacity<<" "<< adj_matrix[i][j].flow<<endl;
	}

    }

  int flow=0;
      for (int j=0; j< adj_matrix.size(); j++)
	{
	  if (adj_matrix[s][j].flow > 0) 
	    flow += adj_matrix[s][j].flow;
	}

      cout<<"Total flow is "<<flow<<endl;

}

int main() 
{ 

  ifstream dataFile;
  int NUM_VERTICES, v1, v2, v3;

  dataFile.open("gdata4.txt");

  if (!dataFile.is_open()) return 0;
 
  if (!(dataFile>>NUM_VERTICES)) return 0;

  cout<<NUM_VERTICES<<endl;

  vector<Vertex> nodes(NUM_VERTICES);

  //In this program, we use adjacency matrix to represent the graph
  vector<vector<Edge> > adj_matrix(NUM_VERTICES);


  cout<<"here1"<<endl;

  int source=4, sink=NUM_VERTICES-1;

  for (int i=0;i<NUM_VERTICES;i++)
    {
  cout<<"here2"<<endl;

      adj_matrix[i] = vector<Edge> (NUM_VERTICES);

      for (int j=0; j< NUM_VERTICES; j++)
	{
	  adj_matrix[i][j].capacity=0;
	  adj_matrix[i][j].residual_capacity=0;
	  adj_matrix[i][j].flow=0;
	}

    }

  cout<<"here"<<endl;

  while ((dataFile>>v1) && (dataFile>>v2) && (dataFile>>v3))
    {

      adj_matrix[v1][v2].capacity=v3;
      adj_matrix[v1][v2].residual_capacity=v3;
      adj_matrix[v1][v2].flow=0;
      }

 dataFile.close();


 show_graph(adj_matrix);


 //run maxflow
 max_flow(nodes, adj_matrix, source, sink);

 
 show_flow(adj_matrix, source);

 return 0; 
 
} 