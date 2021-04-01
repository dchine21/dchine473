CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = pth_mat_vect serial_mat_vect gen-double-matrix print-matrix
OBJECTS = pth_mat_vect.o
SERIAL = serial_mat_vect.o
PFLAGS = -lpthread
CC = gcc

all: pth_mat_vect serial_mat_vect gen-double-matrix print-matrix

pth_mat_vect: pth_mat_vect.o
	$(CC) $(CFLAGS) -o pth_mat_vect $(OBJECTS) $(PFLAGS)

pth_mat_vect.o: pth_mat_vect.c
	$(CC) $(CFLAGS) -c pth_mat_vect.c

serial_mat_vect.o: serial_mat_vect.c
	$(CC)  $(CFLAGS) -c serial_mat_vect.c

print-matrix.o: print-matrix.c
	$(CC) $(CFLAGS) -c print-matrix.c

gen-double-matrix.o: gen-double-matrix.c
	$(CC) $(CFLAGS) -c gen-double-matrix.c

clean:
	rm -f $(PROGS) *.o core*
