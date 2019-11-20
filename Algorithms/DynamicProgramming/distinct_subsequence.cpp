#include<iostream>
#include<string>
#include<vector>
using namespace std;

/**
this function calculates how many distinct subsequences there are that can be
generated from string1, which is of length n, to be equal to string2
of length m
the final outcome is stored in map[n][m]
*/
void distinctSubsequence(const string & string1, const string & string2, 
							vector<vector<int> > & map){

	int n = string1.length();
	int m = string2.length();
	//map[i][j] stores the distinct subsequence of the first i characters
	//of string1 which equaks the first j characters of string2
	//map[0][0] should be trivially 1
	map[0][0] = 1;
	//map[0][j] is trivially 0 for j > 0 because you cannot have a subsequence of nothing
	//to equal something
	for (int j = 1; j <= m; ++j){
		map[0][j] = 0;
	}
	//map[i][0] is trivially 1 because for any nonempty subsequence, you always can make up
	//a nonstring by just doing nothing
	for (int i = 1; i <= n; ++i){
		map[i][0] = 1;
	}
	//for every other cell, dynamically calculate their value based on values that
	//have been calculated
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= m; ++j){
			//if the last character is the same
			if (string1[i-1] == string2[j-1]){
				map[i][j] = map[i-1][j-1] + map[i-1][j];
			}
			else{
				map[i][j] = map[i-1][j];
			}
		}
	}
}

int main(){
	string word1 = "babgbag";
	string word2 = "bag";
	int n = word1.length();
	int m = word2.length();
	vector<vector<int> > map(n+1, vector<int>(m+1));
	distinctSubsequence(word1, word2, map);
	for (int x = 0; x < map.size(); ++x){
		for (int y = 0; y < map[0].size(); ++y){
			cout << map[x][y] << " ";
		}
		cout << endl;
	}
}