#ifndef TEST_APP_CLIENT_H
#define TEST_APP_CLIENT_H
#include"test_app_server.h"
#include"../../access/jmesh_model.h"

#define MESSAGE_TEST_CLIENT_STATUS                 {0xc0,0x08,0x01}
typedef struct test_message_count_st{
		unsigned short client_send_count;
		unsigned short client_rev_count;
		unsigned short server_count;
}test_message_count_t;

JMESH_MESSAGE_CREATE(MESSAGE_TEST_CLIENT_STATUS,       message_test_client_status);

JMESH_MODEL_NAME(test_client);
extern test_message_count_t test_count;
void test_client_init(void);
void test_client_send(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len ,unsigned char* data);
void test_app_count_query(test_message_count_t* message_count);
#define TEST_CLIENT_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define TEST_CLIENT_MODEL_ID   0x0008























#endif
