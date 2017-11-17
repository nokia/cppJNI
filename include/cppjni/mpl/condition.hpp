#pragma once

namespace cppjni
{
namespace mpl
{
    template<bool conditionValue>
    struct condition
    {
        template<typename TrueType, typename>
        using f = TrueType;
    };
    
    template<>
    struct condition<false>
    {
        template<typename , typename FalseType>
        using f = FalseType;
    };
}
}
