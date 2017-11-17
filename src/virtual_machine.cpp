#include <cppjni/virtual_machine.hpp>

#include <iostream>
#include <stdexcept>
#include <string>

#include <cppjni/jni_wrappers/environment.hpp>

namespace cppjni
{

    using namespace std;

    VirtualMachine::VirtualMachine()
        :VirtualMachine(JniVersion::VERSION_LATEST)
    {
    }

    VirtualMachine::VirtualMachine(JniVersion version)
        :VirtualMachine(vector<string>(), version)
    {
    }

    VirtualMachine::VirtualMachine(const vector<string>& programOptions, JniVersion version)
    {
        JavaVMInitArgs initArgs;
        
        vector<JavaVMOption> options;
        options.reserve(programOptions.size() + 2);
        for(const auto& option : programOptions)
            options.push_back(JavaVMOption{const_cast<char*>(option.data()), nullptr});
        
        options.push_back(JavaVMOption{const_cast<char*>("abort"), (void*)VirtualMachine::abort});
        options.push_back(JavaVMOption{const_cast<char*>("exit"), (void*)VirtualMachine::exit});

        initArgs.version = (jint)version;
        initArgs.nOptions = (jint)options.size();
        initArgs.options = options.data();
        initArgs.ignoreUnrecognized = false;
        JNIEnv* mainEnvironment;
        int returnCode = JNI_CreateJavaVM(&virtualMachine, (void**)&mainEnvironment, &initArgs);
        if(returnCode == JNI_OK)
            jniwrappers::Environment::initializeMainEnvironment(virtualMachine, mainEnvironment, version);
        else
        {
            virtualMachine = nullptr;
            throw runtime_error("Failed to instantiate Java Virtual Machine with error: " + to_string(returnCode));
        }
    }
    
    VirtualMachine::~VirtualMachine()
    {
        if(virtualMachine)
        {
            concepts::StaticList<jniwrappers::GlobalReference<jclass>> list;
            for(auto& classRef: list)
                classRef.release();
            
            int returnCode = virtualMachine->DestroyJavaVM();
            if(returnCode != JNI_OK)
                cerr << "Virtual Machine destruction failed with error code: " << returnCode << endl;
            virtualMachine = nullptr;
            jniwrappers::Environment::deinitializeMainEnvironment();
        }
    }

    void VirtualMachine::abort()
    {
        cerr << "VM aborted!" << endl;
    }

    void VirtualMachine::exit(int exitCode)
    {
        cerr << "VM exited with exit code: " << exitCode << endl;
    }

}