#pragma once
#include <string>
#include <vector>

#include <boost/hana/type.hpp>
#include <boost/noncopyable.hpp>

#include <jni.h>

#include "concepts/static_list.hpp"
#include "jni_wrappers/class_loader.hpp"
#include "jni_version.hpp"
#include "types/class.hpp"

namespace cppjni
{
    class VirtualMachine: boost::noncopyable
    {
    public:
        VirtualMachine(const std::vector<std::string>& programOptions, JniVersion version);
        VirtualMachine(JniVersion version);
        VirtualMachine();
        ~VirtualMachine();
        
        template<template<typename> class ClassDefinition>
        auto loadClass();
        
    private:
        jclass getClassUsingCache(const std::string& className);
        
        static void exit(int exitCode);
        static void abort();
        
        JavaVM* virtualMachine;
    };
    
    template<template<typename> class ClassDefinition>
    auto VirtualMachine::loadClass()
    {
        using result_t = types::Class<ClassDefinition>;
        using class_path_t = typename result_t::class_path_t;
        using class_loader_t = jniwrappers::ClassLoader<class_path_t>;
        
        concepts::StaticList<jniwrappers::GlobalReference<jclass>> list;
        return result_t(list.get<class_loader_t>());
    }
}