#pragma once
#include <jni.h>

#include "local_reference.fwd.hpp"

namespace cppjni
{
namespace jniwrappers
{
    struct find_class
    {
        LocalReference<jclass> operator()(const char* className) const;
    };
}
}
