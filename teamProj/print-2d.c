#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//double* allocate_mem(double*** matrix, int n, int m){
//	*matrix = (double**)malloc(n*sizeof(double*));
//	int *mtx_data = malloc(n*m*sizeof(double));
//	for(int i = 0; i < n; i++){
//	(*matrix)[i] = mtx_data + i * m;
//	}
//	return mtx_data;


//}





void print2d(double** a, int nrows, int ncols){
	for(int i = 0; i<nrows; i++){
		for(int j = 0; j<ncols; j++){
			printf("%lf,", a[i][j]);
		}	printf("\n");
	}


}
void print1d(int* a, int len){
	for(int i = 0; i<len; i++){
		printf("%d,", a[i]);
	}

}

void usage(void){
	printf("<usage>: ./print-2d -m <string #input matrix file> \n");
	exit(0);
	}


int main(int argc, char* argv[]){
int c;
FILE *finptr;
char* fileIn;
int* B = (int*) malloc(2*sizeof(int));
int numRows;
int numCols;
double** matrix;

	if(argc == 1)//No params passed
		usage();
	
	while((c = getopt(argc, argv, "m:")) != -1){
		switch(c){
			case 'm':
				fileIn = optarg;
				break;
			case '?':
				default:
					usage();
		}	
	}



	finptr = fopen(fileIn, "r");
	fread(&numRows, sizeof(int), 1, finptr); //get dimensions of matrix to br printed
	fread(&numCols, sizeof(int), 1, finptr);

	printf("%d, %d \n", numRows, numCols);

	//allocate memory for matrix
	matrix = (double**)malloc(numRows*sizeof(double*)); // row pointers
	matrix[0] = (void *) malloc (numRows*numCols*sizeof(double));
	for(int j = 1; j < numRows; j++){
	matrix[j] = matrix[j-1]+numCols;
	}
	
	
	fread(matrix[0], sizeof(double), numRows*numCols, finptr);	
	fclose(finptr);	

	print2d(matrix, numRows, numCols);	



	//print1d(B, 2);

}
