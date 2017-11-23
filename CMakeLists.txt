cmake_minimum_required(VERSION 3.5)
project(cppJNI)

enable_testing()

find_package(Boost 1.61 REQUIRED)

add_definitions(-DUSE_TYPESTRING=8)

add_compile_options(-std=c++14 -ftemplate-depth-1024 -ftemplate-backtrace-limit=0 -Wno-gnu-string-literal-operator-template)

add_subdirectory(src)
add_subdirectory(tst)