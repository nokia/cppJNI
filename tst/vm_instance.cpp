#include "vm_instance.hpp"
#include <cppjni/virtual_machine.hpp>

namespace test 
{
namespace cppjni
{
    ::cppjni::VirtualMachine& getVM()
    {
        static ::cppjni::VirtualMachine testVM({
                "-Djava.class.path=jni.test.jar"
            },
            ::cppjni::JniVersion::VERSION_1_8
        );
        
        return testVM;
    }
}
}
