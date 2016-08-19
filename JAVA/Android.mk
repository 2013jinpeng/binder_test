
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := HelloService.java IHelloService.java client_test_java.java
LOCAL_MODULE := client_test_java
include $(BUILD_JAVA_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := HelloService.java IHelloService.java server_test_java.java
LOCAL_MODULE := server_test_java
include $(BUILD_JAVA_LIBRARY)

