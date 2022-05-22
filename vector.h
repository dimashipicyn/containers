#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include "traits.h"

#include <memory>
#include <iterator>

namespace ft {

    template <class T>
    class vector_iterator
    {
    public:
        typedef std::random_access_iterator_tag     iterator_category;
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef std::ptrdiff_t                      difference_type;
        typedef T&                                  reference;
        typedef size_t                              size_type;

        explicit vector_iterator(pointer c)
            : owner_data_(c)
        {
        }

        ~vector_iterator()
        {
        }

        vector_iterator(const vector_iterator& it)
            : owner_data_(it.owner_data_)
        {

        }

        vector_iterator& operator=(vector_iterator it) {
            std::swap(owner_data_, it.owner_data_);
            return *this;
        }

        bool operator==(const vector_iterator& it) const {
            return owner_data_ == it.owner_data_;
        }

        bool operator!=(const vector_iterator& it) const {
            return !operator==(it);
        }

        bool operator<(const vector_iterator& it) const {
            return owner_data_ < it.owner_data_;
        }

        bool operator>(const vector_iterator& it) const {
            return owner_data_ > it.owner_data_;
        }

        bool operator<=(const vector_iterator& it) const {
            return owner_data_ <= it.owner_data_;
        }

        bool operator>=(const vector_iterator& it) const {
            return owner_data_ >= it.owner_data_;
        }

        vector_iterator& operator++() {
            ++owner_data_;
            return *this;
        }

        vector_iterator operator++(int) {
            vector_iterator<T> tmp(*this);
            owner_data_++;
            return tmp;
        }

        vector_iterator& operator--() {
            --owner_data_;
            return *this;
        }

        vector_iterator operator--(int) {
            vector_iterator<T> tmp(*this);
            owner_data_--;
            return tmp;
        }

        vector_iterator& operator+=(size_type n) {
            owner_data_ += n;
            return *this;
        }

        vector_iterator operator+(size_type n) const {
            vector_iterator<T> tmp(*this);
            tmp += n;
            return tmp;
        }

        friend vector_iterator operator+(size_type n, const vector_iterator& it) {
            vector_iterator<T> tmp(it);
            tmp += n;
            return tmp;
        }

        vector_iterator& operator-=(size_type n) {
            owner_data_ -= n;
            return *this;
        }

        vector_iterator operator-(size_type n) const {
            vector_iterator<T> tmp(*this);
            tmp -= n;
            return tmp;
        }

        difference_type operator-(const vector_iterator& it) const {
            return owner_data_ - it.owner_data_;
        }

        reference operator*() const {
            return *owner_data_;
        }

        pointer operator->() const {
            return owner_data_;
        }

        reference operator[](size_type n) const {
            return owner_data_[n];
        }
    
    private:
        pointer owner_data_;
    };

    template <class T, class Allocator = std::allocator<T>>
    class vector
    {
    public:
        typedef T                           value_type;
        typedef Allocator                   allocator_type;
        typedef size_t                      size_type;
        typedef std::ptrdiff_t              difference_type;
        typedef T&                          reference;
        typedef const T&                    const_reference;
        typedef T*                          pointer;
        typedef const T*                    const_pointer;
        typedef vector_iterator<T>          iterator;

        explicit vector(const allocator_type &alloc = allocator_type())
            : data_(nullptr), size_(0), capacity_(0), alloc_(alloc)
        {
        }

        explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
            : data_(nullptr), size_(0), capacity_(0), alloc_(alloc)
        {
            data_ = alloc_.allocate(n + 1);
            capacity_ = n + 1;
            size_ = n;

            for (size_type i = 0; i < n; i++)
            {
                alloc_.construct(&data_[i], val);
            }
        }

        vector(const vector &v)
            : data_(nullptr), size_(0), capacity_(0), alloc_(v.alloc_)
        {
            data_ = alloc_.allocate(v.capacity());
            size_ = v.size();
            capacity_ = v.capacity();

           for (size_type i = 0; i < v.size(); i++)
           {
               alloc_.construct(&data_[i], v[i]);
           }
            
        }

        template<class InputIter>
        vector(InputIter first, InputIter last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type* = nullptr)
            : data_(nullptr)
            , size_(0)
            , capacity_(0)
            , alloc_(alloc)
        {
            typedef iterator_traits<InputIter> Traits;

            typename Traits::difference_type n = ft::distance(first, last);
            assert(n >= 0);

            realloc(n + 1);
            for (size_t i = 0; i < static_cast<size_t>(n); i++, first++)
            {
                alloc_.construct(&data_[i], *first);
            }
            size_ = n;
        }

        vector& operator=(vector v)
        {
            swap(v);
            return *this;
        }

        void swap(vector &v)
        {
            std::swap(data_, v.data_);
            std::swap(size_, v.size_);
            std::swap(capacity_, v.capacity_);
            std::swap(alloc_, v.alloc_);
        }

        ~vector()
        {
            alloc_.deallocate(data_, capacity_);
        }

        size_type size() const
        {
            return size_;
        }

        size_type capacity() const
        {
            return capacity_;
        }

        size_type max_size() const
        {
            return alloc_.max_size();
        }

        bool empty() const
        {
            return size_ == 0;
        }

        void resize(size_type n, value_type val = value_type())
        {
            if (n >= capacity_)
            {
                realloc(n + 1);
            }
            for (size_type i = size_; i < n; ++i)
            {
                data_[i] = val;
            }
            size_ = n;
        }

        void reserve(size_type n)
        {
            if (n >= capacity_)
            {
                realloc(n);
            }
        }

        void shrink_to_fit()
        {
            if (size_ < (capacity_ / 2))
            {
                realloc(size_ + 1);
            }
        }

        reference at(size_type index)
        {
            if (index >= size_)
            {
                throw std::out_of_range("ft::vector out of range.");
            }
            return data_[index];
        }

        const_reference at(size_type index) const
        {
            if (index >= size_)
            {
                throw std::out_of_range("ft::vector out of range.");
            }
            return data_[index];
        }

        reference operator[](size_type index)
        {
            return data_[index];
        }

        const_reference operator[](size_type index) const
        {
            return data_[index];
        }

        reference front()
        {
            return *data_;
        }

        const_reference front() const
        {
            return *data_;
        }

        reference back()
        {
            return data_[size_ - 1];
        }

        const_reference back() const
        {
            return data_[size_ - 1];
        }

        pointer data()
        {
            return data_;
        }

        const_pointer data() const
        {
            return data_;
        }

        void push_back(const_reference value)
        {
            if (size_ >= capacity_)
            {
                realloc(ft::max(capacity_ * 2, 1UL));
            }
            alloc_.construct(&data_[size_++], value);
        }

        void pop_back()
        {
            --size_;
            data_[size_].~value_type();
        }

        void clear()
        {
            for (size_type i = 0; i < size_; i++)
            {
                data_[i].~value_type();
            }
            size_ = 0;
        }

        allocator_type get_allocator() const
        {
            return alloc_;
        }

        iterator begin() {
            return iterator(data_);
        }

        iterator end() {
            return iterator(data_ + size_);
        }

        iterator insert(iterator pos, const_reference value) {

            difference_type idx = ft::distance(begin(), pos);
            assert(idx >= 0);

            if ((size_ +  1) >= capacity_) {
                realloc(ft::max(capacity_ * 2, 1UL));
            }

            for (size_type i = size_; i > static_cast<size_type>(idx); --i)
            {
                alloc_.construct(&data_[i], data_[i - 1]);
            }

            alloc_.construct(&data_[idx], value);
            ++size_;

            return iterator(&data_[idx]);
        }

        iterator insert(iterator pos, size_type n, const_reference value) {
            difference_type idx = ft::distance(begin(), pos);
            assert(idx >= 0);

            if ((size_ +  n) >= capacity_) {
                realloc(size_ + n + 1);
            }

            for (size_type i = (size_ + n - 1); i > static_cast<size_type>(idx); --i)
            {
                alloc_.construct(&data_[i], data_[i - n]);
            }

            for (size_type i = idx; i < (static_cast<size_type>(idx) + n); i++)
            {    
                alloc_.construct(&data_[i], value);
            }
            
            alloc_.construct(&data_[idx], value);
            
            size_ += n;

            return iterator(&data_[idx]);
        }

        template<class InputIter>
        iterator insert(iterator pos, InputIter first, InputIter last) {
            if (first == last) {
                return pos;
            }

            typedef iterator_traits<InputIter> Traits;

            typename Traits::difference_type n = ft::distance(first, last);
            assert(n >= 0);
            
            difference_type idx = ft::distance(begin(), pos);
            assert(idx >= 0);

            if ((size_ +  n) >= capacity_) {
                realloc(size_ + n + 1);
            }

            for (size_type i = (size_ + n - 1); i > static_cast<size_type>(idx); --i)
            {
                alloc_.construct(&data_[i], data_[i - n]);
            }
            
            for (size_type i = idx; first != last; i++, first++) {
                alloc_.construct(&data_[i], *first);
            }
            
            size_ += n;

            return iterator(&data_[idx]);
        }

    private:
        void realloc(size_type size)
        {
            T *n_data = alloc_.allocate(size);
            if (n_data == nullptr)
            {
                throw std::bad_alloc();
            }
            for (size_t i = 0; i < size_; i++)
            {
                alloc_.construct(&n_data[i], T(data_[i]));
            }
            alloc_.deallocate(data_, capacity_);
            data_ = n_data;
            capacity_ = size;
        }

    private:
        pointer     data_;
        size_type   size_;
        size_type   capacity_;
        Allocator   alloc_;
    };

    template <class T, class Alloc>
    void swap(vector<T, Alloc> &v1, vector<T, Alloc> &v2)
    {
        v1.swap(v2);
    }

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); i++)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }

        return true;
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !operator==(lhs, rhs);
    }

    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        size_t i = 0;
        for (; i < lhs.size(); i++)
        {
            if (i == rhs.size() || rhs[i] < lhs[i])
            {
                return false;
            }
            else if (lhs[i] < rhs[i])
            {
                return true;
            }
        }
        return i != rhs.size();
    }

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        size_t i = 0;
        for (; i < lhs.size(); i++)
        {
            if (i == rhs.size() || rhs[i] < lhs[i])
            {
                return false;
            }
            else if (lhs[i] <= rhs[i])
            {
                return true;
            }
        }
        return i <= rhs.size();
    }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(operator<(lhs, rhs));
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(operator<=(lhs, rhs));
    }
}

#endif