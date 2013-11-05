rm=/bin/rm -f
CC=cc
DEFS=
INCLUDES=-I.

DEFINES= $(INCLUDES) $(DEFS)
CFLAGS= -std=c99 $(DEFINES) -O2 -fomit-frame-pointer -funroll-loops 

all: KeccakF1600_driver

KeccakF1600_driver:  KeccakF1600_driver.c KeccakF1600.o
	$(CC) $(CFLAGS) -o KeccakF1600_driver KeccakF1600_driver.c KeccakF1600.o

KeccakF1600.o: KeccakF1600.c KeccakF1600.h
	$(CC) $(CFLAGS) -c KeccakF1600.c $(LIBS)

clean:
	$(rm) KeccakF1600.o KeccakF1600_driver *.o core *~
