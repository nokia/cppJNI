#pragma once

namespace cppjni
{
namespace concepts
{
    /*
     * Compile time string type heavily inspired by https://github.com/irrequietus/typestring - but completely
     * rewritten due to compilation time problems with very long strings : ).
     * 
     * This header exposes three entities:
     *  - string_type<...> template
     *  - string_type_is macro for generating string_type from string literal (normally not possible in current C++ version)
     *  - concatenate algorithm for string concatenation
     * 
     * This implementation heavily uses Odin Holmes articles about compilation speed (check http://odinthenerd.blogspot.com/) in case of compiler that
     * lacks gnu-string-literal-operator-template.
     *
     * This code internals are still experimental, but externally it's fully usable.
     *
     * Usage:
     * ```c++
     * using str_t = string_type_is("qwe123");
     * using next_str_t = string_type_is("asd456")
     * static_assert("", std::is_same<cppjni::concepts::concatenate<str_t, next_str_t>, string_type_is("qwe123asd456")>::value);
     * ```
     */
    template<char... C>
    struct string_type final
    {
    public:
        static constexpr const char* data() noexcept
        {
            return &characters[0];
        }
    private:
        static constexpr char characters[sizeof...(C) + 1] = {C..., '\x00'};
    };

    template<char... C>
    constexpr char string_type<C...>::characters[sizeof...(C) + 1];

    namespace detail
    {
        template<typename A, typename... Ts>
        struct concatenate_impl;

        template<char... A>
        struct concatenate_impl<string_type<A...>>
        {
            using type = string_type<A...>;
        };


        template<char... A, char... B, typename... Ts>
        struct concatenate_impl<string_type<A...>, string_type<B...>, Ts...>
        {
            using type = typename concatenate_impl<string_type<A..., B...>, Ts...>::type;
        };

        template<char... A, char... B, char... C, char... D, typename... Ts>
        struct concatenate_impl<string_type<A...>, string_type<B...>, string_type<C...>, string_type<D...>, Ts...>
        {
            using type = typename concatenate_impl<string_type<A..., B..., C..., D...>, Ts...>::type;
        };
    }

    template<typename... T>
    using concatenate = typename detail::concatenate_impl<T...>::type;

//For compilers that has support for gnu-string-literal-operator-template
#if not defined _MSC_VER
    //ugly, but necessary: we need to declare this operator in global scope unfortunately, since it would not work with macro
}
}

template<typename T, T... C>
constexpr cppjni::concepts::string_type<C...> operator"" _string_type()
{
    return {};
}

#define string_type_is(x) decltype( x##_string_type)

namespace cppjni
{
namespace concepts
{
#else //if not defined _MSC_VER
    
    namespace detail
    {
        //character grabber function
        constexpr char getChar(const char c[], unsigned size, int charIndex) noexcept
        {
            return N < size ? c[const] : '\x00';
        }

        //meta recursive list
        template<typename Head, typename Tail>
        struct rlist
        {};

        //concatenation of recursive list of characters
        template<typename T>
        struct concatenate_impl_rec;

        template<char... A>
        struct concatenate_impl_rec<string_type<A...>>
        {
            using type = string_type<A...>;
        };

        template<char... A>
        struct concatenate_impl_rec<rlist<string_type<A...>, string_type<>>>
        {
            using type = string_type<A...>;
        };

        template<char... A, char... B>
        struct concatenate_impl_rec<rlist<string_type<A...>, rlist<string_type<B...>, string_type<>>>>
        {
            using type = string_type<A..., B...>;
        };
        template<char... A, char... B, char... C>
        struct concatenate_impl_rec<
                        rlist<
                            string_type<A...>, 
                            rlist<
                                string_type<B...>, 
                                rlist<
                                    string_type<C...>,
                                    string_type<>
                                >
                            >
                        >
                    >
        {
            using type = string_type<A..., B..., C...>;
        };

        template<char... A, char... B, char... C, char... D, typename T>
        struct concatenate_impl_rec<
                    rlist<
                        string_type<A...>, 
                        rlist<
                            string_type<B...>, 
                            rlist<
                                string_type<C...>,
                                rlist<
                                    string_type<D...>,
                                    T
                                >
                            >
                        >
                    >
                >
        {
            using type = 
                typename concatenate_impl_rec<
                    rlist<
                        string_type<A..., B..., C..., D...>, 
                        typename concatenate_impl_rec<T>::type
                    >
                >::type;
        };

        template<char... A, char... B, char... C, char... D, char... E, char... F, char... G, char... H, typename T>
        struct concatenate_impl_rec<
                    rlist<
                        string_type<A...>, 
                        rlist<
                            string_type<B...>, 
                            rlist<
                                string_type<C...>,
                                rlist<
                                    string_type<D...>,
                                    rlist<
                                        string_type<E...>,
                                        rlist<
                                            string_type<F...>,
                                            rlist<
                                                string_type<G...>,
                                                rlist<
                                                    string_type<H...>,
                                                    T
                                                >
                                            >
                                        >
                                    >
                                >
                            >
                        >
                    >
                >
        {
            using type = 
                typename concatenate_impl_rec<
                    rlist<
                        string_type<A..., B..., C..., D..., E..., F..., G..., H...>, 
                        typename concatenate_impl_rec<T>::type
                    >
                >::type;
        };

        template<>
        struct concatenate_impl_rec<string_type<>>
        {
            using type = string_type<>;
        };

        /* Filtering null character strings using fast tracking pattern matching */
        template<unsigned>
        struct filterNulls;

        template<>
        struct filterNulls<1>
        {
            template<char X1>
            struct f
            {
                using type = string_type<X1>;
            };
        };
        
        template<>
        struct filterNulls<1>
                ::f<'\x00'>
        {
            using type = string_type<>;
        };

        template<>
        struct filterNulls<2>
        {
            template<char X1, char X2, char X3, char X4>
            struct f
            {
                using type = string_type<X1, X2, X3, X4>;
            };
            
            template<char X1>
            struct f<X1, '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1>;
            };
            template<char X1, char X2>
            struct f<X1, X2, '\x00', '\x00'>
            {
                using type = string_type<X1, X2>;
            };
            template<char X1, char X2, char X3>
            struct f<X1, X2, X3, '\x00'>
            {
                using type = string_type<X1, X2, X3>;
            };
        };

        template<>
        struct filterNulls<2>
                ::f<'\x00', '\x00', '\x00', '\x00'>
        {
            using type = string_type<>;
        };

        template<>
        struct filterNulls<3>
        {
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8, char X9, char X10, char X11, char X12, char X13, char X14, char X15, char X16>
            struct f
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16>;
            };
            
            template<char X1>
            struct f<X1, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1>;
            };
            template<char X1, char X2>
            struct f<X1, X2, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2>;
            };
            template<char X1, char X2, char X3>
            struct f<X1, X2, X3, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3>;
            };
            template<char X1, char X2, char X3, char X4>
            struct f<X1, X2, X3, X4, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4>;
            };
            template<char X1, char X2, char X3, char X4, char X5>
            struct f<X1, X2, X3, X4, X5, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6>
            struct f<X1, X2, X3, X4, X5, X6, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7>
            struct f<X1, X2, X3, X4, X5, X6, X7, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8>
            struct f<X1, X2, X3, X4, X5, X6, X7, X8, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7, X8>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8, char X9>
            struct f<X1, X2, X3, X4, X5, X6, X7, X8, X9, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7, X8, X9>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8, char X9, char X10>
            struct f<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8, char X9, char X10, char X11>
            struct f<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, '\x00', '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8, char X9, char X10, char X11, char X12>
            struct f<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, '\x00', '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8, char X9, char X10, char X11, char X12, char X13>
            struct f<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, '\x00', '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8, char X9, char X10, char X11, char X12, char X13, char X14>
            struct f<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, '\x00', '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14>;
            };
            template<char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8, char X9, char X10, char X11, char X12, char X13, char X14, char X15>
            struct f<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, '\x00'>
            {
                using type = string_type<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15>;
            };
        };
        template<>
        struct filterNulls<3>
                ::f<'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'>
        {
            using type = string_type<>;
        };

        //size of string to template overload mapping for fast tracking
        constexpr unsigned selectLevel(unsigned size)
        {
            return
                size == 0
                    ? 0
                    : size < 4
                        ? 1
                        : size < 16
                            ? 2
                            : 3;
        }
        
        //wrapper of selectLevel, used when we want to detect quickly end-of-string
        constexpr unsigned levelForEoS(char x, unsigned size)
        {
            return x == '\x00'? 0 : selectLevel(size);
        }
        
        /* 
         * Filter all nulls algorithm using fast tracking aliases.
         * This algorithm (thanks to helper constexpr functions) stops quickly when it finds portion of string that starts with '\0'. This helps
         * greatly with dealing with strings that are potentially very long, but usually are not.
         */
        template<unsigned>
        struct filterAllNulls;

        template<>
        struct filterAllNulls<0>
        {
            template<char... T>
            using f = string_type<>;
        };

        template<>
        struct filterAllNulls<1>
        {
            template<char X, char... Ts>
            using f = 
                rlist<
                    typename filterNulls<1>::template f<X>::type, 
                    typename filterAllNulls<
                        levelForEoS(X, sizeof...(Ts))
                    >::template f<
                        Ts...
                    >
                >;
        };

        template<>
        struct filterAllNulls<2>
        {
            template<char X1, char X2, char X3, char X4, char... Ts>
            using f =
                rlist<
                    typename filterNulls<2>::template f<X1, X2, X3, X4>::type,
                    typename filterAllNulls<
                        levelForEoS(X4, sizeof...(Ts))
                    >::template f<
                        Ts...
                    >
                >;
        };

        template<>
        struct filterAllNulls<3>
        {
            template<
                char X1, char X2, char X3, char X4, char X5, char X6, char X7, char X8, char X9, char X10, char X11, char X12, char X13, char X14, char X15, char X16,
                char... Ts
            >
            using f = 
                rlist<
                    typename filterNulls<3>::template f<X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16>::type,
                    typename filterAllNulls<
                        levelForEoS(X16, sizeof...(Ts))
                    >::template f<
                        Ts...
                    >
                >;
        };

        template<char... C>
        using cutOffEOS = typename concatenate_impl_rec<
                            typename filterAllNulls<(selectLevel(sizeof...(C)))>::template f<C...>
                        >::type;
    }
    
    #define STRING_TYPE0(n,x) \
        ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##0)
        
    #define STRING_TYPE1(n,x) \
        ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##0), \
        ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##1)
        
    #define STRING_TYPE2(n,x) \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##0), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##1), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##2), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##3)
        
    #define STRING_TYPE3(n,x) \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##0), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##1), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##2), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##3), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##4), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##5), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##6), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##7)

    #define STRING_TYPE4(n,x) \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##0), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##1), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##2), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##3), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##4), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##5), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##6), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##7), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##8), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##9), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##A), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##B), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##C), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##D), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##E), \
            ::cppjni::concepts::detail::getChar(x, sizeof(x), 0x##n##F)

    #define STRING_TYPE5(n,x) \
            STRING_TYPE4(n##0,x), \
            STRING_TYPE4(n##1,x)

    #define STRING_TYPE6(n,x) \
            STRING_TYPE4(n##0,x), \
            STRING_TYPE4(n##1,x), \
            STRING_TYPE4(n##2,x), \
            STRING_TYPE4(n##3,x)

    #define STRING_TYPE7(n,x) \
            STRING_TYPE4(n##0,x), \
            STRING_TYPE4(n##1,x), \
            STRING_TYPE4(n##2,x), \
            STRING_TYPE4(n##3,x), \
            STRING_TYPE4(n##4,x), \
            STRING_TYPE4(n##5,x), \
            STRING_TYPE4(n##6,x), \
            STRING_TYPE4(n##7,x)

    #define STRING_TYPE8(n,x) \
            STRING_TYPE4(n##0,x), \
            STRING_TYPE4(n##1,x), \
            STRING_TYPE4(n##2,x), \
            STRING_TYPE4(n##3,x), \
            STRING_TYPE4(n##4,x), \
            STRING_TYPE4(n##5,x), \
            STRING_TYPE4(n##6,x), \
            STRING_TYPE4(n##7,x), \
            STRING_TYPE4(n##8,x), \
            STRING_TYPE4(n##9,x), \
            STRING_TYPE4(n##A,x), \
            STRING_TYPE4(n##B,x), \
            STRING_TYPE4(n##C,x), \
            STRING_TYPE4(n##D,x), \
            STRING_TYPE4(n##E,x), \
            STRING_TYPE4(n##F,x)

    #define STRING_TYPE9(n,x) \
            STRING_TYPE8(n##0,x), \
            STRING_TYPE8(n##1,x)

    #define STRING_TYPE10(n,x) \
            STRING_TYPE8(n##0,x), \
            STRING_TYPE8(n##1,x), \
            STRING_TYPE8(n##2,x), \
            STRING_TYPE7(n##3,x), \
            STRING_TYPE4(n##38,x), \
            STRING_TYPE4(n##39,x), \
            STRING_TYPE4(n##3A,x), \
            STRING_TYPE4(n##3B,x), \
            STRING_TYPE4(n##3C,x), \
            STRING_TYPE4(n##3D,x), \
            STRING_TYPE4(n##3E,x), \
            STRING_TYPE4(n##3F,x)

    #ifdef USE_STRING_TYPE_SIZE_2N
        #if USE_STRING_TYPE_SIZE_2N >= 0 && USE_STRING_TYPE_SIZE_2N <= 10
            #define string_type_is(x) \
                ::cppjni::concepts::detail::cutOffEOS<STRING_TYPE##USE_STRING_TYPE_SIZE_2N(,x)>
        #elif USE_STRING_TYPE_SIZE_2N > 10
            #error Exceeded maximum string_type size!!
        #elif USE_STRING_TYPE_SIZE_2N < 0
            #error String type size cannot be negative!!
        #endif
    #else
        //default is 6 which is 64 characters
        #define string_type_is(x) \
            ::cppjni::concepts::detail::cutOffEOS<STRING_TYPE6(,x)>
    #endif

#endif //if not defined _MSC_VER
}
}