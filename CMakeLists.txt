cmake_minimum_required(VERSION 3.21)
project(21_containers)

set(CMAKE_CXX_STANDARD 11)

add_executable(21_containers main.cpp iterator.hpp iterator_traits.hpp vector.hpp
        type_traits.hpp iterator_function.hpp)
