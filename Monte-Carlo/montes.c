#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<time.h>
double const PI = 3.1415926;
double const k = 1.38065e-23;
double const s = 1e-2;
double const huge = 1e10;
double const A = 8e18;//to change the probality to walk

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

void getStep(double* step){
	/*degree*/
	double deg = rand()/(double)RAND_MAX*2*PI;
	step[0] = s*cos(deg);
	step[1] = s*sin(deg);//s = ?
}

//get distance
double dist(double* site){
	return sqrt(site[0]*site[0]+site[1]*site[1]);
}

//get energy
double energy(double d){
	if (d>2.0||d<-2.0)
		return huge;
	else 
		return -0.5*cos(0.5*PI*d)-cos(1.5*PI*d);
}

void getSite(double* site, double* step,double T){
	double temp[2];
	temp[0] = site[0] +step[0];
	temp[1] = site[1] +step[1];
	double deltaE = energy(dist(temp)) - energy(dist(site));
	if(deltaE<=0){
		site[0] = temp[0];
		site[1] = temp[1];
	}
	else {
		double t = rand()/(float)RAND_MAX;
		//printf("%f\n",t);
		if (t<=exp(-deltaE/(A*k*T))){
			site[0] = temp[0];
			site[1] = temp[1];
		}
	}
}

void output(FILE* fp, int j, double* site){
	fprintf(fp,"%10d %10.5f %10.5f %10.5f\n", j, site[0], site[1], dist(site));
}
	
//main function
void main(int argc, char* argv[]){
	
	//parameters
	int nstep = 10000;
	int times = 1000;
	double T = 293.15;
	char filename[] = "output.txt";
	getMyArgs(argc,argv,&nstep, &times,&T, filename);
	FILE* fp = fopen(filename,"w");
	
	//walk
	int i;
	for(i = 1;i<= times; i++){
		double site[] = { 0.0, 0.0};
		double step[2];
		int j;
		srand(time(0)+i);
		for(j=1;j<nstep;j++){
			getStep(step);
			getSite(site,step,T);
		}
			output(fp,i,site);
	}
	fclose(fp);
}