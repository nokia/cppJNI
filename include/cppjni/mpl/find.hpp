#pragma once
#include <type_traits>

#include "list.hpp"

namespace cppjni
{
namespace mpl
{
    namespace detail
    {
        enum class find_impl_e{NOT_FOUND, FOUND, SEARCH0, SEARCH1};
        
        constexpr find_impl_e select_find_impl(std::size_t size, bool found)
        {
            return found ? find_impl_e::FOUND 
                         : size > 4 ? find_impl_e::SEARCH1 
                                    : size > 0 ? find_impl_e::SEARCH0 
                                               : find_impl_e::NOT_FOUND;
        }
        
        template<find_impl_e>
        struct find_impl;
        
        template<>
        struct find_impl<find_impl_e::NOT_FOUND>
        {
            template<typename...>
            using f = std::false_type;
        };
        template<>
        struct find_impl<find_impl_e::FOUND>
        {
            template<typename ...>
            using f = std::true_type;
        };
        
        template<>
        struct find_impl<find_impl_e::SEARCH0>
        {
            template<typename ToFind, typename T1, typename ...Ts>
            using f = typename find_impl<
                            select_find_impl(
                                sizeof...(Ts),
                                std::is_same<T1, ToFind>::value
                            )
                      >::template f<ToFind, Ts...>;
        };
        
        template<>
        struct find_impl<find_impl_e::SEARCH1>
        {
            template<typename ToFind, typename T1, typename T2, typename T3, typename T4, typename ...Ts>
            using f = typename find_impl<
                            select_find_impl(
                                sizeof...(Ts),
                                std::is_same<T1, ToFind>::value
                                || std::is_same<T2, ToFind>::value
                                || std::is_same<T3, ToFind>::value
                                || std::is_same<T4, ToFind>::value
                            )
                      >::template f<ToFind, Ts...>;
        };
    }
    
    template<typename ToFind>
    struct find
    {
        template<typename C, typename... Ts>
        using continuation = 
            typename C::template f<
                typename detail::find_impl<
                    detail::select_find_impl(sizeof...(Ts), false)
                >::template f<ToFind, Ts...>
            >;
    };
}
}