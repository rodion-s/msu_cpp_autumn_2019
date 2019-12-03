#include <limits>
#include <memory>
#include <stdexcept>

template <typename T>
class Allocator
{
public:
    using pointer_type = T*;
    using value_type = T;
    using size_type = size_t;

    pointer_type allocate(size_type size) {
        return static_cast <pointer_type>(operator new[](size * sizeof(value_type)));
    }
    void deallocate(pointer_type ptr, size_type size) {
        operator delete[](ptr, size * sizeof(value_type));
    }

    template <typename... Args>
    void construct(pointer_type ptr, Args&&... args) {
        ::new(ptr) value_type(std::forward<Args>(args)...);
    }

    void destroy(pointer_type ptr) {
        ptr->~value_type();
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max();
    }
};
template<typename T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:
	using pointer_type = T*;
    using reference_type = T&;
    using size_type = size_t;

    explicit Iterator(pointer_type ptr) : ptr_(ptr) {}
    bool operator==(const Iterator<T>& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) const {
        return !(*this == other);
    }

    reference_type operator*() const {
        return *ptr_;
    }

    Iterator operator+(size_type n) const {
        return Iterator(ptr_ + n);
    }
    Iterator operator-(size_type n) const {
        return Iterator(ptr_ - n);
    }

    Iterator& operator++() {
        ++ptr_;
        return *this;
    }

    Iterator& operator--() {
        --ptr_;
        return *this;
    }

    Iterator operator++(int) {
        auto tmp = this;
        ++ptr_;
        return *tmp;
    }

    Iterator operator--(int) {
        auto tmp = this;
        --ptr_;
        return *tmp;
    }


    Iterator& operator+=(size_type n) {
        ptr_ += n;
        return *this;
    }
    Iterator& operator-=(size_type n) {
        ptr_ -= n;
        return *this;
    }

    bool operator<(const Iterator& other) const {
        return ptr_ < other.ptr_;
    }
    bool operator>(const Iterator& other) const {
        return ptr_ > other.ptr_;
    }
    bool operator<=(const Iterator& other) const {
        return ptr_ <= other.ptr_;
    }
    bool operator>=(const Iterator& other) const {
        return ptr_ >= other.ptr_;
    }
   	reference_type operator[](size_type idx) {
        return ptr_[idx];
    }
};



template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using value_type = T;
    using pointer_type = T*;
    using reference_type = T&;
    using size_type = size_t;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
private:
    pointer_type data_;
    size_type size_;
    size_type available_sz_;
    Alloc alloc_;
public:
    Vector(size_type init_sz = 0) : 
        data_(alloc_.allocate(init_sz)), 
        size_(init_sz), 
        available_sz_(1), 
        alloc_() 
    {
        for (size_type i = 0; i < size_; ++i)
            alloc_.construct(data_ + i);
    }
   
    void resize(size_type new_sz) {
        if (size_ < new_sz) {
            reserve(new_sz << 1);
            for (size_type i = size_; i < new_sz; ++i) {
                alloc_.construct(data_ + i);
            }
            size_ = new_sz;
        } else if(size_ > new_sz) {
            for (size_type i = new_sz; i < size_; ++i) {
                alloc_.destroy(data_ + i);
            }
            size_ = new_sz;
        }
    }

    void reserve(size_type new_sz) {
        if (available_sz_ < new_sz) {
            pointer_type buf = alloc_.allocate(new_sz);
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(buf + i, *(data_ + i));
                alloc_.destroy(data_ + i);
            }
            alloc_.deallocate(data_, available_sz_);
            available_sz_ = new_sz;
            data_ = buf;
        }
    }
    
    reference_type operator[](size_type idx) {
        if (idx < size_) {
            return data_[idx];
        } else {
            throw std::out_of_range("out of range");
        }
    }
    const reference_type operator[](size_type idx) const {
        if (idx < size_) {
            return data_[idx];
        } else {
            throw std::out_of_range("out of range");
        }
    }
    size_type size() const {
        return size_;
    }
    bool empty() const {
        return (size_ == 0);
    }

    void push_back(const T& elem) {
        if (size_ >= available_sz_) {
            reserve(available_sz_ << 1);
        }
        alloc_.construct(data_ + size_, std::move(elem));
        ++size_;
    }
    void push_back(T&& elem) {
        if (size_ >= available_sz_) {
            reserve(available_sz_ << 1);
        }
        alloc_.construct(data_ + size_, std::move(elem));
        ++size_;
    }
    void pop_back() {
        if (size_ > 0) {
        	--size_;
            alloc_.destroy(data_ + size_);
        }
    }
    iterator begin() {
        return iterator(data_);
    }
    iterator end() {
        return iterator(data_ + size_);
    }
    reverse_iterator rbegin() {
        return reverse_iterator(this->end());
    }
    reverse_iterator rend() {
        return reverse_iterator(this->begin());
    }
    void clear() {
        for(size_type i = 0; i < size_; ++i) {
            alloc_.destroy(data_ + i);
        }
        size_ = 0;
    }
    ~Vector() {
        clear();
        alloc_.deallocate(data_, available_sz_);
    }
};
