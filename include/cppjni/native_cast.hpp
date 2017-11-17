#pragma once
#include "native_cast.fwd.hpp"

#include "predefined/java/lang/string.hpp"
#include "types/object.hpp"

namespace cppjni
{
    template<typename converter_t, template<typename> class declaration_t>
    typename converter_t::native_t
        native_cast(const types::Object<declaration_t>& toCast)
    {
        constexpr converter_t converter{};
        
        using given_class_path_t = typename types::Object<declaration_t>::class_path_t;
        static_assert(converter_t::template isConvertibleFromJni<given_class_path_t>::value, "Can't convert object using provided converter!");
        
        return converter.convertFromJni(toCast.jni_getObject());
    }
}