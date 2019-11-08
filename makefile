all:main

main: main.o threadpool.o
	g++ main.o threadpool.o -o main -Wall -lpthread

main.o: main.cpp
	g++ -c main.cpp
	
threadpool.o: threadpool.cpp 
	g++ -c threadpool.cpp

clean:
	rm *.o