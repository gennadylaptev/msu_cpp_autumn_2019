#include "ThreadPool.cpp"
#include <iostream>

void test_1 () {
    ThreadPool pool(8);
    
    std::cout << "Printing integers from 0 to 17 with a pool of workers\n"; 
    
    for (int i = 0; i < 18; i++)
        std::cout << pool.exec( [i] () {return i; } ).get() << " ";
    std::cout << "\n";   
}


int main () {

    test_1 ();    
    
    return 0;
}
