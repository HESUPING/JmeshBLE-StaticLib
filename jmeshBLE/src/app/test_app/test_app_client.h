#ifndef TEST_APP_CLIENT_H
#define TEST_APP_CLIENT_H
#include"test_app_server.h"
#include"../../access/jmesh_model.h"

#define MESSAGE_TEST_CLIENT_START_STATUS                    {0xc0,0x0b,0x01}
#define MESSAGE_TEST_CLIENT_DATA_STATUS                     {0xc0,0x0b,0x02}
#define MESSAGE_TEDT_CLIENT_RESULT_STATUS                   {0xc0,0x0b,0x03}

JMESH_MESSAGE_CREATE(MESSAGE_TEST_CLIENT_START_STATUS,      message_test_client_start_status);
JMESH_MESSAGE_CREATE(MESSAGE_TEST_CLIENT_DATA_STATUS,       message_test_client_data_status);
JMESH_MESSAGE_CREATE(MESSAGE_TEDT_CLIENT_RESULT_STATUS,     message_test_client_result_status);

JMESH_MODEL_NAME(test_client);

typedef struct st_test_resut{
    unsigned short dst;
    unsigned short sent;
    unsigned short received;
    unsigned short responsed;
		unsigned short test_seq;
}test_result_t;

extern test_result_t test_result;

void test_client_init(void);
void test_client_start(unsigned short dst,unsigned short aid,unsigned short addr,unsigned short num,unsigned char repeat,unsigned char interval);
void test_client_send(unsigned short dst,unsigned short aid,unsigned short start_id,unsigned short tid,unsigned short test_seq);
void test_client_result(unsigned short dst,unsigned short aid);

#define TEST_CLIENT_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define TEST_CLIENT_MODEL_ID   0x000b























#endif
