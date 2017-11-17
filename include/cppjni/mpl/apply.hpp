#pragma once
#include "deferred_call.hpp"
#include "list.hpp"

namespace cppjni
{
namespace mpl
{
    template<typename F, typename List>
    struct apply;
    
    template<typename F, typename... Ts>
    struct apply<F, list<Ts...>>
    {
        template<typename C, typename...>
        using continuation = deferred_call<F, C, Ts...>;
    };
    
    namespace eager
    {
        template<typename F, typename List, typename C = mpl::make_list>
        using apply = typename mpl::apply<F, List>::template continuation<C>;
    }
}
}