#include<iostream>
#include<vector>
using namespace std;

/*The problem is to determine if a set of numbers can be partitioned into two
subsets whose sum are the same
ex: {1, 3, 5, 7}; 
return: true, {1, 7}; {3, 5}

{1, 2, 3, 5}
return: false
*/

/*
This function returns true if the set can be partitioned into two subset the sums of which are
the same by a dynamic programming algorithm, searching if (sum of whole set)/2 can be reached by
some subset, which is done by the same algorithm implemented before
*/
bool sameSumSubset(const vector<int> set){
	int K = 0;
	for (int element: set)
		K += element;
	//if the sum of the whole array is an odd number, trivially cannot partition
	if (K % 2 == 1) return 0;
	K = K/2;

	int n = set.size();

	//map[i][j] stores if its possible to use the first i element of A to get j,
	//map[n][K] would be the final solution
	vector<vector<int> > map(n+1, vector<int>(K+1));

	//it is trivially possible to get 0 from any subset of A by just taking nothing
	for (int i = 0; i <= n; ++i){
		map[i][0] = 1;
	}

	//it is trivially impossible to get from an empty set anything other than 0
	for (int j = 1; j <= K; ++j){
		map[0][j] = 0;
	}

	//main loop
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= K; ++j){
			if (set[i-1] > j)
				map[i][j] = map[i-1][j];
			else
				map[i][j] = map[i-1][j] | map[i-1][j - set[i-1]];
		}
	}

	return map[n][K];
}

int main(){
	vector<int> set = {1, 3, 5, 7};
	cout << sameSumSubset(set) << endl;

	vector<int> set2 = {2, 4, 6, 7};
	cout << sameSumSubset(set2) << endl;
}