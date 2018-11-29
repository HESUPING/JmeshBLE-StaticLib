#include"test_app_server.h"
#include"test_app_client.h"
#include"test_app_server_callback.h"
#include"test_app_client_callback.h"
#include"../../jmesh/jmesh_print.h"
static void test_server_start_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void test_server_data_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void test_server_result_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);

JMESH_VENDOR_MODEL_CREATE_START(test_server,TEST_SERVER_COMPANY_ID,TEST_SERVER_MODEL_ID,3)
    JMESH_MESSAGE_ADD(MESSAGE_TEST_SERVER_START,  test_server_start_handler)
    JMESH_MESSAGE_ADD(MESSAGE_TEST_SERVER_DATA,  test_server_data_handler)
    JMESH_MESSAGE_ADD(MESSAGE_TEST_SERVER_RESULT,  test_server_result_handler)

JMESH_MODEL_CREATE_END(test_server)


void test_server_init(void){
    jmesh_element_add_model(&element_app,&test_server);
}

static void test_server_start_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    unsigned short addr;
    unsigned short num;
		unsigned char repeat = 0;
		unsigned char interval = 5;
    print_info("start handler %d\n",len);
    if(len==6) {
        JMESH_BIG_ENDIAN_PICK2(addr, data);
        JMESH_BIG_ENDIAN_PICK2(num, data + 2);
				repeat = data[4];
				interval = data[5];
        test_server_start_callback(addr,aid, num,repeat,interval);
				
        jmesh_access_send(src, nid, aid, &test_server, message_test_client_start_status, 4, data);
    }

}
static void test_server_data_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    unsigned short start_id,tid,received_count;
    unsigned char buff[6];
    if(len==6){
        JMESH_BIG_ENDIAN_PICK2(start_id,data);
        JMESH_BIG_ENDIAN_PICK2(tid,data+2);
        received_count=jmesh_server_data_callback(src,nid,start_id,tid);
        JMESH_BIG_ENDIAN_FILL2(tid,buff);
        JMESH_BIG_ENDIAN_FILL2(received_count,buff+2);
				memcpy(buff+4,data+4,2);
        jmesh_access_send(src,nid,aid,&test_server,message_test_client_data_status,6,buff);
    }
}
static void test_server_result_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    unsigned char buff[8];
    if(len==0){
        JMESH_BIG_ENDIAN_FILL2(test_result.dst,buff);
        JMESH_BIG_ENDIAN_FILL2(test_result.sent,buff+2);
        JMESH_BIG_ENDIAN_FILL2(test_result.received,buff+4);
        JMESH_BIG_ENDIAN_FILL2(test_result.responsed,buff+6);
        jmesh_access_send(src,nid,aid,&test_server,message_test_client_result_status,8,buff);
    }
}


