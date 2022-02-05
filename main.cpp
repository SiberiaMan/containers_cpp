#include<vector>
#include <iostream>
#include <complex>
#include "vector.hpp"
#include <cstdlib>
#include <algorithm>
#include <chrono>

struct S {
    int *arr;
    int value;
    S () {
        std::cout << "Created" << std::endl;
        arr = new int[10];
        value = 10;
    }

    ~S() {
        std::cout << "Destructed" << std::endl;
    }
};

template<typename T>
void print_vector(std::vector<T> &v) {
    //std::cout << v.size() << ' ' << v.capacity() << std::endl;
    for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}

template<typename T>
void print_vector(ft::vector<T> &v) {
    //std::cout << v.size() << ' ' << v.capacity() << std::endl;
    for (typename ft::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}


//int partition(std::vector<int> &v, int l, int r) {
//    int idx = l + rand() % (r - l);
//    int elem = v[idx];
//    int i = l - 1;
//    for (int j = l; j <= r; ++j)
//        if (v[j] <= elem) {
//            i += 1;
//            std::swap(v[i], v[j]);
//        }
//    //std::swap(v[i + 1], elem);
//    return i + 1;
//}

int partition(std::vector<int> &v, int l, int r) {
    int idx = l + rand() % (r - l);
    int elem = v[idx];
    while (l <= r) {
        while(v[l] < elem)
            ++l;
        while (v[r] > elem)
            --r;
        if (l >= r)
            break;
        std::swap(v[r--], v[l++]);
    }
    return r; // r points to elem that bigger or equal ELEM
}

void recursive_quicksort(std::vector<int> &v, int l, int r) {
    if (l < r) {
        int j = partition(v, l, r);
        recursive_quicksort(v, l, j);
        recursive_quicksort(v, j + 1, r);
    }
}

void iterative_quicksort(std::vector<int> &v, int l, int r) {
    std::vector<std::pair<int, int> > s;
    // [..]
    s.push_back(std::make_pair(0, v.size() - 1));
    while (!s.empty()) {
        std::pair<int,int> p = s.back();
        s.pop_back();
        int l = p.first, r = p.second;
        if (l < r) {
            int j = partition(v, l, r);
            s.push_back(std::make_pair(l, j));
            s.push_back(std::make_pair(j + 1, r));
        }
    }
}

void merge(std::vector<int> &v, int l, int r, int mid) {
    // [..)
    int i = 0, j = 0;
    std::vector<int> tmp(r - l);
    while (l + i < mid && mid + j < r) {
        if (v[l + i] < v[mid + j]) {
            tmp[i + j] = v[l + i];
            ++i;
        }
        else {
            tmp[i + j] = v[mid + j];
            ++j;
        }
    }
    while (l + i < mid) {
        tmp[i + j] = v[l + i];
        ++i;
    }
    while (mid + j < r) {
        tmp[i + j] = v[mid + j];
        ++j;
    }
    for (int i = 0; i < (r - l); ++i)
        v[l + i] = tmp[i];
}

void recursive_mergesort(std::vector<int> &v, int l, int r) {
    if (l + 1 < r) {
        int mid = (l + r) / 2;
        recursive_mergesort(v, l, mid);
        recursive_mergesort(v, mid, r);
        merge(v, l, r, (l + r) / 2);
    }
}

void iterative_mergesort(std::vector<int> &v, int l, int r) {
    int n = v.size();

    for (int cur_size = 1; cur_size <= n - 1; cur_size *= 2) {
        for (int l = 0; l < n; l += 2 * cur_size) {
            int mid = std::min(l + cur_size, n);
            int r = std::min(l + 2 * cur_size, n);
            merge(v, l, r, mid);
        }
    }
}

void check_iterative_merge_sort(std::vector<int> &v) {
    std::cout << "ITERATIVE_MERGESORT" << std::endl;
    iterative_mergesort(v, 0, v.size());
}

void check_recursive_merge_sort(std::vector<int> &v) {
    std::cout << "RECURSIVE_MERGESORT" << std::endl;
    recursive_mergesort(v, 0, v.size());
}

void check_iterative_quicksort(std::vector<int> &v) {
    std::cout << "ITERATIVE_QUICKSORT" << std::endl;
    iterative_quicksort(v, 0, v.size() - 1);
}

void check_recursive_quicksort(std::vector<int> &v) {
    std::cout << "RECURSIVE_QUICKSORT" << std::endl;
    recursive_quicksort(v, 0, v.size() - 1);
}

int main() {
    srand(time(0));
    std::vector<int> v;
    for (int i = 0; i < 1000000; i++)
        v.push_back(rand() % 23451);
    //print_vector(v);
    void (*f[4])(std::vector<int> &v) = {&check_iterative_merge_sort,
                                         &check_recursive_merge_sort,
                                         &check_iterative_quicksort,
                                         &check_recursive_quicksort};
    int n; std::cin >> n;
    auto begin = std::chrono::steady_clock::now();
    f[n](v);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    for (int i = 0; i < v.size() - 1; ++i)
        if (v[i] > v[i + 1]) {
            std::cout << "NO" << std::endl;
            break;
        }
    //print_vector(v);
}

