#include<iostream>
#include<string>
#include<vector>
#include<climits>
using namespace std;

//Return whether a string is already a palindrome in itself.
bool isPalindrome(string s){ 
	bool flag = true;
	for (int i = 0; i < s.size(); ++i){
		if (s[i] != s[s.size() - i - 1]) flag = false;
	}
	return flag;
}

int palindromePartition(string s){
	int n = s.size();
	/*initialize a 2-d vector of dimension size+1 to store intermediate values
	because the final number of cut shoudl be stored in cell [1][size]*/
	vector<vector<int> > m(n+1, vector<int>(n+1));

	/*The partition needed for a one-character string is trivially 0*/
	for (int i = 1; i <= n; ++i){
		m[i][i] = 0;
	}

	/*k+1 denotes the length of string we're considering, in each loop the local
	optimal number of cut needed to partition a (k+1) length substring of the given string
	starting at left, which ranges from 1 to n-k, 
	is calculated by the given formula and stored for further use*/
	for (int k = 1; k <= n-1; ++k){
		for (int left = 1; left <= n - k; ++left){
			int right = left + k;
			m[left][right] = INT_MAX;

			/*If the substring is a palindrom, skip this loop and set the number to 0*/
			if (isPalindrome(s.substr(left-1, k+1))){
				m[left][right] = 0;
				continue;
			}

			/*calculate the optimal number of cut recursively based on the optimal number of cut
			calculated for smaller substrings*/
			for (int i = left; i < right; ++i){
				int thisCut = m[left][i] + m[i+1][right] + 1;
				if (thisCut < m[left][right]) m[left][right] = thisCut;
			}
		}
	}

	/*now return m[1][n], in which stored the optimal number of cut for a n length substring
	of the given string, which is itself*/
	return m[1][n];
}

int main(){
	string test1 = "wjmmjwyyccyydjyyjdaa";
	string test2 = "wjmmj";
	string test3 = "wjmm";
	string test4 = "wjm";

	cout << "wjmmjwyyccyydjyyjdaa " << palindromePartition(test1) << endl;
	cout << "wjmmj " << palindromePartition(test2) << endl;
	cout << "wjmm " << palindromePartition(test3) << endl;
	cout << "wjm " << palindromePartition(test4) << endl;
}