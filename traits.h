#ifndef TRAITS_H

#include <iterator>

namespace ft {

    template <bool, typename T = void>
    struct enable_if
    {
    };

    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template<class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category      iterator_category;
        typedef typename Iterator::value_type             value_type;
        typedef typename Iterator::difference_type        difference_type;
        typedef typename Iterator::difference_type        distance_type;
        typedef typename Iterator::pointer                pointer;
        typedef typename Iterator::reference              reference;
    };

    template<class T>
    struct iterator_traits<T*>
    {
        typedef std::random_access_iterator_tag     iterator_category;
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef std::ptrdiff_t                      difference_type;
        typedef T&                                  reference;
        typedef size_t                              size_type;
    };

    template<class T>
    struct iterator_traits<const T*>
    {
        typedef std::random_access_iterator_tag     iterator_category;
        typedef const T                             value_type;
        typedef const T*                            pointer;
        typedef std::ptrdiff_t                      difference_type;
        typedef const T&                            reference;
        typedef size_t                              size_type;
    };

    template <class T, class U>
    struct is_same
    {
        static const bool value = false;
    };

    template <class T>
    struct is_same<T, T>
    {
        static const bool value = true;
    };

    template <class T>
    typename iterator_traits<T>::difference_type distance(T begin, T end)
    {
        typedef iterator_traits<T> Traits;

        if (is_same<typename Traits::iterator_category, typename std::random_access_iterator_tag>::value) {
            return end - begin;
        }
        else {
            typename Traits::difference_type dist = 0;
            for (; begin != end; ++begin)
            {
                ++dist;
            }
            return dist;
        }
    };

    template <class T>
    struct is_integral {
        static const bool value = false;
    };

    template <>
    struct is_integral<bool> {
        static const bool value = true;
    };

    template <>
    struct is_integral<char> {
        static const bool value = true;
    };

    template <>
    struct is_integral<short> {
        static const bool value = true;
    };

    template <>
    struct is_integral<int> {
        static const bool value = true;
    };

    template <>
    struct is_integral<long> {
        static const bool value = true;
    };

    template <>
    struct is_integral<long long> {
        static const bool value = true;
    };

    template <class T>
    const T& max(const T& v1, const T& v2) {
        return (v1 > v2) ? v1 : v2;
    };

} // ft

#endif