#pragma once
#include <type_traits>

#include <boost/hana/integral_constant.hpp>
#include <boost/hana/size.hpp>

#include <jni.h>

#include "environment.hpp"
#include "global_reference.fwd.hpp"

namespace cppjni
{
namespace jniwrappers
{
    namespace detail
    {
        template<typename jni_type_t>
        struct do_call_static_method;
        
#define MAKE_SPECIALIZATION(jniType) \
        template<> \
        struct do_call_static_method<jniType> \
        { \
            jniType operator()(const GlobalReference<jclass>& jniClass, jmethodID methodID, ...) const; \
        }
#define MAKE_OBJECT_SPECIALIZATION(jniType) \
        template<> \
        struct do_call_static_method<jniType> \
        { \
            LocalReference<jniType> operator()(const GlobalReference<jclass>& jniClass, jmethodID methodID, ...) const; \
        }

        MAKE_SPECIALIZATION(void);
        MAKE_SPECIALIZATION(jboolean);
        MAKE_SPECIALIZATION(jbyte);
        MAKE_SPECIALIZATION(jchar);
        MAKE_SPECIALIZATION(jint);
        MAKE_SPECIALIZATION(jlong);
        MAKE_SPECIALIZATION(jfloat);
        MAKE_SPECIALIZATION(jdouble);
        MAKE_SPECIALIZATION(jshort);
        MAKE_OBJECT_SPECIALIZATION(jobject);
        MAKE_OBJECT_SPECIALIZATION(jstring);
        
#undef MAKE_OBJECT_SPECIALIZATION
#undef MAKE_SPECIALIZATION
    }
    
    struct call_static_method
    {
        template<typename jni_type_t, typename sequence_t>
        auto operator()(const GlobalReference<jclass>& jniClass, jmethodID methodID, const sequence_t& s) const
        {
            constexpr auto size = boost::hana::size(sequence_t{});
            return callImpl<jni_type_t>(jniClass, methodID, s, std::make_index_sequence<size>());
        }
        
    private:
        template<typename jni_type_t, typename sequence_t, std::size_t ...I>
        auto callImpl(const GlobalReference<jclass>& jniClass, jmethodID methodID, sequence_t&& s, const std::index_sequence<I...>&) const
        {
            return detail::do_call_static_method<jni_type_t>()(jniClass, methodID, s[boost::hana::int_c<I>]...);
        }
    };
}
}