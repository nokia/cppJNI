#pragma once
#include <boost/noncopyable.hpp>

#include "jni_wrappers/environment.hpp"

namespace cppjni
{
    /**
     * JniThreadHint object is a hint for framework, that current native thread is used inside Java thread (or around its instance).
     * Nothing wrong happens if you ignore instantiating it, but this way you'll able to optimize your code by not attaching and detaching 
     * native thread to JVM multiple times.
     * 
     * How this can happen? New native thread, in order to call any Java method, has to be "attached" to JVM. Attaching happens during first
     * Java call. This operation, among other things, creates java.lang.Thread instance. But since framework does not know when you've stopped 
     * using your native thread, it's immediately detached. If, for example, you're calling some Java method in loop multiple times, that many
     * java.lang.Thread objects will be created. To overcome this issue, below class was created.
     * 
     * Usage: create its instance at the beginning of manually created native thread in which you are using Java.
     */
    class JniThreadHint: boost::noncopyable
    {
    public:
        JniThreadHint() = default;
        ~JniThreadHint() = default;
        
        JniThreadHint(JniThreadHint&&) = delete;
        void operator=(JniThreadHint&&) = delete;
        
    private:
        cppjni::jniwrappers::Environment env;
    };
}