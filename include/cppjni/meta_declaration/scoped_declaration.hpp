#pragma once
#include "method_scope_category.hpp"

namespace cppjni
{
namespace metadeclaration
{
    template<typename function_signature_t>
    struct StaticMethod
    {
        using signature_t = metadeclaration::signature_info<function_signature_t>;
        static constexpr metadeclaration::MethodScopeCategory scope_category = metadeclaration::MethodScopeCategory::STATIC;
    };
    
    template<typename function_signature_t>
    struct Method
    {
        using signature_t = metadeclaration::signature_info<function_signature_t>;
        static constexpr metadeclaration::MethodScopeCategory scope_category = metadeclaration::MethodScopeCategory::INSTANCE;
    };
}
}