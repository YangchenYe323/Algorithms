#include<iostream>
#include<vector>
using namespace std;

/**
This function returns true if there exist a subset of A such that the sum of
its elements equals K. it returns false otherwise
*/
bool knapSack2(const vector<int> & A, int K){
	int n = A.size();
	vector<vector<int> > map(n + 1, vector<int>(K + 1));

	//It is trivially true that there is a subset of the first ith subset of A
	//such that its sum of element is 0, just don't take anything and you're done
	for (int i = 0; i <= n; ++i){
		map[i][0] = 1;
	}

	//It is trivially false that an empty set has any subset whose sum of elements
	//is not 0, i.e., from 1 to K
	for (int j = 1; j <= K; ++j){
		map[0][j] = 0;
	}

	//map[i][j] is 1 if it is possible to constitute j with the first i element of set A,
	//the final answer is stored at map[n][K]
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= K; ++j){
			if (A[i-1] > j) /*if the ith element is bigger than the target sum j, than it cannot
							be used to constitute j*/
				map[i][j] = map[i-1][j];
			else
				map[i][j] = map[i-1][j] | map[i-1][j - A[i-1]]; /*bit-wise operation
																implementing an "or"*/
		}
	}

	return map[n][K];
}

int main(){
	vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int K = 58;
	int M = 55
	cout << knapSack2(A, K) << endl;
	cout << knapSack2(A, M) << endl;
}
