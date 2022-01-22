#include<vector>
#include <iostream>
#include <complex>
#include "vector.hpp"
#include <cstdlib>

struct S {
    int *arr;
    S () {
        std::cout << "Created" << std::endl;
        arr = new int[10];
    }
};

template<typename T>
void print_vector(std::vector<T> &v) {
    std::cout << v.size() << ' ' << v.capacity() << std::endl;
    for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}

template<typename T>
void print_vector(ft::vector<T> &v) {
    std::cout << v.size() << ' ' << v.capacity() << std::endl;
    for (typename ft::vector<T>::const_iterator it = v.cbegin(); it != v.cend(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}

int main() {
	ft::vector<int> v1(5, 1);
	v1.erase(v1.cend() - 1, v1.cend());
	print_vector(v1);
}

