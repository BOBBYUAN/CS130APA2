
all: prog2

prog2: main.o
	g++ main.o -o prog2

main.o: main.cpp splayTree.h
	g++ -c main.cpp

clean:
	rm *.o prog2
