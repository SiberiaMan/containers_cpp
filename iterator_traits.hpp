#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

#include <cstddef>

namespace ft {
    struct input_iterator_tag {};

    struct output_iterator_tag {}; /// not used in project

    struct forward_iterator_tag : public input_iterator_tag {};

    struct bidirectional_iterator_tag : public forward_iterator_tag {};

    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<typename Category, typename T, typename Distance = ptrdiff_t,
            typename Pointer = T*, typename Reference = T&>
    struct iterator {
        typedef Category iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
    }; /// ????

    template<typename Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

    /// Partial specialization for pointer types

    template<typename T>
    struct iterator_traits<T*> {
        typedef random_access_iterator_tag iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    /// Partial specialization for const pointer types

    template<typename T>
    struct iterator_traits<const T*> {
        typedef random_access_iterator_tag iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };
} // namespace

#endif //ITERATOR_TRAITS_H
