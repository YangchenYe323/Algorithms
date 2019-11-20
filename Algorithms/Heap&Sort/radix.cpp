#include<iostream>
#include<vector>
#include<cmath>
using namespace std;


//use radix sort to sort the given array, whose elements has
//at most d digits and are base k
void radixSort(vector<int> & arr, int d, int k){

	int n = arr.size();

	//initialize the bucket
	vector<vector<int> > bucket(k, vector<int>{});

	for (int i = 0; i < d; ++i){
		for (int j = 0; j < n; ++j){
			int bucketIndex = (arr[j] / (int)pow(k, i)) % 10;
			bucket[bucketIndex].push_back(arr[j]);
		}

		arr.clear();

		for (int x = 0; x < k; ++x){
			arr.insert(end(arr), begin(bucket[x]), end(bucket[x]));
			bucket[x].clear();
		}

	}


}

int main(){
	vector<int> map = {234, 425, 631, 349, 528, 910, 214};
	radixSort(map, 3, 10);
	for (int element: map)
		cout << element << endl;

}