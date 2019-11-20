#include<iostream>
#include<vector>
using namespace std;

/*
merge the two given array: {arr[start], ... arr[mid]}, {arr[mid+1],...,arr[end]}
assume two part already sorted
*/
void merge(vector<int> & arr, int start, int mid, int end){

	//size
	int n = end - start + 1;
	vector<int> temp{};

	int leftCursor = start;
	int rightCursor = mid + 1;

	while (leftCursor <= mid || rightCursor <= end){

		if (leftCursor > mid) temp.push_back(arr[rightCursor++]);

		else if (rightCursor > end) temp.push_back(arr[leftCursor++]);

		else if (arr[leftCursor] < arr[rightCursor]) temp.push_back(arr[leftCursor++]);

		else temp.push_back(arr[rightCursor++]);

	}

	for (int i = 0; i < n; ++i){
		arr[start + i] = temp[i];
	}
}

void iterativeMergeSort(vector<int> & arr){

	int n = arr.size();

	int cur_left_size = 1;

	int start;

	//keep track of the size of the left subarray to be merged
	//do not track the size of the whole array and divide by two
	//because might not be evenly divided and might exceed the
	//total size of the array.
	while (cur_left_size < n){
		start = 0;
		while (start < n){
			int mid = min(start + cur_left_size - 1, n-1);
			int end = min(start + 2 * cur_left_size - 1, n - 1);
			merge(arr, start, mid, end);
			start += 2*cur_left_size;
		}

		cur_left_size *= 2;
	}
}

int main(){
	vector<int> arr = {2, 1, 5, 3, 7, 4, 6, 34, 5, 4, 9};
	iterativeMergeSort(arr);

	for (int i : arr){
		cout << i << " ";
	}
}




