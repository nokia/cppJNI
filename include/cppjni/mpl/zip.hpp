#pragma once

#include "list.hpp"

namespace cppjni
{
namespace mpl
{
    
    template<typename F, typename... Ts>
    struct zip_with
    {
        template<typename... Ss>
        struct continuation_helper
        {
            template<typename C>
            using f = typename C::template f<typename F::template f<Ts, Ss>...>;
        };
        template<typename C, typename... Ss>
        using continuation = typename continuation_helper<Ss...>::template f<C>;
    };
}
}
