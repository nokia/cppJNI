#include <cppjni/jni_wrappers/find_class.hpp>

#include <stdexcept>
#include <string>

#include <cppjni/jni_wrappers/environment.hpp>
#include <cppjni/jni_wrappers/exception_check.hpp>
#include <cppjni/jni_wrappers/local_reference.hpp>

using namespace std;

namespace cppjni
{
namespace jniwrappers
{
    LocalReference<jclass> find_class::operator()(const char* className) const
    {
        Environment env;
        jclass foundClass = env->FindClass(className);
        exception_check exceptionCheck;
        exceptionCheck();
        if(foundClass != nullptr)
            return LocalReference<jclass>{foundClass};
        else
            throw invalid_argument("Couldn't find class " + string(className) + "!");
    }
}
}