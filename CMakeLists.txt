cmake_minimum_required(VERSION 3.5)
project(cppJNI)
set(CMAKE_CXX_STANDARD 14)

# Extend CMAKE_PREFIX_PATH with HanaConfig.cmake and Gtest root
#list(APPEND CMAKE_PREFIX_PATH "")
#SET(GTEST_ROOT "")
enable_testing()

find_package(Threads REQUIRED)
find_package(Hana REQUIRED)
add_definitions(-DUSE_TYPESTRING=8)

if (CMAKE_CXX_COMPILER MATCHES GCC)
    add_compile_options(-ftemplate-depth-1024 -ftemplate-backtrace-limit=0 -Wno-gnu-string-literal-operator-template)
elseif (CMAKE_CXX_COMPILER MATCHES LLVM)
    SET(CMAKE_CXX_FLAGS_DEBUG " -Wno-error=ignored-attributes -Wno-error=unused-command-line-argument -Wno-error=deprecated-declarations ${CMAKE_CXX_FLAGS_DEBUG}")
    SET(CMAKE_CXX_FLAGS_RELEASE " -Wno-error=ignored-attributes -Wno-error=unused-command-line-argument -Wno-error=deprecated-declarations ${CMAKE_CXX_FLAGS_RELEASE}")
endif ()

add_subdirectory(src)
add_subdirectory(tst)
