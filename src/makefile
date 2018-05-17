main: main.o monome.o polynome.o monome.h polynome.h
	g++ main.o monome.o polynome.o -o main

main.o: main.cpp monome.h
	g++ -c main.cpp -o main.o

monome.o: monome.cpp monome.h
	g++ -c monome.cpp -o monome.o

polynome.o: polynome.cpp polynome.h monome.h
	g++ -c polynome.cpp -o polynome.o

clean:
	rm *.o