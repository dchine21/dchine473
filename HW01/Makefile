CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = mv1
OBJECTS = mv1.o MyMPI.o
LDFLAGS = -lm
CC = gcc
MCC = mpicc

all: mv1 gen-double-matrix print-matrix

mv1: $(OBJECTS)
	$(MCC) $(LDFLAGS) -o mv1 $(OBJECTS)
mv1.o: mv1.c
	$(MCC) $(LDFLAGS) -c mv1.c

print-matrix.o: print-matrix.c
	$(CC) $(CFLAGS) -c print-matrix.c

MyMPI.o: MyMPI.c MyMPI.h
	$(MCC) $(CFLAGS) -c MyMPI.c

gen-double-matrix.o: gen-double-matrix.c
	$(CC) $(CFLAGS) -c gen-double-matrix.c

functions.o: functions.c functions.h
	$(MCC) $(CFLAGS) -c functions.c $(LDFLAGS)

clean:
	rm -f $(PROGS) *.o core*
