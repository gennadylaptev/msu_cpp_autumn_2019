#include "ThreadPool.hpp"
#include <iostream>
#include <vector>
#include <random>


int create_random_num () {
    std::random_device rd;
    std::mt19937_64 gen (rd());

    std::uniform_int_distribution<int> dis(0, 100000);
    return dis(gen);
}

void test_1 () {

    ThreadPool pool(2);
    std::cout << "Printing integers from 0 to 17 with a pool of workers\n"; 

    for (int i = 0; i < 18; i++)
        std::cout << pool.exec( [i] () {return i; } ).get() << " ";
    std::cout << "\n";
}

void test_2 () {

    ThreadPool pool(4);
    std::cout << "Multiplying random integers with a pool of threads\n";
    auto task2 = [] (int x, int y) { return x*y;};

    std::vector<int> v;
    for (int i = 0; i < 10000; i++) {
        auto res = pool.exec(task2, create_random_num (), create_random_num ()).get();
        v.push_back(res);
    }
    std::cout << "Vector size: " << v.size() << "\n";

}

int main () {
     
    test_1 ();
    test_2 ();
    return 0;
}
