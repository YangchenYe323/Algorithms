#include<iostream>
#include<string>
#include<climits>
#include<map>
#include<vector>
using namespace std;

/**
helper method to find the sigma from start to end
*/
float sigma(int start, int end, const map<int, float> & map){
	if (start > end) return 0;
	float sum = 0.0;
	for (int i = start; i <= end; ++i){
		sum += map.at(i);
	}
	return sum;
}

/**
Use dynamic programming to compute the optimal binary search tree
the optimal average count is stored in m[1][n]
the root of the optimal subtree from i to j is stored in root[i][j],
and can be checked to build up the tree if necessary
*/
void optBinTree(const map<int, float> & map, vector<vector<float> > & m, vector<vector<int> > & root){

	int n = map.size();
	for (int i = 1; i <= n; ++i){
		m[i][i-1] = 0;
	}

	for (int k = 0; k <= n - 1; ++k){
		for (int left = 1; left <= n - k; ++left){
			int right = left + k;
			m[left][right] = 9999999.0;

			for (int i = left; i <= right; ++i){

				float thisCost = m[left][i-1] + m[i+1][right] + sigma(left, right, map);

				if (thisCost < m[left][right]){
					m[left][right] = thisCost;
					root[left][right] = i;
				}
			}
		}
	}

}

int main(){
	map<int, float> words = {
		{1, 0.18},
		{2, 0.19},
		{3, 0.21},
		{4, 0.19},
		{5, 0.23},
	};

	vector<vector<float> > m(7, vector<float>(6));
	vector<vector<int> > root(7, vector<int>(6));

	optBinTree(words, m, root);

	for (int i = 0; i < m.size(); ++i){
		for (int j = 0; j < m.size(); ++j){
			cout << m[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < m.size(); ++i){
		for (int j = 0; j < m.size(); ++j){
			cout << root[i][j] << " ";
		}
		cout << endl;
	}


}