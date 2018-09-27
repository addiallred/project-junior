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
int memoize(int N, vector<vector<string> > G, vector<vector<int> > I){
	I[0][0] = 2;
	for(int i = 1; i < N; i++){
		int x = std::stoi(G[0][i]);
		cout << x << endl;
		int tots = I[0][i-1] + x;
		cout << tots << endl;
		if(tots < I[0][i-1]){
			I[0][i] = tots;
		}
		else{
			I[0][i] = I[0][i-1];
		}
		
	}
	for(int i = 1; i < N; i++){
		int x = std::stoi(G[i][0]);
		cout << x << endl;
		int tots = I[i-1][0] + x;
		cout << tots << endl;
		if(tots < I[i-1][0]){
			I[i][0] = tots;
		}
		else{
			I[i][0] = I[i-1][0];
		}
		
	}
	for(int i = 1; i < N; i++){
		for(int j = 1; j < N; j++){
			int x = std::stoi(G[i][j]);
			cout << x << " - this is the value at " << i << " " << j << endl;
			if(std::stoi(G[i-1][j]) + x > 0 && std::stoi(G[i][j-1]) + x > 0)//handle edge case when it is 0
			{
				I[i][j] = std::max(I[i-1][j], I[i][j-1]);
			}
			else if(std::stoi(G[i-1][j]) + x > 0){
				I[i][j] = I[i-1][j];
				G[i][j] = std::stoi(G[i-1][j]) + x > 0
			}
			else if(std::stoi(G[i][j-1]) + x > 0){
				I[i][j] = I[i][j-1];
			}
			else{
				int tots = std::max(I[i-1][j] + x, I[i][j-1] + x);
				I[i][j] = tots;
			}
			
		}
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cout << I[i][j] << " - this is the value at " << i << " " << j << endl;
		}
	}
	return I[N-1][N-1];
}
//	You can add any custom classes / helper functions here.
int recursive(int N, vector<vector<string> > G, int x, int i, int j, int result){
	if(j >= N){
		return x;
	}
	if(i >= N){
		return x;
	}
	cout << G[i][j] << endl;
	if(i == N-1 && j == N-1){
		if(x + std::stoi(G[i][j]) < x){
			x = x + std::stoi(G[i][j]);
		}
		cout << "x result: " << x << endl;
		return x;
	}
	else{
		if(x + std::stoi(G[i][j]) < x){
			x = x + std::stoi(G[i][j]);
		}
		int current = recursive(N, G, x, i, j+1, result);
		int next_current = recursive(N, G, x, i+1, j, result);
		int temp = std::min(current, next_current);
		if(temp > x){
			x = temp;
		}
		cout << current << endl;
		cout << next_current << endl;
		cout << "x value for " << i << " " << j << " x: " << x << endl;
		return x;
	}
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
	int result = 1000000;
	int start = std::stoi(G[0][0]);
	vector<vector<int> > I;
	I.resize(N);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			I[i].push_back(1);
		}
	}
	 //int result2 = recursive(N, G, I);
	 //cout << "Result " << result2 << endl;
	 int res = memoize(N, G, I);
	 cout << res << endl;
	//cout << solve(N, G) << endl;
	return 0;
}