#pragma once

#include <cppjni/mpl/identity.hpp>
#include <cppjni/mpl/find.hpp>
#include <cppjni/mpl/list.hpp>
#include <cppjni/mpl/apply.hpp>

#include <jni.h>


namespace cppjni
{
namespace concepts
{
    namespace detail
    {        
        using jni_reference_types = mpl::list<
            jobject,
            jclass,
            jthrowable,
            jstring,
            jarray,
            jbooleanArray,
            jbyteArray,
            jcharArray,
            jshortArray,
            jintArray,
            jlongArray,
            jfloatArray,
            jdoubleArray,
            jobjectArray
        >;
    }

    template<typename type_t>
    constexpr auto is_jni_reference_type = 
        mpl::apply<
            mpl::find<type_t>,
            detail::jni_reference_types
        >::template continuation<mpl::identity>::value;
}
}