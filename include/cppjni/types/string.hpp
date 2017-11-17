#pragma once
#include <algorithm>
#include <stdexcept>
#include <string>
#include <type_traits>

#include <boost/hana/core/when.hpp>

#include <jni.h>

#include <typestring.hh>

#include <cppjni/concepts/is_jni_reference_wrapper_type.hpp>
#include <cppjni/jni_wrappers/environment.hpp>

#include "object.fwd.hpp"

namespace cppjni
{
namespace types
{
    struct String
    {
        using native_t = std::string;
        using jni_t = jstring;
        using jni_string_path_t = typestring_is("java/lang/String");
        using jni_type_string_t = irqus::tycat<typestring_is("L"), jni_string_path_t, typestring_is(";")>;
        
        /**
         * This may look a bit complicated: all we want here is to use only char pointers and one dimensional arrays (doesn't matter how it's decorated with const, volatile etc.),
         * but not single char (with const/volatile/reference decoration).
         */
        template<typename type_t>
        struct isConvertibleImpl
        {
            //removing all decorations from potential array type. Order of stripping is important!
            using decayed_type_t = typename std::decay<type_t>::type;
            using unpointered_type_t = typename std::remove_pointer<decayed_type_t>::type;
            using underlying_array_t = typename std::remove_cv<unpointered_type_t>::type;
            
            //removing all decorations from potential single char type
            using unreferenced_char_t = typename std::remove_reference<type_t>::type;
            using underlying_char_t = typename std::remove_cv<unreferenced_char_t>::type;
            
            using type = 
                std::integral_constant<
                    bool,
                    (std::is_same<underlying_array_t, char>::value &&
                     !std::is_same<underlying_char_t, char>::value
                    )
                    || std::is_same<type_t, std::string>::value
                >;
        };
        
        template<typename T>
        using isConvertible = typename isConvertibleImpl<T>::type;
        
        template<typename T>
        using isConvertibleFromJni = std::is_same<jni_string_path_t, T>;
        
        template<template<typename...> class reference_t, typename = boost::hana::when<concepts::is_jni_reference_wrapper_type<reference_t>>>
        native_t convertFromJni(const reference_t<jni_t>& value) const
        {
            return convertFromJni(*value);
        }
        
        template<template<typename...> class reference_t, typename = boost::hana::when<concepts::is_jni_reference_wrapper_type<reference_t>>>
        native_t convertFromJni(const reference_t<jobject>& value) const
        {
            auto&& stringRef = static_cast<jni_t>(*value);
            return convertFromJni(stringRef);
        }
        
        jni_t convertToJni(const char * const nativeValue) const;
        jni_t convertToJni(const native_t& nativeValue) const;
        
    private:
        native_t convertFromJni(jni_t value) const;
    };
}
}