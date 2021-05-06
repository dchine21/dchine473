CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = mpi-stencil-2d make-2d print-2d stencil-2d
OBJECTS1 = make-2d.o 
OBJECTS2 = functions.o mpi-stencil-2d.o
OBJECTS3 = print-2d.o
OBJECTS4 = stencil-2d.o
LDFLAGS = -lm
CC = gcc
MCC = mpicc

all: $(PROGS)

mpi-stencil-2d: $(OBJECTS2)
	$(MCC) -o mpi-stencil-2d $(OBJECTS2) $(LDFLAGS)

make-2d: $(OBJECTS1)
	$(CC) $(LDFLAGS) -o make-2d $(OBJECTS1)

print-2d: $(OBJECTS3)
	$(CC) $(LDFLAGS) -o print-2d $(OBJECTS3)
	
stencil-2d: $(OBJECTS4)
	$(CC) $(LDFLAGS) -o stencil-2d $(OBJECTS4)

make-2d.o: make-2d.c 
	$(CC) $(CFLAGS) -c make-2d.c

print-2d.o: print-2d.c 
	$(CC) $(CFLAGS) -c print-2d.c

mpi-stencil-2d.o: mpi-stencil-2d.c
	$(MCC) $(CFLAGS) -c mpi-stencil-2d.c

stencil-2d.o: stencil-2d.c
	$(CC) $(CFLAGS) -c stencil-2d.c

functions.o: functions.c functions.h
	$(MCC) $(CFLAGS) -c functions.c $(LDFLAGS)

clean:
	rm -f $(PROGS) *.o core*
