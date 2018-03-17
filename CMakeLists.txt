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

add_compile_options(-ftemplate-depth-1024 -ftemplate-backtrace-limit=0 -Wno-gnu-string-literal-operator-template)

add_subdirectory(src)
add_subdirectory(tst)
