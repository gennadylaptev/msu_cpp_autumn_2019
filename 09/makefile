CC=g++
CFLAGS = --std=c++14
LDFLAGS= -pthread -lpthread
SortBinaryFile: SortBinaryFile.cpp, SortBinaryFile.h
	$(CC) -c SortBinaryFile.cpp -o SortBinaryFile.o $(CFLAGS)
compile_test:
	$(CC) -c main.cpp -o main.o  $(CFLAGS)
all: main.o SortBinaryFile.o
	$(CC) main.o SortBinaryFile.o -o main $(CFLAGS) $(LDFLAGS)
run:
	./main
test:
	./main
clean:
	rm -rf main *~ *.bin *.o
check:
	valgrind --leak-check=full -v  ./main
report:
	/usr/bin/time -v ./main
crash_test:
	python3 crash_test.py
clean_bin_files:
	rm -rf *~ *.bin
