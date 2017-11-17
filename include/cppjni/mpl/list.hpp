#pragma once
#include <type_traits>

namespace cppjni
{
namespace mpl
{
    template<typename ...>
    struct list 
    {};
    
    struct make_list
    {
        template<typename... Ts>
        using f = list<Ts...>;
    };
}
}
