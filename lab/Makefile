# Very Simple Make file to let you compile your modified code. You are free to edit it and use macros to make it more efficient.         
all: atomic_lab.o mutexlock_lab.o
	gcc -Wall -pthread -o atomic atomic_lab.o
	gcc -Wall -pthread -o mutex mutexlock_lab.o

atomic_lab.o:
	gcc  -Wall -c atomic_lab.c -pthread

mutexlock_lab.o:
	gcc  -Wall -c mutexlock_lab.c -pthread
	
clean:
	rm  *.o atomic mutex 
