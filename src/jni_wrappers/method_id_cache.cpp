#include <cppjni/jni_wrappers/method_id_cache.hpp>

#include <cppjni/jni_wrappers/environment.hpp>

namespace cppjni
{
namespace jniwrappers
{
    jmethodID MethodIdStaticCache::findMethodId(const char* methodName, const char* jniTypeSignature, jclass classReference, metadeclaration::MethodScopeCategory scopeCategory) const
    {
        jmethodID methodID = nullptr;
        Environment env;
        switch(scopeCategory)
        {
            case metadeclaration::MethodScopeCategory::STATIC: 
                methodID = env->GetStaticMethodID(classReference, methodName, jniTypeSignature);
                break;
                
            case metadeclaration::MethodScopeCategory::INSTANCE:
            case metadeclaration::MethodScopeCategory::CONSTRUCTOR:
                methodID = env->GetMethodID(classReference, methodName, jniTypeSignature);
                break;
        }
        if(methodID == nullptr)
        {
            //TODO: change to some more meaningful exception type
            throw std::runtime_error(
                std::string("Couldn't find class method! Name: ") + methodName + " with signature: " + jniTypeSignature
            );
        }
        return methodID;
    }

}
}