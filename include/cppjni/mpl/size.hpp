#pragma once
#include <type_traits>

#include "identity.hpp"
#include "list.hpp"
#include "apply.hpp"

namespace cppjni
{
namespace mpl
{
    struct size
    {
        template<typename C, typename...Ts>
        using continuation = typename C::template f<std::integral_constant<std::size_t, sizeof...(Ts)>>;
    };

    namespace eager
    {
        template<typename T>
        using size = typename mpl::apply<size, T>::template continuation<mpl::identity>;
    }
}
}
