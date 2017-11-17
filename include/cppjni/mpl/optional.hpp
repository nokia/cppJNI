#pragma once

namespace cppjni
{
namespace mpl
{
    
    template<typename... Ts>
    struct optional_value;
    
    template<>
    struct optional_value<>
    {
        using has_type = std::false_type;
    };
    
    template<typename T>
    struct optional_value<T>
    {
        using has_type = std::true_type;
        using type = T;
    };
    
    struct optional
    {
        template<typename... T>
        using f = optional_value<T...>;
    };
}
}