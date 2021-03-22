#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "functions.h"
#include <time.h>
#include <string.h>
void usage(void){
		printf("<usage>: ./integrate-serial -n <num samples> -a <x start> -b <x end> -f <1,2,3>\n");
		exit(0);
}


int main(int argc, char* argv[]){
	int numSamples;
	double a;
	double b;
	int funct;
	int c;
	double f_a;
	double f_b;
	double estArea;
	double trueArea;
	int underCurve = 0;
	double rectArea;
	unsigned short seed[3] = {5000, 9500, 1235};
	char selFunct[100];
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	if(argc == 1 ){
		usage();
	}
	
	while((c = getopt(argc, argv, "n:a:b:f:")) != -1){
		switch(c){
			case 'n':
				numSamples = atoi(optarg);
				break;
			case 'a':
				a = atof(optarg);
				break;
			case 'b':
				b = atof(optarg);
				break;
			case 'f':
				funct = atoi(optarg);
				break;
			case '?':
				default:
					usage();
		}
	
	}
//	printf("n = %d, a = %f, b = %f, f = %d\n",numSamples,a,b,funct);

	if(a < 0 || b < 0){
	printf("Both a and b must be greater than 0.\n");
	usage();
	}
	if(b <= a){
	printf("Variable b must be strictly greater than a.\n");
	usage();
	}
	if(!(funct == 1 || funct == 2 || funct == 3)){
	printf("Variable f must be either 1,2, or 3.\n");
	usage();
	}
	if(funct == 1){
		strcpy(selFunct,"7x + 1");
	}else if(funct == 2){
		strcpy(selFunct,"2x^2");
	}else{
		strcpy(selFunct,"4x^3");
	}
	

	printf("Estimating integral of %s from %f to %f for %d samples.\n", selFunct,a,b, numSamples);	
	f_a = compFunction(funct, a);
	f_b = compFunction(funct, b);
//	printf("f_a = %f\n", f_a);
//	printf("f_b = %f \n", f_b);
	double f_int_a = compIntegral(funct, a);
	double f_int_b = compIntegral(funct, b);
	trueArea = f_int_b - f_int_a;
	rectArea = (f_b *(b-a));
	
	for(int i = 0; i < numSamples; i++){

		double randX = erand48(seed);
		randX = (randX*(b-a) + a);
		double randY = erand48(seed);
		randY = (randY*(f_b)); 
	//	printf("randX = %f, randY = %f\n", randX, randY);	
		if(randY < compFunction(funct, randX)){
			underCurve++;
		//	printf("Point was under the curve, incremented.\n");
		}
	}
//	printf("Points under curve = %d\n", underCurve);
	estArea = ((underCurve*rectArea) / (double) numSamples);
	printf("Estimated Integral = %f\n", estArea);
	printf("True Integral = %f\n", trueArea);
	end = clock();
	cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC;
	printf("Total runtime: %f\n", cpu_time_used);
}
