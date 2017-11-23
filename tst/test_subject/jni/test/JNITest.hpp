#pragma once
#include <cppjni/concepts/string_type.hpp>
#include <cppjni/method_signature.hpp>
#include <cppjni/predefined/java/lang/object.hpp>
#include <cppjni/predefined/java/lang/string.hpp>
#include <cppjni/predefined/java/util/list.hpp>

namespace test
{
namespace cppjni
{
    namespace cj = ::cppjni;
    namespace java = cj::predefined::java;
    
    template<typename T>
    struct JNITest: virtual java::lang::Object<T>
    {
        using class_path_t = string_type_is("jni/test/JNITest");

        MAKE_JAVA_CONSTRUCTOR(cj::types::Object<::test::cppjni::JNITest>(cj::Int, cj::String))
        
        MAKE_JAVA_METHOD(getPrimitiveField,  cj::Method<cj::Int()>)
        MAKE_JAVA_METHOD(getPrimitiveField2, cj::Method<cj::Int()>)
        MAKE_JAVA_METHOD(getObjectField, cj::Method<cj::types::Object<::test::cppjni::JNITest>()>)
        MAKE_JAVA_METHOD(getStringField, cj::Method<cj::String()>)
        MAKE_JAVA_METHOD(setStringField, 
                            cj::Method<cj::Void(cj::types::Object<java::lang::String>)>, 
                            cj::Method<cj::Void(cj::String)>
        )
        MAKE_JAVA_METHOD(incrementIntField, cj::Method<cj::Void(cj::Int)>)
        MAKE_JAVA_METHOD(staticReturningPrimitive,
                            cj::StaticMethod<cj::Int()>, 
                            cj::StaticMethod<cj::Long(cj::Int)>
        )
        MAKE_JAVA_METHOD(staticReturningString, cj::StaticMethod<cj::String(cj::String)>)
        MAKE_JAVA_METHOD(staticVoid, cj::StaticMethod<cj::Void()>)
        MAKE_JAVA_METHOD(staticFactory, 
                         cj::StaticMethod<cj::types::Object<::test::cppjni::JNITest>()>, 
                         cj::StaticMethod<cj::types::Object<::test::cppjni::JNITest>(cj::Int, cj::String)>
        )
        MAKE_JAVA_METHOD(throwException, cj::Method<cj::Void()>)
        MAKE_JAVA_METHOD(getStringList, cj::StaticMethod<cj::types::Object<java::util::List>()>)
    };
}
}