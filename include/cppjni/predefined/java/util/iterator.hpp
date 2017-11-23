#pragma once

#include <cppjni/method_signature.hpp>
#include <cppjni/predefined/java/lang/object.hpp>

namespace cppjni
{
namespace predefined
{
namespace java
{
namespace util
{
    template<typename T>
    struct Iterator: virtual java::lang::Object<T>
    {
        using class_path_t = string_type_is("java/util/Iterator");
        
        MAKE_JAVA_METHOD(hasNext, Method<Boolean()>)
        MAKE_JAVA_METHOD(next, Method<::cppjni::predefined::java::lang::Object_()>)
    };
}
}
}
}