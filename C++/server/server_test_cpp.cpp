//#define LOG_TAG "FregServer"
 
#include <stdlib.h>
#include <fcntl.h>
 
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>


#include "../common/IHelloService.h"

using namespace android;

 
int main()
{
	defaultServiceManager()->addService(String16(HELLO_NAME), new BnHelloService());
	ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
	
	return 0;
}




