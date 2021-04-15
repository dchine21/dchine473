CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = exchange
OBJECTS = exchange.o functions.o
LDFLAGS = -lm
CC = gcc
MCC = mpicc

all: $(PROGS)

exchange: $(OBJECTS)
	$(MCC) -o exchange $(OBJECTS) $(LDFLAGS)

exchange.o: exchange.c
	$(MCC) $(CFLAGS) -c exchange.c

functions.o: functions.c functions.h
	$(MCC) $(CFLAGS) -c functions.c $(LDFLAGS)
clean:
	rm -f $(PROGS) *.o core*
