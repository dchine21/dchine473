CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = print-2d make-2d stencil-2d
OBJECTS = print-2d.o make-2d.o stencil-2d.o
LDFLAGS = -lm
CC = gcc

all: $(PROGS)

print-2d.o: print-2d.c
	$(CC) $(CFLAGS) -c print-2d.c
print-2d: print-2d.o
	$(CC) $(CFLAGS) -o print-2d print-2d.o

make-2d.o: make-2d.c
	$(CC) $(CFLAGS) -c make-2d.c
make-2d: make-2d.o
	$(CC) $(CFLAGS) -o make-2d make-2d.o

stencil-2d.o: stencil-2d.c
	$(CC) $(CFLAGS) -c stencil-2d.c
stencil-2d: stencil-2d.o
	$(CC) $(CFLAGS) -o stencil-2d stencil-2d.o

clean:
	rm -f $(PROGS) *.o core*
