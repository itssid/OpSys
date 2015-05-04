##########Make File in Multi-File Demo###############################
#	@(#)File:           $CVSfile: Makefile,v $
#	@(#)Version:        $Revision: 0.1 $
#	@(#)Last changed:   $Date: 2015/03/16 23:20:00 $
#	@(#)Purpose:        Demo of Multi-File Code and Make utility
#	@(#)Author:         Narendra Shukla
#	@(#)Copyright:      (C) NS 2015-16
#	@(#)Product:        :CSD 204 Operating Systems Lab
#####################################################################

#############################################
# Add Macros for gcc and PATH names
#############################################

all: main.o chopsticks.o
	gcc -pthread -g -o ../bin/dining ../obj/main.o ../obj/chopsticks.o

main.o:
	gcc -g -o ../obj/main.o -Wall -c ../src/main.c -lpthreads -I../include

chopsticks.o:
	gcc -g -o ../obj/chopsticks.o -Wall -c ../src/chopsticks.c -lpthreads -I../include

clean:
	rm ../bin/dining ../bin/dining 2>/dev/null
	rm ../obj/*.o 2>/dev/null
	rm ../src/*~ ../src/*.o ../src/a.out 2>/dev/null
	rm ../include/*~ 2>/dev/null
	rm ../doc/*~ 2>/dev/null
	rm *~ 2>/dev/null



