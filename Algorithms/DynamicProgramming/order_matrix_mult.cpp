#include <iostream>
#include <climits>
#include <vector>
using namespace std;
const int INFINITY = INT_MAX;

void optMatrix(const vector<int>& c, vector<vector<int> >& m, vector<vector<int> >& lastChange){
	int n = c.size()-1;
	for (int left = 1; left <= n; ++left){
		m[left][left] = 0;
	}
	for (int k = 1; k < n; ++k){
		for (int left = 1; left <= n-k; ++left){
			int right = left + k;
			m[left][right] = INFINITY;
			for (int i = left; i < right; ++i){
				int thisCost = m[left][i] + m[i+1][right] + c[left-1] * c[i] * c[right];
				if (thisCost < m[left][right]){
					m[left][right] = thisCost;
					lastChange[left][right] = i;
				}
				
			}	
		}	
	}
}

int main(){
	vector<int> c = { 10, 20, 1, 40, 5, 30, 15 };
	vector<vector<int> > m(7, vector<int>(7));
	vector<vector<int> > lastChange(7, vector<int>(7));
	
	optMatrix(c, m, lastChange);
	
	for (int i = 1; i < m.size(); ++i){
		for (int j = 1; j < m.size(); ++j){
			cout << m[i][j] << " ";
		}
		cout << endl;	
	}
	for (int i = 1; i < lastChange.size(); ++i){
		for (int j = 1; j < lastChange.size(); ++j){
			cout << lastChange[i][j] << " ";
		}
		cout << endl;	
	}
}
