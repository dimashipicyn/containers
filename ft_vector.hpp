#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include <memory>
#include <iterator>

namespace ft {

    template <typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
              typename _Pointer = _Tp *, typename _Reference = _Tp &>
    struct iterator
    {
        typedef _Category iterator_category;
        typedef _Tp value_type;
        typedef _Distance difference_type;
        typedef _Pointer pointer;
        typedef _Reference reference;
    };

    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    template<class T>
    struct iterator_traits
    {
        typedef typename T::iterator_category      iterator_category;
        typedef typename T::value_type             value_type;
        typedef typename T::difference_type        difference_type;
        typedef          difference_type                            distance_type;
        typedef typename T::pointer                pointer;
        typedef typename T::reference              reference;
    };

    template<class T>
    struct iterator_traits<T*>
    {
        typedef typename T::iterator_category      iterator_category;
        typedef typename T::value_type             value_type;
        typedef typename T::difference_type        difference_type;
        typedef          difference_type                            distance_type;
        typedef typename T::pointer                pointer;
        typedef typename T::reference              reference;
    };


    template <class T>
    class vector_iterator : public iterator<random_access_iterator_tag, T>
    {
    public:
        // typedef typename iterator<random_access_iterator_tag, T>::pointer               pointer;
        // typedef typename iterator<random_access_iterator_tag, T>::value_type            value_type;
        // typedef typename iterator<random_access_iterator_tag, T>::difference_type       difference_type;
        // typedef typename iterator<random_access_iterator_tag, T>::reference             reference;
        // typedef typename iterator<random_access_iterator_tag, T>::iterator_category     iterator_category;
        typedef T value_type;
        typedef T* pointer;
        typedef std::ptrdiff_t difference_type;
        typedef T& reference;
        typedef          size_t                                                         size_type;

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
            data_ = alloc_.allocate(1);
            capacity_ = 1;
        }

        explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
            : data_(nullptr), size_(0), capacity_(0), alloc_(alloc)
        {
            data_ = alloc_.allocate(n + 1);
            capacity_ = n + 1;
            size_ = n;

            for (size_type i = 0; i < size_; ++i)
            {
                data_[i] = val;
            }
        }

        vector(const vector &v)
            : data_(nullptr), size_(0), capacity_(0), alloc_(v.alloc_)
        {
            data_ = alloc_.allocate(v.size() + 1);
            size_ = v.size();
            capacity_ = v.size() + 1;

            std::memcpy(data_, v.data_, size_ * sizeof(T));
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
            return 1073741823;
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

        value_type *data()
        {
            return data_;
        }

        const value_type *data() const
        {
            return data_;
        }

        void push_back(const_reference value)
        {
            if (size_ >= capacity_)
            {
                realloc(capacity_ * 2);
            }
            data_[size_++] = value;
        }

        void pop_back()
        {
            --size_;
            data_[size_].~value_type();
        }

        void clear()
        {
            for (size_t i = 0; i < size_; i++)
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

    private:
        void realloc(size_type size)
        {
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