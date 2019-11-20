#include<iostream>
#include<vector>
#include<climits>
using namespace std;

//use dynamic programming to calculate the optimal cost of passing each
//gas station 
void gasStation(const vector<int> & distance, const vector<int> & costs,
				vector<int> & costMap, vector<int> & wayOfStop){

	int n = distance.size();

	//fill in the cost map and way of stopping
	for (int i = 0; i < n; ++i){
		costMap[i] = INT_MAX;
		//base case: can reach those stations in one ride
		if (distance[i] <= 100){
			costMap[i] = costs[i];
			//wayofstop[i] is negative indicating it is the first station
			//to stop. This information will be used to print how we stop
			wayOfStop[i] = -1;
		}
		else{ //recursive case
			for (int j = i-1; j >= 0; --j){

				//update minimum
				if (distance[i] - distance[j] <= 100 && costs[j] < costMap[i]){

					costMap[i] = costMap[j];
					wayOfStop[i] = j;

				}
			}
			costMap[i] += costs[i];
		}
	}

	//for test use only
	/*for (int num : costMap) cout << num << " ";
	cout << endl;
	for (int num : wayOfStop) cout << num << " ";
	cout << endl;*/

}

//recursively print the gas station we have stopped on our route
//to reaching the gas station located at index
void rec_print(const vector<int> & wayOfStop, int index){

	if (wayOfStop[index] == -1){ //this is the first station to stop at
		cout <<"First stop at: "<< index << "th station," << " ";
	}
	else{
		rec_print(wayOfStop, wayOfStop[index]);
		cout << "Then stop at: " << index << "th station, " << " ";
	}

}

//use the calculated dp map to print out the optimal way to go through
//all stations
void printOptimalCostAndWayOfStop(const vector<int> & distance, 
					const vector<int> & costMap, const vector<int> & wayOfStop ){

	int n = costMap.size();

	int optimalCost = INT_MAX;

	int optimalIdex = 0;

	//calculate the minimun cost that can take us to the destination
	for (int i = n-1; i >= 0; --i){
		//the gas stations that are too far from the outlet is not in
		//our concern because that cannot be tha last gas filling
		if (distance[i] + 100 < distance[n-1]) break;

		if (costMap[i] < optimalCost){
			optimalCost = costMap[i];
			optimalIdex = i;
		}

	}

	//print out the optimal cost
	cout << "The optimal cost is: " << optimalCost << endl;

	//print out which gas station to stop by recursively
	rec_print(wayOfStop, optimalIdex);

}

int main(){


	vector<int> distance = {10, 50, 70, 120, 170, 240, 280, 300, 350, 410, 430};
	vector<int> cost = {2, 3, 5, 4, 6, 3, 7, 1, 8, 5, 7};

	vector<int> costMap(distance.size());
	vector<int> wayOfStop(distance.size());

	gasStation(distance, cost, costMap, wayOfStop);

	printOptimalCostAndWayOfStop(distance, costMap, wayOfStop);

}

