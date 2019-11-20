#include<iostream>
#include<vector>
using namespace std;
//this program implements a simple merge sort algorithm and a binary search algorithm,
//and uses both to solve the problem 4 in O(nlogn) time

//an O(nlogn) sorting algorithm
class sort{
public:
	static void mergeSort(vector<int> & arr){
		int low = 0;
		int high = arr.size() - 1;
		mergeSort_rec(arr, low, high);
	}

private:
	//merge sort
	static void mergeSort_rec(vector<int> & arr, int low, int high){
		if (low == high) return;
		int mid = (low + high) / 2;
		mergeSort_rec(arr, low, mid);
		mergeSort_rec(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}

	//merge an array from index low to index high, the break point being mid
	static void merge(vector<int> & arr, int low, int mid, int high){
		int size = high - low + 1;
		vector<int> container{};
		int i = low;
		int j = mid + 1;
		//merge
		while(i <= mid || j <= high){
			if (i > mid) container.push_back(arr[j++]);

			else if(j > high) container.push_back(arr[i++]);

			else{

				if (arr[i] < arr[j]) container.push_back(arr[i++]);

				else container.push_back(arr[j++]);
			}
		}
		//move the sorted back
		for (int x = 0; x < size; ++x){
			arr[low + x] = container[x];
		}
	}

};

class search{
public:
	//this algorithm tests whether the integer goal is found in the vector arr using
	//an iterative binary search.
	//assume the given array is sorted in increasing order
	static bool searchFound(const vector<int> & arr, int goal){
		int low = 0;
		int high = arr.size() - 1;
		while (low <= high){
			int mid = (low + high) / 2;
			if (arr[mid] == goal) return true;
			else if (arr[mid] < goal) low = mid + 1;
			else high = mid - 1;
		}
		return false;
	}
};

class SumOfTwoNumbers{
public:
	//this method takes an array and a number K, and tests whether K can be 
	//expressed as the sum of any two numbers in the arry, using a combination
	//of merge sort and binary search to reach O(nlogn) running time
	static bool canBeSum(const vector<int> arr, int K){
		//duplicate the vector to sort, which is O(n) time, doesn't
		//impact asymptotic performance
		vector<int> dup_arr(arr.size());
		for (int i = 0; i < arr.size(); ++i){
			dup_arr[i] = arr[i];
		}
		//sort the duplicated array, which costs O(nlogn) time
		sort::mergeSort(dup_arr);

		//for every element e in the array, search for K-e in the same array using
		//binary search, which should costs total O(nlogn) time
		for (int e : dup_arr){
			//found any one is ok
			if (search::searchFound(dup_arr, K-e)) return true;
		}
		//not found, return false
		return false;
	}
};



int main(){
	//test correctness of mergesort
	vector<int> arr = {1, 3, 2, 5, 4, 8, 7, 9, 10};
	sort::mergeSort(arr);
	for (int i = 0; i < arr.size(); ++i){
		cout << arr[i] << " ";
	}
	cout << endl;
	//test binary search
	cout << search::searchFound(arr, 9) <<endl;

	//test solution for problem 4
	vector<int> test = {8, 4, 1, 6};
	int K = 11;
	cout << SumOfTwoNumbers::canBeSum(test, K) << endl;


}