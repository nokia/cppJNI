#pragma once
#include "generate_overloaded_method_declarations.hpp"
#include "method_scope_category.hpp"
#include "signature_info.hpp"

namespace cppjni
{
namespace metadeclaration
{   
    template<typename function_signature_t>
    struct ConstructorMethod
    {
        using signature_t = signature_info<function_signature_t>;
        static constexpr metadeclaration::MethodScopeCategory scope_category = metadeclaration::MethodScopeCategory::CONSTRUCTOR;
    };
    
    template<typename ...signatures_t>
    using generate_overloaded_constructor_declarations = generate_overloaded_method_declarations<jniwrappers::constructor_method_name_t, ConstructorMethod<signatures_t>...>;
}
}