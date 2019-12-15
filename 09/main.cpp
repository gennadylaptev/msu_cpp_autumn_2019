#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <queue>
#include <cstdint>
#include <vector>
#include <string>
#include <random>
#include <functional>
#include <unordered_map>


size_t part_number = 0;
const size_t typesize = sizeof(uint64_t);
const size_t block_size = 200000; // макс. число объектов счит. в память

std::queue<std::string> parts_queue;

std::mutex queue_mutex;
std::mutex part_number_mutex;

struct SplitParam {
    size_t offset1;
    size_t n1;
    size_t offset2;
    size_t n2;
};

void create_seq_file (uint64_t init_val,
                      uint64_t n,
                      std::string filename) {
    std::ofstream fs(filename, std::ios::binary);
    uint64_t limit = init_val + n;
    for (uint64_t i = init_val; i < limit; ++i) {
        fs.write(reinterpret_cast<char *>(& i), typesize);
    }
    fs.close();
}

void create_random_file (size_t n, std::string filename) {
    std::random_device rd;
    std::mt19937_64 gen (rd());

    std::uniform_int_distribution<uint64_t> dis(0, std::numeric_limits<uint64_t>::max());

    std::ofstream fs(filename, std::ios::binary);
    for (size_t i = 0; i < n; ++i) {
        uint64_t temp = dis(gen);
        fs.write(reinterpret_cast<char *>(& temp), typesize);
    }
    fs.close();
}

void display_file (std::string filename) {
    std::vector<uint64_t> v;
    std::ifstream fs (filename, std::ios::binary);

    uint64_t temp;
    while (fs.read(reinterpret_cast<char *>(&temp), typesize)) {
        v.emplace_back(temp);
    }

    fs.close();
    for (const auto& x : v) {
        std::cout << x << " ";
    }

    std::cout << "\n";
}

SplitParam get_split_param (std::string& filename) {
    std::ifstream input (filename, std::ios::binary);
    // get file size
    input.seekg(0, std::ios::end);
    size_t input_size = input.tellg();
    input.close();

    size_t num_ints = input_size / typesize;
    size_t n1 = std::ceil(double(num_ints) / 2);
//    size_t delta = n1 % block_size;
//    n1 += block_size - delta;
    size_t n2 = num_ints - n1;

    size_t offset1 = 0;
    size_t offset2 = n1 * typesize;

    SplitParam res ;
    res.offset1 = offset1;
    res.n1 = n1;
    res.offset2 = offset2;
    res.n2 = n2;

    //std::cout << offset1 << " " << n1 << " " << offset2 << " " << n2 << "\n";

    return res;
}

void create_chunks_ (std::string& filename, size_t pos, size_t n) {
    // pos - число в байтах, с которого начинать чтение
    // n - число интов, которые надо считать
    // загружаем файл кусочками в память,  записываем на диск
    std::ifstream input (filename, std::ios::binary);
    uint64_t * buffer = new uint64_t[block_size];
    input.seekg(pos);

    size_t total = 0;
    size_t i = 0;
    bool stop = !(input.read(reinterpret_cast<char *>(&buffer[i]), typesize));
    i++;
    total++;

    while (!stop and total < n) {
        // read a block of data into buffer
        while (i < block_size and total < n) {
            stop = !(input.read(reinterpret_cast<char *>(&buffer[i]), typesize));
            if (stop)
                break;

            i++;
            total++;
        }

        if (i > 0) {

            // sort buffer
            std::qsort(buffer, i, typesize, [](const void* a, const void* b)
            {
                uint64_t arg1 = *static_cast<const uint64_t*>( a );
                uint64_t arg2 = *static_cast<const uint64_t*>( b );

                if(arg1 < arg2) return -1;
                if(arg1 > arg2) return 1;
                return 0;
            });

            {
                std::lock_guard <std::mutex> lock(part_number_mutex);
                std::string outname = "part_" + std::to_string(part_number) + ".bin";
                part_number++;

                std::ofstream out(outname, std::ios::binary);
                for (int j = 0; j < i; ++j) {
                    out.write(reinterpret_cast<char *>(& buffer[j]), typesize);
                }
                out.close();

                // add to the queue
                std::lock_guard <std::mutex> qlock(queue_mutex);
                parts_queue.emplace(outname);
            }
            // reset the state
            i = 0;
            //delete [] buffer;
            //uint64_t * buffer = new  uint64_t[block_size];
        }
    }
    delete [] buffer;
    input.close();
}

void create_chunks (std::string& filename) {
    // загружаем файл кусочками в память,  записываем на диск
    std::ifstream input (filename, std::ios::binary);
    uint64_t * buffer = new uint64_t[block_size];

    size_t i = 0;
    bool stop = !(input.read(reinterpret_cast<char *>(&buffer[i]), typesize));
    i++;

    while (!stop) {
        // read a block of data into buffer
        while (i < block_size) {
            stop = !(input.read(reinterpret_cast<char *>(&buffer[i]), typesize));
            if (stop)
                break;
            i++;
        }

        if (i > 0) {

            // sort buffer
//            std::qsort(buffer, i, typesize, [](const void* a, const void* b)
//            {
//                uint64_t arg1 = *static_cast<const uint64_t*>( a );
//                uint64_t arg2 = *static_cast<const uint64_t*>( b );
//
//                if(arg1 < arg2) return -1;
//                if(arg1 > arg2) return 1;
//                return 0;
//            });

            std::string outname = "part_" + std::to_string(part_number) + ".bin";
            part_number++;

            std::ofstream out(outname, std::ios::binary);
            for (int j = 0; j < i; ++j) {
                out.write(reinterpret_cast<char *>(& buffer[j]), typesize);
            }
            out.close();

            // reset the state
            i = 0;
            //delete [] buffer;
            //uint64_t * buffer = new  uint64_t[block_size];
        }
    }
    delete [] buffer;
    input.close();
}

void create_chunks_mt (std::string& filename) {
    SplitParam res = get_split_param(filename);

    {
        std::thread t1(std::bind(create_chunks_, std::ref(filename),
                                 std::ref(res.offset1), std::ref(res.n1)));
        std::thread t2(std::bind(create_chunks_, std::ref(filename),
                                 std::ref(res.offset2), std::ref(res.n2)));
        t1.join();
        t2.join();
    }
}

void merge_arrays (std::string& name1,
                   std::string& name2,
                   std::string& outname)
    {
    // load numbers one by one, writes into out file
    std::ifstream fs1 (name1, std::ios::binary);
    std::ifstream fs2 (name2, std::ios::binary);
    std::ofstream out (outname, std::ios::binary);
    uint64_t temp1, temp2;

    // read the data, return bool that it's not successful
    bool stop1 = !(fs1.read(reinterpret_cast<char *>(&temp1), typesize));
    bool stop2 = !(fs2.read(reinterpret_cast<char *>(&temp2), typesize));

    while (!stop1 and !stop2) {
        if (temp1 < temp2) {
            out.write(reinterpret_cast<char *>(&temp1), typesize);
            stop1 = !(fs1.read(reinterpret_cast<char *>(&temp1), typesize));
        }
        else {
            out.write(reinterpret_cast<char *>(&temp2), typesize);
            stop2 = !(fs2.read(reinterpret_cast<char *>(&temp2), typesize));
        }
    }
    while (!stop1) {
        out.write(reinterpret_cast<char *>(&temp1), typesize);
        stop1 = !(fs1.read(reinterpret_cast<char *>(&temp1), typesize));
    }
    while (!stop2) {
        out.write(reinterpret_cast<char *>(&temp2), typesize);
        stop2 = !(fs2.read(reinterpret_cast<char *>(&temp2), typesize));
    }

    //delete input arrays
    fs1.close();
    fs2.close();
    out.close();

    //delete intermediate arrays
    std::remove(name1.c_str());
    std::remove(name2.c_str());
}

void merge_arrays_thread () {

    std::string name1, name2, outname;
    size_t file_num;
    while (true) {

        { // вешаем лок на очередь
            std::lock_guard <std::mutex> lock(queue_mutex);
            size_t queue_size = parts_queue.size();
            if (queue_size > 1) {
                name1 = parts_queue.front();
                parts_queue.pop();
                name2 = parts_queue.front();
                parts_queue.pop();
                //std::cout << "popping: " << name1 << ", " << name2 << "\n";
            }
            else {
                break;
            }
        }

        { // ставим лок на номер нового файла
            std::lock_guard <std::mutex> lock(part_number_mutex);
            file_num = part_number;
            ++part_number;
        }

        outname = "part_" + std::to_string(file_num) + ".bin";
        merge_arrays(name1, name2, outname);

        { // вешаем лок на очередь, добавляем новый файл
            std::lock_guard <std::mutex> lock(queue_mutex);
            parts_queue.emplace(outname);
            //std::cout << "writing into: " << outname << "\n";
        }
    }
    return;
}

void merge_arrays_mt () {
    {
        std::thread t1(merge_arrays_thread);
        std::thread t2(merge_arrays_thread);
        t1.join();
        t2.join();
    }
}

bool check_sorted (std::string& filename) {
    std::ifstream fs (filename, std::ios::binary);
    uint64_t prev, curr;

    bool stop = !(fs.read(reinterpret_cast<char *>(&prev), typesize));

    while (!stop) {
        stop = !(fs.read(reinterpret_cast<char *>(&curr), typesize));
        if (!stop) {
            if (curr < prev) {
                fs.close();
                return false;
            }
            prev = curr;
        }
    }
    fs.close();
    return true;
}

bool check_values (std::string& input,
                   std::string& sorted) {

    // Only for testing, since it loads two files into memory
    std::unordered_map<uint64_t, size_t> input_val, sorted_val;

    std::ifstream is (input, std::ios::binary);
    uint64_t temp;
    while (is.read(reinterpret_cast<char *>(&temp), typesize)) {
        input_val[temp]++;
    }
    is.close();

    uint64_t temp2;
    std::ifstream ss (sorted, std::ios::binary);
    while (ss.read(reinterpret_cast<char *>(&temp2), typesize)) {
        sorted_val[temp2]++;
    }
    ss.close();

    return input_val == sorted_val;
}

int main () {

    std::string sorted_name ("sorted.bin");
    std::string input_name("input.bin");
    create_random_file(40000000, input_name);
    create_chunks_mt (input_name);
    merge_arrays_mt ();

    std::string result_name = parts_queue.front();
    std::rename(result_name.c_str(), sorted_name.c_str());
    std::cout << "Result is sorted = " << check_sorted(sorted_name) << "\n";
    
    // optional test (applicable to for small files)
    //std::cout << "Values are the same = " << check_values(input_name, sorted_name) << "\n";

    return 0;
}
