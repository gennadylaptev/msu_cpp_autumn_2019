#include "LinearAllocator.cpp"
#include <iostream>
#include <string>

std::string yes (" passed!\n");
std::string no (" passed!\n");

void test_1 () {
    std::string name ("Allocation 1");

    LinearAllocator allocator (12);
    char * p = allocator.alloc(4);
    
    if (p != nullptr)
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_2 () {
    std::string name ("Allocation 2");

    LinearAllocator allocator (4);
    char * p = allocator.alloc(12);
    
    if (p == nullptr)
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_3 () {
    std::string name ("Allocation 3");

    LinearAllocator allocator (12);
    char * p1 = allocator.alloc(7);
    char * p2 = allocator.alloc(5);
    
    if (p1 != nullptr and p2 != nullptr)
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_4 () {
    std::string name ("Allocation 4");

    LinearAllocator allocator (12);
    char * p1 = allocator.alloc(7);
    char * p2 = allocator.alloc(6);
    
    if (p1 != nullptr and p2 == nullptr)
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_5 () {
    std::string name ("Reset");

    LinearAllocator allocator (12);
    char * p1 = allocator.alloc(12);
    allocator.reset();
    
    char * p2 = allocator.alloc(12);
    
    if (p2 != nullptr)
        std::cout << name << yes;
    else
        std::cout << name << no;  
}

int main () {

    test_1 ();
    test_2 ();
    test_3 ();
    test_4 ();
    test_5 ();


    return 0;
}
