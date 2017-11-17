#pragma once
#include <exception>
#include <utility>

#include "types/object.hpp"
#include "predefined/java/lang/throwable.hpp"

namespace cppjni
{
    //TODO: derive after standard exception, implement what()
    class JniException
    {
    public:
        using throwable_t = types::Object<predefined::java::lang::Throwable>;
        
        JniException(throwable_t&& throwable)
            :throwable(std::move(throwable))
        {}
        
        const throwable_t& getThrowable() const
        {
            return throwable;
        }
        
        throwable_t& getThrowable()
        {
            return throwable;
        }
        
    private:
        throwable_t throwable;
    };
}