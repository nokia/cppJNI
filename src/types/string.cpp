#include <cppjni/types/string.hpp>
#include <memory>

namespace cppjni
{
namespace types
{
    String::jni_t String::convertToJni(const String::native_t& nativeValue) const
    {
        return convertToJni(nativeValue.data());
    }
    
    String::jni_t String::convertToJni(const char* nativeValue) const
    {
        if(nativeValue != nullptr)
        {
            jniwrappers::Environment env;
            jstring result = env->NewStringUTF(nativeValue);
            if(!result)
                throw std::runtime_error("Couldn't convert native string to Java String! Native value: " + std::string(nativeValue));
            return result;
        }
        else
            return nullptr;
    }
    
    String::native_t String::convertFromJni(String::jni_t value) const
    {
        jniwrappers::Environment env;
        std::string result;
        
        auto deleter = [&](auto toDelete){env->ReleaseStringUTFChars(value, toDelete);};
        std::unique_ptr<const char, decltype(deleter)> chars{env->GetStringUTFChars(value, nullptr), deleter};
        
        if(chars)
            result = chars.get();
        else
            throw std::runtime_error("Couldn't convert to native string from Java String!");
        
        return result;
    }
}
}