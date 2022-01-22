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
            assign(n, val);
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
            return const_iterator(array + sz);
        }

		const_iterator cbegin() {
			return const_iterator(array);
		}

		const_iterator cend() {
			return const_iterator(array + sz);
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


		/// ASSIGN


        void assign(size_t n, const T &value) {
			reserve(n);
			sz = n;
			for (size_t i = 0; i < sz; i++)
				new(array + i) T(value);
        }

        template<typename Iterator>
        void assign (Iterator first, Iterator last,
                     typename ft::enable_if<!ft::is_integral<Iterator>::value>::value* = NULL) {
            typename ft::iterator_traits<Iterator>::difference_type n =
                    ft::distance(first, last);
			reserve(n);
			sz = n;
            for (size_t i = 0; i < n; ++first, ++i)
                new(array + i)  T(*first);
        }


		/// INSERT


		iterator insert(const iterator &pos, const T &value) {
			return insert(pos, 1, value);
		}

		iterator insert(const iterator &pos, size_t n, const T &value) {
			size_t new_cap = sz + n;
			size_t cnt_from_head = pos - begin();
			size_t cnt_from_head_tmp = cnt_from_head;

			reserve(new_cap);
			for (size_t i = 0; i < n; ++i) {
				new(array + sz) T(array[cnt_from_head_tmp++]);
				sz++;
			}
			cnt_from_head_tmp = cnt_from_head;
			for (size_t i = 0; i < n; ++i) {
				new(array + cnt_from_head_tmp++) T(value);
			}
			return iterator(array + cnt_from_head);
		}

		template<typename Iterator>
		iterator insert(const iterator &pos, Iterator first, Iterator last,
						typename ft::enable_if<!ft::is_integral<Iterator>::value>::value* = NULL) {
			typename ft::iterator_traits<Iterator>::difference_type n =
					ft::distance(first, last);
			size_t new_cap = sz + static_cast<size_t>(n);
			size_t cnt_from_head = pos - begin();
			size_t cnt_from_head_tmp = cnt_from_head;

			reserve(new_cap);
			for (size_t i = 0; i < static_cast<size_t>(n); ++i) {
				new(array + sz) T(array[cnt_from_head_tmp++]);
				sz++;
			}
			cnt_from_head_tmp = cnt_from_head;
			for (size_t i = 0; i < static_cast<size_t>(n); ++first, ++i) {
				new(array + cnt_from_head_tmp++) T(*first);
			}
			return iterator(array + cnt_from_head);
		}

		/// ERASE

//		iterator erase(const_iterator pos) {
//			return erase(pos, pos + 1);
//		}

		iterator erase(const_iterator first, const_iterator last) {
			typename const_iterator::difference_type n =
					ft::distance(first, last);
			size_t dist_to_first = first - begin();
			size_t dist_to_last = last - begin();

			if (dist_to_first + n + 1 > sz)
				resize(dist_to_first);
			else {
				for (size_t i = 0; i < static_cast<size_t>(sz - n); ++i)
					new(array + dist_to_first++) T(*(array + dist_to_last++));
				sz -= n;
			}
			return iterator();
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
