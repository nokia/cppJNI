#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

#include <cppjni/method_signature.hpp>
#include <cppjni/virtual_machine.hpp>
#include <cppjni/jni_exception.hpp>

#include <jni/test/JNITest.hpp>
#include "VMInstance.hpp"

namespace test
{
namespace cppjni
{

using namespace ::cppjni;
using namespace ::cppjni::types;
using namespace std;
    
class VirtualMachineShould: public ::testing::Test
{
public:
};

TEST_F(VirtualMachineShould, returnClass)
{
    auto theClass = getVM().loadClass<JNITest>();
    EXPECT_EQ(12345, theClass.staticReturningPrimitive());
}

template<typename T>
struct BadClass: T
{
    using T::T;
    using class_path_t = typestring_is("bad/class/path");
};

TEST_F(VirtualMachineShould, throwWhenClassWasntFound)
{
    EXPECT_THROW(getVM().loadClass<BadClass>(), JniException);
}

}
}
