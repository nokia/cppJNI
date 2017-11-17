#pragma once
#include <type_traits>

#include <boost/hana/integral_constant.hpp>
#include <boost/hana/size.hpp>

#include <jni.h>

#include "environment.hpp"
#include "global_reference.fwd.hpp"
#include "local_reference.fwd.hpp"

namespace cppjni
{
namespace jniwrappers
{
    namespace detail
    {
        
        template<typename jni_type_t>
        struct do_call_object_method;
        
#define MAKE_PRIMITIVE_SPECIALIZATION(jniType) \
        template<> \
        struct do_call_object_method<jniType> \
        { \
            jniType operator()(const GlobalReference<jobject>& jniObject, jmethodID methodID, ...) const; \
        }
    
#define MAKE_OBJECT_SPECIALIZATION(jniType) \
        template<> \
        struct do_call_object_method<jniType> \
        { \
            LocalReference<jniType> operator()(const GlobalReference<jobject>& jniObject, jmethodID methodID, ...) const; \
        }
    
        MAKE_PRIMITIVE_SPECIALIZATION(void);
        MAKE_PRIMITIVE_SPECIALIZATION(jboolean);
        MAKE_PRIMITIVE_SPECIALIZATION(jbyte);
        MAKE_PRIMITIVE_SPECIALIZATION(jchar);
        MAKE_PRIMITIVE_SPECIALIZATION(jshort);
        MAKE_PRIMITIVE_SPECIALIZATION(jint);
        MAKE_PRIMITIVE_SPECIALIZATION(jlong);
        MAKE_PRIMITIVE_SPECIALIZATION(jfloat);
        MAKE_PRIMITIVE_SPECIALIZATION(jdouble);
        MAKE_OBJECT_SPECIALIZATION(jobject);
        MAKE_OBJECT_SPECIALIZATION(jstring);
    
#undef MAKE_PRIMITIVE_SPECIALIZATION
#undef MAKE_OBJECT_SPECIALIZATION
    }
    
    struct call_object_method
    {
        template<typename jni_type_t, typename sequence_t>
        auto operator()(const GlobalReference<jobject>& jniObject, jmethodID methodID, const sequence_t& s) const
        {
            constexpr auto size = decltype(boost::hana::size(s))::value;
            return callImpl<jni_type_t>(jniObject, methodID, s, std::make_index_sequence<size>());
        }
        
    private:
        template<typename jni_type_t, typename sequence_t, std::size_t ...I>
        auto callImpl(const GlobalReference<jobject>& jniObject, jmethodID methodID, const sequence_t& s, const std::index_sequence<I...>&) const
        {
            return detail::do_call_object_method<jni_type_t>()(jniObject, methodID, s[boost::hana::int_c<I>]...);
        }
    };
    

}
}