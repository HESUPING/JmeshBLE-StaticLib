#ifndef TEST_APP_SERVER_H
#define TEST_APP_SERVER_H
#include"../../access/jmesh_model.h"
#include"../../access/jmesh_access.h"


#define MESSAGE_TEST_SERVER_CONTROL            {0xc0,0x07,0x01}


JMESH_MESSAGE_CREATE(MESSAGE_TEST_SERVER_CONTROL,   message_test_server_control);

JMESH_MODEL_NAME(test_server);
void test_server_init(void);
#define TEST_SERVER_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define TEST_SERVER_MODEL_ID   0x0007
#endif
