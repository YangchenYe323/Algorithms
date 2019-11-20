#include<iostream>
#include<vector>
using namespace std;

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

/*
This function determines if K can be expressed as the sum of three numbers in arr,
multiple use of one number allowed.
*/
bool threeNumbers( vector<int> & arr, int K){

	//sort the array
	sort(arr, 0, arr.size()-1);

	//maintain two cursors
	int low, high;

	for (int i = 0; i < arr.size(); ++i){
		//initialize to the smallest and the biggest
		low =0;
		high = arr.size()-1;

		//iterate and search
		while (low <= high){

			if (arr[i] + arr[low] + arr[high] == K) return true;
			else if(arr[i] + arr[low] + arr[high] > K) --high;
			else ++low;

		}

	}
	return false;


}

int main(){

	vector<int> test = {2, 3, 5, 1, 6, 9, 2, 5, 12};
	int K = 14;
	cout << threeNumbers(test, K) << endl;

	cout << threeNumbers(test, 6) << endl;

}