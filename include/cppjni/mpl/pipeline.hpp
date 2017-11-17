#pragma once
#include "deferred_call.hpp"

namespace cppjni
{
namespace mpl
{
    namespace detail
    {
        template<typename C, typename... Cs>
        struct pipeline_impl
        {
            template<typename... Ts>
            using f =
                typename C::template continuation<
                    pipeline_impl<Cs...>,
                    Ts...
                >;
        };
        
        template<typename C>
        struct pipeline_impl<C>
        {
            template<typename... Ts>
            using f = typename C::template f<Ts...>;
        };
    }
    
    template<typename C, typename... Cs>
    struct pipeline
    {
        template<typename COuter, typename... Ts>
        using continuation =
//             deferred_call_f<
                typename detail::pipeline_impl<C, Cs..., COuter>::template f<Ts...>;
//             >;
    };
}
}
