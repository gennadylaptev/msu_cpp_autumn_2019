class LinearAllocator
{
    private:
        std::size_t maxSize;
        char * start_;
        char * current_;
        char * end_;

    public:
        LinearAllocator (std::size_t maxSize);
        ~LinearAllocator ();
        char* alloc (std::size_t size);
        void reset ();
};
