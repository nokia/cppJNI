#pragma once
#include <type_traits>

#include <boost/hana/integral_constant.hpp>
#include <boost/hana/size.hpp>

#include <jni.h>

#include "environment.hpp"
#include "local_reference.hpp"
#include "global_reference.hpp"

namespace cppjni
{
namespace jniwrappers
{
    struct call_constructor
    {
        template<typename jni_return_type_t, typename sequence_t>
        LocalReference<jni_return_type_t> operator()(const GlobalReference<jclass>& jniClass, jmethodID methodID, const sequence_t& s) const
        {
            constexpr auto size = decltype(boost::hana::size(s))::value;
            return LocalReference<jni_return_type_t>{callImpl<jni_return_type_t>(jniClass, methodID, s, std::make_index_sequence<size>())};
        }
        
    private:
        template<typename jni_return_type_t, typename sequence_t, std::size_t ...I>
        LocalReference<jni_return_type_t> callImpl(const GlobalReference<jclass>& jniClass, jmethodID methodID, const sequence_t& s, const std::index_sequence<I...>&) const
        {
            Environment env;
            return LocalReference<jni_return_type_t>{env->NewObject((jclass)*jniClass, methodID, s[boost::hana::int_c<I>]...)};
        }
    };
}
}