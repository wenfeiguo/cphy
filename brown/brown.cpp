#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <fstream>

//#define Kb 1000
double const Kb = 1000.0;
double const Pi = 3.1415926;
//#define T
//#define m
//#define gama

using namespace std;

void usage(char* program){
	fprintf(stderr,"\nProgram Usage:\n", program);
	fprintf(stderr,"	[-T 1000.0]		the temperature,default 5\n");
	fprintf(stderr,"	[-m 1000.0]		the mass, default 1\n");
	fprintf(stderr,"	[-t 1000]		the times ,default 1000\n");
	fprintf(stderr,"	[-y 10.0]		the viscosity, default 1\n");
	fprintf(stderr,"	[-o output.txt] the output file, default: output.txt\n");
	fprintf(stderr,"	[-h]			display this information\n");
	fprintf(stderr,"\n");
	exit(1);
}

void getMyArgs(int argc, char** argv, double* T, double* m, long int* times, float* y, char* filename){
	char ch;
	while((ch = getopt(argc,argv, "T:m:t:y:o:h"))!= -1){
		switch(ch){
			case 'T':
			*T = atoi(optarg); break;
			case 'm':
			*m = atoi(optarg); break;
			case 't':
			*times = atoi(optarg); break;
			case 'y':
			*y = atoi(optarg); break;
			case 'o':
			strcpy(filename,optarg);break;//c++ diferent from c?
			case 'h':
			usage(argv[0]);
			case '?':
			usage(argv[0]);
		}
	}
}

void main(int argc, char* argv[]){
	double T = 5.0;//////////
	double m = 1.0;
	long int times = 1000;
	float y = 1.0;
	char filename[20] = "output.txt";
	float site[2] = {0.0,0.0};
	float sitep[2];
	float v[2]={0.0,0.0} ;//根据文献计算平均速率，赋初值
	float vp[2];
	float dv[2];
	int t = 0;
	ofstream outfile;
	outfile.open(filename);
	//float r = (float)rand()/RAND_MAX;
	double R = 0.0;
	double A = sqrt(2*m*y*Kb*T);
	while(t<times){
		//float r = (float)rand()/RAND_MAX;
		r = t;
		R = exp(-r*r/(2*A*A))/(A*sqrt(2*Pi));
		dv[0] = (-m*y*v[0] + R)/(m*(1+0.5*y));
		dv[1] = (-m*y*v[1] + R)/(m*(1+0.5*y));
		vp[0] = v[0] + dv[0];
		vp[1] = v[1] + dv[1];
		//r+ = r- + v+;
		sitep[0] = site[0] + vp[0];
		sitep[1] = site[1] + vp[1];
		//output();///
		outfile<<site[0]<<"    "<<site[1]<<endl;
		//v- = v+;
		v[0] = vp[0];
		v[1] = vp[1];
		//r- = r+;
		site[0] = sites[0];
		site[1] = sites[1];
		t++;
	}
	