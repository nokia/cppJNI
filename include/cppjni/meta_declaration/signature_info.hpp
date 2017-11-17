#pragma once
#include <type_traits>

#include <boost/hana/core/when.hpp>
#include <boost/hana/tuple.hpp>

#include <cppjni/concepts/is_java_class_definition.hpp>
#include <cppjni/jni_wrappers/generate_jni_signature_string.hpp>
#include <cppjni/mpl/condition.hpp>
#include <cppjni/mpl/list.hpp>
#include <cppjni/types/object.fwd.hpp>
#include <cppjni/types/object_converter.hpp>


namespace cppjni
{
namespace metadeclaration
{
    template<typename T>
    struct replace_java_declaration_with_converter
    {
        using type = T;
    };
    
    template<template <typename> class T>
    struct replace_java_declaration_with_converter<cppjni::types::Object<T>>
    {
        using type = types::ObjectConverter<cppjni::types::Object<T>>;
    };

    template<typename function_signature_t>
    struct signature_info;
    
    template<typename function_return_t, typename ...args_t>
    struct signature_info<function_return_t(args_t...)>
    {
        using original_signature_t = function_return_t(args_t...);
        using arguments_t = mpl::list<
                                typename replace_java_declaration_with_converter<args_t>::type...
                            >;
        using return_t = typename replace_java_declaration_with_converter<function_return_t>::type;
        
        using final_signature_t = return_t(typename replace_java_declaration_with_converter<args_t>::type...);
        using jni_type_string_t = typename ::cppjni::jniwrappers::generate_jni_signature_string<final_signature_t>::type;
    };
}
}