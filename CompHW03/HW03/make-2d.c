#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void usage(void){
	printf("<usage>: ./make-2d -r <rows> -c <cols> -o <output file>\n");
	exit(0);
}

int main (int argc, char* argv[]){
	int i, j;
	int numRows, numCols;
	FILE *foutptr;
	double** a;
	int c;
	char* fileOut;
	
	if(argc == 1){
		usage();
	}
	
	while((c = getopt(argc, argv, "r:c:o:")) != -1){
		switch(c){
			case 'r':
				numRows = atoi(optarg);
				break;
			case 'c':
				numCols = atoi(optarg);
				break;
			case 'o':
				fileOut = optarg;
				break;
			case '?':
				default:
					usage();
		}
	}

	printf("r = %d, c = %d, o = %s\n", numRows, numCols, fileOut);
	
	a = (double **) malloc (numRows*sizeof(double*));
	a[0] = (void *) malloc (numRows*numCols*sizeof(double));
	for(j = 1; j < numRows; j++){
		a[j] = a[j-1] + numCols;
		}

		

	//Create initial matrix
	for(i = 0; i < numRows; i++){
		for(j = 0; j < numCols; j++){
			if(j == 0 || j == numCols - 1){
				a[i][j] = 1;
			}
			else{
				a[i][j] = 0;
			}
		}
	}

	foutptr = fopen(fileOut, "w");
	fwrite (&numRows, sizeof(int), 1, foutptr);
	fwrite (&numCols, sizeof(int), 1, foutptr);
	fwrite (a[0], sizeof(double), numRows*numCols, foutptr);
	fclose (foutptr);

	











}
