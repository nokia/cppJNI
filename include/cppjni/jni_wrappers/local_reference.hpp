#pragma once
#include "local_reference.fwd.hpp"

#include <stdexcept>

#include <boost/hana/core/when.hpp>

#include <jni.h>

#include <cppjni/concepts/is_jni_reference_type.hpp>

#include "environment.hpp"

namespace cppjni
{
namespace jniwrappers
{
    template<typename jni_reference_type_t>
    class LocalReference<jni_reference_type_t, boost::hana::when<concepts::is_jni_reference_type<jni_reference_type_t>>>
    {
    public:
        LocalReference(jni_reference_type_t reference);
        LocalReference(LocalReference&& toMove);
        ~LocalReference();

        operator bool() const {return localRef != nullptr;}

        LocalReference() = delete;
        void operator=(LocalReference&& toMove) = delete;
        LocalReference(const LocalReference&) = delete;
        LocalReference& operator=(const LocalReference& toMove) = delete;
        jni_reference_type_t operator*() const;

    private:
        jni_reference_type_t localRef;
    };

    template<typename jni_reference_type_t>
    LocalReference<jni_reference_type_t, boost::hana::when<concepts::is_jni_reference_type<jni_reference_type_t>>>
        ::LocalReference(LocalReference&& toMove)
            :localRef(toMove.localRef)
    {
        toMove.localRef = nullptr;
    }

    template<typename jni_reference_type_t>
    LocalReference<jni_reference_type_t, boost::hana::when<concepts::is_jni_reference_type<jni_reference_type_t>>>
        ::LocalReference(jni_reference_type_t reference)
            :localRef(reference)
    {
    }

    template<typename jni_reference_type_t>
    LocalReference<jni_reference_type_t, boost::hana::when<concepts::is_jni_reference_type<jni_reference_type_t>>>
        ::~LocalReference()
    {
        if(localRef != nullptr)
        {
            Environment env;
            env->DeleteLocalRef(localRef);
        }
    }

    template<typename jni_reference_type_t>
    jni_reference_type_t LocalReference<jni_reference_type_t, boost::hana::when<concepts::is_jni_reference_type<jni_reference_type_t>>>
        ::operator*() const
    {
        return localRef;
    }
}
}