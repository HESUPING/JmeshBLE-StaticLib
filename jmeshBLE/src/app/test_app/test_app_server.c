#include"test_app_server.h"
#include"test_app_client.h"
#include"test_app_server_callback.h"
#include"test_app_client_callback.h"
#include"../../jmesh/jmesh_print.h"
static void test_server_control_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);

JMESH_VENDOR_MODEL_CREATE_START(test_server,TEST_SERVER_COMPANY_ID,TEST_SERVER_MODEL_ID,1)
    JMESH_MESSAGE_ADD(MESSAGE_TEST_SERVER_CONTROL,  test_server_control_handler)

JMESH_MODEL_CREATE_END(test_server)

void test_server_init(void){
    jmesh_element_add_model(&element_app,&test_server);
}

static void test_server_control_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
	test_count.server_count++;
		
}
