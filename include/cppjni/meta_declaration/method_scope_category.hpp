#pragma once

namespace cppjni
{
namespace metadeclaration
{
    /**
     * Method can be in one of 3 scope categories:
     *  - static scope - can be called using class only
     *  - instance scope - can be called using object instance only
     *  - constructor scope - is an instance method but can be called using class only
     */
    enum class MethodScopeCategory
    {
        STATIC,
        INSTANCE,
        CONSTRUCTOR
    };
}
}