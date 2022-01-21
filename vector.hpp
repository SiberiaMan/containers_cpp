#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <cstdlib>
#include <iostream>

#include "iterator.hpp"
#include "type_traits.hpp"
#include "iterator_function.hpp"

namespace ft {
    template<typename T>
    class vector {
    public:
        // alloc traits
        typedef T           value_type;
        typedef T*          pointer;
        typedef T&      reference;
        typedef const T* const_pointer;
        typedef const T& const_reference;
        typedef ft::normal_iterator<pointer> iterator;
        typedef ft::normal_iterator<const_pointer> const_iterator;

    private:
        size_t sz;
        size_t cap;
        pointer array;
    public:
        vector() : sz(0), cap(0), array(pointer()) {}

        vector(size_t n, const T &val = T()) : sz(0), cap(0), array(pointer()) {
            resize(n, val);
        }

        template<typename Iterator>
        vector(Iterator first, Iterator last,
               typename ft::enable_if<!ft::is_integral<Iterator>::value>::value* = NULL) :
               sz(0), cap(0), array(pointer()){
            assign(first, last);
        }

        ~vector() {
            for (size_t i = 0; i < sz; ++i) {
                (array + i)->~T();
            }
            delete [] reinterpret_cast<char*>(array);
        }

        iterator begin() {
            return iterator(array);
        }

        iterator end() {
            return iterator(array + sz);
        }

        // unsafe method for my implementation
        void reserve(size_t new_capacity) {
            if (new_capacity <= cap)
                return;
            T *new_ptr = reinterpret_cast<T*>(new char[sizeof(T) * new_capacity]);
            for (size_t i = 0; i < sz; ++i)
                // placement new
                new(new_ptr + i) T(array[i]);
            for (size_t i = 0; i < sz; ++i)
                (array + i)->~T();
            delete [] reinterpret_cast<char*>(array);
            array = new_ptr;
            cap = new_capacity;
        }

        void resize(size_t new_size, const T& value = T()) {
            if (new_size <= sz) {
                sz = new_size; // weak, upd: norm
            }
            else {
                reserve(new_size);
                for (; sz != new_size; ++sz)
                    new(array + sz) T(value);
            }
        }

        void push_back(const T &val) {
            size_t new_size = sz + 1;
            if (sz == cap) {
                cap = cap == 0 ? 1 : cap;
                reserve(2 * cap);
            }
            new(array + sz) T(val);
            sz = new_size;
        }

        void pop_back() {
            if (sz) {
                --sz;
            }
        }

        void assign(size_t n, const T &value) {
            resize(n, value);
        }

        template<typename Iterator>
        void assign (Iterator first, Iterator last,
                     typename ft::enable_if<!ft::is_integral<Iterator>::value>::value* = NULL) {
            typename ft::iterator_traits<Iterator>::difference_type n =
                    ft::distance(first, last);
            resize(n);
            for (size_t i = 0; first != last; ++first, ++i)
                new(array + i)  T(*first);
        }

        size_t capacity() const {
            return cap;
        }

        size_t size() const {
            return sz;
        }

        void print_vector() {
            for (size_t i = 0; i < this->sz; ++i)
                std::cout << this->array[i] << ' ';
            std::cout << std::endl;
        }
    };
}

#endif //CONTAINERS_VECTOR_HPP
