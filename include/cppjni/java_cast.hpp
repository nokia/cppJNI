#pragma once
#include "java_cast.fwd.hpp"

#include <utility>

#include "concepts/is_java_class_definition.hpp"
#include "jni_wrappers/environment.hpp"
#include "predefined/java/lang/object.hpp"
#include "types/object.hpp"

namespace cppjni
{
    namespace detail
    {
        template<template<typename> class to_definition_t>
        struct java_cast
        {
            static_assert(concepts::is_java_class_definition<types::Object<to_definition_t>>, "Provided class is not a Java class definition!");
            
            template<template<typename> class from_definition_t>
            types::Object<to_definition_t> operator() (types::Object<from_definition_t>&& toCast) const
            {
                const auto& classRef = toCast.jni_getClass();
                
                return types::Object<to_definition_t>(classRef, std::move(toCast).jni_getObject());
            }
            
            template<template<typename> class from_definition_t>
            types::Object<to_definition_t> operator() (const types::Object<from_definition_t>& toCast) const
            {
                const auto& originalRef = toCast.jni_getObject();
                const auto& classRef = toCast.jni_getClass();
                
                auto&& clonedRef = originalRef.copyReference();
                return types::Object<to_definition_t>(classRef, std::move(clonedRef));
            }
        };
    }
    
    template<template<typename> class to_definition_t>
    constexpr auto java_cast = detail::java_cast<to_definition_t>{};
}