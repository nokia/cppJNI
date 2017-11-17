#pragma once
#include <typestring.hh>

namespace cppjni
{
namespace jniwrappers
{
    using constructor_method_name_t = typestring_is("<init>");
    
    template<typename Signature, typename = void>
    struct generate_jni_signature_string;
    
    template<typename ReturnType, typename ...Args>
    struct generate_jni_signature_string<ReturnType(Args...), void>
    {
        using type = irqus::tycat<
            typestring_is("("), 
                typename Args::jni_type_string_t..., 
            typestring_is(")"), 
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