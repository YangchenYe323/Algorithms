/*==================
Your Name: Yangchen Ye
Your Login ID: yyewm
==================*/

#include <iostream> 
#include<fstream>
#include <vector> 
#include <iterator> 
using namespace std; 

void showHeap(vector<int> h)
{
  /*
    vector <int> :: iterator it; 
    for(it = h.begin(); it != h.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n';
  */

    for(int i=0; i < h.size(); ++i) 
        cout << '\t' << h[i]; 
    cout << '\n';

}

//this helper method percolates up the element at index in a heap
//by iteratively comparing it with its parent node and swap if it is
//smaller than the parent
//the heap is assumed to start from position 1
void percolate_up(vector<int> & heap, int index){
  int cursor = index;
  //while the node is not the root and should go up
  while (cursor != 1 && heap[cursor] < heap[cursor/2]){
    //get the index for its parent
    int parent = cursor / 2;
    //swap
    int temp = heap[cursor];
    heap[cursor] = heap[parent];
    heap[parent] = temp;
    //progress
    cursor = parent;
  }
}

//this helper method returns the index of element's smaller child
//in the heap
int smaller(vector<int> & heap, int index){
  int smaller = -1;
  //if there is a left child
  //update smaller
  if (2 * index < heap.size()){
    smaller = 2 * index;
  }
  //if there is a right child and it is smaller than the left,
  //update smaller
  if (2 * index + 1 < heap.size() && heap[2*index + 1] < heap[2*index]){
    smaller = 2 * index + 1;
  }
  return smaller;
}

//this helper method percolates down the element at idex in the heap
//by iteratively comparing it with its smaller child node and swap if it
//is bigger than that child
//the heap is assumed to start from position 1
void percolate_down(vector<int> & heap, int index){
 
  //work only if the element has a valid smaller child
  //and there is a need to swap
  int next = smaller(heap, index);
  while (next > 0 && heap[index] > heap[next]){
    //swap
    int temp = heap[index];
    heap[index] = heap[next];
    heap[next] = temp;
    //update
    index = next;
    next = smaller(heap, index);
  }

}

/**
This function builds up a heap from an array by successively inserting 
the elements of the array to a minimun heap which is originally empty
*/
void buildHeap1(vector<int> &h1)
{
  //container for temporarily storing the heap
  vector<int> tempHeap{};
  tempHeap.push_back(0);
  for (int i = 1; i < h1.size(); ++i){
    //insert and percolate down to rebuild the heap
    tempHeap.push_back(h1[i]);
    percolate_up(tempHeap, i);
  }

  //get the element back to h1
  h1.push_back(0);
  for (int i = 0; i < h1.size(); ++i){
    h1[i] = tempHeap[i]; 
  }
}

/**
This function initializes a heap from a given array in place by
reversely percolate down the elemeent in the array from size/2 to 1;
*/
void buildHeap2(vector<int> &h2)
{
  int start = h2.size() / 2;
  for (; start > 0; --start){
    percolate_down(h2, start);
  }
}


/*====================================================
Compare the running time of both algorithms in a and b 
for sorted, reverse-ordered, and random inputs. 

Sorted inputs: a sorted array is itself a heap. For algorithm a,
the while loop in percolate_up method is never entered because the newly
inserted element is always bigger, so the work inside the loop in the program 
is always constant. Since other work is also O(n), the overall performance
of the program is O(n). For algorithm b, the running time is also O(n), as the percolate_down
function inside the for loop always costs constant time because its while loop would
never be executed. The number of loop in algorithm b is some place around n/2, so the 
performance is also O(n).

Reverse-ordered inputs: In a reverse-ordered array, if looked as a heap, every child is smaller
than its parent, which means the while loop in percolate_up function would be executed k times,
where k is the height of the heap, which is log(n). Therefore, the running time of algorithm a
would be log(1) + log(2) + ... + log(n), which would amount to O(nlogn).
Things get different in algorithm b. The while loop in percolate_down function would also 
be executed k times, where k is the height of the heap, but in the case of algorithm b, k is 
always the height of the sub-heap rooted at index start. Assume the heap has a total n nodes.
Then it has roughly n/2 nodes at the very last level, and has rough n/4 nodes at the second
last level, in which algorithm b begins percolating nodes down. Whenever the height of subtree
increases by 1, the number of nodes decreses by half. The total running time would be calculated
by, assuming k is the height of the heap:
(n/4) * 1 + (n/8) * 2 + ... + 1 * k = sigma(i = 1, i <= k)((i*n)/(2^i+1)) 
which will ultimately be O(n) running time, as the series 
(i/2^i+1) is ultimately less than a constant number. Therefore, for a reverse-ordered
input, it takes O(n) time to build a heap using algorithm b.

Randomized Inputs: for a random input, the performance of both algoritm a and algorithm b
are the same as with a reverse-ordered input. Algorithm a still takes O(nlogn) times and 
algorithm b still takes O(n). The coefficient will be smaller, but no impact of the overall
performance level

====================================================*/


int findKthLargest(vector<int> &h, int k)
{

  if (k > h.size()) return -1;
  // first build a heap with the first k numbers
  //skipping the first cell
  vector<int> heap(k+1);
  heap[0] = 0;
  for (int i = 0; i < k; ++i){
    heap[i+1] = h[i];
  }
  buildHeap2(heap);
  //compare the new number with the top and 
  //decide whether we should insert the new number. 
  for (int i = k; i < h.size(); ++i){
    //should insert
    if (h[i] > heap[1]){
      heap[1] = h[i];
      percolate_down(heap, 1);
    }
  }
  return heap[1];
}

void findAllLessThanX_rec(vector<int> & h, int x, int root, vector<int> & result){
  if (root < h.size() && h[root] < x){
    result.push_back(h[root]);
    findAllLessThanX_rec(h, x, 2*root, result);
    findAllLessThanX_rec(h, x, 2*root+1, result);
  }
}

//find all numbers less than x in a heap h,
//h is assumed to be a minumun heap
void findAllLessThanX(vector<int> &h, int x)
{
  vector<int> result{};
  int root = 1;
  findAllLessThanX_rec(h, x, root, result);

  for (int i = 0; i < result.size(); ++i){
    cout << result[i] << " ";
  }
  cout << endl;
}
/*
Argument showing the performance of findAllLessThanX is O(K), where k is the number of nodes
less than X.
Proof by mathematical induction:
1. When K = 0, then no nodes is less than X, which means the minimal of the heap, which is the
root node, is not less than X. Therefore, the if statement would not be true, so there is only one
operations executed, which is 2 * 0 + 1
2. When K = 1, then only the root node is less than X, and the recursive call would immediately
fail at the if statement, so 3 operations are executed, which is 2 * 1 + 1
2. Assume when k = n, the operations needed is 2 * n + 1. Then consider k = n + 1;
this means that one more recursive function would pass the if statement, so that 2 more operations
will be executed, because once the if statement is passed, you have to call the recursive
function twice, and since k = n + 1, the newly called recursive function would not pass their
if statement, so there are only 2 more operations. Therefor, for k = n + 1, there are a total
2 * n + 1 + 2 = 2 * (n+1) + 1 operations. 
Therefore, by principles of induction, for any K >= 0, the running time of my algorithm is a
function of K, 2 * K + 1, which is O(k) running time.

*/

int main() 
{ 

  ifstream dataFile;
  vector<int> heap, heap1, heap2;
  int num;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

  heap.push_back(0);
  heap1.push_back(0);
  heap2.push_back(0);

  if (dataFile.is_open()) 
    while (dataFile>>num)
      {
      heap.push_back(num);
      heap1.push_back(num);
      heap2.push_back(num);
      }
  dataFile.close();

  buildHeap1(heap1);
  showHeap(heap1);

  buildHeap2(heap2);
  showHeap(heap2);

  int k, x;
  cout<<"Please input a number k: ";
  cin>>k;

  cout<<k<<"-th largest number is "<<findKthLargest(heap,k)<<endl;

  cout<<"Please input a number X: ";
  cin>>x;
  findAllLessThanX(heap1, x);

  return 0; 
  
} 