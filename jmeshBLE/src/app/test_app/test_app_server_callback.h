#ifndef TEST_APP_SERVER_CALLBACK_H
#define TEST_APP_SERVER_CALLBACK_H
#include"../../access/jmesh_model.h"


void test_server_start_callback(unsigned short addr,unsigned short aid,unsigned short num,unsigned char repeat,unsigned char interval);

unsigned short jmesh_server_data_callback(unsigned short src,unsigned short nid,unsigned short start_id,unsigned short tid);

#endif
