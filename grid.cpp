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
int memoize(int N, vector<vector<string> > G, vector<vector<string> >Gpass, vector<vector<int> > I){
	
	I[0][0] = std::stoi(G[0][0]);
	for(int i = 1; i < N; i++){
		int x = std::stoi(G[0][i]);
		int tots = I[0][i-1] + x;
		if(tots < I[0][i-1]){
			I[0][i] = tots;
		}
		else{
			I[0][i] = I[0][i-1];
		}
		G[0][i] = std::to_string(std::stoi(G[0][i-1]) + x);
		
	}
	for(int i = 1; i < N; i++){
		int x = std::stoi(G[i][0]);
		int tots = I[i-1][0] + x;
		if(tots < I[i-1][0]){
			I[i][0] = tots;
		}
		else{
			I[i][0] = I[i-1][0];
		}
		G[i][0] = std::to_string(std::stoi(G[i-1][0]) + x);
		//cout << "this is g at " << i << " " << 0 << G[i][0] << endl;
	}
	for(int i = 1; i < N; i++){
		for(int j = 1; j < N; j++){
			int x = std::stoi(Gpass[i][j]);
			G[i][j] = std::to_string(max(std::stoi(G[i-1][j]) + x, std::stoi(G[i][j-1]) + x));
		}
	}
	for(int i = 1; i < N; i++){
		for(int j = 1; j < N; j++){
			int x = std::stoi(Gpass[i][j]); 
			if(std::stoi(G[i][j]) < 0){
				cout << x + I[i-1][j] << " above " << x + I[i][j-1] << " to right"  << endl;
				I[i][j] = std::max(x + I[i-1][j], x + I[i][j-1]);
			}
			else{
				I[i][j] = std::max(I[i-1][j], I[i][j-1]);
			}
		}
	}
	/*for(int i = 1; i < N; i++){
		for(int j = 1; j < N; j++){
			int x = std::stoi(G[i][j]);
			cout << "This is x " << x << endl;
			
			if(std::stoi(G[i-1][j]) + x > 0 && std::stoi(G[i][j-1]) + x > 0)//handle edge case when it is 0
			{
				if(std::stoi(G[i-1][j]) + x <  std::stoi(G[i][j-1]) + x ){
					I[i][j] = I[i-1][j];
					G[i][j] = std::to_string(std::stoi(G[i-1][j]) + x);
				}
				else{
					I[i][j] = I[i][j-1];
					G[i][j] = std::to_string(std::stoi(G[i][j-1]) + x);
				}
			}
			else if(std::stoi(G[i-1][j]) + x > 0){
				I[i][j] = I[i-1][j];
				G[i][j] = std::to_string(std::stoi(G[i-1][j]) + x);
			}
			else if(std::stoi(G[i][j-1]) + x > 0){
				I[i][j] = I[i][j-1];
				G[i][j] = std::to_string(std::stoi(G[i][j-1]) + x);
			}
			else{
				if(I[i-1][j] + x < I[i][j-1] + x){
					I[i][j] = I[i][j-1] + x;
					G[i][j] = std::to_string(std::stoi(G[i][j-1]) + x);
				}
				else{
					I[i][j] = I[i-1][j] + x;
					G[i][j] = std::to_string(std::stoi(G[i-1][j]) + x);	
				}
			
			}
			
		}
	}*/
	cout << "Matrix G" << endl;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cout << G[i][j] << "   ";
		}
		cout << endl;
	}
	return I[N-1][N-1];
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
			I[i].push_back(1);
		}
	}
	 //int result2 = recursive(N, G, I);
	 //cout << "Result " << result2 << endl;
	int res = memoize(N, G, G, I);
	if(res >= 0){
		cout << "Lives needed = 1" << endl;
	}
	else{
		res = (res*-1) + 1;
		cout << "Lives needed = " << res << endl;
	}
	//cout << solve(N, G) << endl;
	return 0;
}