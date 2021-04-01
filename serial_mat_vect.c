

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void usage(void){
	printf("<usage>: ./serial_mat_vect -m <matrix file> -v <vector file> -o <output file> \n");
	exit(0);
}



int main (int argc, char *argv[]){
	double overallSeconds;
	double maxOverallSeconds;
	double otherSeconds;
	double compSeconds;
	int i, j;  //Loop indices
	int numRows; //Rows in matrix
	int numCols; //columns in matrix
	int vecNumRows;
	int vecNumCols;
	double** matrix;
	double** vector;
	double** product;

	int ch;
	char* mtxFile;
	char* vecFile;
	char* outFile;
	FILE *foutptr;
	FILE *finptr;

	if(argc == 1)
		usage();

	while((ch = getopt(argc, argv, "m:v:o:")) != -1){
		switch(ch){
			case 'm':
				mtxFile = optarg;
				break;
			case 'v':
				vecFile = optarg;
				break;
			case 'o':
				outFile = optarg;
				break;
			case '?':
				default:
					usage();
		}
	}
	//malloc space for matrix
	finptr = fopen(mtxFile, "r");
	fread(&numRows, sizeof(int), 1, finptr); //get # rows of mtx
	fread(&numCols, sizeof(int), 1, finptr); //get # cols of mtx
	
	matrix = (double**)malloc(numRows*sizeof(double*));
	matrix[0] = (void *) malloc (numRows*numCols*sizeof(double));
	for(int j = 1; j < numRows; j++){
		matrix[j] = matrix[j-1] + numCols;
	}
	fread(matrix[0], sizeof(double), numRows*numCols, finptr);
	fclose(finptr);
	//Malloc space for vector
	finptr = fopen(vecFile, "r");
	fread(&vecNumRows, sizeof(int), 1, finptr); //get # rows of mtx
	fread(&vecNumCols, sizeof(int), 1, finptr); //get # cols of mtx
	
	vector = (double**)malloc(vecNumRows*sizeof(double*));
	vector[0] = (void *) malloc (vecNumRows*vecNumCols*sizeof(double));
	for(int j = 1; j < vecNumRows; j++){
		vector[j] = vector[j-1] + vecNumCols;
	}
	fread(vector[0], sizeof(double), vecNumRows*vecNumCols, finptr);
	fclose(finptr);
	//Malloc space for product
	product = (double**)malloc(numCols*sizeof(double*));
	product[0] = (void*) malloc (numCols*vecNumCols*sizeof(double));
	for(int j = 1; j < numCols; j++){
		product[j] = product[j-1] + vecNumCols;
	}
	
	//Multiply Matrix * Vector
	for(i = 0; i < numRows; i++){
		product[i] = 0.0;
		for(j = 0; j < numCols; j++){
			product[i] += matrix[i][j] * vector[0][j];
		{

	}

	foutptr = fopen(outFile, "w");
	fwrite(&numCols, sizeof(int), 1, foutptr);
	fwrite(&vecNumCols, sizeof(int), 1, foutptr);
	fwrite((void *) product, sizeof(double), &numCols, foutptr);
	fclose(foutptr);





	return(0);
}


