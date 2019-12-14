#include <exception>

template <class T>
class MyAllocator {
    
    public:
        using value_type =  T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference  = T&;
        using const_reference = const T&;
        using size_type =  std::size_t;
        
        MyAllocator ();
        ~MyAllocator ();
        
        pointer allocate (size_type);
        void deallocate (pointer);
        
        template <class... Args>
        void construct (pointer, Args&&...);

        void destroy (pointer);
};

template <class T>
MyAllocator<T>::MyAllocator () {}

template <class T>
MyAllocator<T>::~MyAllocator () {}

template <class T>
typename MyAllocator<T>::pointer MyAllocator<T>::allocate (size_type n) {
    pointer p;
    
    if ((p = static_cast<pointer>(::operator new(sizeof(value_type) * n))) == nullptr)
    {
        throw std::bad_alloc();
    }
    else
    {   
        return p;
    }
}

template <class T>
void MyAllocator<T>::deallocate (pointer p) {
    ::operator delete(p);
}


template <class T>
template <class... Args>
void MyAllocator<T>::construct (pointer p, Args&&... args) {
    ::new((void *)p) value_type (std::forward<Args>(args)...);
}

template <class T>
void MyAllocator<T>::destroy (pointer p) {
    static_cast<T*>(p)->~T();
}
