#ifndef CONTAINERS_NORMAL_ITERATOR_HPP
#define CONTAINERS_NORMAL_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "type_traits.hpp"

namespace ft {
    template<typename Iterator>
    class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
            typename iterator_traits<Iterator>::value_type,
            typename iterator_traits<Iterator>::difference_type,
            typename iterator_traits<Iterator>::pointer,
            typename iterator_traits<Iterator>::reference> {
    protected:
        Iterator it;

        typedef iterator_traits<Iterator>   traits_type;
    public:
        typedef Iterator            iterator_type;
        typedef typename traits_type::difference_type difference_type;
        typedef typename traits_type::pointer pointer;
        typedef typename traits_type::reference reference;


        reverse_iterator() : it() {}

        explicit
        reverse_iterator(const iterator_type &_it) : it(_it) {}

        reverse_iterator(const reverse_iterator &_it) : it(_it.base()) {}

        template<typename Iter>
        reverse_iterator(const reverse_iterator<Iter> &_it) : it(_it.base()) {}

        ~reverse_iterator() { }

        reference
        operator *() const {
            iterator_type tmp = it;
            return *(--tmp);
        }

        pointer
        operator->() const {
            iterator_type tmp = it;
            return (--tmp).operator->();
        }

        reverse_iterator&
        operator++() {
            --it;
            return *this;
        }

        reverse_iterator
        operator++(int) {
            return reverse_iterator(it--);
        }

        reverse_iterator&
        operator--() {
            ++it;
            return *this;
        }

        reverse_iterator
        operator--(int) {
            return reverse_iterator(it++);
        }

        reverse_iterator
        operator+(difference_type n) const {
            return reverse_iterator(it - n);
        }

        reverse_iterator&
        operator+=(difference_type n) {
            it -= n;
            return *this;
        }

        reverse_iterator
        operator-(difference_type n) const {
            return reverse_iterator(it + n);
        }

        reverse_iterator&
        operator-=(difference_type n) {
            it += n;
            return *this;
        }

        reference
        operator[](difference_type n) const {
            return *(*this + n);
        }

        iterator_type
        base() const {
            return it;
        }

    };

    template<typename Iterator>
    inline bool
    operator==(const reverse_iterator<Iterator>& x,
               const reverse_iterator<Iterator>& y)
    { return x.base() == y.base(); }

    template<typename Iterator>
    inline bool
    operator<(const reverse_iterator<Iterator>& x,
              const reverse_iterator<Iterator>& y)
    { return y.base() < x.base(); }

    template<typename Iterator>
    inline bool
    operator!=(const reverse_iterator<Iterator>& x,
               const reverse_iterator<Iterator>& y)
    { return !(x == y); }

    template<typename Iterator>
    inline bool
    operator>(const reverse_iterator<Iterator>& x,
              const reverse_iterator<Iterator>& y)
    { return y < x; }

    template<typename Iterator>
    inline bool
    operator<=(const reverse_iterator<Iterator>& x,
               const reverse_iterator<Iterator>& y)
    { return !(y < x); }

    template<typename Iterator>
    inline bool
    operator>=(const reverse_iterator<Iterator>& x,
               const reverse_iterator<Iterator>& y)
    { return !(x < y); }


    template<typename IteratorL, typename IteratorR>
    inline bool
    operator==(const reverse_iterator<IteratorL>& x,
               const reverse_iterator<IteratorR>& y)
    { return x.base() == y.base(); }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator<(const reverse_iterator<IteratorL>& x,
              const reverse_iterator<IteratorR>& y)
    { return y.base() < x.base(); }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator!=(const reverse_iterator<IteratorL>& x,
               const reverse_iterator<IteratorR>& y)
    { return !(x == y); }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator>(const reverse_iterator<IteratorL>& x,
              const reverse_iterator<IteratorR>& y)
    { return y < x; }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator<=(const reverse_iterator<IteratorL>& x,
               const reverse_iterator<IteratorR>& y)
    { return !(y < x); }

    template<typename IteratorL, typename IteratorR>
    inline bool
    operator>=(const reverse_iterator<IteratorL>& x,
               const reverse_iterator<IteratorR>& y)
    { return !(x < y); }


    template<typename Iterator>
    inline typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator>& x,
              const reverse_iterator<Iterator>& y)
    { return y.base() - x.base(); }

    template<typename IteratorL, typename IteratorR>
    inline typename reverse_iterator<IteratorL>::difference_type
    operator-(const reverse_iterator<IteratorL>& x,
              const reverse_iterator<IteratorR>& y)
    { return y.base() - x.base(); }


    template<typename Iterator>
    inline reverse_iterator<Iterator>
    operator+(typename reverse_iterator<Iterator>::difference_type n,
              const reverse_iterator<Iterator>& x)
    { return reverse_iterator<Iterator>(x.base() - n); }

    template<typename Iterator, typename Container>
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

        explicit normal_iterator(const Iterator &it) : ptr_current(it) {}

        template<typename Iter>
        normal_iterator(const normal_iterator<Iter,
        typename ft::enable_if<(ft::is_same<Iter, typename Container::pointer>::value),
                Container>::value> &it) : ptr_current(it.base()) {}

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

    template<typename Iterator, typename Container>
    inline bool
    operator==(const normal_iterator<Iterator, Container> &lhs,
            const normal_iterator<Iterator, Container> &rhs) {
        return lhs.base() == rhs.base();
    }

    // const and non-const
    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator==(const normal_iterator<IteratorL, Container> &lhs,
               const normal_iterator<IteratorR, Container> &rhs) {
        return lhs.base() == rhs.base();
    }

    template<typename Iterator, typename Container>
    inline bool
    operator!=(const normal_iterator<Iterator, Container> &lhs,
               const normal_iterator<Iterator, Container> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator!=(const normal_iterator<IteratorL, Container> &lhs,
               const normal_iterator<IteratorR, Container> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<typename Iterator, typename Container>
    inline bool
    operator<(const normal_iterator<Iterator, Container> &lhs,
               const normal_iterator<Iterator, Container> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator<(const normal_iterator<IteratorL, Container> &lhs,
               const normal_iterator<IteratorR, Container> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<typename Iterator, typename Container>
    inline bool
    operator<=(const normal_iterator<Iterator, Container> &lhs,
              const normal_iterator<Iterator, Container> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator<=(const normal_iterator<IteratorL, Container> &lhs,
              const normal_iterator<IteratorR, Container> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<typename Iterator, typename Container>
    inline bool
    operator>(const normal_iterator<Iterator, Container> &lhs,
              const normal_iterator<Iterator, Container> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator>(const normal_iterator<IteratorL, Container> &lhs,
              const normal_iterator<IteratorR, Container> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<typename Iterator, typename Container>
    inline bool
    operator>=(const normal_iterator<Iterator, Container> &lhs,
               const normal_iterator<Iterator, Container> &rhs) {
        return lhs.base() >= rhs.base();
    }

    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator>=(const normal_iterator<IteratorL, Container> &lhs,
               const normal_iterator<IteratorR, Container> &rhs) {
        return lhs.base() >= rhs.base();
    }

    template<typename IteratorL, typename IteratorR, typename Container>
    inline typename normal_iterator<IteratorL, Container>::difference_type
    operator-(const normal_iterator<IteratorL, Container> &lhs,
              const normal_iterator<IteratorR, Container> &rhs) {
        return lhs.base() - rhs.base();
    }

    template<typename Iterator, typename Container>
    inline typename normal_iterator<Iterator, Container>::difference_type
    operator-(const normal_iterator<Iterator, Container> &lhs,
            const normal_iterator<Iterator, Container> &rhs) {
        return lhs.base() - rhs.base();
    }

    template<typename Iterator, typename Container>
    inline normal_iterator<Iterator, Container>
    operator+(typename normal_iterator<Iterator, Container>::difference_type n,
            const normal_iterator<Iterator, Container> &rhs) {
        return normal_iterator<Iterator, Container>(rhs.base() + n);
    }
}


#endif //CONTAINERS_NORMAL_ITERATOR_HPP
