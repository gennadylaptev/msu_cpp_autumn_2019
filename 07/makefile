CC=g++
CFLAGS = --std=c++14
compile: main.cpp
	$(CC) main.cpp -o main $(CFLAGS)
run: compile
	./main
test: compile
	./main
clean:
	rm -rf main *~
