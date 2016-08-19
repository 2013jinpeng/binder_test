#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../common/binder.h"

#include "server_test.h"


int svcmgr_publish(struct binder_state *bs, void *target, const char *name, void *ptr)
{
    unsigned status;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_string16_x(&msg, SVC_MGR_NAME);
    bio_put_string16_x(&msg, name);
    bio_put_obj(&msg, ptr);

    if (binder_call(bs, &msg, &reply, target, SVC_MGR_ADD_SERVICE))
        return -1;

    status = bio_get_uint32(&reply);

    binder_done(bs, &msg, &reply);

    return status;
}


void hello()
{
	printf("say hello \n");
}

void say_hello_to(char *name)
{
	printf("say hello to %s\n", name);
}


int hello_server_handler(struct binder_state *bs,
                   struct binder_transaction_data *txn,
                   struct binder_io *msg,
                   struct binder_io *reply)
{
    struct svcinfo *si;
    uint16_t *s;
    unsigned len;
    void *ptr;
    uint32_t strict_policy;
	char name[512/4];
	int i;

//printf("txn->target.ptr:%x\n", (int)txn->target.ptr);
    strict_policy = bio_get_uint32(msg); 
	s = bio_get_string16(msg, &len);

	switch(txn->code) {
    case HELLO:
		hello();
        break;
    case SAY_HELLO_TO:
        s = bio_get_string16(msg, &len);
		if (s == NULL) {
			return -1;
		}
		for (i=0; i<len; i++) {  //将16bit的数据转化为8bit
			name[i] = s[i];
		}
		name[i] = '\0';
        say_hello_to(name);
        break;
    default:
        return -1;
    }

    return 0;
}



int main(int argc, char **argv)
{
    struct binder_state *bs;
    void *svcmgr = BINDER_SERVICE_MANAGER;
	int ret;

    bs = binder_open(128*1024);
	if (!bs) {
		printf("failed to open binder driver\n");
		return -1;
	}
	
	ret = svcmgr_publish(bs, svcmgr, HELLO_NAME, hello_server_handler);
	if (ret) {
		printf("failed to svcmgr_publish hello server ret:%d\n", ret);
		//return -1;
	}
	
	//printf("hello_server_handler:%x \n", (int)hello_server_handler);
	
	binder_loop(bs, hello_server_handler);
	
    return 0;
}

