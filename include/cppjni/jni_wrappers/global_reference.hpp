#pragma once
#include <iostream>

#include "global_reference.fwd.hpp"
#include "environment.hpp"
#include "local_reference.hpp"

namespace cppjni
{
namespace jniwrappers
{
    template<typename jni_reference_type_t>
    class GlobalReference: boost::noncopyable
    {
    public:
        GlobalReference(const LocalReference<jni_reference_type_t>& localReference);
        GlobalReference(GlobalReference&& toMove);
        ~GlobalReference();
        
        GlobalReference& operator=(GlobalReference&& toMove);
        
        GlobalReference() = delete;
        
        operator bool() const {return globalRef != nullptr;}
        
        jni_reference_type_t operator*() const;
        
        GlobalReference copyReference() const;
        
        void swap(GlobalReference& toSwap);
        
        void release()
        {
            if(globalRef != nullptr)
            {
                try
                {
                    Environment env;
                    env->DeleteGlobalRef(globalRef);
                }
                catch(const std::runtime_error& e)
                {
                    std::cerr << "Exception during deleting of GlobalReference: " << e.what() << std::endl;
                }
            }
        }
        
    private:
        GlobalReference(jni_reference_type_t globalRef);
        
        jni_reference_type_t globalRef;
    };
    
    template<typename jni_reference_type_t>
    GlobalReference<jni_reference_type_t>::GlobalReference(const LocalReference<jni_reference_type_t>& localReference)
        :globalRef(nullptr)
    {
        if(*localReference != nullptr)
        {
            Environment env;
            globalRef = (jni_reference_type_t)env->NewGlobalRef(*localReference);
            if(globalRef == nullptr)
                throw std::runtime_error("Couldn't create global reference!");
        }
    }
    
    template<typename jni_reference_type_t>
    GlobalReference<jni_reference_type_t>::GlobalReference(GlobalReference&& toMove)
        :globalRef(toMove.globalRef)
    {
        toMove.globalRef = nullptr;
    }
    
    template<typename jni_reference_type_t>
    GlobalReference<jni_reference_type_t>::~GlobalReference()
    {
        release();
    }
    
    template<typename jni_reference_type_t>
    GlobalReference<jni_reference_type_t>& 
        GlobalReference<jni_reference_type_t>::operator=(GlobalReference&& toMove)
    {
        GlobalReference newRef{std::move(toMove)};
        this->swap(newRef);
        return *this;
    }
    
    template<typename jni_reference_type_t>
    jni_reference_type_t GlobalReference<jni_reference_type_t>::operator*() const
    {
        return globalRef;
    }
    
    template<typename jni_reference_type_t>
    GlobalReference<jni_reference_type_t> GlobalReference<jni_reference_type_t>::copyReference() const
    {
        Environment env;
        if(globalRef != nullptr)
        {
            auto newRef = env->NewGlobalRef(globalRef);
            if(newRef != nullptr)
                return GlobalReference<jni_reference_type_t>(newRef);
            else
                throw std::runtime_error("Couldn't create global reference!");
        }
        else
            throw std::runtime_error("Tried to copy null global refererence!");
    }
    
    template<typename jni_reference_type_t>
    void GlobalReference<jni_reference_type_t>::swap(GlobalReference<jni_reference_type_t>& toSwap)
    {
        std::swap(this->globalRef, toSwap.globalRef);
    }
    
    template<typename jni_reference_type_t>
    GlobalReference<jni_reference_type_t>::GlobalReference(jni_reference_type_t newRef)
        :globalRef(newRef)
    {
    }
}
}