#include <iostream> 
#include<fstream>
#include <vector> 
#include <list> 
#include <iterator>
#include <utility>  // std::pair, std::make_pair
using namespace std; 

#define INF 99999

/**
Name: Yangchen Ye
LoginID: yyewm
*/

struct edge
{
  int out; //end vertex of the edge 
  int weight; //edge weight
};

struct Vertex
{
  list <edge> adj; //adjacency list
  bool known; //known shortest path?
  int dist; //shortest path distance
  int path; //pevious vertex in shortest path
  int heap_pos; //where is the vertex in the heap
};

void initialize_heap(vector<pair<int, int> > &heap)
{
  heap.push_back(make_pair(0,0));
}

//insert a pair in the heap [dist, id] and update nodes[id].heap_pos

void insert_heap(vector<Vertex> & nodes, vector<pair<int, int> > &heap, pair <int, int> p)
{
  pair<int, int> q;

  heap.push_back(p);

  int i=heap.size()-1;

  //
  nodes[heap[i].second].heap_pos=i;

  while ((heap[i]<heap[i/2]) && (i/2>0))
    {
      q=heap[i];
      heap[i]=heap[i/2];
      heap[i/2]=q;
      nodes[heap[i].second].heap_pos=i;
      nodes[heap[i/2].second].heap_pos=i/2;
      i=i/2;
    }

}

//return the index of the smallest child of i in heap
int smallerChild(vector<pair<int, int> > & heap, int i){

  //if no child return -1
  int smaller = -1;

  //check if there is a left child
  if (i * 2 < heap.size()) 
    smaller = i * 2;

  //check if there is a right child that is smaller
  if (i * 2 + 1 < heap.size() && heap[i*2 + 1] < heap[i*2]) 
    smaller = i * 2 + 1;

  return smaller;

}

//delete the minimal iten stored at the first place of the heap and rebuild heap thereafter
pair<int, int> delete_min_in_heap(vector<Vertex> & nodes, vector<pair<int, int> > &heap){

  //store the first element in the heap to return
  pair<int, int> result = heap[1];

  //temporary container
  pair<int, int> q;

  //the last element
  pair<int, int> last = heap[heap.size()-1];

  //move the last to the first and erase the last
  heap[1] = last;
  heap.erase(heap.end()-1);

  //update heap position
  nodes[heap[1].second].heap_pos = 1;

  //percolate down
  int i = 1;
  int smaller = smallerChild(heap, i);
  while (smaller != -1 && heap[i] > heap[smaller]){

    q = heap[i];
    heap[i] = heap[smaller];
    heap[smaller] = q;

    //update position in heap
    nodes[heap[i].second].heap_pos = i;
    nodes[heap[smaller].second].heap_pos = smaller;

    i = smaller;
    smaller = smallerChild(heap, i);

  }

  return result;

}

void show_heap(vector<pair<int, int> > &heap)
{
  for(int i=0; i<heap.size(); i++)
    cout<<"["<<heap[i].first<<","<<heap[i].second<<"]"<<" ";

  cout<<endl;
}

//find the shortest path to each vertex in nodes from s
void dijkstra(vector<Vertex> & nodes, int s)
{ 
  //initialize setting
  pair <int, int> p1;
  vector<pair<int, int> > heap;

  for(int i=0; i<nodes.size(); i++)
    {
      nodes[i].dist = INF;
      nodes[i].known = 0;
    }

  nodes[s].dist = 0;
  nodes[s].path = -1;

  initialize_heap(heap);

  for(int i=0; i<nodes.size(); i++)
    {
      p1 = make_pair(nodes[i].dist, i);
      insert_heap(nodes, heap, p1); 
    }

  //algorithm begins
  //loop until the heap has only one sentinel in it
  while (heap.size() >= 2){

    //set up the curent vertex
    pair<int, int> cur = delete_min_in_heap(nodes, heap);
    int v_index = cur.second;
    int v_dist = cur.first;

    //if already visited this node(with shorter path), skip this 
    //this is necessary because in c++ implementation we don't decreease key.
    //we sent another copy of the same node again into the heap
    if (nodes[v_index].known) continue;

    //mark the state of the node as visited, no further change of
    //distance is possible
    nodes[v_index].known = 1;

    //loop throgh the unknown adjacent vertex
    for (edge e : nodes[v_index].adj){

        int adj_index = e.out;
        int this_weight = e.weight;

        if (!nodes[adj_index].known){

        //if the path from v to adj is a shorter path, update
        if (v_dist + this_weight < nodes[adj_index].dist){
          nodes[adj_index].dist = v_dist + this_weight;
          nodes[adj_index].path = v_index;
          pair<int, int> newPath = make_pair(v_dist + this_weight, e.out);
          //insert a copy of the new pair containing the shortest path into the heap, which
          //will go ahead of the original one, so that the original one will not be considered
          insert_heap(nodes, heap, newPath);
        }

      }

    }

  }

  
  show_heap(heap);
  for(int i=0; i<nodes.size(); i++)
  cout<<"("<<i<<","<<nodes[i].heap_pos<<")"<<" ";
  cout<<endl;
  




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

int main() 
{ 

  ifstream dataFile;
  int NUM_VERTICES, v1, v2, v3;

  dataFile.open("gdata2.txt");

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

 //run dijkstra
 dijkstra(nodes, 0);

 //print out paths
 for(int i=0; i<nodes.size(); i++)
   {
     print_path(nodes, i);
     cout<<endl;
   }

 return 0; 
 
} 