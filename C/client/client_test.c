#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../common/binder.h"

#include "../server/server_test.h"



void *svcmgr_lookup(struct binder_state *bs, void *target, const char *name)
{
    void *ptr;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_string16_x(&msg, SVC_MGR_NAME);
    bio_put_string16_x(&msg, name);

    if (binder_call(bs, &msg, &reply, target, SVC_MGR_CHECK_SERVICE))
        return 0;

    ptr = bio_get_ref(&reply);

    if (ptr)
        binder_acquire(bs, ptr);

    binder_done(bs, &msg, &reply);

    return ptr;
}



void hello(struct binder_state *bs, void *target)
{
	unsigned iodata[512/4];
	struct binder_io msg, reply;

	bio_init(&msg, iodata, sizeof(iodata), 4);
	
	//writeInterfaceToken作用
	bio_put_uint32(&msg, 0);
	bio_put_string16_x(&msg, "IHelloService");

	if (binder_call(bs, &msg, &reply, target, HELLO)) {
		return;
	}
		
	binder_done(bs, &msg, &reply);
}

void say_hello_to(struct binder_state *bs, void *target, char *name)
{
	unsigned iodata[512/4];
	struct binder_io msg, reply;

	bio_init(&msg, iodata, sizeof(iodata), 4);
	
	//writeInterfaceToken作用
	bio_put_uint32(&msg, 0);
	bio_put_string16_x(&msg, "IHelloService");

	bio_put_string16_x(&msg, name);

	if (binder_call(bs, &msg, &reply, target, SAY_HELLO_TO)) {
		return;
	}
		
	binder_done(bs, &msg, &reply);
}



int main(int argc, char **argv)
{
    int fd;
    struct binder_state *bs;
    void *svcmgr = BINDER_SERVICE_MANAGER;
	void *hello_handle;
	

    bs = binder_open(128*1024);
	if (!bs) {
		printf("failed to open binder driver\n");
		return -1;
	}
	
	hello_handle = svcmgr_lookup(bs, svcmgr, HELLO_NAME);
	if (!hello_handle) {
		fprintf(stderr, "failed to get hello service\n");
		return -1;
	}
	//printf("hello_handle:%x \n", (int)hello_handle);
	
	hello(bs, hello_handle);

	say_hello_to(bs, hello_handle, "chenjp");
	
	
    return 0;
}

