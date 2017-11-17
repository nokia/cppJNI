#pragma once

#include "apply.hpp"
#include "identity.hpp"
#include "list.hpp"

namespace cppjni
{
namespace mpl
{
    namespace detail
    {
        template<typename... Ts>
        struct first_of_impl
        {
            static_assert(sizeof...(Ts) != 0, "Empty parameter pack provided!");
        };
        
        template<typename T, typename... Ts>
        struct first_of_impl<T, Ts...>
        {
            using type = T;
        };
    }
    
    struct first_of
    {
        template<typename C, typename...Ts>
        using continuation = typename C::template f<typename detail::first_of_impl<Ts...>::type>;
    };
    
    namespace eager
    {
        template<typename List>
        using head = typename apply<first_of, List>::template f<>;
    }
}
}
