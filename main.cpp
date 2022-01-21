#include<vector>
#include <iostream>
#include <complex>
#include "vector.hpp"

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
    for (typename ft::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}

int main() {
    std::cout << "-----first vector-----" << std::endl;
    ft::vector<int> v1;
    for (int i = 0; i < 10; i++) {
        std::cout << v1.size() << ' ' << v1.capacity() << std::endl;
        v1.push_back(i * i);
    }
    std::cout << "-----second vector-----" << std::endl;
    ft::vector<int> v2;
    for (int i = 0; i < 3; i++) {
        std::cout << v2.size() << ' ' << v2.capacity() << std::endl;
        v2.push_back(20 + i);
    }
    std::cout << "-----assign-----" << std::endl;
    ft::vector<int>::iterator it1 = v2.begin();
    ft::vector<int>::iterator it2 = v2.begin() + 1;
    v1.assign(it1, it2);
    print_vector(v1);


//    std::vector<int> v(130, 10);
//    v.push_back(10);
//    std::cout << v.size() << ' ' << v.capacity() << std::endl;
//    std::vector<int> v2(5);
//    for (int i = 0; i < 5; i++)
//        v2[i] = i * i;
//    std::vector<int>::iterator it1 = v2.begin();
//    std::vector<int>::iterator it2 = v2.begin() + 5;
//    //ft::vector<int> v3(it1, it2);
//    v.assign(it1, it2);
//    print_vector<int>(v);
//    std::cout << v.size() << ' ' << v.capacity() << std::endl;
}

