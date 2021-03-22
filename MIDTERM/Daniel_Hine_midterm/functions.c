#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "functions.h"

//double get_random(double lowBd, double upBd){
//	srand(time(NULL));
//	return (double)(rand()*(upBd-lowBd) + lowBd);


//}

double compFunction(int funct, double x){
	if(funct == 1){
		return 7.0*(x) + 1;

	}else if(funct == 2){
		return 2.0*(x*x);

	}else{
		return 4.0*(x*x*x);
	}


}

double compIntegral(int funct, double x){
	if(funct == 1){
		return (7.0/2.0)*(x*x) + x;
	}else if(funct == 2){
		return (2.0/3.0)*(x*x*x);
	}else{
		return (x*x*x*x);
	}
	
}
