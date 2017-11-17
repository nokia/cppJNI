#pragma once
#include <stdexcept>
#include <utility>
#include <type_traits>

#include <boost/noncopyable.hpp>

#include <jni.h>

#include <cppjni/concepts/is_java_class_definition.hpp>
#include <cppjni/jni_wrappers/global_reference.hpp>
#include <cppjni/predefined/java/lang/object.fwd.hpp>

#include <cppjni/java_cast.fwd.hpp>
#include <cppjni/native_cast.fwd.hpp>

#include "base_object_container.hpp"
#include "object_converter.fwd.hpp"
#include "string.fwd.hpp"

namespace cppjni
{
namespace types
{
    class ObjectContainer: public BaseObjectContainer
    {
    public:
        using isClassScope = std::false_type;
        
        virtual const jniwrappers::GlobalReference<jobject>& jni_getObject() const & = 0;
        virtual jniwrappers::GlobalReference<jobject>&& jni_getObject() && = 0;
    };
    
    template<template<typename> class class_definition_template_t>
    class Object final: public class_definition_template_t<ObjectContainer>, public boost::noncopyable
    {
        friend class ObjectConverter<Object>;
        
        template<template<typename> class friend_definition_template_t>
        friend class ::cppjni::detail::java_cast;
        
        template<typename converter_t, template<typename> class friend_definition_template_t>
        friend typename converter_t::native_t (::cppjni::native_cast)(const types::Object<friend_definition_template_t>& toConvert);
        
    public:
        using base_t = class_definition_template_t<ObjectContainer>;
        static_assert(concepts::is_java_class_definition<base_t>, "Declared class is not a class definition!");
        
        using class_path_t = typename base_t::class_path_t;
        
        using base_t::base_t;
        
        Object(Object&& toMove)
            :jniClass(toMove.jni_getClass()),
             jniObject(std::move(toMove).jni_getObject())
        {
        }
        
        //TODO: move assignment
        
        Object() = delete;
        
        ~Object() = default;
        
    private:
        Object(const jniwrappers::GlobalReference<jclass>& jniClass, jniwrappers::GlobalReference<jobject>&& jniObject)
            :jniClass(jniClass),
            jniObject(std::move(jniObject))
        {
        }
        
        const jniwrappers::GlobalReference<jclass>& jni_getClass() const override
        {
            return jniClass;
        }
        const jniwrappers::GlobalReference<jobject>& jni_getObject() const & override
        {
            return jniObject;
        }
        jniwrappers::GlobalReference<jobject>&& jni_getObject() && override
        {
            return std::move(jniObject);
        }
        
        const jniwrappers::GlobalReference<jclass>& jniClass;
        jniwrappers::GlobalReference<jobject> jniObject;
        
    };

}
}