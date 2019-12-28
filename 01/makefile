CC=g++
CFLAGS = --std=c++14
compile: main.cpp
	$(CC) main.cpp -o main $(CFLAGS)
run: compile
	./main "2 + 2"
test: compile
	python3 test.py
clean:
	rm -rf main
