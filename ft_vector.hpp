#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include <memory>

namespace ft {

template<class T, class Allocator = std::allocator<T>>
class vector {
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
        for (size_type i = 0; i < v.size(); ++i) {
            data_[i] = v.data_[i];
        }
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

    reference at(size_type index) const {
        if (index >= size_) {
            throw std::out_of_range("ft::vector out of range." );
        }
        return data_[index];
    }

    void push_back(const_reference value) {
        realloc();
        data_[size_++] = value;
    }

private:
    void realloc() {
        if (size_ == capacity_) {
            T* n_data = alloc_.allocate(capacity_ * 2);
            if (n_data == nullptr) {
                throw std::bad_alloc();
            }
            std::memcpy(n_data, data_, size_ * sizeof(T));
            alloc.deallocate(data_, capacity_);
            data_ = n_data;
            capacity_ *= 2;
        }
    }

private:
    T* data_;
    size_t size_;
    size_t capacity_;
    Allocator alloc_;
};

}

#endif