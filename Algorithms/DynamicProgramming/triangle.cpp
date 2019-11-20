#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

int min(const vector<int> & a){
	int min = INT_MAX;
	for (int i: a){
		if (i < min) min = i;
	}
	return min;
}

int optPath(int n, const vector<vector<int> > & triangle){
	vector<int> result(n);
	result[0] = triangle[0][0];  
	/*the number at the top of the triangle, 
	which is trivially the shortest path to the 
	only point of the first level*/
	for (int i = 1; i < n; ++i){
	/*update each number between the first and the last number to be the smaller one 
between itself and its preceding number. This is because the shortest path to any
point in any level involves the shorter path to its predecessor point in the previous 
level from which it can be reached
note: this operation should be done in the reverse order of the array in order not 
to let previous result interfere with following calculation*/
		result[i] = result[i - 1];
		for (int j = i-1; j > 0; --j){
			result[j] = min(result[j], result[j-1]);
		}
		for (int k = 0; k <= i; ++k){
/*add each point's own value
 to the shorter path to each point's 											
 predecessor, which is the shortest 													
 path to that point.*/
			result[k] += triangle[i][k];
		}
	}
	return min(result);/*now result stores the shortest path 		
						to each point in the bottom, which is level 		
						n. Just return the minimal one to be 					
						the shortest path from top to bottom.*/

}

int main(){
	vector<vector<int> > a(4, vector<int>(4));
	a[0][0] = 2; a[1][0] = 3; a[1][1] = 4; a[2][0] = 6;
	a[2][1] = 5; a[2][2] = 7; a[3][0] = 4; a[3][1] = 1;
	a[3][2] = 8; a[3][3] = 3;

	cout << optPath(4, a) << endl;
}