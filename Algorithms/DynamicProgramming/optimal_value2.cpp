#include<iostream>
#include<vector>
using namespace std;

void ov2(const vector<int> & weight, const vector<int> & value, int weightLimit, vector<vector<int> > & map){
	
	int n = weight.size();
	for (int i = 0; i <= weightLimit; ++i){
		map[0][i] = 0;
	}
	for (int j = 0; j <= n; ++j){
		map[j][0] = 0;
	}

	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= weightLimit; ++j){
			if (weight[i-1] > j) 
				map[i][j] = map[i-1][j];
			else 
				map[i][j] = max(map[i-1][j], value[i-1] + map[i-1][j-weight[i-1]]);
		}
	}
}

int main(){
	vector<int> w = {1, 5, 3, 4};
	vector<int> v = {15, 10, 9, 5};
	vector<vector<int> > m(5, vector<int>(9));

	ov2(w, v, 8, m);

	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 9; ++j){
			cout << m[i][j] << " ";
		}
		cout << endl;
	}

}