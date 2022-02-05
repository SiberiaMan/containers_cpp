#ifndef CONTAINERS_UTILS_HPP
#define CONTAINERS_UTILS_HPP
namespace ft {
    template<typename T>
    void swap(T &lhs, T &rhs) {
        T tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
}

#endif //CONTAINERS_UTILS_HPP
