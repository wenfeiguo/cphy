#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>
double const PI = 3.1415926;

//the usage /*offer help formation*/
void usage(char* program){
	fprintf(stderr, "\nProgram Usage:\n", program);
	fprintf(stderr, "	[-n 1000000]	number of steps per run, default 1000\n");
	fprintf(stderr, "	[-N 100]		number of run times, default 100\n");
	fprintf(stderr, "	[-o output.txt]	the output file, no longer than output.txt,default: output.txt\n");
	fprintf(stderr, "	[-h]			display this information\n");
	fprintf(stderr, "\n");
	exit(1);
}

//function to get system arguments from command lines
int getMyArgs(int argc, char** argv,int* nstep, int* times, char* filename){
	char ch;
	while((ch = getopt(argc,argv,"N:n:o:h"))!= -1){
		switch (ch){
			case 'N' :
			*times = atoi(optarg);break;
			case 'n':
			*nstep = atoi(optarg); break;
			case 'o':
			strcpy(filename,optarg);break;
			case 'h' :
			usage(argv[0]);
			case '?':
			usage(argv[0]);
		}
	}
}

//function to get the distance
float dist(float* site){
	return sqrt(site[0]*site[0]+site[1]*site[1]);/*此处数据类型是float？那么平方会不会溢出，是否有影响？*/
}

//function to output the data
void output(FILE* fp,int istep,float* site){
	fprintf(fp,"%10d %10.2f %10.2f %10.2f\n",istep,site[0], site[1], dist(site));
}

//function to get the step
void getStep(float* step){
	/*get the degree*/
	float deg = rand()/(float)RAND_MAX*2*PI;
	/*get the radius*/
	float r = rand()/(float)RAND_MAX;
	float radius;
	if (r<0.2)
		radius = 0.0;
	else {
		if (r<0.6)
			radius = 0.5;
		else
			radius = 1.0;
	}
	step[0] = radius*cos(deg);
	step[1] = radius*sin(deg);
}

//function to run the step
void runStep(float* site, float* step){
	site[0] += step[0];
	site[1] += step[1];
}
	
int main(int argc, char* argv[]){
	
	//parameters
	int nstep = 1000;
	char filename[30] = "output.txt";
	int times = 100;
	getMyArgs(argc, argv, &nstep, &times, filename);
	
	FILE* fp = fopen(filename, "w");
	
	//walking
	int i;
	for(i=1;i<=times;i++){
		float site[]={0.0,0.0};
		float step[2];
		fprintf(fp,"The program will run for %d times.\n",i);//调用output函数说明这是第几次运行
		output(fp,0,site);
		int j;
		srand((unsigned) (time(NULL)+i));
		for(j=1;j<nstep;j++){
			getStep(step);
			runStep(site,step);
			output(fp,j,site);
		}
	}
	fclose(fp);
	return 0;
}