all: prim clean

prim: main.o prim.o
	gcc -o prim.bin main.o prim.o

main.o: main.c prim.h
	gcc -o main.o main.c -c -W -Wall

prim.o: prim.c prim.h
	gcc -o prim.o prim.c -c -W -Wall

clean: 
	rm -rf *.o
