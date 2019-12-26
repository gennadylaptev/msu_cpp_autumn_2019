#include "ThreadPool.hpp"

ThreadPool::ThreadPool (size_t poolSize) : poolSize(poolSize) {
    stop_ = false;
    // initialize threads
    for (size_t i = 0; i < poolSize; i++)
        threads_.push_back(std::thread(&ThreadPool::initialize_thread, this));
}

void ThreadPool::initialize_thread () {
     while (true) {
        std::function<void()> job;

        {
            // set the lock
            std::unique_lock <std::mutex> lock(mutex_);

            // wait if there's no jobs and pool is not stopped
            while (!stop_ && jobs_.empty())
                condition_.wait(lock);

            // if pool is stopped - stop execution
            if (stop_) break;
            
            // extract the job from the queue
            job = jobs_.front();
            jobs_.pop(); 
        }
        
        job(); // exec the job
    }
    return;
}


ThreadPool::~ThreadPool ()
{
    stop_ = true;
    condition_.notify_all();

    for ( std::thread& thread_ : threads_ ) {
        thread_.join();
    }
}

