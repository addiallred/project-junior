/*
	CSCI 270 Fall 2018
	Programming Assignment
	Name   :
	Email  :
	USC ID :
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//	Feel free to include any other C++ standard library if necessary.

using namespace std;
int memoize(int N, vector<vector<string> > G, vector<vector<int> > I, vector<vector<int> > doubleP, vector<vector<int> > protection, vector<vector<int> > dp){
	if(std::stoi(G[N-1][N-1]) >= 0){
		I[N-1][N-1] = 1;
		doubleP[N-1][N-1] = 1;
		dp[N-1][N-1] = 1;
		protection[N-1][N-1] = 1;
	}
	else{
		I[N-1][N-1] = (std::stoi(G[N-1][N-1])*-1) + 1;
		doubleP[N-1][N-1] = 1;
		dp[N-1][N-1] = 1;
		protection[N-1][N-1] = 1;
	}
	for(int i = N-2; i >= 0; i--){
		int min = I[N-1][i+1];
		if((min - std::stoi(G[N-1][i])) <= 0){
			I[N-1][i] = 1;
		}
		else{
			I[N-1][i] = min - std::stoi(G[N-1][i]);
		}
		if(std::stoi(G[N-1][i]) < 0){
			protection[N-1][i] = std::min(I[N-1][i+1], dp[N-1][i+1]);
			dp[N-1][i] = std::min(I[N-1][i+1], dp[N-1][i+1]);
			doubleP[N-1][i] = std::max(1, min - std::stoi(G[N-1][i]));
		}
		else{
			//doubleP[N-1][i] = 
		}
	}
	for(int i = N-2; i >= 0; i--){
		int min = I[i+1][N-1];
		if((min - std::stoi(G[i][N-1])) <= 0){
			I[i][N-1] = 1;
		}
		else{
			I[i][N-1] = min - std::stoi(G[i][N-1]);
		}
	}
	for(int i = N-2; i >= 0; i--){
		for(int j = N-2; j >= 0; j--){
			int min = std::min(I[i][j+1], I[i+1][j]);
			if((min - std::stoi(G[i][j])) <= 0){
				I[i][j] = 1;
			}
			else{
				I[i][j] = min - std::stoi(G[i][j]);
			}
		}
	}
	return I[0][0];
}


int solve(int N, vector<vector<string> > G) {
/*
	Please complete this function.
	N: Number of rows / columns of the grid.
	G: A 2d vector (N*N) indicating the grid.
		G[0][0] is the top left corner
		G[N-1][N-1] is the bottom right corner
	Return: the minimum life Brain needs to complete his task.
*/
	return 0;
}

//	The main function reads the input and outputs your answer.
//	Please do not modify it. (Assume the input is well-formed;
//	You don't need to do any error-check)
int main(int argc, char **argv) {
	int N;
	vector<vector<string> > G;
	cin >> N;
	G.resize(N);
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			string tmp;
			cin >> tmp;
			G[i].push_back(tmp);
		}
	}
	vector<vector<int> > I;
	I.resize(N);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			I[i].push_back(0);
		}
	}
	vector<vector<int> > doubleP;
	I.resize(N);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			I[i].push_back(0);
		}
	}
	vector<vector<int> > protection;
	I.resize(N);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			I[i].push_back(0);
		}
	}
	vector<vector<int> > dp;
	I.resize(N);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			I[i].push_back(0);
		}
	}
	 //int result2 = recursive(N, G, I);
	 //cout << "Result " << result2 << endl;
	int res = memoize(N, G,I, doubleP, protection, dp);
	cout << "Lives needed: " << res << endl;
	//cout << solve(N, G) << endl;
	return 0;
}