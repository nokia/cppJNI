#pragma once

namespace cppjni
{
namespace mpl
{
    namespace detail
    {
        template<bool>
        struct deferred_call_impl;
        
        template<>
        struct deferred_call_impl<true>
        {
            template<typename F, typename C, typename... Ts>
            using f = typename F::template continuation<C, Ts...>;
        };
        
        template<bool>
        struct deferred_call_f_impl;
        
        template<>
        struct deferred_call_f_impl<true>
        {
            template<template<typename...> class F, typename... Ts>
            using f = F<Ts...>;
        };
        
        template<bool>
        struct deferred_type_impl;
        
        template<>
        struct deferred_type_impl<true>
        {
            template<typename T>
            using f = T;
        };
    }
    
    template<typename F, typename C, typename... Ts>
    using deferred_call = typename detail::deferred_call_impl<sizeof...(Ts) < 100000>::template f<F, C, Ts...>;
    
    template<template<typename...> class F, typename... Ts>
    using deferred_call_f = typename detail::deferred_call_f_impl<sizeof...(Ts) < 100000>::template f<F, Ts...>;
    
    template<typename T>
    using deferred_type = typename detail::deferred_type_impl<sizeof(T) != 0>::template f<T>;
}
}
