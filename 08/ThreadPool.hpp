#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <future>
#include <functional>


class ThreadPool {
    public:
        explicit ThreadPool (size_t poolSize);
        ~ThreadPool ();
        
        // pass arguments by value
        template <class Func, class... Args>
        auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
        
    private:
        size_t poolSize;
        std::vector<std::thread> threads_; // vector of thread objects
        std::queue< std::function<void()> > jobs_; // queue with jobs
        std::condition_variable condition_; // communication among threads
        std::mutex mutex_; // 
        bool stop_; // is ThreadPoll stopped
        
        void initialize_thread ();
};
