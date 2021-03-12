#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//double randNum(double lower, double uppeir){
//	double num;
//	unsigned short seed[3] = {6000, 5, 1234};
//	seed[1] = 
//	num = erand48(seed);
//	num = (num * (upper - lower) + lower);	

//	return num;
//}





void usage(void){
	printf("<usage>: ./gen-double-matrix -r <int> -c <int> -l <double> -u <double> -o <string> \n");
	exit(0);
	}

void print2d(double** a, int nrows, int ncols){
	for(int i = 0; i<nrows; i++){
		for(int j = 0; j<ncols; j++){
			printf("%lf, ", a[i][j]);
			} printf("\n");
		}
	}	



int main (int argc, char * argv[]) {
   int i, j;
   int numRows, numCols;
   double lowBd, upBd;
   FILE *foutptr;
   double** a;
 //  double* ptr;
   int c;
   char* fileOut;
   unsigned short seed[3] = {5000, 9500, 1234};
	
	if(argc == 1)//No params passed
		usage();


	while((c = getopt(argc, argv, "r:c:l:u:o:")) != -1){
		switch(c){
			case 'r':
				numRows = atoi(optarg);
				break;
			case 'c':
				numCols = atoi(optarg);
				break;
			case 'l':
				lowBd = atof(optarg);
				break;
			case 'u':
				upBd = atof(optarg);
				break;
			case 'o':
				fileOut = optarg;
				break;
			case '?':
				default:
					usage();
		}

	}

	printf("r = %d, c = %d, l = %f, u = %f, o = %s\n", numRows, numCols, lowBd, upBd, fileOut);
	
   a = (double **) malloc (numRows* sizeof(double*)); //row pointers
   a[0] = (void *) malloc (numRows*numCols*sizeof(double)); //2d array 
   for(j = 1; j < numRows; j++){ //assign mem location to point in block
	a[j] = a[j-1] + numCols;
	}	

//	double someNum = randNum(lowBd, upBd);
//	printf("%lf", someNum);
	//fill matrix
	//*ptr = a;
   for (i = 0; i < numRows; i++) {
      for (j = 0; j < numCols; j++){ 
         double randNum = erand48(seed);
	 randNum = (randNum*(upBd-lowBd)+lowBd);
	 a[i][j] = randNum;
	}
   }

  // print2d(a, numRows, numCols);

   foutptr = fopen(fileOut, "w");
   fwrite (&numRows, sizeof(int), 1, foutptr);
   fwrite (&numCols, sizeof(int), 1, foutptr);
   fwrite (a[0], sizeof(double), numRows*numCols, foutptr);
   fclose (foutptr);
	
//	foutptr = fopen(fileOut, "r");
//	fread(&numRows, sizeof(int), 1, foutptr);
//	printf("%d rows \n", numRows);
//	fread(&numCols, sizeof(int), 1, foutptr);
//	printf("%d cols \n", numCols);
//	fread(a, sizeof(double), numRows*numCols, foutptr);
//	print2d(a, numRows, numCols);
//	fclose(foutptr);

}
