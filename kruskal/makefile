all: kruskal clean

kruskal: main.o kruskal.o
	gcc -o kruskal.bin main.o kruskal.o

main.o: main.c kruskal.h
	gcc -o main.o main.c -c -W -Wall

kruskal.o: kruskal.c kruskal.h
	gcc -o kruskal.o kruskal.c -c -W -Wall

clean: 
	rm -rf *.o
