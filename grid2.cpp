/*
	CSCI 270 Fall 2018
	Programming Assignment
	Name   : Addison Allred
	Email  : aallred@usc.edu	
	USC ID : 6713230073
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//	Feel free to include any other C++ standard library if necessary.

using namespace std;
int memoize(int N, vector<vector<string> > G, vector<vector<int> > I, vector<vector<int> > doubleP, vector<vector<int> > protection){
	if(G[N-1][N-1] == "D"){
		I[N-1][N-1] = 1;
		doubleP[N-1][N-1] = 1;
		protection[N-1][N-1] = 1;
	}
	else if(G[N-1][N-1] == "P"){
		I[N-1][N-1] = 1;
		doubleP[N-1][N-1] = 1;
		protection[N-1][N-1] = 1;
	}
	else if(std::stoi(G[N-1][N-1]) >= 0){
		I[N-1][N-1] = 1;
		doubleP[N-1][N-1] = 1;
		protection[N-1][N-1] = 1;
	}
	else{
		I[N-1][N-1] = (std::stoi(G[N-1][N-1])*-1) + 1;
		doubleP[N-1][N-1] = (std::stoi(G[N-1][N-1])*-1) + 1;
		protection[N-1][N-1] = 1;
	}
	for(int i = N-2; i >= 0; i--){
		int min = I[N-1][i+1];
		if(G[N-1][i] == "D"){
			I[N-1][i] = doubleP[N-1][i+1];
			doubleP[N-1][i] = doubleP[N-1][i+1];
			if(doubleP[N-1][i+1] + (protection[N-1][i+1] - I[N-1][i+1]) <= 0){
				
				protection[N-1][i] = 1;
			}
			else{
				protection[N-1][i] = doubleP[N-1][i+1] + (protection[N-1][i+1] - I[N-1][i+1]);
			}
		}
		else if(G[N-1][i] == "P"){
			I[N-1][i] = protection[N-1][i+1];
			if(protection[N-1][i+1] + (doubleP[N-1][i+1] - I[N-1][i+1]) <= 0){
				doubleP[N-1][i] = 1;
			}
			else{
				doubleP[N-1][i] = protection[N-1][i+1] + (doubleP[N-1][i+1] - I[N-1][i+1]);
			}
			protection[N-1][i] = protection[N-1][i+1];
		}
		else if((min - std::stoi(G[N-1][i])) <= 0){
			I[N-1][i] = 1;
			if(I[N-1][i+1] - std::stoi(G[N-1][i])*2 > 0)
			{
				doubleP[N-1][i] = I[N-1][i+1] - std::stoi(G[N-1][i])*2;
			}
			else{
				doubleP[N-1][i] = 1;
			}

			if(protection[N-1][i+1] - std::stoi(G[N-1][i]) > 0){
				protection[N-1][i] = protection[N-1][i+1] - std::stoi(G[N-1][i]);
			}
			else{
				protection[N-1][i] = 1;
			}
		}
		else{
			I[N-1][i] = min - std::stoi(G[N-1][i]);
			if(std::stoi(G[N-1][i]) < 0){
				if(doubleP[N-1][i+1] - std::stoi(G[N-1][i]) <= 0){
					doubleP[N-1][i] = 1;
				}
				else{
					doubleP[N-1][i] = doubleP[N-1][i+1] - std::stoi(G[N-1][i]);
				}
				protection[N-1][i] = min;
			}
 			else{
				if(I[N-1][i+1] - std::stoi(G[N-1][i])*2 > 0)
				{
					doubleP[N-1][i] = I[N-1][i+1] - std::stoi(G[N-1][i])*2;
				}
				else{
					doubleP[N-1][i] = 1;
				}

				if(protection[N-1][i+1] - std::stoi(G[N-1][i]) >= 0){
					protection[N-1][i] = protection[N-1][i+1] - std::stoi(G[N-1][i]);
				}
				else{
					protection[N-1][i] = 1;
				}
			}
			
		}
	}
	for(int i = N-2; i >= 0; i--){
		int min = I[i+1][N-1];
		if(G[i][N-1] == "D"){
			I[i][N-1] = doubleP[i+1][N-1];
			doubleP[i][N-1] = doubleP[i+1][N-1];
			if(doubleP[i+1][N-1] + (protection[i+1][N-1] - I[i+1][N-1]) <= 0){
				protection[i][N-1] = 1;
			}
			else{
				protection[i][N-1] = doubleP[i+1][N-1] + (protection[i+1][N-1] - I[i+1][N-1]);
			}
		}
		else if(G[i][N-1] == "P"){
			I[i][N-1] = protection[i+1][N-1];
			if(protection[i+1][N-1] + (doubleP[i+1][N-1] - I[i+1][N-1]) <= 0){
				protection[i+1][N-1] = 1;
			}
			else{
				doubleP[i][N-1] = protection[i+1][N-1] + (doubleP[i+1][N-1] - I[i+1][N-1]);
			}
			protection[i][N-1] = protection[i+1][N-1];
		}
	
		else if((min - std::stoi(G[i][N-1])) <= 0){
			I[i][N-1] = 1;
			if(I[i+1][N-1] - std::stoi(G[i][N-1])*2 <= 0){
				doubleP[i][N-1] = 1;
			}
			else{
				doubleP[i][N-1] = I[i+1][N-1] - std::stoi(G[i][N-1])*2;
			}
			if(protection[i+1][N-1] - std::stoi(G[i][N-1]) <= 0){
				protection[i][N-1] = 1;
			}
			else{
				protection[i][N-1] = protection[i][N-1] - std::stoi(G[i][N-1]);
			}
		}
		else{
			I[i][N-1] = min - std::stoi(G[i][N-1]);
			if(std::stoi(G[i][N-1]) < 0){
				if( doubleP[i+1][N-1] - std::stoi(G[i][N-1]) <= 0){
					doubleP[i][N-1] = 1;
				}
				else{
					doubleP[i][N-1] = doubleP[i+1][N-1] - std::stoi(G[i][N-1]);
				}
				protection[i][N-1] = min;
			}
			else{
				if( I[i+1][N-1] - std::stoi(G[i][N-1])*2 <= 0){
					doubleP[i][N-1] = 1;
				}
				else{
					doubleP[i][N-1] = I[i+1][N-1] - std::stoi(G[i][N-1])*2;
				}
				if( protection[i+1][N-1] - std::stoi(G[i][N-1]) <= 0){
					protection[i][N-1] = 1;
				}
				else{
					protection[i][N-1] = protection[i+1][N-1] - std::stoi(G[i][N-1]);
				}
			}
		}
	}
	for(int i = N-2; i >= 0; i--){
		for(int j = N-2; j >= 0; j--){
			int min = std::min(I[i][j+1], I[i+1][j]);
			if(G[i][j] == "D"){
				I[i][j] = std::min(doubleP[i][j+1], doubleP[i+1][j]);
				doubleP[i][j] = std::min(doubleP[i+1][j], doubleP[i][j+1]);
				if(doubleP[i][j+1] + (protection[i][j+1] - I[i][j+1]) > 0 ){
					if(doubleP[i+1][j] + (protection[i+1][j] - I[i+1][j]) > 0 ){
						protection[i][j] = std::min(doubleP[i][j+1] + (protection[i][j+1] - I[i][j+1]), doubleP[i][j+1] + (protection[i][j+1] - I[i][j+1]));
					}
					else{
						protection[i][j] = 1;
					}
				}
				else{
					protection[i][j] = 1;
				}
			}
			else if(G[i][j] == "P"){
				I[i][j] = std::min(protection[i][j+1], protection[i+1][j]);
				if(protection[i+1][j] + (doubleP[i+1][j] - I[i+1][j]) > 0){
					if(protection[i][j+1] + (doubleP[i][j+1] - I[i][j+1]) > 0){
						doubleP[i][j] = std::min(protection[i+1][j] + (doubleP[i+1][j] - I[i+1][j]), protection[i][j+1] + (doubleP[i][j+1] - I[i][j+1]));
					}
					else{
						doubleP[i][j] = 1;
					}
				}
				else{
					doubleP[i][j] = 1;
				}
				protection[i][j] = std::min(protection[i][j+1],protection[i+1][j]);
			}
			else if((min - std::stoi(G[i][j])) <= 0){
				I[i][j] = 1;
				if(doubleP[i+1][j] - (std::stoi(G[i][j])*2) > 0){
					if(doubleP[i][j+1] - (std::stoi(G[i][j])*2) > 0){
						doubleP[i][j] = std::min(I[i+1][j] - (std::stoi(G[i][j])*2), I[i][j+1] - (std::stoi(G[i][j])*2));
					}
					else{
						doubleP[i][j] = 1;
					}
				}
				else{
					doubleP[i][j] = 1;
				}
				if(protection[i+1][j] - std::stoi(G[i][j]) > 0 && protection[i][j+1] - std::stoi(G[i][j]) > 0){
					protection[i][j] = std::min(protection[i+1][j] - std::stoi(G[i][j]), protection[i][j+1] - std::stoi(G[i][j]));
				}
				else{
					protection[i][j] = 1;
				}
			}
			else{
				I[i][j] = min - std::stoi(G[i][j]);
				if(std::stoi(G[i][j]) > 0){
					if(doubleP[i+1][j] - (std::stoi(G[i][j])*2) > 0){
						if(doubleP[i][j+1] - (std::stoi(G[i][j])*2) > 0){
							doubleP[i][j] = std::min(I[i+1][j] - (std::stoi(G[i][j])*2), I[i][j+1] - (std::stoi(G[i][j])*2));
						}
						else{
							doubleP[i][j] = 1;
						}
					}
					else{
						doubleP[i][j] = 1;
					}
					if(protection[i+1][j] - std::stoi(G[i][j]) > 0 && protection[i][j+1] - std::stoi(G[i][j]) > 0){
						protection[i][j] = std::min(protection[i+1][j] - std::stoi(G[i][j]), protection[i][j+1] - std::stoi(G[i][j]));
					}
					else{
						protection[i][j] = 1;
					}
				}
				else{
					protection[i][j] = std::min(I[i+1][j], I[i][j+1]);
					if(doubleP[i+1][j] - std::stoi(G[i][j]) > 0 && doubleP[i][j+1] - std::stoi(G[i][j])){
						doubleP[i][j] = std::min(doubleP[i+1][j] - std::stoi(G[i][j]), doubleP[i][j+1] - std::stoi(G[i][j]));
					}
				}
			}

		}
	}
	return I[0][0];
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
	vector<vector<int> > doubleP;
	vector<vector<int> > protection;
	I.resize(N);
	doubleP.resize(N);
	protection.resize(N);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			I[i].push_back(0);
			doubleP[i].push_back(0);
			protection[i].push_back(0);
		}
	}
	
	int res = memoize(N, G,I, doubleP, protection);
	cout << res << endl;
	
	return 0;
}