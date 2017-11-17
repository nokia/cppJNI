#pragma once
#include "meta_declaration/generate_overloaded_method_declarations.hpp"
#include "meta_declaration/generate_overloaded_constructor_declarations.hpp"
#include "meta_declaration/method_scope_category.hpp"
#include "meta_declaration/scoped_declaration.hpp"
#include "method_call/method_caller.hpp"
#include "types/class.hpp"
#include "types/object.hpp"
#include "types/primitives.hpp"
#include "types/string.hpp"


namespace cppjni
{
    using metadeclaration::Method;
    using metadeclaration::StaticMethod;
    
    using types::Boolean;
    using types::Byte;
    using types::Char;
    using types::Short;
    using types::Int;
    using types::Long;
    using types::Float;
    using types::Double;
    using types::Void;
    using types::String;
}

#define MAKE_JAVA_METHOD(functionName, ...) \
using jni_##functionName##_overloads_t = ::cppjni::metadeclaration::generate_overloaded_method_declarations<typestring_is(#functionName), __VA_ARGS__>; \
 \
template<typename ...args_t> \
auto functionName(args_t&&... args) const \
{ \
    using container_type_t = \
        typename ::cppjni::mpl::condition<std::is_base_of<::cppjni::types::ClassContainer, typename std::decay<decltype(*this)>::type>::value> \
        ::template f< \
            ::cppjni::types::ClassContainer, \
            ::cppjni::types::ObjectContainer \
        >;\
    return ::cppjni::methodcall::method_caller<class_path_t, jni_##functionName##_overloads_t, container_type_t>::call(*this, std::forward<args_t>(args)...); \
}

#define MAKE_JAVA_CONSTRUCTOR(...) \
using jni_constructor_overloads_t = ::cppjni::metadeclaration::generate_overloaded_constructor_declarations<__VA_ARGS__>; \
 \
template<typename ...args_t> \
auto Construct(args_t&&... args) const \
{ \
    using container_type_t = \
        typename ::cppjni::mpl::condition<std::is_base_of<::cppjni::types::ClassContainer, typename std::decay<decltype(*this)>::type>::value> \
        ::template f< \
            ::cppjni::types::ClassContainer, \
            ::cppjni::types::ObjectContainer \
        >;\
    return ::cppjni::methodcall::method_caller<class_path_t, jni_constructor_overloads_t, container_type_t>::call(*this, std::forward<args_t>(args)...); \
}

//Helper macro for manual Java class description
#define MAKE_JAVA_GETTER_SETTER(fieldName, fieldType) \
    MAKE_JAVA_METHOD(get##fieldName, cppjni::Method<fieldType()>); \
    MAKE_JAVA_METHOD(set##fieldName, cppjni::Method<cppjni::Void(fieldType)>)
