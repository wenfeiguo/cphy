#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define L 100
#define sp 1
#define T 10
#define epsilon 1.0

using namespace std;

void initial(int Spins[L][L]){
	for(int i=0;i<L;i++){
		for(int j=0;j<L; j++){
			if(rand()%2){
				Spins[i][j] = sp;
			}
			else{
				Spins[i][j] = -sp;
			}
		}
	}
}

double delta_E(int i,int j,int Spins[L][L]){
	int up, down, left, right;
	if(j+1>L-1)
		up = Spins[i][j+1-L];
	else
		up = Spins[i][j+1];
	if(j-1<0)
		down = Spins[i][j-1+L];
	else
		down = Spins[i][j-1];
	if(i-1<0)
		left = Spins[i-1+L][j];
	else
		left = Spins[i-1][j];
	if(i+1>L-1)
		right = Spins[i+1-L][j];
	else
		right = Spins[i+1][j];
	double s = up + down + left + right;
	/*double Ee = 0.5*epsilon*s*Spins[i][j];
	double Ei = -0.5*epsilon*s*Spins[i][j];
	*/
	double e = epsilon*s*Spins[i][j];
	return e;//Ee - Ei;
}

void run(int i, int j, int Spins[L][L]){
	double e =delta_E(i,j,Spins);
	double p = rand()/(double)RAND_MAX;
	if(e<0)
		Spins[i][j] = -Spins[i][j];
	else{
		if(p<exp(-e/T))
			Spins[i][j] = -Spins[i][j];
	}
}

int sum(int Spins[L][L]){
	int s = 0;
	for(int i =0;i<L;i++){
		for(int j =0; j<L;j++){
			s = s+Spins[i][j];
		}
	}
	return s;
}

int main(){
	int Spins[L][L];
	double Energy;
	int Sums;
	int times = 10000000;
	int n = 0;
	
	srand((unsigned)time(NULL));
	initial(Spins);
	
	while(n<times){
		int i = rand()%100;
		int j = rand()%100;
		
		run(i,j,Spins);//include delta_E
		
		if(n%1000000==0)
			cout<<sum(Spins)<<endl;
		
		n++;
	}