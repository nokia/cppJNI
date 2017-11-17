#pragma once
#include <type_traits>

#include <jni.h>

#include <cppjni/concepts/is_java_class_definition.hpp>
#include <cppjni/types/base_object_container.hpp>
#include <cppjni/virtual_machine.fwd.hpp>

namespace cppjni
{
namespace types
{
    class ClassContainer: public BaseObjectContainer
    {
    public:
        using isClassScope = std::true_type;
    };
    
    template<template<typename> class class_definition_template_t>
    class Class final: public class_definition_template_t<ClassContainer>, public boost::noncopyable
    {
        friend class ::cppjni::VirtualMachine;
        
    public:
        using base_t = class_definition_template_t<ClassContainer>;
        static_assert(concepts::is_java_class_definition<base_t>, "Declared class is not a class definition!");
        
        using class_path_t = typename base_t::class_path_t;
        
        using base_t::base_t;
        
        Class() = delete;
        
        Class(Class&& toMove)
            :jniClass(toMove.jni_getClass())
        {
        }
        
        //TODO: move assignment
        
        ~Class() = default;
        
    private:
        Class(const jniwrappers::GlobalReference<jclass>& jniClass)
            :jniClass(jniClass)
        {
        }
        const jniwrappers::GlobalReference<jclass>& jni_getClass() const override
        {
            return jniClass;
        }
        
        const jniwrappers::GlobalReference<jclass>& jniClass;
    };

}
}