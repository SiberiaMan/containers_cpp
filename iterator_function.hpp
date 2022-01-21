#ifndef ITERATOR_FUNCTION_HPP
#define ITERATOR_FUNCTION_HPP

#include "iterator_traits.hpp"

namespace ft {
    template<typename InputIterator>
    inline typename ft::iterator_traits<InputIterator>::difference_type
    _distance(InputIterator first, InputIterator last, input_iterator_tag) {
        typename ft::iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last) {
            ++first;
            ++n;
        }
        return n;
    }

    template<typename RandomAccessIterator>
    inline typename ft::iterator_traits<RandomAccessIterator>::difference_type
    _distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
        return last - first;
    }

    template<typename InputIterator>
    inline typename ft::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last) {
        return ft::_distance(first, last,
         typename ft::iterator_traits<InputIterator>::iterator_category());
    }
}

#endif //ITERATOR_FUNCTION_HPP
