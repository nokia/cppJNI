#include <cppjni/jni_wrappers/environment.hpp>

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace cppjni
{
namespace jniwrappers
{
    
    using namespace std;
        
    struct EnvironmentContext
    {
        bool isMainThread;
        JNIEnv* env;
        size_t refcount;
    };
    
    constexpr EnvironmentContext NULL_ENVIRONMENT_CONTEXT{false, nullptr, 0};

    static thread_local EnvironmentContext environment{false, nullptr, 0};
    static JavaVM* virtualMachine = nullptr;
    static JniVersion jniVersion = JniVersion::VERSION_1_8;

    Environment::Environment()
    {
        if(environment.env == nullptr)
        {
            if(virtualMachine != nullptr)
            {
                environment = NULL_ENVIRONMENT_CONTEXT;
                jint result = virtualMachine->GetEnv((void**)&environment.env, (jint)jniVersion);
                if(result == JNI_EDETACHED)
                {
                    result = virtualMachine->AttachCurrentThread((void**)&environment.env, nullptr);
                    if(result != JNI_OK)
                    {
                        environment.env = nullptr;
                        throw runtime_error("Couldn't attach current thread to VM! Error code: " + to_string(result));
                    }
                }
                else 
                {
                    environment.env = nullptr;
                    if(result == JNI_EVERSION)
                        throw runtime_error("Error during attaching native thread to VM: unsupported version " + to_string((jint)jniVersion) + "!");
                    else
                        throw runtime_error("Undefined error during attaching native thread to VM!");
                }
            }
            else
                throw runtime_error("No JNIEnv! Have you forgot to initialize Java virtual machine?");
        }
        
        ++environment.refcount;
    }

    Environment::~Environment()
    {
        --environment.refcount;
        if(environment.refcount == 0 && !environment.isMainThread)
        {
            jint result = virtualMachine->DetachCurrentThread();
            if(result == JNI_OK)
                environment = NULL_ENVIRONMENT_CONTEXT;
            else
                cerr << "Detaching of native thread failed! Error code: " << result << endl;
        }
    }

    JNIEnv* Environment::operator->()
    {
        return environment.env;
    }

    void Environment::initializeMainEnvironment(JavaVM* vm, JNIEnv* mainEnvironment, JniVersion version)
    {
        environment.env = mainEnvironment;
        environment.isMainThread = true;
        environment.refcount = 0;
        virtualMachine = vm;
        jniVersion = version;
    }

    void Environment::deinitializeMainEnvironment()
    {
        environment = NULL_ENVIRONMENT_CONTEXT;
        virtualMachine = nullptr;
    }

}
}