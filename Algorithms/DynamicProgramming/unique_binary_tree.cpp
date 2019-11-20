/*
NAME:Yangchen Ye
CS Account id: yyewm
 */

#include<iostream>
#include<vector>
using namespace std;

/**
*this function calculate the number of unique bst with n consecutive nodes
*Using an array m, m[n] stores the number of unique bst with n nodes
*m[0] and m[1] are trivially 1, and all subsequent m[n] can be calculated
*based on m[0] to m[n-1]
*/
int numOfBst(int n){
	vector<int> m(n+1);

	if (n == 1) return 1;

	m[0] = 1;
	m[1] = 1;

	for (int i = 2; i <= n; ++i){
		int Num = 0;
		for (int j = 1; j <= i; ++j){
			Num = Num + m[j - 1] * m[i - j];
		}
		m[i] =  Num;
	}

	return m[n];

}

int main(){

	cout << "please input a number" << endl;
	int n;
	cin >> n;

	cout << "The number of unique binary search tree with " << n << " nodes is " << numOfBst(n) << endl;

}