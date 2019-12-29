#include "SortBinaryFile.h"

SortBinaryFile::SortBinaryFile(const std::string &input_file,
                               const std::string &sorted_file) :
        input_file(input_file),
        sorted_file(sorted_file),
        part_number(0),
        exceptionFlag(false) {}

void SortBinaryFile::create_chunks () {
    // load input file by chunks and save chunks onto disk
    // using one thread

    std::ifstream input(input_file, std::ios::binary);
    if (!input.is_open()) {
        throw std::runtime_error("No input file!");
    }

    uint64_t * buffer = new uint64_t[block_size];

    size_t i = 0; // number of read numbers in the current round
    bool stop = !(input.read(reinterpret_cast<char *>(&buffer[i]), typesize));
    i++;

    while (!stop) {
        // read a block of data into buffer
        while (i < block_size) {
            // read a number, return false if failed
            stop = !(input.read(reinterpret_cast<char *>(&buffer[i]), typesize));
            if (stop)
                break;
            i++;
        }

        // if there's any read data
        if (i > 0) {
            std::string outname = "part_" + std::to_string(part_number) + ".bin";
            chunks_queue.emplace(outname);
            part_number++; // increase current number of chunks

            std::ofstream out(outname, std::ios::binary);
            if (!out.is_open())
                throw std::runtime_error("Cannot write chunkfile " + outname + "!\n");

            for (int j = 0; j < i; ++j) {
                out.write(reinterpret_cast<char *>(& buffer[j]), typesize);
            }
            out.close();

            // reset the state
            i = 0;
        }
    }
    delete [] buffer;
    input.close();
}

void SortBinaryFile::sort_chunks_thread () {
    // pop from chunks_queue, sort, add to sorted_queue
    std::string chunk_name;

    while (true) {

        // check if something bad happened in other thread(s)
        if (exceptionFlag)
            return;

        // set lock to the chunks_queue
        {
            std::lock_guard <std::mutex> lock(chunks_mutex);
            if (!chunks_queue.empty()) {
                chunk_name = chunks_queue.front();
                chunks_queue.pop();
            }
            else
                return;
        }

        // load chunk to an array
        std::ifstream chunk_stream (chunk_name, std::ios::binary);

        // if chunk file doesn't open, store the exception in exceptionPtr, abort
        if (!chunk_stream) {
            if (exceptionFlag) // check if we already caught an exception in another thread
                return;
            else {
                std::string msg("No chunk file " + chunk_name + "!");
                store_exception(msg);
                return;
            }
        }

        // read into buffer
        uint64_t * buffer = new uint64_t[block_size];
        size_t i = 0;
        bool stop = !(chunk_stream.read(reinterpret_cast<char *>(&buffer[i]), typesize));
        i++;

        while (!stop) {
            stop = !(chunk_stream.read(reinterpret_cast<char *>(&buffer[i]), typesize));
            if (stop)
                break;
            i++;
        }
        chunk_stream.close();

        // sort it
        std::sort(buffer, buffer+i);

        // write into file
        std::ofstream sorted_stream (chunk_name, std::ios::binary);

        // if fail to open output file store exception, abort
        if (!sorted_stream) {
            if (exceptionFlag) // check if we already caught an exception in another thread
                return;
            else {
                std::string msg("Cannot write sorted chunkfile " + chunk_name + "!");
                store_exception(msg);
                return;
            }
        }

        // write into file sorted chunk
        for (size_t j = 0; j < i; ++j) {
            sorted_stream.write(reinterpret_cast<char *>(& buffer[j]), typesize);
        }
        sorted_stream.close();
        delete [] buffer;

        // add to the sorted queue
        {
            std::lock_guard <std::mutex> lock2(sorted_mutex);
            sorted_queue.emplace(chunk_name);
        }
    }

}

void SortBinaryFile::sort_chunks () {
    std::thread t1(&SortBinaryFile::sort_chunks_thread, this);
    std::thread t2(&SortBinaryFile::sort_chunks_thread, this);
    t1.join();
    t2.join();

    if (exceptionFlag) {
        std::rethrow_exception(exceptionPtr);
    }
}

void SortBinaryFile::merge_two_arrays (
        const std::string& name1,
        const std::string& name2,
        const std::string& outname
        )
{
    // load numbers one by one, writes into out file
    std::ifstream fs1 (name1, std::ios::binary);
    std::ifstream fs2 (name2, std::ios::binary);
    std::ofstream out (outname, std::ios::binary);

    if (!fs1 or !fs2 or !out) {
        // if we cannot open any of the files -
        // delete all of them, throw exception,
        // later `clear_data` will be called and mop out
        // all the temporary files
        if (fs1) {
            fs1.close();
            remove_with_msg(name1);
        }
        if (fs2) {
            fs2.close();
            remove_with_msg(name2);
        }
        if (out) {
            out.close();
            remove_with_msg(outname);
        }
        // we will catch it in `merge_sorted_thread`
        throw std::runtime_error("Merge error: no input and output files!");
    }

    // read the data, return bool that it's not successful
    uint64_t temp1, temp2;
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

    fs1.close();
    fs2.close();
    out.close();

    //delete temp arrays
    remove_with_msg(name1);
    remove_with_msg(name2);
}

void SortBinaryFile::merge_sorted_thread () {

    std::string name1, name2, outname;
    size_t file_num;

    while (true) {

        // check if something bad happened in other thread(s)
        if (exceptionFlag)
            return;

        {
            // set lock on sorted_queue
            std::lock_guard <std::mutex> lock(sorted_mutex);
            size_t queue_size = sorted_queue.size();
            if (queue_size > 1) {
                name1 = sorted_queue.front();
                sorted_queue.pop();
                name2 = sorted_queue.front();
                sorted_queue.pop();
            }
            else break;
        }

        {   // get current part_file number
            std::lock_guard <std::mutex> lock(part_number_mutex);
            file_num = part_number;
            ++part_number;
        }

        outname = "part_" + std::to_string(file_num) + ".bin";

        // if intermediate files are corrupt, merge_two_arrays will throw a runtime error
        if (exceptionFlag)
            return;

        try {
            merge_two_arrays(name1, name2, outname);
        }
        catch (std::runtime_error& no_merge_files_error)
        {
            // catch the exception and then store into exceptionPtr
            exceptionFlag = true;
            {
                std::lock_guard <std::mutex> lock(exception_mutex);
                exceptionPtr = std::current_exception();
            }
            return;
        }

        {   // set lock on queue again - we add new filename
            std::lock_guard <std::mutex> lock(queue_mutex);
            sorted_queue.emplace(outname);
        }
    }
}

void SortBinaryFile::merge_sorted () {

    std::thread t1(&SortBinaryFile::merge_sorted_thread, this);
    std::thread t2(&SortBinaryFile::merge_sorted_thread, this);
    t1.join();
    t2.join();

    // if there are any exceptions - rethrow exception
    // we'll catch it in `sort` method
    if (exceptionFlag) {
        std::rethrow_exception(exceptionPtr);
    }
}

void SortBinaryFile::rename_result () {
    if (!sorted_queue.empty()) {
        std::string result_name = sorted_queue.front();
        std::rename(result_name.c_str(), sorted_file.c_str());
    }
    else {
        throw std::runtime_error("Empty queue! No result file!");
    }
}

void SortBinaryFile::sort() {

    try {
        create_chunks();
    }
    catch  (std::runtime_error& no_input) {
        std::cout << no_input.what() << " Terminate\n";
        return;
    }

    try {
        sort_chunks();
    }
    catch (std::runtime_error& no_chunk_file_error)
    {
        clear_data();
        std::cout << no_chunk_file_error.what() << " Terminate\n";
        return;
    }

    try {
        merge_sorted();
    }
    catch (std::runtime_error& no_merge_files_error)
    {
        clear_data();
        std::cout << no_merge_files_error.what() << " Terminate\n";
        return;
    }

    try {
        rename_result ();
    }
    catch (std::logic_error& empty_queue_error) {
        std::cout << empty_queue_error.what() << "Terminate\n";
        return;
    }
}

void SortBinaryFile::remove_with_msg (const std::string& filename) {
    if (std::remove(filename.c_str()) != 0) {
        std::cout << "Failed to remove " << filename << "\n";
    }
}

void SortBinaryFile::clear_data () {
    // called only in emergency situation
    std::string filename;
    while (!chunks_queue.empty()) {
        filename = chunks_queue.front();
        remove_with_msg(filename);
        chunks_queue.pop();
    }

    while (!sorted_queue.empty()) {
        filename = sorted_queue.front();
        remove_with_msg(filename);
        sorted_queue.pop();
    }
}

void SortBinaryFile::store_exception (const std::string& msg) {
    exceptionFlag = true;
    {
        std::lock_guard <std::mutex> lock(exception_mutex);
        exceptionPtr = std::make_exception_ptr(std::runtime_error(msg));
    }

}