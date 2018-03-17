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

find_package(GTest 1.8)
if (GTEST_FOUND)
    set(SOURCES
            mpl_should.cpp
            class_should.cpp
            object_should.cpp
            predefined_should.cpp
            virtual_machine_should.cpp
            vm_instance.cpp
            )
    set(HEADERS
            test_subject/jni/test/JNITest.hpp
            vm_instance.hpp
            )

    include_directories(
            $<TARGET_PROPERTY:cppJNI,INCLUDE_DIRECTORIES>
            test_subject/
    )
    add_definitions(-DBOOST_HANA_CONFIG_ENABLE_DEBUG_MODE)

    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
    add_dependencies(${PROJECT_NAME} jni.test)
    target_link_libraries(${PROJECT_NAME}
            GTest::GTest
            GTest::Main
            cppJNI
            ${JNI_LIBRARIES}
            Threads::Threads
            )

    add_test(
            NAME CppJNITest
            COMMAND ${PROJECT_NAME}
    )
endif ()
