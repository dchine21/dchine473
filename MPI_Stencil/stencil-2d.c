#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void print2d(double** a, int nrows, int ncols){
	for(int i = 0; i<nrows; i++){
		for(int j = 0; j<ncols; j++){
			printf("%lf ", a[i][j]);
		}	printf("\n");
	}
}

void usage(){
	printf("<usage>: ./stencil-2d -n <num iterations> -i <infile> -o <outfile>\n");
	exit(0);
}


int main(int argc, char* argv[]){
	int c;
	FILE *finptr;
	char* fileIn;
	FILE *foutptr;
	char* fileOut;
	int numRows;
	int numCols;
	double** A;
	double** B;
	int numIter;
	int iters = 0;

	if(argc == 1)
		usage();
	
	while((c = getopt(argc, argv, "n:i:o:")) != -1){
		switch(c){
			case 'n':
				numIter = atoi(optarg);
				break;
			case 'i':
				fileIn = optarg;
				break;
			case 'o':
				fileOut = optarg;
				break;
			case '?':
				default:
					usage();
		}	
	}


	finptr = fopen(fileIn, "r");
	fread(&numRows, sizeof(int), 1, finptr);
	fread(&numCols, sizeof(int), 1, finptr);
	
	
	A = (double**)malloc(numRows*sizeof(double*));
	A[0] = (void*)malloc(numRows*numCols*sizeof(double));

	B = (double**)malloc(numRows*sizeof(double*));
	B[0] = (void*)malloc(numRows*numCols*sizeof(double));

	for(int j = 1; j < numRows; j++){
		A[j] = A[j-1] + numCols;
		B[j] = B[j-1] + numCols;
	}

	fread(A[0], sizeof(double), numRows*numCols, finptr);
	//fread(B[0], sizeof(double), numRows*numCols, finptr);

	//memcpy(B, A, numRows*numCols*sizeof(double));

	fclose(finptr);

	//Create copy of A in B
	for(int i=0; i<numRows; i++){
		for(int j=0; j<numCols; j++){
			B[i][j] = A[i][j];
		}
	}
	printf("Initial: \n");
	print2d(A, numRows, numCols);
	//print2d(B, numRows, numCols);	
	//A[0][0] += 10;	

	//Math for stencil code iterations
	while(iters < numIter){
		printf("LOOP #%d\n", iters);
		for(int i = 1; i < numRows - 1; i++){
			for(int j = 1; j < numCols - 1; j++){
				//printf("Computing cell %d...\n", i+j);
				B[i][j] = (A[i-1][j-1] + A[i-1][j] + A[i-1][j+1] + A[i][j-1] + A[i][j] + A[i][j+1] + A[i+1][j-1] + A[i+1][j] + A[i+1][j+1])/9;
			//printf("B[%d][%d] = %f\n",i,j,B[i][j]);
			}
		}
		print2d(B, numRows, numCols);
		printf("\n");
		//Swap pointers
		double** tmp;
		tmp = A;
		A = B;
		B = tmp;
		iters++;
	}

	

	
	foutptr = fopen(fileOut, "w");
	fwrite (&numRows, sizeof(int), 1, foutptr);
	fwrite (&numCols, sizeof(int), 1, foutptr);
	fwrite (A[0], sizeof(double), numRows*numCols, foutptr);
	fclose (foutptr);


	//Swap pointers
	//double** tmp;
	//tmp = A;
	//A = B;
	//B = tmp;
	




	//print2d(A, numRows, numCols);
	//printf("\n");	
	//print2d(B, numRows, numCols);














}	
