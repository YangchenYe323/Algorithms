#include <iostream> 
#include<fstream>
#include <vector> 
#include <queue>
#include <list> 
#include <iterator> 
using namespace std; 
#define infi 9999

struct edge
{
  int out; //end vertex of the edge 
  int weight; //edge weight
};

struct Vertex
{
  list <edge> adj; //adjacency list
  bool known; //known in the spanning tree?
  int dist; //distance to the existing tree
  int path; //pevious vertex in spanning tree
};

struct heap_item
{
  //id: the node id, 
  //path: the previous node in the spanning tree
  //dist: the weight of the edge connecting the node to the exisiting spanning tree

  int id, path, dist;

  //define the < less than operator for heap_item
  //now you can compare two heap_items 

  bool operator< (const heap_item & p)const
  {
        return dist>p.dist;
  }

};


void showHeap(priority_queue<heap_item> items)
{
  cout<<"HERE COMES SHOWHEAP"<<endl;

  while(!items.empty())
    {
      heap_item item = items.top();
      items.pop();
      cout<<item.id<<" "<<item.dist<<endl;
    }

  cout<<"HERE ENDS SHOWHEAP"<<endl;
}


//initialzie heap, starting node is s
void initHeap(vector<Vertex> & nodes, priority_queue<heap_item> & items, int s)
{
  vector<heap_item> array(nodes.size());


  //assign node id to items in the heap
  for (int i =0; i < array.size(); i++)
    {      
      array[i].id=i;
      array[i].path=-1;
      array[i].dist=infi; 
    }

  //the starting node s
  array[s].dist=0;

  //insert all the nodes in the heap
  for (int i =0; i < array.size(); i++)
    items.push(array[i]);


  showHeap(items);
}
	     

	     

//implement minimal spanning tree based on Prim's algorithm, starting node is s

void mst(vector<Vertex> & nodes, int s)
{

  //initialize heap
  priority_queue<heap_item> items;
  initHeap(nodes, items, s);


  //initialize nodes 
  for(int i=0; i<nodes.size(); i++)
    {
      nodes[i].path = -1;
      nodes[i].known = 0;
      nodes[i].dist = infi;
    }


  while(!items.empty())
    {

      heap_item cur = items.top();
      items.pop();

      Vertex & cur_vertex = nodes[cur.id];

      if (!cur_vertex.known){

        //fix the final set of the vertex
        cur_vertex.known = true;
        cur_vertex.dist = cur.dist;
        cur_vertex.path = cur.path;

        for (edge e : cur_vertex.adj){

          int adj_vertex = e.out;
          int weight = e.weight;

          //push a copy into the heap
          heap_item this_item;
          this_item.id = adj_vertex;
          this_item.dist = weight;
          this_item.path = cur.id;

          items.push(this_item);
        }

      }

    }

}

void show_graph(vector<Vertex> & nodes)
{
  cout<<endl;
  for(int i=0; i<nodes.size(); i++)
    {
      for (auto j : nodes[i].adj)
	cout<<"("<<i<<","<<j.out<<") "<<j.weight<<endl;
    }
}

//print the path for node v
void print_path(vector<Vertex> & nodes, int v)
{
  
  if (nodes[v].path>=0) print_path(nodes, nodes[v].path);
  cout<<v<<" ";
}

int compute_weight(vector<Vertex> & nodes)
{
  int sum=0;
  for (int i=0; i<nodes.size(); i++)
    {
      //cout<<i<<" "<<nodes[i].dist<<endl;
      sum += nodes[i].dist;
    }
  return sum;
}

int main() 
{ 

  ifstream dataFile;
  int NUM_VERTICES, v1, v2, v3;

  dataFile.open("gdata3.txt");

  if (!dataFile.is_open()) return 0;
 
  if (!(dataFile>>NUM_VERTICES)) return 0;

  cout<<NUM_VERTICES<<endl;

  vector<Vertex> nodes(NUM_VERTICES);



  while ((dataFile>>v1) && (dataFile>>v2) && (dataFile>>v3))
    {
      edge e;
      e.out = v2;
      e.weight = v3;
      nodes[v1].adj.push_back(e);
      cout<<v1<<" "<<v2<<" "<<e.weight<<endl; 	 
      }

 dataFile.close();


 show_graph(nodes);

 //run mst
 mst(nodes,0);

 
 //print out paths
 for(int i=0; i<nodes.size(); i++)
   {
     print_path(nodes, i);
     cout<<endl;
   }
 
 cout<<"Sum of  weights of the minimal spanning tree is "<<compute_weight(nodes)<<endl;

 return 0; 
 
} 