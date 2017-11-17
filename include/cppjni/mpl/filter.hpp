#pragma once

#include "deferred_call.hpp"
#include "join.hpp"
#include "list.hpp"
#include "pipeline.hpp"
#include "transform.hpp"

namespace cppjni
{
namespace mpl
{
    namespace detail
    {
        template<bool>
        struct filter_optional;
        
        template<>
        struct filter_optional<true>
        {
            template<typename T>
            using f = list<T>;
        };
        
        template<>
        struct filter_optional<false>
        {
            template<typename T>
            using f = list<>;
        };
    }
    
    template<template <typename> class F>
    struct filter
    {
        template<typename T>
        using filter_pred = typename detail::filter_optional<F<T>::value>::template f<T>;
        
        using filter_pipeline = 
            pipeline<
                transform<filter_pred>, 
                join
            >;
        
        template<typename C, typename... Ts>
        using continuation = deferred_call<deferred_type<filter_pipeline>, deferred_type<C>, Ts...>;
    };
    
    namespace eager
    {
        template<template <typename> class F>
        struct filter
        {
            template<typename... Ts>
            using f = typename mpl::filter<F>::template continuation<make_list, Ts...>;
        };
    }
}
}

