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
        
    };
}


#endif