CC=g++
CFLAGS = --std=c++14
LDFLAGS= -pthread -lpthread

threadpool: ThreadPool.cpp ThreadPool.hpp
	$(CC) -c ThreadPool.cpp -o ThreadPool.o $(CFLAGS)
compile_test: main.cpp
	$(CC) -c main.cpp -o main.o  $(CFLAGS)
all: main.o ThreadPool.o
	$(CC) main.o ThreadPool.o -o main $(CFLAGS) $(LDFLAGS)
run:
	./main
clean:
	rm -rf main *~ *.o
report:
	/usr/bin/time -v ./main
