#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int round(int x){
	int result = (x < 0)? 0: x;
	return result;
}

float ov(const vector<int> & weight, const vector<float> & value, int limit){
	vector<float> result = vector<float>(limit + 1);
	result[0] = 0;
	for (int i = 1; i <= limit; ++i){
		result[i] = INT_MIN;
		for (int j = 0; j < weight.size(); ++j){
			float thisValue;
			if (i < weight[j]) thisValue = 0;
			else thisValue = result[i - weight[j]] + value[j];

			if (thisValue > result[i]) result[i] = thisValue;
		}
	}
	return result[limit];

}

int main(){
	vector<int> weight = {2, 3, 1, 6, 4, 9, 8};
	vector<float> value = {10.34, 12.45, 2.24, 20.01, 15.89, 25.23, 30};

	int i;
	cout << "enter a limit of weight" << endl;
	cin >> i;

	cout << "the most value that can be produced is " << ov(weight, value, i) << endl; 

}