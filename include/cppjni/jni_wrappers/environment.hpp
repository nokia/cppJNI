#pragma once
#include <boost/noncopyable.hpp>

#include <jni.h>

#include <cppjni/jni_version.hpp>
#include <cppjni/virtual_machine.fwd.hpp>

namespace cppjni
{
namespace jniwrappers
{
    /**
     * Takes care of initializing (if necessary) JNI environment. This class is intended to work as a stack-only class, it must not be created on heap!
     */
    class Environment: public boost::noncopyable
    {
        friend class ::cppjni::VirtualMachine;
        
    public:
        /**
         * @throw std::runtime_error if called without Java virtual machine up and running
         */
        Environment();
        ~Environment();
        
        Environment(Environment&&) = delete;
        void operator=(Environment&&) = delete;
        
        JNIEnv* operator->();
        
    private:
        static void initializeMainEnvironment(JavaVM* vm, JNIEnv* mainEnvironment, JniVersion version);
        static void deinitializeMainEnvironment();
    };
}
}