CC=g++
CFLAGS = --std=c++14
compile: Serializer.hpp Deserializer.hpp Data.hpp Error.hpp
	$(CC) tests.cpp -o tests $(CFLAGS)
test: compile
	./tests
clean:
	rm -rf Data.o tests main
