#include <cppjni/jni_wrappers/exception_check.hpp>

#include <cppjni/jni_exception.hpp>
#include <cppjni/jni_wrappers/environment.hpp>
#include <cppjni/jni_wrappers/local_reference.hpp>
#include <cppjni/predefined/java/lang/throwable.hpp>
#include <cppjni/types/object_converter.hpp>


using namespace std;

namespace cppjni
{
namespace jniwrappers
{
    void exception_check::operator()() const
    {
        Environment env;
        LocalReference<jobject> exceptionRef{env->ExceptionOccurred()};
        if(exceptionRef)
        {
            env->ExceptionClear();
            
            types::ObjectConverter<types::Object<predefined::java::lang::Throwable>> converter;
            auto exceptionObject = converter.convertFromJni(std::move(exceptionRef));
            throw JniException(move(exceptionObject));
        }
    }
}
}