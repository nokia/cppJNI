cppJNI
=======
Java Native Interface (JNI) framework wrapper, which uses new C++ features in order to add type safety.

Requirements
--------
 * Boost 1.61 or higher (http://www.boost.org)
 * C++14 compatible compiler (clang >= 3.8, gcc >= 6.0)
 * google test for UT (>= 1.8)

Quick Start
--------
With below silly Java class:
```Java
package jni.test;

public class JNITest {
    private int privatePrimitiveField;
    private String privateObjectField;
    
    public JNITest(int primitiveParam, String objectParam) {
        this.privatePrimitiveField = primitiveParam;
        this.privateObjectField = objectParam;
    }
    
    public int getPrimitiveField() {
        return privatePrimitiveField;
    }
    
    public String getStringField() {
        return privateObjectField;
    }
}
```

Get back to C++ and prepare your Java class description:
```C++
#include <jni/method_signature.hpp>

//class description is a template that must derive it's sole template parameter
template<typename T>
struct MyJNIClass: T
{
    //path to your class package
    using class_path_t = typestring_is("jni/test/MyJNIClass");

    //here you create constructor signature: it returns object of your class, obviously, and takes one integer and string in turn
    MAKE_JAVA_CONSTRUCTORS(jni::types::Object<::MyJNIClass>(jni::types::Int, jni::types::String))
    
    //similarly you can declare methods
    MAKE_JAVA_METHOD(getPrimitiveField, jni::types::Method<jni::types::Int()>)
    MAKE_JAVA_METHOD(getStringField, jni::types::Method<jni::types::String()>)
};
```

Create JVM:
```C++
#include <virtual_machine.hpp>
...
jni::VirtualMachine vm({"-Djava.class.path=path-to-your-jar-file"});
```

Create some classes and work with them:
```C++
...
auto myClass = vm.loadClass<MyJNIClass>();

auto javaObject = myClass.Construct(5, "123ads");
cout << javaObject.getPrimitiveField() << " '" << javaObject.getStringField() << "'" << endl;
...
```
It can't be simpler!

TODO:
--------
    * registering of native methods
    * Java monitors support
    * arrays support
    * class field access
