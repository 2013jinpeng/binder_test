#include <stdint.h>
#include <sys/types.h>

#include <binder/Parcel.h>
#include <binder/IMemory.h>
#include <utils/Errors.h> 
#include <utils/String16.h>
#include <utils/String8.h>


#include "IHelloService.h"


namespace android {

status_t BnHelloService::onTransact(
	uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)

{
	//int32_t policy = data.readInt32();

	//data.enforceInterface(DESCRIPTOR);
	int32_t policy = data.readInt32();
	String16 str = data.readString16();
	

	switch (code) {
		case HELLO: {	
			hello();
			return NO_ERROR;
		} break;
		case SAY_HELLO_TO: {			
			String16 str16 = data.readString16();
			String8 str8(str16);
			int32_t ret = say_hello_to(str8.string());
			reply->writeInt32(ret);
			return NO_ERROR;
		} break;
		
		default:
			return BBinder::onTransact(code, data, reply, flags);
	}

}

void BnHelloService::hello(void)
{
	printf("hello \n");
}

status_t BnHelloService::say_hello_to(const char * name)
{
	static int i = 0;
	
	printf("say hello to %s \n", name);
	i++;
	
	return i;
}


}





