#ifndef TEST_APP_SERVER_H
#define TEST_APP_SERVER_H
#include"../../access/jmesh_model.h"
#include"../../access/jmesh_access.h"


#define MESSAGE_TEST_SERVER_START               {0xc0,0x0a,0x01}
#define MESSAGE_TEST_SERVER_DATA                {0xc0,0x0a,0x02}
#define MESSAGE_TEST_SERVER_RESULT              {0xc0,0x0a,0x03}


JMESH_MESSAGE_CREATE(MESSAGE_TEST_SERVER_START,   message_test_server_start);
JMESH_MESSAGE_CREATE(MESSAGE_TEST_SERVER_DATA,   message_test_server_data);
JMESH_MESSAGE_CREATE(MESSAGE_TEST_SERVER_RESULT,   message_test_server_result);

JMESH_MODEL_NAME(test_server);
void test_server_init(void);






#define TEST_SERVER_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define TEST_SERVER_MODEL_ID   0x000a
#endif
