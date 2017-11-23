#pragma once
#include <cppjni/method_signature.hpp>

#include "class.fwd.hpp"
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
    struct Class: virtual Object<T>
    {
        using class_path_t = string_type_is("java/lang/Class");
        
        MAKE_JAVA_METHOD(getName, Method<types::String()>)
        MAKE_JAVA_METHOD(getSimpleName, Method<types::String()>)
    };
}
}
}
}