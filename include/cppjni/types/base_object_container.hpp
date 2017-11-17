#pragma once
#include <jni.h>

#include <cppjni/jni_wrappers/global_reference.hpp>

namespace cppjni
{
namespace types
{
    class BaseObjectContainer
    {
    public:
        virtual const jniwrappers::GlobalReference<jclass>& jni_getClass() const = 0;
    };
}
}