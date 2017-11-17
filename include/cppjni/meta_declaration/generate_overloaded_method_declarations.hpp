#pragma once

#include <cppjni/mpl/list.hpp>

#include "method_declaration.hpp"

namespace cppjni
{
namespace metadeclaration
{
    template<typename method_name_t, typename ...signature_infos>
    using generate_overloaded_method_declarations = 
        mpl::list<
            method_declaration<method_name_t, signature_infos>...
        >;
}
}