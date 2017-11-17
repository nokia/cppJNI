#pragma once
#include "predefined/java/lang/object.fwd.hpp"
#include "types/object.fwd.hpp"

namespace cppjni
{
    namespace detail
    {
        template<template<typename> class to_definition_t>
        struct java_cast;
    }
}