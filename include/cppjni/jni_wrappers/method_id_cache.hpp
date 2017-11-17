#pragma once
#include <atomic>
#include <stdexcept>
#include <string>

#include <jni.h>

#include <cppjni/meta_declaration/method_scope_category.hpp>


namespace cppjni
{
namespace jniwrappers
{
    struct MethodIdStaticCache
    {
        template<typename class_path_t, typename method_overload_t, typename instance_container_t>
        jmethodID findMethodId(const instance_container_t& container) const
        {
            static jmethodID methodID = [&]{
                constexpr const char* methodName = method_overload_t::name_t::data();
                constexpr const char* jniTypeSignature = method_overload_t::jni_type_string_t::data();
                auto scopeCategory = method_overload_t::scope_category;
                jclass classReference = *container.jni_getClass();
                
                return findMethodId(methodName, jniTypeSignature, classReference, scopeCategory);
            }();
            return methodID;
        }
    private:
        jmethodID findMethodId(const char* methodName, const char* jniTypeSignature, jclass classReference, metadeclaration::MethodScopeCategory scopeCategory) const;
    };
}
}