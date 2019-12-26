#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <future>
#include <functional>
#pragma once

class ThreadPool {

    public:
        explicit ThreadPool (size_t poolSize);
        ~ThreadPool ();
        
        // pass arguments by value
        template <class Func, class... Args>
        auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> { 

            using return_type = decltype(func(args...));
            
            // shared pointer to packaged_task object that
            // stores the job (func(args...))
            auto job = std::make_shared<std::packaged_task<return_type()>>
            (
                std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
            );
            
            std::future<return_type> result = job->get_future();
            {
                std::unique_lock<std::mutex> lock(mutex_);

                if (stop_)
                    throw std::runtime_error("ThreadPool is stopped!");

                jobs_.emplace( [job]() {(*job)( ); } );
            }
            
            condition_.notify_one();
            return result;
        }
        
        
    private:
        size_t poolSize;
        std::vector<std::thread> threads_; // vector of thread objects
        std::queue< std::function<void()> > jobs_; // queue with jobs
        std::condition_variable condition_; // notify all threads that queue is empty
        std::mutex mutex_; // 
        std::atomic_bool stop_; // is ThreadPoll stopped
        
        void initialize_thread ();
};
