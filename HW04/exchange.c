#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "functions.h"
#include <unistd.h>
#include <stdlib.h>

void usage(void){
	printf("<usage>: mpirun -np <# of processes> ./exchange ");
	exit(0);
}


int main(int argc, char *argv[]){

	int rank, size, value;
	int east_recValue = 0;
	int west_recValue = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank == 0){
	//	printf("Starting exchange program\n");
	}
	
	if(size < 2){
		printf("Number of processes must be at least 2. \n");
		return 0;
	}

	value = rank;
	if(rank == 0){
	//	printf("Calling function exchange_values\n");
	}
	printf("1: Process %d has starting value %d \n", rank, rank);


	exchange_values(&east_recValue, &west_recValue, rank, size);
	
	if(rank == 0){
	//	printf("Starting print process\n");
	}
	if(rank == 0){
		printf("2: Process %d received value %d \n", rank, east_recValue);
	}
	if(rank == size - 1){
		printf("2: Process %d received value %d \n", rank, west_recValue);
	}

	if(rank != 0 && rank != size - 1){
		printf("2: Process %d received values %d, %d \n", rank, west_recValue, east_recValue);
	}
	
	MPI_Finalize();
	return 0;


}
