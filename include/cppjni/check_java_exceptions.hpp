#pragma once

#include "jni_wrappers/exception_check.hpp"

namespace cppjni
{
    auto checkJavaExceptions = jniwrappers::exception_check{};
}
