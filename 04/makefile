CC=g++
BigInt_impl: BigInt.hpp BigInt.cpp
	$(CC) -c BigInt.cpp -o BigInt.o --std=c++14
test_compile: BigInt_impl
	$(CC) tests.cpp BigInt.o -o tests --std=c++14
main_compile: BigInt_impl
	$(CC) BigInt.o main.cpp -o main --std=c++14
run: BigInt_impl main_compile
	./main
test: BigInt_impl test_compile
	./tests
clean:
	rm -rf BigInt.o tests main
