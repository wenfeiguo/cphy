#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<time.h>
double const PI = 3.1415926;
double const k = 1.38065e-23;
double const s = 1e-5;

void usage(char* program){
	fprintf(stderr, "\nProgram Usage:\n", program);
	fprintf(stderr, "	[-n 1000000]	number of steps per run, default 1000\n");
	fprintf(stderr, "	[-N 100]		number of run times, default 100\n");
	fprintf(stderr, "	[-o output.txt]	the output file, no longer than output.txt,default: output.txt\n");
	fprintf(stderr, "	[-T 1000.0]		the temperature,default 293.15\n");
	fprintf(stderr, "	[-h]			display this information\n");
	fprintf(stderr, "\n");
	exit(1);
}
	
//for args
void getMyArgs(int argc, char** argv, int* nstep, int* times,double* T, char* filename){
	char ch;
	while((ch = getopt(argc,argv, "N:n:o:T:h"))!=-1){
		switch(ch){
			case 'N':
			*times = atoi(optarg); break;
			case 'n':
			*nstep = atoi(optarg); break;
			case 'o':
			strcpy(filename,optarg);break;
			case 'T':
			*T = atof(optarg); break;
			case 'h':
			usage(argv[0]);
			case '?':
			usage(argv[0]);
		}
	}
}

void getStep(float* step){
	/*degree*/
	float deg = rand()/(float)RAND_MAX*2*PI;
	step[0] = s*cos(deg);
	step[1] = s*sin(deg);//s = ?
}

//get distance
float dist(float* site){
	return sqrt(site[0]*site[0]+site[1]*site[1]);
}

//get energy
float energy(float d){
	return -0.5*cos(0.5*PI*d)-cos(1.5*PI*d);
}

void getSite(float* site, float* step,double T){
	float temp[2];
	temp[0] = site[0] +step[0];
	temp[1] = site[1] +step[1];
	float deltaE = energy(dist(temp)) - energy(dist(site));
	if(deltaE<=0){
		site[0] = temp[0];
		site[1] = temp[1];
	}
	else {
		if (rand()/(float) RAND_MAX <=exp(-deltaE/(k*T))){
			site[0] = temp[0];
			site[1] = temp[1];
		}
	}
}

void output(FILE* fp, int j, float* site){
	fprintf(fp,"%10d %10.2f %10.2f %10.2f\n", j, site[0], site[1], dist(site));
}
	
//main function
void main(int argc, char* argv[]){
	
	//parameters
	int nstep = 10000;
	int times = 1000;
	double T = 293.15;
	char filename[] = "output.txt";
	getMyArgs(argc,argv,&nstep, &times,&T, filename);
	FILE* fp = fopen(filename,"a");
	
	//walk
	int i;
	for(i = 1;i<= times; i++){
		float site[] = { 0.0, 0.0};
		float step[2];
		fprintf(fp,"The program will run for %d times\n",i);
		int j;
		for(j=1;j<nstep;j++){
			getStep(step);
			getSite(site,step,T);
			output(fp,j,site);
		}
	}
	fclose(fp);
}