#include<iostream>
#include<vector>
using namespace std;

//binary search
bool binarySearch(const vector<int> arr, int target){
	
	int low = 0; int high = arr.size()-1;

	int mid;

	while (low <= high){
		mid = (low + high) / 2;

		if (arr[mid] == target) return true;
		else if (arr[mid] > target) high = mid - 1;
		else low = mid + 1;

	}

	return false;

}

int partition(vector<int> & arr, int low, int high){
	int i = low + 1;
	int j = high;

	int pivot = arr[low];

	while (i <= j){

		if (arr[i] > pivot && arr[j] < pivot){
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

		if (arr[i] <= pivot) ++i;

		if (arr[j] >= pivot) --j;

	}

	arr[low] = arr[j];
	arr[j] = pivot;
	return j;
}

//quick sort
void sort(vector<int> & arr, int low, int high){

	if (low >= high) return;

	int j = partition(arr, low, high);
	sort(arr, low, j-1);
	sort(arr, j+1, high);
}


/**
This function determines if K can be expressed as the sum of four numbers in arr,
multiple use of one number allowed.
*/
bool fourNumbers(const vector<int> & arr, int K){

	//store all possible sum of two numbers
	//a number can be used more than once
	//O(n^2) time; O(n^2) space
	vector<int> sumOfTwo{};
	for (int i = 0; i < arr.size(); ++i){
		for (int j = i; j < arr.size(); ++j){
			sumOfTwo.push_back(arr[i] + arr[j]);
		}
	}

	//Sort the generated array 
	//O(n^2log(n^2)) = O(n^2logn)
	sort(sumOfTwo, 0, sumOfTwo.size()-1);

	//for every sum of two, binary search (K - sum)
	//O(n^2log(n^2)) = O(n^2logn)
	for (int element: sumOfTwo){
		cout << element << " ";
		if (binarySearch(sumOfTwo, (K-element))) return true;
	}
	return false;


}

int main(){

	vector<int> test = {2, 3, 5, 1, 6, 9, 2, 5, 12};
	int K = 14;
	cout << fourNumbers(test, K) << endl;

	cout << fourNumbers(test, 35) << endl;

}