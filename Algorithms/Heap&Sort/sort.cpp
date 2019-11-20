/*==================
Your Name: Yangchen Ye
Your Login ID: yyewm
==================*/

#include <iostream> 
#include<fstream>
#include <vector> 
#include <iterator> 
using namespace std; 


void showData(vector<int> h)
{
  /*
    vector <int> :: iterator it; 
    for(it = h.begin(); it != h.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n';
  */

    for(int i=0; i < h.size(); ++i) 
        cout <<"  " << h[i]; 
    cout << '\n';

}

//merge d[low,middle] and d[middle+1,high]
//this function modifies the implementation presented in class by
//doing the merge in-place. No extra space is needed. the way to 
//do it is as follows:
//keep the leftCursor and rightCursor, if arr[leftCursor] <= arr[rightCursor]
//do nothing. if arr[leftCursor] > arr[rightCursor], which means they should be swapped,
//then move arr[rightCursor] to index leftCursor, and move everything in between
//one step toward the right.
//The idea of this merge is to regard the part of array traversed by leftCursor as
//already sorted, and treat leftCursor as the next index of the sorted array.

/*
However, this implementation has a tradeoff in running time. Now the worst case merge
would cost O(n^2) time, more exactly O(n^2/4) time. So the in-place merge sort implemented
this way would run worst case O(n^2logn) time. 
*/
void merge(vector<int> &d, int low, int middle, int high)
{
  int leftCursor = low;
  int rightCursor = middle + 1;

  while (leftCursor <= middle && rightCursor <= high){
  	//no need to move anything
    if (d[leftCursor] <= d[rightCursor]) ++leftCursor;
    //move arr[rightCursor] to the sorted part, and continue merge the unsorted part
    else{
      int pivotValue = d[rightCursor];
      //move everything in between right
      int index = rightCursor;
      while (index > leftCursor){ 
        d[index] = d[index - 1]; 
        --index; 
      }
      //move arr[rightCursor] to its right place in the sorted subarray
      d[index] = pivotValue;

      //update cursor, continue merging the rest part
      ++leftCursor;
      ++rightCursor;
      ++middle;
    }
  }

}

void mergeSort(vector<int> &d, int low, int high)
{

  if (low >= high) return;

  int mid = (low + high) / 2;
  mergeSort(d, low, mid);
  mergeSort(d, mid+1, high);
  merge(d, low, mid, high);

}

//partition d[low,high] into (left, pivot, right)
//return the position of the pivot such that all smaller numbers 
// are on the left and all bigger numbers on the right
int partition(vector<int> &d, int low, int high)
{ 
  int pivotValue = d[low];
  int left = low + 1;
  int right = high;
  while (left <= right){
    //swap
    if (d[left] > pivotValue && d[right] < pivotValue){
      int temp = d[left];
      d[left] = d[right];
      d[right] = temp;
    }

    //progress
    if (d[left] <= pivotValue) ++left;

    if (d[right] >= pivotValue) --right;
  }

  //swap pivot and d[right]
  d[low] = d[right];
  d[right] = pivotValue;

  return right;

}

void quickSort(vector<int> &d, int low, int high)
{

  if (low >= high) return;

  int j = partition(d, low, high);
  quickSort(d, low, j - 1);
  quickSort(d, j + 1, high);


}


int main() 
{ 
  ifstream dataFile;
  vector<int> data1, data2;
  int num;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

  if (dataFile.is_open()) 
    while (dataFile>>num)
      {
      data1.push_back(num);
      data2.push_back(num);
      }
  dataFile.close();

  mergeSort(data1, 0, data1.size()-1);
  showData(data1);

  quickSort(data2, 0, data2.size()-1);
  showData(data2);

  return 0; 
  
} 