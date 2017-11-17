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
    struct Throwable: virtual java::lang::Object<T>
    {
        using class_path_t = typestring_is("java/lang/Throwable");
        
        MAKE_JAVA_METHOD(getLocalizedMessage, Method<types::String()>)
        MAKE_JAVA_METHOD(getMessage, Method<types::String()>)
        MAKE_JAVA_METHOD(printStackTrace, Method<Void()>)
    };
}
}
}
}