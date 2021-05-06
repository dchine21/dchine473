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

	int rank, size;
	//int east_recValue;
	//int west_recValue;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int value[3] = {rank*1, rank*2, rank*3};
	int east_recValue[3];
	int west_recValue[3];
	




	for(int i = 0; i < 3; i++){
		printf("Rank %d, starting value[%d] = %d\n", rank, i, value[i]);
	}
	if(rank == 0){
	//	printf("Starting exchange program\n");
	}
	
	if(size < 2){
		printf("Number of processes must be at least 2. \n");
		return 0;
	}
	
	//value = rank;
	if(rank == 0){
	//	printf("Calling function exchange_values\n");
	}
	printf("1: Process %d has starting value %d \n", rank, value[0]);
	MPI_Status status;
	if(rank % 2 == 0){
		//sendrecv east
		if(rank + 1 != size){		
		//printf("Even numbered process %d, sendrecv with process %d\n", rank, rank+1);
		MPI_Sendrecv(&value[0], 1, MPI_INT, rank+1, 99, east_recValue, 1, MPI_INT, rank+1, 99, MPI_COMM_WORLD, &status);
		//exchange_east(east_recValue, rank, &value[0], size);
		}
		
		//sendrecv west
		if(rank - 1 != -1){
		//printf("Even numbered process %d, sendrecv west\n", rank);
		MPI_Sendrecv(&value[0], 1, MPI_INT, rank-1, 99, west_recValue, 1, MPI_INT, rank-1, 99, MPI_COMM_WORLD, &status);
		//exchange_west(west_recValue, rank, &value[0], size);
		}
	}
	else{
			//sendrecv west
		if(rank - 1 != -1){
		//printf("Odd numbered process %d, sendrecv with process %d \n", rank, rank-1);
		MPI_Sendrecv(&value[0], 1, MPI_INT, rank-1, 99, west_recValue, 1, MPI_INT, rank-1, 99, MPI_COMM_WORLD, &status);
		//exchange_west(west_recValue, rank, &value[0], size);
		}
		//sendrecv east
		if(rank + 1 != size){	
		//printf("Odd numbered process %d, sendrecv east \n", rank);
		MPI_Sendrecv(&value[0], 1, MPI_INT, rank+1, 99, east_recValue, 1, MPI_INT, rank+1, 99, MPI_COMM_WORLD, &status);
		//exchange_east(east_recValue, rank, &value[0], size);
		}
	}






	//exchange_values(east_recValue, west_recValue, rank, value, size);
	
	if(rank == 0){
	//	printf("Starting print process\n");
	}
	if(rank == 0){
			printf("2: Process %d received value %d, %d, %d \n", rank, east_recValue[0], east_recValue[1], east_recValue[2]);
	}
	if(rank == size - 1){
			printf("2: Process %d received value %d, %d, %d \n", rank, west_recValue[0], west_recValue[1], west_recValue[2]);
	}

	if(rank != 0 && rank != size - 1){
		printf("2: Process %d received values %d, %d \n", rank, west_recValue[0], east_recValue[0]);
	}
	
	MPI_Finalize();
	return 0;


}
