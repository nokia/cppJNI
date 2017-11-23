#pragma once
#include <boost/hana/tuple.hpp>

#include "jni_constructor_signature_hack.hpp"
#include "method_scope_category.hpp"

namespace cppjni
{
namespace metadeclaration
{
    struct method_declaration_tag {};

    template<typename method_name_t, typename signature_info_t>
    struct method_declaration
    {
        using sig_info_t = typename signature_info_t::signature_t;
        using return_t = typename sig_info_t::return_t;
        using arguments_t = typename sig_info_t::arguments_t;
        using name_t = method_name_t;
        using jni_type_string_t = jni_constructor_signature_hack<name_t, sig_info_t>;
        
        static constexpr auto scope_category = signature_info_t::scope_category;
    };
}
}