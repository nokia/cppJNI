project(cppJNITest)

# Java part ------------
find_package(Java REQUIRED)
include(UseJava)

set(JAVA_HOME $ENV{JAVA_HOME})
set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")

add_jar(jni.test test_subject/jni/test/JNITest.java)

get_target_property(_jarFile jni.test JAR_FILE)
get_target_property(_classDir jni.test CLASSDIR)


# C++ part  ------------
set(SOURCES
#     jni_mpl_should.cpp
    ClassShould.cpp
    ObjectShould.cpp
    PredefinedShould.cpp
    VirtualMachineShould.cpp
    VMInstance.cpp
)
set(HEADERS
    test_subject/jni/test/JNITest.hpp
    VMInstance.hpp
)

include_directories(
    $<TARGET_PROPERTY:cppJNI,INCLUDE_DIRECTORIES>
    test_subject/
    ${GTEST_INCLUDE_DIR}
    ${GMOCK_INCLUDE_DIR}
)

add_definitions(-DBOOST_HANA_CONFIG_ENABLE_DEBUG_MODE)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_dependencies(${PROJECT_NAME} jni.test)
target_link_libraries(${PROJECT_NAME}
    -L${GTEST_LIBRARY_DIR}
    -L${GMOCK_LIBRARY_DIR}
    gtest
    gmock
    gmock_main
    cppJNI
    ${JNI_LIBRARIES}
    pthread
)

add_test(
    NAME CppJNITest
    COMMAND ${PROJECT_NAME}
)