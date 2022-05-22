#include "vector.h"

namespace ft {
    template <class T, class Container = vector<T>>
    class stack
    {
    public:
        typedef T           value_type;
        typedef size_t      size_type;
        typedef Container   container_type;

        explicit stack(const container_type &ctnr = container_type())
            : container_(ctnr)
        {
        }

        bool empty() const
        {
            return container_.empty();
        }

        size_type size() const
        {
            return container_.size();
        }

        value_type &top()
        {
            return container_.back();
        }

        const value_type &top() const
        {
            return container_.back();
        }

        void push(const value_type &val)
        {
            container_.push_back(val);
        }

        void pop()
        {
            container_.pop_back();
        }

    private:
        container_type container_;
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.container_ == rhs.container_;
    }
    
    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.container_ != rhs.container_;
    }
    
    template <class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.container_ < rhs.container_;
    }
    
    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.container_ <= rhs.container_;
    }
    
    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.container_ > rhs.container_;
    }
    
    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.container_ >= rhs.container_;
    }
}