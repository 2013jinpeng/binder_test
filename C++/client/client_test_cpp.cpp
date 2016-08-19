
//#define LOG_TAG "FregClient"
 
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include <utils/String8.h>

 
#include "../common/IHelloService.h"

using namespace android;

 
int main()
{
    sp<IBinder> binder = defaultServiceManager()->getService(String16(HELLO_NAME));
    if(binder == NULL) {
        printf("Failed to get freg service: %s.\n", HELLO_NAME);
        return -1;
    }

    sp<IHelloService> service = IHelloService::asInterface(binder); 
    if(service == NULL) {
        printf("Failed to get freg service interface.\n");
        return -2;
    }
 
    service->hello();

	service->say_hello_to("haha chenjp");
 
    return 0;
}



