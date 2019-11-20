#include<iostream>
#include<vector>
#include<string>
#include<climits>
#include<math.h>
#include <boost/algorithm/string.hpp>
using namespace std;

/**
helper method to find the cube of extra space after putting to one line the words starting from 
index start to index end;
return INFINITY if those words cannot fit into one line
return 0 if those words can fit into one line and contains the last word
*/
int extraSpace(const vector<int> & arr, int start, int end, int C){
	//count the space needed to hold all the words
	int spaceCost = 0;
	//word's length
	for (int i = start; i <= end; ++i){
		spaceCost += arr[i];
	}
	//the space between all the words
	spaceCost += (end - start);

	//if cannot hold
	if (spaceCost > C)
		return 99999;
	//if the last line
	else if (end == arr.size() - 1)
		return 0;
	else
		return (int)(pow((C - spaceCost), 3));
}

/**
this function uses a dynamic programming algorithm to nicely print all the words
in the vector on the screen.
*/
int optimalPrint(const vector<string> & words, const vector<int> & length, const int C,
					vector<int> & wayOfPrint){
	
	int n = words.size();

	//spaceMap[i] stores the minimal cube of extraspace of printing the first ith words,
	//which is calculated using previous smaller results
	vector<int> spaceMap(n + 1);

	//the extra space left aftr printing 0 word is 0 because not one line
	//is used, so no extra space
	spaceMap[0] = 0;
	//for other cells, find the minimal extraspace based on previous cells
	for (int i = 1; i <= n; ++i){
		spaceMap[i] = INT_MAX;
		for (int j = 0; j < i; ++j){
			//compute the extra space of first print the first j words and print the remaining
			//words in one line, if cannot fit this number would be very large, which is not
			//acceptable
			int thisExraSpace = spaceMap[j] + extraSpace(length, j, i - 1, C);

			//Update the minimal extra space and 
			//the j, which represent the way of printing
			if (thisExraSpace < spaceMap[i]){
				spaceMap[i] = thisExraSpace;
				wayOfPrint[i] = j;
			}
		}
	}

	//after the loop is done, the minimal sum of extra space is stored in spaceMap[n],
	//and the way of printing can be deciphered by looking at the updated wayOfPrint
	//vector, just return the minimal sum
	return spaceMap[n];
}

//now recursively print the words accoridng to the values of j
//first track wayOfPrint[n], j1, which means the printing of the whole paragraph
//is consists of
//printing optimally the first j1 words and the rest as the last line,
//than track wayOfPrint[j1], j2. which means to print the first j1 words, we
//need to first print j2 words and print from j2 to j1-1 on one line
//recursively tracking until we get a 0
int nicePrint(const vector<string> & words, const vector<int> & wayOfPrint, int endPosition){
	if (endPosition == 0)
		return 0;
	int startPosition = nicePrint(words, wayOfPrint, wayOfPrint[endPosition]);
	for (int i = startPosition; i < endPosition; ++i){
		cout << words[i] << " ";
	}
	cout << endl;
	return endPosition;
}

int main(){
	string text = {"Buffy the Vampire Slayer fans are sure to get their fix with the DVD release of the show’s first season. The threedisc collection includes all 12 episodes as well as many extras. There is a collection of interviews by the show’s
creator Joss Whedon in which he explains his inspiration for the show as well as comments on the various cast
members. Much of the same material is covered in more depth with Whedon’s commentary track for the show’s first
two episodes that make up the Buffy the Vampire Slayer pilot. The most interesting points of Whedon’s commentary
come from his explanation of the learning curve he encountered shifting from blockbuster films like Toy Story to a
much lower-budget television series. The first disc also includes a short interview with David Boreanaz who plays
the role of Angel. Other features include the script for the pilot episodes, a trailer, a large photo gallery of publicity
shots and in-depth biographies of Whedon and several of the show’s stars, including Sarah Michelle Gellar, Alyson
Hannigan and Nicholas Brendon.";
	vector<string> results;

	boost::split(results, text, [](char c){return c == ' ';});
	vector<int> length(results.size());
	for (int i = 0; i < results.size(); ++i){
		length[i] = results[i].size();
	}

	int limit = 20;

	vector<int> way(18);

	int minimal = optimalPrint(words, length, limit, way);

	cout << "the minimal cube of extraspace is " << minimal << endl;

	nicePrint(words, way, 17);



}