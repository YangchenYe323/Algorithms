#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<vector<int> > buildMap(const string & pat, int M){

	vector<vector<int> > dp(M, vector<int>(256, 0));

	dp[0][int(pat[0])] = 1;

	int X = 0;

	for (int j = 1; j < M; ++j){

		for (int c = 0; c <= 255; ++c){

			if (int(pat[j]) == c) dp[j][c] = j + 1;
			else dp[j][c] = dp[X][c];

		}

		X = dp[X][pat[j]];

	}

	return dp;

}


int KMPSearch(const string & txt, const string & pat){

	int M = pat.length();

	vector<vector<int> > dp = buildMap(pat, M);

	int j = 0;

	for (int i = 0; i < txt.length(); ++i){

		j = dp[j][int(txt[i])];

		if (j == M) return i - M + 1;

	}

	return -1;

}

int main(){

	string text = "ababababaaaabbababababababc";

	string pat = "abc";

	cout << KMPSearch(text, pat) << endl;

}



