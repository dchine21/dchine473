#include <mpi.h>
#include <stdio.h>
#include <math.h>


/******MACROS********/
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) \
			(BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)

void global_sum(double* result, int rank, int size, double my_value);

void exchange_values(int* east_recValue, int* west_recValue, int rank, int size);

void exchange_east(int* east_recValue , int rank, int size);

void exchange_west(int* west_recValue, int rank, int size);
