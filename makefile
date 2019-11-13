all:main

main: main.o threadpool.o parse.o
	g++ main.o threadpool.o parse.o -o main -Wall -lpthread

main.o: main.cpp
	g++ -c main.cpp
	
threadpool.o: threadpool.cpp 
	g++ -c threadpool.cpp

parse.o: parse.cpp
	g++ -c parse.cpp
clean:
	rm *.o

client: client.cpp
	g++ client.cpp -lpthread -o client