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

void exchange_values(int* east_recValue, int* west_recValue, int rank, int size){
	MPI_Status status;
	if(rank % 2 == 0){
		//sendrecv east
		if(rank + 1 != size){		
		//printf("Even numbered process %d, sendrecv with process %d\n", rank, rank+1);
		MPI_Sendrecv(&rank, 1, MPI_INT, rank+1, 99, east_recValue, 1, MPI_INT, rank+1, 99, MPI_COMM_WORLD, &status);
		}
		
		//sendrecv west
		if(rank - 1 != -1){
		//printf("Even numbered process %d, sendrecv west\n", rank);
		MPI_Sendrecv(&rank, 1, MPI_INT, rank-1, 99, west_recValue, 1, MPI_INT, rank-1, 99, MPI_COMM_WORLD, &status);
		}
	}
	else{
			//sendrecv west
		if(rank - 1 != -1){
		//printf("Odd numbered process %d, sendrecv with process %d \n", rank, rank-1);
		MPI_Sendrecv(&rank, 1, MPI_INT, rank-1, 99, west_recValue, 1, MPI_INT, rank-1, 99, MPI_COMM_WORLD, &status);
		}
		//sendrecv east
		if(rank + 1 != size){	
		//printf("Odd numbered process %d, sendrecv east \n", rank);
		MPI_Sendrecv(&rank, 1, MPI_INT, rank+1, 99, east_recValue, 1, MPI_INT, rank+1, 99, MPI_COMM_WORLD, &status);
		}
	}

	return;
}




//unused
void exchange_east(int* east_recValue, int rank, int size){
	MPI_Status status;
	printf("Process %d starting sendrecv east\n", rank);
	if(rank + 1 != size){
		MPI_Sendrecv(&rank, 1, MPI_INT, rank+1, 99, east_recValue, 1, MPI_INT, rank+1, 99, MPI_COMM_WORLD, &status);
	}
	printf("Process %d received %d from %d \n", rank, *east_recValue, rank+1);
	return;
}

void exchange_west(int* west_recValue, int rank, int size){
	MPI_Status status;
	printf("Process %d starting sendrecv west\n", rank);
	if(rank - 1 != -1){
		MPI_Sendrecv(&rank, 1, MPI_INT, rank-1, 88, west_recValue, 1, MPI_INT, rank-1, 88, MPI_COMM_WORLD, &status);
	}
	return;
}





















