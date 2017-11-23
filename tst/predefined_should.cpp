#include <gtest/gtest.h>

#include <cppjni/predefined/java/lang/class.hpp>
#include <cppjni/predefined/java/lang/object.hpp>
#include <cppjni/predefined/java/lang/throwable.hpp>
#include <cppjni/predefined/java/lang/string.hpp>
#include <cppjni/predefined/java/util/iterator.hpp>
#include <cppjni/predefined/java/util/list.hpp>
#include <cppjni/java_cast.hpp>
#include <cppjni/native_cast.hpp>
#include <cppjni/virtual_machine.hpp>

#include <jni/test/JNITest.hpp>
#include "vm_instance.hpp"

namespace test
{
namespace cppjni
{

using namespace ::cppjni;
using namespace ::cppjni::types;
using namespace ::cppjni::predefined;
using namespace std;

struct PredefinedShould: ::testing::Test
{
};

TEST_F(PredefinedShould, callParameterlessMethod)
{
    auto testClass = getVM().loadClass<java::lang::Object>();
    auto object = testClass.Construct();
    auto objectClass = object.getClass();
    
    EXPECT_EQ("Object", objectClass.getSimpleName());
    EXPECT_EQ("java.lang.Object", objectClass.getName());
}

TEST_F(PredefinedShould, returnGenericList)
{
    auto testClass = getVM().loadClass<JNITest>();
    auto stringList = testClass.getStringList();
    
    auto&& firstString = java_cast<java::lang::String>(stringList.get(0));
    auto&& secondString = java_cast<java::lang::String>(stringList.get(1));
    auto&& thirdString = java_cast<java::lang::String>(stringList.get(2));
    EXPECT_EQ("first", native_cast<String>(firstString));
    EXPECT_EQ("second", native_cast<String>(secondString));
    EXPECT_EQ("third", native_cast<String>(thirdString));
}

TEST_F(PredefinedShould, addStringElementsToList)
{
    auto testClass = getVM().loadClass<JNITest>();
    auto stringClass = getVM().loadClass<java::lang::String>();
    
    auto stringList = testClass.getStringList();
    auto stringObject = stringClass.Construct("newString");
    stringList.add(java_cast<java::lang::Object>(stringObject));
    
    auto&& lastString = java_cast<java::lang::String>(stringList.get(3));
    EXPECT_EQ("newString", native_cast<String>(stringObject));
    EXPECT_EQ("newString", native_cast<String>(lastString));
    //EXPECT_EQ("newString", native_cast<String>(stringList)); //shouldn't compile!
    EXPECT_EQ(true, lastString.equals(java_cast<java::lang::Object>(stringObject)));
}

}
}