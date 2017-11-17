#pragma once
#include <type_traits>

namespace cppjni
{
namespace concepts
{
    namespace detail
    {
        template<typename...>
        using void_t = void;
        
        template<typename T, typename = void>
        struct is_java_class_definition: std::false_type {};
        
        template<typename T>
        struct is_java_class_definition<T, void_t<typename T::class_path_t>>: std::true_type {};
    }

    template<typename T>
    constexpr auto is_java_class_definition = detail::is_java_class_definition<T>{};
}
}