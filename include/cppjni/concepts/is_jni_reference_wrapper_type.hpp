#pragma once

#include <jni.h>

#include <cppjni/mpl/find.hpp>
#include <cppjni/mpl/list.hpp>
#include <cppjni/jni_wrappers/local_reference.fwd.hpp>
#include <cppjni/jni_wrappers/global_reference.fwd.hpp>

namespace cppjni
{
namespace concepts
{
    namespace detail
    {
        using reference_wrapper_types = mpl::list<jniwrappers::LocalReference<jobject>, jniwrappers::GlobalReference<jobject>>;
    }

    template<template<typename...> class possible_ref_t>
    constexpr auto is_jni_reference_wrapper_type = 
        mpl::apply<
            mpl::find<possible_ref_t<jobject>>,
            detail::reference_wrapper_types
        >::template continuation<mpl::identity>::value;
}
}