all: ../bin/sched ../bin/scope
../bin/sched : ../src/sched.c
	gcc -o ../bin/sched ../src/sched.c -pthread -I../include
../bin/scope : ../src/scope.c
	gcc -o ../bin/scope ../src/scope.c -pthread -I../include

clean:
	rm ../bin/* 2>/dev/null
	rm ../obj/*.o 2>/dev/null
	rm ../src/*~ ../src/*.o ../src/a.out 2>/dev/null
	rm ../include/*~ 2>/dev/null
	rm *~ 2>/dev/null
