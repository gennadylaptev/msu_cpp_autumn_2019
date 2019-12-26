#include "SortBinaryFile.h"
#include <random>

const size_t typesize = sizeof(uint64_t);

void create_seq_file (uint64_t init_val,
                      uint64_t n,
                      const std::string& filename) {
    std::ofstream fs(filename, std::ios::binary);
    uint64_t limit = init_val + n;
    for (uint64_t i = init_val; i < limit; ++i) {
        fs.write(reinterpret_cast<char *>(& i), typesize);
    }
    fs.close();
}

void create_random_file (size_t n, const std::string& filename) {
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

void display_file (const std::string& filename) {
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

bool check_sorted (const std::string& infile) {
    std::ifstream fs (infile, std::ios::binary);
    if (!fs) {
        throw std::runtime_error("No file to compare!");
    }
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

int main (int argc, char* argv[]) {
    std::string input_name("input.bin");
    std::string sorted_name("sorted.bin");
    create_random_file(2000000, input_name);

    SortBinaryFile sorter(input_name, sorted_name);
    sorter.sort();

    bool is_sorted = false;

    try {
        is_sorted = check_sorted(sorted_name);
        std::cout << "Result is sorted = " << is_sorted << "\n";
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}