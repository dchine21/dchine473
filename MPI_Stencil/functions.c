
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
#include <mpi.h>
long int findSize(char file_name[]){
	FILE* fp = fopen(file_name, "r");

	if (fp == NULL){
	printf("File not found!\n");
	return -1;
	}

	fseek(fp, 0L, SEEK_END);
	
	long int res = ftell(fp);

	fclose(fp);
	
	return res;
}


double** alloc2d(int nrows, int ncols) {
   // first allocate a block of memory for the row pointers
   double **x = (double **)malloc(nrows*sizeof(double *));
   // Now allocate a block of memory for the 2D array
   x[0] = (void *)malloc(nrows*ncols*sizeof(double));
	int j; 
  // Last, assign the memory location to point to in the block of data for each row pointer
   for (j = 1; j < nrows; j++) {
      x[j] = x[j-1] + ncols;
   }
   return x;
}

void alloc2dnew(double*** a, int nrows, int ncols) {
   // first allocate a block of memory for the row pointers
   double **x = (double **)malloc(nrows*sizeof(double *));
   // Now allocate a block of memory for the 2D array
   x[0] = (void *)malloc(nrows*ncols*sizeof(double));
	int j;   
// Last, assign the memory location to point to in the block of data for each row pointer
   for (j = 1; j < nrows; j++) {
      x[j] = x[j-1] + ncols;
   }

   *a = x;
}

void fill2d(double** a, int nrows, int ncols) {
   	int i,j;
    for(i=0; i<nrows; i++) {
        for(j=0; j<ncols; j++) {
            a[i][j] = j+i*ncols;
        }
    }
}

void createBStart(double** b, double** a, int nrows, int ncols) {
	int i,j;
    for(i=0; i<nrows; i++) {
        for(j=0; j<ncols; j++) {
            //if(j == 0 || j == ncols-1)
                b[i][j] = a[i][j];
            //else
               // b[i][j] = 0;
        }
    }
}

void print2d(double** a, int nrows, int ncols) {
	int i,j;
    for(i=0; i<nrows; i++) {
        for(j=0; j<ncols; j++) {
            printf("%.2f\t", a[i][j]);
        } printf("\n");
    }
    printf("\n");
}


void exchange_values(double** east_recValue, double** west_recValue, double** value, int rank, int size, int cols, int my_high){
		MPI_Status status;
	//int** values = &value;
	if(rank % 2 == 0){
		//sendrecv east
		if(rank + 1 != size){	
		//printf("rank %d, size %d\n", rank, size);	
		//printf("Even numbered process %d, sendrecv with process %d\n", rank, rank+1);
		MPI_Sendrecv(value[my_high], cols, MPI_DOUBLE, rank+1, 99, east_recValue[my_high+1], cols, MPI_DOUBLE, rank+1, 99, MPI_COMM_WORLD, &status);
		//printf("Process %d, recv %f\n", rank, east_recValue[my_high+1][0]);
		//exchange_east(east_recValue, rank, &value[0], size);
		}
		MPI_Barrier(MPI_COMM_WORLD);		
		//sendrecv west
		if(rank - 1 != -1){
		//printf("Even numbered process %d, sendrecv west\n", rank);
		MPI_Sendrecv(value[1], cols, MPI_DOUBLE, rank-1, 99, west_recValue[0], cols, MPI_DOUBLE, rank-1, 99, MPI_COMM_WORLD, &status);
		//exchange_west(west_recValue, rank, &value[0], size);
		}
	}
	else{
			//sendrecv west
		if(rank - 1 != -1){
		//rintf("Odd numbered process %d, sendrecv with process %d \n", rank, rank-1);
		//printf("Process %d sending: %f\n", rank, value[1][0]);
		MPI_Sendrecv(value[1], cols, MPI_DOUBLE, rank-1, 99, west_recValue[0], cols, MPI_DOUBLE, rank-1, 99, MPI_COMM_WORLD, &status);
	//	printf("Process %d, recv values, %f, %f, %f from process %d\n", rank, west_recValue[0][0], west_recValue[0][1], west_recValue[0][1], rank-1);
		
	//exchange_west(west_recValue, rank, &value[0], size);
		}
		MPI_Barrier(MPI_COMM_WORLD);
		//sendrecv east
		if(rank + 1 != size){	
		//printf("Odd numbered process %d, sendrecv east with process %d \n", rank, rank+1);
		MPI_Sendrecv(value[my_high], cols, MPI_DOUBLE, rank+1, 99, east_recValue[my_high+1], cols, MPI_DOUBLE, rank+1, 99, MPI_COMM_WORLD, &status);
		//printf("Process %d, recv values, %f, %f, %f from process %d\n", rank, east_recValue[0][0], east_recValue[0][1], east_recValue[0][2], rank+1);
				

		//exchange_east(east_recValue, rank, &value[0], size);
		}
	}

return;
}


