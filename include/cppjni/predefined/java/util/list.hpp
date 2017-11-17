#pragma once

#include <cppjni/method_signature.hpp>
#include <cppjni/predefined/java/lang/object.hpp>
#include <cppjni/predefined/java/util/iterator.hpp>

namespace cppjni
{
namespace predefined
{
namespace java
{
namespace util
{
    template<typename T>
    struct List: virtual java::lang::Object<T>
    {
        using class_path_t = typestring_is("java/util/List");
        
        MAKE_JAVA_METHOD(add, Method<Boolean(java::lang::Object_)>, Method<Void(Int, java::lang::Object_)>)
        MAKE_JAVA_METHOD(contains, Method<Boolean(java::lang::Object_)>)
        MAKE_JAVA_METHOD(get, Method<java::lang::Object_(Int)>)
        MAKE_JAVA_METHOD(indexOf, Method<Int(java::lang::Object_)>)
        MAKE_JAVA_METHOD(iterator, Method<Boolean()>)
        MAKE_JAVA_METHOD(lastIndexOf, Method<Int(java::lang::Object_)>)
        MAKE_JAVA_METHOD(size, Method<Int()>)
        MAKE_JAVA_METHOD(subList, Method<List(Int, Int)>)
    };
}
}
}
}