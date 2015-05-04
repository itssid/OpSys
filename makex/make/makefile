CC = gcc
CFLAGS = -I../include

ODIR =../obj
SDIR =../src
IDIR =../include
ODEP =../obj/ex.o ../obj/func.o
DEPS = ../include/func.h

../obj/%.o: ../src/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

../bin/outfile : ../obj/ex.o ../obj/func.o 
	$(CC) -o ../bin/outfile ../obj/ex.o ../obj/func.o $(CFLAGS)
