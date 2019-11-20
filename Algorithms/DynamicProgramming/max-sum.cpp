/*
NAME: Yangchen Ye
CS Account id: yyewm
 */

#include <iostream>
#include<fstream>
#include <vector>
#include<climits>
using namespace std;

//this function returns the maximal sum of contigious subarray of vector a
int maxSubSum( const vector<int> & a )
{

  int n = a.size();

  //map[i] stores the maximal sum of contigious subarray ending at index i,
  //which is calculated based on maximal contigious subarray ending at index
  //i-1
  vector<int> map(n);

  //the maximal sum of contigious subarray ending at index 0 is
  //0 if a[0] < 0 and a[0] otherwise
  map[0] = max(0, a[0]);

  for (int i = 1; i < n; ++i){
  	//for subsequent cells, map[i] is just a[i] + map[i-1],
  	//if the consequent map[i] falls below 0, than map[i]
  	//should be reset to 0, meaning the maximal sum of subarray ending
  	//at i is reached by not getting any element at all
  	map[i] = map[i-1] + a[i];
  	if (map[i] < 0) 
  		map[i] = 0;
  }

  //now return the max one of the whole map
  int max = INT_MIN;
  for (int sum : map){
  	if (sum > max)
  		max = sum;
  }
  return max;

}

int main()
{
  int num;
  ifstream dataFile;
  vector<int> data;

  // READING NUMBERS FROM A FILE
  dataFile.open("data.txt");

  if (dataFile.is_open()) {
    while (dataFile>>num)
      data.push_back(num);
  }

  dataFile.close();

  //  for (int i=0; i<data.size(); i++)
  //    cout<<"Number "<<i<<" is "<< data[i]<<endl;


  int result;
  result = maxSubSum( data );
  cout << "Max sum is " <<  result << endl;

  return 0;
}