#pragma once
#include "object_converter.fwd.hpp"

#include <utility>

#include <boost/hana/core/when.hpp>

#include <jni.h>

#include <typestring.hh>

#include <cppjni/concepts/is_jni_reference_wrapper_type.hpp>
#include <cppjni/concepts/static_list.hpp>
#include <cppjni/jni_wrappers/class_loader.hpp>
#include <cppjni/jni_wrappers/local_reference.hpp>
#include <cppjni/jni_wrappers/global_reference.hpp>
#include <cppjni/mpl/condition.hpp>

#include "object.hpp"

namespace cppjni
{
namespace types
{
    template<template<typename> class class_definition_t>
    struct ObjectConverter<Object<class_definition_t>>
    {
        using native_t = types::Object<class_definition_t>;
        using jni_t = jobject;
        using class_path_t = typename class_definition_t<types::ObjectContainer>::class_path_t;
        using jni_type_string_t = irqus::tycat<typestring_is("L"), class_path_t, typestring_is(";")>;
        
        template<typename T>
        using isConvertible = 
            std::integral_constant<
                bool,
                std::is_same<T, native_t>::value || std::is_same<T, jniwrappers::LocalReference<jobject>>::value
            >;
        
        native_t convertFromJni(native_t&& jniObject) const
        {
            return native_t(std::move(jniObject));
        }
        
        template<template<typename...> class reference_t, typename = boost::hana::when<concepts::is_jni_reference_wrapper_type<reference_t>>>
        native_t convertFromJni(reference_t<jobject>&& jniObject) const
        {
            concepts::StaticList<jniwrappers::GlobalReference<jclass>> list;
            jniwrappers::GlobalReference<jobject> globalRef{jniObject};
            
            return native_t(list.get<jniwrappers::ClassLoader<class_path_t>>(), std::move(globalRef));
        }
        
        jni_t convertToJni(const native_t& value) const
        {
            return *value.jni_getObject();
        }
    };
    
}
}