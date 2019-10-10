#include <chrono>
#include <iostream>

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
        : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us = 
            std::chrono::duration_cast<microseconds>
                (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};

int main() {

    int size = 10000;
     
    int ** a = new int*[size];
    for (int i = 0; i < size; i++)
        a[i] = new int[size];
        
    for (int j = 0; j < size; j++) {
        for (int k = 0; k < size; k++)
            a[j][k] = rand() % 10000;
    }
        
    volatile int sum = 0;
	Timer timer;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            sum += a[j][i];
    }
	
	// don't forget to free all allocated memory
	for (int i = 0; i < size; i++)
		delete [] a[i];
	delete [] a;
    
    return 0;
}
