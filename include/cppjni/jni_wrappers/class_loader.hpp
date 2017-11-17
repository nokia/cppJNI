#pragma once
#include <stdexcept>
#include <utility>

#include <jni.h>

#include "current_environment.hpp"
#include "global_reference.hpp"

namespace cppjni
{
namespace jniwrappers
{
    template<typename class_path_t>
    struct ClassLoader
    {
        using type = GlobalReference<jclass>;
        
        type operator()() const
        {
            CurrentEnvironment env;
            auto foundClass = env.findClass(class_path_t::data());
            return GlobalReference<jclass>{std::move(foundClass)};
        }
    };
}
}