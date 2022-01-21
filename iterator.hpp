#ifndef CONTAINERS_NORMAL_ITERATOR_HPP
#define CONTAINERS_NORMAL_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
    /// T is pointer (const or non-const)
    template<typename Iterator>
    class normal_iterator {
    private:
        Iterator ptr_current;

        typedef ft::iterator_traits<Iterator>  traits_type;
    public:
        typedef typename traits_type::iterator_category iterator_category;
        typedef typename traits_type::value_type value_type;
        typedef typename traits_type::difference_type difference_type;
        typedef typename traits_type::reference reference;
        typedef typename traits_type::pointer pointer;

        normal_iterator() : ptr_current(Iterator()) {}

        normal_iterator(const Iterator &it) : ptr_current(it) {}

        /// missed permission to const_iterator conversion

        ~normal_iterator() {}

        // Forward iterator requirements
        reference
        operator *() const {
            return *ptr_current;
        }

        pointer
        operator->() const {
            return ptr_current;
        }

        normal_iterator&
        operator++() {
            ptr_current++;
            return *this;
        }

        normal_iterator
        operator++(int) {
            return normal_iterator(ptr_current++);
        }

        // Bidirectional iterator requirements
        normal_iterator&
        operator--() {
            ptr_current--;
            return *this;
        }

        normal_iterator
        operator--(int) {
            return normal_iterator(ptr_current--);
        }

        // Random access iterator requirements
        reference
        operator[](difference_type n) const {
            return ptr_current[n];
        }

        normal_iterator&
        operator+=(difference_type n) {
            ptr_current += n;
            return *this;
        }

        normal_iterator
        operator+(difference_type n) const {
            return normal_iterator(ptr_current + n);
        }

        normal_iterator&
        operator-=(difference_type n) {
            ptr_current -= n;
            return *this;
        }

        normal_iterator
        operator-(difference_type n) const {
            return normal_iterator(ptr_current - n);
        }

        const Iterator&
        base() const {
            return ptr_current;
        }
    };

    template<typename Iterator>
    inline bool
    operator==(const normal_iterator<Iterator> &lhs,
            const normal_iterator<Iterator> &rhs) {
        return lhs.base() == rhs.base();
    }

    // const and non-const
    template<typename IteratorL, typename IteratorR>
    inline bool
    operator==(const normal_iterator<IteratorL> &lhs,
               const normal_iterator<IteratorR> &rhs) {
        return lhs.base() == rhs.base();
    }

    template<typename Iterator>
    inline bool
    operator!=(const normal_iterator<Iterator> &lhs,
               const normal_iterator<Iterator> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator!=(const normal_iterator<IteratorL> &lhs,
               const normal_iterator<IteratorR> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<typename Iterator>
    inline bool
    operator<(const normal_iterator<Iterator> &lhs,
               const normal_iterator<Iterator> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator<(const normal_iterator<IteratorL> &lhs,
               const normal_iterator<IteratorR> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<typename Iterator>
    inline bool
    operator<=(const normal_iterator<Iterator> &lhs,
              const normal_iterator<Iterator> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator<=(const normal_iterator<IteratorL> &lhs,
              const normal_iterator<IteratorR> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<typename Iterator>
    inline bool
    operator>(const normal_iterator<Iterator> &lhs,
              const normal_iterator<Iterator> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator>(const normal_iterator<IteratorL> &lhs,
              const normal_iterator<IteratorR> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<typename Iterator>
    inline bool
    operator>=(const normal_iterator<Iterator> &lhs,
               const normal_iterator<Iterator> &rhs) {
        return lhs.base() >= rhs.base();
    }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator>=(const normal_iterator<IteratorL> &lhs,
               const normal_iterator<IteratorR> &rhs) {
        return lhs.base() >= rhs.base();
    }

    template<typename IteratorL, typename IteratorR>
    inline typename normal_iterator<IteratorL>::difference_type
    operator-(const normal_iterator<IteratorL> &lhs,
              const normal_iterator<IteratorR> &rhs) {
        return lhs.base() - rhs.base();
    }

    template<typename Iterator>
    inline typename normal_iterator<Iterator>::difference_type
    operator-(const normal_iterator<Iterator> &lhs,
            const normal_iterator<Iterator> &rhs) {
        return lhs.base() - rhs.base();
    }

    template<typename Iterator>
    inline normal_iterator<Iterator>
    operator+(typename normal_iterator<Iterator>::difference_type n,
            const normal_iterator<Iterator> &rhs) {
        return normal_iterator<Iterator>(rhs.base() + n);
    }
}


#endif //CONTAINERS_NORMAL_ITERATOR_HPP
