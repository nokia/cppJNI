#pragma once
#include <cppjni/concepts/string_type.hpp>

namespace cppjni
{
namespace jniwrappers
{
    using constructor_method_name_t = string_type_is("<init>");
    
    template<typename Signature, typename = void>
    struct generate_jni_signature_string;
    
    template<typename ReturnType, typename ...Args>
    struct generate_jni_signature_string<ReturnType(Args...), void>
    {
        using type = concepts::concatenate<
            string_type_is("("),
                typename Args::jni_type_string_t..., 
            string_type_is(")"), 
            typename ReturnType::jni_type_string_t
        >;
    };
    
    template<typename ReturnType>
    struct generate_jni_signature_string<ReturnType, int>
    {
        using type = typename ReturnType::jni_type_string_t;
    };
}
}