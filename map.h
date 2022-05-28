#ifndef MAP_H
#define MAP_H

#include <algorithm>

namespace ft {

    template<class K, class V>
    struct pair
    {
        typedef K first_type;
        typedef V second_type;
        K first;
        V second;
        pair(first_type k, second_type v) : first(k), second(v) {}

        template <class U, class W>
        pair(const pair<U, W> &pr) : first(pr.first), second(pr.second) {}
    };

    template <class T, class U>
    pair<T, U> make_pair(T t, U u)
    {
        return pair<T, U>(t, u);
    }

    template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
    class map {
    public:
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef pair<const key_type, mapped_type>       value_type;
        typedef Compare                                 key_compare;
        typedef Allocator                               allocator_type;
        typedef allocator_type::reference               reference;
        typedef allocator_type::const_reference         const_reference;
        typedef allocator_type::pointer                 pointer;
        typedef allocator_type::const_pointer           const_pointer;
        typedef size_t                                  size_type;

        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            : alloc_(alloc)
            , comp_(comp)
            , root(nullptr)
        {

        }



    private:

        allocator_type  alloc_;
        key_compare     comp_;
    };
}


#endif