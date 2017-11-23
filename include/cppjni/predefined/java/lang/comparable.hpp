#pragma once
#include <cppjni/method_signature.hpp>

#include "object.hpp"

namespace cppjni
{
namespace predefined
{
namespace java
{
namespace lang
{
    template<typename T>
    struct Comparable: virtual Object<T>
    {
        using class_path_t = string_type_is("java/lang/Comparable");
        
        MAKE_JAVA_METHOD(compareTo, Method<types::Int(Object_)>)
    };
}
}
}
}