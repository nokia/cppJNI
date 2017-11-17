#pragma once
#include "find_class.hpp"
#include "call_constructor.hpp"
#include "call_object_method.hpp"
#include "call_static_method.hpp"
#include "exception_check.hpp"

namespace cppjni
{
namespace jniwrappers
{
    struct CurrentEnvironment
    {
        find_class findClass;
        
        call_constructor callConstructor;
        call_object_method callObjectMethod;
        call_static_method callStaticMethod;
        
        exception_check exceptionCheck;
    };
}
}