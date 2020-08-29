all:
	gcc -Wall -O3 -pedantic -c -o libmap.o libmap.c
	gcc -Wall -O3 -pedantic -c hanoi.c -o hanoi.o
	ar rcs libmap.a libmap.o
	gcc -Wall -O3 -pedantic -o hanoi.x hanoi.o -L. -lmap
	./hanoi.x
