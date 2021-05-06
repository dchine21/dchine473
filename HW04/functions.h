#include <mpi.h>
#include <stdio.h>
#include <math.h>

void global_sum(double* result, int rank, int size, double my_value);

void exchange_values(int east_recValue[], int west_recValue[], int rank, int value[], int size);

void exchange_east(int east_recValue[], int rank, int value[], int size);

void exchange_west(int west_recValue[], int rank, int value[], int size);
