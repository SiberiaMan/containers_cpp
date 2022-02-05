#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <cstdlib>
#include <iostream>

#include "iterator.hpp"
#include "type_traits.hpp"
#include "iterator_function.hpp"
#include "utils.hpp"

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
        typedef ft::normal_iterator<pointer, vector> iterator;
        typedef ft::normal_iterator<const_pointer, vector> const_iterator;
        typedef ft::reverse_iterator<iterator>   reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        size_t sz;
        size_t cap;
        pointer array;
    public:
        vector() : sz(0), cap(0), array(pointer()) {}

        explicit
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
            return iterator(array + sz);
        }

		const_iterator begin() const {
			return const_iterator(array);
		}

		const_iterator end() const {
			return const_iterator(array + sz);
		}

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        reference at(size_t n) {
            if (n >= sz)
                throw std::out_of_range("invalid position");
            return *(array + n);
        }

        const_reference at(size_t n) const {
            if (n >= sz)
                throw std::out_of_range("invalid position");
            return *(array + n);
        }

        reference operator[](size_t n) {
            return *(array + n);
        }

        const_reference operator[](size_t n) const {
            return *(array + n);
        }

        reference front() {
            return *array;
        }

        const_reference front() const {
            return *array;
        }

        reference back() {
            return *(array + sz - 1);
        }

        const_reference back() const {
            return *(array + sz - 1);
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
            //std::cout << "REALLOC" << std::endl;
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
                (array + sz)->~T();
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
            size_t prev_sz = sz;
			size_t cnt_from_head = pos - begin();
            size_t cnt_from_head_tmp = cnt_from_head;
            size_t cnt_from_tail = sz - cnt_from_head;

            sz += n;
            reserve(sz);

            for (size_t i = 0; cnt_from_tail > 0; ++i, --cnt_from_tail) {
                new(array + sz - i - 1) T(array[prev_sz - i - 1]);
            }
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
            size_t prev_sz = sz;
			size_t cnt_from_head = pos - begin();
			size_t cnt_from_head_tmp = cnt_from_head;
            size_t cnt_from_tail = sz - cnt_from_head;

            sz += static_cast<size_t>(n);
			reserve(sz);

			for (size_t i = 0; cnt_from_tail > 0; ++i, --cnt_from_tail) {
				new(array + sz - i - 1) T(array[prev_sz - i - 1]);
			}
			cnt_from_head_tmp = cnt_from_head;
            if (first.operator->() > (array + cnt_from_head)) {
                for (size_t i = 0; i < static_cast<size_t>(n); ++first, ++i) {
//                    std::cout << "========" << std::endl;
//                    std::cout << (array + cnt_from_head_tmp) << std::endl;
//                    std::cout << first.operator->() << std::endl;
//                    std::cout << "========" << std::endl;
                    new(array + cnt_from_head_tmp++) T(*first);
                }
            }
            else {
                first += (n - 1);
                cnt_from_head_tmp += (n - 1);
                for (size_t i = 0; i < static_cast<size_t>(n); --first, ++i) {
//                    std::cout << "========" << std::endl;
//                    std::cout << (array + cnt_from_head_tmp) << std::endl;
//                    std::cout << first.operator->() << std::endl;
//                    std::cout << "========" << std::endl;
                    new(array + cnt_from_head_tmp--) T(*first);
                }
            }
			return iterator(array + cnt_from_head);
		}

		/// ERASE

		iterator erase(const_iterator pos) {
			return erase(pos, pos + 1);
		}

		iterator erase(const_iterator first, const_iterator last) {
			typename const_iterator::difference_type n =
					ft::distance(first, last);
			size_t dist_to_first = first - begin();
			size_t dist_to_last = last - begin();
            size_t dist_to_first_tmp = dist_to_first;

			if (dist_to_first + n + 1 > sz) {
                resize(dist_to_first);
            }
			else {
				for (size_t i = 0; i < static_cast<size_t>(sz - n); ++i)
					new(array + dist_to_first_tmp++) T(*(array + dist_to_last++));
				sz -= n;
			}
			return iterator(array + dist_to_first);
		}

        void clear() {
            for (; sz > 0; --sz)
                (array + sz - 1)->~T();
        }

        size_t capacity() const {
            return cap;
        }

        size_t size() const {
            return sz;
        }

        bool empty() const {
            return (sz == 0);
        }

        void swap(vector<T> &other) {
            ft::swap(this->sz, other.sz);
            ft::swap(this->cap, other.cap);
            ft::swap(this->array, other.array);
            //ft::swap(this->sz, other.sz);
        }

        //size_t max_size() {} ALLOCATOR


        void print_vector() {
            for (size_t i = 0; i < this->sz; ++i)
                std::cout << this->array[i] << ' ';
            std::cout << std::endl;
        }
    };
}

#endif //CONTAINERS_VECTOR_HPP
