#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mpi.h>
#include "functions.h"

#define SWAP(x, y) { double **temp = x; x = y; y = temp; }
#define BLOCK_LOW(id,p,n) (((id)*(n))/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)

void *MPI_stencil(int rank, int size);

void usage(void) {
   printf("USAGE: mpirun -np <# of processes> ./mpi-stencil-2d -v <debug> -n <num iter.> -i <infile> -o <outfile>\n");
   exit(EXIT_SUCCESS);
}

int opt, rows, cols, n, debug, my_rows;
double **A, **B, **FIN;
double compStart, compFinish, compTotal;
int my_startRow, my_lastRow, my_Rows;
int main(int argc, char* argv[]) {
   
   if(argc == 1)
      usage();
   
   int rank, size;
   char *infile, *outfile;
   FILE *fptr;
   double ovStart, ovFinish, ovTotal;
   while((opt = getopt(argc, argv, "v:n:i:o:")) != -1){
      switch(opt){  
         
         case 'v':
               if(optarg != NULL)
                  debug = atoi(optarg);
            break;  
         case 'n':
               if(optarg != NULL)
                  n = atoi(optarg);
            break;  
         case 'i':
               if(optarg != NULL){
                  
                  infile = malloc(strlen(optarg)+1);
                  
                  if(infile != NULL)
                     strcpy(infile,optarg);
                  else{
                      printf("Error: could not malloc space for input filename.");
                      exit(EXIT_FAILURE);
                  }
                    
               } 
            break;    
         case 'o': 
               if(optarg != NULL){
                  
                  outfile = malloc(strlen(optarg)+1);
                  
                  if(outfile != NULL)
                     strcpy(outfile,optarg);
                  else{
                      printf("Error: could not malloc space for output filename.");
                      exit(EXIT_FAILURE);
                  }
                    
               } 
            break;
         case '?':
         default:
               usage();

      }   
    } 
   GET_TIME(ovStart);
   if ((fptr = fopen (infile, "r")) == NULL){
         printf("Error: could not open input file \n");
         usage();
     }
    
    fptr = fopen(infile, "r");

    fread(&rows, sizeof(int), 1, fptr);
    fread(&cols, sizeof(int), 1, fptr);
    
    fclose(fptr);
    alloc2dnew(&FIN, rows, cols);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//fptr = fopen(infile, "r");
	my_startRow = BLOCK_LOW(rank, size, rows);
	my_lastRow = BLOCK_HIGH(rank, size, rows);
	my_rows = BLOCK_SIZE(rank, size, rows);
	
	//printf("Process %d: start = %d, last = %d, number %d\n",rank, my_startRow, my_lastRow, my_rows);
	

	//alloc use cases
	//if(rank == 0 || rank == size-1){
	//	alloc2dnew(&A, my_rows+1, cols);
	//	alloc2dnew(&B, my_rows+1, cols);
	//}else{
    	alloc2dnew(&A, my_rows+2, cols);
    	alloc2dnew(&B, my_rows+2, cols);
	//}
	fptr = fopen(infile, "r");
	fseek(fptr, ((my_startRow*cols*8))+8, SEEK_SET);
	long int res = ftell(fptr);
	//printf("process %d starting at %d bytes\n", rank, res);	
	//fclose(fptr);
	MPI_Barrier(MPI_COMM_WORLD);


   if (!(rows < 0 || cols < 0)){
	//if(rank > 0){
      fread(A[1], sizeof(double), (my_rows*cols), fptr);
      fclose(fptr);
	//printf("process %d read file\n", rank);
	//}
	//else{
	//fread(A[0], sizeof(double), (my_rows*cols), fptr);
	//fclose(fptr);
	//}
	//MPI_Barrier(MPI_COMM_WORLD);
      createBStart(B, A, my_rows+2, cols);
	//MPI_Barrier(MPI_COMM_WORLD);
      //if(debug == 2){
	//if(rank == 2)
      //print2d(A, my_rows+2, cols);
      //}

	//MPI_Barrier(MPI_COMM_WORLD);
      //if(thread_count > rows-2)
      //   thread_count--;
 
      if(debug == 1){
	if(rank == 0){
	long int res = findSize(infile);
        if(res != -1){
		printf("%s has size of %ld bytes \n", infile ,res);
		}
      	}	
	}      
      
	
	//printf("1\n");
      //printf("2\n");
      //printf("3\n");
	//if(rank == 0){
	//printf("rank %d, recv: %f, into lastRow: %d\n", rank, A[my_lastRow+2][0], my_lastRow);
	//}
	MPI_Barrier(MPI_COMM_WORLD);
	//exchange_values(A, A, A, rank, size, cols, my_rows);

	//printf("prep exchange\n");
	//	if(rank == 2){
		//printf("rank %d, recv %f: \n",rank, A[my_lastRow+2][0]);

	//	print2d(A, my_rows+2, cols);
	//}
        MPI_stencil(rank, size);  
      //printf("4\n");
	MPI_Gather(A[1], my_rows*cols, MPI_DOUBLE, FIN[0], my_rows*cols, MPI_DOUBLE,  0, MPI_COMM_WORLD);	
      //printf("5\n");
        if(rank == 0 && debug == 2){
	print2d(FIN, rows, cols);
	}
     
      	//MPI_Finalize();
	//print2d(FIN, rows, cols);
	//printf("6\n");
  }else{

      fclose(fptr);
      printf("Error: rows and columns could not be read from input file");
      usage();

   }

   if((fptr = fopen(outfile,"w")) == NULL){
      printf("Error: could not open output file \n");
      usage();
   }
    if(rank == 0){
    fwrite (&rows, sizeof(int), 1, fptr);
    fwrite (&cols, sizeof(int), 1, fptr);
    fwrite (FIN[0], sizeof(double), rows*cols, fptr);
    fclose (fptr);
    GET_TIME(ovFinish);
    ovTotal = ovFinish - ovStart;
    if(debug == 1 && rank == 0){
	long int res = findSize(outfile);
        if(res != -1){
		printf("%s has size of %ld bytes \n", outfile ,res);
	}
    }
	}
    if(rank == 0){
   	 if(debug == 2 || debug == 1){
    	printf("Computation time = %e\n", compTotal);
    	printf("Overall time = %e\n", ovTotal);
    	printf("Other time = %e\n", ovTotal - compTotal);
    	}
    }
	MPI_Finalize();
}

void *MPI_stencil(int rank, int size) {
  
   rank = rank;
   size = size;
   int start_row, end_row;
   //double **a = A, **b = B;
   start_row = my_startRow;
   end_row = my_lastRow;
   //printf("%ld is ready", my_rank);

   GET_TIME(compStart);
   exchange_values(A, A, A, rank, size, cols, my_rows);

   //exchange_values(B, B, B, rank, size, cols, my_rows);
	int iterations,i,j;
   for (iterations = 0; iterations < n; iterations++){
	MPI_Barrier(MPI_COMM_WORLD);
	
	exchange_values(A, A, A, rank, size, cols, my_rows);
		
	MPI_Barrier(MPI_COMM_WORLD);
      for ( i = 1; i <= my_rows; i++){
      	for ( j = 1; j < cols-1; j++){	
		if(i != 0 && !(end_row == rows-1 && i == my_rows)  && rank+i != 1){
		B[i][j] = ( A[i-1][j-1] + A[i-1][j] + A[i-1][j+1] + A[i][j+1] + A[i+1][j+1] + A[i+1][j] + A[i+1][j-1] + A[i][j-1] + A[i][j]  ) / 9.0;
            }
	}
      }

   MPI_Barrier(MPI_COMM_WORLD);
   //SWAP(A,B);
      
      double** tmp = A;
      A = B;
      B = tmp;
      if(debug == 2){
	MPI_Gather(tmp[1], my_rows*cols, MPI_DOUBLE, FIN[0], my_rows*cols, MPI_DOUBLE,  0, MPI_COMM_WORLD);	
     	if(rank == 0){
	print2d(FIN, rows, cols);
	}
      	}
      
   //exchange_values(A, A, A, rank, size, cols, my_rows);
   MPI_Barrier(MPI_COMM_WORLD);
   }
   GET_TIME(compFinish);
   compTotal = compFinish - compStart;
   
    return NULL;
}

