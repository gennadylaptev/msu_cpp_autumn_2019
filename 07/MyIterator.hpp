#include <iterator>

template <class T>
class MyIterator :public std::iterator<std::random_access_iterator_tag, T> {

    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using iterator = MyIterator<T>;
        
        MyIterator (pointer, pointer);
        MyIterator (const iterator&);
        MyIterator& operator=(const iterator&);
        
        bool operator== (const iterator&) const;
        bool operator!= (const iterator&) const;
        
        bool operator> (const iterator&) const;
        bool operator>= (const iterator&) const;
        bool operator< (const iterator&) const;
        bool operator<= (const iterator&) const;
        
        iterator& operator++ ();
        void operator++ (int);
        iterator& operator-- ();
        void operator-- (int);
        
        reference operator* (); 
       
    private:
        pointer begin_;
        pointer current_;

};


template <class T>
MyIterator<T>::MyIterator (pointer start, pointer end) : begin_(begin_), current_(end) {}

template <class T>
MyIterator<T>::MyIterator (const iterator& other) : 
    begin_(other.begin_), current_(other.current_) {}

template <class T>
MyIterator<T>& MyIterator<T>::operator= (const iterator& other) {
    begin_ = other.ptr_;
    current_ = other.current_;
    return *this;    
}


template <class T>
bool MyIterator<T>::operator== (const iterator& other) const {
    return current_ == other.current_;
}

template <class T>
bool MyIterator<T>::operator!= (const iterator& other) const {
    return !(*this == other);
}

template <class T>
bool MyIterator<T>::operator> (const iterator& other) const {
    return current_ > other.current_;
}

template <class T>
bool MyIterator<T>::operator>= (const iterator& other) const {
    return current_ >= other.current_;
}

template <class T>
bool MyIterator<T>::operator< (const iterator& other) const {
    return current_ < other.current_;
}

template <class T>
bool MyIterator<T>::operator<= (const iterator& other) const {
    return current_ <= other.current_;
}


template <class T>
typename MyIterator<T>::iterator& MyIterator<T>::operator++ () {
    ++current_;
    return *this;
}

template <class T>
void MyIterator<T>::operator++ (int) {
    current_++;
}


template <class T>
typename MyIterator<T>::iterator& MyIterator<T>::operator-- () {
    --current_;
    return *this;
}

template <class T>
void MyIterator<T>::operator-- (int) {
    current_--;
}


template <class T>
typename MyIterator<T>::reference MyIterator<T>::operator* () {
    return *current_;
}

