#include <stdio.h>
#include<stdlib.h>

int gcd(int a, int b){
    int t;
	while(b){
		t=a%b;
		a=b;
		b=t;
	}
	return a;
}

int main(){
	int a, b;
	scanf("%d%d",&a,&b);
	printf("The GCD of [%d] and [%d] is : %d\n",a,b,gcd(a,b));
}