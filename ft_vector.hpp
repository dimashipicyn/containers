#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include <memory>
#include <iterator>

namespace ft {

template<class T>
class iterator : public std::iterator {
public:
    typedef T*      pointer;

    explicit iterator(pointer c)
        : owner_(c)
    {

    }
    ~iterator() {

    }
    pointer owner_;
};


template<class T, class Allocator = std::allocator<T>>
class vector {
    friend void swap(vector<T, Allocator>& x, vector<T, Allocator>& y);
public:
    typedef T               value_type;
    typedef Allocator       allocator_type;
    typedef size_t          size_type;
    typedef std::ptrdiff_t  difference_type;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef T*              pointer;
    typedef const T*        const_pointer;

    explicit vector(const allocator_type& alloc = allocator_type())
        : data_(nullptr)
        , size_(0)
        , capacity_(0)
        , alloc_(alloc)
    {
        data_ = alloc_.allocate(1);
        capacity_ = 1;
    }

    explicit vector(size_type n
                    , const value_type& val = value_type()
                    , const allocator_type& alloc = allocator_type()
                    )
        : data_(nullptr)
        , size_(0)
        , capacity_(0)
        , alloc_(alloc)
    {
        data_ = alloc_.allocate(n + 1);
        capacity_ = n + 1;
        size_ = n;

        for (size_type i = 0; i < size_; ++i) {
            data_[i] = val;
        }
    }

    vector(const vector& v)
        : data_(nullptr)
        , size_(0)
        , capacity_(0)
        , alloc_(v.alloc_)
    {
        data_ = alloc_.allocate(v.size() + 1);
        size_ = v.size();
        capacity_ = v.size() + 1;

        std::memcpy(data_, v.data_, size_ * sizeof(T));
    }

    vector& operator=(vector v) {
        swap(v);
        return *this;
    }

    void swap(vector& v) {
        std::swap(data_, v.data_);
        std::swap(size_, v.size_);
        std::swap(capacity_, v.capacity_);
    }

    ~vector() {
        alloc_.deallocate(data_, capacity_);
    }

    size_type size() const {
        return size_;
    }

    size_type capacity() const {
        return capacity_;
    }

    size_type max_size() const {
        return 1073741823;
    }

    bool empty() const {
        return size_ == 0;
    }

    void resize(size_type n, value_type val = value_type()) {
        if (n >= capacity_) {
            realloc(n + 1);
        }
        for (size_type i = size_; i < n; ++i)
        {
            data_[i] = val;
        }
        size_ = n;
    }

    void reserve(size_type n) {
        if (n >= capacity_) {
            realloc(n);
        }
    }

    void shrink_to_fit() {
        if (size_ < (capacity_ / 2)) {
            realloc(size_ + 1);
        }
    }

    reference at(size_type index) {
        if (index >= size_) {
            throw std::out_of_range("ft::vector out of range." );
        }
        return data_[index];
    }

    const_reference at(size_type index) const {
        if (index >= size_) {
            throw std::out_of_range("ft::vector out of range." );
        }
        return data_[index];
    }

    reference operator[](size_type index) {
        return data_[index];
    }

    const_reference operator[](size_type index) const {
        return data_[index];
    }

    reference front() {
        return *data_;
    }

    const_reference front() const {
        return *data_;
    }

    reference back() {
        return data_[size_ - 1];
    }

    const_reference back() const {
        return data_[size_ - 1];
    }

    value_type* data() {
        return data_;
    }

    const value_type* data() const {
        return data_;
    }

    void push_back(const_reference value) {
        if (size_ >= capacity_) {
            realloc(capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void pop_back() {
        --size_;
        data_[size_].~value_type();
    }

    void clear() {
        for (size_t i = 0; i < size_; i++)
        {
            data_[i].~value_type();
        }
        size_ = 0;
    }

    allocator_type get_allocator() const {
        return alloc_;
    }

private:
    void realloc(size_type size) {
        T *n_data = alloc_.allocate(size);
        if (n_data == nullptr)
        {
            throw std::bad_alloc();
        }
        std::memcpy(n_data, data_, size_ * sizeof(T));
        alloc_.deallocate(data_, capacity_);
        data_ = n_data;
        capacity_ = size;
    }

private:
    pointer data_;
    size_type size_;
    size_type capacity_;
    Allocator alloc_;
};

template <class T, class Alloc>
void swap(vector<T, Alloc> &v1, vector<T, Alloc> &v2)
{
    v1.swap(v2);
}

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); i++)
    {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    
    return true;
}

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !operator==(lhs, rhs);
}

template <class T, class Alloc>
bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    size_t i = 0;
    for (; i < lhs.size(); i++)
    {
        if (i == rhs.size() || rhs[i] < lhs[i]) {
            return false;
        }
        else if (lhs[i] < rhs[i]) {
            return true;
        }
    }
    return i != rhs.size();
}

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    size_t i = 0;
    for (; i < lhs.size(); i++)
    {
        if (i == rhs.size() || rhs[i] < lhs[i]) {
            return false;
        }
        else if (lhs[i] <= rhs[i]) {
            return true;
        }
    }
    return i <= rhs.size();
}

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(operator<(lhs, rhs));
}

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(operator<=(lhs, rhs));
}

}

#endif