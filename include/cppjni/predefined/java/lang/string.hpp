#pragma once

#include <cppjni/method_signature.hpp>

#include "object.hpp"
#include "comparable.hpp"

namespace cppjni
{
namespace predefined
{
namespace java
{
namespace lang
{
    template<typename T>
    struct String: virtual Comparable<T>, virtual Object<T>
    {
        using class_path_t = typestring_is("java/lang/String");
        
        MAKE_JAVA_CONSTRUCTOR(types::Object<java::lang::String>(), types::Object<java::lang::String>(::cppjni::String))
        
        MAKE_JAVA_METHOD(charAt, Method<types::Char(types::Int)>)
    };
}
}
}
}