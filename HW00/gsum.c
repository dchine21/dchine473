#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "functions.h"

int main(int argc, char *argv[]){

	

	
	int rank, size, value;
	double sum = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if((size & (size - 1)) != 0){
		if(!rank){
		printf("Number of processes must be a power of 2.\nThe program will now exit.\n");
		}
		return 0;
		
	}

	value = rank;

	global_sum(&sum, rank, size, value);
	
	printf("FINAL IN MAIN: Proccess %d has Sum = %f\n", rank, sum);

	MPI_Finalize();
	return 0;

}
