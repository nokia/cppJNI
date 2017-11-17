#pragma once
#include "list.hpp"
#include "optional.hpp"

namespace cppjni
{
namespace mpl
{
    namespace detail
    {
        enum class find_if_impl_e{NOT_FOUND, FOUND, SEARCH0, SEARCH1};
        
        constexpr find_if_impl_e select_find_if_impl(std::size_t size, bool found)
        {
            return found ? find_if_impl_e::FOUND
                         : size > 0 ? find_if_impl_e::SEARCH0
                                    : find_if_impl_e::NOT_FOUND;
        }
        
        template<find_if_impl_e>
        struct find_if_impl;
        
        template<>
        struct find_if_impl<find_if_impl_e::NOT_FOUND>
        {
            template<typename C, template <typename> class, typename prev_type_t, typename...>
            using f = typename C::template f<>;
        };
        
        template<>
        struct find_if_impl<find_if_impl_e::FOUND>
        {
            template<typename C, template <typename> class, typename prev_type_t, typename ...>
            using f = typename C::template f<prev_type_t>;
        };
        
        template<>
        struct find_if_impl<find_if_impl_e::SEARCH0>
        {
            template<typename C, template <typename> class F, typename prev_type_t, typename T1, typename ...Ts>
            using f = 
                typename find_if_impl<
                    select_find_if_impl(
                        sizeof...(Ts),
                        F<T1>::value
                    )
                >::template f<C, F, T1, Ts...>;
        };
    }
    
    template<template <typename> class F>
    struct find_if
    {
        template<typename C, typename... Ts>
        using continuation = 
            typename detail::find_if_impl<
                detail::select_find_if_impl(sizeof...(Ts), false)
            >::template f<C, F, void, Ts...>;
    };
}
}