#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "functions.h"

#define SWAP(x, y) { double **temp = x; x = y; y = temp; }
#define BLOCK_LOW(id,p,n) ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)

void *Pth_stencil(void* rank);

void usage(void) {
   printf("USAGE: ./stencil-2d -v <debug> -n <num iter.> -i <infile> -o <outfile> -t <num threads>\n");
   exit(EXIT_SUCCESS);
}

int opt, rows = -1, cols = -1, n, debug, thread_count;
double **A, **B;
pthread_barrier_t barrier;
double compStart, compFinish, compTotal;
int main(int argc, char* argv[]) {
   
   if(argc == 1)
      usage();
   
   int thread;
   char *infile, *outfile;
   FILE *fptr;
   pthread_t* thread_handles;
   double ovStart, ovFinish, ovTotal;
   while((opt = getopt(argc, argv, "v:n:i:o:t:")) != -1){
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
            case 't':
               if(optarg != NULL)
                  thread_count = atoi(optarg);
            break;  
         case '?':
         default:
               usage();

      }   
    } 
   
   //  if ((fptr = fopen (infile, "r")) == NULL){
   //      printf("Error: could not open input file \n");
   //      usage();
   //  }
    GET_TIME(ovStart);
    fptr = fopen(infile, "r");

    fread(&rows, sizeof(int), 1, fptr);
    fread(&cols, sizeof(int), 1, fptr);

    alloc2dnew(&A, rows, cols);
    alloc2dnew(&B, rows, cols);

   if (!(rows < 0 || cols < 0)){

      fread(A[0], sizeof(double), (rows*cols), fptr);
      fclose(fptr);

      createBStart(B, rows, cols);
      if(debug == 2){
      print2d(A, rows, cols);
      }
      //if(thread_count > rows-2)
      //   thread_count--;
 
      if(debug == 1){
	
	long int res = findSize(infile);
        if(res != -1){
		printf("%s has size of %ld bytes \n", infile ,res);
	}
      }
      //printf("1\n");
      pthread_barrier_init(&barrier, NULL, thread_count);
      //printf("2\n");
      thread_handles = malloc(thread_count*sizeof(pthread_t));
      //printf("3\n");

      for (thread = 0; thread < thread_count; thread++)
         pthread_create(&thread_handles[thread], NULL, Pth_stencil, (void*) thread);
      
      //printf("4\n");

      for (thread = 0; thread < thread_count; thread++)
         pthread_join(thread_handles[thread], NULL);
      //printf("5\n");
     pthread_barrier_destroy(&barrier);
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

    fwrite (&rows, sizeof(int), 1, fptr);
    fwrite (&cols, sizeof(int), 1, fptr);
    fwrite (A[0], sizeof(double), rows*cols, fptr);
    fclose (fptr);
    GET_TIME(ovFinish);
    ovTotal = ovFinish - ovStart;
    if(debug == 1){
	long int res = findSize(outfile);
        if(res != -1){
		printf("%s has size of %ld bytes \n", outfile ,res);
	}
    }

    if(debug == 2 || debug == 1){
    printf("Computation time = %e\n", compTotal);
    printf("Overall time = %e\n", ovTotal);
    printf("Other time = %e\n", ovTotal - compTotal);
    }
}

void *Pth_stencil(void* rank) {

   long my_rank = (long) rank;
   int start_row, end_row;
   //double **a = A, **b = B;
   
   //printf("%ld is ready", my_rank);

   start_row = BLOCK_LOW(my_rank, thread_count, rows);
   end_row = BLOCK_HIGH(my_rank,thread_count, rows);
   
    if(my_rank == 0 ){
	    //start_row++;
    }
    if(my_rank == thread_count-1){
	    //end_row--;
    }

   //start_row++;
   //end_row++;
	//printf("Thread Count: %d\n", thread_count);
	//printf("rank %ld, start_row: %d, end_row: %d\n", my_rank, start_row, end_row);
	//pthread_barrier_wait(&barrier);
	int iterations, i, j;
   GET_TIME(compStart);
   for (iterations = 0; iterations < n; iterations++){
      for (i = start_row; i <= end_row; i++){
		//if(i != 0 && i != rows-1){
            for (j = 1; j < cols-1; j++){
		if(i != 0 && i != rows-1){
	//printf("rank %ld, col %d\n", my_rank, j);
		B[i][j] = ( A[i-1][j-1] + A[i-1][j] + A[i-1][j+1] + A[i][j+1] + A[i+1][j+1] + A[i+1][j] + A[i+1][j-1] + A[i][j-1] + A[i][j]  ) / 9.0;
            }
	}
      }
	//printf("%ld waiting: %d\n",my_rank, iterations);
      
   pthread_barrier_wait(&barrier);
	
   if(my_rank == 0){
      //SWAP(A, B);
      double** tmp = A;
      A = B;
      B = tmp;
      if(debug == 2){
      print2d(A, rows, cols);
      	}
      }
   pthread_barrier_wait(&barrier);
   }
   GET_TIME(compFinish);
   compTotal = compFinish - compStart;
   //if(my_rank == 0){
//	if(debug == 2 || debug == 1)
	//printf("Computation time = %e seconds\n", compFinish - compStart);
  // }
    return NULL;
}
