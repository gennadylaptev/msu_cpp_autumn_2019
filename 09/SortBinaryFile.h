#include <fstream>
#include <thread>
#include <mutex>
#include <queue>
#include <cstdint>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <exception>
#include <iostream>
#include <atomic>

class SortBinaryFile {

public:
    SortBinaryFile (const std::string& input_file,
                    const std::string& sorted_file);
    void sort ();

private:
    void create_chunks ();
    void sort_chunks_thread ();
    void sort_chunks ();
    void merge_two_arrays (const std::string& name1,
                           const std::string& name2,
                           const std::string& outname);
    void merge_sorted_thread ();
    void merge_sorted ();
    void rename_result();
    void clear_data ();
    void remove_with_msg (const std::string&);

    void store_exception (const std::string& msg);

    // fields
    const size_t typesize = sizeof(uint64_t);
    const size_t block_size = 200000;

    std::string input_file;
    std::string sorted_file;

    std::mutex chunks_mutex;
    std::mutex queue_mutex;
    std::mutex sorted_mutex;
    std::mutex part_number_mutex;
    std::mutex exception_mutex;

    size_t part_number;
    std::queue<std::string> chunks_queue;
    std::queue<std::string> sorted_queue;

    // to communicate to other threads that something bad happened
    std::atomic_bool exceptionFlag;
    std::exception_ptr exceptionPtr;
};
