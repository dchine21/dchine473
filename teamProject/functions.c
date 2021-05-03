
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

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
   // Last, assign the memory location to point to in the block of data for each row pointer
   int j;
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
   // Last, assign the memory location to point to in the block of data for each row pointer
   int j;
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

void createBStart(double** b, int nrows, int ncols) {
   int i, j;
    for(i=0; i<nrows; i++) {
        for(j=0; j<ncols; j++) {
            if(j == 0 || j == ncols-1)
                b[i][j] = 1;
            else
                b[i][j] = 0;
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
