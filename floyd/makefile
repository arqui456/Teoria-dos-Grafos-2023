all: floyd clean

floyd: main.o floyd.o
	gcc -o floyd.bin main.o floyd.o

main.o: main.c floyd.h
	gcc -o main.o main.c -c -W -Wall

floyd.o: floyd.c floyd.h
	gcc -o floyd.o floyd.c -c -W -Wall

clean: 
	rm -rf *.o
