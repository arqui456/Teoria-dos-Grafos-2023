all: dijkstra clean

dijkstra: main.o dijkstra.o
	gcc -o dijkstra.bin main.o dijkstra.o

main.o: main.c dijkstra.h
	gcc -o main.o main.c -c -W -Wall -Wextra -pedantic -g

dijkstra.o: dijkstra.c dijkstra.h
	gcc -o dijkstra.o dijkstra.c -c -W -Wall -Wextra -pedantic -g

clean: 
	rm -rf *.o
