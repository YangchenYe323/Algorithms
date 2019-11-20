#include<iostream>
#include<vector>
#include<string>
using namespace std;

void longestSubsequence(const string & a, const string & b, vector<vector<int> > & map){
	int m = a.size();
	int n = b.size();

	for (int i = 0; i <= m; ++i){
		map[i][0] = 0;
	}
	for (int i = 0; i <= n; ++i){
		map[0][i] = 0;
	}

	for (int i = 1; i <= m; ++i){
		for (int j = 1; j <= n; ++j){
			if (a[i-1] == b[j-1])
				map[i][j] = 1 + map[i-1][j-1];
			else
				map[i][j] = max(map[i-1][j], map[i][j-1]);
		}
	}
}

int main(){
	string a = "abcdefg";
	string b = "aacofgwa";
	vector<vector<int> > map(a.size()+1, vector<int>(b.size()+1));
	longestSubsequence(a, b, map);
	for (int i = 0; i < a.size()+1; ++i){
		for (int j = 0; j < b.size()+1; ++j){
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}