#pragma once
#include <type_traits>
#include <utility>

#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_with.hpp>
//#include <boost/static_assert.hpp>

#include <jni.h>

#include <cppjni/jni_wrappers/call_constructor.hpp>
#include <cppjni/jni_wrappers/call_static_method.hpp>
#include <cppjni/jni_wrappers/call_object_method.hpp>
#include <cppjni/jni_wrappers/generate_jni_signature_string.hpp>
#include <cppjni/jni_wrappers/current_environment.hpp>
#include <cppjni/jni_wrappers/method_id_cache.hpp>
#include <cppjni/meta_declaration/method_scope_category.hpp>
#include <cppjni/mpl/all.hpp>
#include <cppjni/mpl/filter.hpp>
#include <cppjni/mpl/find_if.hpp>
#include <cppjni/mpl/list.hpp>
#include <cppjni/mpl/optional.hpp>
#include <cppjni/mpl/pipeline.hpp>
#include <cppjni/mpl/size.hpp>
#include <cppjni/mpl/zip.hpp>

namespace cppjni
{
namespace methodcall
{
    template<bool is_class_scope>
    struct is_allowed_method_category;
    
    template<>
    struct is_allowed_method_category<true>
    {
        template<typename method_declaration_t>
        using f = std::integral_constant<
                    bool, 
                       method_declaration_t::scope_category == metadeclaration::MethodScopeCategory::STATIC 
                    || method_declaration_t::scope_category == metadeclaration::MethodScopeCategory::CONSTRUCTOR
                  >;
    };
    
    template<>
    struct is_allowed_method_category<false>
    {
        template<typename method_declaration_t>
        using f = std::integral_constant<
                    bool, 
                    method_declaration_t::scope_category  == metadeclaration::MethodScopeCategory::INSTANCE
                  >;
    };
    
    template<typename T>
    struct list_to_tuple;
    
    template<typename... Ts>
    struct list_to_tuple<mpl::list<Ts...>>
    {
        static constexpr auto value = boost::hana::make_tuple(Ts{}...);
    };
    
    template<std::size_t args_count>
    struct has_args_count
    {
        template<typename T>
        using f = std::integral_constant<bool, mpl::eager::size<typename T::arguments_t>::value == args_count>;
    };

    struct is_convertible
    {
        template<typename T1, typename T2>
        using f = typename T2::template isConvertible<T1>;
    };

    template<typename container_t, typename converted_args_t, typename method_name_t, typename jni_return_type_t>
    struct call_static_method
    {
        auto operator()(const container_t& container, jmethodID methodID, converted_args_t&& convertedArguments) const
        {
            auto&& caller =
                typename mpl::condition<std::is_same<method_name_t, jniwrappers::constructor_method_name_t>::value>::template f<
                    jniwrappers::call_constructor,
                    jniwrappers::call_static_method
                >{};
            return caller.template operator()<jni_return_type_t>(container.jni_getClass(), methodID, std::move(convertedArguments));
        }
    };
    
    template<typename container_t, typename converted_args_t, typename jni_return_type_t>
    struct call_object_method
    {
        auto operator()(const container_t& container, jmethodID methodID, converted_args_t&& convertedArguments) const
        {
            return jniwrappers::call_object_method{}.operator()<jni_return_type_t>(container.jni_getObject(), methodID, std::move(convertedArguments));
        }
    };
    
    template<typename container_t, typename scope_caller_t, typename converted_args_t>
    struct call_function_returning_void
    {
        void operator()(const container_t& container, jmethodID methodID, converted_args_t&& convertedArguments) const
        {
            constexpr jniwrappers::CurrentEnvironment env{};
            scope_caller_t{}(container, methodID, std::move(convertedArguments));
            env.exceptionCheck();
        }
    };
    
    template<typename container_t, typename return_type_converter_t, typename scope_caller_t, typename converted_args_t>
    struct call_function_returning_value
    {
        auto operator()(const container_t& container, jmethodID methodID, converted_args_t&& convertedArguments) const
        {
            constexpr jniwrappers::CurrentEnvironment env{};
            auto&& jniCallResult = scope_caller_t{}(container, methodID, std::move(convertedArguments));
            env.exceptionCheck();
            return return_type_converter_t{}.convertFromJni(std::move(jniCallResult));
        }
    };
    
    /**
     * Implementation of actual Java method call - both compile-time and run-time.
     */
    template<typename class_path_t, typename all_overloads_t, typename instance_container_t>
    struct method_caller
    {
        template<typename... passed_args_t>
        struct are_overloaded_args_convertible_to_passed_args
        {
            template<typename overload_decl_t>
            using f = 
                typename mpl::apply<
                    mpl::pipeline<
                        mpl::zip_with<is_convertible, passed_args_t...>,
                        mpl::all<mpl::is_true>
                    >,
                    typename overload_decl_t::arguments_t
                >::template continuation<mpl::identity>;
        };
        
        template<typename... passed_args_t>
        static auto call(const instance_container_t& container, passed_args_t&&... args)
        {
            jniwrappers::Environment env;
            (void)env;
            namespace hana = boost::hana;
            using namespace metadeclaration;
            
            using is_allowed_method_category_for_current_scope = is_allowed_method_category<instance_container_t::isClassScope::value>;
            
            using found_overload_t = 
                typename mpl::apply<
                    typename mpl::pipeline<
                        mpl::filter<is_allowed_method_category_for_current_scope::template f>,
                        mpl::filter<
                            has_args_count<
                                sizeof...(passed_args_t)
                            >::template f
                        >,
                        mpl::find_if<
                            are_overloaded_args_convertible_to_passed_args<passed_args_t...>::template f
                        >
                    >,
                    all_overloads_t
                >::template continuation<mpl::optional>;
            static_assert(
                found_overload_t::has_type::value == true,
                "Couldn't convert all parameters to appropriate overload!"
            );
            
            using selected_declaration_t = typename found_overload_t::type;
            jmethodID methodID = jniwrappers::MethodIdStaticCache{}.findMethodId<class_path_t, selected_declaration_t>(container);
            
            constexpr auto converters = list_to_tuple<typename selected_declaration_t::arguments_t>::value;
            auto&& passedArgs = hana::make_tuple(std::forward<passed_args_t>(args)...);
            auto&& convertedArguments = hana::zip_with(
                [](auto&& native, auto converter) {
                    return converter.convertToJni(native);
                },
                passedArgs, 
                converters
            );
            
            using method_name_t = typename selected_declaration_t::name_t;
            using return_t = typename selected_declaration_t::return_t;
            using jni_return_type_t = typename return_t::jni_t;
            using scope_caller_t = 
                typename mpl::condition<instance_container_t::isClassScope::value>::template f<
                    call_static_method<instance_container_t, decltype(convertedArguments), method_name_t, jni_return_type_t>,
                    call_object_method<instance_container_t, decltype(convertedArguments), jni_return_type_t>
                >;
                
            using return_result_t = typename return_t::native_t;
            using result_returner_t = 
                typename mpl::condition<std::is_same<return_result_t, void>::value>::template f<
                    call_function_returning_void<instance_container_t, scope_caller_t, decltype(convertedArguments)>,
                    call_function_returning_value<instance_container_t, return_t, scope_caller_t, decltype(convertedArguments)>
                >;
            return result_returner_t{}(
                container,
                methodID,
                std::move(convertedArguments)
            );
        }
    };
}
}