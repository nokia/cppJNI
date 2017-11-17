#pragma once
#include <cppjni/jni_wrappers/generate_jni_signature_string.hpp>
#include <cppjni/mpl/condition.hpp>
#include <cppjni/types/primitives.hpp>

/**
* In order to call JNI constructor you have to:
*  - find it's method id using GetMethodID instead of GetStaticMethodID:
*      * "&lt;init&gt;" as method name
*      * void as it's return type in it's signature (constructor arguments stay the same)
*  - call separate method "NewObject" with the same parameters as with regular static method call
* This means that in Java, constructor is more an instance method rather than static - which was counterintuitive to me at first.
* Metafunctions in this file cover subsituting return type with void in constructor method signature string.
*/
namespace cppjni
{
namespace metadeclaration
{
    namespace detail
    {
        template<typename F>
        struct replace_return_with_void;
        
        template<typename return_t, typename ...args_t>
        struct replace_return_with_void<return_t(args_t...)>
        {
            using type = types::Void(args_t...);
        };
        
        struct voided_return_type_sig_string 
        {
            template<typename T>
            using f = typename jniwrappers::generate_jni_signature_string<
                                                    typename detail::replace_return_with_void<
                                                        typename T::original_signature_t
                                                    >::type
                                                >::type;
        };
        struct original_return_type_sig_string 
        {
            template<typename T>
            using f = typename T::jni_type_string_t;
        };
    }
    template<typename method_name_t, typename sig_info_t>
    using jni_constructor_signature_hack = typename mpl::condition<
                                             std::is_same<method_name_t, jniwrappers::constructor_method_name_t>::value
                                           >::template f<
                                                detail::voided_return_type_sig_string,
                                                detail::original_return_type_sig_string
                                           >::template f<sig_info_t>;
}
}