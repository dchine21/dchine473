#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include "functions.h"
void global_sum(double* result, int rank, int size, double my_value){

	int step = 1;
	MPI_Status status;
	int totalSteps = log2(size);

	int mask;
	
	while(step <= totalSteps){
//	my_value += *result;
		mask = (int)(pow(2, (step-1)) + 0.5);
		if(rank < (rank^mask)){
			printf("Phase %d: Process %d is sending %f to Process %d\n", step, rank, my_value, rank^mask);
			MPI_Ssend(&my_value, 1, MPI_DOUBLE_PRECISION, rank^mask, 99, MPI_COMM_WORLD);
			MPI_Recv(result, 1, MPI_DOUBLE_PRECISION, rank^mask, 88, MPI_COMM_WORLD, &status);
			printf("Phase %d: Process %d is receiving from Process %d\n", step, rank, rank^mask);
			
			}
		else{
			MPI_Recv(result, 1, MPI_DOUBLE_PRECISION, rank^mask, 99, MPI_COMM_WORLD, &status);
			printf("Phase %d: Process %d is receiving from Process %d\n", step, rank, rank^mask);
			MPI_Ssend(&my_value, 1, MPI_DOUBLE_PRECISION, rank^mask, 88, MPI_COMM_WORLD);
			printf("Phase %d: Process %d is sending %f to Process %d\n", step, rank, my_value, rank^mask);

			}
			//printf("Result = %f", *result);
			my_value += *result;
			step = step + 1;
		}
		*result = my_value;

}
