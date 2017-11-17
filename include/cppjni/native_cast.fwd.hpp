#pragma once
#include "types/object.fwd.hpp"

namespace cppjni
{
    template<typename converter_t, template<typename> class java_definition_t>
    typename converter_t::native_t native_cast(const types::Object<java_definition_t>& toConvert);
}