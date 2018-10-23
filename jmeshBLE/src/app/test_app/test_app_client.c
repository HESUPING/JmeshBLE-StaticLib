#include"test_app_client.h"
#include"test_app_server.h"
#include"../../driver/jmesh_system.h"
#include"light_client.h"
#include"../../access/jmesh_access.h"
#include"../../access/jmesh_access_callback.h"
#include"../../onchip_system/os_timer_event.h"
#include"../../jmesh/jmesh_print.h"

test_message_count_t test_count= {0};
static os_timer_event_t test_app_timer;
static void test_client_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void test_app_timer_handler(const void* argc);
JMESH_VENDOR_MODEL_CREATE_START(test_client,TEST_CLIENT_COMPANY_ID,TEST_CLIENT_MODEL_ID,3)
    JMESH_MESSAGE_ADD(MESSAGE_TEST_CLIENT_STATUS,test_client_status_handler)

JMESH_MODEL_CREATE_END(test_client)

void test_client_init(void){
    jmesh_element_add_model(&element_app,&test_client);
		os_timer_event_set(&test_app_timer,5000,test_app_timer_handler,NULL);
}

void test_app_timer_handler(const void* argc)
{
		unsigned char data[20] = "hello world!\n";
		jmesh_access_send(10,0,1,&test_client,message_test_server_control,20,data);
}


static void test_client_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		print_buffer_info(len,data,"test_client receive: ");
		test_count.client_rev_count++;
}

void test_client_send(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len ,unsigned char* data)
{
    jmesh_mutex_lock();
    jmesh_access_send(dst,netkey_index,appkey_index,&test_client,message_test_server_control,len,data);
    jmesh_mutex_unlock();		
		test_count.client_send_count++;
}

void test_app_count_query(test_message_count_t* message_count)
{
		memcpy(message_count,&test_count,sizeof(test_message_count_t)); 
}


