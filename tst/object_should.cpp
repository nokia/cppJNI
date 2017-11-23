#include <thread>

#include <gtest/gtest.h>

#include <cppjni/jni_exception.hpp>
#include <cppjni/jni_thread_hint.hpp>
#include <cppjni/virtual_machine.hpp>

#include <jni/test/JNITest.hpp>
#include "vm_instance.hpp"

namespace test
{
namespace cppjni
{

using namespace ::cppjni;
using namespace ::cppjni::types;
using namespace std;

struct ObjectShould: ::testing::Test
{
    ObjectShould()
        :jniClass(getVM().loadClass<JNITest>())
    {}
protected:
    Class<JNITest> jniClass;
};

TEST_F(ObjectShould, callParameterlessMethod)
{
    auto testObject = jniClass.staticFactory();
    
    EXPECT_EQ(12345, testObject.getPrimitiveField());
    EXPECT_EQ(12345, testObject.getObjectField().getPrimitiveField());
}

TEST_F(ObjectShould, callMethodWithPrimitiveTypes)
{
    auto testObject = jniClass.Construct(5, "123");
    
    EXPECT_EQ(5, testObject.getPrimitiveField());
    EXPECT_EQ(5 + 2, testObject.getPrimitiveField2());
    EXPECT_EQ("123", testObject.getStringField());
    testObject.incrementIntField(10);
    EXPECT_EQ(15, testObject.getPrimitiveField());
}
/* TODO: Fix this
TEST_F(ObjectShould, callMethodWithBothConverterOrJavaObjectInItsSignature)
{
    auto testObject = jniClass.Construct(5, "123");
    testObject.setStringField("qwe");
    EXPECT_EQ("qwe", testObject.getStringField());
    auto testString = getVM().loadClass<::cppjni::predefined::java::lang::String>().Construct("asd");
    testObject.setStringField(testString);
    EXPECT_EQ("asd", testObject.getStringField());
}*/

TEST_F(ObjectShould, throwException)
{
    auto theObject = jniClass.Construct(5, "");
    ASSERT_THROW(theObject.throwException(), JniException);
    
    try
    {
        theObject.throwException();
    }
    catch(JniException& e)
    {
        auto& throwable = e.getThrowable();
        EXPECT_EQ(string("Some message"), throwable.getMessage());
    }
}

TEST_F(ObjectShould, workOnSeparateThread)
{
    auto objectOnLocalThread = jniClass.Construct(0, "123");
    auto objectOnDifferentThread = jniClass.Construct(10000, "qweqwe");
    
    thread testThread([&]() {
        JniThreadHint guard;
        for(size_t i = 0; i < 10000; ++i)
            objectOnDifferentThread.incrementIntField(1);
    });
    for(size_t i = 0; i < 10000; ++i)
        objectOnLocalThread.incrementIntField(10);
    testThread.join();
    
    EXPECT_EQ(100000, objectOnLocalThread.getPrimitiveField());
    EXPECT_EQ(20000, objectOnDifferentThread.getPrimitiveField());
}

TEST_F(ObjectShould, constructOnSeparateThread)
{
    int result;
    thread testThread([&]() {
        JniThreadHint guard;
        auto objectOnLocalThread = jniClass.Construct(44, "123");
        result = objectOnLocalThread.getPrimitiveField();
    });
    testThread.join();
    ASSERT_EQ(44, result);
}

}
}