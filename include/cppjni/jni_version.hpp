#pragma once
#include <jni.h>

namespace cppjni
{
    enum class JniVersion: jint
    {
        VERSION_1_1 = JNI_VERSION_1_1,
        VERSION_1_2 = JNI_VERSION_1_2,
        VERSION_1_4 = JNI_VERSION_1_4,
        VERSION_1_6 = JNI_VERSION_1_6,
        VERSION_1_8 = JNI_VERSION_1_8,
        
        VERSION_LATEST = VERSION_1_8
    };
}