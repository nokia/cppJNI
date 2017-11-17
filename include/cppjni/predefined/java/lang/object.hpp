#pragma once
#include "object.fwd.hpp"

#include <cppjni/method_signature.hpp>

#include "class.fwd.hpp"

namespace cppjni
{
namespace predefined
{
namespace java
{
namespace lang
{
    template<typename T>
    struct Object: virtual T
    {
        using class_path_t = typestring_is("java/lang/Object");
        
        MAKE_JAVA_CONSTRUCTOR(types::Object<java::lang::Object>())
        
        MAKE_JAVA_METHOD(equals, Method<Boolean(types::Object<java::lang::Object>)>)
        MAKE_JAVA_METHOD(getClass, Method<types::Object<Class>()>)
        MAKE_JAVA_METHOD(hashCode, Method<Int()>)
        MAKE_JAVA_METHOD(notify, Method<Void()>)
        MAKE_JAVA_METHOD(notifyAll, Method<Void()>)
        MAKE_JAVA_METHOD(toString, Method<types::String()>)
        MAKE_JAVA_METHOD(wait, Method<Void()>, Method<Void(Long)>, Method<Void(Long, Int)>)
    };
    
    /*
     * Shortcut for commonly used java.lang.Object
     */
    using Object_ = types::Object<Object>;
}
}
}
}