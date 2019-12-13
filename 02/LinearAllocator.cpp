#include <cstdlib> 
#include "LinearAllocator.hpp"


LinearAllocator::LinearAllocator (std::size_t maxSize) : maxSize (maxSize) {
    
    start_ = static_cast<char *>(std::malloc(maxSize));
    
    if (start_ != nullptr) {
        end_ = start_ + maxSize - 1;
    }
    else
        end_ = nullptr;
    
    current_ = start_;                       
}

LinearAllocator::~LinearAllocator () {
    if ( start_ != nullptr ) {
        free(start_);
    }
}

char * LinearAllocator::alloc (std::size_t size) {

    if (start_ == nullptr)
        return nullptr;
    
    else if ( current_ + size - 1 > end_ )
        return nullptr;
    
    else {
        char * new_pointer = current_;
        current_ += size;
        return new_pointer;
    }
}

void LinearAllocator::reset () {
    current_ = start_;
}

