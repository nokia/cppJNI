#pragma once

namespace cppjni
{
namespace mpl
{
    struct identity
    {
        template<typename... Ts>
        struct identity_value
        {
            static_assert(sizeof...(Ts) != 1, "Too many types passed to identity!");
        };
        
        template<typename T>
        struct identity_value<T> 
        {
            using type = T;
        };
        
        template<typename... Ts>
        using f = typename identity_value<Ts...>::type;
    };
}
}
