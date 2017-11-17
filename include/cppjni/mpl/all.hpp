#pragma once
#include <type_traits>

#include "identity.hpp"

namespace cppjni
{
namespace mpl
{
    namespace detail
    {
        enum class all_selection_e {CONTINUE, TRUE, FALSE};
        
        constexpr all_selection_e select_all_impl(unsigned size, bool isTrue)
        {
            return !isTrue ? all_selection_e::FALSE
                          : size > 1 ? all_selection_e::CONTINUE
                                     : all_selection_e::TRUE;
        }
        
        template<all_selection_e>
        struct all_impl;
        
        template<>
        struct all_impl<all_selection_e::TRUE>
        {
            template<typename C, template<typename> class, typename ...>
            using f = typename C::template f<std::true_type>;
        };
        
        template<>
        struct all_impl<all_selection_e::FALSE>
        {
            template<typename C, template<typename> class, typename ...>
            using f = typename C::template f<std::false_type>;
        };
        
        template<>
        struct all_impl<all_selection_e::CONTINUE>
        {
            template<typename C, template<typename> class F, typename T, typename... Ts>
            using f = typename all_impl<select_all_impl(sizeof...(Ts), F<T>::value)>::template f<C, F, Ts...>;
        };
    }
    
    template<template<typename> class F>
    struct all
    {
        template<typename C, typename... Ts>
        using continuation = typename detail::all_impl<detail::select_all_impl(sizeof...(Ts), true)>::template f<C, F, Ts...>;
    };
    
    template<typename T>
    using is_true = std::is_base_of<std::true_type, T>;
    
    template<typename T>
    using is_false = std::is_base_of<std::false_type, T>;
}
}
