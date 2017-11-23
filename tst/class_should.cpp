#include <string>
#include <iostream>

#include <gtest/gtest.h>

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

struct ClassShould: ::testing::Test
{
    ClassShould()
        :jniClass(getVM().loadClass<JNITest>())
    {}
protected:
    Class<JNITest> jniClass;
};

TEST_F(ClassShould, callStaticMethodWithPrimitiveTypes)
{
    EXPECT_EQ(12345, jniClass.staticReturningPrimitive());
    EXPECT_EQ(654326, jniClass.staticReturningPrimitive(5));
}

TEST_F(ClassShould, callStaticMethodWithStringTypes)
{
    EXPECT_EQ(string("dudiduba") + "qwe123", jniClass.staticReturningString("dudiduba"));
    EXPECT_EQ(string("dudiduba") + "qwe123", jniClass.staticReturningString(string("dudiduba")));
}

TEST_F(ClassShould, callStaticMethodWithStringTypesWithNULLValue)
{
    const char* nullString1 = nullptr;
    const char nullString2[] = "";
    char nullString3[1] = "";
    const char* const nullString4 = nullptr;
    const char* const& nullString5 = nullString4;
    char* nullString6 = nullptr;
    char* const nullString7 = nullptr;
    
    EXPECT_EQ(string("nullqwe123"), jniClass.staticReturningString(nullString1));
    EXPECT_EQ(string("qwe123"), jniClass.staticReturningString(nullString2));
    EXPECT_EQ(string("qwe123"), jniClass.staticReturningString(nullString3));
    EXPECT_EQ(string("nullqwe123"), jniClass.staticReturningString(nullString4));
    EXPECT_EQ(string("nullqwe123"), jniClass.staticReturningString(nullString5));
    EXPECT_EQ(string("nullqwe123"), jniClass.staticReturningString(nullString6));
    EXPECT_EQ(string("nullqwe123"), jniClass.staticReturningString(nullString7));
}

TEST_F(ClassShould, callStaticVoidMethod)
{
    jniClass.staticVoid();
}

TEST_F(ClassShould, createNewObjectWithItsConstructor)
{
    auto object = jniClass.Construct(444, "555");
    EXPECT_EQ(444, object.getPrimitiveField());
    EXPECT_EQ(string("555"), object.getStringField());
}

}
}