#pragma once

#include "list.hpp"
#include "deferred_call.hpp"

namespace cppjni
{
namespace mpl
{
    template<template<typename> class F>
    struct transform
    {
        template<typename C, typename... Ts>
        using continuation = 
            deferred_call_f<C::template f, F<Ts>...>;
    };
}
}
