#include"test_app_client.h"
#include"test_app_server.h"
#include"../../driver/jmesh_system.h"
#include"../../network/jmesh_seq.h"
#include"../../access/jmesh_access.h"
#include"../../access/jmesh_access_callback.h"
#include"../../onchip_system/os_timer_event.h"
#include"../../jmesh/jmesh_print.h"
#include "test_app_client_callback.h"


static void test_client_start_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void test_client_data_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void test_client_result_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);

JMESH_VENDOR_MODEL_CREATE_START(test_client,TEST_CLIENT_COMPANY_ID,TEST_CLIENT_MODEL_ID,3)
    JMESH_MESSAGE_ADD(MESSAGE_TEST_CLIENT_START_STATUS,test_client_start_status_handler)
    JMESH_MESSAGE_ADD(MESSAGE_TEST_CLIENT_DATA_STATUS,test_client_data_status_handler)
    JMESH_MESSAGE_ADD(MESSAGE_TEDT_CLIENT_RESULT_STATUS,test_client_result_status_handler)

JMESH_MODEL_CREATE_END(test_client)


void test_client_init(void)
{
    jmesh_element_add_model(&element_app,&test_client);
}
void test_client_start(unsigned short dst,unsigned short aid,unsigned short addr,unsigned short num,unsigned char repeat,unsigned char interval){
    unsigned char buff[6];
    JMESH_BIG_ENDIAN_FILL2(addr,buff);
    JMESH_BIG_ENDIAN_FILL2(num,buff+2);
		buff[4] = repeat;
		buff[5] = interval;
    test_result.dst=addr;
    test_result.sent=0;
    test_result.received=0;
    test_result.responsed=0;
    print_info("test start dst %x addr %x,num %d\n",dst,addr,num);
    jmesh_access_send(dst,0,aid,&test_client,message_test_server_start,6,buff);

}
void test_client_send(unsigned short dst,unsigned short aid,unsigned short start_id,unsigned short tid,unsigned short test_seq)
{
    unsigned char buff[6];
    JMESH_BIG_ENDIAN_FILL2(start_id,buff);
    JMESH_BIG_ENDIAN_FILL2(tid,buff+2);
    JMESH_BIG_ENDIAN_FILL2(test_seq,buff+4);
    print_info("test client send dst %x,tid %d\n",dst,tid);
    jmesh_access_send(dst,0,aid,&test_client,message_test_server_data,6,buff);
}
void test_client_result(unsigned short dst,unsigned short aid)
{
    jmesh_access_send(dst,0,aid,&test_client,message_test_server_result,0,NULL);
}


static void test_client_start_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    unsigned short addr,num;
    if(len==4){
        JMESH_BIG_ENDIAN_PICK2(addr,data);
        JMESH_BIG_ENDIAN_PICK2(num,data+2);
        test_client_start_status_callback(src,addr,num);
    }
}
static void test_client_data_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    unsigned short tid,received,test_seq;
    if(len==6){
        JMESH_BIG_ENDIAN_PICK2(tid,data);
        JMESH_BIG_ENDIAN_PICK2(received,data+2);
        JMESH_BIG_ENDIAN_PICK2(test_seq,data+4);	
        test_client_data_status_callback(src,tid,received,test_seq);
			
    }
}
static void test_client_result_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    unsigned short addr,sent,received,responsed;
    if(len==8){
        JMESH_BIG_ENDIAN_PICK2(addr,data);
        JMESH_BIG_ENDIAN_PICK2(sent,data+2);
        JMESH_BIG_ENDIAN_PICK2(received,data+4);
        JMESH_BIG_ENDIAN_PICK2(responsed,data+6);
        test_client_result_status_callback(src,addr,sent,received,responsed);
    }
}



