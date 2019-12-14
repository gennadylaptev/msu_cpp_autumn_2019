#include <iterator>
#include <cstddef>

template <class T>
class MyIterator :public std::iterator<std::random_access_iterator_tag, T> {

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using const_pointer = const T*;
        using iterator = MyIterator<T>;
        using difference_type = std::ptrdiff_t;
        
        MyIterator ();
        MyIterator (pointer);
        MyIterator (const iterator&);
        MyIterator& operator=(const iterator&);
        
        
        bool operator== (const iterator&) const;
        bool operator!= (const iterator&) const;
        bool operator> (const iterator&) const;
        bool operator>= (const iterator&) const;
        bool operator< (const iterator&) const;
        bool operator<= (const iterator&) const;
        
        iterator& operator++ ();
        iterator operator++ (int);
        iterator& operator-- ();
        iterator operator-- (int);
        
        iterator operator+ (difference_type) const;
        iterator& operator+= (difference_type);
        
        iterator operator- (difference_type) const;
        difference_type operator- (const iterator&);
        iterator& operator-= (difference_type);
        
        reference operator[] (difference_type) const;
        reference operator* () const;
        const_pointer operator-> () const;
        
        friend iterator operator+ (difference_type n, const iterator& other) {
            return MyIterator(n + other.ptr_);
        }
       
    private:
        pointer ptr_;
};

//Constructors, assignment operator
template <class T>
MyIterator<T>::MyIterator () : ptr_(nullptr) {}

template <class T>
MyIterator<T>::MyIterator (pointer p) : ptr_(p) {}

template <class T>
MyIterator<T>::MyIterator (const iterator& other) : ptr_(other.ptr_) {}

template <class T>
typename MyIterator<T>::iterator& MyIterator<T>::operator= (const iterator& other) {
    ptr_ = other.ptr_;
    return *this;    
}

// comparison operators
template <class T>
bool MyIterator<T>::operator== (const iterator& other) const {
    return ptr_ == other.ptr_;
}

template <class T>
bool MyIterator<T>::operator!= (const iterator& other) const {
    return !(*this == other);
}

template <class T>
bool MyIterator<T>::operator> (const iterator& other) const {
    return ptr_ > other.ptr_;
}

template <class T>
bool MyIterator<T>::operator>= (const iterator& other) const {
    return ptr_ >= other.ptr_;
}

template <class T>
bool MyIterator<T>::operator< (const iterator& other) const {
    return ptr_ < other.ptr_;
}

template <class T>
bool MyIterator<T>::operator<= (const iterator& other) const {
    return ptr_ <= other.ptr_;
}

// increment, decrement
template <class T>
typename MyIterator<T>::iterator& MyIterator<T>::operator++ () {
    ++ptr_;
    return *this;
}

template <class T>
typename MyIterator<T>::iterator& MyIterator<T>::operator-- () {
    --ptr_;
    return *this;
}

template <class T>
typename MyIterator<T>::iterator MyIterator<T>::operator-- (int) {
    iterator OldIterator (*this);
    ptr_--;
    return OldIterator;
}

template <class T>
typename MyIterator<T>::iterator MyIterator<T>::operator++ (int) {
    iterator OldIterator (*this);
    ptr_++;
    return OldIterator;
}

// +
template <class T>
typename MyIterator<T>::iterator MyIterator<T>::operator+ (difference_type n) const {
    return MyIterator(ptr_ + n);
}

template <class T>
typename MyIterator<T>::iterator& MyIterator<T>::operator+= (difference_type n) {
    ptr_ += n;
    return *this;
}

// -
template <class T>
typename MyIterator<T>::iterator MyIterator<T>::operator- (difference_type n) const {
    return MyIterator(ptr_ - n);
}

template <class T>
typename MyIterator<T>::difference_type MyIterator<T>::operator- (const iterator& other) {
    return ( static_cast<difference_type>(ptr_ - other.ptr_) );
}

template <class T>
typename MyIterator<T>::iterator& MyIterator<T>::operator-= (difference_type n) {
    ptr_ -= n;
    return *this;
}



template <class T>
typename MyIterator<T>::reference MyIterator<T>::operator[] (difference_type n) const {
    return ptr_[n];
}

template <class T>
typename MyIterator<T>::reference MyIterator<T>::operator* () const {
    return *ptr_;
}

template <class T>
typename MyIterator<T>::const_pointer MyIterator<T>::operator-> () const {
    return ptr_;
} 


