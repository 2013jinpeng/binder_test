#ifndef ANDROID_IHELLOSERVICE_H
#define ANDROID_IHELLOSERVICE_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/KeyedVector.h>

#define HELLO_NAME "Hello"


namespace android {

enum {
	HELLO = IBinder::FIRST_CALL_TRANSACTION,
	SAY_HELLO_TO
};


class IHelloService: public IInterface
{
public:
    DECLARE_META_INTERFACE(HelloService);

	virtual void hello(void) = 0;
	virtual status_t say_hello_to(const char *name) = 0;

};


class BnHelloService: public BnInterface<IHelloService>
{
public:
    virtual status_t onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);

	virtual void hello(void);
	virtual status_t say_hello_to(const char *name);

};


class BpHelloService: public BpInterface<IHelloService>
{
public:
	BpHelloService(const sp<IBinder>& impl) 
        : BpInterface<IHelloService>(impl)
    {
 
    }
	
	virtual void hello(void);
	virtual status_t say_hello_to(const char *name);
};



}; // namespace android

#endif // ANDROID_IHELLOSERVICE_H

