#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int eggDropTwoEggs(int n){
	vector<int> f(n+1);
	f[0] = 0;
	f[1] = 1;
	if (n < 2) return f[n];
	for (int i = 2; i <= n; ++i){
		f[i] = INT_MAX;
		for (int j = 1; j < n; ++j){
			int thisNum = max(j, 1 + f[i - j]);
			if (thisNum < f[i])
				f[i] = thisNum;
		}
	}
	return f[n];

}

int main(){
	int n = 36;
	cout << eggDropTwoEggs(n) << endl;
}