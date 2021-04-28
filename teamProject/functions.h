#ifndef __H_FUNCTIONS__
#define __H_FUNCTIONS__

double** alloc2d(int nrows, int ncols);

void alloc2dnew(double*** a, int nrows, int ncols);

void fill2d(double** a, int nrows, int ncols);

void createBStart(double** b, int nrows, int ncols);

void print2d(double** a, int nrows, int ncols);

#endif