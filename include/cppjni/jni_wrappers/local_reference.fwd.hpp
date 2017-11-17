#pragma once
#include <boost/hana/core/when.hpp>

#include <cppjni/concepts/is_jni_reference_type.hpp>

namespace cppjni
{
namespace jniwrappers
{
    template<typename jni_reference_type_t, typename = boost::hana::when<true>>
    class LocalReference;
}
}