#include <iostream>
#include<fstream>
#include <vector>
#include <cstring>
using namespace std;

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */


/* The following is a recursive implementation of LCS, 
which is not effieicnt. Your job is to implement it using 
dynamic programming. 

You only need to change the following function in this assignment. 
Name: Yangchen Ye
Lab id: yyewm
 */

int lcs( string &X, string &Y, int m, int n )  
{  	
	//map[i][j] stores the length of longest common subsequence
	//of the first i characters of string X and j characters of string Y

	//either i or j is 0 would make map[i][j] 0;
    vector<vector<int> > map(m+1, vector<int>(n+1));
    for (int i = 0; i <= m; ++i){
      map[i][0] = 0;
    }
    for (int i = 0; i <= n; ++i){
      map[0][i] = 0;
    }

    for (int i = 1; i <= m; ++i){
      for (int j = 1; j <= n; ++j){
      	//if the ith of X and jth of Y are the same character
        if (X[i-1] == Y[j-1])
          map[i][j] = map[i-1][j-1] + 1;
        else
          map[i][j] = max(map[i-1][j], map[i][j-1]);
      }
    }
    return map[m][n];
} 


int main()
{
  int a,b;
  string A, B;
  ifstream dataFile;


  // READING STRINGSS FROM A FILE
  dataFile.open("lcs.txt"); 

  if (dataFile.is_open()) { //if the file is open
    // next read the first line to A and econd line to B
    dataFile>>A;
    dataFile>>B; 
  }

  dataFile.close(); 

  cout<<"The two sequences are:\n"<<A<<"\n"<<B<<"\n"<<"\n";
  //cout<<"The string lengths are: "<<A.length()<<" and "<<B.length()<<"\n";
  a=A.length();
  b=B.length();

  cout<<"The length of the longest common subsequence is "<<lcs(A,B,a,b)<<"\n";

  return 0;
}