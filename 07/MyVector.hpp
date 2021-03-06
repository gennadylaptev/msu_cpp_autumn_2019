#include "MyIterator.hpp"
#include "MyAllocator.hpp"
#include <stdexcept>

template <class T>
class MyVector {
    
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = const T&;
        using vector = MyVector<T>;
        using iterator = MyIterator<T>;
        using const_iterator = const MyIterator<T>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using init_list = std::initializer_list<T>;
        // MyVector uses only MyAllocator as an allocator class template
        using allocator_type = MyAllocator<T>; 
        using size_type = std::size_t;
        
        explicit MyVector (size_type initial_size = 0);
        MyVector (init_list);
        MyVector (const vector&);
        MyVector (vector&&);
        MyVector& operator= (const vector&);
        MyVector& operator= (vector&&);
        ~MyVector ();
        
        value_type& operator[] (size_type);
        const value_type operator[] (size_type) const;
        reference at (size_type i) ;
        const_reference at (size_type i) const ;
    
        iterator begin();
        iterator end();
        reverse_iterator rbegin () ;
        reverse_iterator rend () ;
        const_iterator cbegin () const;
        const_iterator cend () const;
        const_reverse_iterator crbegin () const;
        const_reverse_iterator crend () const ;
        
        void shrink_to_fit ();
        void swap (vector&) ;
        void reserve (size_type);
        void resize (size_type);
        void resize (size_type, const value_type&);
        
        void push_back (const value_type &);
        void push_back (value_type &&);
        void pop_back();
        
        void clear();
        bool empty();
        
        size_type size () const;
        size_type capacity () const;
        
        allocator_type get_allocator () const;
        
    private:
        allocator_type allocator_;
        pointer first_; // first element
        pointer last_;  // last element
        pointer end_;   // end of allocated memory

        void copy_data (pointer to, pointer from, size_type n);
        void delete_vector ();
        void reallocate (size_type);
        void fill_with_value (pointer, size_type, const value_type&);
};

template <class T>
void swap (MyVector<T>& left, MyVector<T>& right) {
    left.swap(right);
}

template <class T>
MyVector<T>::MyVector (size_type initial_size) {
    first_ = allocator_.allocate(initial_size);
    last_ = first_;
    end_ = first_ + initial_size;
}

template <class T>
MyVector<T>::MyVector (init_list values) {
    
    auto it = values.begin();
    const auto end = values.end();
    size_type size = values.size();
    
    first_ = allocator_.allocate(size);

    last_ = first_ + size;
    end_ = first_ + size;
    
    pointer p = first_; 
    while (it != end) {
        allocator_.construct(p, static_cast<value_type>(*it) );
        p++;
        it++;
    }
}

template <class T>
MyVector<T>::MyVector (const vector& other) {

    first_ = allocator_.allocate(other.capacity());
    last_ = first_ + other.size();
    end_ = first_ + other.capacity();
    copy_data(first_, other.first_, other.size());            
}

template <class T>
MyVector<T>::MyVector (vector&& other) : 
    first_(other.first_), last_(other.last_), end_(other.end_) {
    other.first_ = nullptr;
    other.last_ = nullptr;
    other.end_ = nullptr;
}

template <class T>
MyVector<T>& MyVector<T>::operator= (const vector& other) {

    delete_vector();

    allocator_ = other.get_allocator(); 
    
    first_ = allocator_.allocate(other.capacity());
    last_ = first_ + other.size();
    end_ = first_ + other.capacity();

    copy_data(first_, other.first_, other.size());

    return *this;
}

template <class T>
MyVector<T>& MyVector<T>::operator= (vector&& other) {
    
    if (*this != other) {
        delete_vector();
        first_ = other.first_;
        last_ = other.last_;
        end_ = other.end_;
    }
    return *this;
}

template <class T>
MyVector<T>::~MyVector () {
    delete_vector();
}


template <class T>
typename MyVector<T>::value_type& MyVector<T>::operator[] (size_type i) {
    return *(first_ + i);
}

template <class T>
const typename MyVector<T>::value_type MyVector<T>::operator[] (size_type i) const {
    return *(first_ + i);
}
template <class T>
typename MyVector<T>::reference MyVector<T>::at (size_type i) {
    if (i < 0 or (i > (size() -1)))
        throw std::out_of_range("Index error!");
    else
        return first_[i];
}

template <class T>
typename MyVector<T>::const_reference MyVector<T>::at (size_type i) const {
    if (i < 0 or (i > (size() - 1)))
        throw std::out_of_range("Index error!");
    else
        return first_[i];
}

template <class T>
typename MyVector<T>::iterator MyVector<T>::begin () {
    return iterator(first_);
}

template <class T>
typename MyVector<T>::iterator MyVector<T>::end () {
    return iterator(last_);
}

template <class T>
std::reverse_iterator<typename MyVector<T>::iterator> MyVector<T>::rbegin() {
    return std::reverse_iterator<iterator>(end()) ;
}

template <class T>
std::reverse_iterator<typename MyVector<T>::iterator> MyVector<T>::rend() {
    return std::reverse_iterator<iterator>(begin()) ;
}

template <class T>
typename MyVector<T>::const_iterator MyVector<T>::cbegin() const {
    return iterator(first_);
}

template <class T>
typename MyVector<T>::const_iterator MyVector<T>::cend() const {
    return iterator(last_) ;
}

template <class T>
typename MyVector<T>::const_reverse_iterator MyVector<T>::crbegin() const {
    return std::reverse_iterator<iterator>(cbegin());
}

template <class T>
typename MyVector<T>::const_reverse_iterator  MyVector<T>::crend() const {
    return std::reverse_iterator<iterator>(cend());
}

template <class T>
void MyVector<T>::shrink_to_fit () {
    reallocate(size());
}

template <class T>
void MyVector<T>::swap(vector& other) {
    std::swap(this->first_, other.first_);
    std::swap(this->last_, other.last_);
    std::swap(this->end_, other.end_);
}


template <class T>
void MyVector<T>::reserve(size_type n) {
    if (n > capacity()) {
        reallocate(n);
    }
}

template <class T>
void MyVector<T>::resize(size_type n) {
    if (n < size()) {
        last_ = first_ + n;
        reallocate(n);
    }
    else if (n > size() and n < capacity()) {
        size_type d = end_ - last_;
        fill_with_value (last_, d, value_type() );
        last_ = end_;
    }
    else if (n > capacity()) {}
        reallocate(n);
        
        size_type d = end_ - last_;
        fill_with_value (last_, d, value_type() );
        last_ = end_;
}

template <class T>
void MyVector<T>::resize (size_type n, const value_type& x)  {
    if (n < size()) {
        last_ = first_ + n;
        reallocate(n);
    }
    else if (n > size() and n < capacity()) {
        size_type d = end_ - last_;
        fill_with_value (last_, d, x );
        last_ = end_;
    }
    else if (n > capacity()) {}
        reallocate(n);
        
        size_type d = end_ - last_;
        fill_with_value (last_, d, x );
        last_ = end_;
}

template <class T>
void MyVector<T>::push_back (const value_type & x) {
    if (last_ == end_) {
        // growth factor 1.5
        size_type new_capacity = capacity();
        new_capacity = 1.5 * new_capacity + 1; 
        reallocate(new_capacity);
    }
    allocator_.construct(last_, x);
    last_++;
}

template <class T>
void MyVector<T>::push_back (value_type && x) {
    if (last_ == end_) {
        // growth factor 1.5
        size_type new_capacity = capacity();
        new_capacity = 1.5 * new_capacity + 1; 
        reallocate(new_capacity);
    }
    allocator_.construct(last_, std::move(x));
    //allocator_.construct(last_, std::forward<value_type &&>(x));
    last_++;
}

template <class T>
void MyVector<T>::pop_back () {
    if (size() > 0)
        last_--;
}


template <class T>
void MyVector<T>::clear () {
    for (size_type i = 0; i < size(); i++)
        allocator_.destroy(first_ + i);
        
     last_ = first_;
}

template <class T>
bool MyVector<T>::empty() {
    return (size() == 0);
}


template <class T>
typename MyVector<T>::size_type MyVector<T>::size () const {
    return last_ - first_;
}

template <class T>
typename MyVector<T>::size_type MyVector<T>::capacity () const {
    return end_ - first_;
}


template <class T>
typename MyVector<T>::allocator_type MyVector<T>::get_allocator () const {
    return allocator_;
}

template <class T>
void MyVector<T>::copy_data (pointer to, pointer from, size_type n) {
    // n first elements
    for (size_type i = 0; i < n; i++)
        allocator_.construct(to + i, from[i]); //
}

template <class T>
void MyVector<T>::delete_vector () {

    for (size_type i = 0; i < size(); i++)
        allocator_.destroy(first_ + i);
        
    allocator_.deallocate(first_);
    last_ = nullptr;
    end_ = nullptr;
}

template <class T>
void MyVector<T>::reallocate (size_type n) {
    // 1. copy data to buffer
    // 2. delete old data
    // 3. allocate new memory (of size n)
    // 4. copy data to new memory
    
    size_type old_size = size();
    value_type buffer[old_size];
    copy_data(buffer, first_, old_size);

    delete_vector();

    first_ = allocator_.allocate(n);
    copy_data(first_, buffer, old_size);
    
    last_  = first_ + old_size;
    end_ = first_ + n;    
}

template <class T>
void MyVector<T>::fill_with_value (pointer start,
                                   size_type n,
                                   const value_type& value) {
    
    for (size_type i = 0; i < n; i++) {
        allocator_.construct(start + i, value);
    }
}
