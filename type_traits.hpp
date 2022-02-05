#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {
    template<bool condition, typename U = void>
    struct enable_if {};

    template<typename U>
    struct enable_if<true, U> {
        typedef U value;
    };

    template<typename T, typename U>
    struct is_same_m {
        static const bool value = false;
    };

    template<typename T>
    struct is_same_m<T, T> {
        static const bool value = true;
    };

    template<typename T, typename U>
    struct is_same {
        static const bool value = is_same_m<T, U>::value;
    };

    template<typename T>
    struct is_integral {
        static const bool value = false;
    };

    template<>  struct is_integral<bool>            { static const bool value = true; };
    template<>  struct is_integral<char>            { static const bool value = true; };
    template<>  struct is_integral<signed char>     { static const bool value = true; };
    template<>  struct is_integral<unsigned char>   { static const bool value = true; };
    template<>  struct is_integral<wchar_t>         { static const bool value = true; };
    template<>  struct is_integral<short>           { static const bool value = true; };
    template<>  struct is_integral<unsigned short>  { static const bool value = true; };
    template<>  struct is_integral<int>             { static const bool value = true; };
    template<>  struct is_integral<unsigned int>    { static const bool value = true; };
    template<>  struct is_integral<long>            { static const bool value = true; };
    template<>  struct is_integral<unsigned long>   { static const bool value = true; };
}

#endif
