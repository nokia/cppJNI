package jni.test;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class JNITest
{
    public static final int CONSTANT_PRIMITIVE = 12345;
    public static final long CONSTANT_PRIMITIVE_LONG = 654321L;
    public static final String CONSTANT_STRING = "qwe123";
    
    private int privatePrimitiveField;
    private String privateObjectField;
    
    public JNITest(int primitiveParam, String objectParam) {
        this.privatePrimitiveField = primitiveParam;
        this.privateObjectField = objectParam;
    }
    
    public static JNITest staticFactory(int primitiveParam, String objectParam) {
        return new JNITest(primitiveParam, objectParam);
    }
    
    public static JNITest staticFactory() {
        return new JNITest(CONSTANT_PRIMITIVE, CONSTANT_STRING);
    }
    
    public static int staticReturningPrimitive() {
        return CONSTANT_PRIMITIVE;
    }
    
    public static void staticVoid() {
        System.out.println("I am void static public method");
    }
    
    public static long staticReturningPrimitive(int x) {
        return CONSTANT_PRIMITIVE_LONG + x;
    }
    
    public static String staticReturningString(String str) {
        return str + CONSTANT_STRING;
    }
    
    public int getPrimitiveField() {
        return privatePrimitiveField;
    }
    public int getPrimitiveField2() {
        return privatePrimitiveField + 2;
    }
    
    public String getStringField() {
        return privateObjectField;
    }
    
    public void setStringField(String value) {
        privateObjectField = value;
    }
    
    public JNITest getObjectField() {
        return this;
    }
    
    public void incrementIntField(int about) {
        privatePrimitiveField += about;
    }
    
    public void throwException() {
        throw new RuntimeException("Some message");
    }
    
    public static List<String> getStringList() {
        List<String> result = new ArrayList<String>();
        result.add("first");
        result.add("second");
        result.add("third");
        return result;
    }
}