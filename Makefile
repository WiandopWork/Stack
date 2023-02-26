build: main.o stack.o tests.o
	gcc main.o stack.o tests.o

main.o: main.c
	gcc -c main.c

stack.o: stack.c stack.h
	gcc -c stack.c

tests.o: tests/tests.c tests/tests.h
	gcc -c tests/tests.c

clean: main.o stack.o tests.o
	del a.exe main.o stack.o tests.o


coverage_check: main.c stack.c stack.h tests/tests.c tests/tests.h
	gcc -c --coverage main.c
	gcc -c --coverage stack.c
	gcc -c --coverage tests/tests.c

link_check: main.o stack.o tests.o
	gcc --coverage main.o stack.o tests.o -o check.exe

start_check: coverage_check link_check
	make coverage_check
	make link_check

	./check.exe

	gcov main.c -m -b
	gcov stack.c -m -b
	gcov tests.c -m -b

	make clean_check

clean_check:
	del check.exe *.c.gcov *.gcda *.gcno

