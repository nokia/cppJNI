#include <type_traits>

#include "cppjni/mpl/all.hpp"
#include "cppjni/mpl/condition.hpp"
#include "cppjni/mpl/filter.hpp"
#include "cppjni/mpl/find.hpp"
#include "cppjni/mpl/find_if.hpp"
#include "cppjni/mpl/head.hpp"
#include "cppjni/mpl/identity.hpp"
#include "cppjni/mpl/join.hpp"
#include "cppjni/mpl/list.hpp"
#include "cppjni/mpl/optional.hpp"
#include "cppjni/mpl/pipeline.hpp"
#include "cppjni/mpl/size.hpp"
#include "cppjni/mpl/transform.hpp"
#include "cppjni/mpl/apply.hpp"
#include "cppjni/mpl/zip.hpp"

namespace test
{
    using namespace cppjni::mpl;
    using namespace std;
    
    struct A {};
    struct B {};
    
    template<typename T>
    using is_int = is_same<T, int>;
    
    template<typename T>
    using any = true_type;
    
    using testList1 = list<A, B, int>;
    using testList2 = list<list<A>, list<B>, list<int>>;
    
    template<typename T>
    using wrap_in_list = list<T>;
    
    static_assert(
        is_same<
            testList2,
            eager::apply<transform<wrap_in_list>, testList1>
        >::value,
        ""
    );
    
    static_assert(
        is_same<
            testList1,
            eager::apply<join, testList2>
        >::value,
        ""
    );
    
    static_assert(
        is_same<
            testList1,
            eager::apply<
                join, testList2
            >
        >::value,
        ""
    );
    
    static_assert(
        is_same<
            testList1,
            eager::apply<filter<any>, testList1>
        >::value,
        ""
    );
    
    static_assert(
        is_same<
            std::false_type,
            eager::apply<all<is_true>, testList1, identity>
        >::value,
        ""
    );
    
    static_assert(
        is_same<
            std::true_type,
            eager::apply<all<any>, testList1, identity>
        >::value,
        ""
    );
    
    static_assert(
        is_same<
            optional_value<int>,
            eager::apply<find_if<is_int>, testList1, optional>
        >::value,
        ""
    );
}
