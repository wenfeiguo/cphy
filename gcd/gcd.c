#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(char* program){
	fprintf(stderr, "\nProgram Usage:\n", program);
	fprintf(stderr, "	[-a 10000000]	value of a, default 22\n");
	fprintf(stderr, "	[-b 10000000]	value of b, default 33\n");
	fprintf(stderr, "	[-h]			display this information\n");
	fprintf(stderr, "\n");
	exit(1);
}

int getMyArgs(int argc, char** argv,int* a, int* b){
	char ch;
	while((ch = getopt(argc,argv,"a:b:h"))!= -1){
		switch (ch){
			case 'a':
			*a = atoi(optarg); break;
			case 'b':
			*b = atoi(optarg); break;
			case 'h':
			usage(argv[0]);
			case '?':
			usage(argv[0]);
		}
	}
}

int gcd(int a ,int b){
	while(a!=b){
		if (a > b)
			a=a-b;
		else 
			b=b-a;
	}
	return a;
}

int main(int argc,char* argv[]){
	int a = 22;
	int b = 33;
	getMyArgs(argc,argv,&a,&b);
	printf("The GCD of [%d] and [%d] is : %d\n",a,b,gcd(a,b));
	return 1;
}