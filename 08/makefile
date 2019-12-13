CC=g++
CFLAGS = --std=c++14
LDFLAGS= -pthread -lpthread
compile: main.cpp
	$(CC) main.cpp -o main $(CFLAGS) $(LDFLAGS)
run: compile
	./main
test: compile
	./main
clean:
	rm -rf main *~
