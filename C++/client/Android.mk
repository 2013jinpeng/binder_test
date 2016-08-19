LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= client_test_cpp.cpp ../common/BpHelloService.cpp
LOCAL_MODULE_TAGS :=optional
LOCAL_CERTIFICATE := platform
LOCAL_MODULE := client_test_cpp
LOCAL_SHARED_LIBRARIES := libc liblog libcutils libutils libbinder
LOCAL_32_BIT_ONLY := true
include $(BUILD_EXECUTABLE)

