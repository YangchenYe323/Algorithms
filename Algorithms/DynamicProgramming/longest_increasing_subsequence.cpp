#include<iostream>
#include<vector>
#include<climits>
using namespace std;

/**
This function calculates the longest increasing subsequence of the given array
using dynamic programming
*/
int longestIncreasingSubsequence(const vector<int> & arr){

	int n = arr.size();

	//dp[i] stores the longest increasing subsequence ending at arr[i]
	vector<int> dp(n);

	dp[0] = 1;

	//the final result to be updated during the loop
	int longest = dp[0];

	//main loop
	for (int i = 1; i < n; ++i){
		//if everything before i is bigger than it, than its
		//longest subsequence ending at i is triviallly 1
		dp[i] = 1;

		//calculating dp[i] based on dp[0] ... dp[i-1]
		for (int j = 0; j < i; ++j){
			if (arr[j] < arr[i]){
				int thisLength = dp[j] + 1;
				if (thisLength > dp[i]) dp[i] = thisLength;
			}
		}

		//update global maximun after each local maximun is calculated
		if (dp[i] > longest) longest = dp[i];

	}

	//return global maximun
	return longest;

}


int main(){
	vector<int> test1 = {3, 10, 2, 1, 20};

	cout << longestIncreasingSubsequence(test1) << endl;

	vector<int> test2 = {3, 2};

	cout << longestIncreasingSubsequence(test2) << endl;

	vector<int> test3 = {10, 22, 9, 33, 21, 50, 41, 60, 80};

	cout << longestIncreasingSubsequence(test3) << endl;


}


