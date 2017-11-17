#include <cppjni/jni_wrappers/call_static_method.hpp>
#include <cppjni/jni_wrappers/global_reference.hpp>
#include <cppjni/jni_wrappers/local_reference.hpp>

namespace cppjni
{
namespace jniwrappers
{
namespace detail
{
    #define MAKE_PRIMITIVE_SPECIALIZATION(jniType, name) \
    jniType do_call_static_method<jniType>::operator()(const GlobalReference<jclass>& jniClass, jmethodID methodID, ...) const \
    { \
        va_list args; \
        va_start(args, methodID); \
        jniwrappers::Environment env; \
        auto result = (jniType)env->CallStatic##name##MethodV((jclass)*jniClass, methodID, args); \
        va_end(args); \
        return result; \
    }
    
#define MAKE_OBJECT_SPECIALIZATION(jniType) \
    LocalReference<jniType> do_call_static_method<jniType>::operator()(const GlobalReference<jclass>& jniClass, jmethodID methodID, ...) const \
    { \
        va_list args; \
        va_start(args, methodID); \
        jniwrappers::Environment env; \
        auto result = (jniType)env->CallStaticObjectMethodV((jclass)*jniClass, methodID, args); \
        va_end(args); \
        return LocalReference<jniType>(result); \
    }
    
    void do_call_static_method<void>::operator()(const GlobalReference<jclass>& jniClass, jmethodID methodID, ...) const
    {
        va_list args;
        va_start(args, methodID);
        jniwrappers::Environment env;
        env->CallStaticVoidMethodV((jclass)*jniClass, methodID, args);
        va_end(args);
    }

    MAKE_PRIMITIVE_SPECIALIZATION(jboolean, Boolean);
    MAKE_PRIMITIVE_SPECIALIZATION(jbyte, Byte);
    MAKE_PRIMITIVE_SPECIALIZATION(jchar, Char);
    MAKE_PRIMITIVE_SPECIALIZATION(jshort, Short);
    MAKE_PRIMITIVE_SPECIALIZATION(jint, Int);
    MAKE_PRIMITIVE_SPECIALIZATION(jlong, Long);
    MAKE_PRIMITIVE_SPECIALIZATION(jfloat, Float);
    MAKE_PRIMITIVE_SPECIALIZATION(jdouble, Double);
    MAKE_OBJECT_SPECIALIZATION(jobject);
    MAKE_OBJECT_SPECIALIZATION(jstring);

#undef MAKE_PRIMITIVE_SPECIALIZATION
#undef MAKE_OBJECT_SPECIALIZATION
}
}
}
