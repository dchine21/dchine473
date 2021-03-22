CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = integrate-serial integrate-parallel
PARALLEL = integrate-parallel.o functions.o
SERIAL = integrate-serial.o functions.o
LDFLAGS = -lm
CC = gcc
MCC = mpicc

all: integrate-serial integrate-parallel

integrate-parallel: $(PARALLEL)
	$(MCC) $(LDFLAGS) -o integrate-parallel $(PARALLEL)

integrate-parallel.o: integrate-parallel.c
	$(MCC) $(LDFLAGS) -c integrate-parallel.c

integrate-serial: $(SERIAL)
	$(CC) $(CFLAGS) $(LDFLAGS) -o integrate-serial $(SERIAL)

integrate-serial.o: integrate-serial.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c integrate-serial.c

functions.o: functions.c functions.h
	$(MCC) $(CFLAGS) -c functions.c $(LDFLAGS)

clean:
	rm -f $(PROGS) *.o core*
