
/*   Matrix-vector multiplication, Version 1
 *
 *   This program multiplies a matrix and a vector input from
 *   separate files. The result vector is printed to standard
 *   output.
 *
 *   Data distribution of matrix: rowwise block striped
 *   Data distribution of vector: replicated 
 *
 *   Programmed by Michael J. Quinn
 *
 *   Last modification: 9 September 2002
 */

#include <stdio.h>
#include <mpi.h>
#include "MyMPI.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Change these two definitions when the matrix and vector
   element types change */

typedef double dtype;
#define mpitype MPI_DOUBLE


void usage(void){
	printf("<usage>: ./mv1 -m <matrix file> -v <vector file> -o <output file> \n");
	exit(0);

}




int main (int argc, char *argv[]) {
   dtype **a;       /* First factor, a matrix */
   dtype **b;        /* Second factor, a vector */
   dtype *c_block;  /* Partial product vector */
   dtype *c;        /* Replicated product vector */
   double    max_seconds;
   double    seconds;    /* Elapsed time for matrix-vector multiply */
   dtype *storage;  /* Matrix elements stored here */
   int    i, j;     /* Loop indices */
   int    id;       /* Process ID number */
   int    m;        /* Rows in matrix */
   int    n;        /* Columns in matrix */
   int    nprime;   /* Elements in vector */
   int    p;        /* Number of processes */
   int    rows;     /* Number of rows on this process */
   int    its;
   int ch;
   char* mtxFile;
   char* vecFile;
   char* outFile;
   int vecN;
   int vecM;
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




   MPI_Init (&argc, &argv);
   MPI_Comm_rank (MPI_COMM_WORLD, &id);
   MPI_Comm_size (MPI_COMM_WORLD, &p);

   read_row_striped_matrix (mtxFile, (void *) &a,
      (void *) &storage, mpitype, &m, &n, MPI_COMM_WORLD);
   rows = BLOCK_SIZE(id,p,m);
   print_row_striped_matrix ((void **) a, mpitype, m, n,
      MPI_COMM_WORLD);

   //read_replicated_vector (vecFile, (void *) &b, mpitype,
     // &nprime, MPI_COMM_WORLD);
   //print_replicated_vector (b, mpitype, nprime,
     // MPI_COMM_WORLD);
  read_row_striped_matrix (vecFile, (void *) &b, 
	(void *) &storage, mpitype, &vecM, &vecN, MPI_COMM_WORLD);
  print_row_striped_matrix ((void **) b, mpitype, vecM, vecN, MPI_COMM_WORLD);

   printf("%d, %d \n" , rows, n);
   c_block = (dtype *) malloc (rows * sizeof(dtype));
   c = (dtype *) malloc (n * sizeof(dtype));
   MPI_Barrier (MPI_COMM_WORLD);
   seconds = - MPI_Wtime();
   for (i = 0; i < rows; i++) {
      c_block[i] = 0.0;
      for (j = 0; j < n; j++)
         c_block[i] += a[i][j] * b[0][j];
   }

   replicate_block_vector (c_block, n, (void *) c, mpitype,
      MPI_COMM_WORLD);
   MPI_Barrier (MPI_COMM_WORLD);
   seconds += MPI_Wtime();

   print_replicated_vector (c, mpitype, n, MPI_COMM_WORLD);

   MPI_Allreduce (&seconds, &max_seconds, 1, mpitype, MPI_MAX,
      MPI_COMM_WORLD);
   if (!id) {
      printf ("MV1) N = %d, Processes = %d, Time = %12.6f sec,",
         n, p, max_seconds);
      printf ("Mflop = %6.2f\n", 2*n*n/(1000000.0*max_seconds));
   }
   MPI_Finalize();
   return 0;
}
