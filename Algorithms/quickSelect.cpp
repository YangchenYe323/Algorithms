#include<iostream>
#include<vector>
using namespace std;

//inverse insertion sort, sort in decreasing order
void insertionSort(vector<int> & arr, int left, int  right){

	for (int i = left + 1; i <= right; ++i){
		int pivot = arr[i];
		int j = i;

		while (j > left && arr[j-1] < pivot){
			arr[j] = arr[j-1];
			--j;
		}

		arr[j] = pivot;

	}

}

//inverse partition
//all value left should be greater than pivot.
//all value right should be smaller
int partition(vector<int> & arr, int left, int right){

	int pivot = arr[left];
	int i = left + 1;
	int j = right;

	while (i <= j){
		if (arr[i] < pivot && arr[j] > pivot){
			int temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		}
		if (arr[i] >= pivot) ++i;
		if (arr[j] <= pivot) --j;
	}

	arr[left] = arr[j];
	arr[j] = pivot;
	return j;


}

void quickSelect(vector<int> & arr, int left, int right, int k){


	if (left + 5 > right){
		insertionSort(arr, left, right);
	}
	else{

		//partition pivot value, left subarray bigger, right subarray smaller
		int j = partition(arr, left, right);

		if (k - 1 < j) quickSelect(arr, left, j-1, k);
		else if (k - 1 > j) quickSelect(arr, j+1, right, k);

	}


}

//select the kth biggst element
int select(vector<int> & arr, int k){

	quickSelect(arr, 0, arr.size()-1, k);

	//no use, for testing purpose only
	for (int element : arr) cout << element << " ";
	cout << endl;

	return arr[k-1];
}


/*int main(){

	vector<int> test = { 872, 234, 481, 765, 123, 789, 642, 
 						880, 314, 284, 159, 731, 623, 712, 
 						527, 358, 372, 467, 417, 538, 813, 
 						514, 659, 537, 942, 649, 735, 478, 
 						714, 835, 253, 646, 174, 385, 138, 
						};

	cout << select(test, 18) << endl;


}*/