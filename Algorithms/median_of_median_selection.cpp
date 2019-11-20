#include "quickSelect.cpp"
using namespace std;

//A median-of-median-of-five algorithm modified on the quick selection algorithm

//overload, partition the given pivotIndex instead of partition the first  
int partition(vector<int> & arr, int left, int right, int pivotIndex){

	int pivot = arr[pivotIndex];
	int i = left, j = right;

	while (i <= j){

		if (arr[i] < pivot && arr[j] > pivot){
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

		if (arr[i] >= pivot) ++i;

		if (arr[j] <= pivot) --j;
	}

	arr[pivotIndex] = arr[j];
	arr[j] = pivot;

	return j;

}

void medianOfFiveSelect(vector<int> & arr, int left, int right){

	//always find the kth largest number
	int k = arr.size() / 2 + 1;

	int n = arr.size();

	//for small arrays, just sort
	if (left + 5 > right){ 
		insertionSort(arr, left, right);
	}
	else{

		//initialize a vector of medians
		vector<int> listOfMedian{};
		//sort every five numbers
		//push the medians into the list
		//this is O(n)
		for (int i = 0; i < n; i += 5){
			if (i + 4 < n) insertionSort(arr, i, i+4);
			listOfMedian.push_back(i + 2);
		}

		//recursively find the median of that list
		medianOfFiveSelect(listOfMedian, 0, listOfMedian.size()-1);
		int pivotIndex = listOfMedian[listOfMedian.size()/2];

		//partition the pivot
		int j = partition(arr, left, right, pivotIndex);

		//decide which route to go
		//either way the size of the array is reduced to about 70%
		if (k-1 < j) medianOfFiveSelect(arr, left, j-1);
		else if (k-1 > j) medianOfFiveSelect(arr, j+1, right);

	}


}


int main(){
	vector<int> test = { 872, 234, 481, 765, 123, 789, 642, 
 						880, 314, 284, 159, 731, 623, 712, 
 						527, 358, 372, 467, 417, 538, 813, 
 						514, 659, 537, 942, 649, 735, 478, 
 						714, 835, 253, 646, 174, 385, 138, 
						};

	medianOfFiveSelect(test, 0, test.size()-1);

	for (int element: test) cout << element << " ";
	cout << endl;
	
	cout << test[test.size()/2];
}

