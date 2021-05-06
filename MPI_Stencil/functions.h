#include <mpi.h>
#include <stdio.h>
#ifndef _TIMER_H_
#define _TIMER_H_

#include <sys/time.h>

#define GET_TIME(now) { \
	struct timeval t; \
	gettimeofday(&t, NULL); \
	now = t.tv_sec + t.tv_usec/1000000.0; \
}
#endif
#ifndef __H_FUNCTIONS__
#define __H_FUNCTIONS__

long int findSize(char file_name[]);

double** alloc2d(int nrows, int ncols);

void alloc2dnew(double*** a, int nrows, int ncols);

void fill2d(double** a, int nrows, int ncols);

void createBStart(double** b, double** a, int nrows, int ncols);

void print2d(double** a, int nrows, int ncols);

void exchange_values(double** east_recValue, double** west_recValue, double** value, int rank, int size, int cols, int my_high);
#endif
