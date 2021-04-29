CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = pth-stencil-2d make-2d print-2d
OBJECTS1 = make-2d.o functions.o 
OBJECTS2 = pth-stencil-2d.o functions.o pthread_barrier.o
OBJECTS3 = print-2d.o
LDFLAGS = -lm
CC = gcc

all: $(PROGS)

make-2d: $(OBJECTS1)
	$(CC) $(LDFLAGS) -o make-2d $(OBJECTS1)

pth-stencil-2d: $(OBJECTS2)
	$(CC) $(LDFLAGS) -o pth-stencil-2d $(OBJECTS2) -lpthread

print-2d: $(OBJECTS3)
	$(CC) $(LDFLAGS) -o print-2d $(OBJECTS3)
	
make-2d.o: make-2d.c 
	$(CC) $(CFLAGS) -c make-2d.c

pth-stencil-2d.o: pth-stencil-2d.c 
	$(CC) $(CFLAGS) -c pth-stencil-2d.c

print-2d.o: print-2d.c 
	$(CC) $(CFLAGS) -c print-2d.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

pthread_barrier.o: pthread_barrier.c pthread_barrier.h
	$(CC) $(CFLAGS) -c pthread_barrier.c

clean:
	rm -f $(PROGS) *.o core*
