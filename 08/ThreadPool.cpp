#include "ThreadPool.hpp"

ThreadPool::ThreadPool (size_t poolSize) : poolSize(poolSize) {
    stop_ = false;
    // initialize threads
    for (size_t i = 0; i < poolSize; i++)
        threads_.push_back (std::thread(&ThreadPool::initialize_thread, this));
}

void ThreadPool::initialize_thread () {
     while (true) {
        std::function<void()> job;
        {
            // set the lock
            std::unique_lock <std::mutex> lock(mutex_);

            while (!stop_ && jobs_.empty())
                condition_.wait(lock);

            if (stop_) break;
            
            // extract the job from the queue
            job = jobs_.front();
            jobs_.pop(); 
        }
        
        job(); // exec the job
    }
    return;
}


template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    
    using return_type = decltype(func(args...));
    
    // shared pointer to packaged_task object that
    // stores the job (func(args...))
    auto job = std::make_shared< std::packaged_task<return_type()> >
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


ThreadPool::~ThreadPool ()
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        stop_ = true;
    }

    condition_.notify_all();

    for ( std::thread& thread_ : threads_ ) {
        thread_.join();
    }
}

