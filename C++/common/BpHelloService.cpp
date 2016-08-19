#include <stdint.h>
#include <sys/types.h>

#include <binder/Parcel.h>
#include <binder/IMemory.h>
#include <utils/Errors.h> 
#include <utils/String16.h>

#include "IHelloService.h"



namespace android {

void BpHelloService::hello(void) 
{
	Parcel data, reply;

	//data.writeInt32(0);
	data.writeInterfaceToken(BpHelloService::getInterfaceDescriptor());
	remote()->transact(HELLO, data, &reply);
}

status_t BpHelloService::say_hello_to(const char *name)
{
	Parcel data, reply;

	//data.writeInt32(0);
	data.writeInterfaceToken(BpHelloService::getInterfaceDescriptor());
	data.writeString16(String16(name));
	remote()->transact(SAY_HELLO_TO, data, &reply);

	return reply.readInt32();
}

//IMPLEMENT_META_INTERFACE(HelloService, "android.test.IHelloService"); 
IMPLEMENT_META_INTERFACE(HelloService, "IHelloService");   //NAME为描述符,java会通过该描述符进行检测

}




















